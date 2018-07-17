#include <opencv2/opencv.hpp>


const int gainSliderMax = 200;
const int biasSliderMax = 100;
int gainSlider;
int biasSlider;
double gain;
double bias;

cv::Mat src;
cv::Mat dst;


static void on_trackbar_gain(int, void*)
{
    gain = ((double)gainSlider / 100.0) + 1.0;    
    
    src.convertTo(dst, -1, gain, bias);
    
    imshow("Linear Blend", dst);
}

static void on_trackbar_bias(int, void*)
{
    bias = (double) biasSlider;    
    
    src.convertTo(dst, -1, gain, bias);
    
    imshow("Linear Blend", dst);
}


int main (int argc, char* argv[])
{    
    cv::String imagefile("flower.jpg");
    
    src = cv::imread(imagefile, cv::IMREAD_COLOR);
    
    if (src.empty())
    {
        std::cout << "Cannot load " << imagefile << std::endl;
        return -1;
    }
    
    gainSlider = 0;
    biasSlider = 0;
    
    
    cv::namedWindow("Linear Blend", cv::WINDOW_AUTOSIZE);
    
    cv::String gainTrackbarName = "Contrast";
    cv::String biasTrackbarName = "Brightness";
    
    cv::createTrackbar(gainTrackbarName, "Linear Blend", &gainSlider, gainSliderMax, on_trackbar_gain);
    cv::createTrackbar(biasTrackbarName, "Linear Blend", &biasSlider, biasSliderMax, on_trackbar_bias);
    
    on_trackbar_gain(gainSlider, 0);
    on_trackbar_bias(biasSlider, 0);
    
    
    cv::waitKey(0);
    

    return 0;
}
