
#ifndef _STATS_H
#define _STATS_H

#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
#include <utility>
#include <cmath>
#include <vector>
using namespace std;
using namespace cs221util;

class stats {

//private:
public:
	vector< vector< long >> sumRed;
	vector< vector< long >> sumGreen;
	vector< vector< long >> sumBlue;
	vector< vector< long >> sumsqRed;
	vector< vector< long >> sumsqGreen;
	vector< vector< long >> sumsqBlue;


	/* returns the sums of all pixel values across all color channels.
	* useful in computing the variance of a square
	* PA3 function
	* @param channel is one of r, g, or b
	* @param ul is (x,y) of the upper left corner of the square 
	* @param dim is log of side length of the square */
	long getSum(char channel, pair<int,int> ul, int dim);

	/* returns the sums of squares of all pixel values across all color channels.
	* useful in computing the variance of a square
	* PA3 function
	* @param channel is one of r, g, or b
	* @param ul is (x,y) of the upper left corner of the square 
	* @param dim is the log of the side length of the square */
	long getSumSq(char channel, pair<int,int> ul, int dim);

public:

	// initialize the private vectors so that, for each color,  entry 
	// (x,y) is the cumulative sum of the the color values from (0,0)
	// to (x,y). Similarly, the sumSq vectors are the cumulative
	// sum of squares from (0,0) to (x,y).
	stats(PNG & im); 

	// given a square, compute its sum of squared deviations from mean, over all color channels.
	/* @param ul is (x,y) of the upper left corner of the square 
	* @param dim is log of side length of the square*/
	double getVar(pair<int,int> ul, int dim);

	// given a square, return the average color value over the square as a pixel.
	/* Each color component of the pixel is the average value of that component over
	* the square.
	* @param ul is (x,y) of the upper left corner of the square 
	* @param dim is log of side length of the square */
	RGBAPixel getAvg(pair<int,int> ul, int dim);

	// given a square, return the number of pixels in the square
	/* @param ul is (x,y) of the upper left corner of the square 
	* @param dim is log of side length of the square */
	long rectArea(int dim);

};

#endif
