#include <stdio.h>
unsigned dp[4005];
const unsigned INF=0x80000000;
int main()
{
    int n;
    scanf("%d", &n);
    dp[0] =1;
    for (int i = 1; i <= n; ++i)  //enumerate the volume
      for (int j = i; j <= n; ++j)
            dp[j] = (dp[j] + dp[j - i]) % INF;
    printf("%u\n", dp[n] - 1);
    return 0;
}
