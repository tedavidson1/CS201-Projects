
/*Project Checklist:
/ = in progress
O = not tested, not tested fully
X = completed
[X] Default Constructor
[X] Array Build constructor
[X] Destructor: use post order to delete
[X] copy Constructor :use preorder to copy
[X] copy assignment operator

[X] Traditional Search: still has an error in it for some reason

[X] Insert
[X]preemptive split of 4 node

[X] Remove: Helpers listed below. Needs to update keyshereunder still, doing -1 for visits
  [X]Merge: Good to go I think
  [X]RemoveLeaf: Good to go I think
  [X]rotateLeft: Good to go I think
  [X]rotateRight: Good to go I think

[X] Rank 
[X] Select
[X] successor
[X] predecessor

[X] Size
[X] preorder
[X] inorder
[X] postorder
*/

#include <iostream>
using namespace std;
template <typename keytype, typename valuetype>

class Node { //node class
public:
  int nodeStatus; //2-3-4 Node?
  int keysHereUnder = 0; //How many keys are at/beneath. Set to 0 for a default value

  keytype firstKey; //what we use for tree navigation
  keytype secondKey;
  keytype thirdKey; //each node can have 3 keys

  valuetype firstValue; //first data bit
  valuetype secondValue; //second data bit
  valuetype thirdValue; //third data bit

  Node *parent = NULL; //parent
  Node *childOne = NULL; //first child
  Node *childTwo = NULL; //second child
  Node *childThree = NULL; //third child
  Node *childFour = NULL; //third child
};

template <typename keytype, typename valuetype>
class Two4Tree { //the tree
//key is like the numbers we see in examples
private:
  int treeSize;
  Node<keytype, valuetype>* root; //had them switched originally

public:
  Two4Tree(){ //default constructor
    //cout << "In default constructor" << endl;
    treeSize = 0;
    root = NULL;
  }

  Two4Tree(keytype k[], valuetype V[], int s){ //build from array constructor
      //cout << "In array constructor" << endl;
      treeSize = 0;
      root = NULL;
      for (int i = 0; i < s; i++){
        insert(k[i], V[i]);
      }
    } //end of array constructor

  ~Two4Tree(){
    //use postorder for easy removal
    Node<keytype, valuetype>* curNode = new Node<keytype, valuetype>;
    curNode = root;
    postorderDeletion(curNode);
  }

  Two4Tree (const Two4Tree& src){ //copy constructor
    //cout << "Copy" << endl;
    if (src.root == NULL){
      root = NULL;
      treeSize = src.treeSize;
    }
    else{
    Node<keytype, valuetype>* curNode = new Node<keytype, valuetype>; //navigation
    curNode = src.root; //we use this to navigate the built structure
    Node<keytype, valuetype>* newNode = new Node<keytype, valuetype>;
    newNode = preorderConstruction(curNode);
    treeSize = src.treeSize;
    //cout << "I survived" << endl;
    root = newNode;
  }
}//end of copy constructor

  Two4Tree &operator=(const Two4Tree &src){ //copy assignment
    if (src.root == NULL){
      root = NULL;
      treeSize = src.treeSize;
      return *this;
    }
    else{
    postorderDeletion(root); //clearing it
    Node<keytype, valuetype>* srcRoot = new Node<keytype, valuetype>;
    root = preorderConstruction(srcRoot); //making it just like src
    treeSize = src.treeSize;
    return *this;
    }
  }

Node <keytype, valuetype>* preorderConstruction(Node<keytype, valuetype>* curNodeSource){
Node<keytype, valuetype>* newNode = new Node<keytype, valuetype>;
    if (curNodeSource == NULL) return NULL; //so it isn't a valid node in tree at all
    else if (curNodeSource->nodeStatus == 2){ //at a 2 Node
      //cout << "2 Node Case" << endl;
      newNode->firstKey = curNodeSource->firstKey;
      newNode->firstValue = curNodeSource->firstValue;
      newNode->nodeStatus = curNodeSource->nodeStatus;
      newNode->keysHereUnder = curNodeSource->keysHereUnder;
      newNode->parent = curNodeSource->parent; //just in case
      newNode->childOne = preorderConstruction(curNodeSource->childOne);
      newNode->childTwo = preorderConstruction(curNodeSource->childTwo);
    }
    else if (curNodeSource->nodeStatus == 3){
      //cout << "3 Node Case" << endl;
      newNode->firstKey = curNodeSource->firstKey;
      newNode->firstValue = curNodeSource->firstValue;
      newNode->secondKey = curNodeSource->secondKey;
      newNode->secondValue = curNodeSource->secondValue;
      newNode->nodeStatus = curNodeSource->nodeStatus;
      newNode->keysHereUnder = curNodeSource->keysHereUnder;
      newNode->parent = curNodeSource->parent; //just in case
      newNode->childOne = preorderConstruction(curNodeSource->childOne);
      newNode->childTwo = preorderConstruction(curNodeSource->childTwo);
      newNode->childThree = preorderConstruction(curNodeSource->childThree);
    }
    else{
      //cout << "4 Node Case" << endl;
      newNode->firstKey = curNodeSource->firstKey;
      newNode->firstValue = curNodeSource->firstValue;
      newNode->secondKey = curNodeSource->secondKey;
      newNode->secondValue = curNodeSource->secondValue;
      newNode->thirdKey = curNodeSource->thirdKey;
      newNode->thirdValue = curNodeSource->thirdValue;
      newNode->nodeStatus = curNodeSource->nodeStatus;
      newNode->keysHereUnder = curNodeSource->keysHereUnder;
      newNode->parent = curNodeSource->parent; //just in case
      newNode->childOne = preorderConstruction(curNodeSource->childOne);
      newNode->childTwo = preorderConstruction(curNodeSource->childTwo);
      newNode->childThree = preorderConstruction(curNodeSource->childThree);
      newNode->childFour = preorderConstruction(curNodeSource->childFour);
    }
    //kid has no clue who parent is though
if (newNode->childOne != NULL){
    if (newNode->nodeStatus == 2){
      //cout << "2 Node Parents" << endl;
      //cout << "Key: "<<newNode->firstKey << endl;
      newNode->childOne->parent = newNode;
      newNode->childTwo->parent = newNode;
    }
    else if (newNode->nodeStatus == 3){
      //cout << "3 Node Parents" << endl;
      //cout << "Keys: "<< newNode->firstKey << " " << newNode->secondKey << endl;
      newNode->childOne->parent = newNode;
      newNode->childTwo->parent = newNode;
      newNode->childThree->parent = newNode;
    }
    else{
      //cout << "4 Node Parents" << endl;
      //cout << "Keys: "<< newNode->firstKey << " " << newNode->secondKey << " " << newNode->thirdKey << endl;
      newNode->childOne->parent = newNode;
      newNode->childTwo->parent = newNode;
      newNode->childThree->parent = newNode;
      newNode->childFour->parent = newNode;
    }
  }
    return newNode;
} // end of function

  void postorderDeletion(Node<keytype, valuetype>* curNode){
    //cout << "Destructor" << endl;
    if (curNode == NULL) return;
    else if (curNode->nodeStatus == 2){
      postorderDeletion(curNode->childOne);
      postorderDeletion(curNode->childTwo);
      delete curNode;
    }
    else if (curNode->nodeStatus == 3){
      postorderDeletion(curNode->childOne);
      postorderDeletion(curNode->childTwo);
      postorderDeletion(curNode->childThree);
      delete curNode;
    }
    else{
      postorderDeletion(curNode->childOne);
      postorderDeletion(curNode->childTwo);
      postorderDeletion(curNode->childThree);
      postorderDeletion(curNode->childFour);
      delete curNode;
    }
  }

//Errors on this, needs to be fixed
  valuetype * search(keytype k){
    //cout << "Made it to search" << endl;
    Node<keytype, valuetype>* curNode = new Node<keytype, valuetype>;
    curNode = root; ///new node is where the root is, starting point
    //if statement spaghetti incoming
    while (curNode != NULL){ //while we aren't at a node that is nonexistant
    //cout << "Checking" << endl;

      if (curNode->nodeStatus == 2){
        //cout << "2 Node choices" << endl;
        if (k == curNode->firstKey) return &curNode->firstValue; //equals case
        else if (k < curNode->firstKey) curNode = curNode->childOne;
        else curNode = curNode->childTwo;
      } //end of Two Node Status

      else if (curNode->nodeStatus == 3){
        //cout << "3 Node choices" << endl;
        if (k == curNode->firstKey) return &curNode->firstValue;
        else if (k == curNode->secondKey) return &curNode->secondValue;
        if (k < curNode->firstKey) curNode = curNode->childOne;
        else if (k < curNode->secondKey) curNode = curNode->childTwo;
        else curNode = curNode->childThree; // if k > secondKey
      } //end of Three Node Status

      else{ //Four Node Status
        //cout << "4 Node choices" << endl;
        if (k == curNode->firstKey) return &curNode->firstValue;
        else if (k == curNode->secondKey) return &curNode->secondValue;
        else if (k == curNode->thirdKey) return &curNode->thirdValue;
        else if (k < curNode->firstKey) curNode = curNode->childOne;
        else if (k < curNode->secondKey) curNode = curNode->childTwo;
        else if (k < curNode->thirdKey) curNode = curNode->childThree;
        else curNode = curNode->childFour;
        /*
        else if (k == curNode->secondKey) return &curNode->secondValue;
        else if (k == curNode->thirdKey) return &curNode->thirdValue;
        //else if (k < curNode->firstKey) curNode = curNode->childOne;
        else if (k < curNode->secondKey) curNode = curNode->childTwo;
        else if (k < curNode->thirdKey) curNode = curNode->childThree;
        else curNode = curNode->childFour;
        */
      }//end of Four Node Status

      }
      return 0;
    }//end of function

  void insert(keytype k, valuetype v){
    //cout << "Inserting key: " << k << endl;
    Node<keytype, valuetype>* curNode = root; //navigator

    Node<keytype, valuetype>* insertNode = new Node<keytype, valuetype>; //for root case
    insertNode->parent = NULL;
    insertNode->childOne = NULL;
    insertNode->childTwo = NULL;
    insertNode->childThree = NULL;
    insertNode->childFour = NULL;

    if (root == NULL){ //there is nothing at all
      //cout << "Root Case" << endl;
      root = insertNode; //the root becomes this node
      insertNode->nodeStatus = 2; //setting it up
      insertNode->firstKey = k;
      insertNode->firstValue = v;
      //cout << "Success" << endl;
      //treeSize++; //since now the first node
      insertNode->keysHereUnder++;
      treeSize++;
      return;
    }
    //root check for 4 node
    if (curNode->nodeStatus == 4){
      //cout << "Root is a 4 Node. Must split" << endl;
      curNode = split(curNode);
    }

    //modified search to get to the leaves
    while (((curNode->childOne && curNode->childTwo) != NULL) || curNode->nodeStatus == 4){ //while we aren't at a leaf node

    //if (curNode->nodeStatus == 2) cout << "Current Node First Key: " << curNode->firstKey << " " << endl;
    //else if (curNode->nodeStatus == 3) cout << "Current Node First Key: " << curNode->firstKey << " " << "Second Key: " << curNode->secondKey << endl;
    //else cout << "Current Node First Key: " << curNode->firstKey << " " << "Second Key: " << curNode->secondKey << " Third Key: " << curNode->thirdKey <<endl;

    //cout << "Searching for leaf" << endl;
    curNode->keysHereUnder++;
      if(curNode->nodeStatus == 4){ //if we land on a 3 node, we have to split it
      //  cout << "Splitting a 4 node" << endl;
        curNode = split(curNode); //calls to split it. Returns the parent of node we split
      }

      //searching for next node to visit
      if (curNode->nodeStatus == 2){ //2 node case
      //  cout << "Two Node Case: Key in node is " << curNode->firstKey << endl;
        if (k <= curNode->firstKey){
        //  cout << "Less than or equal to first key" << endl;
          curNode = curNode->childOne;
        }
        else{
        //  cout << "Greater than first key" << endl;
          curNode = curNode->childTwo;
        }
      } //end of Two Node Status

      else if (curNode->nodeStatus == 3){ //3 node case
      //  cout << "Three Node Case: Keys in node are " << curNode->firstKey << " " << curNode->secondKey << endl;
        if (k <= curNode->firstKey) {
        //  cout << "Less than or equal to first key" << endl;
          curNode = curNode->childOne;
        }
        else if (k <= curNode->secondKey) {
        //cout << "Less than or equal to second key" << endl;
          curNode = curNode->childTwo;
        }
        else {
        //  cout << "Greater than second key" << endl;
          curNode = curNode->childThree; // if k > secondKey
        }
      } //end of Three Node Status

      else{ //we made a 4 node above us
        //cout << "Four Node Case" << endl;
        //cout << "Current Node First Key: " << curNode->firstKey << " " << "Second Key: " << curNode->secondKey << " Third Key: " << curNode->thirdKey <<endl;
        //cout << "Left: " << curNode->childOne->firstKey << "Middle Left: " << curNode->childTwo->firstKey << "Middle Right: " << curNode->childThree->firstKey << "Right: " << curNode->childFour->firstKey << endl;
        if (k <= curNode->firstKey) {
          //cout << "Less than or equal to first key" << endl;
          curNode = curNode->childOne;
        }
        else if (k <= curNode->secondKey) {
        //  cout << "Less than or equal to second key" << endl;
          curNode = curNode->childTwo;
        }
        else if (k <= curNode->thirdKey)  {
        //  cout << "Greater than second key" << endl;
          curNode = curNode->childThree; // if k > secondKey
        }
        else{ //greater than third key
          //cout << "Greater than third key" << endl;
          curNode = curNode->childFour;
        }
      }

    } //we are now at the node to insert into
      //we know that there are no chilren attached since the tree grows from the bottom pushing up

      /*if(curNode->nodeStatus == 4){ //if we land on a 3 node, we have to split it
        cout << "Splitting a 4 node" << endl;
        curNode = split(curNode); //calls to split it. Returns the parent of node we split
      }*/

    if (curNode->nodeStatus == 2){
        //cout << "Now doing 2 node insertion" << endl;
        if (k <= curNode->firstKey){ //less than the only key
          curNode->secondKey = curNode->firstKey; //move first to second
          curNode->secondValue = curNode->firstValue;

          curNode->firstKey = k; //move in the new data
          curNode->firstValue = v;
        }
        else{ //greater than the only key. No need to move anything, just expand.
          curNode->secondKey = k; //move in the new data
          curNode->secondValue = v;
        }
        curNode->nodeStatus = 3;
        //cout << "Node is now: " << curNode->firstKey << " " << curNode->secondKey << endl;
        curNode->keysHereUnder++;
        treeSize++;
        return;
      }

      else{ //so we are inserting into a 3 node
        //  cout << "Now doing 3 node insertion" << endl;
          //cout << curNode->nodeStatus << endl;
          if (k <= curNode->firstKey){ //less than the first key
            //  cout << "less than or equal to first key" << endl;
            curNode->thirdKey = curNode->secondKey; //move second to third
            curNode->thirdValue = curNode->secondValue;
            curNode->secondKey = curNode->firstKey; //move first to second
            curNode->secondValue = curNode->firstValue;

            curNode->firstKey = k; //move in the new data
            curNode->firstValue = v;
          }
          else if (k <= curNode->secondKey) { //less than the second key
           //cout << "less than or equal to second key" << endl;
            curNode->thirdKey = curNode->secondKey; //move second to third
            curNode->thirdValue = curNode->secondValue;

            curNode->secondKey = k; //move in the new data to open slot 2
            curNode->secondValue = v;
          }
          else{ //greater than the second key
          //  cout << "greater than second key" << endl;
            curNode->thirdKey = k; //move in the new data to open slot 3
            curNode->thirdValue = v;
          }
          curNode->nodeStatus = 4;
      //  cout << "Node is now: " << curNode->firstKey << " " << curNode->secondKey << " " << curNode->thirdKey << endl;
          curNode->keysHereUnder++;
          treeSize++;
          return;
        }
  }//end of insert

int remove(keytype k){
  Node<keytype, valuetype>* curNode = root;
  return removeRecursive(k, curNode);
}

int removeRecursive(keytype k, Node<keytype, valuetype>* curNode){
while (curNode != NULL){ //while we aren't at a non existant
//cout << "Hunting: " << k << endl;
//cout << "Current Stuff in the Node: ";
//if (curNode->nodeStatus == 2) cout << curNode->firstKey << endl;
//else if (curNode->nodeStatus == 3) cout << curNode->firstKey << " " << curNode->secondKey << endl;
//else cout << curNode->firstKey << " " << curNode->secondKey << " " << curNode->thirdKey << endl;

  if (curNode->childOne == NULL){ //if we have a leaf
  //check if we equal a leaf, the good situation
  //cout << "Leaf Removal" << endl;
  int result = removeLeaf(curNode, k);
  if (result == 1) treeSize--;
  return result;
   /*if ((curNode->nodeStatus == 3) && (curNode->childOne == NULL) && ((k == curNode->firstKey) || (k == curNode->secondKey))){
    removeLeaf(curNode, k);
    treeSize--;
    return 1;
  }
  else if ((curNode->nodeStatus == 4) && (curNode->childOne == NULL) && (k == (curNode->firstKey || curNode->secondKey || curNode->thirdKey))){
    removeLeaf(curNode, k);
    treeSize--;
    return 1;
  }*/
}//end of leaf case

  else if ((curNode->nodeStatus == 2 && (k == curNode->firstKey)) || (curNode->nodeStatus == 3 && ((k == curNode->firstKey) || (k == curNode->secondKey))) || (curNode->nodeStatus == 4 && ((k == curNode->firstKey) || (k == curNode->secondKey) || (k == curNode->thirdKey)))){
    //made this if statement very rigorous because of fear of a bug
    //since I can't necessarily delete an int in the node on a removal of stuff from the right, so I need to verify node type too
  //else if (curNode->childOne != NULL){ //we are an internal node, check node type
    //cout << "Internal Node" << endl;
    if (curNode->nodeStatus == 2){//2 node case, check if k is in the node
      //cout << "Internal: 2 Node Case" << endl;
      if (curNode->firstKey == k){//we are the internal node
        //cout << "Internal: 2 Node Case: We equal the internal" << endl;
        if (curNode->childOne->nodeStatus >= 3){ //if it has a spare node
          //cout << "Internal: 2 Node Case: Left Child has a spare" << endl;
          Node<keytype, valuetype>* pred = getPredecessor(curNode->childOne);
          keytype predKey = getPredKey(pred); //gets the predecessor key
          valuetype predValue = getPredValue(pred);
          curNode->firstKey = predKey;
          curNode->firstValue = predValue;
          return removeRecursive(predKey, curNode->childOne);
          //return 1;
        }
        else if (curNode->childTwo->nodeStatus >= 3){ //if it has a spare node
          //cout << "Internal: 2 Node Case: Right Child has a spare" << endl;
          Node<keytype, valuetype>* succ = getSuccessor(curNode->childTwo);
          //keytype succKey = successor(k); //gets the successor key
          //valuetype succValue = selectValue(rank(k) + 1);
          curNode->firstKey = succ->firstKey;
          curNode->firstValue = succ->firstValue;
          return removeRecursive(succ->firstKey, curNode->childTwo);
          //return 1;
        }
        else{ //merge case
          //cout << "Internal: 2 Node Case: Merge" << endl;
          curNode = merge(curNode, k);
          return removeRecursive(k, curNode); //since we made a new node in this case
          //return 1;
        }
      }
    }//end of 2 Node case

    else if (curNode->nodeStatus == 3){//3 node case, check if k is in the node
      //cout << "Internal: 3 Node Case" << endl;
      if (curNode->firstKey == k){//we are the first key
        //cout << "Internal: 3 Node Case: We equal the first key" << endl;
        if (curNode->childOne->nodeStatus >= 3){ //if child one has a spare node
          //cout << "Internal: 3 Node Case: First Key: Left Child has a spare" << endl;
          Node<keytype, valuetype>* pred = getPredecessor(curNode->childOne);
          keytype predKey = getPredKey(pred);
          valuetype predValue = getPredValue(pred);
          curNode->firstKey = predKey;
          curNode->firstValue = predValue;
          return removeRecursive(predKey, curNode->childOne);
          //return 1;
        }
        else if (curNode->childTwo->nodeStatus >= 3){ //if child two has a spare node
          //cout << "Internal: 3 Node Case: First Key: Middle Child has a spare" << endl;
          Node<keytype, valuetype>* succ = getSuccessor(curNode->childTwo);
          //keytype succKey = successor(k); //gets the successor key
          //valuetype succValue = selectValue(rank(k) + 1);
          curNode->firstKey = succ->firstKey;
          curNode->firstValue = succ->firstValue;
          return removeRecursive(succ->firstKey, curNode->childTwo);
          //return 1;
        }
        else{
        //cout << "Internal: 3 Node Case: First Key: Merge" << endl;
        curNode = merge(curNode, k);
        return removeRecursive(k, curNode->childOne); //was going to child One
        //return 1;
        }
      }//end of first key case
      if (curNode->secondKey == k){//we are the second key
        //cout << "Internal: 3 Node Case: We equal the second key" << endl;
        if (curNode->childTwo->nodeStatus >= 3){ //if child two has a spare node
          //cout << "Internal: 3 Node Case: Second Key: Left Child has a spare" << endl;
          Node<keytype, valuetype>* pred = getPredecessor(curNode->childTwo);
          keytype predKey = getPredKey(pred);
          valuetype predValue = getPredValue(pred);
          curNode->secondKey = predKey;
          curNode->secondValue = predValue;
          return removeRecursive(predKey, curNode->childTwo);
          //return 1;
        }
        else if (curNode->childThree->nodeStatus >= 3){ //if child three has a spare node
          //cout << "Internal: 3 Node Case: Second Key: Right Child has a spare" << endl;
          Node<keytype, valuetype>* succ = getSuccessor(curNode->childThree);
          //keytype succKey = successor(k); //gets the successor key
          //valuetype succValue = selectValue(rank(k) + 1);
          curNode->secondKey = succ->firstKey;
          curNode->secondValue = succ->firstValue;
          return removeRecursive(succ->firstKey, curNode->childThree);
          //return 1;
        }
        else{
          //cout << "Internal: 3 Node Case: Second Key: Merge" << endl;
          curNode = merge(curNode, k);
          return removeRecursive(k, curNode->childTwo);
          //return 1;
        }
      }//end of second key case
    }//end of 3 node case

    else if (curNode->nodeStatus == 4){//4 node case, check if k is in the node
      //cout << "Internal: 4 Node Case" << endl;
      if (curNode->firstKey == k){//we are the first key
        //cout << "Internal: 4 Node Case: We equal the first key" << endl;
        if (curNode->childOne->nodeStatus >= 3){ //if child one has a spare node
          //cout << "Internal: 4 Node Case: First Key: Left Child has a spare" << endl;
          Node<keytype, valuetype>* pred = getPredecessor(curNode->childOne);
          keytype predKey = getPredKey(pred);
          valuetype predValue = getPredValue(pred);
          curNode->firstKey = predKey;
          curNode->firstValue = predValue;
          return removeRecursive(predKey, curNode->childOne);
          //return 1;
        }
        else if (curNode->childTwo->nodeStatus >= 3){ //if child two has a spare node
          //cout << "Internal: 4 Node Case: First Key: Right Child has a spare" << endl;
          Node<keytype, valuetype>* succ = getSuccessor(curNode->childTwo);
          //keytype succKey = successor(k); //gets the successor key
          //valuetype succValue = selectValue(rank(k) + 1);
          curNode->firstKey = succ->firstKey;
          curNode->firstValue = succ->firstValue;
          return removeRecursive(succ->firstKey, curNode->childTwo);
          //return 1;
        }
        else{
          //cout << "Internal: 4 Node Case: First Key: Merge" << endl;
          curNode = merge(curNode, k);
          return removeRecursive(k, curNode->childOne);
          //return 1;
        }
      }//end of first key case
      if (curNode->secondKey == k){//we are the second key
        //cout << "Internal: 4 Node Case: We equal the second key" << endl;
        if (curNode->childTwo->nodeStatus >= 3){ //if child two has a spare node
          //cout << "Internal: 4 Node Case: Second Key: Left Child has a spare" << endl;
          Node<keytype, valuetype>* pred = getPredecessor(curNode->childTwo);
          keytype predKey = getPredKey(pred);
          valuetype predValue = getPredValue(pred);
          curNode->secondKey = predKey;
          curNode->secondValue = predValue;
          return removeRecursive(predKey, curNode->childTwo);
          //return 1;
        }
        else if (curNode->childThree->nodeStatus >= 3){ //if child three has a spare node
          //cout << "Internal: 4 Node Case: Second Key: Right Child has a spare" << endl;
          Node<keytype, valuetype>* succ = getSuccessor(curNode->childThree);
          //keytype succKey = successor(k); //gets the successor key
          //valuetype succValue = selectValue(rank(k) + 1);
          curNode->secondKey = succ->firstKey;
          curNode->secondValue = succ->firstValue;
          return removeRecursive(succ->firstKey, curNode->childThree);
          //return 1;
        }
        else{
          //cout << "Internal: 4 Node Case: Second Key: Merge" << endl;
          curNode = merge(curNode, k);
          return removeRecursive(k, curNode->childTwo);
          //return 1;
        }
      }//end of second key case
      if (curNode->thirdKey == k){//we are the third key
        //cout << "Internal: 4 Node Case: We equal the third key" << endl;
        if (curNode->childThree->nodeStatus >= 3){ //if child three has a spare node
          //cout << "Internal: 4 Node Case: Third Key: Left Child has a spare" << endl;
          Node<keytype, valuetype>* pred = getPredecessor(curNode->childThree);
          keytype predKey = getPredKey(pred);
          valuetype predValue = getPredValue(pred);
          curNode->thirdKey = predKey;
          curNode->thirdValue = predValue;
          return removeRecursive(predKey, curNode->childThree);
          //return 1;
        }
        else if (curNode->childFour->nodeStatus >= 3){ //if child four has a spare node
          //cout << "Internal: 4 Node Case: Third Key: Right Child has a spare" << endl;
          Node<keytype, valuetype>* succ = getSuccessor(curNode->childFour);
          //keytype succKey = successor(k); //gets the successor key
          //valuetype succValue = selectValue(rank(k) + 1);
          curNode->thirdKey = succ->firstKey;
          curNode->thirdValue = succ->firstValue;
          return removeRecursive(succ->firstKey, curNode->childFour);
          //return 1;
        }
        else{
          //cout << "Internal: 4 Node Case: Third Key: Merge" << endl;
          curNode = merge(curNode, k);
          return removeRecursive(k, curNode->childThree);
          //return 1;
        }
      }//end of third key case
    }//end of 4 node case
  }//end of internal node case

  else{ //k is not in the internal node
    //cout << "Not in the internal node" << endl;
    Node<keytype, valuetype>* target = new Node <keytype, valuetype>;
    //searching for next node to visit
    //could make this section a function since used so often
    if (curNode->nodeStatus == 2){ //2 node case
      //cout << " 2 Node Search" << endl;
      if (k <= curNode->firstKey){
        //cout << "   Go left" << endl;
        target = curNode->childOne; //go left
      }
      else{
        //cout << "   Go right" << endl;
        target = curNode->childTwo; //go right
      }
    } //end of Two Node Status

    else if (curNode->nodeStatus == 3){ //3 node case
      //cout << " 3 Node Search" << endl;
      if (k <= curNode->firstKey) {
        //cout << "   Go left" << endl;
        target = curNode->childOne; //go left
      }
      else if (k <= curNode->secondKey) {
        //cout << "   Go middle" << endl;
        target = curNode->childTwo; //go middle
      }
      else {
        //cout << "   Go right" << endl;
        target = curNode->childThree; //go right
      }
    } //end of Three Node Status

    else{ //we made a 4 node above us
      //cout << " 4 Node Search" << endl;
      if (k <= curNode->firstKey) {
        //cout << "   Go left" << endl;
        target = curNode->childOne; //go left
      }
      else if (k <= curNode->secondKey) {
        //cout << "   Go middle left" << endl;
        target = curNode->childTwo; //go middle left
      }
      else if (k <= curNode->thirdKey)  {
        //cout << "   Go middle right" << endl;
        target = curNode->childThree; //go middle right
      }
      else{ //greater than third key
        //cout << "   Go right" << endl;
        target = curNode->childFour; //go right
      }
    }
    //now have our destination
    if (target->nodeStatus == 2){ //if we are about to hit a 2 node
      //cout << "About to hit a 2 Node" << endl;
      if (curNode->nodeStatus == 2){ //if we are already a two node
        //cout << " Currently a 2 Node" << endl;
        if (target == curNode->childOne){//we are the left of the parent
          //cout << "   Target is left of parent" << endl;
          if (curNode->childTwo->nodeStatus >= 3){ //if sibling is a 3+ node
            //cout <<"      Right Sibling has an extra"<< endl;
            rotateLeft(curNode->childOne, curNode->childTwo, &curNode->firstKey, &curNode->firstValue);
          }
          else{
            //cout << "     Must merge" << endl;
            target = merge(curNode, curNode->firstKey); // fill in
          }
        } //end of left of parent 2 Node
        else{//we are right of parent
            //cout << "   Target is right of parent" << endl;
            if (curNode->childOne->nodeStatus >= 3){
              //cout <<"      Left Sibling has an extra"<< endl;
              rotateRight(curNode->childOne, curNode->childTwo, &curNode->firstKey, &curNode->firstValue); //fill in
            }
            else{
              //cout << "     Must merge" << endl;
              //cout << "curNode first key: " << curNode->firstKey << endl;
               target = merge(curNode, curNode->firstKey); //this is the preemptive merge iirc
            }
        }//end of right of parent 2 node
      }
      else if (curNode->nodeStatus == 3){ //if we are currently a 3 node
        //cout << " Currently a 3 Node" << endl;
        if (target == curNode->childOne){ //left of parent
          //cout << "   Target is left of parent" << endl;
          if (curNode->childTwo->nodeStatus >= 3){ //if sibling is 3+ node
            //cout <<"      Right Sibling has an extra"<< endl;
            rotateLeft(curNode->childOne, curNode->childTwo, &curNode->firstKey, &curNode->firstValue);
          }
          else{
            //cout << "     Must merge" << endl;
            target = merge(curNode, curNode->firstKey);
          }
        }
        else if (target == curNode->childTwo){ //we are middle child
          //cout << "   Target is middle of parent" << endl;
          /*if (curNode->childOne->nodeStatus >= 3){ //left sibling 3+
            cout <<"      Left Sibling has an extra"<< endl;
            rotateRight(curNode->childOne, curNode->childTwo, &curNode->firstKey, &curNode->firstValue);
          }*/
           if (curNode->childThree->nodeStatus >= 3){ //right sibling is 3+
            //cout <<"      Right Sibling has an extra"<< endl;
            rotateLeft(curNode->childTwo, curNode->childThree, &curNode->secondKey, &curNode->secondValue);
          }
          else{
            //cout << "     Must merge" << endl;
            target = merge(curNode, curNode->secondKey);
          }
        }
        else{ //we are rightmost child
          //cout << "   Target is right of parent" << endl;
          if (curNode->childTwo->nodeStatus >= 3){ //left sibling is 3+
            //cout <<"      Left Sibling has an extra"<< endl;
            rotateRight(curNode->childTwo, curNode->childThree, &curNode->secondKey, &curNode->secondValue);
          }
          else{
            //cout << "     Must merge" << endl;
            target = merge(curNode, curNode->secondKey);
          }
        }
      }//end of 3 Node parent case

      else{ //we are a 4 node
        //cout << " Currently a 4 Node" << endl;
        if (target == curNode->childOne){//leftmost
          //cout << "   Target is left of parent" << endl;
          if (curNode->childTwo->nodeStatus >= 3){ //sibling is 3+
            //cout <<"      Right Sibling has an extra"<< endl;
            rotateLeft(curNode->childOne, curNode->childTwo, &curNode->firstKey, &curNode->firstValue);
          }
          else{
            //cout << "     Must merge" << endl;
            target = merge(curNode, curNode->firstKey);
          }
        }
        else if (target == curNode->childTwo){ //middle left
          //cout << "   Target is  middle left of parent" << endl;
          /*if (curNode->childOne->nodeStatus >= 3){
            cout <<"      Left Sibling has an extra"<< endl;
            rotateRight(curNode->childOne, curNode->childTwo, &curNode->firstKey, &curNode->firstValue);
          }*/
           if (curNode->childThree->nodeStatus >= 3){
            //cout <<"      Right Sibling has an extra"<< endl;
            rotateLeft(curNode->childTwo, curNode->childThree, &curNode->secondKey, &curNode->secondValue);
          }
          else{
            //cout << "     Must merge" << endl;
            target = merge(curNode, curNode->secondKey);
          }
        }
        else if (target == curNode->childThree){ //middle right
          //cout << "   Target is middle right of parent" << endl;
          /*if (curNode->childTwo->nodeStatus >= 3){
            cout <<"      Left Sibling has an extra"<< endl;
            rotateRight(curNode->childTwo, curNode->childThree, &curNode->secondKey, &curNode->secondValue);
          }*/
           if (curNode->childFour->nodeStatus >= 3){
            //cout <<"      Right Sibling has an extra"<< endl;
            rotateLeft(curNode->childThree, curNode->childFour, &curNode->thirdKey, &curNode->thirdValue);
          }
          else{
            //cout << "     Must merge" << endl;
            target = merge(curNode, curNode->thirdKey);
          }
        }
        else{ //right most child
          //cout << "   Target is right of parent" << endl;
          if (curNode->childThree->nodeStatus >= 3){ //left sibling is 3+
            //cout <<"      Left Sibling has an extra"<< endl;
            rotateRight(curNode->childThree, curNode->childFour, &curNode->thirdKey, &curNode->thirdValue);
          }
          else{
            //cout << "     Must merge" << endl;
            target = merge(curNode, curNode->thirdKey);
          }
        } //end of right most child
      }//end of 4 node case
      //can now safely go to the target and have it not be a 2 node
      //cout << "Going to: " << target->firstKey << endl;
      curNode = target;
    } //end of about to hit a 2 node
    else{ //node isn't a 2 node, don't do anything
      //cout <<"It is not a 2 Node" << endl;
      curNode = target; //now we are the target
    }
  }//end of not there yet
}// end of while loop
return 0; //must not exist, has been completely checked for
}//end of removeRecursive

void fixCounts(Node<keytype, valuetype>* travelNode){//go back up the tree, fix key counts
  while (travelNode != 0){ //while we aren't invalid
    travelNode->keysHereUnder--; //subtract 1 since we go up the path we came from
    travelNode = travelNode->parent; //go to parent
  }
}//end of fixCounts

Node<keytype, valuetype>* getSuccessor(Node<keytype, valuetype>* firstRight){
  //given the node to the right of the current key, go find the successor of current key
  //get to the left most child
  while (firstRight->childOne != 0){
    firstRight = firstRight->childOne;
  }
  return firstRight;
}

Node<keytype, valuetype>* getPredecessor(Node<keytype, valuetype>* firstLeft){
  //given the node to the left of the current key, go find the successor of current key
  //get to the right most child
  while (firstLeft->childOne != 0){
    if (firstLeft->nodeStatus == 2){
      firstLeft = firstLeft->childTwo;
    }
    else if (firstLeft->nodeStatus == 3){
      firstLeft = firstLeft->childThree;
    }
    else{
      firstLeft = firstLeft->childFour;
    }
  }
  return firstLeft;
}//end of getPredecessor

keytype getPredKey (Node<keytype, valuetype>* predNode){ //gets the key from pred since there are cases
  if (predNode->nodeStatus == 2){
    return predNode->firstKey;
  }
  else if (predNode->nodeStatus == 3){
    return predNode->secondKey;
  }
  else{
    return predNode->thirdKey;
  }
} //end of getPredKey

valuetype getPredValue (Node<keytype, valuetype>* predNode){ //gets the key from pred since there are cases
  if (predNode->nodeStatus == 2){
    return predNode->firstValue;
  }
  else if (predNode->nodeStatus == 3){
    return predNode->secondValue;
  }
  else{
    return predNode->thirdValue;
  }
} //end of getPredValue

void rotateLeft(Node <keytype, valuetype>* left, Node <keytype, valuetype>* right, keytype *keyAddress, valuetype *valAddress){
  //we need to steal from a sibling on the right
  left->secondKey = *keyAddress; //gets the parent key
  left->secondValue = *valAddress; //gets the parent value

  if (right->childOne != 0){
    right->keysHereUnder = (right->keysHereUnder - 1) - right->childOne->keysHereUnder; //-1 since we just took a parent key away
  }
  else{
    right->keysHereUnder = right->keysHereUnder - 1;
  }

  left->childThree = right->childOne; //takes siblings first child
  //left->childThree->parent = left;
  left->nodeStatus = 3; //becomes 3 since always a 2

  if (left->childThree != 0){
    left->childThree->parent = left;
    left->keysHereUnder = (left->keysHereUnder + 1) + left->childThree->keysHereUnder; //+1 since we added a key
  }
  else{
    left->keysHereUnder = left->keysHereUnder + 1;
  }

  //now fix the parent
  *keyAddress = right->firstKey;
  *valAddress = right->firstValue;

  //now fix the sibling
  //right->nodeStatus = right->nodeStatus - 1; //since it could be a 3 or 4
  //now move everything left 1 since we took from the left
  //may cause seg fault, so could require cases per node type

  //wrote cases because looking for bugs, need to be exact
  if (right->nodeStatus == 3){
    right->childOne = right->childTwo;
    right->childTwo = right->childThree;
    right->childThree = NULL;

    right->firstKey = right->secondKey;
    right->firstValue = right->secondValue;
    right->nodeStatus = 2;
  }

  else{ //4 node case
    right->childOne = right->childTwo;
    right->childTwo = right->childThree;
    right->childThree = right->childFour;
    right->childFour = NULL; //added this in

    right->firstKey = right->secondKey;
    right->secondKey = right->thirdKey;
    right->firstValue = right->secondValue;
    right->secondValue = right->thirdValue;
    right->nodeStatus = 3;
  }
  /*
  right->childOne = right->childTwo;
  right->childTwo = right->childThree;
  right->childThree = right->childFour;
  right->childFour = NULL; //added this in

  right->firstKey = right->secondKey;
  right->secondKey = right->thirdKey;
  right->firstValue = right->secondValue;
  right->secondValue = right->thirdValue;
  */
  //right->nodeStatus = right->nodeStatus - 1; //since it could be a 3 or 4
}//end of rotateLeft

void rotateRight(Node <keytype, valuetype>* left, Node <keytype, valuetype>* right, keytype *keyAddress, valuetype *valAddress){
  //we need to steal from a sibling on the left
  //need to scoot everything down one
  //move children down 1
  //cout << "In rotate right" << endl;
  right->childFour = right->childThree;
  right->childThree = right->childTwo;
  right->childTwo = right->childOne;
  //move key/values down 1
  right->secondKey = right->firstKey;
  right->secondValue = right->firstValue;

  right->nodeStatus = 3; //we now have a 3 node
  right->firstKey = *keyAddress; //gets the parent key
  right->firstValue = *valAddress; //gets the parent value
  //somes cases depending on sibling node type
  if (left->nodeStatus == 3){ //if sibling is a 3
    //cout << "3 Node Sibling" << endl;
    //cout << left->childThree->keysHereUnder << endl;
    if (left->childThree != 0){
      left->keysHereUnder = (left->keysHereUnder - 1) - (left->childThree->keysHereUnder); //-1 since losing a parent key, subtract branch we take away
    }
    else{
      left->keysHereUnder = left->keysHereUnder - 1;
    }

    //cout << "This far 1" << endl;
    *keyAddress = left->secondKey;
    *valAddress = left->secondValue;
    //before taking key, update key counts
    //cout << "This far 2" << endl;
    right->childOne = left->childThree;
    //right->childOne->parent = right;

    if (right->childOne != 0){
      //cout << "This far 3.1" << endl;
      right->childOne->parent = right;
      right->keysHereUnder = right->keysHereUnder + 1 + right->childOne->keysHereUnder; //+1 for extra node, then add the new branch
    }
    else{
      //cout << "This far 3.2" << endl;
      right->keysHereUnder = right->keysHereUnder + 1;
    }
    left->childThree = NULL;
  }//end of sibling 3 node case

  else{ //if a 4 node
    //cout << "4 Node Sibling" << endl;
    if (left->childFour != 0){
      left->keysHereUnder = (left->keysHereUnder - 1) - (left->childFour->keysHereUnder); //-1 since losing a parent key, subtract branch we take away
    }
    else{
      left->keysHereUnder = left->keysHereUnder - 1;
    }
    *keyAddress = left->thirdKey;
    *valAddress = left->thirdValue;
    right->childOne = left->childFour;
    //right->childOne->parent = right;
    if (right->childOne != 0){
      right->childOne->parent = right;
      right->keysHereUnder = right->keysHereUnder + 1 + right->childOne->keysHereUnder; //+1 for extra node, then add the new branch
    }
    else{
      right->keysHereUnder = right->keysHereUnder + 1;
    }
    left->childFour = NULL;
  }//end of sibling 4 node case

  //cout << "Survivded rotateRight" << endl;
  left->nodeStatus = (left->nodeStatus) - 1; //decrement by 1
}

Node<keytype, valuetype>* merge(Node<keytype, valuetype>* mergeNode, keytype k){
  //we have the parent and the key, can use as selectors to save some effort
  //cout <<"In Merge Helper"<< endl;
  if (mergeNode->nodeStatus == 2){
    //cout <<"  2 Node Case"<< endl;
    Node<keytype, valuetype>* newNode = new Node <keytype, valuetype>;
    newNode->parent = mergeNode->parent; //same parent
    newNode->nodeStatus = 4; //has 3 keys
    //set the newNode back to the parent somehow
    if (newNode->parent != NULL){
    if (mergeNode->parent->childOne == mergeNode) newNode->parent->childOne = newNode;
    else if (mergeNode->parent->childTwo == mergeNode) newNode->parent->childTwo = newNode;
    else if (mergeNode->parent->childThree == mergeNode) newNode->parent->childThree = newNode;
    else newNode->parent->childFour = newNode;
  }

    newNode->firstKey = mergeNode->childOne->firstKey;
    newNode->firstValue = mergeNode->childOne->firstValue;
    newNode->secondKey = mergeNode->firstKey;
    newNode->secondValue = mergeNode->firstValue;
    newNode->thirdKey = mergeNode->childTwo->firstKey;
    newNode->thirdValue = mergeNode->childTwo->firstValue;

    newNode->childOne = mergeNode->childOne->childOne;
    newNode->childTwo = mergeNode->childOne->childTwo;
    newNode->childThree = mergeNode->childTwo->childOne;
    newNode->childFour = mergeNode->childTwo->childTwo;

    if ((newNode->childOne && newNode->childTwo) != NULL){ //if they exist
      newNode->childOne->parent = newNode;
      newNode->childTwo->parent = newNode;
      newNode->childThree->parent = newNode;
      newNode->childFour->parent = newNode;
  }

  newNode->keysHereUnder = mergeNode->childOne->keysHereUnder + mergeNode->childTwo->keysHereUnder + 1; //+1 for self
delete mergeNode->childOne;
delete mergeNode->childTwo;
if (mergeNode == root){
  root = newNode;
}
delete mergeNode; //last because needed to remove kids
//cout <<"    First Key: " << newNode->firstKey << " Second Key: " << newNode->secondKey << " Third Key: " << newNode->thirdKey << endl;
return newNode;
}// end of 2 node case

  else if (mergeNode->nodeStatus == 3){ //3 node case, 2 possible merges
    //cout <<"  3 Node Case"<< endl;
    if (k == mergeNode->firstKey){ //equals the first key
      //cout <<"    First Key Case"<< endl;
      mergeNode->childOne->keysHereUnder = mergeNode->childOne->keysHereUnder + mergeNode->childTwo->keysHereUnder + 1; //+1 for self coming down
      mergeNode->childOne->nodeStatus = 4;
      mergeNode->childOne->secondKey = mergeNode->firstKey;
      mergeNode->childOne->secondValue = mergeNode->firstValue;
      mergeNode->childOne->thirdKey = mergeNode->childTwo->firstKey;
      mergeNode->childOne->thirdValue = mergeNode->childTwo->firstValue;

      mergeNode->childOne->childThree = mergeNode->childTwo->childOne; //move the children over
      mergeNode->childOne->childFour = mergeNode->childTwo->childTwo;

      if ((mergeNode->childTwo->childOne && mergeNode->childTwo->childTwo) != 0){ //was NULL
      mergeNode->childTwo->childOne->parent = mergeNode->childOne; //let children know who the new parent is
      mergeNode->childTwo->childTwo->parent = mergeNode->childOne;
    }
      //move stuff over

      mergeNode->firstKey = mergeNode->secondKey;
      mergeNode->firstValue = mergeNode->secondValue;
      delete mergeNode->childTwo; //already copied the data
      mergeNode->childTwo = mergeNode->childThree; //move in the new child pointer
      mergeNode->childThree = NULL; //safety measure
      mergeNode->nodeStatus = 2;
      return mergeNode;
    } //end of first key

    else{ //equals second key
      //cout <<"    Second Key Case" << endl;
      mergeNode->childTwo->keysHereUnder = mergeNode->childTwo->keysHereUnder + mergeNode->childThree->keysHereUnder + 1; //+1 for self coming down
      mergeNode->childTwo->nodeStatus = 4;
      mergeNode->childTwo->secondKey = mergeNode->secondKey;
      mergeNode->childTwo->secondValue = mergeNode->secondValue;
      mergeNode->childTwo->thirdKey = mergeNode->childThree->firstKey;
      mergeNode->childTwo->thirdValue = mergeNode->childThree->firstValue;

      mergeNode->childTwo->childThree = mergeNode->childThree->childOne; //move the children over
      mergeNode->childTwo->childFour = mergeNode->childThree->childTwo;

      if ((mergeNode->childThree->childOne && mergeNode->childThree->childTwo) != NULL){
      mergeNode->childThree->childOne->parent = mergeNode->childTwo; //let children know who the new parent is
      mergeNode->childThree->childTwo->parent = mergeNode->childTwo;
    }
      //move stuff over
      delete mergeNode->childThree; //already copied the data
      mergeNode->nodeStatus = 2;
      return mergeNode;
    } //end of second key
  }// end of 3 node case

  else{ //4 node case, 3 possible merges
    //cout <<"  4 Node Case" << endl;
    if (k == mergeNode->firstKey){ //equals the first key
      //cout <<"    First Key Case"<< endl;
      mergeNode->childOne->keysHereUnder = mergeNode->childOne->keysHereUnder + mergeNode->childTwo->keysHereUnder + 1; //+1 for self coming down
      mergeNode->childOne->nodeStatus = 4;
      mergeNode->childOne->secondKey = mergeNode->firstKey;
      mergeNode->childOne->secondValue = mergeNode->firstValue;
      mergeNode->childOne->thirdKey = mergeNode->childTwo->firstKey;
      mergeNode->childOne->thirdValue = mergeNode->childTwo->firstValue;

      mergeNode->childOne->childThree = mergeNode->childTwo->childOne; //move the children over
      mergeNode->childOne->childFour = mergeNode->childTwo->childTwo;

      if ((mergeNode->childTwo->childOne && mergeNode->childTwo->childTwo) != NULL){
      mergeNode->childTwo->childOne->parent = mergeNode->childOne; //let children know who the new parent is
      mergeNode->childTwo->childTwo->parent = mergeNode->childOne;
    }

      //move stuff over
      mergeNode->firstKey = mergeNode->secondKey;
      mergeNode->firstValue = mergeNode->secondValue;
      mergeNode->secondKey = mergeNode->thirdKey;
      mergeNode->secondValue = mergeNode->thirdValue;
      delete mergeNode->childTwo; //already copied the data
      mergeNode->childTwo = mergeNode->childThree; //move in the new child pointer
      mergeNode->childThree = mergeNode->childFour;
      mergeNode->childFour = NULL; //safety measure
      mergeNode->nodeStatus = 3;
      return mergeNode;
    } //end of first key

    else if (k == mergeNode->secondKey){ //equals second key
      //cout <<"    Second Key Case"<< endl;
      mergeNode->childTwo->keysHereUnder = mergeNode->childTwo->keysHereUnder + mergeNode->childThree->keysHereUnder + 1; //+1 for self coming down
      mergeNode->childTwo->nodeStatus = 4;
      mergeNode->childTwo->secondKey = mergeNode->secondKey;
      mergeNode->childTwo->secondValue = mergeNode->secondValue;
      mergeNode->childTwo->thirdKey = mergeNode->childThree->firstKey;
      mergeNode->childTwo->thirdValue = mergeNode->childThree->firstValue;

      mergeNode->childTwo->childThree = mergeNode->childThree->childOne; //move the children over
      mergeNode->childTwo->childFour = mergeNode->childThree->childTwo;

      if ((mergeNode->childThree->childOne && mergeNode->childThree->childTwo) != NULL){
      mergeNode->childThree->childOne->parent = mergeNode->childTwo; //let children know who the new parent is
      mergeNode->childThree->childTwo->parent = mergeNode->childTwo;
    }
      //move stuff over
      mergeNode->secondKey = mergeNode->thirdKey;
      mergeNode->secondValue = mergeNode->thirdValue;
      delete mergeNode->childThree; //already copied the data
      mergeNode->childThree = mergeNode->childFour;
      mergeNode->childFour = NULL; //safety measure
      mergeNode->nodeStatus = 3;
      return mergeNode;
    } //end of second key

    else{ //equals third key
      //cout <<"    Third Key Case"<< endl;
      mergeNode->childThree->keysHereUnder = mergeNode->childThree->keysHereUnder + mergeNode->childFour->keysHereUnder + 1; //+1 for self coming down
      mergeNode->childThree->nodeStatus = 4;
      mergeNode->childThree->secondKey = mergeNode->thirdKey;
      mergeNode->childThree->secondValue = mergeNode->thirdValue;
      mergeNode->childThree->thirdKey = mergeNode->childFour->firstKey;
      mergeNode->childTwo->thirdValue = mergeNode->childFour->firstValue;

      mergeNode->childThree->childThree = mergeNode->childFour->childOne; //move the children over
      mergeNode->childThree->childFour = mergeNode->childFour->childTwo;

      if ((mergeNode->childFour->childOne && mergeNode->childFour->childTwo) != NULL){
      mergeNode->childFour->childOne->parent = mergeNode->childThree; //let children know who the new parent is
      mergeNode->childFour->childTwo->parent = mergeNode->childThree;
    }
      //move stuff over
      delete mergeNode->childFour; //already copied the data
      mergeNode->nodeStatus = 3;
      return mergeNode;
    } //end of third key
  }//end of 4 Node case
}//end of merge

  int removeLeaf (Node<keytype, valuetype>* leaf, keytype k){
    //can't be a two node since we would have rotated or merged already
    if (leaf->nodeStatus == 3){ //three node cases
      if  (k == leaf->firstKey){ //remove the first key
        leaf->nodeStatus = 2; //make a 2 node
        leaf->firstKey = leaf->secondKey;
        leaf->firstValue = leaf->secondValue;
      }
      else if (k == leaf->secondKey){ //remove second key
        leaf->nodeStatus = 2; //no need to touch key 2, will be overwritten
      }
      else{
        return 0;
      }
    }//end of 3 node case

    else if (leaf->nodeStatus == 4){ //4 node case
      if (k == leaf->firstKey){ //removing first key
        leaf->nodeStatus = 3; //make a 3 node
        leaf->firstKey = leaf->secondKey;
        leaf->firstValue = leaf->secondValue;
        leaf->secondKey = leaf->thirdKey;
        leaf->secondValue = leaf->thirdValue;
      }
      else if (k == leaf->secondKey){ //removing second key
        leaf->nodeStatus = 3; //make a 3 node
        leaf->secondKey = leaf->thirdKey;
        leaf->secondValue = leaf->thirdValue;
      }
      else if (k == leaf->thirdKey){ //removing third key
        leaf->nodeStatus = 3; //no need to touch key 3, will be overwritten
      }
      else{
        return 0;
      }
    }//end of 4 node case
    else{ //if a single item
      if (leaf == root){
        //cout << "leaf is root" << endl;
        delete leaf;
        root = NULL;
        return 1;
      }
      else{
        return 0;
      }
    }//end of root case
    fixCounts(leaf);
    return 1;
  }//end of removeleaf

  int rank(keytype k){
    Node<keytype, valuetype>* curNode = new Node<keytype, valuetype>;
    curNode = root; ///new node is where the root is, starting point
    int total = 0;
    //cout << "Searching for: " << k << endl;
    //if statement spaghetti incoming
    while ((curNode->childOne && curNode->childTwo) != NULL){ //while we aren't at a node that is nonexistant
  //  cout << "Checking: " << curNode->firstKey << endl;

      if (curNode->nodeStatus == 2){
        //cout << "2 Node choices" << endl;
        if (k == curNode->firstKey) return (total + curNode->childOne->keysHereUnder + 1); //done
        else if (k < curNode->firstKey){ //if less than only key, go left
            //cout << "Go left" << endl;
            curNode = curNode->childOne; //going left
        }
        else{
            //cout << "Go right" << endl;
            total = total + curNode->childOne->keysHereUnder + 1;
            curNode = curNode->childTwo;
        }
      } //end of Two Node Status

      else if (curNode->nodeStatus == 3){
        //cout << "3 Node choices" << endl;
        if (k == curNode->firstKey) return (total + curNode->childOne->keysHereUnder + 1);
        else if (k == curNode->secondKey) return (total + curNode->childOne->keysHereUnder + curNode->childTwo->keysHereUnder + 2);
        else if (k < curNode->firstKey){
          //cout << "Go left" << endl;
          curNode = curNode->childOne;
        }
        else if (k < curNode->secondKey){
          total = total + curNode->childOne->keysHereUnder + 1;
          curNode = curNode->childTwo;
          //cout << "Go middle" << endl;
        }
        else{
          total = total + curNode->childOne->keysHereUnder + curNode->childTwo->keysHereUnder + 2;
          curNode = curNode->childThree; // if k > secondKey
          //cout << "Go right" << endl;
        }
      } //end of Three Node Status

      else{ //Four Node Status
        //cout << "4 Node choices" << endl;
        if (k == curNode->firstKey) return (total + curNode->childOne->keysHereUnder + 1);
        else if (k == curNode->secondKey) return (total + curNode->childOne->keysHereUnder + curNode->childTwo->keysHereUnder + 2);
        else if (k == curNode->thirdKey) return (total + curNode->childOne->keysHereUnder + curNode->childTwo->keysHereUnder + curNode->childThree->keysHereUnder + 3);
        else if (k < curNode->firstKey){
          curNode = curNode->childOne;
        }
        else if (k < curNode->secondKey) {
          total = total + curNode->childOne->keysHereUnder + 1;
          curNode = curNode->childTwo;
        }
        else if (k < curNode->thirdKey) {
          total = total + curNode->childOne->keysHereUnder + curNode->childTwo->keysHereUnder + 2;
          curNode = curNode->childThree;
        }
        else{
          total = total + curNode->childOne->keysHereUnder + curNode->childTwo->keysHereUnder + curNode->childThree->keysHereUnder + 3;
          curNode = curNode->childFour;
        }
      }//end of Four Node Status
    }//end of while

    //if we are at a leaf because we were kicked out of while loop
    //cout << "Leaf" << endl;
      if (curNode->nodeStatus == 2){
        if (curNode->firstKey == k){
          total = total + 1;
          return total;
        }
      }
      else if (curNode->nodeStatus == 3){
        if (curNode->firstKey == k) return total + 1;
        else if (curNode->secondKey == k) return total + 2;
      }
      else if (curNode->nodeStatus == 4){
        if (curNode->firstKey == k) return total + 1;
        else if (curNode->secondKey == k) return total + 2;
        else if (curNode->thirdKey == k) return total + 3;
      }
      else{
      return 0;
    }
  } //end of function

  //DID NOT DO VERY WELL, FIX IT
  keytype select(int pos){
    Node<keytype, valuetype>* curNode = root; //starting point

    while (curNode != NULL){
      int left;
      int middleLeft;
      int middleRight;
      int right;

      if(curNode->childOne == 0){ //if it's null, we are at a leaf, so special tactic
        //cout << "Null case left: " << left << endl;
        //cout << "Pos: " << pos << endl;
        //cout << curNode->firstKey << endl;
        if (pos == 1) return curNode->firstKey;
        else if (pos == 2) return curNode->secondKey;
        else if (pos == 3) return curNode->thirdKey;
        else return 0;
      }

      else if (curNode->nodeStatus == 2){
        //cout << "2 Node Case" << endl;
        left = curNode->childOne->keysHereUnder + curNode->nodeStatus - 1;
        //cout << "Pos: " << pos << endl;
        //cout << "Left: " << left << endl;
        if (pos == left){
          return curNode->firstKey;
        }
        else if (pos < left){
          curNode = curNode->childOne;
        }
        else{
          curNode = curNode->childTwo;
          pos = pos - left;
        }
      }

      else if (curNode->nodeStatus == 3){
        //cout << "3 Node Case" << endl;
        //cout << "Pos: " << pos << endl;
        left = curNode->childOne->keysHereUnder + 1; //for left most node
        middleLeft = curNode->childOne->keysHereUnder + curNode->childTwo->keysHereUnder + 1; //for left most node
        middleRight = middleLeft + 1; //for rightmost node
        //cout << "Left: " << left << endl;
        //cout << "Middle: " << middleLeft << endl;
        //cout << "Right; " << middleRight << endl;
      if (pos < left){
        curNode = curNode->childOne;
      }
      else if (pos == left){
        return curNode->firstKey;
      }
      else if (pos < middleRight){
        curNode = curNode->childTwo;
        pos = pos - left;
      }
      else if (pos == middleRight){
        return curNode->secondKey;
      }
      else{
        curNode = curNode->childThree;
        pos = pos - middleRight;
      }
    }
    /*  if (pos == left){
          return curNode->firstKey;
        }
      else if (pos == middleLeft + 1){
          return curNode->secondKey;
      }
      else if (pos < left){
        curNode = curNode->childOne;
      }
      else if (pos < middleRight){
        curNode = curNode->childTwo;
        pos = pos - left;
        }
      else{
        curNode = curNode->childThree;
        pos = pos - middleRight;
        }
      }
*/
      else{
        //cout << "4 Node Case" << endl;
        //cout << "Pos: " << pos << endl;
        left = curNode->childOne->keysHereUnder + 1; //for left most key
        middleLeft = left + curNode->childTwo->keysHereUnder + 1;
        middleRight = middleLeft + curNode->childThree->keysHereUnder + 1;
        right = curNode->childOne->keysHereUnder + curNode->childTwo->keysHereUnder + curNode->childThree->keysHereUnder + 2;

        //cout << "Left: " << left << endl;
        //cout << "Middle: " << middleLeft << endl;
        //cout << "Middle Right: " << middleRight << endl;
        //cout << "Right: " << right << endl;
      if (pos < left){
        curNode = curNode->childOne;
      }

      else if (pos == left){
        return curNode->firstKey;
      }

      else if (pos < middleLeft){
        curNode = curNode->childTwo;
        pos = pos - left;
      }

      else if (pos == middleLeft){
        return curNode->secondKey;
      }

      else if (pos < middleRight){
        curNode = curNode->childThree;
        pos = pos - middleLeft;
      }

      else if (pos == middleRight){
        return curNode->thirdKey;
      }

      else{
        curNode = curNode->childFour;
        pos = pos - middleRight;
      }




/*
      if (pos == left){
          return curNode->firstKey;
        }
      else if (pos == middleLeft + 1){
          return curNode->secondKey;
      }
      else if (pos == right + 1){
          return curNode->thirdKey;
      }
      else if (pos < left){
        curNode = curNode->childOne;
      }
      else if (pos <= middleLeft){
        curNode = curNode->childTwo;
        pos = pos - left;
        }
        else if (pos <= right){
          curNode = curNode->childThree;
          pos = pos - middleLeft;
          }
      else{
        curNode = curNode->childFour;
        pos = pos - (right + 1);
        }
      }
*/
}
    }//end of while
    return 0; //case where it does not exist
  } //end of function


  keytype successor(keytype k){
    int target = rank(k) + 1; //want the key 1 greater than it
    return select(target);
  }

  keytype predecessor(keytype k){
    int target = rank(k) - 1; //want the key 1 less than it
    return select(target);
  }

  int size(){
    return treeSize;
  }

  void preorder(){
    Node<keytype, valuetype>* curNode = root;
    preorderRecursion(curNode);
    cout << endl;
  }

void preorderRecursion(Node<keytype, valuetype>* curNode){
  if (curNode == NULL) return;
  else if (curNode->nodeStatus == 2){
    cout << curNode->firstKey << " ";
    preorderRecursion(curNode->childOne);
    preorderRecursion(curNode->childTwo);
  }
  else if (curNode->nodeStatus == 3){
    cout << curNode->firstKey << " " << curNode->secondKey << " ";
    preorderRecursion(curNode->childOne);
    preorderRecursion(curNode->childTwo);
    preorderRecursion(curNode->childThree);
  }
  else{
    cout << curNode->firstKey << " " << curNode->secondKey << " " << curNode->thirdKey << " ";
    preorderRecursion(curNode->childOne);
    preorderRecursion(curNode->childTwo);
    preorderRecursion(curNode->childThree);
    preorderRecursion(curNode->childFour);
  }
}

void inorder(){
    Node<keytype, valuetype>* curNode = root;
    inorderRecursion(curNode);
    cout << endl;
  }

void inorderRecursion(Node<keytype, valuetype>* curNode){
  if (curNode == NULL) return;
  else if (curNode->nodeStatus == 2){
    inorderRecursion(curNode->childOne);
    //cout << curNode->firstKey << curNode->keysHereUnder << " ";
    cout << curNode->firstKey << " ";
    inorderRecursion(curNode->childTwo);
  }
  else if (curNode->nodeStatus == 3){
    inorderRecursion(curNode->childOne);
    cout << curNode->firstKey << " ";
    inorderRecursion(curNode->childTwo);
    cout << curNode->secondKey << " ";
    //cout << curNode->secondKey << curNode->keysHereUnder << " ";
    inorderRecursion(curNode->childThree);
  }
  else{
    inorderRecursion(curNode->childOne);
    cout << curNode->firstKey << " ";
    inorderRecursion(curNode->childTwo);
    cout << curNode->secondKey << " ";
    inorderRecursion(curNode->childThree);
    cout << curNode->thirdKey << " ";
    //cout << curNode->thirdKey << curNode->keysHereUnder << " ";
    inorderRecursion(curNode->childFour);
  }
}

  void postorder(){
    //can't do recursion with this, make a new function
    Node<keytype, valuetype>* curNode = root;
    postorderRecursion(curNode);
    cout << endl;
  }

  void postorderRecursion(Node<keytype, valuetype>* curNode){
    if (curNode == NULL) return;
    else if (curNode->nodeStatus == 2){
      postorderRecursion(curNode->childOne);
      postorderRecursion(curNode->childTwo);
      cout << curNode->firstKey << " ";
    }
    else if (curNode->nodeStatus == 3){
      postorderRecursion(curNode->childOne);
      postorderRecursion(curNode->childTwo);
      postorderRecursion(curNode->childThree);
      cout << curNode->firstKey <<  " " << curNode->secondKey << " ";
    }
    else{
      postorderRecursion(curNode->childOne);
      postorderRecursion(curNode->childTwo);
      postorderRecursion(curNode->childThree);
      postorderRecursion(curNode->childFour);
      cout << curNode->firstKey << " " << curNode->secondKey << " " << curNode->thirdKey << " ";
    }
  }

  Node<keytype, valuetype>* split(Node<keytype, valuetype>* splitNode){
    //function called when a node with nodeStatus = 4 detected
    //returns the highest node made from split
    Node<keytype, valuetype>* newNode = new Node<keytype, valuetype>;
    //now we have a new, blank node to work with
    //cout << "In split" << endl;

    if (splitNode->parent == NULL){ //node has no parent, so it is the root
      //cout << "has no parent, root case" << endl;
      Node<keytype, valuetype>* newLeft = new Node<keytype, valuetype>;
      Node<keytype, valuetype>* newRight = new Node<keytype, valuetype>;
      //cout << "Set new nodes statuses" << endl;
      newNode->nodeStatus = 2; //they are all two nodes
      newLeft->nodeStatus = 2;
      newRight->nodeStatus = 2;
      //cout << "Set new nodes first keys" << endl;
      newLeft->firstKey = splitNode->firstKey; //reassign keys
      newNode->firstKey = splitNode->secondKey; //to new nodes
      newRight->firstKey = splitNode->thirdKey;
//cout << "Set new nodes first values" << endl;
      newLeft->firstValue = splitNode->firstValue; //reassign values
      newNode->firstValue = splitNode->secondValue; //to new nodes
      newRight->firstValue = splitNode->thirdValue;
//cout << "Set new left kids" << endl;
      newLeft->childOne = splitNode->childOne; //parent knows kids
      newLeft->childTwo = splitNode->childTwo;
      //cout << "left kids are set. Now telling kids who their parent is (newLeft)" << endl;
      if ((newLeft->childOne && newLeft->childTwo) != NULL){
      newLeft->childOne->parent = newLeft; //kids know parent
      newLeft->childTwo->parent = newLeft;
}
//cout << "Set new right kids" << endl;
      newRight->childOne = splitNode->childThree; //parent knows kids
      newRight->childTwo = splitNode->childFour;
    if ((newRight->childOne && newRight->childTwo) != NULL){
      //cout << "Right's child one first key: " << newRight->childOne->firstKey;
      //cout << "Right's child two first key: " << newRight->childTwo->firstKey;
      newRight->childOne->parent = newRight; //kids know parent
      newRight->childTwo->parent = newRight;
    }
//cout << "parent to left and right" << endl;
      newNode->childOne = newLeft; //newNode is above
      newNode->childTwo = newRight; //makes both kids
//cout << "Set left and rights parent to new node" << endl;
      newLeft->parent = newNode; //links to parent
      newRight->parent = newNode;
//cout << "about to delete splitnode" << endl;
      delete splitNode; //now get rid of the old node left behind
      //cout << "deleted split node" << endl;
      root = newNode;
      //treeSize++; commented out because he wants it to be key count, not nodes
      //treeSize++;

      if ((newLeft->childOne && newLeft->childTwo) != NULL){
        newLeft->keysHereUnder = newLeft->childOne->keysHereUnder + newLeft->childTwo->keysHereUnder + 1;
      }
      else{
        newLeft->keysHereUnder++;
      }

      if ((newRight->childOne && newRight->childTwo) != NULL){
        newRight->keysHereUnder = newRight->childOne->keysHereUnder + newRight->childTwo->keysHereUnder + 1;
      }
      else{
        newRight->keysHereUnder++;
      }

      newNode->keysHereUnder = newLeft->keysHereUnder + newRight->keysHereUnder;
      //returns newNode
    }

    else{ //splitting where there is a parent above
      //since we split, we know there is a first key and second key
      //we assume they are already in order due to insertion

      if (splitNode->parent->nodeStatus == 2){ // if parent is a 2 node.               ///THIS MAY HAVE BEEN WRECKED BY THE AUTO REPLACE FEATURE. DOUBLE CHECK!!!!
        //cout << "Parent above type split" << endl;
        if (splitNode == splitNode->parent->childOne){ //if we are the left child
          //cout << "2 Node Parent: Left Child" << endl;
          splitNode->parent->childThree = splitNode->parent->childTwo; //scoot over 1

          Node<keytype, valuetype>* newMiddle = new Node<keytype, valuetype>; //middle node
          Node<keytype, valuetype>* newLeft = new Node<keytype, valuetype>; //left node

          //All of newleft
          newLeft->nodeStatus = 2; //the node is a 2 node
          newLeft->firstKey = splitNode->firstKey; //moving the key to own node
          newLeft->firstValue = splitNode->firstValue; // move the value with it
          newLeft->childOne = splitNode->childOne; //making new connections
          newLeft->childTwo = splitNode->childTwo; //to previous 4 children
          if ((newLeft->childOne && newLeft->childTwo) != NULL){
          newLeft->childOne->parent = newLeft;
          newLeft->childTwo->parent = newLeft;
          newLeft->keysHereUnder = newLeft->childOne->keysHereUnder + newLeft->childTwo->keysHereUnder + 1;
        }
        else{
          newLeft->keysHereUnder++;
        }
          newLeft->parent = splitNode->parent; //setting parent
          splitNode->parent->childOne = newLeft; //parent knows this is new kid

          //All of newMiddle config
          newMiddle->nodeStatus = 2; //the node is a 2 node
          newMiddle->firstKey = splitNode->thirdKey; //moving the key to own node
          newMiddle->firstValue = splitNode->thirdValue; // move the value with it
          newMiddle->childOne = splitNode->childThree; //making new connections
          newMiddle->childTwo = splitNode->childFour; //to previous 4 children
          if ((newMiddle->childOne && newMiddle->childTwo) != NULL){
          newMiddle->childOne->parent = newMiddle;
          newMiddle->childTwo->parent = newMiddle;
          newMiddle->keysHereUnder = newMiddle->childOne->keysHereUnder + newMiddle->childTwo->keysHereUnder + 1;
        }
        else{
          newMiddle->keysHereUnder++;
        }
          newMiddle->parent = splitNode->parent; //setting parent
          splitNode->parent->childTwo = newMiddle; //parent knows this is new kid

          //Kids are taken care of, now fix parent.
          //We are left side, so less than parent. Move it right.
          splitNode->parent->secondKey = splitNode->parent->firstKey; //move key
          splitNode->parent->secondValue = splitNode->parent->firstValue; //move value

          //Now move stuff up from splitting node
          splitNode->parent->firstKey = splitNode->secondKey; //key
          splitNode->parent->firstValue = splitNode->secondValue;//value
          splitNode->parent->nodeStatus = 3; //status update

          newNode = splitNode->parent; //item to return will be the parent
          delete splitNode;
          //treeSize++; for counting nodes
        } // end of left child case

      else{ //right child case
        //no need to scoot anything over
        //cout << "2 Node Parent: Right Child" << endl;
        Node<keytype, valuetype>* newMiddle = new Node<keytype, valuetype>; //middle node
        Node<keytype, valuetype>* newRight = new Node<keytype, valuetype>; //right node

        //All of newRight
        newRight->nodeStatus = 2; //the node is a 2 node
        newRight->firstKey = splitNode->thirdKey; //moving the key to own node
        newRight->firstValue = splitNode->thirdValue; // move the value with it
        newRight->childOne = splitNode->childThree; //making new connections
        newRight->childTwo = splitNode->childFour; //to previous 4 children
        if ((newRight->childOne && newRight->childTwo) != NULL){
        newRight->childOne->parent = newRight;
        newRight->childTwo->parent = newRight;
        newRight->keysHereUnder = newRight->childOne->keysHereUnder + newRight->childTwo->keysHereUnder + 1;
      }
      else{
        newRight->keysHereUnder++;
      }
        newRight->parent = splitNode->parent; //setting parent
        splitNode->parent->childThree = newRight; //parent knows this is new kid

        //All of newMiddle config
        newMiddle->nodeStatus = 2; //the node is a 2 node
        newMiddle->firstKey = splitNode->firstKey; //moving the key to own node
        newMiddle->firstValue = splitNode->firstValue; // move the value with it
        newMiddle->childOne = splitNode->childOne; //making new connections
        newMiddle->childTwo = splitNode->childTwo; //to previous 4 children
        if ((newMiddle->childOne && newMiddle->childTwo) != NULL){
        newMiddle->childOne->parent = newMiddle;
        newMiddle->childTwo->parent = newMiddle;
        newMiddle->keysHereUnder = newMiddle->childOne->keysHereUnder + newMiddle->childTwo->keysHereUnder + 1;
      }
      else{
        newMiddle->keysHereUnder++;
      }
        newMiddle->parent = splitNode->parent; //setting parent
        splitNode->parent->childTwo = newMiddle; //parent knows this is new kid

        //Kids are taken care of, now fix parent.
        //We are right side, so greater than parent. Keep original position

        //Now move stuff up from splitting node
        splitNode->parent->secondKey = splitNode->secondKey; //key
        splitNode->parent->secondValue = splitNode->secondValue;//value
        splitNode->parent->nodeStatus = 3; //status update

        newNode = splitNode->parent; //ride out of here
        delete splitNode;
        //treeSize++; for counting nodes
      }//end of right child case
    }//end of 2 Node case

    else{ //3 Node Case, we do not need a 4 node case as we'd never have a 4 node above us, split on way down
      if (splitNode == splitNode->parent->childOne){ //if we are the left child
        //cout << "3 Node Parent: Left Child" << endl;
        //Scoot the parent stuff over
        splitNode->parent->thirdKey = splitNode->parent->secondKey; //key 2 becomes key 3
        splitNode->parent->thirdValue = splitNode->parent->secondValue; //value 2 becomes value 3
        splitNode->parent->secondKey = splitNode->parent->firstKey; //key 1 becomes key 2
        splitNode->parent->secondValue = splitNode->parent->firstValue; //value 1 becomes value 2

        //move the children pointers over 1 as well
        splitNode->parent->childFour = splitNode->parent->childThree; //3 becomes 4
        splitNode->parent->childThree = splitNode->parent->childTwo; // 2 becomes 3

        Node<keytype, valuetype>* newMiddle = new Node<keytype, valuetype>; //middleleft node
        Node<keytype, valuetype>* newLeft = new Node<keytype, valuetype>; //left node

        //all of newLeft stuff
        newLeft->nodeStatus = 2; //the node is a 2 node
        newLeft->firstKey = splitNode->firstKey; //moving the key to own node
        newLeft->firstValue = splitNode->firstValue; // move the value with it
        newLeft->childOne = splitNode->childOne; //making new connections
        newLeft->childTwo = splitNode->childTwo; //to previous 4 children
        if ((newLeft->childOne && newLeft->childTwo) != NULL){
        newLeft->childOne->parent = newLeft;
        newLeft->childTwo->parent = newLeft;
        newLeft->keysHereUnder = newLeft->childOne->keysHereUnder + newLeft->childTwo->keysHereUnder + 1;
      }
      else{
        newLeft->keysHereUnder++;
      }

        newLeft->parent = splitNode->parent; //setting parent
        splitNode->parent->childOne = newLeft; //parent knows this is new kid

        //all of newMiddle stuff
        newMiddle->nodeStatus = 2; //the node is a 2 node
        newMiddle->firstKey = splitNode->thirdKey; //moving the key to own node
        newMiddle->firstValue = splitNode->thirdValue; // move the value with it
        newMiddle->childOne = splitNode->childThree; //making new connections
        newMiddle->childTwo = splitNode->childFour; //to previous 4 children
        if ((newMiddle->childOne && newMiddle->childTwo) != NULL){
        newMiddle->childOne->parent = newMiddle;
        newMiddle->childTwo->parent = newMiddle;
        newMiddle->keysHereUnder = newMiddle->childOne->keysHereUnder + newMiddle->childTwo->keysHereUnder + 1;
      }
      else{
        newMiddle->keysHereUnder++;
      }

        newMiddle->parent = splitNode->parent; //setting parent
        splitNode->parent->childTwo = newMiddle; //parent knows this is new kid

        //now just move up the stuff from splitnode. we are on the left.
        splitNode->parent->firstKey = splitNode->secondKey; //key
        splitNode->parent->firstValue = splitNode->secondValue;//value
        splitNode->parent->nodeStatus = 4; //status update

        newNode = splitNode->parent; //ride out of here
        delete splitNode;
        //treeSize++; for counting nodes
    } //end of left child case

    else if (splitNode == splitNode->parent->childTwo){ //if we are the middle child
      //cout << "3 Node Parent: Middle Child" << endl;
      //Scoot the parent stuff over
      splitNode->parent->thirdKey = splitNode->parent->secondKey; //key 2 becomes key 3
      splitNode->parent->thirdValue = splitNode->parent->secondValue; //value 2 becomes value 3

      //move the children pointers over 1 as well
      splitNode->parent->childFour = splitNode->parent->childThree; //3 becomes 4

      //3 is clear and 2 is still occupied. We can still access even if we give up 2 slot to new node due to parent pointer
      Node<keytype, valuetype>* newRight = new Node<keytype, valuetype>; //middleleft node
      Node<keytype, valuetype>* newLeft = new Node<keytype, valuetype>; //middleRight node, using esaier names of course

      //all of newLeft stuff
      newLeft->nodeStatus = 2; //the node is a 2 node
      newLeft->firstKey = splitNode->firstKey; //moving the key to own node
      newLeft->firstValue = splitNode->firstValue; // move the value with it
      newLeft->childOne = splitNode->childOne; //making new connections
      newLeft->childTwo = splitNode->childTwo; //to previous 4 children
      if ((newLeft->childOne && newLeft->childTwo) != NULL){
      newLeft->childOne->parent = newLeft;
      newLeft->childTwo->parent = newLeft;
      newLeft->keysHereUnder = newLeft->childOne->keysHereUnder + newLeft->childTwo->keysHereUnder + 1;
    }
    else{
      newLeft->keysHereUnder++;
    }
      newLeft->parent = splitNode->parent; //setting parent
      splitNode->parent->childTwo = newLeft; //parent knows this is new kid

      //all of newRight stuff
      newRight->nodeStatus = 2; //the node is a 2 node
      newRight->firstKey = splitNode->thirdKey; //moving the key to own node
      newRight->firstValue = splitNode->thirdValue; // move the value with it
      newRight->childOne = splitNode->childThree; //making new connections
      newRight->childTwo = splitNode->childFour; //to previous 4 children
      if ((newRight->childOne && newRight->childTwo) != NULL){
      newRight->childOne->parent = newRight;
      newRight->childTwo->parent = newRight;
      newRight->keysHereUnder = newRight->childOne->keysHereUnder + newRight->childTwo->keysHereUnder + 1;
    }
    else{
      newRight->keysHereUnder++;
    }
      newRight->parent = splitNode->parent; //setting parent
      splitNode->parent->childThree = newRight; //parent knows this is new kid

      //now just move up the stuff from splitnode. we are in the middle
      splitNode->parent->secondKey = splitNode->secondKey; //key
      splitNode->parent->secondValue = splitNode->secondValue;//value
      splitNode->parent->nodeStatus = 4; //status update

      newNode = splitNode->parent; //ride out of here
      delete splitNode;
      //treeSize++; counting nodes
    } //end of middle child case

    else{ //if we are the right child

      //No need to scoot any keys/values over since nodes grow to the right
//cout << "3 Node Parent: Right Child" << endl;
      //no need to move child pointers either

      Node<keytype, valuetype>* newMiddle = new Node<keytype, valuetype>; //middleRight node
      Node<keytype, valuetype>* newRight = new Node<keytype, valuetype>; //right node

      //all of newMiddle stuff
      newMiddle->nodeStatus = 2; //the node is a 2 node
      newMiddle->firstKey = splitNode->firstKey; //moving the key to own node
      newMiddle->firstValue = splitNode->firstValue; // move the value with it
      newMiddle->childOne = splitNode->childOne; //making new connections
      newMiddle->childTwo = splitNode->childTwo; //to previous 4 children
      if ((newMiddle->childOne && newMiddle->childTwo) != NULL){
      newMiddle->childOne->parent = newMiddle;
      newMiddle->childTwo->parent = newMiddle;
      newMiddle->keysHereUnder = newMiddle->childOne->keysHereUnder + newMiddle->childTwo->keysHereUnder + 1;
    }
    else{
      newMiddle->keysHereUnder++;
    }
      newMiddle->parent = splitNode->parent; //setting parent
      splitNode->parent->childThree = newMiddle; //parent knows this is new kid
      //cout << "made it to here" << endl;
      //all of newRight stuff
      newRight->nodeStatus = 2; //the node is a 2 node
      newRight->firstKey = splitNode->thirdKey; //moving the key to own node
      newRight->firstValue = splitNode->thirdValue; // move the value with it
      newRight->childOne = splitNode->childThree; //making new connections
      newRight->childTwo = splitNode->childFour; //to previous 4 children
      if ((newRight->childOne && newRight->childTwo) != NULL){
      newRight->childOne->parent = newRight;
      newRight->childTwo->parent = newRight;
      newRight->keysHereUnder = newRight->childOne->keysHereUnder + newRight->childTwo->keysHereUnder + 1;
    }
    else{
      newRight->keysHereUnder++;
    }
      newRight->parent = splitNode->parent; //setting parent
      splitNode->parent->childFour = newRight; //parent knows this is new kid

      //now just move up the stuff from splitnode. we are on the left.
      splitNode->parent->thirdKey = splitNode->secondKey; //key
      splitNode->parent->thirdValue = splitNode->secondValue;//value
      splitNode->parent->nodeStatus = 4; //status update

      newNode = splitNode->parent; //ride out of here
      delete splitNode;
      //treeSize++; counting nodes
  } //end of right child case
} //end of 3 Node case
} //end of parent above case
//cout << "Did a split" << endl;
return newNode; //return the new node if case 1, modified parent if case 2
} //end of split function

valuetype selectValue(int pos){ //modified select to get value
  Node<keytype, valuetype>* curNode = root; //starting point

  while (curNode != NULL){
    int left;
    int middleLeft;
    int middleRight;
    int right;

    if(curNode->childOne == 0){ //if it's null, we are at a leaf, so special tactic
      //cout << "Null case left: " << left << endl;
      //cout << "Pos: " << pos << endl;
      //cout << curNode->firstKey << endl;
      if (pos == 1) return curNode->firstValue;
      else if (pos == 2) return curNode->secondValue;
      else if (pos == 3) return curNode->thirdValue;
      else return 0;
    }

    else if (curNode->nodeStatus == 2){
      //cout << "2 Node Case" << endl;
      left = curNode->childOne->keysHereUnder + curNode->nodeStatus - 1;
      //cout << "Pos: " << pos << endl;
      //cout << "Left: " << left << endl;
      if (pos == left){
        return curNode->firstValue;
      }
      else if (pos < left){
        curNode = curNode->childOne;
      }
      else{
        curNode = curNode->childTwo;
        pos = pos - left;
      }
    }

    else if (curNode->nodeStatus == 3){
      //cout << "3 Node Case" << endl;
      //cout << "Pos: " << pos << endl;
      left = curNode->childOne->keysHereUnder + 1; //for left most node
      middleLeft = curNode->childOne->keysHereUnder + curNode->childTwo->keysHereUnder + 1;
      middleRight = middleLeft  + 1;
      //cout << "Left: " << left << endl;
      //cout << "Middle: " << middleLeft << endl;
      //cout << "Right; " << middleRight << endl;
    if (pos == left){
        return curNode->firstValue;
      }
    else if (pos == middleLeft + 1){
        return curNode->secondValue;
    }
    else if (pos < left){
      curNode = curNode->childOne;
    }
    else if (pos < middleRight){
      curNode = curNode->childTwo;
      pos = pos - left;
      }
    else{
      curNode = curNode->childThree;
      pos = pos - (middleLeft + 1);
      }
    }

    else{
      //cout << "4 Node Case" << endl;
      //cout << "Pos: " << pos << endl;
      left = curNode->childOne->keysHereUnder + 1; //for left most key
      middleLeft = curNode->childOne->keysHereUnder + curNode->childTwo->keysHereUnder + 1;
      middleRight = middleLeft  + 1; //for second key
      right = curNode->childOne->keysHereUnder + curNode->childTwo->keysHereUnder + curNode->childThree->keysHereUnder + 2;

      //cout << "Left: " << left << endl;
      //cout << "Middle: " << middleLeft << endl;
      //cout << "Middle Right: " << middleRight << endl;
      //cout << "Right: " << right << endl;
    if (pos == left){
        return curNode->firstValue;
      }
    else if (pos == middleLeft + 1){
        return curNode->secondValue;
    }
    else if (pos == right + 1){
        return curNode->thirdValue;
    }
    else if (pos < left){
      curNode = curNode->childOne;
    }
    else if (pos <= middleLeft){
      curNode = curNode->childTwo;
      pos = pos - left;
      }
      else if (pos <= right){
        curNode = curNode->childThree;
        pos = pos - middleLeft;
        }
    else{
      curNode = curNode->childFour;
      pos = pos - (right + 1);
      }
    }

  }//end of while
  return 0; //case where it does not exist
} //end of function

}; //end of class
