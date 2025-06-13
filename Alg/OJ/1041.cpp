#include <bits/stdc++.h>
using namespace std;
#define int long long
double findMedianSortedArrays(const vector<int> &A, const vector<int> &B)
{
    int m = A.size(), n = B.size();

    // 保证 A 是较短的数组
    if (m > n)
        return findMedianSortedArrays(B, A);

    int imin = 0, imax = m, halfLen = (m + n + 1) / 2;
    while (imin <= imax)
    {
        int i = (imin + imax) / 2;
        int j = halfLen - i;

        if (i < m && B[j - 1] > A[i])
            imin = i + 1; // i太小
        else if (i > 0 && A[i - 1] > B[j])
            imax = i - 1; // i太大
        else
        {
            // i正好
            int maxLeft = 0;
            if (i == 0)
                maxLeft = B[j - 1];
            else if (j == 0)
                maxLeft = A[i - 1];
            else
                maxLeft = max(A[i - 1], B[j - 1]);

            if ((m + n) % 2 == 1)
                return maxLeft;

            int minRight = 0;
            if (i == m)
                minRight = B[j];
            else if (j == n)
                minRight = A[i];
            else
                minRight = min(A[i], B[j]);

            return (maxLeft + minRight) / 2.0;
        }
    }

    return 0.0; // 不会执行到这里
}

signed main()
{
    int nums;
    cin >> nums;

    while (nums--)
    {
        int n, m;
        cin >> n >> m;
        vector<int> nums1(n), nums2(m);

        for (int i = 0; i < n; ++i)
            cin >> nums1[i];
        for (int i = 0; i < m; ++i)
            cin >> nums2[i];

        double result = findMedianSortedArrays(nums1, nums2);
        cout << result << endl;
    }

    return 0;
}
