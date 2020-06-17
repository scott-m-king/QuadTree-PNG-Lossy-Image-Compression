#include "qtcount.h"

bool qtcount::prunable(Node * root, int tol) {
    bool result = true;
    cout << "hello" << endl;
    checkAvg(root, tol, root->avg, result);
    return result;
}

void qtcount::checkAvg(Node* node, int tol, RGBAPixel avg, bool result) {
    if (node->NW == NULL) {
        int red = pow((node->avg.r - avg.r),2);
        int green = pow((node->avg.g - avg.g),2);
        int blue = pow((node->avg.b - avg.b),2);

        if ((red + green + blue) > tol) result = false;
        return;
    } 

    checkAvg(node->NW, tol, avg, result);
    checkAvg(node->NE, tol, avg, result);
    checkAvg(node->SW, tol, avg, result);
    checkAvg(node->SE, tol, avg, result);
}