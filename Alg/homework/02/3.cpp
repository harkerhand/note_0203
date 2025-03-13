#include <bits/stdc++.h>
using namespace std;
#define int long long

struct TreeNode
{
    vector<TreeNode *> children;
};

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

signed main()
{
    TreeNode *root = new TreeNode();
    root->children.push_back(new TreeNode());
    root->children.push_back(new TreeNode());
    root->children.push_back(new TreeNode());
    root->children[0]->children.push_back(new TreeNode());
    root->children[0]->children.push_back(new TreeNode());
    root->children[1]->children.push_back(new TreeNode());
    root->children[2]->children.push_back(new TreeNode());
    /*

        1
       /|\
      1 1 1
     /| | |
    1 1 1 1

    */
    cout << max(dps(root, true), dps(root, false)) << endl;
    return 0;
}