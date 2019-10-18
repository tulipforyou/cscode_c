/*
Designed by sch;
time:2019.10.17
本文件用于二叉树的二叉链表结点类的声明
*/
#ifndef _BINARYNODE_H
#define _BINARYNODE_H

#include<iostream>
using namespace std;

template <class T>
class BinaryNode
{
public:
    T data;                      //数据域
    BinaryNode<T> *left, *right; //左右孩子结点

    BinaryNode(T data, BinaryNode<T> *left = NULL, BinaryNode<T> *right = NULL)
    {
        this->data=data;
        this->left=left;
        this->right=right;
    }
};

#endif