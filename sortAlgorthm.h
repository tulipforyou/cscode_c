#ifndef _SORTALGORITHM_H
#define _SORTALGORITHM_H

#include <iostream>
#include <vector>
using namespace std;

template <class T>
class sortAlgorithm
{
public:
    int insertSort(vector<T> &v); //直接插入排序
    int shellSort(vector<T> &v);  //希尔排序
    int bubbleSort(vector<T> &v); //冒泡排序
    void quickSort(vector<T> &v);
    vector<T> quickSort(vector<T> &v, int n, int begin, int end); //快速排序
    int selectSort(vector<T> &v);                           //选择排序
    void print(vector<T> &v);
};

template <class T>
int sortAlgorithm<T>::insertSort(vector<T> &v)
{
    int n = v.size();
    for (int i = 1; i < n; i++)
    {
        T tmp = v[i];
        int j;
        for (j = i - 1; j >= 0 && tmp < v[j]; j--)
            v[j + 1] = v[j];
        v[j + 1] = tmp;
    }
    print(v);
    return -1;
}

template <class T>
int sortAlgorithm<T>::shellSort(vector<T> &v)
{
    int n = v.size();
    for (int delta = n / 2; delta > 0; delta /= 2)
        for (int i = delta; i < n; i++)
        {
            T tmp = v[i];
            int j;
            for (j = i - delta; j >= 0 && tmp < v[j]; j -= delta)
                v[j + delta] = v[j];
            v[j + delta] = tmp;
        }
    print(v);
    return -1;
}

template <class T>
int sortAlgorithm<T>::bubbleSort(vector<T> &v)
{
    int n = v.size();
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (v[j] > v[j + 1])
            {
                T tmp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = tmp;
            }
        }
    }
    print(v);
    return -1;
}

template <class T>
void sortAlgorithm<T>::quickSort(vector<T> &v)
{
    int n = v.size();
    vector<T> vv=quickSort(v, v.size(), 0, v.size() - 1);
    for (int i = 0; i < vv.size(); i++)
        cout << vv[i] << " ";
    cout << endl;
}
template <class T>
vector<T> sortAlgorithm<T>::quickSort(vector<T> &v, int n, int begin, int end)
{
    if (begin >= 0 && begin < n && end >= 0 && end < n && begin < end)
    {
        int i = begin, j = end;
        T tmp = v[i]; //基准值
        while (i != j)
        {
            while (i < j && tmp <= v[j])
                j--;
            if (i < j)
                v[i++] = v[j];
            while (i < j && tmp >= v[i])
                i++;
            if (i < j)
                v[j--] = v[i];
        }
        v[i] = tmp;
        quickSort(v, n, begin, j - 1);
        quickSort(v, n, i + 1, end);
    }
    return v;
}

template <class T>
int sortAlgorithm<T>::selectSort(vector<T> &v)
{
    int n = v.size();
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
            if (v[j] < v[min])
                min = j;
        if (min != i)
        {
            T tmp = v[i];
            v[i] = v[min];
            v[min] = tmp;
        }
    }
    print(v);
    return -1;
}

template <class T>
void sortAlgorithm<T>::print(vector<T> &v)
{
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;
}

#endif