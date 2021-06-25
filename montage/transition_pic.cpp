#include <stdio.h>                                                                                                                                                                                                 
#include <opencv2/opencv.hpp>
#include <vector>
#include <unistd.h>


using namespace cv; 
using namespace std;


int main(int argc, char** argv )
{
    vector<Mat> dstImg_list;
    int pic_count = 9;
    double alpha = 0.1;
    char dst_filename[50];

    // 简单读取图片 把两张尺寸差别很大的图片resize到相同的640×640
    for (int i = 1; i <= pic_count; i++)
    {

        Mat src_img1 = imread("../scenery_data/scenery_1.jpeg");
        Mat src_img2 = imread("../scenery_data/scenery_2.jpeg");
        resize(src_img1, src_img1, Size(640, 640));
        resize(src_img2, src_img2, Size(640, 640));
        // 然后把图片的左半部分取出

        Mat dstImg;
        addWeighted(src_img1, alpha, src_img2, 1 - alpha, 0.0, dstImg);
        alpha += 0.1;
        dstImg_list.push_back(dstImg);
        sprintf(dst_filename, "../scenery_data/result_%d.jpeg", i);
        imwrite(dst_filename, dstImg);
        memset(dst_filename, 0, sizeof(dst_filename)/sizeof(char));
    } 
}
