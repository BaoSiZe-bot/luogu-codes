#include <algorithm>
#include <cstdio>
namespace Fujiwara
{
const int N = 2e6 + 5, NN = 2e5 + 5;

struct Edge
{
    int v, p;
} e[N << 1];
int ed[N], cnt, n, m, q;
static void add(int u, int v)
{
    e[++cnt] = {v, ed[u]};
    ed[u] = cnt;
}
int d[N], a[N], ft[23][N];
static void dfs(int ro, int fa)
{
    ft[0][ro] = fa;
    d[ro] = d[fa] + 1;
    for (int i = 1; i <= 20; ++i)
        ft[i][ro] = ft[i - 1][ft[i - 1][ro]];
    for (int i = ed[ro]; i; i = e[i].p)
        if (e[i].v != fa)
            dfs(e[i].v, ro);
}
static int lca(int u, int v)
{
    if (d[u] < d[v])
        u ^= v ^= u ^= v;
    for (int i = 22; ~i; --i)
    {
        if (d[ft[i][u]] >= d[v])
            u = ft[i][u];
        if (u == v)
            return u;
    }
    for (int i = 22; ~i; --i)
        if (ft[i][u] != ft[i][v])
        {
            u = ft[i][u];
            v = ft[i][v];
        }
    return ft[0][u];
}

struct dat
{
    int l, r;
    int mn;
};
struct tag
{
    int x = 0;
    bool operator==(const tag &nbr) const
    {
        return x == nbr.x;
    }
};
static dat f(const tag &t, const dat &d)
{
    dat nw = d;
    nw.mn = std::max(1, nw.mn + t.x);
    return nw;
}
static tag g(const tag &x, const tag &y)
{
    tag nw = x;
    nw.x += y.x;
    return nw;
}
static dat h(const dat &a, const dat &b)
{
    dat nw;
    nw.l = a.l;
    nw.r = b.r;
    nw.mn = std::min(a.mn, b.mn);
    return nw;
}
static dat lf(int x, int id)
{
    dat lf;
    lf.l = lf.r = id;
    lf.mn = x;
    return lf;
}
static const tag tt;
template <const size_t N, typename dat, typename tag, typename T, T I[]> struct SegmentTree
{
#define ci const int &
#define ct const tag &
#define cd const dat &
    dat d[N];
    tag t[N];
    void init(ci rt, ci l, ci r)
    {
        t[rt] = tt;
        if (l == r)
        {
            d[rt] = lf(I[l], l);
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
        if (l <= d[rt].l && d[rt].r <= r)
            return d[rt];
        pushdown(rt);
        int mid = (d[rt].l + d[rt].r) >> 1;
        if (r <= mid)
            return qry(rt << 1, l, r);
        if (l > mid)
            return qry(rt << 1 | 1, l, r);
        return h(qry(rt << 1, l, r), qry(rt << 1 | 1, l, r));
    }
#undef ci
#undef ct
#undef cd
};
SegmentTree<(NN << 2), dat, tag, int, a> st;
static void solve1()
{
    st.init(1, 1, n);
    while (q--)
    {
        int op, l, r;
        scanf("%d%d%d", &op, &l, &r);
        if (op == 1)
            st.upd(1, l, r, {-1});
        else
            printf("%d\n", st.qry(1, l, r).mn);
    }
}
static int Azusa()
{
    scanf("%d%d%d", &n, &m, &q);
    bool fl = 1;
    for (int i = 2, x; i <= n; ++i)
    {
        scanf("%d", &x);
        fl &= (x == i - 1);
        add(i, x);
        add(x, i);
    }
    for (int i = 1; i <= m; ++i)
        scanf("%d", a + i);
    if (fl)
    {
        solve1();
        return 0;
    }
    dfs(1, 1);
    while (q--)
    {
        int op, l, r;
        scanf("%d%d%d", &op, &l, &r);
        if (op == 1)
        {
            for (int i = l; i <= r; ++i)
                a[i] = ft[0][a[i]];
        }
        else
        {
            if (l == r)
            {
                printf("%d\n", a[l]);
                continue;
            }
            int p = lca(a[l], a[l + 1]);
            for (int i = l + 2; i <= r && p > 1; ++i)
                p = lca(p, a[i]);
            printf("%d\n", p);
        }
    }
    return 0;
}
}  // namespace Fujiwara
int main()
{
    freopen("ac.in", "r", stdin);
    freopen("ac.out", "w", stdout);
    return Fujiwara::Azusa();
}
