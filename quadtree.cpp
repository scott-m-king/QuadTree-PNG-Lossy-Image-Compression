
/**
 *
 * quadtree (pa3)
 * quadtree.cpp
 * This file will be used for grading.
 *
 */

#include "quadtree.h"
using namespace std;


// Node constructor, given.
quadtree::Node::Node(pair<int,int> ul, int d,RGBAPixel a, double v)
	:upLeft(ul),dim(d),avg(a),var(v),NW(NULL),NE(NULL),SE(NULL),SW(NULL)
	{}

// quadtree destructor, given.
quadtree::~quadtree() {
	clear();
}
// quadtree copy constructor, given.
quadtree::quadtree(const quadtree & other) {
	copy(other);
}
// quadtree assignment operator, given.
quadtree & quadtree::operator=(const quadtree & rhs) {
	if (this != &rhs) {
		clear();
		copy(rhs);
	}
	return *this;
}


quadtree::quadtree(PNG & imIn) {
        /* Your code here! */

}


quadtree::Node * quadtree::buildTree(stats & s, pair<int,int> & ul, int dim) {
        /* Your code here! */

}


PNG quadtree::render() {
        /* Your code here! */

}

int quadtree::idealPrune(int leaves){
        /* Your code here! */

}

int quadtree::pruneSize(int tol){
        /* Your code here! */

}

void quadtree::prune(int tol){
        /* Your code here! */

}

void quadtree::clear() {
/* your code here */
}

void quadtree::copy(const quadtree & orig){
/* your code here */
}


