#include <algorithm>
#include <cstdio>

const int ULE = -1; // 无效赋值
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
    int mn;
    dat(int _l = 0, int _r = 0, int _mn = INT_MAX) : l(_l), r(_r), mn(_mn) {}
};

struct tag
{
    int b;  // 赋值
    tag(int _b = ULE) : b(_b) {}
    bool operator==(const tag &other) const 
    {
        return b == other.b;
    }
};
const tag tt;
const dat dd;
__attribute__((always_inline)) inline dat f(const tag &t, const dat &d)
{
    if (t == tt)
        return d;
    return dat{d.l, d.r, t.b};
}
__attribute__((always_inline)) inline tag g(const tag &x, const tag &y)
{
    if (x == tt)
        return y;
    return x;
}
__attribute__((always_inline)) inline dat h(const dat &a, const dat &b)
{
    return dat{a.l, b.r, std::min(a.mn, b.mn)};
}
template <const size_t N, typename dat, typename tag, typename T, T I[]> struct SegmentTree
{
#define ci const int &
#define ct const tag &
#define cd const dat &
    dat d[N];
    tag t[N];
    void init(ci rt, ci l, ci r)
    {
        d[rt] = {l, r};
        t[rt] = tt;
        if (l == r)
        {
            d[rt].mn = I[l];
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
int w[N], a[N];
SegmentTree<N << 2, dat, tag, int, a> st;

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
    st.upd(1, dfn[u], dfn[v], k);
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
        res = h(res, st.qry(1, dfn[u], dfn[v]));
    return res;
}
inline int get_son(int u, int v) //在u-v链上找u的直系儿子(u是祖先)
{
    while (tp[u] != tp[v])
    {
        if (pr[tp[v]] == u)
            return tp[v];
        v = pr[tp[v]];
    }
    return e[p[u]].v;
}
inline int get(int x, int r)
{
    if (x == r)
        return st.qry(1, 1, n).mn;
    if (dfn[x] >= dfn[r] || dfn[x] + num[x] - 1 < dfn[r])
        return st.qry(1, dfn[x], dfn[x] + num[x] - 1).mn;
    int p = get_son(x, r);
    int lt = dfn[p] - 1, rt = dfn[p] + num[p];
    return std::min(st.qry(1, 1, lt).mn, rt > n ? INT_MAX : st.qry(1, rt, n).mn);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    for (int i = 1; i <= n; ++i)
        scanf("%d", w + i);
    int r;
    scanf("%d", &r);
    pre(1, 0);
    dec(1, 1);
    st.init(1, 1, n);
    while (m--)
    {
        int op;
        scanf("%d", &op);
        if (op == 1)
            scanf("%d", &r);
        else if (op == 2)
        {
            int x, y, v;
            scanf("%d%d%d", &x, &y, &v);
            upd(x, y, {v});
        }
        else
        {
            int x;
            scanf("%d", &x);
            printf("%d\n", get(x, r));
        }
    }
    return 0;
}