#include <iostream>
#include <vector>
using namespace std;
int main()
{
    vector<int> v;
    for (int i = 0; i < 5; i++)
        v.push_back(i);
    cout << v.size() << endl;
    for (vector<int>::iterator i = v.begin(); i != v.end(); i++)
        cout << *i << " ";
    cout << endl;
    return 0;
}