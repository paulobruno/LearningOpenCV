#include <opencv2/opencv.hpp>


int main(int argc, char* argv[])
{
    cv::String imageName("HappyFish.png");

    if (argc > 1)
    {
        imageName = argv[1];
    }
    
    cv::Mat image = cv::imread(imageName, cv::IMREAD_COLOR);
    
    if (!image.data)
    {
        printf("No image data.\n");
        return -1;
    }
    
    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
    
    imwrite("Gray_Image.jpg", grayImage);
    
    namedWindow(imageName, cv::WINDOW_AUTOSIZE);
    namedWindow("Grayscale image", cv::WINDOW_AUTOSIZE);
    
    imshow(imageName, image);
    imshow("Grayscale image", grayImage);
    
    cv::waitKey(0);
    
    return 0;
}
