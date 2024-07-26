#include <bits/stdc++.h>
using namespace std;
int dp[305][305], s[305], a[305];
int main()
{
    memset(dp, 127, sizeof(dp));
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        int x;
        cin >> x;
        s[i] = s[i - 1] + x;
        a[i] = a[i + n] = x;
        dp[i][i] = 0;
    }
    for (int i = n + 1; i <= (n << 1); ++i)
    {
        s[i] = s[i - 1] + a[i];
        dp[i][i] = 0;
    }
    for (int len = 1; len < n; ++len)
        for (int l = 1; l <= (n << 1) - len; ++l)
        {
            int r = l + len;
            for (int x = l; x < r; ++x)
                dp[l][r] = min(dp[l][r], dp[l][x] + dp[x + 1][r] + s[r] - s[l - 1]);
        }
    int ans = INT_MAX;
    for (int i = 1; i <= n; ++i)
        ans = min(ans, dp[i][i + n - 1]);
    cout << ans << endl;
    memset(dp, 128, sizeof(dp));
    for (int i = 1; i <= (n << 1); ++i)
        dp[i][i] = 0;
    for (int len = 1; len < n; ++len)
        for (int l = 1; l <= (n << 1) - len; ++l)
        {
            int r = l + len;
            for (int x = l; x < r; ++x)
                dp[l][r] = max(dp[l][r], dp[l][x] + dp[x + 1][r] + s[r] - s[l - 1]);
        }
    ans = INT_MIN;
    for (int i = 1; i <= n; ++i)
        ans = max(ans, dp[i][i + n - 1]);
    cout << ans << endl;
    return 0;
}
