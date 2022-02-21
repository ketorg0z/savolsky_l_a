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
  test.convertTo(test, CV_32FC1, 1.0 / 255.0);
  cv::imshow("test1", test);
  for (int i = 0; i < 60; ++i) {
    for (int j = 0; j < 768; ++j) {
      test.at<float>(i, j) = NontrivialFunc(test.at<float>(i, j));
    }
  }
  img.convertTo(test, CV_32FC1, 1.0 / 255.0);
  for (int i = 0; i < 256; ++i) {
    for (int j = 0; j < 256; ++j) {
      std::cout << img.at<float>(i, j) << std::endl;
    }
  }

  cv::imshow("test", test);
  cv::imshow("img", img);
  cv::waitKey(0);
  return 0;
}