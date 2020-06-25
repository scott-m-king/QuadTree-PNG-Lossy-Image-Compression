# QuadTree PNG Lossy Image Compression

A program to compress PNG images based on a calculation of average colour difference across a subsquare of pixels within the image. For this program, we used a QuadTree data structure to store calculated information about the color variance between pixels in a a 2^k x 2^k subsquare of the image. We then prune nodes off the QuadTree if the variance is greater than a user-specified value based on various compression strategies. 

Completed as a programming assignment for UBC CPSC 221 - Basic Data Structures and Algorithms. 

## Compression Strategies
*When a tree is pruned, all of the pixels contained in the tree are replaced a pixel whose colour is a calculation the average color across all the children before the prune.* 

### The Leaf Test
- Prunes off all of a subtree's children if the sum of squared differences between the root's color variance and all of its leaves' color variance is less than or equal to the tolerance (a parameter used to compare against a node's stored color variance information)

### The Variance Test
- Prunes off all of a subtree's children if the root's variance is strictly less than the tolerance input

### Ideal Prune
- We used a binary search approach to "optimize" our compression strategies by finding the minimum tolerance needed to produce an image with x number of squares. This allows the user to choose the quality of the output in a more predictable way than using tolerance (colour variance can vary greatly across images). 

## What I learned
- Dynamic programming concepts allowed us to avoid costly recalculation of colour variance for each subsquare by populating 2D vectors for each colour channel (RGB values) and using previously calculated values and matrix positions to calculate subsquare variance and average colour information in constant time. If we were to make these calculations on an ad-hoc basis without storing precalculated information, it would come at a cost of quadratic running time per calculation. 

- Recursion became more intuitive and less intimidating when working with QuadTrees. Many functions in this program required us to recurse over all nodes in the tree which helped build the foundation for using recursion with trees. 

- Passing values by reference to functions in C++ is important for avoiding behind-the-scenes calls to the copy constructor of an object with each call to a function. When working on the QuadTree constructor, we found that the creation of nodes was taking an unusally long time. After some digging, we found that some helper functions were not taking in parameters by reference (vectors in this specific case) which was inducing a call to the copy constructors for those parameters 4^n times in the constructor for the QuadTree structure. 
