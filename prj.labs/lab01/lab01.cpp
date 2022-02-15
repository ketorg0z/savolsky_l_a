#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
 cv::Mat I_1(60, 768, CV_8UC1);

  cv::Rect2d rc = { 0, 0, 3, 60 };
  for (int i = 0; i < 768; i += 3) {
    cv::rectangle(I_1, rc, { float(i / 3) }, -1);
    rc.x += 3;
  }
  cv::imshow("I_1", I_1);
  cv::waitKey(0);

  cv::imwrite("I_1.png", I_1);

  cv::Mat G_1;
  I_1.convertTo(G_1, CV_32FC1, 1.0/255.0);
  auto start = std::chrono::high_resolution_clock::now();
  cv::pow(G_1, 2.35,G_1);
  auto stop = std::chrono::high_resolution_clock::now();
  int duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
  std::cout << "G_1 duration - " << duration << " microseconds" << std::endl;

  cv::imshow("G_1", G_1);
  cv::waitKey(0);

  G_1.convertTo(G_1, CV_8UC3, 255);
  cv::imwrite("G_1.png", G_1);

  cv::Mat G_2;
  I_1.convertTo(G_2, CV_32FC1, 1.0/255.0);
  start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < 60; ++i){
    for (int j = 0; j < 768; ++j){
      G_2.at<float>(i, j) = std::pow(G_2.at<float>(i, j), 2.35);
    }
  }
  stop = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
  std::cout << "G_2 duration - " << duration << " microseconds" << std::endl;

  cv::imshow("G_2", G_2);
  cv::waitKey(0);

  G_2.convertTo(G_2, CV_8UC3, 255);
  cv::imwrite("G_2.png", G_2);

  cv::Mat I_2(180, 768, CV_32FC1);
  std::vector<cv::Mat> matrices = {I_1, G_1, G_2};
  cv::vconcat(matrices, I_2);

  cv::imshow("I_2", I_2);
  cv::waitKey(0);

  cv::imwrite("I_2.png", I_2);
  return 0;
}
