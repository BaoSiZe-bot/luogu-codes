#include <bits/stdc++.h>

using namespace std;

string s;
int dp[30005];
signed main()
{
    int n, s = 0;
    scanf("%d",&n);
    for (int i = 1; i <= n; ++i)
    {
        int t1, t2, t3;
        scanf("%d%d%d", &t1, &t2, &t3);
        s += max({t1, t2, t3});
        for (int j = s; j >= 0; --j)
        {
            int mn = 0x3f3f3f3f;
            if (t1 && j - t1 >= 0)
                mn = min(mn, dp[j - t1]);
            if (t3 && j - t3 >= 0)
                mn = min(mn, dp[j - t3] + t3);
            if (t2)
                mn = min(mn, dp[j] + t2);
            dp[j] = mn;
        }
    }
    int mx = 0x3f3f3f3f;
    for (int i = 0; i <= s; ++i)
        mx = min(mx, max(i, dp[i]));
    printf("%d", mx);
    return 0;
}
