#include <algorithm>
#include <cstdio>

using ll = long long;
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
    ll s;
    dat(int _l = 0, int _r = 0, ll _s = 0) : l(_l), r(_r), s(_s) {}
};
struct tag
{
    ll k;
    tag(ll _k = 1000) : k(_k) {}
    bool operator==(const tag &other)
    {
        return k == other.k;
    }
};
__attribute__((always_inline)) inline dat f(const tag &t, const dat &d)
{
    if (t.k == 1000)
        return d;
    return dat{d.l, d.r, (d.r - d.l + 1) * t.k};
}
__attribute__((always_inline)) inline tag g(const tag &x, const tag &y)
{
    if (x.k == 1000)
        return y;
    return x;
}
__attribute__((always_inline)) inline dat h(const dat &a, const dat &b)
{
    return dat{a.l, b.r, a.s + b.s};
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
        d[rt] = {l, r, 0};
        t[rt] = tt;
        if (l == r)
        {
            d[rt].s = I[l];
            return;
        }
        int mid = (l + r) >> 1;
        init(rt << 1, l, mid);
        init(rt << 1 | 1, mid + 1, r);
        d[rt] = h(d[rt << 1], d[rt << 1 | 1]);
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
    ll s = 0;
    while (tp[u] ^ tp[v])
    {
        if (d[tp[u]] < d[tp[v]])
            std::swap(u, v);
        s += st.qry(1, dfn[tp[u]], dfn[u]).s;
        u = pr[tp[u]];
    }
    if (dfn[u] > dfn[v])
        std::swap(u, v);
    s += st.qry(1, dfn[u], dfn[v]).s;
    return s;
}

int main()
{
    int n, m;
    scanf("%d", &n);
    for (int i = 2; i <= n; ++i)
    {
        int u;
        scanf("%d", &u);
        ++u;
        add(u, i);
        add(i, u);
    }
    pre(1, 0);
    dec(1, 1);
    st.init(1, 1, n);
    scanf("%d", &m);
    while (m--)
    {
        char op[10];
        int x;
        scanf("%s%d", op, &x);
        ++x;
        if (op[0] == 'i')
        {
            printf("%lld\n", d[x] - qry(1, x));
            upd(1, x, 1);
        }
        else
        {
            printf("%lld\n", qry(x));
            upd(x, 0);
        }
    }
    return 0;
}