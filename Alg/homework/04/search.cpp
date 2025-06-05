#include <iostream>
#include <array>
#include <map>
#include <tuple>
using namespace std;

constexpr int H = 7, W = 8;

const array<array<int, W>, H> a = {{{6, 6, 2, 6, 5, 2, 4, 1},
                                    {1, 3, 2, 0, 1, 0, 3, 4},
                                    {1, 3, 2, 4, 6, 6, 5, 4},
                                    {1, 0, 4, 3, 2, 1, 1, 2},
                                    {5, 1, 3, 6, 0, 4, 5, 5},
                                    {5, 5, 4, 0, 2, 6, 0, 3},
                                    {6, 0, 5, 3, 4, 2, 0, 3}}};

// 输出编号图，每对骨牌用其固定编号标记
array<array<int, W>, H> b{};

// 每个格子是否已使用
array<array<bool, W>, H> used{};

// 骨牌是否已使用：仅存储 x <= y 的组合
array<array<bool, 7>, 7> domino{};

// 映射 (i,j) 点数对 → 骨牌编号（i <= j）
map<pair<int, int>, int> domino_number;

// 方向向量：右和下
const int dx[] = {0, 1};
const int dy[] = {1, 0};

// 检查是否在网格内
inline bool in_grid(int x, int y)
{
    return 0 <= x && x < H && 0 <= y && y < W;
}

bool dfs(int pos)
{
    if (pos == H * W)
        return true;

    int i = pos / W;
    int j = pos % W;

    if (used[i][j])
        return dfs(pos + 1); // 当前位置已经用过，递归下一个

    for (int d = 0; d < 2; ++d)
    {
        int ni = i + dx[d], nj = j + dy[d];
        if (!in_grid(ni, nj) || used[ni][nj])
            continue;

        int x = a[i][j], y = a[ni][nj];
        int u = min(x, y), v = max(x, y);
        if (domino[u][v])
            continue;

        int id = domino_number[{u, v}];
        used[i][j] = used[ni][nj] = true;
        domino[u][v] = true;
        b[i][j] = b[ni][nj] = id;

        if (dfs(pos + 1))
            return true;

        used[i][j] = used[ni][nj] = false;
        domino[u][v] = false;
        b[i][j] = b[ni][nj] = 0;
    }

    return false;
}

void init_domino_map()
{
    int id = 1;
    for (int i = 0; i <= 6; ++i)
        for (int j = i; j <= 6; ++j)
            domino_number[{i, j}] = id++;
}

int main()
{
    init_domino_map();

    if (dfs(0))
    {
        cout << "找到一种合法骨牌覆盖方案（编号图）：\n";
        for (int i = 0; i < H; ++i)
        {
            for (int j = 0; j < W; ++j)
                cout << b[i][j] << "\t";
            cout << "\n";
        }
    }
    else
    {
        cout << "无法找到合法的骨牌覆盖方案。\n";
    }

    return 0;
}
