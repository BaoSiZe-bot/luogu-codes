#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <utility>
#define x first
#define y second
#define I c[i].y
#define J c[j].y
#define K c[k].y
using ll = long long;
const int N = 1e3 + 5;
ll dis[N][N], res[N][N];
std::pair<int, int> c[N];
int main()
{
    memset(dis, 0x3f, sizeof(dis));
    memset(res, 0x3f, sizeof(res));
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &c[i].first);
        c[i].second = i;
        dis[i][i] = 0;
    }
    std::sort(c + 1, c + n + 1);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        ll w;
        scanf("%d%d%d", &u, &v, &w);
        dis[u][v] = std::min(dis[u][v], w);
        dis[v][u] = std::min(dis[v][u], w);
    }
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j) //
            {
                dis[I][J] = std::min(dis[I][J], dis[I][K] + dis[K][J]);
                res[I][J] = std::min(res[I][J], dis[I][J] + std::max({c[i].x, c[j].x, c[k].x}));
            }
    while (q--)
    {
        int s, t;
        scanf("%d%d", &s, &t);
        printf("%d\n", res[s][t]);
    }
    return 0;
}
