#include <bits/stdc++.h>
using namespace std;
#define int long long

int quality(string word) { return rand() % 100; }

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

signed main()
{
    string sentence = "I am a student";
    cout << "max:" << maxQuality(sentence) << endl;
    return 0;
}