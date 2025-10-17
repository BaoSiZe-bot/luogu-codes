#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000000007;
const int N = 500005;

struct Edge {
    int to, nxt;
    long long len;
};
int n, hd[N], pnt, mxd;
Edge e[N << 1];
long long dep[N];

inline void AddEdge(int u, int v, long long w) {
    e[++pnt].to = v;
    e[pnt].len = w;
    e[pnt].nxt = hd[u];
    hd[u] = pnt;
}

inline void Read() {
    cin >> n;
    for (int i = 1;i < n;i++) {
        int u, v, w; cin >> u >> v >> w;
        AddEdge(u, v, w); AddEdge(v, u, w);
    }
}

inline void Dfs(int u, int fa) {
    if (dep[u] > dep[mxd]) mxd = u;
    for (int i = hd[u];~i;i = e[i].nxt) {
        if (e[i].to != fa) {
            dep[e[i].to] = dep[u] + e[i].len;
            Dfs(e[i].to, u);
        }
    }
}

inline void Solve() {
    dep[1] = 0; mxd = 0; Dfs(1, -1);
    int rt = mxd; mxd = 0; dep[rt] = 0; Dfs(rt, -1);
    cout << dep[mxd] % mod * (mod + 1 >> 1) % mod << endl;
}

int main() {
    freopen("tb.in", "r", stdin);
    freopen("tb.out", "w", stdout);
    std::ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    memset(hd, -1, sizeof(hd));
    Read();
    Solve();
    return 0;
}