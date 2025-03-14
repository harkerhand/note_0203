#include <bits/stdc++.h>
using namespace std;
#define int long long

// 归并排序并统计逆序对
int mergeAndCount(vector<double> &arr, int left, int mid, int right)
{
    vector<double> temp(right - left + 1); // 临时数组
    int i = left, j = mid + 1, k = 0;
    int count = 0;

    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
        { // 如果左边元素小于等于右边，不构成逆序对
            temp[k++] = arr[i++];
        }
        else
        { // 发生逆序
            temp[k++] = arr[j++];
            count += (mid - i + 1); // 左边 i 及其之后的元素都比当前 j 大
        }
    }

    // 复制剩余元素
    while (i <= mid)
        temp[k++] = arr[i++];
    while (j <= right)
        temp[k++] = arr[j++];

    // 复制回原数组
    for (int p = 0; p < k; ++p)
    {
        arr[left + p] = temp[p];
    }

    return count;
}

// 归并排序框架，递归统计逆序对
int mergeSortAndCount(vector<double> &arr, int left, int right)
{
    if (left >= right)
        return 0; // 递归终止

    int mid = left + (right - left) / 2;
    int count = 0;

    count += mergeSortAndCount(arr, left, mid);      // 统计左半部分逆序对
    count += mergeSortAndCount(arr, mid + 1, right); // 统计右半部分逆序对
    count += mergeAndCount(arr, left, mid, right);   // 统计跨越两部分的逆序对

    return count;
}

signed main()
{
    vector<double> arr = {7.5, 3.2, 5.1, 2.8, 6.4}; // 示例数据
    int inversions = mergeSortAndCount(arr, 0, arr.size() - 1);

    cout << "逆序对个数: " << inversions << endl;
    return 0;
}
