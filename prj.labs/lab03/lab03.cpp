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
  //cv::Mat img = cv::imread("./data/cross_0256x0256.png");
  cv::Mat img = cv::imread("../data/cross_0256x0256.png");
  cv::Mat grayscale(256, 256, CV_8UC1);
  cv::Mat grayscaleLUT(256, 256, CV_8UC1);
  cv::Mat RGBLUT(256, 256, CV_8UC3);
  std::vector<double> y(256);
  std::vector<double> x(256);
  std::vector<uint8_t> LUT(256);


  for (int i = 0; i < 256; ++i) {
    double xValue = (double)i / 255;
    x[i] = xValue;
    double yValue = NontrivialFunc(xValue);
    y[i] = yValue;
    LUT[i] = cv::saturate_cast<uint8_t>(yValue * 255);
  }

  cv::imwrite("../data/lab03_rgb.png", img);

  cv::cvtColor(img, grayscale, cv::COLOR_BGR2GRAY);
  cv::imwrite("../data/lab03_gre.png", grayscale);

  cv::LUT(grayscale, LUT, grayscaleLUT);
  cv::imwrite("../data/lab03_gre_res.png", grayscaleLUT);

  cv::LUT(img, LUT, RGBLUT);
  cv::imwrite("../data/lab03_rgb_res.png", RGBLUT);

  cv::Mat viz = drawFunc(x, y);
  cv::imwrite("../data/lab03_viz_func.png", viz);

  return 0;
}
