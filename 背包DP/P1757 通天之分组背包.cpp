#include <bits/stdc++.h>
using namespace std;
int v, t, w[2005], c[2005], p, a[2005], b[1005][1005], dp[2005], cnt, n;
int main()
{
    cin >> v >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> w[i] >> c[i] >> p;
        cnt = max(t, p);
        a[p]++;
        b[p][a[p]] = i;
    }
    for (int i = 1; i <= cnt; i++)
        for (int j = v; j >= 0; j--)
            for (int k = 1; k <= a[i]; k++)
                if (w[b[i][k]] <= j)
                    dp[j] = max(dp[j], dp[j - w[b[i][k]]] + c[b[i][k]]);
    cout << dp[v];
    return 0;
}
