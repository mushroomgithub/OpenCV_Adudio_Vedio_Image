#include "highgui.h"
#include <iostream>
using namespace std;
int main(int argc,char** argv)//图像像素值都加10之后的结果
{
	if(argc<2)
		exit(-1);
	IplImage*image=cvLoadImage(argv[1],1);//默认是强制加载三通道彩色图像,通道数为3，位深为8
	//IplImage*image=cvLoadImage(argv[1],0);//强制当前加载图像为灰阶图像,通道数为1,位深为8
	//cout<<"当前应用程序名为："<<argv[0]<<endl;
	if(image==NULL)
		cout<<"加载图片失败！"<<endl;
	cvNamedWindow("MoGu",1);//flag=1时，表示窗口不能手动缩放
	//cvNamedWindow("MoGu",0);//flag=0时，表示窗口可以手动缩放
	int width,height,depth,channels,widthstep;
	uchar* pchar;
	width=image->width;
	height=image->height;
	depth=image->depth;
	channels=image->nChannels;
	widthstep=image->widthStep;
	cout<<"图像宽度为："<<width<<endl;
	cout<<"图像高度为："<<height<<endl;
	cout<<"图像的位深大小为："<<depth<<endl;
	cout<<"图像通道数："<<channels<<endl;
	cout<<"图像每行像素所占的字节数为："<<widthstep<<endl;
	int i,j;
	for(i=0;i<height;i++)
	{
		pchar=(uchar*)image->imageData+i*widthstep;//定位某行，image->imageData表示图像数据存放的首地址，加上指定行数*每行的字节数,可以跳转到下一行
		for(j=0;j<width;j++)
		{
			uchar* temp=pchar+j*channels;//pchar即是每行图像存储数据的首地址，加上某列的通道数，可以跳转的下一列像素点，和上面结合在一起就可以定位某行某列的指定的像素，定位到该像素点后可以设置改点像素的通道值
			temp[0]+=10;//通道B
			temp[1]+=10;//通道G
			temp[2]+=10;//通道R
		}
	}
	cvShowImage("MoGu",image);
	cvWaitKey();
	cvReleaseImage(&image);
	cvDestroyWindow("MoGu");
	return 0;
}