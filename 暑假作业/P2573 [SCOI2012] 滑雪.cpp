#include <bits/stl_algobase.h>
#include <bits/stl_algo.h>
#include <stdio.h>
#include <bitset>
int h[1000005];
using ll = long long;
template <const int N> struct GR
{
private:
    struct Edge
    {
        int v, w, p;
    } e[N];
    int ed[N], cnt = 0;

public:
    inline void add(int u, int v, int w)
    {
        e[++cnt] = {v, w, ed[u]};
        ed[u] = cnt;
    }
    inline Edge ge(int x)
    {
        return e[x];
    }
    inline int gd(int x)
    {
        return ed[x];
    }
};
GR<2000005> g;  //链式前向星

int p[1000005], s[1000005];
inline int fd(int x)
{
    return (p[x] ^ x) ? p[x] = fd(p[x]) : x;
}
class Edge
{  //Edge set
    int u, v, w;

public:
    Edge() {}
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
    bool operator<(const Edge &x) const
    {
        if (h[v] ^ h[x.v])
            return h[v] > h[x.v];
        return w < x.w;
    }
    int par(int id = 0)
    {
        return fd(id ? u : v);
    }
    int gw()
    {
        return w;
    }
} e[2000005];

int ec;  //边集数组
int q[1000005], hd, tl;  //queue for bfs
std::bitset<1000005> f;  // bool array
ll rc;
inline void bfs(int st)
{
    q[hd = tl = 1] = st;
    f.set(st);
    while (hd <= tl)
    {
        int nw = q[hd++];
        for (int i = g.gd(nw); i; i = g.ge(i).p)
        {
            int to = g.ge(i).v;
            e[++ec] = {nw, to, g.ge(i).w};
            if (!f.test(to))
            {
                f.set(to);
                ++rc;
                q[++tl] = to;
            }
        }
    }
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &h[i]);
        p[i] = i;
    }
    for (int i = 1; i <= m; ++i)
    {
        int u, v, k;
        scanf("%d%d%d", &u, &v, &k);
        h[u] < h[v] ? g.add(v, u, k) : g.add(u, v, k);
    }
    bfs(1);
    std::sort(e + 1, e + ec + 1);
    ll res = 0;
    for (int i = 1; i <= ec; ++i)
    {
        int u = e[i].par(1), v = e[i].par();
        if (u ^ v)
        {
            p[u] = v;
            res += e[i].gw();
        }
    }
    printf("%lld %lld", rc + 1, res);
    return 0;
}  //刘禹灏天 says rime is
