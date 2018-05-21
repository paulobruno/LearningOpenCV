#include <opencv2/opencv.hpp>
#include <iostream>


int main(int argc, char* argv[])
{
    double alpha = 0.5;
    double beta, input;
    
    cv::String imagefile1("valve.png");
    cv::String imagefile2("flower.jpg");
    
    cv::Mat src1 = imread(imagefile1, cv::IMREAD_COLOR);
    cv::Mat src2 = imread(imagefile2, cv::IMREAD_COLOR);
    cv::Mat dst;
    
    if (src1.empty())
    {
        std::cout << "Cannot load " << imagefile1 << std::endl;
        return -1;
    }
    
    if (src2.empty())
    {
        std::cout << "Cannot load " << imagefile2 << std::endl;
        return -1;
    }
    
    
    std::cout << "Alpha value: ";
    std::cin >> input;
    
    if (0 <= input && 1 >= input)
    {
        alpha = input;
    }
    
    beta = 1.0 - alpha;
    
    cv::addWeighted(src1, alpha, src2, beta, 0.0, dst);
    
    cv::namedWindow("Linear Blend", cv::WINDOW_AUTOSIZE);
    cv::imshow("Linear Blend", dst);
    cv::waitKey(0);
            
    
    return 0;
}
