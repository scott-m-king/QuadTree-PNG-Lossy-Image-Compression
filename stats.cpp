
#include "stats.h"
#include <cmath>
#include <typeinfo>

#define LOG(msg, var) std::cout << msg << var << std::endl

stats::stats(PNG & im){
  long red = 0;
  long green = 0;
  long blue = 0;
  long redsq = 0;
  long greensq = 0;
  long bluesq = 0;

  sumRed.resize(im.width());
  sumGreen.resize(im.width());
  sumBlue.resize(im.width());
  sumsqRed.resize(im.width());
  sumsqGreen.resize(im.width());
  sumsqBlue.resize(im.width());

  for (int row = 0; row < (int) im.width(); row++) {
    for (int col = 0; col < (int) im.height(); col++) {
      red += im.getPixel(row, col)->r;
      green += im.getPixel(row, col)->g;
      blue += im.getPixel(row, col)->b;
      redsq += pow(red, 2);
      greensq += pow(green, 2);
      bluesq += pow(blue, 2);

      sumRed[row].push_back(red);
      sumGreen[row].push_back(green);
      sumBlue[row].push_back(blue);
      sumsqRed[row].push_back(pow(red,2));
      sumsqGreen[row].push_back(pow(green,2));
      sumsqBlue[row].push_back(pow(blue,2));
    }
  }
}

long stats::getSum(char channel, pair<int,int> ul, int dim){
  int result = 0;
  for (int i = 0; i <= dim; i++) {
    for (int j = 0; j <= dim; j++) {
      switch(channel) {
        case 'r':
          result += sumRed[ul.first+i][ul.second+j];
        case 'g':
          result += sumGreen[ul.first+i][ul.second+j];
        case 'b':
          result += sumBlue[ul.first+i][ul.second+j];
      }
    }
  }
  return result;
}

long stats::getSumSq(char channel, pair<int,int> ul, int dim){
  int result = 0;
  for (int i = 0; i <= dim; i++) {
    for (int j = 0; j <= dim; j++) {
      switch(channel) {
        case 'r':
          result += sumsqRed[ul.first+i][ul.second+j];
        case 'g':
          result += sumsqGreen[ul.first+i][ul.second+j];
        case 'b':
          result += sumsqBlue[ul.first+i][ul.second+j];
      }
    }
  }
  return result;
}

// SK Comment: Since the dim represents log base 2 of side length, to calculate total area is 2^(dim) * 2.
long stats::rectArea(int dim) {
  return pow(2, dim) * 2;
}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// see written specification for a description of this function.
double stats::getVar(pair<int,int> ul, int dim){
  long red = getSumSq('r', ul, dim) - (pow(getSum('r', ul, dim),2) / rectArea(dim));
  LOG("Red: ", red);
  return 0; // stub
}
		
RGBAPixel stats::getAvg(pair<int,int> ul, int dim){
/* Your code here!! */
  return RGBAPixel();
}
