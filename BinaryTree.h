/*
Designed by sch;
time:2019.10.17
本文件用于二叉树类的声明
*/
#ifndef _BINARYTREE_H
#define _BINARYTREE_H

#include <iostream>
#include "BinaryNode.h"
using namespace std;

template <class T>
class BinaryTree
{
public:
    BinaryNode<T> *root;                        //根结点
    BinaryTree();                               //构造空二叉树
    BinaryTree(T preList[], int n);             //以表明空子树的先根序列构造二叉树
    BinaryTree(T preList[], T inList[], int n); //以表明空子树的先根和中根序列构造二叉树

    bool empty();                                                        //判空
    friend ostream &operator<<(ostream &out, BinaryTree<T> &);           //输出先根序列,重载<<运算符，使之可以输出BinaryTree型数据
    void inOrder();                                                      //输出中根序列
    void postOrder();                                                    //输出后跟序列
    void insert(T x);                                                    //插入元素X作为根结点
    BinaryNode<T> *insert(BinaryNode<T> *p, T x, bool leftChild = true); //插入X作为P的孩子结点
    void remove(BinaryNode<T> *parent, bool leftChild);                  //删除parent结点的左或右子树
    void remove();                                                       //删除二叉树
    int count(BinaryNode<T> *p);                                         //返回二叉树结点数
    int height(BinaryNode<T> *p);                                        //返回二叉树高度
    BinaryNode<T> *search(T key);                                        //先根遍历首次出现KEY的结点，T重载==
    BinaryNode<T> *parent(BinaryNode<T> *node);                          //返回NODE的父结点
    void levelOrder();                                                   //层次遍历二叉树
    int level(T key);                                                    //返回KEY所在层
    bool operator==(BinaryTree<T> &btree);                               //重载==，比较两个二叉树是否相等
    BinaryTree(BinaryTree<T> &btree);                                    //拷贝构造函数，深拷贝
    BinaryTree<T> &operator=(BinaryTree<T> &btree);                      //重载=赋值运算符
    ~BinaryTree();
private:
    void preOrder(BinaryNode<T> *p);                   //先根遍历以P为根的子树
    void inOrder(BinaryNode<T> *p);                    //中根遍历以P为根的子树
    void postOrder(BinaryNode<T> *p);                  //后根遍历以P为根的子树
    void remove(BinaryNode<T> *p);                     //删除以P为根的子树
    BinaryNode<T> *create(T preList[], int n, int &i); //以标明空子树的先根遍历序列创建子树
};

template <class T>
BinaryTree<T>::BinaryTree()
{
    this->root = NULL;
}

template <class T>
BinaryTree<T>::BinaryTree(T preList[], int n) 
{
    int i=0;
    this->root=this->create(preList,n,i);
}

template <class T>
bool BinaryTree<T>::empty() //判空
{
    return this->root = NULL;
}

template <class T>
ostream &operator<<(ostream &out, BinaryTree<T> &btree)
{
    out << "先根次序遍历：" << endl;
    btree.preOrder(btree.root);
    out << endl;
    return out;
}
template <class T>
void BinaryTree<T>::preOrder(BinaryNode<T> *p)
{
    if (p == NULL)
        cout << "#";
    else
    {
        cout << p->data << " ";
        preOrder(p->left);
        preOeder(p->right);
    }
}

template <class T>
void BinaryTree<T>::inOrder()
{
    cout << "中根次序遍历：" << endl;
    this->inOrder(root);
    cout << endl;
}
template <class T>
void BinaryTree<T>::inOrder(BinaryNode<T> *p)
{
    if (p != NULL)
    {
        inOrder(p->left);
        cout << p->data << " ";
        inOrder(p->right);
    }
}

template <class T>
void BinaryTree<T>::postOrder()
{
    cout << "后跟次序遍历：" << endl;
    this->postOrder(root);
    cout << endl;
}
template <class T>
void BinaryTree<T>::postOrder(BinaryNode<T> *p)
{
    if (p != NULL)
    {
        postOrder(p->left);
        postOrder(p->right);
        cout << p->data << " ";
    }
}

template <class T>
int BinaryTree<T>::count(BinaryNode<T> *p)
{
    static int i = 0;
    if (p != NULL)
    {
        ++i;
        count(p->left);
        count(p->right);
    }
    return i;
}

template <class T>
int BinaryTree<T>::height(BinaryNode<T> *p)
{
    static int left=0;
    static int right=0;
    if(p!=NULL)
    {
        left=height(p->left);
        right=height(p->right);
    }
    else
    {
        return 0;
    }
    return left>right?(left+1):(right+1);
}

template <class T>
void BinaryTree<T>::insert(T x)
{
    this->root=new BinaryNode<T>(x,this->root,NULL);
}

template <class T>
BinaryNode<T> *insert(BinaryNode<T> *p, T x, bool leftChild)
{
    if(p==NULL)return NULL;
    if(leftChild)
        return p->left=new BinaryNode<T>(x,p->left,NULL);
    return p->right=new BinaryNode<T>(x,NULL,p->right);
}

template <class T>
void BinaryTree<T>::remove(BinaryNode<T> *parent, bool leftChild)
{
    if(parent!=NULL)
    {
        if(leftChild)
        {
            remove(parent->left);
            parent->left=NULL;
        }
        else
        {
            remove(parent->right);
            parent->right=NULL;
        }
        
    }
}

template <class T>
void BinaryTree<T>::remove(BinaryNode<T> *p)
{
    if(p!=NULL)
    {
        remove(p->left);
        remove(p->right);
        delete p;
    }
}

template <class T>
void BinaryTree<T>::remove()
{
    this->remove(root);
}

template<class T>
BinaryNode<T> *create(T preList[], int n, int &i)
{
    BinaryNode<T>*p=NULL;
    if(i<n)
    {
        T len=preList[i];
        i++;
        if(len!=NULL)
        {
            p=new BinaryNode<T>(len);
            p->left=create(preList,n,i);
            p->right=create(preList,n,i);
        }
    }
    return p;
}

template<class T>
BinaryTree<T>::~BinaryTree()
{
    this->remove(root);
}

#endif