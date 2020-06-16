
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
  int dim = min(log2(imIn.width()), log2(imIn.height()));
	stats s = stats(imIn);
	pair<int,int> ul = {0,0};

	root = buildTree(s, ul, dim);
	traverse(root);
	edge = dim;
}

quadtree::Node * quadtree::buildTree(stats & s, pair<int,int> & ul, int dim) {
	cout << "Dim: " << dim << endl;

	if (dim == 0) {
		Node* root = new Node(ul, dim, s.getAvg(ul, dim), s.getVar(ul, dim));
		root->NW = NULL;
		root->NE = NULL;
		root->SE = NULL;
		root->SW = NULL;
		return root;
	}

	Node* root = new Node(ul, dim, s.getAvg(ul, dim), s.getVar(ul, dim));

	// 2^dim/2 == 2^(dim-1) (dim represents log_2 of side length, need to half each recursion)
	int offset = pow(2,dim-1); 

	pair<int,int> nw = {ul.first, ul.second};
	pair<int,int> ne = {ul.first, ul.second+offset};
	pair<int,int> sw = {ul.first+offset, ul.second};
	pair<int,int> se = {ul.first+offset,ul.second+offset};

	root->NW = buildTree(s, nw, dim-1);
	root->NE = buildTree(s, ne, dim-1);
	root->SE = buildTree(s, se, dim-1);
	root->SW = buildTree(s, sw, dim-1);

	return root;
}

void quadtree::traverse(Node* root) {
	// if (root == NULL) return;
	// traverse(root->NW);
	// traverse(root->NE);
	// traverse(root->SE);
	// traverse(root->SW);

	// cout << "Avg: " << s.getAvg(ul, dim) << ", Var: " << s.getVar(ul, dim) << endl;
	// cout << "(" << root->upLeft.first << ", " << root->upLeft.second << ")" << endl;
}

PNG quadtree::render() {
	// pixels depend on the size of the squares
	return PNG();
}

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
	deleteNodes(root);
}

void quadtree::deleteNodes(Node*& root) {
	// if (root == NULL) return;
	// deleteNodes(root->NW);
	// deleteNodes(root->NE);
	// deleteNodes(root->SE);
	// deleteNodes(root->SW);
	// delete root;
	// root = NULL;
}

void quadtree::copy(const quadtree & orig) {
	/* your code here */
}


