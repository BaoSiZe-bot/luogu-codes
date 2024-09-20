//edit by VC 6.0

#include <bits/stdc++.h>

using namespace std;

int dp[10005], a[105];
int main() {
	int n, m, i, j;
	cin >> n >> m;
	for(i = 1; i <= n; ++i)
		cin >> a[i];
	for(i = 1; i <= n; ++i)
		for(j = m; j >= a[i]; --j)
			if(a[i] == j)dp[j]++;
			else dp[j] += dp[j - a[i]];
	cout << dp[m];
	return 0;
}
