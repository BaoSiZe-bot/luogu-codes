#include <bits/stdc++.h>
#define int long long

using namespace std;
using namespace __gnu_cxx;

const int M = 1e8;

int dp[15][8192][15], f[15][15];
signed main()
{
	int n, m;
	scanf("%lld%lld", &m, &n);	
	for (int i = 1; i <= m; ++i)
		for (int j = 1; j <= n; ++i)
			scanf("%lld", f[i][j]);
	dp[0][0][0] = 1;
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j < (1 << m); ++j)
			for (int k = 0; k < (1 << m); ++k)
			{
				if(j & k)
					continue;
				if(j & (j << 1))
					continue;
				if(j & (j >> 1))
					continue;
				
				bool fl = 1;
				for (int p = 1; p <= m; ++p)
					if(!f[i][p] && (j >> (p - 1) & 1))
						fl = 0;
				if(!fl)
					continue;
				int cnt1 = __builtin_popcountll(j), cnt2 = __builtin_popcountll(k);
				for (int p = cnt1 + cnt2; p <= n * m; ++p)
					if(!p)
						dp[i][j][p] = 1;
					else
						dp[i][j][p] = (dp[i][j][p - cnt2] + dp[i][k][p]) % M;
			}
	int res = 0;
	for (int i = 1; i <= n * m; ++i)
		for (int j = 0; j < (1 << m); ++j)
			res = (res + dp[n][j][i]) % M;
	
	printf("%lld", res);
	return 0;
}
