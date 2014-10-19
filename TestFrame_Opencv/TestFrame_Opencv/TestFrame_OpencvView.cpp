
// TestFrame_OpencvView.cpp : CTestFrame_OpencvView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "TestFrame_Opencv.h"
#endif

#include "TestFrame_OpencvDoc.h"
#include "TestFrame_OpencvView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestFrame_OpencvView

IMPLEMENT_DYNCREATE(CTestFrame_OpencvView, CScrollView)

BEGIN_MESSAGE_MAP(CTestFrame_OpencvView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTestFrame_OpencvView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CTestFrame_OpencvView 构造/析构

CTestFrame_OpencvView::CTestFrame_OpencvView()
{
	// TODO: 在此处添加构造代码

}

CTestFrame_OpencvView::~CTestFrame_OpencvView()
{
}

BOOL CTestFrame_OpencvView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CTestFrame_OpencvView 绘制

void CTestFrame_OpencvView::OnDraw(CDC* pDC)//测试DrawToHDC在Frame中显示图像，和在对话框中调用StrechDlBits函数显示图像作对比
{
	CTestFrame_OpencvDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CvvImage img;
	img.Load("游戏动漫.jpg");
	HDC hDC=pDC->GetSafeHdc();
	CRect rect(0,0,img.Width(),img.Height());
	img.DrawToHDC(hDC,&rect);
	CSize sizeTotal;
	sizeTotal.cx=img.Width();
	sizeTotal.cy=img.Height();
	SetScrollSizes(MM_TEXT,sizeTotal);//设置滚动条范围为图像的尺寸
	ResizeParentToFit();//令视图窗口的大小控制其父窗口框架窗口的大小
}


// CTestFrame_OpencvView 打印


void CTestFrame_OpencvView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CTestFrame_OpencvView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CTestFrame_OpencvView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CTestFrame_OpencvView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CTestFrame_OpencvView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTestFrame_OpencvView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CTestFrame_OpencvView 诊断

#ifdef _DEBUG
void CTestFrame_OpencvView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CTestFrame_OpencvView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CTestFrame_OpencvDoc* CTestFrame_OpencvView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestFrame_OpencvDoc)));
	return (CTestFrame_OpencvDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestFrame_OpencvView 消息处理程序
