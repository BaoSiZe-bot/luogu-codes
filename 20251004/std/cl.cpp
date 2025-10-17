#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000000007;
const int N = 8005;

int n;
vector <int> gr[N];
int f[N][N], g[N][N], siz[N], tmp[N], ans[N];

inline void Read() {
    cin >> n;
    for (int i = 1;i < n;i++) {
        int u, v;
        cin >> u >> v;
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
}

inline void Dfs1(int u, int fa) {
    siz[u] = 1;
    f[u][1] = 1;
    for (int v : gr[u]) {
        if (v != fa) {
            Dfs1(v, u);
            memcpy(tmp, f[u], sizeof(tmp));
            for (int i = 1;i <= siz[u];i++) {
                for (int j = 1;j <= siz[v];j++) tmp[i + j] = (tmp[i + j] + 1ll * f[u][i] * f[v][j]) % mod;
            }
            memcpy(f[u], tmp, sizeof(f[u]));
            siz[u] += siz[v];
        }
    }
}

inline void Dfs2(int u, int fa) {
    if (fa != -1) {
        for (int i = 1;i <= siz[u];i++) ans[i] = (ans[i] + 1ll * f[u][i] * g[u][i]) % mod;
    }
    for (int v : gr[u]) {
        if (v != fa) {
            g[v][1] = 1;
            for (int i = 2;i <= siz[v];i++) g[v][i] = g[u][i - 1];
            for (int w : gr[u]) {
                if (w != v && w != fa) {
                    for (int i = 0;i <= siz[v];i++) tmp[i] = g[v][i];
                    for (int i = 1;i <= siz[v];i++) {
                        for (int j = 1;j <= siz[w] && i + j <= siz[v];j++) tmp[i + j] = (tmp[i + j] + 1ll * g[v][i] * f[w][j]) % mod;
                    }
                    for (int i = 0;i <= siz[v];i++) g[v][i] = tmp[i];
                }
            }
            Dfs2(v, u);
        }
    }
}

int main() {
    freopen("cl.in", "r", stdin);
    freopen("cl.out", "w", stdout);
    std::ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    Read();
    Dfs1(1, -1);
    Dfs2(1, -1);
    for (int i = 1;i <= n / 2;i++) cout << ans[i] << " ";
    cout << endl;
    return 0;
}
