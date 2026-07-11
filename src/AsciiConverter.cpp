#include "AsciiConverter.hpp"

#include <chrono>
#include <iostream>
#include <thread>

using namespace std;
using namespace cv;
using namespace chrono;

AsciiConverter::AsciiConverter(string_view pal) : pal_(pal) {}

char AsciiConverter::mapIntensityToChar(unsigned char px) const {
  size_t idx = (static_cast<size_t>(px) * (pal_.length() - 1)) / 255;
  return pal_[idx];
}

string AsciiConverter::imageToAscii(const Mat &img, int w, int h, bool autoH) {
  if (img.empty())
    return "Error: Empty frame/image.\n";

  Mat gray;

  if (img.channels() >= 3)
    cvtColor(img, gray, COLOR_BGR2GRAY);
  else
    gray = img.clone();

  int th = h;

  if (autoH) {
    double ar = static_cast<double>(gray.rows) / gray.cols;
    th = static_cast<int>(w * ar * 0.55);
  }

  th = max(1, th);
  w = max(1, w);

  Mat out;
  resize(gray, out, Size(w, th), 0, 0, INTER_AREA);

  string ascii;
  ascii.reserve((w + 1) * th);

  for (int i = 0; i < out.rows; i++) {
    for (int j = 0; j < out.cols; j++)
      ascii += mapIntensityToChar(out.at<unsigned char>(i, j));

    ascii += '\n';
  }

  return ascii;
}

string AsciiConverter::textToAscii(const string &txt, int w, int h) {
  int base = 0;
  int font = FONT_HERSHEY_SIMPLEX;

  double scale = 1.3;
  int thick = 2;

  Size sz = getTextSize(txt, font, scale, thick, &base);

  Mat canvas = Mat::zeros(sz.height + 30, sz.width + 40, CV_8UC1);

  putText(canvas, txt, Point(20, sz.height + 15), font, scale, Scalar(255),
          thick);

  return imageToAscii(canvas, w, h, false);
}

void AsciiConverter::playVideoAsAscii(const string &path, int w, int h,
                                      bool autoH) {

  VideoCapture cap(path);

  if (!cap.isOpened()) {
    cerr << "\nError: Could not open video file.\n";
    this_thread::sleep_for(seconds(2));
    return;
  }

  double fps = cap.get(CAP_PROP_FPS);
  int delay = fps > 0 ? static_cast<int>(1000.0 / fps) : 33;

  Mat frame;

  cout << "\033[2J";

  while (true) {

    auto st = high_resolution_clock::now();

    cap >> frame;

    if (frame.empty())
      break;

    cout << "\033[H" << imageToAscii(frame, w, h, autoH) << flush;

    auto ed = high_resolution_clock::now();

    milliseconds t = duration_cast<milliseconds>(ed - st);

    if (t.count() < delay)
      this_thread::sleep_for(milliseconds(delay) - t);

    if (!cout)
      break;
  }

  cout << "\nPlayback complete. Press Enter...";
  cin.ignore();
  cin.get();
}
