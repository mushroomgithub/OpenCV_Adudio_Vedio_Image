
// TestFrame_OpencvView.h : CTestFrame_OpencvView ��Ľӿ�
//

#pragma once
#include<cv.h>
#include<highgui.h>
#include<cvaux.h>
#include"cvvImage.h"
class CTestFrame_OpencvView : public CScrollView
{
protected: // �������л�����
	CTestFrame_OpencvView();
	DECLARE_DYNCREATE(CTestFrame_OpencvView)

// ����
public:
	CTestFrame_OpencvDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CTestFrame_OpencvView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // TestFrame_OpencvView.cpp �еĵ��԰汾
inline CTestFrame_OpencvDoc* CTestFrame_OpencvView::GetDocument() const
   { return reinterpret_cast<CTestFrame_OpencvDoc*>(m_pDocument); }
#endif

