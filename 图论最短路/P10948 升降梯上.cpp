#include <stdio.h>
#include <string.h>
#include <queue>
using ll = long long;
int c[25], pos, n, m;
int d[1005][25];
bool f[1005][25];
struct Node
{
    int u, v;
    bool operator<(const Node &other) const
    {
        return d[other.u][other.v] < d[u][v];
    }
};
inline int abs(int x)
{
    return x < 0 ? -x : x;
}
inline void dij()
{
    memset(d, 0x3f, sizeof(d));
    d[1][pos] = 0;
    std::priority_queue<Node> q;
    q.push({1, pos});
    while (!q.empty())
    {
        Node nw = q.top();
        q.pop();
        if (f[nw.u][nw.v])
            continue;
        f[nw.u][nw.v] = 1;
        for (int i = 1; i <= m; ++i)
        {
            Node to = {nw.u + c[i], i};
            int w = abs(nw.v - i) + (abs(c[i]) << 1);
            if (to.u >= 1 && to.u <= n && !f[to.u][to.v] && d[to.u][to.v] > d[nw.u][nw.v] + w)
            {
                d[to.u][to.v] = d[nw.u][nw.v] + w;
                q.push(to);
            }
        }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d", c + i);
        if (!c[i])
            pos = i;
    }
    dij();
    int res = 0x3f3f3f3f;
    for (int i = 1; i <= m; ++i)
        res = std::min(res, d[n][i]);
    if (res == 0x3f3f3f3f)
        return 0 * printf("-1\n");
    printf("%d\n", res);
    return 0;
}
