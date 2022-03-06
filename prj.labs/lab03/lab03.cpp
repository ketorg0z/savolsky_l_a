#include <opencv2/opencv.hpp>

float NontrivialFunc(float& val) {
  return std::abs(2 * std::pow(val, 2) - 2 * std::pow(val, 0.5));
}

int main() {
  cv::Mat img = cv::imread("../data/cross_0256x0256.png", 0);
  cv::Mat test(60, 768, CV_8UC1);

  cv::Rect2d rc = { 0, 0, 3, 60 };
  for (int i = 0; i < 768; i += 3) {
    cv::rectangle(test, rc, { float(i / 3) }, -1);
    rc.x += 3;
  }
  img.convertTo(img, CV_8UC1, 255);
  test.convertTo(test, CV_32FC1, 1.0 / 255.0);
  for (int i = 0; i < 60; ++i) {
    for (int j = 0; j < 768; ++j) {
      test.at<float>(i, j) = NontrivialFunc(test.at<float>(i, j));
    }
  }
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
  cv::Mat LUT(1, 256, CV_8U);
  for (int i = 0; i < 256; ++i) {
    LUT.at<uchar>(i) = i;
//    std::cout << static_cast<unsigned>(LUT.at<uchar>(i)) << std::endl;
  }


  LUT.convertTo(LUT, CV_32F, 1.0/255.0);
//  for (int i = 0; i < 256; ++i) std::cout << LUT.at<float>(i) << std::endl;
  for (int i = 0; i < 256; ++i) LUT.at<float>(i) = NontrivialFunc(LUT.at<float>(i));
//  for (int i = 0; i < 256; ++i) std::cout << LUT.at<float>(i) << std::endl;
  LUT.convertTo(LUT, CV_8U, 255);
//  for (int i = 0; i < 256; ++i) {
//    std::cout << static_cast<unsigned>(LUT.at<uchar>(i)) << std::endl;
//  }
  cv::LUT(img, LUT, img);
    for (int i = 0; i < 256; ++i) {
      for (int j = 0; j < 256; ++j) {
        std::cout << img.at<int>(i, j) << std::endl;
      }
    }
  img.convertTo(img, CV_32FC1, 1.0 / 255.0);
  cv::imshow("test", test);
  cv::imshow("img", img);
  cv::waitKey(0);
  return 0;
}
