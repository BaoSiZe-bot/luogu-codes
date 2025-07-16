#include <algorithm>
#include <cstdio>

using ll = long long;

const ll INF = 2e11;
const int N = 2e5 + 5, M = 4e5 + 5;

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

struct dat
{
    int l, r;
    ll s, mn, mx;
    dat(int _l = 0, int _r = 0, ll _s = 0, ll _mn = INF, ll _mx = -INF) : l(_l), r(_r), s(_s), mn(_mn), mx(_mx) {}
};

struct tag
{
    ll k, b;  // 乘法，赋值
    tag(ll _k = 1, ll _b = INF) : k(_k), b(_b) {}
    bool operator==(const tag &other)
    {
        return k == other.k && b == other.b;
    }
};
__attribute__((always_inline)) inline dat f(const tag &t, const dat &d)
{
    if (t.b == INF)
    {
        if (t.k > 0)
            return dat{d.l, d.r, d.s * t.k, d.mn * t.k, d.mx * t.k};
        return dat{d.l, d.r, d.s * t.k, d.mx * t.k, d.mn * t.k};
    }
    return dat{d.l, d.r, t.b * t.k * (d.r - d.l + 1), t.b * t.k, t.b * t.k};
}
__attribute__((always_inline)) inline tag g(const tag &x, const tag &y)
{
    if (x.b == INF)
        return tag{x.k * y.k, y.b};
    return x;
}
__attribute__((always_inline)) inline dat h(const dat &a, const dat &b)
{
    return dat{a.l, b.r, a.s + b.s, std::min(a.mn, b.mn), std::max(a.mx, b.mx)};
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
            d[rt].s = d[rt].mn = d[rt].mx = I[l];
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
    void upd(ci rt, ci x, ct k)
    {
        if (d[rt].l == d[rt].r)
        {
            d[rt] = f(k, d[rt]);
            return;
        }
        pushdown(rt);
        int mid = (d[rt].l + d[rt].r) >> 1;
        if (x <= mid)
            upd(rt << 1, x, k);
        else
            upd(rt << 1 | 1, x, k);
        d[rt] = h(d[rt << 1], d[rt << 1 | 1]);
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
            w[to] = e[i].w;
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

inline void upd(int u, int v, tag k)
{
    while (tp[u] ^ tp[v])
    {
        if (d[tp[u]] < d[tp[v]])
            std::swap(u, v);
        st.upd(1, dfn[tp[u]], dfn[u], k);
        u = pr[tp[u]];
    }
    if (dfn[u] > dfn[v])
        std::swap(u, v);
    if (u ^ v)
        st.upd(1, dfn[u] + 1, dfn[v], k);
}
inline dat qry(int u, int v)
{
    dat res = 0;
    while (tp[u] ^ tp[v])
    {
        if (d[tp[u]] < d[tp[v]])
            std::swap(u, v);
        res = h(res, st.qry(1, dfn[tp[u]], dfn[u]));
        u = pr[tp[u]];
    }
    if (dfn[u] > dfn[v])
        std::swap(u, v);
    if (u ^ v)
        res = h(res, st.qry(1, dfn[u] + 1, dfn[v]));
    return res;
}

int eu[M], ev[M];
int main()
{
    int n, m;
    scanf("%d", &n);
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        ++u;
        ++v;
        add(u, v, w);
        add(v, u, w);
        eu[i] = u;
        ev[i] = v;
    }
    pre(1, 0);
    dec(1, 1);
    st.init(1, 1, n);
    scanf("%d", &m);
    while (m--)
    {
        char op[10];
        int u, v;
        scanf("%s%d%d", op, &u, &v);
        if (op[0] == 'C')
        {
            if (d[eu[u]] > d[ev[u]])
                std::swap(eu[u], ev[u]);
            st.upd(1, dfn[ev[u]], tag(1, v));
        }
        ++u;
        ++v;
        if (op[0] == 'N')
        {
            tag k(-1, INF);
            upd(u, v, k);
        }
        else if (op[0] == 'S')
            printf("%lld\n", qry(u, v).s);
        else if (op[0] == 'M')
        {
            if (op[1] == 'I')
                printf("%lld\n", qry(u, v).mn);
            else
                printf("%lld\n", qry(u, v).mx);
        }
    }
    return 0;
}