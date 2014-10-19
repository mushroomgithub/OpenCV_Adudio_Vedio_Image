
// TestBITMAPDlg.h : ͷ�ļ�
//

#pragma once

#include<cv.h>
#include<highgui.h>
#include<cvaux.h>
#define  IMAGE_WIDTH 256
#define  IMAGE_HEIGTH 256
#define  IMAGE_CHANNELS 3

// CTestBITMAPDlg �Ի���
class CTestBITMAPDlg : public CDialogEx
{
// ����
public:
	CTestBITMAPDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CTestBITMAPDlg();
// �Ի�������
	enum { IDD = IDD_TESTBITMAP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
