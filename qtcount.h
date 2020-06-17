#ifndef _QTCOUNT_H_
#define _QTCOUNT_H_

#include <utility>
#include <cmath>
#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
#include "quadtree.h"
//#include "stats.h"
using namespace std;
using namespace cs221util;

class qtcount:public quadtree {
    /* this derived class allows for a generic prune algorithm */

    public:
        qtcount(PNG & im):quadtree(im){} // invokes base class constructor
    private:

        /* function prunable returns true if all of the leaf nodes in root's 
        * subtree have color within tol of root->avg. Distance is measured as 
        * square distance over the color channels: (r1-r2)^2 + (g1-g2)^2 + (b1-b2)^2 
        * and "within" is inclusive of tol.
        */
        bool prunable(Node * root, int tol);

        // add your own helper functions here.
        void checkAvg(Node* node, int tol, RGBAPixel avg, bool result);

};

#endif
