#include "AsciiConverter.hpp"

#include <iostream>
#include <string>

using namespace std;
using namespace cv;

void clr() { cout << "\033[2J\033[H"; }

void getSize(int &w, int &h, bool &autoH) {

  string sw, sh;

  cout << "Width [100]: ";
  getline(cin, sw);

  w = sw.empty() ? 100 : stoi(sw);

  cout << "Auto height? (y/n) [y]: ";

  string ch;
  getline(cin, ch);

  if (ch == "n" || ch == "N") {

    autoH = false;

    cout << "Height [40]: ";
    getline(cin, sh);

    h = sh.empty() ? 40 : stoi(sh);
  }

  else
    autoH = true;
}

int main() {

  AsciiConverter ac;

  string ch;

  while (true) {

    clr();

    cout << "====================================\n";
    cout << "      ASCII ART CONVERTER\n";
    cout << "====================================\n";
    cout << "1. Text\n";
    cout << "2. Image\n";
    cout << "3. Video\n";
    cout << "4. Exit\n";
    cout << "====================================\n";
    cout << "Choice: ";

    getline(cin, ch);

    if (ch == "4") {
      cout << "Goodbye!\n";
      break;
    }

    int w = 100;
    int h = 40;

    bool autoH = true;

    if (ch == "1") {

      string txt;

      cout << "\nText: ";
      getline(cin, txt);

      getSize(w, h, autoH);

      clr();

      cout << ac.textToAscii(txt, w, h);

      cout << "\nPress Enter...";
      cin.get();
    }

    else if (ch == "2") {

      string path;

      cout << "\nImage path: ";
      getline(cin, path);

      Mat img = imread(path);

      if (img.empty()) {

        cout << "Cannot open image.\n";
        cin.get();

        continue;
      }

      getSize(w, h, autoH);

      clr();

      cout << ac.imageToAscii(img, w, h, autoH);

      cout << "\nPress Enter...";
      cin.get();
    }

    else if (ch == "3") {

      string path;

      cout << "\nVideo path: ";
      getline(cin, path);

      getSize(w, h, autoH);

      ac.playVideoAsAscii(path, w, h, autoH);
    }
  }

  return 0;
}
