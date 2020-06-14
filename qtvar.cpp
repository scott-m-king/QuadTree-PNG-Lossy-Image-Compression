#include "qtvar.h"

bool qtvar::prunable(Node * root, int tol) {
    return root->var < tol;
}
