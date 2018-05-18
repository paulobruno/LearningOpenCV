#include <opencv2/opencv.hpp>


cv::Mat& scan_and_reduce_fast(cv::Mat& I, const uchar* const table);
cv::Mat& scan_and_reduce_iterator(cv::Mat& I, const uchar* const table);


int main (int argc, char* argv[])
{
    int divideWith = 64;

    
    // creating lookup table
    uchar table[256];

    for (int i = 0; i < 256; ++i)
    {
        table[i] = (uchar)(divideWith * (i/divideWith));
    }
    

    // read image
    cv::String imageName("aerial_clouds_dawn.jpg");
    
    cv::Mat grayImage = cv::imread(imageName, cv::IMREAD_GRAYSCALE);

    if (!grayImage.data)
    {
        std::cout << "No " << imageName << " image data." << std::endl;
        return -1;
    }
    
    cv::Mat reducedImage;
    double t = 0.0;
    
    
    // fast version
    reducedImage = grayImage.clone();

    t = (double) cv::getTickCount();

    scan_and_reduce_fast(reducedImage, table);

    t = 1000.0 * ((double) cv::getTickCount() - t) / cv::getTickFrequency();
    std::cout << "Fast version" << std::endl 
              << "\tTimes passed in milisseconds: " << t << " ms" << std::endl;
    
    
    // iterator version
    reducedImage = grayImage.clone();

    t = (double) cv::getTickCount();

    scan_and_reduce_iterator(reducedImage, table);

    t = 1000.0 * ((double) cv::getTickCount() - t) / cv::getTickFrequency();
    std::cout << "Iterator version" << std::endl
              << "\tTimes passed in milisseconds: " << t << " ms" << std::endl;
    
    
    // opencv LUT version
    cv::Mat lookUpTable(1, 256, CV_8U);
    uchar* p = lookUpTable.ptr();

    for (int i = 0; i < 256; ++i)
    {
        p[i] = table[i];
    }

    reducedImage = grayImage.clone();

    t = (double) cv::getTickCount();

    cv::LUT(reducedImage, lookUpTable, reducedImage);

    t = 1000.0 * ((double) cv::getTickCount() - t) / cv::getTickFrequency();
    std::cout << "Opencv LUT version" << std::endl 
              << "\tTimes passed in milisseconds: " << t << " ms" << std::endl;
    

    // show image 
    imwrite("Reduced_Image.jpg", reducedImage);
    
    namedWindow(imageName, cv::WINDOW_AUTOSIZE);
    namedWindow("Reduced image", cv::WINDOW_AUTOSIZE);
    
    imshow(imageName, grayImage);
    imshow("Reduced image", reducedImage);
    
    
    cv::waitKey(0);
    

    return 0;
}


cv::Mat& scan_and_reduce_fast(cv::Mat& I, const uchar* const table)
{
    CV_Assert(CV_8U == I.depth());

    int channels = I.channels();
    int nRows = I.rows;
    int nCols = I.cols * channels;

    if (I.isContinuous())
    {
        nCols *= nRows;
        nRows = 1;
    }

    int i, j;
    uchar* p;

    for (i = 0; i < nRows; ++i)
    {
        p = I.ptr<uchar>(i);

        for (j = 0; j < nCols; ++j)
        {
            p[j] = table[p[j]];
        }
    }

    return I;
}


cv::Mat& scan_and_reduce_iterator(cv::Mat& I, const uchar* const table)
{
    CV_Assert(CV_8U == I.depth());

    int channels = I.channels();
    
    switch (channels)
    {
        case 1:
        {
            cv::MatIterator_<uchar> it, end;
            for (it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it)
            {
                *it = table[*it];
            }
            break;
        }

        case 3:
        {
            cv::MatIterator_<cv::Vec3b> it, end;
            
            for (it = I.begin<cv::Vec3b>(), end = I.end<cv::Vec3b>(); it != end; ++it)
            {
                (*it)[0] = table[(*it)[0]];
                (*it)[1] = table[(*it)[1]];
                (*it)[2] = table[(*it)[2]];
            }
        }
    }

    return I;
}

