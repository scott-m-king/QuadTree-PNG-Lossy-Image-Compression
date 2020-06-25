
// File:        main.cpp
// Author:      cheeren
// Date:        2018-02-25
// Description: Partial test of PA3 functionality
//              Reads Point data from external files
//              Produces PNG images of the point sets


#include "qtcount.h"
#include "qtvar.h"
#include "cs221util/RGBAPixel.h"
#include "cs221util/PNG.h"

using namespace cs221util;
using namespace std;

int main()
{


	// read in image
	PNG origIm1;
	origIm1.readFromFile("images/orig/KJVFbig.png");
	PNG origIm2;
	origIm2.readFromFile("images/orig/adasquare.png");
	PNG origIm3;
	origIm3.readFromFile("images/orig/stanley-totem-poles.png");
	PNG origIm4;
	origIm4.readFromFile("images/orig/leaf.png");
	// PNG origIm5;
	// origIm5.readFromFile("images/orig/network.png");
	// PNG origIm6;
	// origIm6.readFromFile("images/orig/scott.png");

	// use it to build a quadtree
	qtcount t1(origIm1);
	qtcount tCopy1(t1);
	qtcount t2(origIm2);
	qtcount tCopy2(t2);
	qtcount t3(origIm3);
	qtcount tCopy3(t3);
	qtcount t4(origIm4);
	qtcount tCopy4(t4);
	// qtcount t5(origIm5);
	// qtcount tCopy5(t5);
	// qtcount t6(origIm6);
	// qtcount tCopy6(t6);

	// prune the quadtree
	tCopy1.prune(10000); 
	tCopy2.prune(10000); 
	tCopy3.prune(3000); 
	tCopy4.prune(tCopy4.idealPrune(10000));
	// tCopy5.prune(10000);
	// tCopy6.prune(10000);

    
	// render the quadtree
	PNG ppic1 = tCopy1.render();
	PNG ppic2 = tCopy2.render();
	PNG ppic3 = tCopy3.render();
	PNG ppic4 = tCopy4.render();
	// PNG ppic5 = tCopy5.render();
	// PNG ppic6 = tCopy6.render();

	ppic1.writeToFile("images/out/output-prunedKJVFbig.png");
	ppic2.writeToFile("images/out/output-prunedadasquare.png");
	ppic3.writeToFile("images/out/output-prunedstanley-totem-poles-square.png");
	ppic4.writeToFile("images/out/output-prunednetwork.png");
	// ppic5.writeToFile("images/out/output-networkpruned.png");
	// ppic6.writeToFile("images/out/output-scottpruned.png");
	

	// use it to build a quadtree
	qtvar v1(origIm1);
	qtvar vCopy1(v1);
	qtvar v2(origIm2);
	qtvar vCopy2(v2);
	qtvar v3(origIm3);
	qtvar vCopy3(v3);
	qtvar v4(origIm4);
	qtvar vCopy4(v4);
	// qtvar v5(origIm5);
	// qtvar vCopy5(v5);
	// qtvar v6(origIm6);
	// qtvar vCopy6(v6);

	// prune the quadtree
	vCopy1.prune(10000); 
	vCopy2.prune(10000); 
	vCopy3.prune(3000); 
	vCopy4.prune(vCopy4.idealPrune(10000)); 
	// vCopy5.prune(10000);
	// vCopy6.prune(30000);
	
	// render the quadtree
	PNG vpic1 = vCopy1.render();
	PNG vpic2 = vCopy2.render();
	PNG vpic3 = vCopy3.render();
	PNG vpic4 = vCopy4.render();
	// PNG vpic5 = vCopy5.render();
	// PNG vpic6 = vCopy6.render();

	vpic1.writeToFile("images/out/output-prunedKJVFbig-var.png");
	vpic2.writeToFile("images/out/output-prunedadasquare-var.png");
	vpic3.writeToFile("images/out/output-prunedstanley-totem-poles-var.png");
	vpic4.writeToFile("images/out/output-prunednetwork-var.png");
	// vpic5.writeToFile("images/out/output-prunednetwork-var.png");
	// vpic6.writeToFile("images/out/output-scottpruned-var.png");

    // comparisons

    qtcount countcomp(origIm3);
    qtvar varcomp(origIm3);

    countcomp.prune(countcomp.idealPrune(10000));
    varcomp.prune(varcomp.idealPrune(10000));

/*
// I wrote two member functions to help me understand the different 
// compression strategies. I'm leaving this code here, so you 
// can explore similarly, if you like. The functions have been
// removed from the given code, but you can add them if you want!!
    cout << "count: " << countcomp.count() << endl;
    cout << "count dim: " << countcomp.dimsum() << endl;
    cout << "var: " << varcomp.count() << endl;
    cout << "var dim: " << varcomp.dimsum() << endl;
*/

    PNG countpng = countcomp.render();
    PNG varpng = varcomp.render();

    countpng.writeToFile("images/out/output-comp-count-stanley");
    varpng.writeToFile("images/out/output-comp-var-stanley");

  return 0;
}

