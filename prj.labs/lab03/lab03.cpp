#include <opencv2/opencv.hpp>

double NontrivialFunc(double& val) {
  return std::abs(2 * std::pow(val, 2) - 2 * std::pow(val, 0.5));
}

cv::Mat drawFunc(std::vector<double>& xCords, std::vector<double>& yCords) {
  double size = 517;
  cv::Mat graph = cv::Mat::ones((int)size, (int)size, CV_8UC1) * 255;
  line(graph, cv::Point2d(0, 507), cv::Point2d(517, 507), { 0 }, 2, 8, 0);
  line(graph, cv::Point2d(5, 517), cv::Point2d(5, 0), { 0 }, 2, 8, 0);
  cv::putText(graph, "X", cv::Point2f(500, 500), 1, 1, { 0 });
  cv::putText(graph, "Y", cv::Point2f(10, 15), 1, 1, { 0 });
  cv::putText(graph, "0", cv::Point2f(7, 503), 1, 1, { 0 });
  for (int i = 1; i < xCords.size(); ++i) {
    double prevXCord = xCords[i - 1];
    double prevYCord = yCords[i - 1];
    double xCord = xCords[i];
    double yCord = yCords[i];
    cv::Point2d prevPoint(size * prevXCord + 5, size - (size * prevYCord) - 5);
    cv::Point2d point(size * xCord + 5, size - (size * yCord) - 5);
    line(graph, prevPoint, point, { 100 }, 2, 8, 0);
  }

  return graph;
}

int main() {
  cv::Mat img = cv::imread("./data/cross_0256x0256.png", 0);
  //cv::Mat img = cv::imread("../data/cross_0256x0256.png", 0);
  cv::Mat test(60, 768, CV_8UC1);
  std::vector<float> y(256);
  std::vector<float> x(256);
  std::vector<uint8_t> LUT(256);


  for (int i = 0; i < 256; ++i) {
    double xValue = (double)i / 255;
    x[i] = xValue;
    double yValue = NontrivialFunc(xValue);
    y[i] = yValue;
    LUT[i] = cv::saturate_cast<uint8_t>(yValue * 255);
  }

  img.convertTo(img, CV_8UC1, 255);

//  img.convertTo(img, CV_32FC1, 1.0 / 255.0);
//  for (int i = 0; i < 256; ++i) {
//    for (int j = 0; j < 256; ++j) {
//      img.at<float>(i, j) = NontrivialFunc(img.at<float>(i, j));
//    }
//  }
//  img.convertTo(img, CV_8UC1, 255);
//  for (int i = 0; i < 256; ++i) {
//    for (int j = 0; j < 256; ++j) {
//      std::cout << img.at<uint>(i, j) << std::endl;
//    }
//  }
  //cv::Mat LUT(1, 256, CV_8U);
  //for (int i = 0; i < 256; ++i) {
    //LUT.at<uchar>(i) = i;
//    std::cout << static_cast<unsigned>(LUT.at<uchar>(i)) << std::endl;
  //}


  //LUT.convertTo(LUT, CV_32F, 1.0/255.0);
//  for (int i = 0; i < 256; ++i) std::cout << LUT.at<float>(i) << std::endl;
  //for (int i = 0; i < 256; ++i) LUT.at<float>(i) = NontrivialFunc(LUT.at<float>(i));
//  for (int i = 0; i < 256; ++i) std::cout << LUT.at<float>(i) << std::endl;
  //LUT.convertTo(LUT, CV_8U, 255);
//  for (int i = 0; i < 256; ++i) {
//    std::cout << static_cast<unsigned>(LUT.at<uchar>(i)) << std::endl;
//  }
  //cv::LUT(img, LUT, img);
  //  for (int i = 0; i < 256; ++i) {
  //    for (int j = 0; j < 256; ++j) {
  //      std::cout << img.at<int>(i, j) << std::endl;
  //    }
  //  }
  //img.convertTo(img, CV_32FC1, 1.0 / 255.0);
  //cv::imshow("test", test);
  cv::imshow("img", img);
  cv::waitKey(0);
  return 0;
}
