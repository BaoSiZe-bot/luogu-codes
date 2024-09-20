#include <bits/stdc++.h>
#define ri register int
#define FU(i, S, T) for (ri i = S; i <= T; ++i)
#define FD(i, S, T) for (ri i = T; i >= S; --i)
using namespace std;

const int N = 10005, MX = 0x7ffffffe;
int x[N], y[N], l[N], h[N], dp[N][1005];
bool f[N];
int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    FU(i, 0, n - 1) cin >> x[i + 1] >> y[i + 1];
    FU(i, 0, n) h[i] = m + 1;
    FU(i, 0, k - 1)
    {
        int t;
        cin >> t >> l[t] >> h[t];
        f[t] = 1;
    }
    FU(i, 1, n)
    FU(j, 0, m)
    dp[i][j] = MX;
    dp[0][0] = MX;
    FU(i, 1, n)
    {
        int ml = min(m - y[i], h[i] - 1);
        FU(j, x[i], m) dp[i][j] = min({dp[i][j], dp[i - 1][j - x[i]] + 1, dp[i][j - x[i]] + 1});
        FU(j, m - x[i], m) dp[i][m] = min({dp[i][m], dp[i - 1][j] + 1, dp[i][j] + 1});
        FU(j, l[i] + 1, ml) dp[i][j] = min(dp[i][j], dp[i - 1][j + y[i]]);
        FU(j, h[i], m) dp[i][j] = MX;
        FD(j, 1, l[i]) dp[i][j] = MX;
    }
    int mn = MX, t = k;
    FD(i, 1, n)
    {
        FU(j, l[i] + 1, h[i] - 1) mn = min(mn, dp[i][j]);
        if (mn < MX)
            break;
        if (f[i])
            t--;
    }
    if (t == k)
        cout << 1 << endl << mn;
    else
        cout << 0 << endl << t;
    return 0;
}
