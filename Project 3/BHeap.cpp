/*Project Checklist:

/ = in progress
O = not tested, not tested fully
X = completed

//MAKE CDA HAVE THE IFNDEF STUFF
[X] Default Constructor
[X] Array Constructor:
[X] copy constructor: assuming it works for now
[X] copy assignment: tested, seems to work
[X] Destructor

[X] peekKey
[X] extractMin:
[X] insert
[X] merge: SOURCE OF ALL PROBLEMS IT THAT HEAD BIT, SOMETHING
           IS WRONG WITH HOW I HANDLE THESE PASSED IN BHEAPS
[X] printKey: he wants it printing backwards, so I modified it to do so


left Off: Fix the spacing of the printing methods


Pretty sure that my destructor doesn't work;\

Aborted (Core Dumped) even if I don't call delete on H2


Gets through ALL of tester except the merging of Y. The logic is correct it
seems since I get thr proper rootlist pre-Heap2 deletion, but I get a aborted (core dumped)
when the delete is called. Tested with test case at bottom of main (Bruh Moment) one.
May be that I am using a BHeap* in everything that calls merge, but merge gives a literal
BHeap object, if that makes sense. Everything regarding BHeaps made in other functions would have
to change, as well as all references to BHeap. May be worth attempting through the copy
constructors as thay have a similar situation (a src. object deal). I took a picture
of what the intro server has to say about it, says "BHeap was not declared in thi scope"

Infinite loop when consolidating the tree

Incorrect connection formed when combining the two trees together (not consolidating)
Maybe I need to make my calls to "new Bheap" not have a pointer attached to them

error: redefinition of class CDA<elmtype> is my only error
otherwise, just write merge, copy assignment and copy constructor

Think the error is that CDA.cpp is being called twice when compiling, so
I need a fix for this (CDA.h) file?

*/

#include <iostream>
#include "CDA.cpp"
using namespace std;
template <typename keytype>

class Node { //node class
public:
  keytype key; //key stored in node
  Node *next = NULL; //used for the root list
  Node *parent = NULL; //points to parent
  CDA<Node<keytype>*> children; //learned my lesson from the previous project, changed keytype to Node since I point to Nodes, not keytype keys
  //can use length of children list to figure out node type
  //ie: a b0 would have a children list of size 0
};

template <typename keytype>
class BHeap{
private:
  Node<keytype>* head; //head to root level linked list
public:

  BHeap(){
    head = NULL; //make the head NULL, nothing in the root list
  } //end of constructor

  BHeap(keytype k[], int s){
    head = NULL;
    for (int i = 0; i < s; i++){ //for loop to insert each item
      insert(k[i]);
    }
  }//end of array constructor

  ~BHeap(){
    //cout << "In deconstructor" << endl;
    Node<keytype> *curNode = head; //poinst to current head
    Node<keytype> *holder;
    //delete the curNode, but make the head the thing after it
    while (curNode != NULL){
      //cout << "Current LL Root: " << curNode->key << endl;
      holder = curNode->next;
      recursiveDelete(curNode); //now delete the tree held at curNode
      curNode = holder;
    }
    curNode = NULL;
    holder = NULL;
    //head = NULL;
    //cout << "End of deconstructor" << endl;
  }//end of deconstructor

  BHeap (const BHeap& src){ //copy constructor
    //cout << "Copy" << endl;
    Node<keytype> *curNode = src.head;
    Node <keytype> *newStart = new Node<keytype>;
    head = newStart;
    //doing head first so i can make a trailer
    newStart->key = curNode->key;
    for (int i = 0; i < curNode->children.Length(); i++){//go through list of kids
      newStart->children.AddEnd(preorderConstruction(curNode->children[i]));
    }
    curNode = curNode->next; //increment

    while (curNode != NULL){//while we still have roots to go through
      Node <keytype> *newNode = new Node<keytype>;
      newNode->key = curNode->key;
      for (int i = 0; i < curNode->children.Length(); i++){//go through list of kids
        newNode->children.AddEnd(preorderConstruction(curNode->children[i]));
      }
      newStart->next = newNode;
      newStart = newStart->next;
      curNode = curNode->next;
    } //handled making the root list
}//end of copy constructor

BHeap &operator=(const BHeap &src){ //copy assignment
  //cout << "Copy assignment" << endl;
  //clear the current tree
  Node<keytype> *removeNode;
  while (head != NULL){
    removeNode = head; // current head
    head = head->next; //just made the head be the next thing
    recursiveDelete(removeNode); //now delete the tree held at curNode
  }

  Node<keytype> *curNode = src.head;
  Node <keytype> *newStart = new Node<keytype>;
  head = newStart;
  //doing head first so i can make a trailer
  newStart->key = curNode->key;
  for (int i = 0; i < curNode->children.Length(); i++){//go through list of kids
    newStart->children.AddEnd(preorderConstruction(curNode->children[i]));
  }
  curNode = curNode->next; //increment

  while (curNode != NULL){//while we still have roots to go through
    Node <keytype> *newNode = new Node<keytype>;
    newNode->key = curNode->key;
    for (int i = 0; i < curNode->children.Length(); i++){//go through list of kids
      newNode->children.AddEnd(preorderConstruction(curNode->children[i]));
    }
    newStart->next = newNode;
    newStart = newStart->next;
    curNode = curNode->next;
  } //handled making the root list
  return *this;
  }

Node <keytype>* preorderConstruction(Node<keytype>* curNodeSource){
  Node<keytype>* newNode = new Node<keytype>;
  if (curNodeSource == NULL) return NULL; ///just in case
  newNode->key = curNodeSource->key; //give it the same key
  for (int i = 0; i < curNodeSource->children.Length(); i++){//go through list of kids
    newNode->children.AddEnd(preorderConstruction(curNodeSource->children[i])); //call again on children
  }
  return newNode; //finally return the node since all children are known
}

  void recursiveDelete(Node<keytype> *curNode){
    //goes through and recursively deletes the children
    if (curNode == NULL) return;
    //cout << "In recursive delete" << endl;
    for (int i = 0; i < curNode->children.Length(); i++){
      recursiveDelete(curNode->children[i]); //go through all the kids first
    }
    //cout << "Deleting a node" << endl;
    //cout << "Deleting: " << curNode->key << endl;
    delete curNode; //now delete the node
  } //end of recursive delete

  keytype peekKey(){
    Node<keytype> *curNode = head;
    keytype min = head->key; //equals first key
    while (curNode != NULL){
      if (curNode->key < min) min = curNode->key;
      curNode = curNode->next;
    }
    return min;
  }//end of peek key

  keytype extractMin(){
    //when you extract, if possible, you could put the kids into a new heap
    //and then call merge (throw their roots in a new heap, make a helper
    //to do this, then call merge)
    Node<keytype> *curNode = head;
    Node<keytype>* min = head;
    //Node<keytype>* trailer = new Node<keytype>; //node used to trail behind
    //cout << "finding min node" << endl;
    while (curNode != NULL){ //finding min node
      if (curNode->key < min->key) min = curNode;
      curNode = curNode->next;
    }

    keytype minValue = min->key; //stored min value
    //cout << "Deleting: " << minValue << endl;
    //cout << "The min value is " << minValue << endl;
    //if (min == head) cout << "MIN IS THE HEAD" << endl;
    curNode = head; //reset to head
    //cout << "Going to the node before min" << endl;

    if (min != head){
    while (curNode->next->key != minValue){ //going to node before min node
      curNode = curNode->next;
    }
}

    if (min->children.Length() == 0){//no children case
      //cout << "min has no children" << endl;
      if (min == head){
        head = min->next;
      }
      else{
      curNode->next = min->next; //bridge the gap in linked list
    }
      delete min; //delete the node
  } //end of no children case


    else{ //min has children. tie them into a new heap and call merge
      //cout << "Children case" << endl;
      BHeap<keytype> *newHeap = new BHeap<keytype>;
      //now add them all in to the new heap
      newHeap->head = min->children[0]; //head is the first child
      Node<keytype> *navNode = newHeap->head; //equals the head
      //cout << navNode->key << " " ;
      for (int i = 1; i < min->children.Length(); i++){ //do for rest of children
        navNode->next = min->children[i];
        navNode = navNode->next;
        //cout << navNode->key << " " ;
        min->children[i]->parent = NULL; //make sure parent is set null
      }
      //navNode = newHeap->head;
/*
      while (navNode != NULL){
        cout << navNode->key << " ";
        navNode = navNode->next;
      }
      */
      navNode->next = NULL; //setting the very end to be NULL just in case

      if (min == head){
        head = min->next;
      }
      else{
      curNode->next = min->next; //bridge the gap in linked list before delete
    }
      delete min; //delete the node, since we got kids
      merge(*newHeap); //merge in the new trees with the current heap
      //cout << "I merged" << endl;
    } //end of has children case
    return minValue; //return the min
  }//end of extract min

  void insert(keytype k){
    //make a new heap with that single node and call merge
    if (head == NULL){ //if current heap is empty
      //cout << "Insert: heap is empty" << endl;
      Node<keytype> *insertNode = new Node<keytype>; //make it the root
      insertNode->key = k;
      head = insertNode; //make the head of root list equal the new node
      //cout << head->key << endl;
      return;
    }

    else{ //the heap already has at least one item in it
    //cout << "Insert: heap has an item already" << endl;
    BHeap<keytype> *newHeap = new BHeap<keytype>;
    Node<keytype> *insertNode = new Node<keytype>; //make the new node
    newHeap->head = insertNode;
    insertNode->key = k; //give it the key
    merge(*newHeap); //merge this new heap into the current one
    }
  }//end of insert


  void merge(BHeap<keytype> &H2){
    //the really big one that basically everything will have to use
    //given a second Bheap, merge it in with the current one
    //first put all of the element in, in order
    //cout << "Merge: Inside merge" << endl;
    Node<keytype> *H1Node = head; //add everything into here
    Node<keytype> *H2Node = H2.head;
    Node<keytype> *follower;

/*
    cout << "PASSED IN CHILDREN" << endl;
    while (H2Node != NULL){
      cout << H2Node->key << " ";
      H2Node = H2Node->next;
    }
    cout << endl; //ENDL HERE
  H2Node = H2.head;
*/
    //cout << H2Node->key << endl;
    Node <keytype> *temp;
    //H2.head = NULL; //the head now points to no nodes, as they are all moving into H1
    //since both heap are in order, we can do easily
    while (H1Node && H2Node != NULL){ //since we don't know sizes, was H1Node->next instead of H1Node

    //print the tree to see current loook
    /*
    cout << "STATUS: " << endl;
    temp = head;
    while (temp != NULL){
      cout << temp->key << " ";
      temp = temp->next;
    }
cout << endl;
*/
      //less than head case
      if (H2Node->children.Length() <= H1Node->children.Length() && H1Node == head){
        //cout << "Head case" << endl;
        //cout << " Head c ase: " << "H2: "<< H2Node->children.Length()<< " " << "H1: " << H1Node->children.Length()  << endl;
        //cout << " Head case: " << "H2: "<< H2Node->key<< " " << "H1: " << H1Node->key  << endl;
        head = H2Node; //make the head be the ndoe from H2
        H2Node = H2Node->next; //go ahead and make H2 be the next node;
        head->next = H1Node; //since node from H2 list is head, we can say its next is H1
        H1Node = head; //reset the head to be the node inserted.
        H2.head = H2Node; //UNSURE IF IT HELPS
      }


      //inserting between 2 nodes, put behind the H1
      else if (H2Node->children.Length() <= H1Node->children.Length()){
        //cout << " Case 2: Middle Insertion" << endl;
        temp = H1Node->next; //make the temp be the thing after H1Node
        follower->next = H2Node;
        H2Node = H2Node->next;
        H2.head = H2Node;
        follower->next->next = H1Node;
        H1Node = follower->next;
        /*
        follower->next->next = H1Node;
        H1Node->next = H2Node; //H1Node now points to H2Node atm
        H2Node = H2Node->next; //H2Node is now its next node
        H1Node->next->next = temp; //Stringing everything together
        //H1Node = H1Node->next; //incrementing H1Node to the node we inserted
        H2.head = H2Node; //UNSURE IF IT HELPS
        */
      }

      else{ //H2Node is not less than or equal to the H1Node
        //cout << " Case 3: Not <= to the H1 Node" << endl;
        follower = H1Node; //NEW
        H1Node = H1Node->next;
      }
    }

    //now done, if H1 is bigger than H2, no need to do anything
    //but if H2 is larger, H1 would become null, so we can just add everything to the end
    if (H2Node != NULL){ //then H1 must be NULL
      //cout << "   H2 still has items remaining, move them in" << endl;
      if (head == NULL){
        head = H2Node;
        //set the new head to be the H2Node, everything else is already strung together
      }

      else{
      H1Node = head;
      while (H1Node->next != NULL) H1Node = H1Node->next;

      while (H2Node != NULL){
      H1Node->next = H2Node; //next is the current H2Node
      H2Node = H2Node->next; //H2 Node will become its next
      H2.head = H2Node; //UNSURE IF IT HELPS
      H1Node = H1Node->next; //H1 node is the newly inserted H2 node
      }
    }
    }

    Node<keytype> *curNode = head;
    //cout << "Checking tree before consolidation: " << endl;

    //while (curNode != NULL){
    //cout << "b"<< curNode->children.Length() << " " ;
    //curNode = curNode->next;
  //}
  //cout << endl; //PRINTED ENDL HERE

    //Node<keytype> *curNode = head;
    //cout << "Checking tree before consolidation: " << endl;

    //while (curNode != NULL){
    //cout << "b"<< curNode->children.Length() << " " ;
    //curNode = curNode->next;
  //}
  //cout << endl; //PRINTED ENDL HERE

    //now consolidate the trees to be their proper types
    curNode = head;
    Node <keytype> *trailer; //to follow behind
    //cout << "     Tree Consolidation" << endl;
    while (curNode->next != NULL){ //iterate through the entire list
      //cout << "     curNode is a b" << curNode->children.Length() << endl;
      if (curNode->children.Length() == curNode->next->children.Length()){
        //if current node has same number of children as next node
        if (curNode->key <= curNode->next->key){ //make next node our child
          //cout << "     CurNode <= Next, make Next the child of CurNode" << endl;
          temp = curNode->next; //temp is the next node
          curNode->next = temp->next; //curNode will now point to the thing after temp
          temp->next = NULL; //temp no longer has a next
          temp->parent = curNode; //curNode is parent now
          curNode->children.AddEnd(temp); //the node pointer to children list
        } //current smaller than next

        else if (curNode->key > curNode->next->key){ //make curnode the next nodes child

          if (curNode == head){ //head case is special
            //cout << "     CurNode > Next and CurNode is the head" << endl;
            //make curNode the child of Next
            temp = curNode->next; //temp is the next node
            head = temp;
            temp->children.AddEnd(curNode);
            curNode = temp; //make curNode point to the node that made cur a child

            /*
            curNode->next = head; //redefine head
            curNode->next = NULL; //no longer has a next
            head->children.AddEnd(curNode); //add curNode to the children
            curNode = head; //reset curnode to point to new head
            */
        }

        else{ //if we are in the middle of the list
          //cout << "     CurNode > Next" << endl;
          temp = curNode->next; //temp is the next node
          trailer->next = temp; //make past node point to future node
          curNode->next = NULL; //won't have a next anymore
          temp->children.AddEnd(curNode); //put curNode pointer in children
          curNode = temp; //now the current Node is temp (the next)
          //trailer won't change as the next node could be of our new type
        }
      }//end of next is smaller than current
    }//end of same root type case

      else{ //not same node type, just iterate
        //cout << "     Not same node type, iterate" << endl;
        trailer = curNode; //trailer will be the previous curNode
        curNode = curNode->next; //curNode becomes the next node
      }

    } //end of while loop
    //everything should be done, just delete the previous tree
    //cout << "Current tree" << endl;
    curNode = head;
    //while (curNode != NULL){
    //cout << curNode->key << " " ;
    //curNode = curNode->next;
  //}
  //cout << endl;
    //cout << "     Survived, calling delete on H2" << endl;
    trailer = NULL;
    curNode = NULL;
    temp = NULL;
    H1Node = NULL;
    H2Node = NULL;
    //H2.head = NULL; //no nodes left in it, is still pointing to something though
    //INVESTIGATE ABOVE LINE, IT IS THE SORUCE OF PROBLEMS
    //delete &H2;
    /*
    cout << "Checking tree after consolidation: " << endl;
    curNode = head;
    while (curNode != NULL){
    cout << "b"<< curNode->children.Length() << " " ;
    curNode = curNode->next;
  }
  cout << endl; //PRINTED ENDL HERE
*/

  }//end of merge


  void printKey(){
    //modified preorder needs ton be used here
    Node<keytype>* curRoot = head; //goes through the root list
    //will use length of children array for tree type
    cout << " " << endl;
    while (curRoot != NULL){
      Node<keytype>* curNode = curRoot; //we equal the top of the tree
      cout << "B" << curNode->children.Length() << endl;
      recursivePrint(curNode); //goes through and prints all keys under
      cout << endl;
      curRoot = curRoot->next;
    }//end of traversing all roots
    //cout << " " << endl;
  }//end of print key

  void recursivePrint(Node<keytype>* curNode){
    //it seems he wants stuff to print in reverse
    cout << curNode->key << " "; //prints the curNode's key
    for (int i = curNode->children.Length() - 1; i >= 0; i--){
      recursivePrint(curNode->children[i]); //recursively calls from left to right
    }
  }//end of recursive print

};
