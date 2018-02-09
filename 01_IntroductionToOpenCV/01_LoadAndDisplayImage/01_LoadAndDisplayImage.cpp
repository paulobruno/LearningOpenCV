#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>


int main(int argc, char* argv[])
{
    cv::String imageName("HappyFish.png");
    
    if (argc > 1)
    {
        imageName = argv[1];
    }
    
    cv::Mat image = cv::imread(imageName, cv::IMREAD_COLOR);
    
    if (image.empty())
    {
        printf("Could not open or find the image\n");
        return -1;
    }
    
    cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);
    cv::imshow("Display window", image);

    cv::waitKey(0);

    return 0;
}

