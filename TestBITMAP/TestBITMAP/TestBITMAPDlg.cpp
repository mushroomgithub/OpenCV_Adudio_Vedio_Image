
// TestBITMAPDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestBITMAP.h"
#include "TestBITMAPDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestBITMAPDlg 对话框




CTestBITMAPDlg::CTestBITMAPDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestBITMAPDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	TheImage=NULL;
	bmi=NULL;
	bmih=NULL;
	palettes=NULL;
}
CTestBITMAPDlg::~CTestBITMAPDlg()
{
	cvReleaseImage(&TheImage);
}
void CTestBITMAPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestBITMAPDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CTestBITMAPDlg 消息处理程序

BOOL CTestBITMAPDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CvSize imageSize;
	imageSize.width=IMAGE_WIDTH;
	imageSize.height=IMAGE_HEIGTH;
	TheImage=cvCreateImage(imageSize,IPL_DEPTH_8U,IMAGE_CHANNELS);
	cvNamedWindow("图像数据初始化前显示窗口");//显示刚刚创建的图像，默认是灰色的
	cvShowImage("图像数据初始化前显示窗口",TheImage);
	
	//根据图像通道数，初始化DIB图像数据,一下不是必须的
	if(TheImage->nChannels==1)//对灰度图像
	{
		float dx=(TheImage->width/256.0f);
		for(int w=0;w<TheImage->width;w++)
			for(int h=0;h<TheImage->height;h++)
				TheImage->imageData[w*(TheImage->height)+h]=(char)(w/dx);//复制数据到IPL
		/*for(int h=0;h<TheImage->height;h++)
			for(int w=0;w<TheImage->width;w++)
				TheImage->imageData[TheImage->width*h+w]=(char)(h/dx);*/
	}
	else if(TheImage->nChannels==3)//对于RGB图像
	{
		IplImage *Temp=cvCreateImage(imageSize,IPL_DEPTH_8U,1);
		int h,w;
		float dx=(Temp->width/256.0f);//dx=1.00000
		for(w=0;w<Temp->width;w++)
			for(h=0;h<Temp->height;h++)
				Temp->imageData[Temp->height*w+h]=(char)(w/dx);
		/*for(h=0;h<TheImage->height;h++)
			for(w=0;w<TheImage->width;w++)
				TheImage->imageData[TheImage->widthStep*h+w]=(char)(h/dx);*/
		cvSetImageCOI(TheImage,1);//选择蓝色通道
		cvCopy(Temp,TheImage);

		for(w=0;w<Temp->width;w++)
			for(h=0;h<Temp->height;h++)
				Temp->imageData[Temp->height*w+h]=(char)(255-w/dx);
		/*for(h=0;h<TheImage->height;h++)
			for(w=0;w<TheImage->width;w++)
				TheImage->imageData[TheImage->widthStep*h+w]=(char)(255-h/dx);*/
		cvSetImageCOI(TheImage,2);//选择绿色通道
		cvCopy(Temp,TheImage);

		for(w=0;w<Temp->width;w++)
			for(h=0;h<Temp->height;h++)
				Temp->imageData[Temp->height*w+h]=(char)(w/dx);
		/*for(h=0;h<TheImage->height;h++)
			for(w=0;w<TheImage->width;w++)
				TheImage->imageData[TheImage->widthStep*h+w]=(char)(h/dx);*/
		cvSetImageCOI(TheImage,3);//选择红色通道
		cvCopy(Temp,TheImage);

		cvReleaseImage(&Temp);
	}

	bmi=(BITMAPINFO*)buff;
	bmih=&bmi->bmiHeader;
	memset(bmih,0,sizeof(*bmih));
	bmih->biSize=sizeof(BITMAPINFOHEADER);
	bmih->biBitCount=8*TheImage->nChannels;
	bmih->biCompression=BI_RGB;
	bmih->biWidth=IMAGE_WIDTH;
	bmih->biHeight=-IMAGE_HEIGTH;
	bmih->biPlanes=1;//必须为1
	palettes=bmi->bmiColors;
	if(TheImage->nChannels==1)//如果是单通道，创建调色板
	{
		for(int i=0;i<256;i++)
		{
			palettes[i].rgbBlue=palettes[i].rgbGreen=palettes[i].rgbRed=(BYTE)i;
			palettes[i].rgbReserved=0;
		}
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTestBITMAPDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestBITMAPDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		DisPlayData();//显示图像数据

		CDialogEx::OnPaint();
	}
	//DisPlayData();
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTestBITMAPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTestBITMAPDlg::DisPlayData(void)
{
	//CClientDC dc(this);
	CPaintDC dc(this);
	CDC *pDC=&dc;
	StretchDIBits(pDC->GetSafeHdc(),
		0,
		0,
		(int)IMAGE_WIDTH,
		(int)IMAGE_HEIGTH,
		0,
		0,
		IMAGE_WIDTH,
		IMAGE_HEIGTH,
		TheImage->imageData,
		bmi,
		DIB_RGB_COLORS,
		SRCCOPY);
	RedrawWindow(NULL,
		NULL,
		RDW_INVALIDATE);
	//Invalidate(FALSE);
}
