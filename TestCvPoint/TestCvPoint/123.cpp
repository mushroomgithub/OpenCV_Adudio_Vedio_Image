/*#include<iostream>
#include<tchar.h>
#include<iomanip>
using namespace std;
int main(int argc,char** argv)
{
	int curve1[8]={10,10,10,100,100,100,100,10};
	int curve2[10]={30,30,30,130,130,130,130,130,150,10};
	int* curveArr[2]={curve1,curve2};
	cout<<"curveArr[0]指向的数组元素为:"<<endl;
	for(int i=0;i<8;i++)
		cout<<setw(4)<<curveArr[0][i];
	cout<<endl;
	cout<<"curveArr[1]指向的数组元素为:"<<endl;
	for(int j=0;j<10;j++)
		cout<<setw(4)<<curveArr[1][j];
	cout<<endl;
	return 0;
}*/

#include "cv.h"  
#include "highgui.h"  
int main(int argc, char* argv[]) 
{ 
	char wndname[] = "MushRoom Testing!"; 
	cvNamedWindow(wndname); 
	int arr[1]; 
	arr[0] = 4; 
	CvPoint ** pt = new CvPoint*[1]; 
	pt[0] = new CvPoint[4]; 
	pt[0][0] = cvPoint(0,0); 
	pt[0][1] = cvPoint(100,10); 
	pt[0][2] = cvPoint(30,60); 
	pt[0][3] = cvPoint(10,100); 
	IplImage *image=cvLoadImage("Hydrangeas.jpg",-1);
	cvPolyLine( image, pt, arr, 1, 1, CV_RGB(250,0,0)); 
	cvFillPoly(image,pt,arr,1,CV_RGB(250,0,0)); 
	cvShowImage(wndname,image); 
	cvWaitKey(1000000); 
	return 0; 
}