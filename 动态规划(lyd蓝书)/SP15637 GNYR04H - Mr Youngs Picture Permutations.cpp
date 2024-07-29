#include <bits/stdc++.h>
#include <cstring>
#define int long long

using namespace std;
int a[35], dp[35][35][35][35][35];
signed main()
{
    int k;
    while (scanf("%lld", &k), k)
    {
        memset(a, 0, sizeof a);
        for (int i = 1; i <= k; i++)
            scanf("%lld", a + i);
        memset(dp, 0, sizeof(dp));
        dp[0][0][0][0][0] = 1;
        for (int i = 0; i <= a[1]; ++i)
            for (int j = 0; j <= a[2]; ++j)
                for (int k = 0; k <= a[3]; ++k)
                    for (int p = 0; p <= a[4]; ++p)
                        for (int l = 0; l <= a[5]; ++l)
                        {
                            dp[i + 1][j][k][p][l] += dp[i][j][k][p][l];
                            if (j < i)
                                dp[i][j + 1][k][p][l] += dp[i][j][k][p][l];
                            if (k < j)
                                dp[i][j][k + 1][p][l] += dp[i][j][k][p][l];
                            if (p < k)
                                dp[i][j][k][p + 1][l] += dp[i][j][k][p][l];
                            if (l < p)
                                dp[i][j][k][p][l + 1] += dp[i][j][k][p][l];
                        }
        printf("%lld\n", dp[a[1]][a[2]][a[3]][a[4]][a[5]]);
    }
    return 0;
}
