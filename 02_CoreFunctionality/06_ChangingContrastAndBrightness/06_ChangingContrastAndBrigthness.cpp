#include <opencv2/opencv.hpp>
#include <iostream>


int main(int argc, char* argv[])
{
    double gain = 1.0;
    double bias = 0.0;
    double input;
    
    
    cv::String imagefile("flower.jpg");
    
    cv::Mat src = imread(imagefile, cv::IMREAD_COLOR);
    
    if (src.empty())
    {
        std::cout << "Cannot load " << imagefile << std::endl;
        return -1;
    }
    
    std::cout << "Gain value [1-3]: ";
    std::cin >> input;
    
    if (1 <= input && 3 >= input)
    {
        gain = input;
    }
    
    std::cout << "Bias value [0-100]: ";
    std::cin >> input;
    
    if (0 <= input && 100 >= input)
    {
        bias = input;
    }
    
        
    cv::Mat dst = cv::Mat::zeros(src.size(), src.type());
        
    for (int j = 0; j < src.rows; ++j)
    {
        for (int i = 0; i < src.cols; ++i)
        {
            for (int c = 0; c < src.channels(); ++c)
            {
                dst.at<cv::Vec3b>(j,i)[c] = cv::saturate_cast<uchar>(gain *(src.at<cv::Vec3b>(j,i)[c]) + bias);
            }
        }
    }
    
    
    cv::namedWindow("Original Image", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("New Image", cv::WINDOW_AUTOSIZE);
    
    cv::imshow("Original Image", src);
    cv::imshow("New Image", dst);
    
    cv::waitKey(0);
            
    
    return 0;
}
