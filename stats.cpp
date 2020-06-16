
#include "stats.h"
#include <cmath>
#include <typeinfo>

#define LOG(msg, var) std::cout << msg << var << std::endl

stats::stats(PNG & im){
  setVectorDimensions(im);

  for (int i = 0; i < (int) im.height(); i++) {
    populateEdges(0, i, im);
  }

  setAccumulators();

  for (int i = 1; i < (int) im.width(); i++) {
    populateEdges(i, 0, im);
  }

  for (int row = 1; row < (int) im.width(); row++) {
    for (int col = 1; col < (int) im.height(); col++) {
      long red = im.getPixel(row, col)->r;
      long green = im.getPixel(row, col)->g;
      long blue = im.getPixel(row, col)->b;

      sumRed[row].push_back(sumRed[row][col-1] + sumRed[row-1][col] - sumRed[row-1][col-1] + red);
      sumGreen[row].push_back(sumGreen[row][col-1] + sumGreen[row-1][col] - sumGreen[row-1][col-1] + green);
      sumBlue[row].push_back(sumBlue[row][col-1] + sumBlue[row-1][col] - sumBlue[row-1][col-1] + blue);

      sumsqRed[row].push_back(sumsqRed[row][col-1] + sumsqRed[row-1][col] - sumsqRed[row-1][col-1] + pow(red,2));
      sumsqGreen[row].push_back(sumsqGreen[row][col-1] + sumsqGreen[row-1][col] - sumsqGreen[row-1][col-1] + pow(green,2));
      sumsqBlue[row].push_back(sumsqBlue[row][col-1] + sumsqBlue[row-1][col] - sumsqBlue[row-1][col-1] + pow(blue,2));
    }
  }
}

void stats::setVectorDimensions(PNG& im) {
  sumRed.resize(im.width());
  sumGreen.resize(im.width());
  sumBlue.resize(im.width());
  sumsqRed.resize(im.width());
  sumsqGreen.resize(im.width());
  sumsqBlue.resize(im.width());
}

void stats::populateEdges (int row, int col, PNG& im) {
  long red = im.getPixel(row, col)->r;
  long green = im.getPixel(row, col)->g;
  long blue = im.getPixel(row, col)->b;

  redSum += red;
  greenSum += green;
  blueSum += blue;
  redSumSq += pow(red,2);
  greenSumSq += pow(green,2);
  blueSumSq += pow(blue,2);

  sumRed[row].push_back(redSum);
  sumGreen[row].push_back(greenSum);
  sumBlue[row].push_back(blueSum);
  sumsqRed[row].push_back(redSumSq);
  sumsqGreen[row].push_back(greenSumSq);
  sumsqBlue[row].push_back(blueSumSq);
}

void stats::setAccumulators() {
  redSum = sumRed[0][0];
  greenSum = sumGreen[0][0];
  blueSum = sumBlue[0][0];
  redSumSq = sumsqRed[0][0];
  greenSumSq = sumsqGreen[0][0];
  blueSumSq = sumsqBlue[0][0];
}

long stats::getSum(char channel, pair<int,int> ul, int dim){
  switch(channel) {
    case 'r': return getSumHelper(sumRed, ul, dim);
    case 'g': return getSumHelper(sumGreen, ul, dim);
    case 'b': return getSumHelper(sumBlue, ul, dim);
    default:  return -1;
  }
}

long stats::getSumSq(char channel, pair<int,int> ul, int dim){
  switch(channel) {
    case 'r': return getSumHelper(sumsqRed, ul, dim);
    case 'g': return getSumHelper(sumsqGreen, ul, dim);
    case 'b': return getSumHelper(sumsqBlue, ul, dim);
    default:  return -1;
  }
}

long stats::getSumHelper(vector<vector<long>> sums, pair<int,int> ul, int dim) {
  int subAmount = pow(2,dim);
  
  int lrRow = ul.first + pow(2,dim)-1;
  int lrCol = ul.second + pow(2,dim)-1;
  long lr = sums[lrRow][lrCol];

  long leftSub = 0;
  long upSub = 0; 
  long cornerSub = 0;

  if (ul.first != 0) upSub = sums[lrRow-subAmount][lrCol];
  if (ul.second != 0) leftSub = sums[lrRow][lrCol-subAmount];
  if (ul.first != 0 && ul.second != 0) cornerSub = sums[ul.first-subAmount][ul.second-subAmount];

  return lr - leftSub - upSub + cornerSub;
}

// Since the dim represents log base 2 of side length, 
// to calculate total area is 2^(dim) * 2^(dim) = 4^(dim).
long stats::rectArea(int dim) {
  return pow(4, dim);
}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// see written specification for a description of this function.
double stats::getVar(pair<int,int> ul, int dim){
  long red = getSumSq('r', ul, dim) - (pow(getSum('r', ul, dim),2) / rectArea(dim));
  long green = getSumSq('g', ul, dim) - (pow(getSum('g', ul, dim),2) / rectArea(dim));
  long blue = getSumSq('b', ul, dim) - (pow(getSum('b', ul, dim),2) / rectArea(dim));

  return (double) red + green + blue;
}

RGBAPixel stats::getAvg(pair<int,int> ul, int dim){
  long red = getSum('r', ul, dim) / rectArea(dim);
  long green = getSum('g', ul, dim) / rectArea(dim);
  long blue = getSum('b', ul, dim) / rectArea(dim);

  return RGBAPixel(red, green, blue);
}
