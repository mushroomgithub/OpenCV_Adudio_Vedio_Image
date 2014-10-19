
// TestFrame_OpencvView.h : CTestFrame_OpencvView 类的接口
//

#pragma once
#include<cv.h>
#include<highgui.h>
#include<cvaux.h>
#include"cvvImage.h"
class CTestFrame_OpencvView : public CScrollView
{
protected: // 仅从序列化创建
	CTestFrame_OpencvView();
	DECLARE_DYNCREATE(CTestFrame_OpencvView)

// 特性
public:
	CTestFrame_OpencvDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CTestFrame_OpencvView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // TestFrame_OpencvView.cpp 中的调试版本
inline CTestFrame_OpencvDoc* CTestFrame_OpencvView::GetDocument() const
   { return reinterpret_cast<CTestFrame_OpencvDoc*>(m_pDocument); }
#endif

