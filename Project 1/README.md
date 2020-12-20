This is my circular dynamic array class to implement that data structure.

Grade: 86%

There are still errors on Search and Empty  Slots.


All functions:

CDA(); Default Constructor. The array should beof capacity 1, size 0, and ordered is false. O(1)

CDA(int s); For this constructor the array should be of capacity and sizes with ordered = false. O(1)

~CDA(); Destructor for the class. O(1)

elmtype& operator[](int i); Traditional [] operator. Should print a message if i is out of bounds (outside 0...size-1) and return a reference to value of type elmtype stored in the class for this purpose. O(1)

void AddEnd(elmtype v); increases the size of the array by 1 and stores v at the end of the array. Should double the capacity when the new element doesn't fit.  If ordered is true, check to be sure that the array is still in order. O(1) amortized 

void AddFront(elmtype v); increases the size of the array by 1 and stores v at the beginning of the array. Should double the capacity when the new element doesn't fit. The new element should be the item returned at index 0.  If ordered is true, check to be sure that the array is still in order. O(1) amortized 

void DelEnd(); reduces the size of the array by 1 at the end. Should shrink the capacity when only 25% of the array is in use after the delete.The capacity should never go below 4. O(1) amortized

void DelFront(); reduces the size of the array by 1 at the beginning of the array. Should shrink the capacity when only 25% of the array is in use after the delete. The capacity should never go below 4. O(1) amortized 

int Length(); returns the size of the array. O(1)

int EmptySlots(); returns the capacity-size of the array. O(1) 

void Clear(); Frees any space currently used and starts over with an array of capacity 1 and size 0.O(1)

intOrdered(); Returns the status of the ordered flag. 1 is increasing order, -1 is decreasing order, 0 is unordered. O(1)

int SetOrdered(); Check to see if the array is in order.  Set the order flag appropriately.  Return 1 if the array was in increasing order, -1 if the array was in decreasing order and 0 otherwise. O(size)

elmtype Select(int k); returns the kth smallest element in the array. If the array is in increasing order, then return the item at index k-1. If the array is in decreasing order, then return the item at index size - k.  Otherwise use the quickselect algorithm. Quickselect should choose a random partition element. O(1) or O(size) expected 

void InsertionSort(); Performs insertion sort on the array.  Sets ordered to true. Should return decreasing order. O(size*size) worst case 

void MergeSort(); Sorts the values in the array using the mergesort algorithm. Set ordered to true. Should return decreasing order. O(sizelg size)worst case

void CountingSort(int m); Sorts the values in the array using counting sort, where the values in the array are in the range 0...m.  Set ordered to true. You may assume that all values in the array are integers in the range 0...m. Should return decreasing order. O(size * m) 

int Search(elmtype e) If the array is ordered in either increasing or decreasing order, perform a binary search of the array looking for the item e. Otherwise perform linear search. Returns the index of the item if found or -1 otherwise. O(lg size) or O(size)
