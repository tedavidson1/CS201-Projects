/*Project Checklist:
/ = in progress
[X] Default Constructor
[X] Modified Constructor
[X] Deconstructor
[X] index operator
[X] Copy Constructor
[X] copy assignment operator
[X] AddEnd
[X] AddFront
[X] DelEnd
[X] DelFront

[X] Length
[X] EmptySlots
[X] Clear
[X] Ordered
[X] SetOrdered

[X] elmtype select
[X] InsertionSort
[X] MergeSort
[X] CountingSort
[X] Search

[X] Double Size and Copy
[X] Halve Size and Copy at 25%

Complete!
*/

#include <iostream>
#include <math.h>
#include <vector>
using namespace std;
template <typename elmtype>

class CDA {

private:
  //will edit all varaible names later, rn just need to write things I'll get
  elmtype failure; //return when out of bounds
  int capacity = 0; //how many spaces it has
  int size = 0; //how full it is
  int ordered = 0; //ordered flag
  int frontIndex = 0; //what is the first value's index?
  elmtype *CDArray; //the actual array

public:
    CDA(){ //create new CDA
      capacity = 1;
      size = 0;
      ordered = 0;
      frontIndex = 0;
      CDArray = new elmtype [capacity];
    }

    CDA(int s){ //create new CDA with capacity and size of s
      capacity = s;
      size = s; //why would size be s?
      ordered = 0;
      frontIndex = 0;
      CDArray = new elmtype [capacity];
    }

    ~CDA(){
    delete  [] CDArray;
    }

    CDA (const CDA &src){ //copy constructor
      CDArray = new elmtype [src.capacity];
      for (int i = 0; i < src.size; i++){
        CDArray[i] = src.CDArray[(src.frontIndex + i) % src.capacity];
      }
      frontIndex = 0;
      size = src.size;
      capacity = src.capacity;
      ordered = src.ordered;
  }

    CDA &operator=(const CDA &src){ //copy assignment, left side can already exist, so clear it
      delete[] CDArray;
      elmtype *newArray = new elmtype [src.capacity];
      for (int i = 0; i < src.size; i++){
        newArray[i] = src.CDArray[(src.frontIndex + i) % src.capacity];//slightly faster method I think
      } //because it avoids having to resize through AddEnd
      CDArray = newArray;
      frontIndex = 0;
      size = src.size;
      capacity = src.capacity;
      ordered = src.ordered;
      return *this;
    }

    elmtype& operator[](int i){
      if (i >= size){
        cout << "Out of Bounds" << endl;
        return failure;
      }
      else{
      elmtype& value = CDArray[(frontIndex + i) % capacity];
      ordered = 0;
      return value;
    }
  }

//                //
// Add and Delete //
// and dynamic stuff //

void doubleSize() {
elmtype *doubledArray = new elmtype [capacity * 2];
for (int i = 0; i < size; i++){
  doubledArray[i] = CDArray[(frontIndex + i) % capacity];
}
 //actually prints the new array's data
//everything is copied to the doubled size array
delete[] CDArray;
CDArray = doubledArray;
size = capacity;
capacity = capacity * 2;
frontIndex = 0;
ordered = 0;
} // end of doubleSize

void halveSize(){
  elmtype *halvedArray = new elmtype [capacity / 2];
  for (int i = 0; i < size; i++){
    halvedArray[i] = CDArray[(frontIndex + i) % capacity];
  }
  delete CDArray;
  CDArray = halvedArray;
  capacity = capacity / 2;
  frontIndex = 0;
  ordered = 0;
}



void AddEnd(elmtype v){
  if (capacity == size){
    doubleSize();
  }

  if (frontIndex == 0){
    CDArray[size] = v;
  }
  else{
    CDArray[(frontIndex + size) % capacity] = v;
  }

  if (size == 0){
    ordered = 1;
  }
  else if (ordered == 1){
    if (v < CDArray[(frontIndex + (size - 1)) % capacity]) //had -1, was error
      ordered = 0;
  }
  else if (ordered == -1){
    if (v > CDArray[(frontIndex + (size - 1)) % capacity]) //had-1, was error
    ordered = 0;
  }
  size++; //may need to adjust when I size++ relative to the math above
}


void AddFront (elmtype v){
  if (capacity == size){
    doubleSize();
  }

  if (size == 0){
    AddEnd(v);
    return; //test this to see if it handles the order correctly and size
  }
  else {
    frontIndex = (frontIndex + capacity - 1) % capacity;
    CDArray[frontIndex] = v;
    size++;
  }
  if (ordered == 1){
    if (v > CDArray[(frontIndex + 1) % capacity])
      ordered = 0;
  }
  else if (ordered == -1){
    if (v < CDArray[(frontIndex + 1) % capacity])
    ordered = 0; //orderd == 0 here for some reason
  }
}// end of add front

void DelFront(){
  frontIndex = (frontIndex + 1) % capacity;
  size--;

  if (((double)size / capacity) <= .25){
    if ((capacity / 2) < 4){
      return;
    }
    else{
    halveSize();
  }
  }
}


void DelEnd(){
  size--; //due to modular arithmetic, this works
  if (((double)size / capacity) <= .25){
    if ((capacity / 2) < 4){
      return;
    }
    else{
    halveSize();
  }
  }
}

//                //
// Side Operations//
//                //

void Clear(){
  delete[] CDArray;
  CDA();
}


int Length(){
  return size;
}

int Capacity(){ //personal test function
  return capacity;
}

int EmptySlots(){
  return capacity - size;
}

int Ordered(){
  return ordered;
}

  int SetOrdered(){
    bool ascending = true;
    bool descending = true;
    //cout << ascending << descending << endl;
    //cout << "Current Siz: " << size << endl;
      for (int i = 0; i < size - 1; i++){ //don't have to check last item since we compare it with element before it anyways
        if (CDArray[(frontIndex + i) % capacity] < CDArray[(frontIndex + (i+1)) % capacity]){
          //cout << "Current :" << CDArray[(size + i) % capacity] << " " << "Next: " << CDArray[(size + (i+1)) % capacity] << endl;
          descending = false;
        }
         else if (CDArray[(frontIndex + i) % capacity] > CDArray[(frontIndex + (i+1)) % capacity]){
          ascending = false;
        }
        //cout << "Checked: " << CDArray[(size + i) % capacity] << endl;
        //cout << "Ascending is " << ascending << endl;
        //cout << "descending is " << descending << endl;
      }
      if (ascending == true){
        ordered = 1;
        return 1;
      }
      else if (descending == true){
        ordered = -1;
        return -1;
      }
      else{
        ordered = 0;
        return 0;
      }
  }//end of SetOrdered

//                   //
// Searches and Sorts//
//                   //

elmtype Select(int k){
  if (ordered == 1){
    return CDArray[(frontIndex + (k-1)) % capacity];
  }
  else if (ordered == -1){
    //cout << "The decreasing case" << endl;
    return CDArray[(frontIndex + (size - k)) % capacity]; //DOES NOT WORK, FIX
  }
  else{ //quick select time
    vector<elmtype> copyList;
    for (int i = 0; i < size; i++){
      copyList.push_back(CDArray[(frontIndex + i) % capacity]);
    }
    //may need to cut out to meet time contraints
    //no idea if vectors allowed, he did use Lists in the example code
    return QuickSelect(copyList,k);
    //is returning a memory address, not sure as to what I need to change
    //in order to get it to give me an actual value, otherwise, seems to work
  }
}

  elmtype QuickSelect(vector<elmtype> valuesList, int k){
    elmtype pivot = valuesList.at(rand() % valuesList.size()); //random partition
    //cout << "Pivot: " << pivot << endl;
    vector<elmtype> L;
    vector<elmtype> E;
    vector<elmtype> G;

    for (int i = 0; i < valuesList.size(); i++){
    	if (valuesList.at(i) < pivot){
    		L.push_back(valuesList.at(i));
    	}
    	else if (valuesList.at(i) == pivot){
    		E.push_back(valuesList.at(i));
    	}
    	else{
    		G.push_back(valuesList.at(i));
    	}
    }

    if (k <= L.size()){
    	return QuickSelect(L, k);
    }
    else if (k <= L.size() + E.size()){
    	return pivot;
    }
    else{
      return QuickSelect(G, k-L.size() - E.size());
    }
  }//end of quickselect

int Search(elmtype e){
  if (ordered != 0){
    int left = 0;
    int right = size - 1;
      while (left <= right){
        int m = floor((left + right) / 2); //finds middle, had floor at first
        if (CDArray[(frontIndex + m) % capacity] < e){
          left = m + 1;
        }
        else if (CDArray[(frontIndex + m) % capacity] > e){
          right = m - 1;
        }
        else{
          return m;
        }
      }
  }//end of binary search
  else{
    for (int i = 0; i < size; i++){
      if (CDArray[(frontIndex + i) % capacity] == e)
        return i;
    }
  }
  return -1;
}//end of search

void InsertionSort(){
  for (int i = 1; i < size; i++){ //original: i =1; i < size; i++
    for (int j = i; (j > 0) && (CDArray[(frontIndex + (j - 1)) % capacity] < CDArray[(frontIndex + j) % capacity]); j--){
      elmtype temp = CDArray[(frontIndex + j) % capacity];
      CDArray[(frontIndex + j) % capacity] = CDArray[(frontIndex + (j-1)) % capacity];
      CDArray[(frontIndex + (j-1)) % capacity] = temp;
    }
  }
  ordered = -1;
}//end of insertion sort

void MergeSort(){
  elmtype *copyArray = new elmtype [size];
  for (int i = 0; i < size; i++){
  	copyArray[i] = CDArray[(frontIndex + i) % capacity];
  }
  divide(copyArray, 0, size - 1); //all recursion
  delete[] CDArray;
  CDArray = copyArray;
  capacity = size; //since new array
  frontIndex = 0; //since new array
  ordered = -1;
}

void merge(elmtype *arr, int l, int m, int r){
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;

  elmtype L[n1], R[n2];

  for (i = 0; i <n1; i++){
    L[i] = arr[l + i];
  }
  for (j = 0; j < n2; j++){
    R[j] = arr[m + 1 + j];
  }
i = 0;
j = 0;
k = l;

  while (i < n1 && j < n2){
    if (L[i] >= R[j]){
      arr[k] = L[i];
      i++;
    }
    else{
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1){
      arr[k] = L[i];
      i++;
      k++;
  }

  while (j < n2){
    arr[k] = R[j];
    j++;
    k++;
  }

}

void divide(elmtype *arr, int l, int r){
  if (l < r){
    int m = l + (r - l) / 2;
    divide(arr, l, m);
    divide(arr, m+1, r);
    merge(arr, l, m, r);
  }
}

void CountingSort(int m){
  ordered = -1; //set order flag to -1, since we make descending order
  int count [m+1]; //array of indexes 0 to m was = {}
  for (int i = 0; i < m+1; i++){
    count [i] = 0;
  }

  for (int i = 0; i < size; i++){
    count[CDArray[(frontIndex + i) % capacity]] += 1;
  }

  int total = 0;
  for (int i = m; i >= 0; i--){
    int temp = count[i];
    count[i] = total;
    total = total + temp;
  }

  elmtype *sortedArray = new elmtype [capacity];
    for (int i = 0; i < size; i++){
      sortedArray[count[CDArray[(frontIndex + i) % capacity]]] = CDArray[(frontIndex + i) % capacity];
      count[CDArray[(frontIndex + i) % capacity]] += 1;
}
delete[] CDArray;
CDArray = sortedArray;
frontIndex = 0;
//ordered = -1;
}//end of CountingSort

};
