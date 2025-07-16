#include <algorithm>
#include <cassert>
#include <cstdio>
#include <utility>
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 23, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 23], *p1 = buf, *p2 = buf;
inline void rd(int &x)
{
    x = 0;
    int f = 1;
    char c = getchar();
    for (; c < 48 || c > 57; c = getchar())
        c == 45 && (f = ~f + 1);
    for (; c > 47 && c < 58; c = getchar())
        x = (x << 1) + (x << 3) + (c ^ 48);
    x *= f;
}
const int N = 4e5 + 5, M = 2e5 + 5;
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
    int l, r, s, cl, cr;
    dat(int _l = N, int _r = 0, int _s = 0, int _cl = -1, int _cr = -1) : l(_l), r(_r), s(_s), cl(_cl), cr(_cr) {}
};
struct tag
{
    int k;
    tag(int _k = 0) : k(_k) {}
    bool operator==(const tag &other) const
    {
        return k == other.k;
    }
};
const tag tt;
const dat dd;
__attribute__((always_inline)) inline dat f(const tag &t, const dat &d)
{
    if (t == tt)
        return d;
    return dat{d.l, d.r, d.r - d.l, t.k, t.k};
}
__attribute__((always_inline)) inline tag g(const tag &x, const tag &y)
{
    if (x == tt)
        return y;
    return x;
}
__attribute__((always_inline)) inline dat h(const dat &a, const dat &b)
{
    if (a.l > a.r)
        return b;
    if (b.l > b.r)
        return a;
    return dat{a.l, b.r, a.s + b.s + (a.cr == b.cl), a.cl, b.cr};
}
template <const size_t N, typename dat, typename tag, typename T, T I[]> struct SegmentTree
{
#define ci const int &
#define ct const tag &
#define cd const dat &
    dat d[N];
    tag t[N];
    void clear(int n)
    {
        for (int i = 1; i <= n << 2; ++i)
        {
            d[i] = dd;
            t[i] = tt;
        }
    }
    void init(ci rt, ci l, ci r)
    {
        d[rt] = {l, r, 0};
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
int w[N], a[N];
SegmentTree<N << 2, dat, tag, int, a> st;

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
inline int get_col(int x)
{
    return x ? st.qry(1, dfn[x], dfn[x]).cl : -1;
}
inline int qry(int u, int v)
{
    int s = 0;
    while (tp[u] ^ tp[v])
    {
        if (d[tp[u]] < d[tp[v]])
            std::swap(u, v);
        dat q = st.qry(1, dfn[tp[u]], dfn[u]);
        s += q.s + (q.cl == get_col(pr[tp[u]]));
        u = pr[tp[u]];
    }
    if (d[u] > d[v])
        std::swap(u, v);
    if (u != v)
        s += st.qry(1, dfn[u], dfn[v]).s;
    return s;
}
inline void cln(int n, int m)
{
    cnt = 0;
    pts = 0;
    st.clear(n);
    for (int i = 1; i <= n; ++i)
    {
        w[i] = a[i] = m + n + i;  // 默认颜色不能重叠，因为全是轻边
        ed[i] = 0; // 初始化边表
        d[i] = p[i] = pr[i] = tp[i] = rk[i] = num[i] = dfn[i] = 0;
    }
}

inline void init(int n, int m)
{
    cln(n, m);
    for (int i = 2; i <= n; ++i)
    {
        int u, v;
        rd(u);
        rd(v);
        add(u, v);
        add(v, u);
    }
    pre(1, 0);
    dec(1, 1);
    st.init(1, 1, n);
}

inline void opt(int id)
{
    int op, a, b;
    rd(op);
    rd(a);
    rd(b);
    if (op == 1)
        upd(a, b, id);
    else
        printf("%d\n", qry(a, b));
}

inline void solve()
{
    int n, m;
    rd(n);
    rd(m);
    init(n, m);
    for (int i = 1; i <= m; ++i)
        opt(i);
}

int main()
{
    int T;
    rd(T);
    while (T--)
        solve();
    return 0;
}