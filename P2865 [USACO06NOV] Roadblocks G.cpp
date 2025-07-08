#include <queue>
#include <stdio.h>
#include <string.h>
#define x first
#define y second
const int M = 2e5 + 5, N = 5e3 + 5;
struct Edge
{
    int v, w, p;
} e[M];
int ed[N], cnt;
inline void add(int u, int v, int w)
{
    e[++cnt] = {v, w, ed[u]};
    ed[u] = cnt;
}
int d1[N], d2[N];
bool f[N];
inline void dij()
{
    memset(d1, 0x3f, sizeof(d1));
    memset(d2, 0x3f, sizeof(d2));
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;
    q.push({0, 1});
    d1[1] = 0;
    while (!q.empty())
    {
        auto nw = q.top();
        q.pop();
        if (d2[nw.y] < nw.x) // 已经松弛更新完成
            continue;
        for (int i = ed[nw.y]; i; i = e[i].p)
        {
            int to = e[i].v;
            if (d1[to] > nw.x + e[i].w)
            {
                d2[to] = d1[to];
                d1[to] = nw.x + e[i].w;
                q.push({d1[to], to});
            }
            if (d2[to] > nw.x + e[i].w && nw.x + e[i].w > d1[to])
            {
                d2[to] = nw.x + e[i].w;
                q.push({d2[to], to});
            }
        }
    }
}
int main()
{
    int n, r;
    scanf("%d%d", &n, &r);
    for (int i = 1; i <= r; ++i)
    {
        int a, b, d;
        scanf("%d%d%d", &a, &b, &d);
        add(a, b, d);
        add(b, a, d);
    }
    dij();
    printf("%d\n", d2[n]);
    return 0;
}
