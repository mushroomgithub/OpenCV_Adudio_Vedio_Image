
// TestBITMAPDlg.h : 头文件
//

#pragma once

#include<cv.h>
#include<highgui.h>
#include<cvaux.h>
#define  IMAGE_WIDTH 256
#define  IMAGE_HEIGTH 256
#define  IMAGE_CHANNELS 3

// CTestBITMAPDlg 对话框
class CTestBITMAPDlg : public CDialogEx
{
// 构造
public:
	CTestBITMAPDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CTestBITMAPDlg();
// 对话框数据
	enum { IDD = IDD_TESTBITMAP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	IplImage *TheImage;
	BITMAPINFO *bmi;
	BITMAPINFOHEADER *bmih;
	RGBQUAD *palettes;
	unsigned int buff[sizeof(BITMAPFILEHEADER)+sizeof(RGBQUAD)*256];
public:
	void DisPlayData(void);
};
