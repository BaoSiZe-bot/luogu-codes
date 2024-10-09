#include <stdbool.h>
#include <string.h>
#include <stdio.h>
const char F[] = "First\n", S[] = "Second\n";
int t;
struct Edge
{
    int v, p;
} e[2000005];
int ed[1000005], cnt;
bool vs[1000005];
void add(int u, int v)
{
    e[++cnt].v = v;
    e[cnt].p = ed[u];
    ed[u] = cnt;
}
bool chk(int rt)
{
    bool f = 1;
    vs[rt] = 1;
    for (int i = ed[rt]; i; i = e[i].p)
        if (!vs[e[i].v])
            f ^= chk(e[i].v);
    return f;
}
int main()
{
    scanf("%d", &t);
    while (t--)
    {
        memset(ed, 0, sizeof ed);
        memset(vs, 0, sizeof vs);
        cnt = 0;
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= m; ++i)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            add(u, v);
            add(v, u);
        }
        bool f1 = chk(1), fn = chk(n);
        int t = (n * (n - 1ll) >> 1) - m;
        printf(n & 1 ? t & 1 ? F : S : f1 ^ fn ? F : (t - (f1 && fn)) & 1 ? F : S);
    }
    return 0;
}
