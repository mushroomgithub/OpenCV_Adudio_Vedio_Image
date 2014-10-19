#include<iostream>
#include<cv.h>
#include<highgui.h>
#include<cvaux.h>
using namespace std;

void PrintMat(CvMat *A);//��ӡ��ʾ����
void GenRandn(CvMat *arr,int seed);//������̬�ֲ����������
void GenRand(CvMat *arr,int seed);//����[0,1]���ȷֲ����������
static int com_func(const void *_a,const void *_b,void *userData);//�ȽϺ���
void Test_Multiply();//���Ծ������
void Test_cvGetRawData();//��������������CvMat������
void Test_DCT();//�����ά��ɢ���ұ任
void Test_Rand();//���������
void Test_SeqSort();//��ά��������

int main(int argc,char ** argv)
{
	Test_Multiply();
	Test_cvGetRawData();
	Test_DCT();
	Test_Rand();
	Test_SeqSort();
	return 0;
}
void Test_SeqSort()//���Զ�ά��������
{
	CvMemStorage *storage=cvCreateMemStorage(0);
	CvSeq *seq=cvCreateSeq(CV_32SC2,sizeof(CvSeq),sizeof(CvPoint),storage);
	cout<<"---Test seq Sot---"<<endl;
	for(int i=0;i<10;i++)
	{
		CvPoint pt;
		pt.x=rand()%1000;
		pt.y=rand()%1000;
		cvSeqPush(seq,&pt);
	}
	cout<<"---Original point set---"<<endl;
	for(int i=0;i<10;i++)
	{
		CvPoint  *pt=(CvPoint*)cvGetSeqElem(seq,i);
		cout<<pt->x<<"  "<<pt->y<<endl;
	}
	cvSeqSort(seq,com_func,0);
	cout<<"---After Sorting---"<<endl;
	for(int i=0;i<10;i++)
	{
		CvPoint  *pt=(CvPoint*)cvGetSeqElem(seq,i);
		cout<<pt->x<<"  "<<pt->y<<endl;
	}
	cvClearSeq(seq);
	cvReleaseMemStorage(&storage);
}
static int com_func(const void *_a,const void *_b,void *userData)//�ȽϺ���
{
	CvPoint *a=(CvPoint*)_a;
	CvPoint *b=(CvPoint*)_b;
	int y_diff=a->y-b->y;
	int x_diff=a->x-b->x;
	return y_diff?y_diff:x_diff;
}
void Test_Rand()//�����������
{
	CvMat *a=cvCreateMat(10,6,CV_32F);
	cout<<"---Test generate Rand Maritex---"<<endl;
	for(int i=0;i<5;i++)
	{
		GenRand(a,i);
		PrintMat(a);
	}
	cvReleaseMat(&a);
}

void PrintMat(CvMat *A)//��ʾ����
{
	int i,j;
	cout<<"---Mat="<<endl;
	for(i=0;i<A->rows;i++)
	{
		cout<<endl;
		switch(CV_MAT_DEPTH(A->type))
		{
		case CV_32F:
		case CV_64F:
			for(j=0;j<A->cols;j++)
			{
				cout<<(float)cvGetReal2D(A,i,j)<<"   ";
			}
			break;
		case CV_8U:
		case CV_16U:
			for(j=0;j<A->cols;j++)
			{
				cout<<(float)cvGetReal2D(A,i,j)<<"   ";
			}
			break;
		default:break;
		}
	}
	cout<<endl;
}
void GenRand(CvMat *arr,int seed)
{
	CvRandState rng;
	rng.state=cvRNG(0xffffffff);
	cvRandInit(&rng,0,1,seed,CV_RAND_UNI);
	cvRandArr(&rng.state,arr,CV_RAND_UNI,cvRealScalar(0),cvRealScalar(1));
}
void GenRandn(CvMat *arr,int seed)
{
	CvRandState rng;
	rng.state=cvRNG(0xffffffff);
	cvRandInit(&rng,0,1,seed,CV_RAND_NORMAL);
	cvRandArr(&rng.state,arr,CV_RAND_NORMAL,cvRealScalar(0),cvRealScalar(1));
}
void Test_Multiply()
{
	double a[]={1,2,3,4,
	5,6,7,8,
	9,10,11,12};
	double b[]={1,5,9,
	2,6,10,
	3,7,11,
	4,8,12};
	double c[9];
	CvMat Ma,Mb,Mc;
	cout<<"---Test MultiPlay---"<<endl;
	cvInitMatHeader(&Ma,3,4,CV_64FC1,a,CV_AUTO_STEP);
	cvInitMatHeader(&Mb,4,3,CV_64FC1,b,CV_AUTO_STEP);
	cvInitMatHeader(&Mc,3,3,CV_64FC1,c,CV_AUTO_STEP);
	//cvMatMulAdd(&Ma,&Mb,0.&Mc);
	cvMatMul(&Ma,&Mb,&Mc);
	PrintMat(&Ma);
	PrintMat(&Mb);
	PrintMat(&Mc);
	return;
}

void Test_cvGetRawData()
{
	float *data;
	int step;
	float a[]={1,2,3,4,
	-5,6,7,8,
	9,10,-11,-12,14};
	CvMat array;
	CvSize size;
	int x,y;
	cout<<"---Test Get Raw Data---"<<endl;
	cvInitMatHeader(&array,3,4,CV_32FC1,a,CV_AUTO_STEP);
	cvGetRawData(&array,(uchar**)&data,&step,&size);
	step/=sizeof(data[0]);
	cout<<"---CvMat="<<endl;
	PrintMat(&array);
	cout<<"--Data="<<endl;
	for(y=0;y<size.height;y++,data+=step)
	{
		cout<<endl;
		for(x=0;x<size.width;x++)
		{
			data[x]=(float)fabs(data[x]);
			cout<<data[x]<<"  ";
		}
	}
	cout<<endl;
	return;
}

void Test_DCT()
{
	float data[]={1,2,3,4,5,6,7,8};
	CvMat a;
	a=cvMat(2,4,CV_32FC1,data);
	cout<<"---Test DCT---"<<endl;
	cout<<"Original matriex="<<endl;
	PrintMat(&a);
	cvDCT(&a,&a,CV_DXT_INVERSE);
	cout<<"---2-D IDCT="<<endl;
	PrintMat(&a);
}