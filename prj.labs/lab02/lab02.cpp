#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>

int main() {
  cv::Mat img = cv::imread("../data/cross_0256x0256.png");

  cv::imwrite("../data/cross_0256x0256_025.jpeg", img, {cv::IMWRITE_JPEG_QUALITY, 25});

  cv::Mat img025 = cv::imread("../data/cross_0256x0256_025.jpeg");

  //Сжатое изображение

  std::vector<cv::Mat> img025_RGB(3);
  cv::split(img025, img025_RGB);
  cv::Mat zeros  = cv::Mat::zeros(256, 256, CV_8UC1);
  cv::Mat img025_R;
  cv::Mat img025_G;
  cv::Mat img025_B;

  //Красный канал
  std::vector<cv::Mat> channels;
  channels.push_back(zeros);
  channels.push_back(zeros);
  channels.push_back(img025_RGB[2]);
  cv::merge(channels, img025_R);
  channels.clear();

  //Зелёный канал
  channels.push_back(zeros);
  channels.push_back(img025_RGB[1]);
  channels.push_back(zeros);
  cv::merge(channels, img025_G);
  channels.clear();

  //Синий канал
  channels.push_back(img025_RGB[0]);
  channels.push_back(zeros);
  channels.push_back(zeros);
  cv::merge(channels, img025_B);
  channels.clear();

  cv::Mat resulth, resultl, result;
  cv::hconcat(img025, img025_G, resulth);
  cv::hconcat(img025_R, img025_B, resultl);
  cv::vconcat(resulth, resultl, result);
  cv::imshow("res", result);
  cv::waitKey(0);

  cv::imwrite("../data/cross_0256x0256_jpg_channels.png", result);

  //Оригинальное изображение

  std::vector<cv::Mat> img_RGB(3);
  cv::split(img, img_RGB);
  cv::Mat img_R;
  cv::Mat img_G;
  cv::Mat img_B;

  //Красный канал
  channels.push_back(zeros);
  channels.push_back(zeros);
  channels.push_back(img_RGB[2]);
  cv::merge(channels, img_R);
  channels.clear();

  //Зелёный канал
  channels.push_back(zeros);
  channels.push_back(img_RGB[1]);
  channels.push_back(zeros);
  cv::merge(channels, img_G);
  channels.clear();

  //Синий канал
  channels.push_back(img_RGB[0]);
  channels.push_back(zeros);
  channels.push_back(zeros);
  cv::merge(channels, img_B);
  channels.clear();

  cv::hconcat(img, img_G, resulth);
  cv::hconcat(img_R, img_B, resultl);
  cv::vconcat(resulth, resultl, result);
  cv::imshow("res", result);
  cv::waitKey(0);

  cv::imwrite("../data/cross_0256x0256_png_channels.png", result);

  //Гистограммы

  //Оригинальное изображение
  int histSize = 256;

  float range[] = { 0, 256 } ;
  const float* histRange = { range };

  cv::Mat b_hist, g_hist, r_hist;

  cv::calcHist( &img_RGB[0], 1, 0, cv::Mat(), b_hist, 1, &histSize, &histRange);
  cv::calcHist( &img_RGB[1], 1, 0, cv::Mat(), g_hist, 1, &histSize, &histRange);
  cv::calcHist( &img_RGB[2], 1, 0, cv::Mat(), r_hist, 1, &histSize, &histRange);

  int hist_w = 512;
  int hist_h = 200;
  int bin_w = cvRound( (double) hist_w/histSize );

  cv::Mat histImage100( hist_h, hist_w, CV_8UC3, cv::Scalar( 0,0,0) );

  cv::normalize(b_hist, b_hist, 0, histImage100.rows, cv::NORM_MINMAX, -1, cv::Mat() );
  cv::normalize(g_hist, g_hist, 0, histImage100.rows, cv::NORM_MINMAX, -1, cv::Mat() );
  cv::normalize(r_hist, r_hist, 0, histImage100.rows, cv::NORM_MINMAX, -1, cv::Mat() );

  for( int i = 1; i < histSize; i++ )
  {
      cv::line( histImage100, cv::Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
                       cv::Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
                       cv::Scalar( 255, 0, 0), 2, 8, 0  );
      cv::line( histImage100, cv::Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
                       cv::Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
                       cv::Scalar( 0, 255, 0), 2, 8, 0  );
      cv::line( histImage100, cv::Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
                       cv::Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
                       cv::Scalar( 0, 0, 255), 2, 8, 0  );
  }

  //Сжатое изображение

  cv::calcHist( &img025_RGB[0], 1, 0, cv::Mat(), b_hist, 1, &histSize, &histRange);
  cv::calcHist( &img025_RGB[1], 1, 0, cv::Mat(), g_hist, 1, &histSize, &histRange);
  cv::calcHist( &img025_RGB[2], 1, 0, cv::Mat(), r_hist, 1, &histSize, &histRange);

  cv::Mat histImage025( hist_h, hist_w, CV_8UC3, cv::Scalar( 0,0,0) );

  cv::normalize(b_hist, b_hist, 0, histImage025.rows, cv::NORM_MINMAX, -1, cv::Mat() );
  cv::normalize(g_hist, g_hist, 0, histImage025.rows, cv::NORM_MINMAX, -1, cv::Mat() );
  cv::normalize(r_hist, r_hist, 0, histImage025.rows, cv::NORM_MINMAX, -1, cv::Mat() );

  for( int i = 1; i < histSize; i++ )
  {
      cv::line( histImage025, cv::Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
                       cv::Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
                       cv::Scalar( 255, 0, 0), 2, 8, 0  );
      cv::line( histImage025, cv::Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
                       cv::Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
                       cv::Scalar( 0, 255, 0), 2, 8, 0  );
      cv::line( histImage025, cv::Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
                       cv::Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
                       cv::Scalar( 0, 0, 255), 2, 8, 0  );
  }

  cv::vconcat(histImage100, histImage025, result);
  cv::imshow("Hists", result);
  cv::waitKey(0);

  cv::imwrite("../data/cross_0256x0256_hists.png", result);
  return 0;
}
