This was my last DSA project.

Grade: 100%

This project had two components: a standard heap and a binomial heap

The Heap class performs the following operations:

Heap() Default constructor O(1)

Heap(keytype k[], int s) Array Constructor, bottom up heap building O(s)

~Heap() Destructor O(1)

keytype peekKey() Returns minimum key without modification O(1)

keytype extractMin() Removes the minimum, restores heap order, returns the key O(lg n)

void insert (keytype k) Inserts k into the heap O (lg n)

void printKey() Prints the keys stored, starting at the root O(n)


The BHeap class performs the following operations:

BHeap() Default constructor O(1)

BHeap(keytype k[], int s) Array Constructor, repatead insertion O(s)

~BHeap() Destructor O(n)

keytype peekKey() Returns minimum key without modification O(lg n)

void insert (keytype k) Inserts key k into the heap O(lg n)

void merge(BHeap<keytype> &H2) Merges H2 into the current heap, consuming H2 O(lg n)

void printKey() Prints all keys,starts with smallest binomial tree first. Prints size of tree, then a modified preorder. O(n)

