## 1.1

- 将数组 $X$ 和 $Y$ 分为两部分：
   - 选择 $X$ 和 $Y$ 的中间元素 $X[\frac{n}{2}]$ 和 $Y[\frac{n}{2}]$。
   - 比较这两个中位数：
     - 如果 $X[\frac{n}{2}] < Y[\frac{n}{2}]$，则可以排除数组 $X$ 的前半部分和数组 $Y$ 的后半部分。因为这部分中的所有元素都不可能是最终的中位数。
     - 如果 $X[\frac{n}{2}] > Y[\frac{n}{2}]$，则排除数组 $X$ 的后半部分和数组 $Y$ 的前半部分。
 - 继续在剩余部分中递归进行这个过程，直到找到中位数。

**边界条件**：
   - 如果某个数组只剩下一个元素，那么直接在另一个数组中找到对应的中位数。

### 具体实现：

```cpp
double findMedianSortedArrays(const vector<int>& X, const vector<int>& Y) {
    int n = X.size();
    if (n == 0) return -1;  // 处理空数组的情况
    int left = 0, right = n - 1;
    while (left <= right) {
        int midX = left + (right - left) / 2;
        int midY = (n - 1) - midX;  // 对应Y中的位置
        // 比较中位数
        if (X[midX] < Y[midY]) {
            left = midX + 1;  // 需要排除 X 的前半部分
        } else if (X[midX] > Y[midY]) {
            right = midX - 1; // 需要排除 Y 的后半部分
        } else {
            return X[midX];  // 找到了中位数
        }
    }
    return -1;  // 理论上不会走到这里
}
```
---

## 1.2

1. **核心思想**：
   - 利用二分查找找到两个数组的“分割点”，使得合并后的数组的左半部分和右半部分的元素个数相等（或者左半部分比右半部分多一个元素）。然后通过这个分割点确定中位数。
   - 假设我们在数组 $ X $ 上进行二分查找，设当前的分割点为 $ i $（在 $ X $ 中），那么在数组 $ Y $ 中，另一个分割点 $ j $ 可以通过以下关系确定：  
     $$
     i + j = \left\lfloor \frac{m + n + 1}{2} \right\rfloor
     $$
     这里，$\frac{m + n + 1}{2}$ 表示合并后数组的左半部分的大小（如果总元素数是奇数，左半部分比右半部分多一个元素）。

2. **二分查找的条件**：
   - 对于选定的分割点 $ i $，我们要求满足：
     - $ X[i-1] \leq Y[j] $（左半部分的最大值小于右半部分的最小值）
     - $ Y[j-1] \leq X[i] $（右半部分的最大值小于左半部分的最小值）
   - 如果这两个条件不成立，说明需要调整分割点（在 $ X $ 中选择更大的或更小的分割点）。

3. **处理边界情况**：
   - 需要特别处理 $ i = 0 $ 或 $ i = m $ 的情况，这意味着某一侧的数组已经没有元素了，处理时要特别注意。

### 具体实现：

```cpp
double findMedianSortedArrays(const vector<int>& X, const vector<int>& Y) {
    int m = X.size();
    int n = Y.size();
    // 确保 X 是较小的那个数组
    if (m > n) {
        return findMedianSortedArrays(Y, X);
    }
    int left = 0, right = m;
    while (left <= right) {
        int i = left + (right - left) / 2; // X 的分割点
        int j = (m + n + 1) / 2 - i; // Y 的分割点
        
        // 边界情况的处理
        int X_left = (i == 0) ? INT_MIN : X[i - 1];
        int X_right = (i == m) ? INT_MAX : X[i];
        int Y_left = (j == 0) ? INT_MIN : Y[j - 1];
        int Y_right = (j == n) ? INT_MAX : Y[j];
        // 检查分割点是否满足条件
        if (X_left <= Y_right && Y_left <= X_right) {
            // 找到正确的分割点
            if ((m + n) % 2 == 0) {
                // 偶数长度，返回中间两个数的平均值
                return (max(X_left, Y_left) + min(X_right, Y_right)) / 2.0;
            } else {
                // 奇数长度，返回左半部分的最大值
                return max(X_left, Y_left);
            }
        } else if (X_left > Y_right) {
            // X 的分割点太大，调整左边界
            right = i - 1;
        } else {
            // X 的分割点太小，调整右边界
            left = i + 1;
        }
    }
    return -1; // 理论上不会到达这里
}
```

## 2

1. **分割建筑物**：将所有建筑物按左边界 $ a_i $ 进行排序。每次从建筑物集合中选择一半来递归计算天际线。

2. **合并天际线**：
   - 对于左右两部分的天际线，进行合并时，我们遍历左右两边的建筑物起始位置，动态地计算当前的最大高度。
   - 每当高度发生变化时，记录一个关键点。

3. **终止条件**：
   只剩下一个建筑时，直接返回其天际线。

### 具体实现：

```cpp
vector<Contour> mergeContour(const vector<Contour> &b1, const vector<Contour> &b2)
{
    vector<Contour> res;
    int i = 0, j = 0;
    int h1 = 0, h2 = 0;
    while (i < b1.size() && j < b2.size())
    {
        if (b1[i].x < b2[j].x)
        {
            int x = b1[i].x;
            h1 = b1[i].h;
            int maxh = max(h1, h2);
            if (res.size() == 0 || res.back().h != maxh)
                res.push_back({x, maxh});
            i++;
        }
        else
        {
            int x = b2[j].x;
            h2 = b2[j].h;
            int maxh = max(h1, h2);
            if (res.size() == 0 || res.back().h != maxh)
                res.push_back({x, maxh});
            j++;
        }
    }
    while (i < b1.size())
    {
        if (res.size() == 0 || res.back().h != b1[i].h)
            res.push_back(b1[i++]);
    }
    while (j < b2.size())
    {
        if (res.size() == 0 || res.back().h != b2[j].h)
            res.push_back(b2[j++]);
    }

    return res;
}

vector<Contour> getContour(const vector<Building> &buildings, int l, int r)
{
    if (l == r)
    {
        return {{buildings[l].x1, buildings[l].h}, {buildings[l].x2, 0}};
    }
    int m = (l + r) / 2;
    auto b1 = getContour(buildings, l, m);
    auto b2 = getContour(buildings, m + 1, r);
    return mergeContour(b1, b2);
}
```

## 3

- 递归地将数组分成两半，直到每个子数组的长度为 1。
- 计算跨越中间的最大子数组和。
- 返回左半部分、右半部分和跨越中间的最大子数组和中的最大值。

### **分治法实现**

```cpp
int maxSubArray(vector<int> &nums)
{
    // 分治
    int n = nums.size();
    if (n == 1)
        return nums[0];
    int mid = n / 2;
    vector<int> left(nums.begin(), nums.begin() + mid);
    vector<int> right(nums.begin() + mid, nums.end());
    int left_max = maxSubArray(left);
    int right_max = maxSubArray(right);
    // 跨越中点的最大子序列
    int left_sum = INT_MIN;
    int right_sum = INT_MIN;
    int sum = 0;
    for (int i = mid - 1; i >= 0; i--)
    {
        sum += nums[i];
        left_sum = max(left_sum, sum);
    }
    sum = 0;
    for (int i = mid; i < n; i++)
    {
        sum += nums[i];
        right_sum = max(right_sum, sum);
    }
    int cross_max = left_sum + right_sum;
    return max(max(left_max, right_max), cross_max);
}
```


**也可以 $O(n)$**

- 从左到右遍历数组，记录当前子数组的和 `sum`
- 如果 `sum` 为正，则继续累加后面的元素，因为正数会增加总和
- 如果 `sum` 为负，则将 `sum` 重置为 0，因为负数会减小总和，从当前位置重新开始
- 每次更新最大子数组和 `max_sum`
  
### **贪心实现**

```cpp
int maxSubArray(vector<int> &nums)
{
    int n = nums.size();
    int max_sum = INT_MIN;
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += nums[i];
        max_sum = max(max_sum, sum);
        if (sum < 0)
            sum = 0;
    }
    return max_sum;
}
```

## 4

二分查找，找到 `a[i] > a[i+1]` 的 i 即可

### **具体实现**

```cpp
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
```

## 5

1. **拆分问题**：
   - 将集合 $ S $ 拆分成左右两个子集 $ S_1 $ 和 $ S_2 $。
   - 递归检查是否在 $ S_1 $ 或 $ S_2 $ 中找到两个数的和等于 $ x $。
   - 如果不行，则检查是否可以通过 **跨两个子集的元素之和** 得到 $ x $。

2. **合并结果**：
   - 计算 $ S_1 $ 和 $ S_2 $ 各自的所有可能元素和，并存储一个集合用于快速查找。

3. **终止条件**：
   - 当子集大小为 1 时，直接返回 `false`（因为一个数无法形成和）。

---

### **具体实现**
```cpp
bool hasPairWithSum(const std::vector<double>& S, int left, int right, double x) {
    if (right - left <= 1) return false; // 递归终止：少于两个元素

    int mid = left + (right - left) / 2;
    
    // 递归检查左半部分和右半部分
    if (hasPairWithSum(S, left, mid, x) || hasPairWithSum(S, mid, right, x))
        return true;

    // 使用哈希集合存储左半部分的元素
    std::unordered_set<double> leftSet;
    for (int i = left; i < mid; ++i) {
        leftSet.insert(S[i]);
    }

    // 检查右半部分的元素是否能与左半部分的某个元素求和为 x
    for (int i = mid; i < right; ++i) {
        if (leftSet.contains(x - S[i])) {
            return true;
        }
    }

    return false;
}
```

---

## 6

统计归并排序的调整次数即可


### **具体实现**

```cpp
int mergeAndCount(vector<double> &arr, int left, int mid, int right)
{
    vector<double> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    int count = 0;
    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
        {
            temp[k++] = arr[j++];
            count += (mid - i + 1); // 左边 i 及其之后的元素都比当前 j 大
        }
    }
    // 复制剩余元素
    while (i <= mid)
        temp[k++] = arr[i++];
    while (j <= right)
        temp[k++] = arr[j++];

    for (int p = 0; p < k; ++p)
    {
        arr[left + p] = temp[p];
    }

    return count;
}

int mergeSortAndCount(vector<double> &arr, int left, int right)
{
    if (left >= right)
        return 0; // 递归终止
    int mid = left + (right - left) / 2;
    int count = 0;
    count += mergeSortAndCount(arr, left, mid);
    count += mergeSortAndCount(arr, mid + 1, right);
    count += mergeAndCount(arr, left, mid, right);
    return count;
}
```