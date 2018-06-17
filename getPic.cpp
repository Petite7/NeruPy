#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>

using namespace cv;
using namespace std;

cv::Mat org,dst,img,tmp;
void on_mouse(int event,int x,int y,int flags,void *ustc)//event����¼����ţ�x,y������꣬flags��ק�ͼ��̲����Ĵ���
{
    static Point pre_pt = cv::Point(-1,-1);//��ʼ����
    static Point cur_pt = cv::Point(-1,-1);//ʵʱ����
    char temp[16];
    if (event == CV_EVENT_LBUTTONDOWN)//������£���ȡ��ʼ���꣬����ͼ���ϸõ㴦��Բ
    {
        org.copyTo(img);//��ԭʼͼƬ���Ƶ�img��
        sprintf(temp,"(%d,%d)",x,y);
        pre_pt = Point(x,y);
        putText(img,temp,pre_pt,FONT_HERSHEY_SIMPLEX,0.5,Scalar(0,0,0,255),1,8);//�ڴ�������ʾ����
        circle(img,pre_pt,2,Scalar(255,0,0,0),CV_FILLED,CV_AA,0);//��Բ
        imshow("img",img);
    }
    else if (event == CV_EVENT_MOUSEMOVE && !(flags & CV_EVENT_FLAG_LBUTTON))//���û�а��µ����������ƶ��Ĵ�����
    {
        img.copyTo(tmp);//��img���Ƶ���ʱͼ��tmp�ϣ�������ʾʵʱ����
        sprintf(temp,"(%d,%d)",x,y);
        cur_pt = Point(x,y);
        putText(tmp,temp,cur_pt,FONT_HERSHEY_SIMPLEX,0.5,Scalar(0,0,0,255));//ֻ��ʵʱ��ʾ����ƶ�������
        imshow("img",tmp);
    }
    else if (event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON))//�������ʱ������ƶ�������ͼ���ϻ�����
    {
        img.copyTo(tmp);
        sprintf(temp,"(%d,%d)",x,y);
        cur_pt = Point(x,y);
        putText(tmp,temp,cur_pt,FONT_HERSHEY_SIMPLEX,0.5,Scalar(0,0,0,255));
        rectangle(tmp,pre_pt,cur_pt,Scalar(0,255,0,0),1,8,0);//����ʱͼ����ʵʱ��ʾ����϶�ʱ�γɵľ���
        imshow("img",tmp);
    }
    else if (event == CV_EVENT_LBUTTONUP)//����ɿ�������ͼ���ϻ�����
    {
        org.copyTo(img);
        sprintf(temp,"(%d,%d)",x,y);
        cur_pt = Point(x,y);
        putText(img,temp,cur_pt,FONT_HERSHEY_SIMPLEX,0.5,Scalar(0,0,0,255));
        circle(img,pre_pt,2,Scalar(255,0,0,0),CV_FILLED,CV_AA,0);
        rectangle(img,pre_pt,cur_pt,Scalar(0,255,0,0),1,8,0);//���ݳ�ʼ��ͽ����㣬�����λ���img��
        imshow("img",img);
        img.copyTo(tmp);
        //��ȡ���ΰ�Χ��ͼ�񣬲����浽dst��
        int width = abs(pre_pt.x - cur_pt.x);
        int height = abs(pre_pt.y - cur_pt.y);
        if (width == 0 || height == 0)
        {
            printf("width == 0 || height == 0");
            return;
        }
        dst = org(Rect(min(cur_pt.x,pre_pt.x),min(cur_pt.y,pre_pt.y),width,height));
        cv::resize(dst,dst,Size(28,28));
        cvtColor( dst, dst, CV_BGR2GRAY );
        threshold(dst, dst, 170, 255, CV_THRESH_BINARY);
        imwrite("/media/sda/Ubuntu 14.0/myMNIST/MNIST_recognize/temp3.png",dst);//ע�⽫�����Ϊ�Լ��Ĵ������洢��ַ
        namedWindow("dst");
        imshow("dst",dst);
        waitKey(0);
    }
}
int main()
{
    org = imread("/media/sda/Ubuntu 14.0/myMNIST/MNIST_recognize/num3.jpg");//��ȡͼƬ��ַ
    org.copyTo(img);
    org.copyTo(tmp);
    namedWindow("img");//����һ��img����
    setMouseCallback("img",on_mouse,0);//���ûص�����
    imshow("img",img);
    cv::waitKey(0);
}
