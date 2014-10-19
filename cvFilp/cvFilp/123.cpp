#include "stdio.h"
#include "cv.h"
#include "highgui.h"
int main()
{
	IplImage *pSrcImg = NULL;
	IplImage *pClnImgX = NULL;
	IplImage *pClnImgY = NULL;
	IplImage *pClnImgX_Y = NULL;

	pSrcImg = cvLoadImage("Hydrangeas.jpg", 1);//1��ʾ���ص�ͼ��ǿ��ת��Ϊ��ɫͼ��
	//pSrcImg = cvLoadImage("Hydrangeas.jpg", 0);//0��ʾ���ص�ͼ��ǿ��ת��Ϊ��ɫͼ��
	if (pSrcImg == NULL)
	{
		printf("Fail to load images\n");
		return -1;
	}

	pClnImgX = cvCloneImage(pSrcImg);//��ԭͼ��¡������ͼ�����ڲ�ͬ��ת��
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

	cvFlip(pClnImgX, NULL,0); //���������� //����cvFlip(src,pClnImg, 0);//pClinlmg����������ͼ�񣬻��߸���ͼ��,��pCInimgͼ����X�ᷭת,����ֱ����
	cvFlip(pClnImgY, NULL,1);//��pCInimgͼ����X�ᷭת,��ˮƽ����
	cvFlip(pClnImgX_Y, NULL,-1);//��pCInimgͼ����X��Y�ᷭת

	cvNamedWindow("src", 0);//��������ͼ��Ҫ��ʾ�Ĵ���
	cvNamedWindow("turnoverX",0);//������X�ᷭתͼ�񴰿ڣ���ֱ���񴰿�
	cvNamedWindow("turnoverY",0);//����ͼ����Y�ᷭת��ͼ����ʾ����,ˮƽ���񴰿�
	cvNamedWindow("turnoverX_Y",0);//����ͼ����X��Y�ᷭת��ͼ�����ʾ����

	cvShowImage("src", pSrcImg);//ͼ��������ʾ
	cvShowImage("turnoverX", pClnImgX);//ͼ��X�ᷭת��ʾ����ֱ������ʾ
	cvShowImage("turnoverY",pClnImgY);//ͼ��Y�ᷭת��ʾ��ˮƽ������ʾ
	cvShowImage("turnoverX_Y",pClnImgX_Y);//ͼ��X_Y�ᷭת��ʾ

	cvWaitKey(0);//�ӳ���ʾ����ֹ����һ������

	cvReleaseImage(&pSrcImg);//cvReleaseImage����ֻ�ǽ�IplImage*�͵ı���ֵ��ΪNULL����������������Ǵ��ڵĲ������ڴ��еĴ洢λ�ò��䡣
	cvReleaseImage(&pClnImgX);
	cvReleaseImage(&pClnImgY);
	cvReleaseImage(&pClnImgX_Y);

	cvDestroyWindow("src");//���ٴ���
	cvDestroyWindow("turnoverX");
	cvDestroyWindow("turnoverY");
	cvDestroyWindow("turnoverX_Y");
	return 0;
}