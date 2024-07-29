#include <bits/stdc++.h>

using namespace std;

int dp[200005], a[105][105];

inline int max(int a, int b)
{
	return a > b ? a : b;
}

int main()
{
	int s, n, m;
	scanf("%d%d%d", &s, &n, &m);
	for (int i = 1; i <= s; ++i)
		for (int j = 1; j <= n; ++j)
		{
			scanf("%d", a[j] + i);
			a[j][i] = a[j][i] << 1 | 1;
		}
	for (int i = 1; i <= n; ++i)
	{
		sort(a[i] + 1, a[i] + s + 1);
		for (int j = m; j; --j)
			for (int k = 1; k <= s; ++k)
				j >= a[i][k] && (dp[j] = max(dp[j], dp[j - a[i][k]] + i * k));
	}
	printf("%d", dp[m]);
	return 0;
}
