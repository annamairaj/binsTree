
// Name: Anna Mairaj
// Compiler:  g++
// File type: implementation file binstree.cpp
//================================================================

#include <iostream>
#include "binstree.h"
using namespace std;

// constructor  initializes  
BST::BST()
{
  Root = NULL;   // This is an empty tree
}

// destructor must completely destroy the tree
BST::~BST()
{
  deleteTraverse(Root); // traverse to delete all vertices in post order
  Root = NULL;
}

// PURPOSE: Does Post Order traversal of the tree and deletes each vertex
// PARAM:   V is a pointer to the vertex to be deleted
void BST::deleteTraverse(Vertex *V) {  // recursive post order traversal
  if (V != NULL) {
    deleteTraverse(V->left);   // destroy left sub tree of V
    deleteTraverse(V->right);  // destroy right sub tree of V
    delete V;                  // delete V
  }
}

// PURPOSE: Show vertices in IN order traversal from the Root
void BST::Display() {
    cout << "--- Elements in the IN order: ---" << endl;
    if (Root != NULL) {
        cout << "Root is: " << Root->elem << endl;
        InOrderTraversal(Root);
    } else {
        cout << "The tree is empty." << endl;
    }
    cout << "---------------------------------" << endl;
}

// PURPOSE: Does IN order traversal from V recursively
// PARAM: V is te pointer to the vertex to visit right now
void BST::InOrderTraversal(Vertex *V)
{
  if (V != NULL) {
    deleteTraverse(V->left);   // destroy left sub tree of V
    cout << V->elem << " (H: " << V->height << ", B: " << V->balance << ")" << endl;
    deleteTraverse(V->right);  // destroy right sub tree of V
    delete V;                  // delete Vß
  }
}

// PURPOSE: Searches for an element in PRE-order traversal
// This is the same as Depth First Traversal
bool BST::Search(el_t K)
{
  PreOrderSearch(Root, K);  // start pre-order traversal from the Root
}
// PURPOSE: Does PRE order search from V recursively
// PARAM: V is the pointer to the vertex to be visited now
//        K is what we are looking for
bool BST::PreOrderSearch(Vertex *V, el_t K)
{
  if (V != NULL) {
    if (K == V->elem) {
      return true; // found the element in V
    } else if (K < V->elem) {
       return PreOrderSearch(V->left, K);  // traverse left sub-tree of V recursively
        } else {
            return PreOrderSearch(V->right, K); // traverse right sub-tree of V recursively
        }
    }
      return false;
}

// ------ The following are for adding and deleting vertices -----

// PURPOSE: Adds a vertex to the binary search tree for a new element
// PARAM: the new element E
// ALGORITHM: We will do this iteratively (not recursively)
// to demonstrate the algorithm that is in the notes
//    - smaller than the current -> go to the left
//    - bigger than the current  -> go to the right
//    - cannot go any further    -> add it there
void BST::InsertVertex(el_t E) {
  // Set up a new vertex first
  Vertex *N;         // N will point to the new vertex to be inserted
  N = new Vertex;    // a new vertex is created
  N->left  = NULL;   // make sure it does not
  N->right = NULL;   // point to anything
  N->elem  = E;      // put element E in it
  N->height = 0;
  N->balance = 0;
  N->up = NULL;      // no parent for now

  cout << "Trying to insert " << E << endl;

  if (Root == NULL)  // Special case: we have a brand new empty tree
    {
      Root = N;      // the new vertex is added as the Root
      cout << "...adding " << E << " as the Root" << endl;
      return;
    }// end of the special case

  else  // the tree is not empty
    {
      Vertex *V;       // V will point to the current vertex
      Vertex *Parent;  // Parent will always point to V's parent

      V = Root;        // start with the Root as V
      Parent = NULL;   // above V so it does not point to anything

      // go down the tree until you cannot go any further
      while (V != NULL) {
        Parent = V; // Update Parent before moving down
        if (N->elem == V->elem) { // the element already exists
          cout << "...error: the element already exists" << endl;
          return;
        } else if (N->elem < V->elem) {  // what I have is smaller than V
          cout << "...going to the left" << endl;
           V = V->left; // change V to be V's left
            } else {  // what I have is bigger than V
                cout << "...going to the right" << endl;
                V = V->right; // change V to be V's right
            }
      }//end of while
      
      // reached NULL -- Must add N as the Parent's child
      if (N->elem < Parent->elem) {
        Parent->left = N; // Parent's left should point to N
        N->up = Parent;   // N must point UP to the Parent
        cout << "...adding " << E << " as the left child of "
             << Parent->elem << endl;
        } else {
        Parent->right = N; // Parent's right should point to N
        N->up = Parent;     // N must point UP to the Parent
        cout << "...adding " << E << " as the right child of " 
        << Parent->elem << endl;
        cout << N->elem << " now points UP to " << N->up->elem << endl;
        }
    }// end of normal case
}// end of InsertVertex


// PURPOSE: Deletes a vertex that has E as its element.
// PARAM: element E to be removed
// ALGORITHM: First we must find the vertex then call Remove
void BST::DeleteVertex(el_t E) {
  cout << "Trying to delete " << E << endl;

  Vertex *V;       // the current vertex
  Vertex *Parent;  // Parent will always point to V's parent

  // case 1: Lonely Root  --------------------
  if ((E == Root->elem) && (Root->left == NULL) && (Root->right == NULL)) {
    cout << "...deleting the lonely Root" << endl;
    delete Root;
    Root = NULL;
    return;
  }  // only the Root was there and deleted it

  // case 2:  One Substree Root ----------------
  // if what you want to delete is the Root
  if (E == Root->elem) {
    cout << "... deleting the Root with just one child" << endl;
    if (Root->left != NULL) {
      Vertex *temp = Root->left; // keep the left child
            delete Root; // delete the Root
            Root = temp; // make left child the new Root
            Root->up = NULL; // new Root has no parent
            return;
    } else if (Root->right != NULL) { // if it has only the right subtree
     Vertex *temp = Root->right; // keep the right child
            delete Root; // delete the Root
            Root = temp; // make right child the new Root
            Root->up = NULL; // new Root has no parent
            return;
        }
  }// end of deleting the Root with one subtree

  // ---- Otherwise deleting something else  --------------
  V = Root;  // start with the Root to look for E
  Parent = NULL;  // above the V so does not point to anything yet

  // going down the tree looking for E
  while (V != NULL) {
    if (E == V->elem) {  // found it
      cout << "...removing " << V->elem << endl;
      remove(V, Parent); // call remove here to remove V
      return;
    } else if (E < V->elem) {
      cout << "...going to the left" << endl;
       Parent = V; // update Parent
       V = V->left; // go left
    } else {
      cout << "...going to the right" << endl;
      Parent = V; // update Parent
      V = V->right; // go right
    }
  }// end of while

  // reached NULL  -- did not find it
  cout << "Did not find the key in the tree." << endl;

}// end of DeleteVertex


// PURPOSE: Removes vertex pointed to by V
// PARAM: V and its parent  pointer P
// Case 1: it is a leaf, delete it
// Case 2: it has just one child, bypass it
// Case 3: it has two children, replace it with the max of the left subtree
void BST::remove(Vertex *V, Vertex *P)
{
  if (V->left == NULL && V->right == NULL) { // if V is a leaf (case 1)
    cout << "removing a leaf" << endl;
    if (P->left == V) { // if V is a left child of P
      P->left = NULL; // Parent's left becomes NULL
    } else {// V is a right child of the Parent
      P->right = NULL; // Parent's right becomes NULL
    } delete V; // delete V
  } else if (V->left != NULL && V->right == NULL) { // if V has just the left child so bypass V (case 2)
    Vertex* C = V->left; // C is the left child
    cout << "removing a vertex with just the left child" << endl;
       if (P->left == V) {
            P->left = C; // Parent's left points to C
        } else {
            P->right = C; // Parent's right points to C
        }
        C->up = P; // Make C point UP to the parent
    cout << C->elem << " points up to " << C->up->elem << endl;
    delete V; // delete V
  } else if (V->right != NULL && V->left == NULL) { // if V has just the right child so bypass V (case 2)
    Vertex* C = V->right;  // C is the right child
    cout << "removing a vertex with just the right child" << endl;
     // Determine if V is a left or right child of its parent
    if (P->left == V) {
        P->left = C; // Parent's left points to C
    } else {
        P->right = C; // Parent's right points to C
    }
    
    C->up = P; // Make C point UP to the parent
    cout << C->elem << " points up to " << C->up->elem << endl;

    delete V; // Be sure to delete V

  } else { // V has two children (case 3)
    cout << "removing an internal vertex with children" << endl;
    cout << "..find the MAX of its left sub-tree" << endl;
    el_t Melem;
    // find MAX element in the left sub-tree of V
    Melem = findMax(V);
    cout << "..replacing " << V->elem << " with " << Melem << endl;
    V->elem = Melem; // Replace V's element with Melem here
  }
}// end of remove

// PURPOSE: Finds the Maximum element in the left sub-tree of V
// and also deletes that vertex
el_t BST::findMax(Vertex *V) {
  Vertex *Parent = V;
  V = V->left;         // start with the left child of V

  while (V->right != NULL) {
    Parent = V;            // Update Parent to the current V
    V = V->right;         // Move V to its right child
    }

  // reached NULL Right  -- V now has the MAX element
  el_t X = V->elem;
  cout << "...Max is " << X << endl;
  remove(V, Parent);    // remove the MAX vertex
  return X;             // return the MAX element

}// end of FindMax