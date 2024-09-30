#include <stdio.h>
using ll = long long;
struct Edge
{
    int v, p;
} e[20005];
int ed[5005], cnt;
inline void add(int u, int v)
{
    e[++cnt] = {v, ed[u]};
    ed[u] = cnt;
}
inline int min(int a, int b)
{
    return a < b ? a : b;
}
inline int swt(int id)
{
    return id & 1 ? id + 1 : id - 1;
}
int dfn[5005], low[5005], pos[5005], du[5005], gtm, pts;
bool br[5005];
inline void tarjan(int x, int fe)
{
    dfn[x] = low[x] = ++gtm;
    for (int i = ed[x]; i; i = e[i].p)
    {
        int to = e[i].v;
        if (!dfn[to])
        {
            tarjan(to, i);
            low[x] = min(low[x], low[to]);
            if (low[to] > dfn[x])
                br[i] = br[swt(i)] = 1;
        }
        else if (i ^ swt(fe))
            low[x] = min(low[x], dfn[to]);
    }
}
inline void shrink(int rt)
{
    pos[rt] = pts;
    for (int i = ed[rt]; i; i = e[i].p)
        if (!br[i] && !pos[e[i].v])
            shrink(e[i].v);
}
int main()
{
    int f, r;
    scanf("%d%d", &f, &r);
    for (int i = 1; i <= r; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    for (int i = 1; i <= f; ++i)
        if (!dfn[i])
            tarjan(i, 0);
    for (int i = 1; i <= f; ++i)
        if (!pos[i])
        {
            ++pts;
            shrink(i);
        }
    for (int i = 1; i <= f; ++i)
        for (int j = ed[i]; j; j = e[j].p)
            if (pos[i] ^ pos[e[j].v])
                du[pos[i]]++;
    int res = 0;
    for (int i = 1; i <= pts; ++i)
        res += (du[i] == 1);
    printf("%d", (res + 1) >> 1);
    return 0;
}
