#include <stdio.h>                                                                                                                                                                                                 
#include <opencv2/opencv.hpp>
#include <vector>


using namespace cv; 
using namespace std;


int main(int argc, char** argv )
{
    vector<Mat> source_images;
    char filenames[20];
    int count = 216;

    // 想要生成的图片
    Mat srcImage = imread("../test.png");
    resize(srcImage, srcImage, Size(1920, 1080));


    // 简单读取图片 把两张尺寸差别很大的图片resize到相同的640×640
    for (int i = 0; i <= count-1; i++)
    {
        Mat src_img;
        // int 转 string
        sprintf(filenames, "../out_img/%d.png", i);
        src_img = imread(filenames);
        // 所有图片缩成小图
        resize(src_img, src_img, Size(30, 30), 0, 0, INTER_NEAREST);
        source_images.push_back(src_img);
    }
    
    int width = 1920;
    int height = 1080;

    // 思路就是遍历原始照片的每个固定大小的像素块， 根据像素块的特征相似度来找出最接近的
    Mat montageImage;
    resize(srcImage, montageImage, Size(1920, 1080));


    int bins = 128;
    int hist_sizes[] = {bins, bins, bins};
    float range[] = {0, 255};
    const float *ranges[] = {range, range, range};
    int chanels[] = {0, 1, 2};
    
    vector<MatND> hist_list;

    for (size_t i = 0; i < count; i++)
    {
        /* code */
        MatND hist_RGB;
        Mat frame;
        source_images[i].copyTo(frame);

        // 计算直方图信息
        calcHist(&frame, 1, chanels, Mat(), hist_RGB, 3, hist_sizes, ranges, true, false);
        hist_list.push_back(hist_RGB);
    }

    int number_order = 0;
    for (int y = 0; y < height; y = y + 30)
    {
        for (int  x = 0; x < width; x = x + 30)
        {
            Mat roiImg = srcImage(Rect(x, y, 30, 30));

            MatND hist_roi;

            double match_max = 0.0;
            calcHist(&roiImg, 1, chanels, Mat(), hist_roi, 3, hist_sizes, ranges, true, false);

            for(int i = 0; i < count; i++){
                double match = 0;
                match = compareHist(hist_roi, hist_list[i], HISTCMP_CORREL);
                if (match > match_max)
                {
                    /* 将匹配度最高的值计算出来 */
                    number_order = i;
                    match_max = match;
                }
                
            }
            source_images[number_order].copyTo(roiImg);
            printf("正在生成中 ： \033[01;32m %.2f%% \r", (y/(double)1080 + x/(double)1920 /100) * 100);
            fflush(stdout);
        }
        
    }
    
    Mat dstImage;
    addWeighted(montageImage, 0.2, srcImage, 0.8, 3, dstImage);
    
    imwrite("linear_dstImage_pikaqiu.png", dstImage);
    imshow("montage", dstImage);
    waitKey(0);

    
}
