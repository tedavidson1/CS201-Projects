# CS201-Projects
Projects from CS201: Data Structures and Algorithms

This is my 2-3-4 Tree class used to implement the 2-3-4 Tree data structure.

There is a single error in the project regarding the search function. I am still unsure as to what is causing the error.

All functions: 
Two4Tree(); Default Constructor. The tree should be empty O(1)
Two4Tree(keytype k[],valuetype V[], int s); For this constructor the tree should be built using the arrays   K and V containing s items of keytype and valuetype. O(s lg s)
~Two4Tree(); Destructor for the class. O(n) 
valuetype *search(keytype k); Traditional search.  Should return a pointer to the valuetype stored with the key.  If the key is not stored in the tree then the function should return NULL. O(lg n)
void insert(keytype k, valuetype v); Inserts the node with key k and value v into the tree. O(lg n) 
int remove(keytype k); Removes the node with key k and returns 1.  If key k is not found then remove should return 0. O(lg n) 
int rank(keytype k); Returns the rank of the key k in the tree.  Returns 0 if the key k is not found. The smallest item in the tree is rank 1. O(lg n) 
keytype select(int pos); Order Statistics. Returns the key of the node at position pos in the tree.  Calling with pos = 1 should return the smallest key in the tree, pos = n should return the largest. O(lg n) 
keytype successor(keytype k); Returns the key after k in the tree. O(lg n)
keytype predecessor(keytype k); Returns the key before k in the tree. O(lg n)
int size(); returns the number of nodes in the tree. O(1)
void preorder(); Prints the keys of the tree in a preorder traversal. O(n)
void inorder(); Prints the keys of the tree in an inorder traversal.O(n) 
void postorder(); Prints the keys of the tree in a postorder traversal. O(n)

