#include <bits/stdc++.h>

using namespace std;

int a[550][550];
int dp[1050][550][55];
int main()
{
    int n, m;
    cin >> m >> n;
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> a[i][j];
    memset(dp, -1, sizeof(dp));
    dp[2][1][1] = 0;
    for (int p = 3; p < n + m; ++p)
        for (int i = 1; i < n; ++i)
            for (int j = i + 1; j <= n; ++j)
            {
                int t = dp[p][i][j];
                t = max({t, dp[p - 1][i][j], dp[p - 1][i - 1][j], dp[p - 1][i][j - 1], dp[p - 1][i - 1][j - 1]});
                if (t == -1)
                    continue;
                dp[p][i][j] = t + a[p - i][i] + a[p - j][j];
            }
    cout << dp[m + n - 1][n - 1][n];
    return 0;
}
