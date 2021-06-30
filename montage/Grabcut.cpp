#include <stdio.h>                                                                                                                                                                                                 
#include <opencv2/opencv.hpp>
#include <vector>


using namespace cv; 
using namespace std;


int main(int argc, char** argv )
{
    //
    Mat srcImg = imread("../lvbu.jpg");
    Mat mask, bgModel, fgModel;
    Rect rect(Point(90, 0), Point(srcImg.cols - 95, srcImg.rows));
    // 扣人像区域时， 训练的轮数， 越多越准确
    int times = 10;
    grabCut(srcImg, mask, rect, bgModel, fgModel, times, GC_INIT_WITH_RECT);

    rectangle(srcImg, rect, Scalar(255), 2, 8);
    // imshow("src", srcImg);
    // 展示前景色  同时将人的轮廓已经展示出来 
    //  掩码 与 1 ， 放大效果
    // imshow("mask", (mask & 1) * 255);

    Mat resultMask = (mask & 1) * 255;
    // 将白色的部分图上之前的颜色
    Mat resultImage_red = Mat(srcImg.rows, srcImg.cols, CV_8UC3);
    Mat resultImage_green = Mat(srcImg.rows, srcImg.cols, CV_8UC3);
    Mat resultImage_blue = Mat(srcImg.rows, srcImg.cols, CV_8UC3);
    Mat resultImage_white = Mat(srcImg.rows, srcImg.cols, CV_8UC3);
    // Mat resultImage;
    // resize(resultImage, resultImage, Size(srcImg.rows, srcImg.cols));

    for (int i = 0; i < srcImg.rows; i++)
    {
        for (int j = 0; j < srcImg.cols; j++)
        {
            Vec3b &pixel_src = srcImg.at<Vec3b>(i, j);
            Vec3b &pixel_result_red = resultImage_red.at<Vec3b>(i, j);
            Vec3b &pixel_result_green = resultImage_green.at<Vec3b>(i, j);

            Vec3b &pixel_result_blue = resultImage_blue.at<Vec3b>(i, j);

            Vec3b &pixel_result_white = resultImage_white.at<Vec3b>(i, j);

            uchar &pixel_mask = resultMask.at<uchar>(i, j);
            // 将mask中白色的部分用原来的图填充
            if(pixel_mask == 255)
            {
                // 对三个通道进行赋值
                for (int k = 0; k < 3; k++)
                {
                    pixel_result_red[k] = pixel_src[k];
                    pixel_result_green[k] = pixel_src[k];
                    pixel_result_blue[k] = pixel_src[k];
                    pixel_result_white[k] = pixel_src[k];
                }
                
            }
            else{
                pixel_result_red[1] = 0;
                pixel_result_red[2] = 255;
                pixel_result_red[3] = 0;

                pixel_result_blue[1] = 0;
                pixel_result_blue[2] = 0;
                pixel_result_blue[3] = 255;

                pixel_result_green[1] = 255;
                pixel_result_green[2] = 0;
                pixel_result_green[3] = 0;

                pixel_result_white[1] = 255;
                pixel_result_white[2] = 255;
                pixel_result_white[3] = 255;
            }
        }
        
    }
    
    imwrite("red.png", resultImage_red);
    imwrite("green.png", resultImage_green);
    imwrite("blue.png", resultImage_blue);
    imwrite("white.png", resultImage_white);
    // imshow("fgModel", fgModel);

    waitKey(0);

    return 0;
    
}
