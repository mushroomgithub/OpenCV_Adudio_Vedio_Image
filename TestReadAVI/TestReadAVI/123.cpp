//#include "stdafx.h"
/*#include"highgui.h"
#include"cv.h"

//记录滚动条的当前位置
int g_slider_pos = 0 ;

//滚动条的回调函数 参数 pos 是指当前滚动条所在位置
void on_changed(int pos)
{
	printf( "g_slider_pos is %d \n",g_slider_pos);
}

int main(int argc,char* argv[])
{
	cvNamedWindow( "show");

	//在窗口show上创建名字为Position的滚动条
	cvCreateTrackbar( "Position","show" ,&g_slider_pos,400,on_changed);
	//显示滚动条
	cvShowImage( "show",NULL);
	//等待用户按键
	cvWaitKey(0);

	return 0;
}
*/

//② 视频播放控制

//#include "stdafx.h"
#include"highgui.h"
#include"cv.h"

	//声明一个CvCapture类型指针 用于接收cvCreateFileCapture的返回值
	CvCapture* g_capture = NULL;
//记录滚动条的当前位置
int g_slider_pos = 0 ;
//对视频帧进行计数的变量
int frame_count = 0;

//滚动条的回调函数  参数int pos 是指当前滚动条所在位置
void on_changed(int pos)
{
	//设置g_capture的属性  使得 从位置pos开始播放视频
	cvSetCaptureProperty(g_capture,CV_CAP_PROP_POS_FRAMES,pos);
	//在拉动滚动条后  保持变量frame_count与滚动条的位置是同步的                
	frame_count = pos ;
}

int main(int argc,char* argv[])
{
	//创建一个窗口           
	cvNamedWindow( "show");
	//打开有一个视频文件
	g_capture=cvCreateFileCapture( "D:\\视频采集.avi");
	//获取视频的总帧数
	int frames=(int )cvGetCaptureProperty(g_capture,CV_CAP_PROP_FRAME_COUNT);

	if(frames>0)
	{
		//在窗口show上创建名字为Position的滚动条
		cvCreateTrackbar( "Position","show" ,&g_slider_pos,frames,on_changed);
	}   

	//图像指针变量
	IplImage* frame;

	while(1)
	{
		//从g_capture获取一帧图像 填充到相应的内存缓冲区
		frame=cvQueryFrame(g_capture);
		//如果到视频结尾 则退出循环
		if(!frame) break ;
		//显示图像
		cvShowImage( "show",frame);
		//接收用户按键
		char c = cvWaitKey(33);
		//如果接收到 按键'Esc' 则退出循环
		if(c==27)
			break;
		//滚动条 随着视频的播放 进行移动
		cvSetTrackbarPos( "Position","show" ,frame_count);
		frame_count++;
	}
	//释放资源
	cvReleaseCapture(&g_capture);
	cvDestroyWindow( "show");

	return 0;
}