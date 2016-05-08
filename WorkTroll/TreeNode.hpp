/*
 * AvlTree.hpp
 *
 *  Created on: 23 Nov 2015
 *      Author: Daniel
 */

#ifndef TREENODE_HPP_
#define TREENODE_HPP_
#define NULL 0
template<class T, class F>
class TreeNode {
private:
  T data;
  TreeNode<T,F>* leftSon;
  TreeNode<T,F>* rightSon;
  TreeNode<T,F>* father;
  int height;
  F compFunc;

public:
  explicit  TreeNode<T,F>();
  TreeNode<T,F>(const T&);
  TreeNode<T,F>(const TreeNode<T,F>&);

  T& getData();
  TreeNode<T,F>* getLeft();
  TreeNode<T,F>* getRight();
  TreeNode<T,F>* getFather();
  int getHeight();

  void setData(const T& data);
  void setLeft(TreeNode<T,F>* left);
  void setRight(TreeNode<T,F>* right);
  void setFather(TreeNode<T,F>* father);
  void setHeight();
  
  bool operator==(const TreeNode<T,F>&) const;
  bool operator!=(const TreeNode<T,F>&) const;
  bool operator<(const TreeNode<T,F>&) const;
  bool operator<=(const TreeNode<T,F>&) const;
  bool operator>(const TreeNode<T,F>&) const;  
  bool operator>=(const TreeNode<T,F>&) const;
  
  int getBf();
  bool isHeightBalance();

  int calcHeight();
};

/*******************************************************************************
 *     			Constructors and Destroyer                             *
 *******************************************************************************/

template<class T, class F>
TreeNode<T,F>::TreeNode(): data(), leftSon(), rightSon(), father(),
			   height(0), compFunc(){
}

template<class T, class F>
TreeNode<T,F>::TreeNode(const T& data): data(data) , leftSon(), 
	rightSon(), father(), height(0), compFunc(){
}

template<class T, class F>
TreeNode<T,F>::TreeNode(const TreeNode<T,F>& tr): data(tr.data),
	 leftSon(), rightSon(), father(), height(tr.height), compFunc() {
	if (tr.leftSon != NULL)
		this->leftSon = new TreeNode<T,F>(*tr.leftSon);
	else
		this->leftSon = NULL;
	if (tr.rightSon != NULL)
		this->rightSon = new TreeNode<T,F>(*tr.rightSon);
	else
		this->rightSon = NULL;
}


/*******************************************************************************
 *      		 Gets and Sets			                       *
 *******************************************************************************/

template<class T, class F>
T& TreeNode<T,F>::getData() {
  return data;
}

template<class T, class F>
TreeNode<T,F>* TreeNode<T,F>::getLeft() {
  return leftSon;
}

template<class T, class F>
TreeNode<T,F>* TreeNode<T,F>::getRight() {
  return rightSon;
}

template<class T, class F>
TreeNode<T,F>* TreeNode<T,F>::getFather() {
  return father;
}

template<class T, class F>
int TreeNode<T,F>::getHeight() {
  setHeight();
  return height;
}

template<class T, class F>
void TreeNode<T,F>::setData(const T& data) {
  this->data=data;
}

template<class T, class F>
void TreeNode<T,F>::setLeft(TreeNode<T,F>* left) {
  this->leftSon = left;
  this->setHeight();
}

template<class T, class F>
void TreeNode<T,F>::setRight(TreeNode<T,F>* right) {
  this->rightSon = right;
  this->setHeight();
}

template<class T, class F>
void TreeNode<T,F>::setFather(TreeNode<T,F>* father) {
  this->father = father;
}

template<class T, class F>
void TreeNode<T,F>::setHeight(){
  int leftH = 0, rightH = 0;
  if ( !this->leftSon && !this->rightSon){
    this->height = 0;
    return;
  }  
  if (this->leftSon){
    leftH = this->leftSon->height;
  }
  if (this->rightSon){
    rightH = this->rightSon->height;
  }
  if (leftH > rightH){
    this->height = leftH + 1;
  }
  else{
    this->height = rightH + 1;
  }
}


/*******************************************************************************
 *        		    Comparison Functions                               *
 *******************************************************************************/

template<class T, class F>
bool TreeNode<T,F>::operator<(const TreeNode<T,F>& node) const{
  return compFunc(this->data, node.data);
}

template<class T, class F>
bool TreeNode<T,F>::operator>(const TreeNode<T,F>& node) const{
  return compFunc(node.data, this->data);
}

template<class T, class F>
bool TreeNode<T,F>::operator==(const TreeNode<T,F>& node) const{
  return ((!(node < (*this))) && (!(*this < node)));
}

template<class T, class F>
bool TreeNode<T,F>::operator!=(const TreeNode<T,F>& node) const{
  return !((*this) == node);
}

template<class T, class F>
bool TreeNode<T,F>::operator>=(const TreeNode<T,F>& node) const{
  return !((*this) < node);
}

template<class T, class F>
bool TreeNode<T,F>::operator<=(const TreeNode<T,F>& node) const{
  return !(node < (*this));
}



/*******************************************************************************
 *        		      	BF Functions	                               *
 *******************************************************************************/

template<class T, class F>
int TreeNode<T,F>::getBf() {
  int leftH = 0, rightH = 0;
  if (this->leftSon != NULL){
    leftH = 1 + (this->leftSon)->height;
  }
  if (this->rightSon != NULL){
    rightH = 1 + (this->rightSon)->height;
  }
  return (leftH - rightH);
}

template<class T, class F>
bool TreeNode<T,F>::isHeightBalance() {
  int diff = this->getBf();
  if (diff < 0) {
    diff = diff * (-1);
  }
  return (diff < 1);
}


template<class T, class F>
void treeTotalDestroy(TreeNode<T,F>* root) {
	if (root==NULL) {
		return;
	}
  if (root->getLeft()  != NULL) {
    treeTotalDestroy(root->getLeft());
  }
  if (root->getRight()  != NULL) {
    treeTotalDestroy(root->getRight());
  }
  delete root;
}

template<class T, class F>
static int calcHeightAux(TreeNode<T,F>* root){
  if(root == NULL){
    return -1;
  }
  int leftH = calcHeightAux(root->getLeft());
  int rightH = calcHeightAux(root->getRight());
  if (leftH > rightH){
    return leftH + 1;
  }
  return rightH + 1;
}

template<class T, class F>
int TreeNode<T,F>::calcHeight(){
  return calcHeightAux(this);
}

#endif /* AVLTREE_HPP_ */
