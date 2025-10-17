#include <cstdio>
#include <fstream>
#include <utility>
#include <vector>

namespace Fujiwara
{
using std::ifstream;
using std::ofstream;
using std::pair;
using std::vector;

using ll = long long;
const int N = 5e3 + 5;

int f[N][N];
vector<vector<int>> g;
vector<pair<int, int>> qr;

int n, m, q;
ifstream fi;
ofstream fo;
static void fio()
{
    fi.open("A.in");
    fi.tie(nullptr);
    fo.open("A.out");
    fo.tie(nullptr);
}
static int Azusa()
{
    scanf("%d%d%d", &n, &m, &q);
    g.resize(n + 1);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    return 0;
}
}  // namespace Fujiwara
int main()
{
    Fujiwara::fio();
    std::ios::sync_with_stdio(0);
    return Fujiwara::Azusa();
}
