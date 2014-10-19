
// TestBITMAPDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestBITMAP.h"
#include "TestBITMAPDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CTestBITMAPDlg �Ի���




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


// CTestBITMAPDlg ��Ϣ�������

BOOL CTestBITMAPDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CvSize imageSize;
	imageSize.width=IMAGE_WIDTH;
	imageSize.height=IMAGE_HEIGTH;
	TheImage=cvCreateImage(imageSize,IPL_DEPTH_8U,IMAGE_CHANNELS);
	cvNamedWindow("ͼ�����ݳ�ʼ��ǰ��ʾ����");//��ʾ�ոմ�����ͼ��Ĭ���ǻ�ɫ��
	cvShowImage("ͼ�����ݳ�ʼ��ǰ��ʾ����",TheImage);
	
	//����ͼ��ͨ��������ʼ��DIBͼ������,һ�²��Ǳ����
	if(TheImage->nChannels==1)//�ԻҶ�ͼ��
	{
		float dx=(TheImage->width/256.0f);
		for(int w=0;w<TheImage->width;w++)
			for(int h=0;h<TheImage->height;h++)
				TheImage->imageData[w*(TheImage->height)+h]=(char)(w/dx);//�������ݵ�IPL
		/*for(int h=0;h<TheImage->height;h++)
			for(int w=0;w<TheImage->width;w++)
				TheImage->imageData[TheImage->width*h+w]=(char)(h/dx);*/
	}
	else if(TheImage->nChannels==3)//����RGBͼ��
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
		cvSetImageCOI(TheImage,1);//ѡ����ɫͨ��
		cvCopy(Temp,TheImage);

		for(w=0;w<Temp->width;w++)
			for(h=0;h<Temp->height;h++)
				Temp->imageData[Temp->height*w+h]=(char)(255-w/dx);
		/*for(h=0;h<TheImage->height;h++)
			for(w=0;w<TheImage->width;w++)
				TheImage->imageData[TheImage->widthStep*h+w]=(char)(255-h/dx);*/
		cvSetImageCOI(TheImage,2);//ѡ����ɫͨ��
		cvCopy(Temp,TheImage);

		for(w=0;w<Temp->width;w++)
			for(h=0;h<Temp->height;h++)
				Temp->imageData[Temp->height*w+h]=(char)(w/dx);
		/*for(h=0;h<TheImage->height;h++)
			for(w=0;w<TheImage->width;w++)
				TheImage->imageData[TheImage->widthStep*h+w]=(char)(h/dx);*/
		cvSetImageCOI(TheImage,3);//ѡ���ɫͨ��
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
	bmih->biPlanes=1;//����Ϊ1
	palettes=bmi->bmiColors;
	if(TheImage->nChannels==1)//����ǵ�ͨ����������ɫ��
	{
		for(int i=0;i<256;i++)
		{
			palettes[i].rgbBlue=palettes[i].rgbGreen=palettes[i].rgbRed=(BYTE)i;
			palettes[i].rgbReserved=0;
		}
	}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestBITMAPDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		DisPlayData();//��ʾͼ������

		CDialogEx::OnPaint();
	}
	//DisPlayData();
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
