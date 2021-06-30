// 2-2-1
#include <stdio.h>                                                                                                                                                                                                 
#include <opencv2/opencv.hpp>
#include <vector>
#include <unistd.h>


using namespace cv; 
using namespace std;


int main(int argc, char** argv )
{
    Mat srcImg = imread("../test.png", IMREAD_UNCHANGED);

    // 图片是3通道 0-255  然后我们分成6分
    vector<Vec3d> colors;
    unsigned long index = 0;
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            for (int k = 0; k < 6; k++)
            {
                /* 存储颜色 */
                colors.push_back(Vec3d());
                colors[index][0] = i / 5.0 * 255;   // i , j , k 最大是5    5除以5乘以255=255 刚好
                colors[index][1] = j / 5.0 * 255;
                colors[index][2] = k / 5.0 * 255;
                index += 1;
            }
        } 
    }
    index = 0;
    Mat temp = srcImg.clone();
    while(index < colors.size())
    {
        for (int r = 0; r < srcImg.rows; r++)
        {
            for (int c = 0; c < srcImg.cols; c++)
            {
                Vec4b &pixel_temp = temp.at<Vec4b>(r, c);
                // 像素点的透明度
                if(pixel_temp[3] == 0){
                    continue;
                }
                else
                {
                    for (int i = 0; i < 3; i++)
                    {
                        pixel_temp[i] = colors[index][i];
                    }  
                }
            } 
        }
        char outImgPath[64] = {};
        sprintf(outImgPath, "../out_img/out_img_%.0f_%.0f_%.0f.png", colors[index][0], colors[index][1], colors[index][2]);
        imwrite(outImgPath, temp);
        index += 1;
    }
            

    return 0;
}
