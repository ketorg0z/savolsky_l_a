#include <opencv2/opencv.hpp>

int main() {
  //cv::Mat img(180, 768, CV_8UC1);
  //// draw dummy image
  //img = 0;
  //cv::Rect2d rc = {0, 0, 768, 60 };
  //cv::rectangle(img, rc, { 100 }, -1);
  //rc.y += rc.height;
  //cv::rectangle(img, rc, { 250 }, 1);
  //rc.y += rc.height;
  //cv::rectangle(img, rc, { 150 }, -1);
  //// save result
  //cv::imwrite("lab01.png", img);

  cv::Mat img(60, 768, CV_8UC1);
  // draw dummy image

  cv::Rect2d rc = { 0, 0, 3, 60 };
  for (int i = 0; i < 768; i += 3) {
    cv::rectangle(img, rc, { float(i / 3) }, -1);
    rc.x += 3;
  }

  //cv::imwrite("I_1.png", img);
  //cv::imshow("img", img);
  //cv::waitKey(0);

  cv::Mat img2(60, 768, CV_32FC1);
  img.convertTo(img, CV_64FC3);
  cv::imshow("img", img);
  cv::waitKey(0);
  cv::pow(img, 2.35, img2);

  //cv::imwrite("G_1.png", img2);
  //cv::imshow("img", img2);
  //cv::waitKey(0);
}
