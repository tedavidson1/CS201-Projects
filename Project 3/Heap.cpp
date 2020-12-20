/*Project Checklist:

/ = in progress
O = not tested, not tested fully
X = completed

[X] Default Constructor

[X] Array Constructor:

[X] copy constructor: TEST THESE
[X] copy assignment: TEST THESE
[X] Destructor
[X] peekKey
[X] extractMin:
[X] insert; did a light test of inserting 9,5,3,1,4,2 and it seemed to work
[X] printKey

[X] Heapify function

left Off: Extract min
*/

#include <iostream>
#include "CDA.cpp"
#include <math.h>
using namespace std;
template <typename keytype>

class Heap{
private:
  CDA<keytype> HeapArray; //CDA object

public:
  Heap(){ //default constructor
    CDA<keytype> HeapArray; //make the CDA
  }

  Heap(keytype k[], int s){ //array constructor
    for (int i = 0; i < s; i++){
      HeapArray.AddEnd(k[i]);
    }
    //now do the fixing of the levels
    for (int i = s - 1; i >= 0; i--){
      //cout << "Run: " << i << endl;
      Heapify(i, leftChild(i), rightChild(i));
    }
  }

  ~Heap(){ //Destructor
    //delete HeapArray;
    //figure the CDArray's own deconstructor will trigger
  }

  Heap ( Heap &src){ //copy constructor, build based on src, new object
    for (int i = 0; i < src.HeapArray.Length(); i++){
      HeapArray.AddEnd(src.HeapArray[i]); //should insert the current value of src to the end
    } //does for every value in src
  }

  Heap &operator=( Heap &src){ //copy assignment,clear, pre-existing object, build based on source and return
    HeapArray.Clear(); //need to clear it first
    for (int i = 0; i < src.HeapArray.Length(); i++){
      HeapArray.AddEnd(src.HeapArray[i]); //should insert the current value of src to the end
    } //does for every value in src
    return *this;
  }

  keytype peekKey(){ //return min key in heap
    return HeapArray[0];
  }

  keytype extractMin(){ //remove and return min key in heap
    keytype min = HeapArray[0]; //storing, will return at the end
    int size = HeapArray.Length(); //length is how many items are in array
    //cout << "Size is: " << size << endl;
    //move last value to the top
    HeapArray[0] = HeapArray[size - 1]; //moved bottom most to top
    //cout << "Value moved to top is: " << HeapArray[size - 1] << endl;
    HeapArray.DelEnd(); //delete the end from the array
    //now heapify
    Heapify(0, leftChild(0), rightChild(0));
    return min;
}//end of extract min

  void insert(keytype k ){ //inserts key k into the heap
    HeapArray.AddEnd(k);
    //above is just for testing purposes
    //since it doesn't cover the process of maintaining the tree property
    int size = HeapArray.Length(); //length is how many items are in array
    int child = size - 1; //gives the index of the last item
    int parent = parentIndex(child); //gets index of parent
    //int parent = floor((child - 1)/2); //equation to find parent

    //move up the value as far as it needs to go
    while (HeapArray[child] < HeapArray[parent] && child != 0){
      keytype temp = HeapArray[parent]; //store copy of parent data
      HeapArray[parent] = HeapArray[child]; //parent now has child data
      HeapArray[child] = temp; //child now has parent data
      child = parent;
      parent = parentIndex(child);
    } //end of while
  } //end of insert

  void printKey(){ //outputs keys stored, starting at root
    for (int i = 0; i < HeapArray.Length(); i++){
      cout << HeapArray[i] << " ";
    }
    cout << endl;
  }


//Helper functions that could be useful

int parentIndex(int index){ //given an index, finds the parent index
  return floor((index - 1)/2);
}

int leftChild (int index){ //like above, but for left
  int leftIndex = (2 * index) + 1;
  return leftIndex;

  //if (leftIndex <= HeapArray.Length() - 1) return leftIndex;
  //else return -1; //can use this to check if out of bounds naturally
}

int rightChild (int index){
   int rightIndex = (2 * index) + 2;
   return rightIndex;
}

void Heapify(int cur, int left, int right)
{
    //int l = left(i);
    //int r = right(i);
    int smallest = cur; //location we swap with
    if (left < HeapArray.Length() && HeapArray[left] < HeapArray[cur])
        smallest = left;
    if (right < HeapArray.Length() && HeapArray[right] < HeapArray[smallest])
        smallest = right;
    if (smallest != cur)
    {
      keytype temp;
      if (smallest == left){
        temp = HeapArray[cur]; //temp is cur
        HeapArray[cur] = HeapArray[left]; //cur is now left value
        HeapArray[left] = temp; //giving left temp
      }
      else{ //right case
        temp = HeapArray[cur]; //temp is cur
        HeapArray[cur] = HeapArray[right]; //cur is now right value
        HeapArray[right] = temp; //giving right temp
      }
        Heapify(smallest, leftChild(smallest), rightChild(smallest));
    }
}
/*
void Heapify(int cur, int left, int right){ //used to solve min and bottom up
  keytype temp;
  if (HeapArray[cur] > HeapArray[left] || HeapArray[cur] > HeapArray[right]){

  if (left < HeapArray.Length() && HeapArray[left] < HeapArray[right]){
    //swap cur with left
    temp = HeapArray[cur];
    HeapArray[cur] = HeapArray[left];
    HeapArray[left] = temp;
    Heapify(left, leftChild(left), rightChild(left));
  }

  else if (right < HeapArray.Length() && HeapArray[right] < HeapArray[left]){
    //swap cur with right
    temp = HeapArray[cur];
    HeapArray[cur] = HeapArray[right];
    HeapArray[right] = temp;
    Heapify(right, leftChild(right), rightChild(right));
  }
  else{
    return;
  }
}
return;
} //end of heapify
*/
};//end of class
