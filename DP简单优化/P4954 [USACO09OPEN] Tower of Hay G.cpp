#include <stdio.h>

int a[100005], s[100005], q[100005], h[100005], dp[100005];
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = n; i; --i)
    {
        scanf("%d", a + i);
    }
    for (int i = 1; i <= n; ++i)
        s[i] = s[i - 1] + a[i];
    int hd = 1, tl = 0, t = 0;
    for (int i = 1; i <= n; ++i)
    {
        while (hd <= tl && s[q[hd]] + h[q[hd]] <= s[i])
            ++hd;
        t = q[hd - 1];
        h[i] = s[i] - s[t];
        dp[i] = dp[t] + 1;
        while (hd <= tl && s[i] + h[i] <= s[q[tl]] + h[q[tl]])
            --tl;
        q[++tl] = i;
    }
    printf("%d", dp[n]);
    return 0;
}
