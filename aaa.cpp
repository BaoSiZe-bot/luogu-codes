#include <cstdio>
#include <cstring>
using namespace std;

typedef long long ll;

inline char nc()
{  //fread快读
    static char buf[100000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

inline int read()
{
    int x(0), f(1);
    char ch = nc();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = ~f + 1;
        ch = nc();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = nc();
    }
    return x * f;
}

const int N = 1500010;  //试出来的一个常数
const int inf = 0x3f3f3f3f;
int n, m, c;
int start, m_end;

struct edge
{
    int v;
    int w;
    int nxt;
} e[N << 1];

int head[N], cnt;

inline void add(int u, int v, int w)
{
    e[++cnt] = (edge){v, w, head[u]};
    head[u] = cnt;
}

inline int ls(int s)
{
    return s << 1;
}
inline int rs(int s)
{
    return s << 1 | 1;
}

int minv[N << 2], minp[N << 2];

inline void push_up(int o)
{
    int lc = ls(o);
    int rc = rs(o);
    if (minv[lc] <= minv[rc])
    {
        minv[o] = minv[lc];
        minp[o] = minp[lc];
    }
    else
    {
        minv[o] = minv[rc];
        minp[o] = minp[rc];
    }
}

void build(int o, int l, int r)
{
    if (l == r)
    {
        minv[o] = inf;
        minp[o] = l;
        return;
    }
    int mid = (l + r) >> 1;
    build(ls(o), l, mid);
    build(rs(o), mid + 1, r);
    push_up(o);
}

void modfity(int o, int l, int r, int p, int w)
{
    if (l == r)
    {
        minv[o] = w;
        return;
    }
    int mid = (l + r) >> 1;
    if (p <= mid)
        modfity(ls(o), l, mid, p, w);
    else
        modfity(rs(o), mid + 1, r, p, w);
    push_up(o);
}

int dis[N];

void dijkspfa(int s)
{
    build(1, 0, n);
    modfity(1, 0, n, s, 0);
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0;
    while (minv[1] != inf)
    {
        int u = minp[1];
        modfity(1, 0, n, u, inf);
        for (int i(head[u]); i; i = e[i].nxt)
        {
            if (dis[u] + e[i].w < dis[e[i].v])
            {
                dis[e[i].v] = dis[u] + e[i].w;
                modfity(1, 0, n, e[i].v, dis[e[i].v]);
            }
        }
    }
}

int main()
{
    n = read(), m = read(), c = read();
    for (int i(1); i <= m; ++i)
    {
        int u = read(), v = read(), w = read();
        add(u, v, w);
    }
    for (int i(0); i <= n; ++i)
    {
        for (int j(0); j <= 20; ++j)
        {
            int qwq = i ^ (1 << j);
            if (qwq <= n)
                add(i, qwq, c * (1 << j));
        }
    }
    start = read(), m_end = read();
    dijkspfa(start);
    printf("%d", dis[m_end]);
    return 0;
}
