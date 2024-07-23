#include <bits/stdc++.h>

using namespace std;

char s[55];
int dp[55][55];

int main()
{
    cin.tie(0) -> sync_with_stdio(0);
    cin >> (s + 1);
	int len = strlen(s + 1);
	memset(dp, 127, sizeof(dp));
	for (int i = 1; i <= len; ++i)
		dp[i][i] = 1;
	for (int i = 1; i < len; ++i)
		for (int j = 1; j <= len - i; ++j)
		{
			int k = i + j;
			if (s[j] ^ s[k])
				for (int l = j; l < k; ++l)
					dp[j][k] = min(dp[j][k], dp[j][l] + dp[l + 1][k]);
			else
				dp[j][k] = min(dp[j + 1][k], dp[j][k - 1]);
		}
	printf("%d", dp[1][len]);
	return 0;
}
