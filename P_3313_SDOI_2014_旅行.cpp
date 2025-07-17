#include <algorithm>
#include <cstdio>

const int ULE = -1; // 无效赋值
const int N = 5e6 + 5, M = 4e5 + 5;

struct Edge
{
    int v, p;
} e[M];
int ed[N], cnt;
inline void add(int u, int v)
{
    e[++cnt] = {v, ed[u]};
    ed[u] = cnt;
}

int root[N];
struct dat
{
    int l, r;
    int s, mx;
    int ls, rs;
    dat(int _l = 0, int _r = 0, int _s = 0, int _mx = 0, int _ls = 0, int _rs = 0) : l(_l), r(_r), s(_s), mx(_mx), ls(_ls), rs(_rs) {}
};
const dat dd;
__attribute__((always_inline)) inline void h(dat &dest, const dat &a, const dat &b)
{
    dest.s = a.s + b.s;
    dest.mx = std::max(a.mx, b.mx);
}
template <const size_t N, typename dat, typename T, T I[]> struct SegmentTree
{
#define ci const int &
#define cd const dat &
    dat d[N];
    int cnt = 0;
    void upd(int &rt, ci l, ci r, ci x, ci k)
    {
        if (!rt)
            d[rt = ++cnt] = {l, r};
        if (d[rt].l == d[rt].r)
        {
            d[rt].s = d[rt].mx = k;
            return;
        }
        int mid = (d[rt].l + d[rt].r) >> 1;
        if (x <= mid)
            upd(d[rt].ls, l, mid, x, k);
        else
            upd(d[rt].rs, mid + 1, r, x, k);
        h(d[rt], d[d[rt].ls], d[d[rt].rs]);
    }
    dat qry(ci rt, ci l, ci r)
    {
        if (d[rt].r < l || r < d[rt].l)
            return dd;
        if (l <= d[rt].l && d[rt].r <= r)
            return d[rt];
        dat ret = d[rt];
        h(ret, qry(d[rt].ls, l, r), qry(d[rt].rs, l, r));
        return ret;
    }
#undef ci
#undef ct
#undef cd
};
int w[N], a[N], c[N];
SegmentTree<N << 2, dat, int, a> st;

int n, m;
int num[N], pr[N], p[N], d[N];
inline void pre(int x, int fa)
{
    pr[x] = fa;
    num[x] = 1;
    int mx = 0;
    d[x] = d[fa] + 1;
    for (int i = ed[x]; i; i = e[i].p)
    {
        int to = e[i].v;
        if (to != fa)
        {
            pre(to, x);
            num[x] += num[to];
            if (num[to] > mx)
            {
                p[x] = i;
                mx = num[to];
            }
        }
    }
}

int dfn[N], tp[N], rk[N], pts;
inline void dec(int x, int t)
{
    tp[x] = t;
    dfn[x] = ++pts;
    rk[dfn[x]] = x;
    a[dfn[x]] = w[x];
    if (!p[x])
        return;
    dec(e[p[x]].v, t);
    for (int i = ed[x]; i; i = e[i].p)
    {
        int to = e[i].v;
        if (to != pr[x] && i != p[x])
            dec(to, to);
    }
}

inline dat qry(int u, int v, int c)
{
    dat res = 0;
    while (tp[u] ^ tp[v])
    {
        if (d[tp[u]] < d[tp[v]])
            std::swap(u, v);
        h(res, res, st.qry(root[c], dfn[tp[u]], dfn[u]));
        u = pr[tp[u]];
    }
    if (dfn[u] > dfn[v])
        std::swap(u, v);
    h(res, res, st.qry(root[c], dfn[u], dfn[v]));
    return res;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d", w + i, c + i);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    pre(1, 0);
    dec(1, 1);
    for (int i = 1; i <= n; ++i)
        st.upd(root[c[i]], 1, n, dfn[i], {w[i]});
    while (m--)
    {
        char op[10];
        int x, y;
        scanf("%s%d%d", op, &x, &y);
        if (op[0] == 'C')
        {
            if (op[1] == 'C')
            {
                st.upd(root[c[x]], 1, n, dfn[x], 0);
                st.upd(root[c[x] = y], 1, n, dfn[x], {w[x]});
            }
            else
                st.upd(root[c[x]], 1, n, dfn[x], w[x] = y);
        }
        else
        {
            dat res = qry(x, y, c[x]);
            printf("%d\n", op[1] == 'S' ? res.s : res.mx);
        }
    }
    return 0;
}