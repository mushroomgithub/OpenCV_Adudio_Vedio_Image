#include<iostream>
#include"cv.h"
#include"highgui.h"
using namespace std;
int main(int argc, char* argv[])                       //  Canny ��Ե���
{
	IplImage* pImage = NULL;
	IplImage* pImgCanny = NULL;
	IplImage* pImg8u = NULL;
	IplImage* pImg8uSmooth = NULL;

	pImage = cvLoadImage(argv[1]);                //  ���������ͼ��
	if (!pImage) return 0; 
	cvNamedWindow("Example6-in",CV_WINDOW_AUTOSIZE);
	cvShowImage("Example6-in",pImage);

	pImg8u      =cvCreateImage(cvGetSize(pImage),IPL_DEPTH_8U,1);//����һ����ԭͼ��ߴ��С��ͬ�ĵ�ͨ����λ��Ϊ8��ͼ�����ָ��
	pImg8uSmooth=cvCreateImage(cvGetSize(pImage),IPL_DEPTH_8U,1);
	pImgCanny   =cvCreateImage(cvGetSize(pImage),IPL_DEPTH_8U,1);//cvCannyֻ���ܵ�ͨ��ͼ����Ϊ����

	cvCvtColor(pImage,pImg8u,CV_BGR2GRAY);//ʵ��RGB��ɫ�ؼ����Ҷ���ɫ�ռ��ת��
	cvSmooth(pImg8u,pImg8uSmooth,CV_GAUSSIAN,3,0,0);//ƽ����˹�˲�
	cvCanny(pImg8uSmooth,pImgCanny,100,200,3);//Canny��Ե���

	cvNamedWindow("Example6-out",CV_WINDOW_AUTOSIZE);
	cvShowImage("Example6-out", pImgCanny);       //  ��ʾCanny��Ե��⴦��֮���ͼ����
	cvWaitKey(0);

	cvReleaseImage(&pImage);
	cvReleaseImage(&pImg8u);
	cvReleaseImage(&pImg8uSmooth);
	cvReleaseImage(&pImgCanny);

	cvDestroyWindow("Example6-in");
	cvDestroyWindow("Example6-out");
	return 0;
}
