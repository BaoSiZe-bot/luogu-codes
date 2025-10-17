#include <bits/stdc++.h>
using namespace std;

const int N = 2000005, M = 300005;

struct Edge {
    int to, nxt;
    Edge() {
        nxt = -1;
    }
};
int n, hd[N], pnt, dfn[N], idx[N], _time, top[N], siz[N], son[N], dep[N], fa[N], a[M], cdp[N], m, q;
Edge e[N];

struct Segtree {
    int mnd[M << 2], mxd[M << 2], mds[M << 2], tag[M << 2];
    inline void Update(int p) {
        mnd[p] = min(mnd[p << 1], mnd[p << 1 | 1]);
        mxd[p] = max(mxd[p << 1], mxd[p << 1 | 1]);
        mds[p] = min(mds[p << 1], mds[p << 1 | 1]);
    }
    inline void putTag(int p, int d) {
        mnd[p] += d; mxd[p] += d; mds[p] += d; tag[p] += d;
    }
    inline void Pushdown(int p) {
        if (tag[p]) {
            putTag(p << 1, tag[p]);
            putTag(p << 1 | 1, tag[p]);
            tag[p] = 0;
        }
    }
    inline void Build(int p, int pl, int pr) {
        tag[p] = 0;
        if (pl == pr) {
            mnd[p] = mxd[p] = dfn[a[pl]];
            mds[p] = cdp[a[pl]];
            return;
        }
        int mid = pl + pr >> 1;
        Build(p << 1, pl, mid); Build(p << 1 | 1, mid + 1, pr);
        Update(p);
    }
    inline void Modify(int p, int pl, int pr, int l, int r) {
        if (pl == l && pr == r) {
            if (mds[p] > 0) {
                putTag(p, -1);
                return;
            }
            if (pl == pr) {
                mnd[p] = mxd[p] = dfn[fa[idx[mnd[p]]]];
                mds[p] = cdp[idx[mnd[p]]];
                return;
            }
            Pushdown(p);
            int mid = pl + pr >> 1;
            Modify(p << 1, pl, mid, l, mid);
            Modify(p << 1 | 1, mid + 1, pr, mid + 1, r);
            Update(p);
            return;
        }
        Pushdown(p);
        int mid = pl + pr >> 1;
        if (mid >= r) Modify(p << 1, pl, mid, l, r);
        else if (mid + 1 <= l) Modify(p << 1 | 1, mid + 1, pr, l, r);
        else {
            Modify(p << 1, pl, mid, l, mid);
            Modify(p << 1 | 1, mid + 1, pr, mid + 1, r);
        }
        Update(p);
    }
    inline int qMin(int p, int pl, int pr, int l, int r) {
        if (pl == l && pr == r) return mnd[p];
        Pushdown(p);
        int mid = pl + pr >> 1;
        if (mid >= r) return qMin(p << 1, pl, mid, l, r);
        else if (mid + 1 <= l) return qMin(p << 1 | 1, mid + 1, pr, l, r);
        else return min(qMin(p << 1, pl, mid, l, mid), qMin(p << 1 | 1, mid + 1, pr, mid + 1, r));
    }
    inline int qMax(int p, int pl, int pr, int l, int r) {
        if (pl == l && pr == r) return mxd[p];
        Pushdown(p);
        int mid = pl + pr >> 1;
        if (mid >= r) return qMax(p << 1, pl, mid, l, r);
        else if (mid + 1 <= l) return qMax(p << 1 | 1, mid + 1, pr, l, r);
        else return max(qMax(p << 1, pl, mid, l, mid), qMax(p << 1 | 1, mid + 1, pr, mid + 1, r));
    }
};
Segtree sgt;

inline void AddEdge(int u, int v) {
    e[++pnt].to = v;
    e[pnt].nxt = hd[u];
    hd[u] = pnt;
}

inline void Read() {
    cin >> n >> m >> q;
    for (int i = 2;i <= n;i++) {
        cin >> fa[i];
        AddEdge(fa[i], i);
    }
    for (int i = 1;i <= m;i++) cin >> a[i];
}

inline void Dfs1(int u) {
    siz[u] = 1;
    for (int i = hd[u];~i;i = e[i].nxt) {
        dep[e[i].to] = dep[u] + 1;
        Dfs1(e[i].to);
        siz[u] += siz[e[i].to];
        if (siz[e[i].to] > siz[son[u]]) son[u] = e[i].to;
    }
}

inline void Dfs2(int u, int tp) {
    top[u] = tp;
    dfn[u] = ++_time;
    idx[_time] = u;
    if (son[u]) {
        cdp[son[u]] = cdp[u] + 1;
        Dfs2(son[u], tp);
    }
    for (int i = hd[u];~i;i = e[i].nxt) {
        if (e[i].to != son[u]) {
            cdp[e[i].to] = 0;
            Dfs2(e[i].to, e[i].to);
        }
    }
}

inline int Lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    return u;
}

inline void Solve() {
    sgt.Build(1, 1, m);
    while (q--) {
        int opt, l, r;
        cin >> opt >> l >> r;
        if (opt == 1) sgt.Modify(1, 1, m, l, r);
        else {
            int x = max(1, sgt.qMax(1, 1, m, l, r)), y = max(sgt.qMin(1, 1, m, l, r), 1);
            cout << Lca(idx[x], idx[y]) << "\n";
        }
    }
}

int main() {
    freopen("ac.in", "r", stdin);
    freopen("ac.out", "w", stdout);
    std::ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    memset(hd, -1, sizeof(hd));
    Read();
    dep[1] = 1; Dfs1(1);
    cdp[1] = 0x3f3f3f3f; Dfs2(1, 1);
    Solve();
    return 0;
}
