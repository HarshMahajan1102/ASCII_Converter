#ifndef ASCII_CONVERTER_HPP
#define ASCII_CONVERTER_HPP

#include <opencv2/opencv.hpp>

#include <string>
#include <string_view>

class AsciiConverter {

public:
  explicit AsciiConverter(std::string_view pal = " .:-=+*#%@");

  std::string imageToAscii(const cv::Mat &img, int w = 100, int h = 40,
                           bool autoH = true);

  std::string textToAscii(const std::string &txt, int w = 80, int h = 30);

  void playVideoAsAscii(const std::string &path, int w = 100, int h = 40,
                        bool autoH = true);

private:
  std::string pal_;

  char mapIntensityToChar(unsigned char px) const;
};

#endif
