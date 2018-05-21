#include <opencv2/opencv.hpp>


void sharpen(const cv::Mat& myImage, cv::Mat& result)
{
    CV_Assert(CV_8U == myImage.depth());
    
    const int nChannels = myImage.channels();
    result.create(myImage.size(), myImage.type());
    
    for (int j = 1; j < myImage.rows-1; ++j)
    {
        const uchar* previous = myImage.ptr<uchar>(j-1);
        const uchar* current  = myImage.ptr<uchar>(j  );
        const uchar* next     = myImage.ptr<uchar>(j+1);
        
        uchar* output = result.ptr<uchar>(j);
        
        for (int i = nChannels; i < nChannels*(myImage.cols-1); ++i)
        {
            *output++ = cv::saturate_cast<uchar>(5*current[i] - current[i-nChannels] - current[i+nChannels] - previous[i] - next[i]);
        }
    }
    
    result.row(0).setTo(cv::Scalar(0));
    result.row(result.rows-1).setTo(cv::Scalar(0));
    result.col(0).setTo(cv::Scalar(0));
    result.col(result.cols-1).setTo(cv::Scalar(0));
}


int main (int argc, char* argv[])
{
    cv::String filename("aerial-clouds-dawn.jpg");
    cv::Mat src = cv::imread(filename, cv::IMREAD_COLOR);
            
    if (src.empty())
    {
        std::cerr << "Can't open image ["  << filename << "]" << std::endl;
        return -1;
    }
    
    
    cv::Mat dst;
    
    
    double t = (double) cv::getTickCount();
    
    sharpen(src, dst);
    
    t = 1000.0 * ((double) cv::getTickCount() - t) / cv::getTickFrequency();
    std::cout << "C version:" << std::endl
              << "\tTimes passed in milisseconds: " << t << " ms" << std::endl;
    
    
    cv::Mat kernel = (cv::Mat_<char>(3,3) <<  0, -1,  0,
                                             -1,  5, -1,
                                              0, -1,  0);
                                              
    
    t = (double) cv::getTickCount();
    
    filter2D(src, dst, src.depth(), kernel);
    
    t = 1000.0 * ((double) cv::getTickCount() - t) / cv::getTickFrequency();
    std::cout << "opencv filter 2D version:" << std::endl
              << "\tTimes passed in milisseconds: " << t << " ms" << std::endl;
 
    
        
    namedWindow(filename, cv::WINDOW_AUTOSIZE);
    namedWindow("Filtered", cv::WINDOW_AUTOSIZE);
    
    imshow(filename, src);
    imshow("Filtered", dst);

    cv::waitKey(0);


    return 0;
}
