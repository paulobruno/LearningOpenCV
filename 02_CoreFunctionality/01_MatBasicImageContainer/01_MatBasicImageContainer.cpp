#include <opencv2/opencv.hpp>


int main (int argc, char* argv[])
{
    cv::Mat M(2, 2, CV_8UC3, cv::Scalar(0, 0, 255));
    std::cout << "M = " << std::endl << " " << M << std::endl << std::endl;

    return 0;
}
