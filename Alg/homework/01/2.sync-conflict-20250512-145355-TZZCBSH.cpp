#include <bits/stdc++.h>
using namespace std;
#define int long long

struct Building
{
    int x1, x2, h;
};

struct Contour
{
    int x, h;
};
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

signed main()
{
    int n = 8;
    vector<Building> buildings = {
        {1, 5, 11},
        {2, 7, 6},
        {3, 9, 13},
        {12, 16, 7},
        {14, 25, 3},
        {19, 22, 18},
        {23, 29, 13},
        {24, 28, 4}};

    auto contour = getContour(buildings, 0, n - 1);

    for (auto i : contour)
    {
        cout << i.x << " " << i.h << endl;
    }
}