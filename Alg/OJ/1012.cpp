#include <bits/stdc++.h>
using namespace std;
#define int long long

struct Point
{
    int x, y;
    double len = 0, angle = 0;
    bool operator<(const Point &p) const
    {
        if (x == p.x)
            return y < p.y;
        return x < p.x;
    }
    bool operator==(const Point &p) const
    {
        return x == p.x && y == p.y;
    }
};

bool is_same_line(Point a, Point b, Point c)
{
    return (a.x - b.x) * (c.y - b.y) == (a.y - b.y) * (c.x - b.x);
}

bool is_left(Point a, Point b, Point c)
{
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x) > 0;
}

// 最下最左点
Point find_base(const vector<Point> &points)
{
    Point res = {LLONG_MAX, LLONG_MAX};
    for (auto &p : points)
    {
        if (p.y < res.y || (p.y == res.y && p.x < res.x))
        {
            res = p;
        }
    }
    return res;
}

void solve()
{
    int n;
    cin >> n;
    set<Point> input_points;
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        input_points.insert({x, y});
    }

    vector<Point> points(input_points.begin(), input_points.end());
    n = points.size();
    if (n <= 1)
    {
        for (auto &p : points)
            cout << p.x << " " << p.y << endl;
        return;
    }

    // 找到最下最左点并将其放在第一个位置
    Point base = find_base(points);
    rotate(points.begin(), find(points.begin(), points.end(), base), points.end());

    // 计算每个点相对于基准点的极角和距离
    for (int i = 1; i < n; i++)
    {
        points[i].len = hypot(points[i].x - base.x, points[i].y - base.y);
        points[i].angle = atan2(points[i].y - base.y, points[i].x - base.x);
    }

    // 按极角排序，若极角相同则按距离排序
    sort(points.begin() + 1, points.end(), [](const Point &a, const Point &b)
         { return a.angle != b.angle ? a.angle < b.angle : a.len < b.len; });

    // 栈来维护凸包
    vector<Point> hull;
    hull.push_back(points[0]);

    int k = 2;
    // 找到跟第一个点和第二个点共线的所有点
    while (k < n && is_same_line(points[0], points[1], points[k]))
        k++;
    // 推入最后一个共线点
    hull.push_back(points[k - 1]);
    // 如果还未遍历完，则把k指向的点也加入凸包
    if (k < n)
        hull.push_back(points[k]);

    // 遍历剩下的点
    for (int i = k + 1; i < n; i++)
    {
        // 如果当前点与凸包的最后两个点不构成左转，则弹出最后一个点
        while (hull.size() > 1 && !is_left(hull[hull.size() - 2], hull.back(), points[i]))
        {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }

    for (auto &p : hull)
    {
        cout << p.x << " " << p.y << endl;
    }
}

signed main()
{
    int t;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        cout << "case " << i + 1 << ":" << endl;
        solve();
    }
}
