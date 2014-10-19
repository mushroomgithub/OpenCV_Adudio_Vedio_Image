#include<iostream>
#include"cv.h"
#include"highgui.h"
using namespace std;
int main(int argc, char* argv[])                       //  Canny 边缘检测
{
	IplImage* pImage = NULL;
	IplImage* pImgCanny = NULL;
	IplImage* pImg8u = NULL;
	IplImage* pImg8uSmooth = NULL;

	pImage = cvLoadImage(argv[1]);                //  输入待处理图像
	if (!pImage) return 0; 
	cvNamedWindow("Example6-in",CV_WINDOW_AUTOSIZE);
	cvShowImage("Example6-in",pImage);

	pImg8u      =cvCreateImage(cvGetSize(pImage),IPL_DEPTH_8U,1);//创建一副和原图像尺寸大小相同的单通道的位深为8的图像对象指针
	pImg8uSmooth=cvCreateImage(cvGetSize(pImage),IPL_DEPTH_8U,1);
	pImgCanny   =cvCreateImage(cvGetSize(pImage),IPL_DEPTH_8U,1);//cvCanny只接受单通道图像作为输入

	cvCvtColor(pImage,pImg8u,CV_BGR2GRAY);//实现RGB彩色控件到灰度颜色空间的转换
	cvSmooth(pImg8u,pImg8uSmooth,CV_GAUSSIAN,3,0,0);//平滑高斯滤波
	cvCanny(pImg8uSmooth,pImgCanny,100,200,3);//Canny边缘检测

	cvNamedWindow("Example6-out",CV_WINDOW_AUTOSIZE);
	cvShowImage("Example6-out", pImgCanny);       //  显示Canny边缘检测处理之后的图像结果
	cvWaitKey(0);

	cvReleaseImage(&pImage);
	cvReleaseImage(&pImg8u);
	cvReleaseImage(&pImg8uSmooth);
	cvReleaseImage(&pImgCanny);

	cvDestroyWindow("Example6-in");
	cvDestroyWindow("Example6-out");
	return 0;
}
