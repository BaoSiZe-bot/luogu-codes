#include <algorithm>
#include <cassert>
#include <cstdio>
#include <utility>

using ll = long long;
const ll INF = 2e11;
const int N = 2e5 + 5, M = 4e5 + 5;
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

struct dat
{
    int l, r;
    ll s, cl, cr;
    dat(int _l = N, int _r = 0, ll _s = 0, ll _cl = -1, ll _cr = -1) : l(_l), r(_r), s(_s), cl(_cl), cr(_cr) {}
};
struct tag
{
    ll k;
    tag(ll _k = INF) : k(_k) {}
    bool operator==(const tag &other)
    {
        return k == other.k;
    }
};
__attribute__((always_inline)) inline dat f(const tag &t, const dat &d)
{
    if (t.k == INF)
        return d;
    return dat{d.l, d.r, 1, t.k, t.k};
}
__attribute__((always_inline)) inline tag g(const tag &x, const tag &y)
{
    if (x.k == INF)
        return y;
    return x;
}
__attribute__((always_inline)) inline dat h(const dat &a, const dat &b)
{
    if (a.l > a.r)
        return b;
    if (b.l > b.r)
        return a;
    return dat{a.l, b.r, a.s + b.s - (a.cr == b.cl), a.cl, b.cr};
}
const tag tt;
const dat dd;
template <const size_t N, typename dat, typename tag, typename T, T I[]> struct SegmentTree
{
#define ci const int &
#define ct const tag &
#define cd const dat &
    dat d[N];
    tag t[N];
    void init(ci rt, ci l, ci r)
    {
        d[rt] = {l, r, 1};
        t[rt] = tt;
        if (l == r)
        {
            d[rt].cl = d[rt].cr = I[l];
            return;
        }
        int mid = (l + r) >> 1;
        init(rt << 1, l, mid);
        init(rt << 1 | 1, mid + 1, r);
        d[rt] = h(d[rt << 1], d[rt << 1 | 1]);
        assert(d[rt].cl == I[l] && d[rt].cr == I[r]);
    }
    void pushdown(ci rt)
    {
        if (t[rt] == tt)
            return;
        d[rt << 1] = f(t[rt], d[rt << 1]);
        t[rt << 1] = g(t[rt], t[rt << 1]);
        d[rt << 1 | 1] = f(t[rt], d[rt << 1 | 1]);
        t[rt << 1 | 1] = g(t[rt], t[rt << 1 | 1]);
        t[rt] = tt;
    }
    void upd(ci rt, ci l, ci r, ct k)
    {
        if (d[rt].r < l || r < d[rt].l)
            return;
        if (l <= d[rt].l && d[rt].r <= r)
        {
            t[rt] = g(k, t[rt]);
            d[rt] = f(k, d[rt]);
            return;
        }
        pushdown(rt);
        upd(rt << 1, l, r, k);
        upd(rt << 1 | 1, l, r, k);
        d[rt] = h(d[rt << 1], d[rt << 1 | 1]);
    }
    dat qry(ci rt, ci l, ci r)
    {
        if (d[rt].r < l || r < d[rt].l)
            return dd;
        if (l <= d[rt].l && d[rt].r <= r)
            return d[rt];
        pushdown(rt);
        return h(qry(rt << 1, l, r), qry(rt << 1 | 1, l, r));
    }
#undef ci
#undef ct
#undef cd
};
ll w[N], a[N];
SegmentTree<N << 2, dat, tag, ll, a> st;

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

inline void upd(int x, int k)
{
    st.upd(1, dfn[x], dfn[x] + num[x] - 1, {k});
}
inline ll qry(int x)
{
    return st.qry(1, dfn[x], dfn[x] + num[x] - 1).s;
}

inline void upd(int u, int v, int k)
{
    while (tp[u] ^ tp[v])
    {
        if (d[tp[u]] < d[tp[v]])
            std::swap(u, v);
        st.upd(1, dfn[tp[u]], dfn[u], {k});
        u = pr[tp[u]];
    }
    if (dfn[u] > dfn[v])
        std::swap(u, v);
    st.upd(1, dfn[u], dfn[v], {k});
}
inline ll qry(int u, int v)
{
    dat sl = dd, sr = dd;
    while (tp[u] ^ tp[v])
    {
        if (d[tp[u]] < d[tp[v]])
        {
            sr = h(st.qry(1, dfn[tp[v]], dfn[v]), sr);
            v = pr[tp[v]];
        }
        else
        {
            sl = h(st.qry(1, dfn[tp[u]], dfn[u]), sl);
            u = pr[tp[u]];
        }
    }
    if (d[u] > d[v])
        sl = h(st.qry(1, dfn[v], dfn[u]), sl);
    else
        sr = h(st.qry(1, dfn[u], dfn[v]), sr);
    std::swap(sl.cl, sl.cr);
    return h(sl, sr).s;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("\n%lld", &w[i]);
    for (int i = 2; i <= n; ++i)
    {
        int u, v;
        scanf("\n%d %d", &u, &v);
        add(u, v);
        add(v, u);
    }
    pre(1, 0);
    dec(1, 1);
    st.init(1, 1, n);
    while (m--)
    {
        char op;
        int x, y, k;
        scanf("\n%c %d %d", &op, &x, &y);
        if (op == 'C')
        {
            scanf(" %d", &k);
            upd(x, y, k);
        }
        else
            printf("%lld\n", qry(x, y));
    }
    return 0;
}