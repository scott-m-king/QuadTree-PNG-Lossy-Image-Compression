
#include "stats.h"
#include <cmath>
#include <typeinfo>

#define LOG(msg, var) std::cout << msg << var << std::endl

stats::stats(PNG & im){
  sumRed.resize(im.width());
  sumGreen.resize(im.width());
  sumBlue.resize(im.width());
  sumsqRed.resize(im.width());
  sumsqGreen.resize(im.width());
  sumsqBlue.resize(im.width());

  int redSum = 0;
  int greenSum = 0;
  int blueSum = 0;
  int redSumSq = 0;
  int greenSumSq = 0;
  int blueSumSq = 0;

  for (int row = 0; row < (int) im.width(); row++) {
    redSum += im.getPixel(row, 0)->r;
    greenSum += im.getPixel(row, 0)->g;
    blueSum += im.getPixel(row, 0)->b;
    redSumSq += pow(redSum,2);
    greenSumSq += pow(greenSum,2);
    blueSumSq += pow(blueSum,2);

    sumRed[row].push_back(redSum);
    sumGreen[row].push_back(greenSum);
    sumBlue[row].push_back(blueSum);
    sumsqRed[row].push_back(redSumSq);
    sumsqGreen[row].push_back(greenSumSq);
    sumsqBlue[row].push_back(blueSumSq);
  }

  redSum = 0;
  greenSum = 0;
  blueSum = 0;
  redSumSq = 0;
  greenSumSq = 0;
  blueSumSq = 0;

  for (int col = 1; col < (int) im.height(); col++) {
    redSum += im.getPixel(0, col)->r;
    greenSum += im.getPixel(0, col)->g;
    blueSum += im.getPixel(0, col)->b;
    redSumSq += pow(redSum,2);
    greenSumSq += pow(greenSum,2);
    blueSumSq += pow(blueSum,2);

    sumRed[0].push_back(redSum);
    sumGreen[0].push_back(greenSum);
    sumBlue[0].push_back(blueSum);
    sumsqRed[0].push_back(redSumSq);
    sumsqGreen[0].push_back(greenSumSq);
    sumsqBlue[0].push_back(blueSumSq);
  }

  for (int row = 1; row < (int) im.width(); row++) {
    for (int col = 1; col < (int) im.height(); col++) {
      long red = im.getPixel(row, col)->r;
      long green = im.getPixel(row, col)->g;
      long blue = im.getPixel(row, col)->b;
      sumRed[row].push_back(sumRed[row][col-1] + sumRed[row-1][col] + red);
      sumGreen[row].push_back(sumGreen[row][col-1] + sumGreen[row-1][col] + green);
      sumBlue[row].push_back(sumBlue[row][col-1] + sumBlue[row-1][col] + blue);
      sumsqRed[row].push_back(sumsqRed[row][col-1] + sumsqRed[row-1][col] + pow(red,2));
      sumsqGreen[row].push_back(sumsqGreen[row][col-1] + sumsqGreen[row-1][col] + pow(green,2));
      sumsqBlue[row].push_back(sumsqBlue[row][col-1] + sumsqBlue[row-1][col] + pow(blue,2));
    }
  }
}

long stats::getSum(char channel, pair<int,int> ul, int dim){
  switch(channel) {
    case 'r':
      return sumRed[ul.first+dim][ul.second+dim];
    case 'g':
      return sumGreen[ul.first+dim][ul.second+dim];
    case 'b':
      return sumBlue[ul.first+dim][ul.second+dim];
  }
}

long stats::getSumSq(char channel, pair<int,int> ul, int dim){
  switch(channel) {
    case 'r':
      return sumsqRed[ul.first+dim][ul.second+dim];
    case 'g':
      return sumsqGreen[ul.first+dim][ul.second+dim];
    case 'b':
      return sumsqBlue[ul.first+dim][ul.second+dim];
  }
}

// SK Comment: Since the dim represents log base 2 of side length, to calculate total area is 2^(dim) * 2.
long stats::rectArea(int dim) {
  return pow(2, dim) * 2;
}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// see written specification for a description of this function.
double stats::getVar(pair<int,int> ul, int dim){
  long red = getSumSq('r', ul, dim) - (pow(getSum('r', ul, dim),2) / rectArea(dim));
  long green = getSumSq('g', ul, dim) - (pow(getSum('g', ul, dim),2) / rectArea(dim));
  long blue = getSumSq('b', ul, dim) - (pow(getSum('b', ul, dim),2) / rectArea(dim));
  return red + green + blue;
}
		
RGBAPixel stats::getAvg(pair<int,int> ul, int dim){
/* Your code here!! */
  return RGBAPixel();
}
