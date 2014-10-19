//#include "stdafx.h"
/*#include"highgui.h"
#include"cv.h"

//��¼�������ĵ�ǰλ��
int g_slider_pos = 0 ;

//�������Ļص����� ���� pos ��ָ��ǰ����������λ��
void on_changed(int pos)
{
	printf( "g_slider_pos is %d \n",g_slider_pos);
}

int main(int argc,char* argv[])
{
	cvNamedWindow( "show");

	//�ڴ���show�ϴ�������ΪPosition�Ĺ�����
	cvCreateTrackbar( "Position","show" ,&g_slider_pos,400,on_changed);
	//��ʾ������
	cvShowImage( "show",NULL);
	//�ȴ��û�����
	cvWaitKey(0);

	return 0;
}
*/

//�� ��Ƶ���ſ���

//#include "stdafx.h"
#include"highgui.h"
#include"cv.h"

	//����һ��CvCapture����ָ�� ���ڽ���cvCreateFileCapture�ķ���ֵ
	CvCapture* g_capture = NULL;
//��¼�������ĵ�ǰλ��
int g_slider_pos = 0 ;
//����Ƶ֡���м����ı���
int frame_count = 0;

//�������Ļص�����  ����int pos ��ָ��ǰ����������λ��
void on_changed(int pos)
{
	//����g_capture������  ʹ�� ��λ��pos��ʼ������Ƶ
	cvSetCaptureProperty(g_capture,CV_CAP_PROP_POS_FRAMES,pos);
	//��������������  ���ֱ���frame_count���������λ����ͬ����                
	frame_count = pos ;
}

int main(int argc,char* argv[])
{
	//����һ������           
	cvNamedWindow( "show");
	//����һ����Ƶ�ļ�
	g_capture=cvCreateFileCapture( "D:\\��Ƶ�ɼ�.avi");
	//��ȡ��Ƶ����֡��
	int frames=(int )cvGetCaptureProperty(g_capture,CV_CAP_PROP_FRAME_COUNT);

	if(frames>0)
	{
		//�ڴ���show�ϴ�������ΪPosition�Ĺ�����
		cvCreateTrackbar( "Position","show" ,&g_slider_pos,frames,on_changed);
	}   

	//ͼ��ָ�����
	IplImage* frame;

	while(1)
	{
		//��g_capture��ȡһ֡ͼ�� ��䵽��Ӧ���ڴ滺����
		frame=cvQueryFrame(g_capture);
		//�������Ƶ��β ���˳�ѭ��
		if(!frame) break ;
		//��ʾͼ��
		cvShowImage( "show",frame);
		//�����û�����
		char c = cvWaitKey(33);
		//������յ� ����'Esc' ���˳�ѭ��
		if(c==27)
			break;
		//������ ������Ƶ�Ĳ��� �����ƶ�
		cvSetTrackbarPos( "Position","show" ,frame_count);
		frame_count++;
	}
	//�ͷ���Դ
	cvReleaseCapture(&g_capture);
	cvDestroyWindow( "show");

	return 0;
}