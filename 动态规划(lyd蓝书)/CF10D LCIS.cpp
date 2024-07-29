#include <bits/stdc++.h>
using namespace std;
int dp[3005], a[3005], b[3005], pre[3005], n, m;
inline void print(int x)
{
    if (!x)
        return;
    print(pre[x]);
    cout << b[x] << " ";
}
int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    cin >> m;
    for (int i = 1; i <= m; ++i)
        cin >> b[i];
    for (int i = 1; i <= n; ++i)
    {
        int t = 0;
        for (int j = 1; j <= m; ++j)
        {
            if (a[i] == b[j])
            {
                dp[j] = dp[t] + 1;
                pre[j] = t;
            }
            if (a[i] > b[j] && dp[t] < dp[j])
                t = j;
        }
    }
    int ans = 0;
    for (int i = 1; i <= m; ++i)
        if (dp[i] > dp[ans])
            ans = i;
    cout << dp[ans] << endl;
    print(ans);
    return 0;
}
