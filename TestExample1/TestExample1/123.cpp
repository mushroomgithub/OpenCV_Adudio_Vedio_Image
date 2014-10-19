#include<cv.h>
#include<highgui.h>
#include<cvaux.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
#define  NUMBER 100
#define DELAY 5
char wndName[]="Mogu Demo";
CvScalar random_color(CvRNG* rng)
{
	int color=cvRandInt(rng);
	return CV_RGB(color&255,(color>>8)&255,(color>>16)&255);
}

int main(int argc,char** argv)
{
   int line_type=CV_AA;
   int i;
   CvPoint pt1,pt2;
   double angle;
   CvSize sz;
   CvPoint ptt[6];
   CvPoint* pt[2];
   int arr[2];
   CvFont font;
   CvRNG rng;
   int width=1000,height=700;
   int width3=width*3;
   int height3=height*3;
   CvSize text_size;
   int ymin=0;

	return 0;
}