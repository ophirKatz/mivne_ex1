/*
* this is the impelemtation of the Avl tree by the
* number one hotshot Daniel Lyubin
*/
#ifndef AVLTREE_HPP_
#define AVLTREE_HPP_

#include "TreeNode.hpp"
#include <string>
#include <iostream>
#include <cmath>

using std::string;
using std::exception;

namespace AuxFuncs {
  template<class T,class F>
  TreeNode<T,F>* pFind(TreeNode<T,F>* nodeTS, const TreeNode<T,F>* dNode);
  
  template<class T,class F>
  void pInsert(TreeNode<T,F>* root ,TreeNode<T,F>* dNode);
  
  template<class T, class F>
  void preOrderAux(TreeNode<T,F>* node, T*& preOrdArr, int* i);

  template<class T, class F>
  void inOrderAux(TreeNode<T,F>* node, T*& inOrdArr, int* i);

  template<class T, class F>
  void postOrderAux(TreeNode<T,F>* node, T*& postOrdArr, int* i);

  template<class T, class F>
  bool isLeaf(TreeNode<T,F>* node);
  
  template<class T, class F>
  TreeNode<T,F>* returnMinFromRight(TreeNode<T,F>* node);
  
  template<class T, class F>
  int numOfChildren(TreeNode<T,F>* node);

  template<class T, class F>
  void removeSingle(TreeNode<T,F>*& nodeTD);
	
  template<class T, class F>
  void removeAux(TreeNode<T,F>*& root,TreeNode<T,F>* nodeTD);

  template<class T, class F>
  void rollCheck(TreeNode<T,F>* node);
  
  template<class T, class F>
  void rollLL(TreeNode<T,F>* node);

  template<class T, class F>
  void rollRL(TreeNode<T,F>* node);

  template<class T, class F>
  void rollLR(TreeNode<T,F>* node);

  template<class T, class F>
  void rollRR(TreeNode<T,F>* node);

  template<class T, class F>
  void insertArrayToTreeAux(T* arr, int n, int& i, 
				   TreeNode<T,F>* root);

  template<class T, class F>
  T& getMaxAux(TreeNode<T,F>* node);

  template<class T, class F>
  T& getMinAux(TreeNode<T,F>* node);

}

namespace treeExceptions {
  class AlreadyExists {};
  class NotFound {};
  class ArraySizeInvalid{};
  class NotSorted {};
}
using namespace treeExceptions;
using namespace AuxFuncs;


template<class T,class F>
class AvlTree {
private:
  TreeNode<T,F>* root;
  int treeSize;
  bool isSorted(T* arr, int n);
public:
  AvlTree<T,F>();
  AvlTree<T,F>(const AvlTree<T,F>& tree);
  ~AvlTree<T,F>();

  int size();
  int height();

  void insert(const T& data);
  void remove(const T& data);
  T& find(const T& data);
  T& findMin();
  T& findMax();
  void insertArrayToTree(T* arr, int n);
	AvlTree<T,F>& operator=(const AvlTree<T,F>& avlTree);
  /*These functions return copy of the elements in the tree
   *	according to the order
   */
  T* preOrder();
  T* inOrder();
  T* postOrder();

};

/***************Implmentation*****************/
/*C'tors and D'tor*/
template<class T,class F>
AvlTree<T,F>::AvlTree():
  root(NULL), treeSize(0) {
}

template<class T,class F>
AvlTree<T,F>::AvlTree(const AvlTree<T,F>& tree):
  treeSize(tree.treeSize) {
  if (tree.root == NULL){
    this->root=NULL;	
  }
  else
    this->root=new TreeNode<T,F>(*tree.root); 
}


template<class T, class F>
AvlTree<T,F>::~AvlTree<T,F>() {
  treeTotalDestroy(root);
  root = NULL;
}




/******Get Functions********/
template<class T,class F>
int AvlTree<T,F>::size() {
  return this->treeSize;
}

template<class T,class F>
int AvlTree<T,F>::height() {
  return this->root->getHeight();
}

/* 
 * This function gets a root, and data node to insert, and search 
 * recursivly the appropriate location in the tree and store it there.
 */
template<class T, class F>
void AuxFuncs::pInsert(TreeNode<T,F>* root, TreeNode<T,F>* dNode) {
  if ((*dNode) == (*root)){
    throw AlreadyExists();
  }
  else if ((*dNode) < (*root)){
    if(!root->getLeft()){
      root->setLeft(dNode);
      dNode->setFather(root);
      root->setHeight();
      return;
    }
    pInsert(root->getLeft(), dNode);
  }
  else if ((*dNode) > (*root)) {
    if(!root->getRight())  {
      root->setRight(dNode);
      dNode->setFather(root);
      root->setHeight();
      return;
    }
    pInsert(root->getRight(), dNode);
  }
  root->setHeight();
  rollCheck(root);
}

template<class T, class F>
void AvlTree<T,F>::insert(const T& data){
  if (!root){
    root = new TreeNode<T,F>(data);
    this->treeSize++;
    return;
  }
  TreeNode<T,F>* dNode = new TreeNode<T,F>(data);
  try {
    pInsert(root, dNode);
  } catch (AlreadyExists& e) {
    delete dNode;
    throw AlreadyExists();
  }
  if (root->getFather()){
    root = root->getFather();
  }
  this->treeSize++;
}

/*
 * This function recives some nodeTS (To Search in) and a data node, and returns the node in 
 *  the tree of the nodeTS which has the same data as the data node, NULL otherwise.
 */
template<class T, class F>
TreeNode<T,F>* AuxFuncs::pFind(TreeNode<T,F>* nodeTS, const TreeNode<T,F>* dNode){
  if(!nodeTS){
    return NULL;
  }
  if ((*dNode) == (*nodeTS)){
    return nodeTS;
  }
  if ((*dNode) < (*nodeTS)){
    return pFind(nodeTS->getLeft(), dNode);
  } 
  return pFind(nodeTS->getRight(), dNode);
}

template<class T, class F>
T& AvlTree<T,F>::find(const T& data){
  if(!this->root){
    throw NotFound();
  }
  TreeNode<T,F>* dNode = new TreeNode<T,F>(data);
  TreeNode<T,F>* found = pFind(this->root, dNode);
  if(found == NULL){
    delete dNode;
    throw NotFound();
  }
  delete dNode;
  return found->getData();
}


template<class T, class F>
void AvlTree<T,F>::insertArrayToTree(T* arr, int n){
  if(n != this->treeSize){
    throw ArraySizeInvalid();
  }
  
  if (!AvlTree<T,F>::isSorted(arr, n)){
    throw NotSorted();
  }
  int i = 0;
  insertArrayToTreeAux(arr, n, i, this->root);
}

template<class T, class F>
void AuxFuncs::insertArrayToTreeAux(T* arr, int n, int& i, 
				 TreeNode<T,F>* root){
  if(!root || n == i){
    return;
  }
  insertArrayToTreeAux(arr, n, i, root->getLeft());
  if(n != i){
    root->setData(arr[i]);
    i++;
    insertArrayToTreeAux(arr, n, i,root->getRight());
  }
}

/************Orders**************/
template<class T, class F>
void AuxFuncs::preOrderAux(TreeNode<T,F>* node, T*& preOrdArr,int* i) {
  if (node == NULL) 
    return;
  preOrdArr[*i] = node->getData();
  *i=*i+1;
  preOrderAux(node->getLeft(), preOrdArr,i);
  
  preOrderAux(node->getRight(), preOrdArr,i);
  
}

template<class T, class F>
T* AvlTree<T,F>::preOrder() {
  if (this->treeSize == 0)
			return NULL;
  T* preOrdArr = new T[this->treeSize];
  int i=0;
  preOrderAux(this->root,preOrdArr,&i);
  return preOrdArr;
}

template<class T, class F>
void AuxFuncs::inOrderAux(TreeNode<T,F>* node, T*& inOrdArr,int* i) {
  if (node == NULL)
    return;
  inOrderAux(node->getLeft(), inOrdArr,i);
  inOrdArr[*i] = node->getData();
  *i=*i+1;
  inOrderAux(node->getRight(), inOrdArr,i);
}

template<class T, class F>
T* AvlTree<T,F>::inOrder() {
  if (this->treeSize == 0)
		return NULL;
  T* inOrdArr = new T[this->treeSize];
  int i=0;
  inOrderAux(this->root,inOrdArr,&i);
  return inOrdArr;
}


template<class T, class F>
void AuxFuncs::postOrderAux(TreeNode<T,F>* node, T*& postOrdArr, int* i) {
  if (node == NULL) 
    return;
  
  postOrderAux(node->getLeft(), postOrdArr,i);

  postOrderAux(node->getRight(), postOrdArr,i);
  
  postOrdArr[*i] = node->getData();
  *i=*i+1;
}

template<class T, class F>
T* AvlTree<T,F>::postOrder() {
  if (this->treeSize == 0)
		return NULL;
  T* postOrdArr = new T[this->treeSize];
  int i=0;
  postOrderAux(this->root,postOrdArr,&i);
  return postOrdArr;
}

template<class T, class F>
bool AuxFuncs::isLeaf(TreeNode<T,F>* node) {
  return node->getLeft() == NULL && node->getRight() == NULL;
}

/*This function returns the smallest value from right 
 *that is bigger than node's
 */
template<class T, class F>
TreeNode<T,F>* AuxFuncs::returnMinFromRight(TreeNode<T,F>* node) {
  if (node->getLeft() == NULL) {
    if (node->getRight() != NULL) {
      node->getRight()->setFather(node->getFather());
    }
    if (node->getFather()->getLeft() != NULL) {
      if ( *(node->getFather()->getLeft()) == *node ) {
	node->getFather()->setLeft(node->getRight());
      }
      else {
	node->getFather()->setRight(node->getRight());
      }  
    }
    else {
      node->getRight()->setFather(node->getFather());
      node->getFather()->setRight(node->getRight());
    }
    return node;
  }
  TreeNode<T,F>* replacement = returnMinFromRight(node->getLeft());
  //check rolling
  //switch between node and his father
  return replacement;
}

template<class T, class F>
int AuxFuncs::numOfChildren(TreeNode<T,F>* node) {
  return (node->getLeft()!= NULL) + (node->getRight() != NULL);
}


template<class T, class F>
void deleteIfLeaf(TreeNode<T,F>*& nodeTD) {
  if (nodeTD->getFather() != NULL) {
    if ( nodeTD->getFather()->getLeft() != NULL )
      if ( (*nodeTD->getFather()->getLeft()) == (*nodeTD) )
	nodeTD->getFather()->setLeft(NULL);
      else
	nodeTD->getFather()->setRight(NULL);	
    else
      nodeTD->getFather()->setRight(NULL);	
  }
  delete nodeTD;
  nodeTD = NULL;
}

/*This function deletes the received node. */
template<class T, class F>
void deleteIfHasOneChild(TreeNode<T,F>*& nodeTD) {
  TreeNode<T,F>* father = NULL;
  if (nodeTD->getFather() != NULL)
    father = nodeTD->getFather();
  TreeNode<T,F>* temp = nodeTD;
  if (nodeTD->getLeft() != NULL) {
    nodeTD->getLeft()->setFather(father);
    
    if (father != NULL) {
      if ( father->getLeft() != NULL )
	if ( (*father->getLeft()) == (*nodeTD) )
	  father->setLeft(nodeTD->getLeft());
	else
	  father->setRight(nodeTD->getLeft());
      else
	father->setRight(nodeTD->getLeft());
    }
    
    nodeTD = nodeTD->getLeft();
  }
  else {
    nodeTD->getRight()->setFather(father);
    
    if (father != NULL) {
      if ( father->getLeft() != NULL )
	if ( (*father->getLeft()) == (*nodeTD) )
	  father->setLeft(nodeTD->getRight());
	else
	  father->setRight(nodeTD->getRight());
      else
	father->setRight(nodeTD->getRight());
    }
    nodeTD = nodeTD->getRight();
  }
  delete temp;			
}

template<class T, class F>
void deleteIfHasTwoSons(TreeNode<T,F>*& nodeTD) {
  TreeNode<T,F>* replacement = returnMinFromRight(nodeTD->getRight());
  nodeTD->setData(replacement->getData());
  delete replacement;
}

/*nodeTD- node To Delete*/
template<class T, class F>
void AuxFuncs::removeSingle(TreeNode<T,F>*& nodeTD) {
  /*If the nodeTD is a leaf*/
  if (isLeaf(nodeTD)) {
    deleteIfLeaf(nodeTD);
    return;
  }
  /*if the nodeTD has only child*/
  if (numOfChildren(nodeTD) == 1) {
    deleteIfHasOneChild(nodeTD);
    return;
  }/*If has 2 children*/
  else {
    deleteIfHasTwoSons(nodeTD);
  }
}	

template<class T, class F>
void AuxFuncs::removeAux(TreeNode<T,F>** root,TreeNode<T,F>* nodeTD) {
  if (*root == NULL)
    throw NotFound();
  else if ( (*(*root)) > (*nodeTD) ) {
    TreeNode<T,F>* left = (*root)->getLeft();
    removeAux(&left, nodeTD);
  }
  else if ( (*(*root)) < (*nodeTD) ) {
    TreeNode<T,F>* right = (*root)->getRight();
    removeAux(&right, nodeTD);
  }
  else if (*(*root) == *nodeTD) {
    removeSingle(*root);
  }
  if (*root != NULL){
    (*root)->setHeight();
    rollCheck(*root);
  }
}

template<class T, class F>
void AvlTree<T,F>::remove(const T& data) {
  TreeNode<T,F>* nodeTD = new TreeNode<T,F>(data);
  try {
    removeAux(&this->root,nodeTD);
  }
  catch (NotFound& e) {
    delete nodeTD;
    throw NotFound();
  }
  delete nodeTD;
  this->treeSize--;
  if (root != NULL) {
    if(root->getFather()){
      root = root->getFather();
    }
  }
}

template<class T, class F>
T& AvlTree<T,F>::findMin() {
  return AuxFuncs::getMinAux(this->root);
}
template<class T, class F>
T& AvlTree<T,F>::findMax() {
  return AuxFuncs::getMaxAux(this->root);
}	
template<class T, class F>
void updateFathers(TreeNode<T,F>** node) {
	if ((*node)->getRight() != NULL)
			(*node)->getRight()->setFather(*node);
	if ((*node)->getLeft() != NULL)
			(*node)->getLeft()->setFather(*node);
	TreeNode<T,F>* left = (*node)->getLeft();
	if (left == NULL)
			return;
	else
		updateFathers(&left);
	TreeNode<T,F>* right =(*node)->getRight(); 
	if (right == NULL)
		return;
	else
		updateFathers(&right);
}
template<class T, class F>
AvlTree<T,F>& AvlTree<T,F>::operator=(const AvlTree<T,F>& avlTree) {
	if (&avlTree == this)
		return *this;
	treeTotalDestroy(this->root);
	if (avlTree.root == NULL)
		this->root = NULL;
	else
		this->root = new TreeNode<T,F>(*(avlTree.root));
	if (this->root != NULL) {
		this->root->setFather(NULL);
		updateFathers(&this->root);
	}
	this->treeSize = avlTree.treeSize;
	return *this;
}

template<class T, class F>
void AuxFuncs::rollCheck(TreeNode<T,F>* node){
  if (node->getBf() == 2 && node->getLeft()){
    int leftBf = node->getLeft()->getBf();
    if ( leftBf >= 0){
    //  std::cout << "LL" << std::endl;
      rollLL(node);
    }else if(leftBf == -1 && node->getLeft()){
    //  std::cout << "LR" << std::endl;
      rollLR(node);
    }
    else{
    //  std::cout <<"No Roll" << std::endl;
    }
  }else if(node->getBf() == -2 && node->getRight()){
    int rightBf = node->getRight()->getBf();
    if (rightBf <= 0){
    //  std::cout << "RR" << std::endl;
      rollRR(node);
    }else if(rightBf == 1 && node->getRight()){
    //   std::cout << "RL" << std::endl;
      rollRL(node);
    }else{
    //  std::cout <<"No Roll" << std::endl;
    }
  }else{
  //  std::cout <<"No Roll" << std::endl;
  }
}

template<class T, class F>
void AuxFuncs::rollLL(TreeNode<T,F>* node){
  TreeNode<T,F>* A = node->getLeft();
  node->setLeft(A->getRight());
  if(node->getLeft()){
    node->getLeft()->setFather(node);
  }
  A->setRight(node);
  A->setFather(node->getFather());
  if(A->getFather()){
    if((A->getFather()->getRight()) &&
        (*(A->getFather()->getRight()) == *node)){
      node->getFather()->setRight(A);
    }else{
      node->getFather()->setLeft(A);
    }
  }
  node->setFather(A);
  node->setHeight();
  A->setHeight();
}

template<class T, class F>
void AuxFuncs::rollRR(TreeNode<T,F>* node){
  TreeNode<T,F>* A = node->getRight();
  node->setRight(A->getLeft());
  if(node->getRight()){
    node->getRight()->setFather(node);
  }
  A->setLeft(node);
  A->setFather(node->getFather());
  if(A->getFather()){
      if( (A->getFather()->getRight()) &&
          (*(A->getFather()->getRight())) == *node){
        node->getFather()->setRight(A);
      }else{
        node->getFather()->setLeft(A);
      }
    }
  node->setFather(A);
  node->setHeight();
  A->setHeight();
}

template<class T, class F>
void AuxFuncs::rollLR(TreeNode<T,F>* node){
  TreeNode<T,F>* B = node->getLeft();
  rollRR(B);
  rollLL(node);
}

template<class T, class F>
void AuxFuncs::rollRL(TreeNode<T,F>* node){
  TreeNode<T,F>* B =node->getRight();
  rollLL(B);
  rollRR(node);
}


template<class T, class F>
bool AvlTree<T,F>::isSorted(T* arr, int n){
  for(int i = 1; i < n; i++){
    TreeNode<T,F> temp1(arr[i]), temp2(arr[i]);
    if(temp1 < temp2){
      return false;
    }
  }
  return true;
}

template<class T, class F>
T& AuxFuncs::getMaxAux(TreeNode<T,F>* node) {
  if (node->getRight() == NULL)
    return node->getData();
  return getMaxAux(node->getRight());
}

template<class T, class F>
T& AuxFuncs::getMinAux(TreeNode<T,F>* node) {
   if (node->getLeft() == NULL)
    return node->getData();
  return getMinAux(node->getLeft());
}

#endif
