#include <cstdio>

namespace Fujiwara
{
using ll = long long;
const int N = 1005;
const ll M = 998244353;
int __id, n, l, a[N], p[N], f[N];

ll res;
static void dfs(int x)
{
	if (x == n + 1)
	{
		ll t = 1;
		for (int i = 1; i <= n; ++i)
		{
			ll cnt = 0;
			for (int j = p[i]; j < a[i]; j += l)
				++cnt;
			(t *= cnt) %= M;
		}
		(res += t) %= M;
	}
	for (int i = 0; i < l; ++i)
		if (!f[i])
		{
			f[i] = 1;
			p[x] = i;
			dfs(x + 1);
			f[i] = 0;
		}	
}

static void input()
{
	scanf("%d%d%d", &__id, &n, &l);
	for (int i = 1; i <= n; ++i)
		scanf("%d", a + i);
}


static int Azusa()
{
	input();
	if (n <= 8 && l <= 9)
	{
		dfs(1);
		printf("%lld\n", res);
		return 0;
	}
    return 0;
}
} // namespace Fujiwara

int main()
{
	freopen("number.in", "r", stdin);
	freopen("number.out", "w", stdout);
    return Fujiwara::Azusa();
}