#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<int> getLongest(vector<int> a)
{
    int t = a.size();
    vector<vector<int>> dp(t + 1);
    dp[1].push_back(a[0]);
    // i: index
    for (int i = 2; i <= t; i++)
    {
        int &the = a[i - 1];
        // j: length
        for (int j = t; j >= 1; j--)
        {
            if (j == 1)
            {
                int dp2_back = dp[2].empty() ? LONG_LONG_MIN : dp[2].back();
                if (the <= dp[1].back() && the >= dp2_back) // check replace
                {
                    auto tmp = dp[1];
                    tmp.push_back(the);
                    dp[2] = tmp;
                }
                dp[j] = {max(dp[j][0], the)};
                continue;
            }
            if (dp[j].size() == 0)
                continue;

            int dp2_back = dp[j + 1].empty() ? LONG_LONG_MIN : dp[j + 1].back();
            if (j < t && the <= dp[j].back() && the >= dp2_back)
            {
                auto nw = dp[j];
                nw.push_back(the);
                dp[j + 1] = nw;
            }
            if (the >= dp[j].back() && the <= *(dp[j].end() - 2))
            {
                dp[j].back() = the;
            }
        }
    }
    for (int i = t; i >= 1; i--)
    {
        if (dp[i].size() > 0)
        {
            return dp[i];
        }
    }
    return {};
}

void erase_vector(vector<int> &a, const vector<int> &to_erase)
{
    unordered_multiset<int> s(to_erase.begin(), to_erase.end());
    vector<int> result;
    for (int x : a)
    {
        if (s.count(x))
        {
            s.erase(s.find(x));
        }
        else
        {
            result.push_back(x);
        }
    }
    a = result;
}

signed main()
{
    int n;
    cin >> n;
    while (n--)
    {
        int t;
        cin >> t;
        vector<int> a(t);
        for (auto &x : a)
            cin >> x;
        int cnt = 1;
        auto ans = getLongest(a);
        erase_vector(a, ans);
        while (a.size() > 0)
        {
            auto tmp = getLongest(a);
            erase_vector(a, tmp);
            cnt++;
        }
        cout << ans.size() << " " << cnt << endl;
    }
}