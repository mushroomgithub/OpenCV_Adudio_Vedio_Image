
// TestFrame_OpencvView.cpp : CTestFrame_OpencvView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTestFrame_OpencvView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CTestFrame_OpencvView ����/����

CTestFrame_OpencvView::CTestFrame_OpencvView()
{
	// TODO: �ڴ˴���ӹ������

}

CTestFrame_OpencvView::~CTestFrame_OpencvView()
{
}

BOOL CTestFrame_OpencvView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CScrollView::PreCreateWindow(cs);
}

// CTestFrame_OpencvView ����

void CTestFrame_OpencvView::OnDraw(CDC* pDC)//����DrawToHDC��Frame����ʾͼ�񣬺��ڶԻ����е���StrechDlBits������ʾͼ�����Ա�
{
	CTestFrame_OpencvDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	CvvImage img;
	img.Load("��Ϸ����.jpg");
	HDC hDC=pDC->GetSafeHdc();
	CRect rect(0,0,img.Width(),img.Height());
	img.DrawToHDC(hDC,&rect);
	CSize sizeTotal;
	sizeTotal.cx=img.Width();
	sizeTotal.cy=img.Height();
	SetScrollSizes(MM_TEXT,sizeTotal);//���ù�������ΧΪͼ��ĳߴ�
	ResizeParentToFit();//����ͼ���ڵĴ�С�����丸���ڿ�ܴ��ڵĴ�С
}


// CTestFrame_OpencvView ��ӡ


void CTestFrame_OpencvView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CTestFrame_OpencvView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CTestFrame_OpencvView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CTestFrame_OpencvView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CTestFrame_OpencvView ���

#ifdef _DEBUG
void CTestFrame_OpencvView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CTestFrame_OpencvView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CTestFrame_OpencvDoc* CTestFrame_OpencvView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestFrame_OpencvDoc)));
	return (CTestFrame_OpencvDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestFrame_OpencvView ��Ϣ�������
