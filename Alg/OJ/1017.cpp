#include <bits/stdc++.h>
using namespace std;
#define int long long

int merge_sort(vector<int> &a, vector<int> &temp, int left, int right)
{
    if (right - left <= 1)
        return 0;
    int mid = (left + right) / 2;
    int inv_count = merge_sort(a, temp, left, mid) + merge_sort(a, temp, mid, right);
    int i = left, j = mid, k = left;
    while (i < mid && j < right)
    {
        if (a[i] <= a[j])
            temp[k++] = a[i++];
        else
        {
            temp[k++] = a[j++];
            inv_count += mid - i; // a[i] > a[j]，且i之后都比a[j]大
        }
    }
    while (i < mid)
        temp[k++] = a[i++];
    while (j < right)
        temp[k++] = a[j++];
    for (int i = left; i < right; i++)
        a[i] = temp[i];
    return inv_count;
}

int count_inversions(vector<int> a)
{
    int n = a.size();
    vector<int> temp(n);
    return merge_sort(a, temp, 0, n);
}

void solve()
{
    int n;
    cin >> n;
    vector<int> edges(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> edges[i];
    cout << count_inversions(edges) << endl;
}

signed main()
{
    int t;
    cin >> t;
    while (t--)
        solve();
}