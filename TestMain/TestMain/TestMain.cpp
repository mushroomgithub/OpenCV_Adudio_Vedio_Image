#include "highgui.h"
#include <iostream>
using namespace std;
int main(int argc,char** argv)//ͼ������ֵ����10֮��Ľ��
{
	if(argc<2)
		exit(-1);
	IplImage*image=cvLoadImage(argv[1],1);//Ĭ����ǿ�Ƽ�����ͨ����ɫͼ��,ͨ����Ϊ3��λ��Ϊ8
	//IplImage*image=cvLoadImage(argv[1],0);//ǿ�Ƶ�ǰ����ͼ��Ϊ�ҽ�ͼ��,ͨ����Ϊ1,λ��Ϊ8
	//cout<<"��ǰӦ�ó�����Ϊ��"<<argv[0]<<endl;
	if(image==NULL)
		cout<<"����ͼƬʧ�ܣ�"<<endl;
	cvNamedWindow("MoGu",1);//flag=1ʱ����ʾ���ڲ����ֶ�����
	//cvNamedWindow("MoGu",0);//flag=0ʱ����ʾ���ڿ����ֶ�����
	int width,height,depth,channels,widthstep;
	uchar* pchar;
	width=image->width;
	height=image->height;
	depth=image->depth;
	channels=image->nChannels;
	widthstep=image->widthStep;
	cout<<"ͼ����Ϊ��"<<width<<endl;
	cout<<"ͼ��߶�Ϊ��"<<height<<endl;
	cout<<"ͼ���λ���СΪ��"<<depth<<endl;
	cout<<"ͼ��ͨ������"<<channels<<endl;
	cout<<"ͼ��ÿ��������ռ���ֽ���Ϊ��"<<widthstep<<endl;
	int i,j;
	for(i=0;i<height;i++)
	{
		pchar=(uchar*)image->imageData+i*widthstep;//��λĳ�У�image->imageData��ʾͼ�����ݴ�ŵ��׵�ַ������ָ������*ÿ�е��ֽ���,������ת����һ��
		for(j=0;j<width;j++)
		{
			uchar* temp=pchar+j*channels;//pchar����ÿ��ͼ��洢���ݵ��׵�ַ������ĳ�е�ͨ������������ת����һ�����ص㣬����������һ��Ϳ��Զ�λĳ��ĳ�е�ָ�������أ���λ�������ص��������øĵ����ص�ͨ��ֵ
			temp[0]+=10;//ͨ��B
			temp[1]+=10;//ͨ��G
			temp[2]+=10;//ͨ��R
		}
	}
	cvShowImage("MoGu",image);
	cvWaitKey();
	cvReleaseImage(&image);
	cvDestroyWindow("MoGu");
	return 0;
}