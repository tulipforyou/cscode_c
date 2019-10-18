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

/*******************************分块查找************************************/

#endif
