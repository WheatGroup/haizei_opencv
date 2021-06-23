#include <stdio.h>                                                                                                                                                                                                 
#include <opencv2/opencv.hpp>
#include <vector>


using namespace cv; 
using namespace std;


int main(int argc, char** argv )
{
    vector<Mat> imgs;
    char filename[20];
    int count = 3;

    // 简单读取图片 把两张尺寸差别很大的图片resize到相同的640×640
    for (int i = 1; i < count; i++)
    {
        // int 转 string
        sprintf(filename, "../data/%d.jpg", i);
        Mat src_img = imread(filename);
        resize(src_img, src_img, Size(640, 640));
        // 然后把图片的左半部分取出
        Mat tmp_img;
        if(i == 1){
            tmp_img = src_img(Rect(0, 0, 320, 640));
        }
        else
        {
            tmp_img = src_img(Rect(320, 0, 320, 640));
        }
        imgs.push_back(tmp_img);
        imshow("imshow", tmp_img);
        waitKey(0);  
    
    }

    Mat dst;
    double alpha = 0.5;
    double beta = ( 1.0 - alpha );
    // addWeighted(imgs[0], alpha, imgs[1], beta, 0.0, dst);
    hconcat(imgs[0], imgs[1], dst);
    imshow("imshow", dst);
    waitKey(0);  
    
}
