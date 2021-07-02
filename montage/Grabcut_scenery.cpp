#include <stdio.h>                                                                                                                                                                                                 
#include <opencv2/opencv.hpp>
#include <vector>


using namespace cv; 
using namespace std;


int main(int argc, char** argv )
{
    // 先将人像从风景图中抠出来
    Mat srcImg = imread("../lvbu.jpg");
    Mat mask, bgModel, fgModel;
    Rect rect(Point(90, 0), Point(srcImg.cols - 95, srcImg.rows));
    // 扣人像区域时， 训练的轮数， 越多越准确
    int times = 10;
    grabCut(srcImg, mask, rect, bgModel, fgModel, times, GC_INIT_WITH_RECT);

    rectangle(srcImg, rect, Scalar(255), 2, 8);


    Mat resultMask = (mask & 1) * 255;
    // 将白色的部分图上之前的颜色
    Mat resultImage_red = Mat(srcImg.rows, srcImg.cols, CV_8UC3);
    Mat resultImage_green = Mat(srcImg.rows, srcImg.cols, CV_8UC3);
    Mat resultImage_blue = Mat(srcImg.rows, srcImg.cols, CV_8UC3);
    Mat resultImage_white = Mat(srcImg.rows, srcImg.cols, CV_8UC3);
    // Mat resultImage;
    Mat sceneryImg =  imread("../scenery_data/scenery_2.jpeg");
    resize(sceneryImg, sceneryImg, Size(srcImg.cols, srcImg.rows));

    for (int i = 0; i < srcImg.rows; i++)
    {
        for (int j = 0; j < srcImg.cols; j++)
        {
            Vec3b &pixel_src = srcImg.at<Vec3b>(i, j);
            Vec3b &pixel_scenery = sceneryImg.at<Vec3b>(i, j);
            
            uchar &pixel_mask = resultMask.at<uchar>(i, j);
            // 将mask中白色的部分用原来的图填充
            if(pixel_mask == 255)
            {
                // 对三个通道进行赋值
                for (int k = 0; k < 3; k++)
                {
                    pixel_scenery[k] = pixel_src[k];
                }
                
            }
            else{
                 for (int k = 0; k < 3; k++)
                {
                    pixel_scenery[k] = pixel_scenery[k];

                }
            }
        }
        
    }
    
    imwrite("scenery.png", sceneryImg);
   

    waitKey(0);

    return 0;
    
}
