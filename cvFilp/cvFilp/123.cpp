#include "stdio.h"
#include "cv.h"
#include "highgui.h"
int main()
{
	IplImage *pSrcImg = NULL;
	IplImage *pClnImgX = NULL;
	IplImage *pClnImgY = NULL;
	IplImage *pClnImgX_Y = NULL;

	pSrcImg = cvLoadImage("Hydrangeas.jpg", 1);//1表示加载的图像强制转换为彩色图像
	//pSrcImg = cvLoadImage("Hydrangeas.jpg", 0);//0表示加载的图像强制转换为灰色图像
	if (pSrcImg == NULL)
	{
		printf("Fail to load images\n");
		return -1;
	}

	pClnImgX = cvCloneImage(pSrcImg);//从原图克隆出三幅图像，用于不同的转换
	pClnImgY = cvCloneImage(pSrcImg);
	pClnImgX_Y = cvCloneImage(pSrcImg);

	if (pClnImgX == NULL)
	{
		printf("Fail to clone the image\n");
		return -1;
	}
	if (pClnImgY == NULL)
	{
		printf("Fail to clone the image\n");
		return -1;
	}
	if (pClnImgX_Y == NULL)
	{
		printf("Fail to clone the image\n");
		return -1;
	}

	cvFlip(pClnImgX, NULL,0); //核心在这里 //不是cvFlip(src,pClnImg, 0);//pClinlmg必须先载入图像，或者复制图像！,将pCInimg图像沿X轴翻转,即垂直镜像
	cvFlip(pClnImgY, NULL,1);//将pCInimg图像沿X轴翻转,即水平镜像
	cvFlip(pClnImgX_Y, NULL,-1);//将pCInimg图像沿X和Y轴翻转

	cvNamedWindow("src", 0);//创建正常图像要显示的窗口
	cvNamedWindow("turnoverX",0);//创建沿X轴翻转图像窗口，垂直镜像窗口
	cvNamedWindow("turnoverY",0);//创建图像沿Y轴翻转的图像显示窗口,水平镜像窗口
	cvNamedWindow("turnoverX_Y",0);//创建图像沿X和Y轴翻转的图像的显示窗口

	cvShowImage("src", pSrcImg);//图像正常显示
	cvShowImage("turnoverX", pClnImgX);//图像X轴翻转显示，垂直镜像显示
	cvShowImage("turnoverY",pClnImgY);//图像Y轴翻转显示，水平镜像显示
	cvShowImage("turnoverX_Y",pClnImgX_Y);//图像X_Y轴翻转显示

	cvWaitKey(0);//延迟显示，防止窗口一闪而过

	cvReleaseImage(&pSrcImg);//cvReleaseImage函数只是将IplImage*型的变量值赋为NULL，而这个变量本身还是存在的并且在内存中的存储位置不变。
	cvReleaseImage(&pClnImgX);
	cvReleaseImage(&pClnImgY);
	cvReleaseImage(&pClnImgX_Y);

	cvDestroyWindow("src");//销毁窗口
	cvDestroyWindow("turnoverX");
	cvDestroyWindow("turnoverY");
	cvDestroyWindow("turnoverX_Y");
	return 0;
}