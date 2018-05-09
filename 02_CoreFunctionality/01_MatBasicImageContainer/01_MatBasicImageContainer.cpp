#include <opencv2/opencv.hpp>
#include <vector>


int main (int argc, char* argv[])
{
    // Creating a Mat object explicity

    cv::Mat M(2, 2, CV_8UC3, cv::Scalar(0, 0, 255));
    std::cout << "M = " << std::endl << " " << M << std::endl << std::endl;

    M.create(4, 4, CV_8UC(2));
    std::cout << "M = " << std::endl << " " << M << std::endl << std::endl;

    cv::Mat E = cv::Mat::eye(4, 4, CV_64F);
    std::cout << "E = " << std::endl << " " << E << std::endl << std::endl;

    cv::Mat O = cv::Mat::ones(2, 2, CV_32F);
    std::cout << "O = " << std::endl << " " << O << std::endl << std::endl;

    cv::Mat Z = cv::Mat::zeros(3, 3, CV_8UC1);
    std::cout << "Z = " << std::endl << " " << Z << std::endl << std::endl;

    cv::Mat C = (cv::Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    std::cout << "C = " << std::endl << " " << C << std::endl << std::endl;

    cv::Mat RowClone = C.row(1).clone();
    std::cout << "RowClone = " << std::endl << " " << RowClone << std::endl << std::endl;

    cv::Mat R = cv::Mat(3, 2, CV_8UC3);
    cv::randu(R, cv::Scalar::all(0), cv::Scalar::all(255));


    // Output formatting

    std::cout << "R (default) = " << std::endl << " " << R << std::endl << std::endl;

    std::cout << "R (python) = " << std::endl << " " << cv::format(R, cv::Formatter::FMT_PYTHON) << std::endl << std::endl;

    std::cout << "R (csv) = " << std::endl << " " << cv::format(R, cv::Formatter::FMT_CSV) << std::endl << std::endl;

    std::cout << "R (numpy) = " << std::endl << " " << cv::format(R, cv::Formatter::FMT_NUMPY) << std::endl << std::endl;

    std::cout << "R (c) = " << std::endl << " " << cv::format(R, cv::Formatter::FMT_C) << std::endl << std::endl;
    

    // Output of other common items

    cv::Point2f P(5, 1);
    std::cout << "Point (2D) = " << P << std::endl << std::endl;

    cv::Point3f P3f(2, 6, 7);
    std::cout << "Point (3D) = " << P3f << std::endl << std::endl;

    std::vector<float> v;
    v.push_back( (float)CV_PI);
    v.push_back(2);
    v.push_back(3.01f);
    std::cout << "Vector of floats via Mat = " << cv::Mat(v) << std::endl << std::endl;

    std::vector<cv::Point2f> vPoints(20);
    for (size_t i = 0; i < vPoints.size(); ++i)
    {
        vPoints[i] = cv::Point2f((float)(i * 5), (float)(i% 7));
    }
    std::cout << "A vector of 2D Points = " << vPoints << std::endl << std::endl;


    return 0;
}
