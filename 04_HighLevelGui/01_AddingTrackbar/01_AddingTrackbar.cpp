#include <opencv2/opencv.hpp>


const int alphaSliderMax = 100;
int alphaSlider;
double alpha;
double beta;

cv::Mat src1;
cv::Mat src2;
cv::Mat dst;


static void on_trackbar(int, void*)
{
    alpha = (double) alphaSlider/alphaSliderMax;
    
    beta = (1.0 - alpha);
    
    cv::addWeighted(src1, alpha, src2, beta, 0.0, dst);
    
    imshow("Linear Blend", dst);
}


int main (int argc, char* argv[])
{
    src1 = cv::imread("flower.jpg");
    src2 = cv::imread("valve.png");
    
    if (src1.empty())
    {
        std::cout << "Cannot load src1" << std::endl;
    }

    if (src2.empty())
    {
        std::cout << "Cannot load src2" << std::endl;
    }
    
    alphaSlider = 0;
    
    cv::namedWindow("Linear Blend", cv::WINDOW_AUTOSIZE);
    
    cv::String trackbarName = "trackbar";
    cv::createTrackbar(trackbarName, "Linear Blend", &alphaSlider, alphaSliderMax, on_trackbar);
    
    on_trackbar(alphaSlider, 0);
    
    cv::waitKey(0);
    

    return 0;
}
