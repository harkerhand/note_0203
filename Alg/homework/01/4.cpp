#include <bits/stdc++.h>
using namespace std;
#define int long long

int findCount(vector<int> &a)
{
    int n = a.size();
    int left = 0, right = n - 1;
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (a[mid] <= a[mid + 1])
            right = mid;
        else if (a[mid] > a[mid + 1])
            left = mid + 1;
    }
    return left;
}

signed main()
{
    vector<int> a = {1, 2, 3, 4, 5, 6, -4, -3, -2, -1, 0};
    cout << findCount(a) << endl;
    vector<int> b = {10, 11, 11, 1, 1, 3, 4, 5, 6, 7, 8, 9};
    cout << findCount(b) << endl;
    return 0;
}