/*#include "stdio.h"
#include "cv.h"
#include "highgui.h"
int main()
{
IplImage *img=cvLoadImage("Hydrangeas.jpg",1);
CvScalar s;
int i,j;
for(i=0;i<img->height;i++){
	for(j=0;j<img->width;j++){
		s=cvGet2D(img,i,j); // get the (i,j) pixel value
		printf("B=%f, G=%f, R=%f ",s.val[0],s.val[1],s.val[2]);
		/*s.val[0]=111;
		s.val[1]=111;
		s.val[2]=111;
		cvSet2D(img,i,j,s);*///set the (i,j) pixel value
	/*}
}
//cvFlip(img,NULL,0);
cvNamedWindow("Image",1);
cvShowImage("Image",img);
cvWaitKey(0); //等待按键
cvDestroyWindow( "Image" );//销毁窗口
cvReleaseImage( &img ); //释放图像
return 0;
}*/