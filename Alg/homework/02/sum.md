## 1

**定义** `dp[i][j][k]` 表示从 `i` 到 `j` 的子数组，使用 `k` 个乘号能得到的最大值。

**状态转移方程**：
- 在 `i~j` 之间选择一个 `m` 作为分割点：
  - 若 `m` 处是 `+`，则：
    $$
    dp[i][j][k] = \max(dp[i][m][k'] + dp[m+1][j][k-k'])
    $$
  - 若 `m` 处是 `*`，则：
    $$
    dp[i][j][k] = \max(dp[i][m][k'] * dp[m+1][j][k-k'-1])
    $$
  - 其中 `0 ≤ k' ≤ k`，`0 ≤ k-k' ≤ k`，并且 `k-k'-1` 确保 `*` 号数量正确。

**边界条件**：
- `dp[i][i][0] = v[i]` （只有一个数时，无符号，只能是它本身）


### **代码实现**
```cpp
int maxExpressionValue(const vector<int> &nums, int K)
{
    int N = nums.size();
    vector<vector<vector<int>>> dp(N, vector<vector<int>>(N, vector<int>(K + 1, 0)));
    // 初始化dp[i][i][0]，即单个数的值
    for (int i = 0; i < N; ++i)
    {
        dp[i][i][0] = nums[i];
    }
    // 枚举区间长度 len = j - i
    for (int len = 1; len < N; ++len)
    {
        for (int i = 0; i + len < N; ++i)
        {
            int j = i + len;
            for (int k = 0; k <= K; ++k)
            {
                int maxVal = numeric_limits<int>::min();
                // 选一个 m 作为分割点(右侧切分)
                for (int m = i; m < j; ++m)
                {
                    for (int k1 = 0; k1 <= k; ++k1)
                    {
                        if (k1 < k)
                        { // 乘号用完 试一下乘号
                            maxVal = max(maxVal, dp[i][m][k1] * dp[m + 1][j][k - k1 - 1]);
                        }
                        // 加号情况
                        maxVal = max(maxVal, dp[i][m][k1] + dp[m + 1][j][k - k1]);
                    }
                }
                dp[i][j][k] = maxVal;
            }
        }
    }
    return dp[0][N - 1][K];
}
```

---

## 2

设 `dp[i]` 表示前 `i` 个元素的最优划分，使得满足条件的子序列中最大值的和最小。

### **状态转移方程**
我们尝试在 `j` 处划分 `i` 个元素，即：
$$
dp[i] = \min_{j < i} (dp[j] + \max(a_{j+1}, ..., a_i))
$$
其中：
- `dp[j]` 表示前 `j` 个元素的最优解，
- $a_{j+1}, ..., a_i$ 形成一个新的子序列，最大值为 $\max(a_{j+1}, ..., a_i)$，
- 需要保证 $sum(a_{j+1}, ..., a_i) \leq B$。

**边界条件：**
- `dp[0] = 0`（表示没有元素时，最大值和为 0）。
- `dp[i] = ∞` 初始化，以便在 `min` 计算时更新最优值。

---

## **代码实现**
```cpp
int minMaxSum(vector<int> &nums, int B)
{
    int N = nums.size();
    vector<int> dp(N + 1, 1e9 + 7);
    dp[0] = 0;
    dp[1] = nums[1];
    for (int i = 2; i <= N; i++)
    {
        int sum = 0, mx = 0;
        for (int j = i; j > 0; --j)
        {
            sum += nums[j - 1];
            mx = max(mx, nums[j - 1]);
            if (sum > B)
                break;
            dp[i] = min(dp[i], dp[j - 1] + mx);
        }
    }
    return dp[N];
}
```

---

## 3

- 设 `f[u][0]` 表示以 `u` 为根的子树中，**当 `u` 为白色时，最大的黑色节点数**。
- 设 `f[u][1]` 表示以 `u` 为根的子树中，**当 `u` 为黑色时，最大的黑色节点数**。
- 对于某个节点 `u`，如果 `u` 为黑色，那么它的所有子节点必须是白色，因此：
  $$
  f[u][1] = 1 + \sum_{v \in \text{children}(u)} f[v][0]
  $$
- 如果 `u` 为白色，它的子节点可以是黑色或白色：
  $$
  f[u][0] = \sum_{v \in \text{children}(u)} \max(f[v][0], f[v][1])
  $$
- **最终答案**：`max(f[r][0], f[r][1])`，其中 `r` 是根节点。

---

## **代码实现**
```cpp
int dps(TreeNode *root, bool black)
{
    if (root == nullptr)
        return 0;
    if (black)
    {
        int sum = 0;
        for (auto child : root->children)
        {
            sum += dps(child, false);
        }
        return sum + 1;
    }

    int sum = 0;
    for (auto child : root->children)
    {
        sum += max(dps(child, true), dps(child, false));
    }
    return sum;
}
```

---

## 4

设 `dp[i]` 表示前 `i` 个字符（`y[1:i]`）的最大质量和。

#### **状态转移方程**
对于 `dp[i]`，我们可以选择 `j` 作为最后一个单词的起始位置（即 `y[j:i]` 是最后一个单词），那么：
$$
dp[i] = \max_{j < i} (dp[j] + quality(y[j:i]))
$$
其中 `quality(y[j:i])` 是 `y[j:i]` 作为一个单词的质量。


### **代码实现**
```cpp
int maxQuality(string sentence)
{
    int n = sentence.size();
    vector<int> dp(n + 1, 0);
    for (int i = 0; i <= n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            string word = sentence.substr(j, i - j);
            dp[i] = max(dp[i], dp[j] + quality(word));
        }
    }
    return dp[n];
}
```

---

## 5


1. **排序**：按活动的 **结束时间** \( f_i \) 升序排序，保证前面的活动能更早结束，以便后续活动有更多选择。
2. **找前驱**：对于每个活动 \( a_i \)，找到 **最后一个不与 \( a_i \) 冲突的活动**（即 `p[i]`，使得 \( f_{p[i]} \leq s_i \)）。
3. **动态规划**：
   - 设 `dp[i]` 为前 `i` 个活动的最优解，即在前 `i` 个活动中选择不重叠活动的最大权重和。
   - 递推公式：
     $$
     dp[i] = \max(dp[i-1], v_i + dp[p[i]])
     $$
     - `dp[i-1]`：表示不选择当前活动 `i`，直接继承前 `i-1` 个活动的最优解。
     - `v_i + dp[p[i]]`：表示选择 `i`，则需要加上 `i` 的权重 `v_i`，同时前驱活动 `p[i]` 的最优解 `dp[p[i]]`。

---

---

### **代码实现**
```cpp
int getMaxValue(vector<Activity> &acts)
{
    sort(acts.begin(), acts.end(), [](Activity &a, Activity &b)
         { return a.finish < b.finish; });
    int n = acts.size();
    vector<int> dp(n, 0);
    vector<int> pre(n, -1);
    for (int i = 0; i < n; i++)
    {
        int left = 0, right = i - 1;
        while (left <= right)
        {
            int mid = (left + right) / 2;
            if (acts[mid].finish <= acts[i].start)
            {
                if (acts[mid + 1].finish <= acts[i].start)
                    left = mid + 1;
                else
                {
                    pre[i] = mid;
                    break;
                }
            }
            else
                right = mid - 1;
        }
    }
    dp[0] = acts[0].value;
    for (int i = 1; i < n; i++)
    {
        dp[i] = max(dp[i - 1], acts[i].value);
        if (pre[i] != -1)
            dp[i] = max(dp[i], dp[pre[i]] + acts[i].value);
    }
    return dp[n - 1];
}
```

---

## 6

令 `dp[v][m]` 表示 **携带 `m` 元时，到达顶点 `v` 的最短路径长度**。  
状态转移时，需要满足：
- **`m >= B(v)`** 才能进入顶点 `v`。
- 从 `u` 走到 `v`，路径长度 `dp[v][m - B(v)]` 需要更新。

#### **2. 递推关系**
从 `u` 到 `v`，如果 `m ≥ B(v)`，则：
$$
dp[v][m - B(v)] = \min(dp[v][m - B(v)], dp[u][m] + A(u, v))
$$

#### **3. 初始化**
- `dp[s][M - B(s)] = 0`，表示从起点 `s` 出发并支付 `B(s)` 费用。
- 其他 `dp[v][m]` 设为 `INF`。

#### **4. 目标**
找到 **所有 `m` 下 `dp[d][m]` 最小值**。

---

### **代码实现**
```cpp
int getMinPathDist(int n, vector<vector<Edge>> &graph, vector<int> &cost, int M, int s, int d)
{
    vector<vector<int>> dp(n, vector<int>(M + 1, INT_MAX));

    if (M >= cost[s])
        dp[s][M - cost[s]] = 0;

    for (int money = M; money >= 0; --money)
    {
        for (int u = 0; u < n; ++u)
        {
            if (dp[u][money] == INT_MAX)
                continue;
            for (const Edge &edge : graph[u])
            {
                int v = edge.to;
                int w = edge.length;
                if (money >= cost[v])
                {
                    int newMony = money - cost[v];
                    dp[v][newMony] = min(dp[v][newMony], dp[u][money] + w);
                }
            }
        }
    }

    int minDist = INT_MAX;
    for (int money = 0; money <= M; ++money)
    {
        minDist = min(minDist, dp[d][money]);
    }
    return minDist;
}
```

---

## 7

- `dp[c]`：表示背包容量为 `c` 时能获得的最大价值（如果容量为 `c` 时没有解，则 `dp[c] = -∞`，表示不可能填满）。
- `dp[0] = 0`，表示容量为 0 时，价值为 0。

#### **状态转移方程**
对于每个物品 `i`（大小 `s_i`，价值 `v_i`），我们尝试将其加入背包（但注意要确保容量恰好为 `C`）：

- 对于每个可能的背包容量 `c`，如果 `c >= s_i`，可以考虑将物品 `i` 放入当前背包，此时：
  $$
  dp[c] = \max(dp[c], dp[c - s_i] + v_i)
  $$
  即：当前容量 `c` 的最大价值，要么是之前的最大值 `dp[c]`，要么是加入物品 `i` 后的价值 `dp[c - s_i] + v_i`。

#### **初始状态**
- `dp[0] = 0`：当背包容量为 `0` 时，最大价值为 `0`。
- 其他 `dp[c]` 初始化为 `-∞`，表示还没有找到合法解。

---

### **代码实现**

```cpp
int fullPackage(int n, int C, vector<int> w, vector<int> v)
{
    vector<int> dp(C + 1, -1e9 - 7);
    dp[0] = 0;
    for (int i = 0; i < n; i++)
    {
        for (int c = C; c >= w[i]; --c)
        {
            dp[c] = max(dp[c], dp[c - w[i]] + v[i]);
        }
    }
    return dp[C] == -1e9 - 7 ? -1 : dp[C];
}
```

---

## 8

要求 $O(nlogn)$

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

---

## 9

定义 `dp[i]` 表示以 `arr[i]` 作为结尾的最长非降子序列的长度。

### **状态转移方程**
1. **初始状态**：每个元素本身都可以作为一个长度为 1 的非降子序列，因此 `dp[i] = 1` 初始值。
   
2. **转移方程**：对于每个元素 `arr[i]`，我们需要考虑所有在它之前的元素 `arr[j]`（`j < i`），如果 `arr[j] <= arr[i]`，那么 `arr[i]` 可以接在 `arr[j]` 后面扩展出一个非降子序列。因此：
   $$
   dp[i] = \max(dp[i], dp[j] + 1) \quad \text{for all} \quad j < i \quad \text{and} \quad arr[j] \leq arr[i]
   $$

   这意味着，如果找到了一个 `arr[j]`（`j < i`）使得 `arr[j] <= arr[i]`，我们就可以考虑通过将 `arr[i]` 添加到以 `arr[j]` 为结尾的子序列上，更新 `dp[i]`。

3. **最终结果**：最长的非降子序列的长度就是 `dp` 数组中的最大值：
   $$
   \text{result} = \max(dp[0], dp[1], \dots, dp[n-1])
   $$


```cpp
int maxSubSequnceLen(vector<int> &arr)
{
    int n = arr.size();
    vector<int> dp(n, 1);  // dp[i] 表示以 arr[i] 结尾的最长非降子序列长度
    // 填充 dp 数组
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (arr[j] <= arr[i])
            {
                dp[i] = max(dp[i], dp[j] + 1);  // 如果 arr[j] <= arr[i]，更新 dp[i]
            }
        }
    }
    // 返回 dp 数组中的最大值
    return *max_element(dp.begin(), dp.end());
}
```
