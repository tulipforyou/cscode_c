/*
Designed by sch
time:2019.10.18
本文件用于查找算法测试用例
*/
#ifndef _FINDALGORITHM_H
#define _FINDALGORITHM_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "BinaryTree.h"
using namespace std;

template <class T>
class findAlgorithm
{
public:
    int binarySearch(T key, vector<T> &v); //二分查找（顺序存储，数据有序）

    /*bool operator==(findAlgorithm &test);
    bool operator<(findAlgorithm &test);*/

private:
    int count(vector<T> &v);
    int binarySearch(T key, vector<T> &v, int begin, int end);
};

/********************************二分查找************************************/
template <class T>
int findAlgorithm<T>::binarySearch(T key, vector<T> &v)
{
    return binarySearch(key, v, 0, this->count(v) - 1);
}

template <class T>
int findAlgorithm<T>::count(vector<T> &v)
{
    int i = 0;
    typename vector<T>::iterator it = v.begin();
    for (typename vector<T>::iterator it = v.begin(); it != v.end(); it++)
        i += 1;
    return i;
}

template <class T>
int findAlgorithm<T>::binarySearch(T key, vector<T> &v, int begin, int end)
{
    static int i = 0;
    while (begin <= end)
    {
        int mid = (begin + end) / 2;
        if (v[mid] == key)
        {
            // return mid;
            cout << "查找值位于： " << mid << endl;
            i += 1;
            return i;
        }
        if (key < v[mid])
        {
            end = mid - 1;
            i += 1;
        }
        else
        {
            begin = mid + 1;
            i += 1;
        }
        cout << "第" << i << "次比较:";
        cout << begin << " " << end << endl;
    }
    return -1;
}

/*******************************二叉排序树查找************************************/
template <class T>
class binarySortTree : public BinaryTree<T>
{
public:
    binarySortTree() {}
    void CreatebinarySortTree(vector<T> &v, int n);
    T *search(T key);
    void insert(T key);
    void remove(T key);
};

template <class T>
void binarySortTree<T>::CreatebinarySortTree(vector<T> &v, int n)
{
    for (int i = 0; i < n; i++)
        this->insert(v[i]);
}

template <class T>
T *binarySortTree<T>::search(T key)
{
    BinaryNode<T> *p = this->root;
    while (p != NULL && p->data != key)
    {
        if (key < p->data)
            p = p->left;
        else
            p = p->right;
    }
    cout<<"查找值的地址是："<<&p->data<<endl;
    cout<<"查找值是："<<p->data<<endl;
    return p == NULL ? NULL : &p->data;
}

template <class T>
void binarySortTree<T>::insert(T key)
{
    if (this->root == NULL)
        this->root = new BinaryNode<T>(key);
    BinaryNode<T> *p = this->root, *parent = NULL;
    while (p != NULL)
    {
        if (p->data == key)
            return; //直接返回，不插入重复值
        parent = p;
        if (key < p->data)
            p = p->left;
        else
            p = p->right;
    }
    if (key < parent->data)
        parent->left = new BinaryNode<T>(key);
    else
        parent->right = new BinaryNode<T>(key);
}

#endif
