#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>
#include <vector>

//#define ONLINE_JUDGE "I miss zhr."
using std::greater;
using std::sort;
using std::vector;

const int N = 2e5 + 5, K = 26;
vector<int> cs[K];
int T, n;
char s[N];
int res[N];

inline void clr()
{
    for (int i = 0; i < 26; ++i)
        cs[i].clear();
    memset(res, 0, sizeof(res));
    scanf("%d%s", &n, s + 1);
}
inline void pre()
{
    int cnt = 1;
    for (int i = 2; i <= n + 1; ++i)
    {
        if (s[i] == s[i - 1])
            ++cnt;
        else
        {
            cs[s[i - 1] - 'a'].emplace_back(cnt);
            cnt = 1;
        }
    }
    for (int i = 0; i < 26; ++i)
        sort(cs[i].begin(), cs[i].end(), greater<int>());
}
inline void get()
{
    for (int i = 0; i < 26; ++i)
    {
        int s = 0;
        for (int j = 0; j < cs[i].size(); ++j)
        {
            s += cs[i][j];
            res[j] = std::max(res[j], s);
        }
        for (int j = cs[i].size(); j <= n; ++j)
            res[j] = std::max(res[j], s);
    }
}
void out()
{
    for (int i = 0; i <= n; ++i)
        printf("%d ", res[i]);
    printf("\n");
}
inline void solve()
{
    clr();
    pre();
    get();
    out();
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("str.in", "r", stdin);
    freopen("str.out", "w", stdout);
#endif
    scanf("%d", &T);
    while (T--)
        solve();
    return 0;
}
