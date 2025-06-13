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
    int i = 0, j = 0, h1 = 0, h2 = 0;

    while (i < b1.size() && j < b2.size())
    {
        int x;
        if (b1[i].x < b2[j].x)
        {
            x = b1[i].x;
            h1 = b1[i].h;
            i++;
        }
        else if (b1[i].x > b2[j].x)
        {
            x = b2[j].x;
            h2 = b2[j].h;
            j++;
        }
        else
        {
            x = b1[i].x;
            h1 = b1[i].h;
            h2 = b2[j].h;
            i++, j++;
        }

        int maxh = max(h1, h2);
        if (res.empty() || res.back().h != maxh)
        {
            res.push_back({x, maxh});
        }
    }

    while (i < b1.size())
    {
        if (res.empty() || res.back().h != b1[i].h)
            res.push_back(b1[i]);
        i++;
    }

    while (j < b2.size())
    {
        if (res.empty() || res.back().h != b2[j].h)
            res.push_back(b2[j]);
        j++;
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
    auto left = getContour(buildings, l, m);
    auto right = getContour(buildings, m + 1, r);
    return mergeContour(left, right);
}

signed main()
{
    int n;
    cin >> n;
    vector<Building> buildings(n);
    for (auto &b : buildings)
        cin >> b.x1 >> b.x2 >> b.h;

    sort(buildings.begin(), buildings.end(), [](const Building &a, const Building &b)
         { return a.x1 < b.x1; });

    auto contour = getContour(buildings, 0, n - 1);

    for (auto &p : contour)
        cout << p.x << " " << p.h << "\n";
}
