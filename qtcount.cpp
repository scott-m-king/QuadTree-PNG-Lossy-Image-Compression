#include "qtcount.h"

bool qtcount::prunable(Node * root, int tol) {
    bool result = true;
    checkAvg(root, tol, root->avg, result);
    return result;
}

void qtcount::checkAvg(Node * node, int tol, RGBAPixel & avg, bool & result) {
    if (node->NE == NULL && node->NW == NULL && node->SE == NULL && node->SW == NULL) {
        int red = pow((avg.r - node->avg.r),2);
        int green = pow((avg.g - node->avg.g),2);
        int blue = pow((avg.b - node->avg.b),2);

        if ((red + green + blue) > tol) result = false;
        return;
    } else {
        checkAvg(node->NW, tol, avg, result);
        checkAvg(node->NE, tol, avg, result);
        checkAvg(node->SW, tol, avg, result);
        checkAvg(node->SE, tol, avg, result);
    }
}