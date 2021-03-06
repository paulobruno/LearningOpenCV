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
    
    double t = (double) cv::getTickCount();
    
    // pixelwise operations only for didatic purpose
    // the 'correct' version is to use convertTo (below)    
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
    
    t = 1000.0 * ((double) cv::getTickCount() - t) / cv::getTickFrequency();
    std::cout << "for version:" << std::endl
              << "\tTimes passed in milisseconds: " << t << " ms" << std::endl;
              
    cv::namedWindow("Original Image", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("New Image", cv::WINDOW_AUTOSIZE);
    
    cv::imshow("Original Image", src);
    cv::imshow("New Image", dst);
    
    
    t = (double) cv::getTickCount();
    
    // 'correct' version, a lot faster and gives the same result
    src.convertTo(dst, -1, gain, bias);
    
    t = 1000.0 * ((double) cv::getTickCount() - t) / cv::getTickFrequency();
    std::cout << "convertTo version:" << std::endl
              << "\tTimes passed in milisseconds: " << t << " ms" << std::endl;
              
    cv::namedWindow("Convert To Version", cv::WINDOW_AUTOSIZE);
    cv::imshow("Convert To Version", dst);
    
    
    // gamma correction
    cv::Mat lookUpTable(1, 256, CV_8U);
    uchar* p = lookUpTable.ptr();
    double gamma_ = 1.0;

    std::cout << "Gamma value [0-4]: ";
    std::cin >> input;
    
    if (0 <= input && 4 >= input)
    {
        gamma_ = input;
    }

    for( int i = 0; i < 256; ++i)
    {
        p[i] = cv::saturate_cast<uchar>(cv::pow((double)i / 255.0, gamma_) * 255.0);
    }
    cv::Mat res = src.clone();
    LUT(src, lookUpTable, res);
    
    cv::namedWindow("Gamma correction", cv::WINDOW_AUTOSIZE);
    cv::imshow("Gamma correction", res);
    
    
    cv::waitKey(0);
            
    
    return 0;
}
