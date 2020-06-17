
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
  int sideLength = min(log2(imIn.height()), log2(imIn.width()));
  sideLength = pow(2,sideLength);

  imIn.resize(sideLength,sideLength);
  int dim = log2(sideLength);

  stats s = stats(imIn);
  pair<int,int> ul = {0,0};

  edge = sideLength;
  root = buildTree(s, ul, dim);
}

quadtree::Node * quadtree::buildTree(stats & s, pair<int,int> & ul, int dim) {

  Node* temp = new Node(ul, dim, s.getAvg(ul, dim), s.getVar(ul, dim));

  if (dim > 0) {
    int offset = pow(2,dim-1); 

    pair<int,int> nw = {ul.first, ul.second};
    pair<int,int> ne = {ul.first+offset, ul.second};
    pair<int,int> se = {ul.first, ul.second+offset};
    pair<int,int> sw = {ul.first+offset,ul.second+offset};

    temp->NW = buildTree(s, nw, dim-1);
    temp->NE = buildTree(s, ne, dim-1);
    temp->SE = buildTree(s, se, dim-1);
    temp->SW = buildTree(s, sw, dim-1);
  } else {
		temp->NW = NULL;
		temp->NE = NULL;
		temp->SE = NULL;
		temp->SW = NULL;
	}

  return temp;
}

PNG quadtree::render() {
	// pixels depend on the size of the squares
	return PNG();
}

// PNG quadtree::renderHelper(Node* root) {
// 	return PNG();
// }

int quadtree::idealPrune(int leaves) {
	return 0;
}

int quadtree::pruneSize(int tol) {
	return 0;
}

void quadtree::prune(int tol) {
	/* Your code here! */
}

void quadtree::clear() {
	deleteTree(root);
	delete root;
	root = NULL;
}

void quadtree::deleteTree(Node*& root) {
	if (root == NULL) return;
	deleteTree(root->NW);
	deleteTree(root->NE);
	deleteTree(root->SE);
	deleteTree(root->SW);
	delete root;
	root = NULL;
}

void quadtree::copy(const quadtree & orig) {
	edge = orig.edge;
	root = copyTree(orig.root);
}

quadtree::Node* quadtree::copyTree(Node* node) {
	if (node == NULL) return NULL;
	Node* temp = new Node(node->upLeft, node->dim, node->avg, node->var);
	temp->NW = copyTree(node->NW);
	temp->NE = copyTree(node->NE);
	temp->SE = copyTree(node->SE);
	temp->SW = copyTree(node->SW);
	return temp;
}


