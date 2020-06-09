#ifndef _QTVAR_H_
#define _QTVAR_H_

#include <utility>
#include <cmath>
#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
#include "quadtree.h"
//#include "stats.h"
using namespace std;
using namespace cs221util;

class qtvar:public quadtree {

    /* this derived class allows for a generic prune algorithm */
    public:
        qtvar(PNG & im):quadtree(im){} // invokes base class constructor

    private:
        /* function prunable returns true if root->var is strictly less than 
        * tol. That is, a subtree can be pruned if its variance isn't too
        * high. 
        */
        bool prunable(Node * root, int tol);

};

#endif

