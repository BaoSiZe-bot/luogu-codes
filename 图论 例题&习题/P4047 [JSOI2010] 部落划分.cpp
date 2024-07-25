#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <math.h>
/**
 * @class Edge
 * @brief the Edge Struct
 */
struct Edge
{
    int u, v, d;
    bool operator<(const Edge &other) const
    {
        return d < other.d;
    }
} e[10000005];
int p[1005], h[1005], x[1005], y[1005], res[1005], cnt;

/**
 * @brief find the parent of node
 * @param x the id to find
 * @return return the id of parent
 */
inline int fd(int x)
{
    return ~p[x] ? p[x] = fd(p[x]) : x;
}

int main()
{
    memset(p, 0xff, sizeof p);
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d", x + i, y + i);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j < i; ++j)
            e[++cnt] = {i, j, (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j])};
    std::sort(e + 1, e + cnt + 1);
    int t = 0;
    for (int i = 1; t < n - 1; ++i)
    {
        int u = fd(e[i].u), v = fd(e[i].v), ds = e[i].d;
        if (u ^ v)
        {
            if (h[u] > h[v])
                p[v] = u;
            else if (h[u] < h[v])
                p[u] = v;
            else
            {
                p[v] = u;
                h[u]++;
            }
            ++t;
            res[t] = ds;
        }
    }
    printf("%.2lf\n", sqrt(res[n - k + 1]));
    return 0;
}
