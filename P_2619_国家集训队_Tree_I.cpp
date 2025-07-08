#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <utility>

#define fi first
#define se second

int n, m, need;
const int N = 5e4 + 5, M = 2e5 + 5;

struct Edge
{
    int s, t, c, col;
    bool operator<(const Edge &a) const
    {
        return (c ^ a.c) ? c < a.c : col < a.col;
    }
} e[M], f[M];

int p[N], h[N];
inline int fd(int x)  // find parent
{
    return (~p[x]) ? p[x] = fd(p[x]) : x;
}

inline std::pair<int, int> check(int del)
{
    memset(h, 0, sizeof h);
    memset(p, 0xff, sizeof p);
    memcpy(f, e, sizeof(e));
    for (int i = 1; i <= m; ++i)
        if (!f[i].col)
            f[i].c += del;
    std::sort(f + 1, f + m + 1);
    int cct = 0, cbt = 0;
    for (int i = 1, cnt = 0; cnt < n - 1 && i <= m; ++i)
    {
        int u = fd(f[i].s), v = fd(f[i].t);
        if (u ^ v)
        {
            ++cnt;
            cct += f[i].c;
            cbt += !f[i].col;
            (h[u] <= h[v]) ? p[u] = v : p[v] = u;
            h[u] += (h[u] == h[v]);
        }
    }
    for (int i = 1; i <= m; ++i)
        if (!f[i].col)
            f[i].c -= del;
    return {cct, cbt};
}

int main()
{
    scanf("%d%d%d", &n, &m, &need);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d%d%d", &e[i].s, &e[i].t, &e[i].c, &e[i].col);
        ++e[i].s;
        ++e[i].t;
    }
    int l = -114, r = 114, res = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        auto ret = check(mid);
        if (ret.se >= need)
        {
            res = ret.fi - need * mid;
            l = mid + 1;
        }
        else
            r = mid - 1;
    }
    printf("%d\n", res);
    return 0;
}
