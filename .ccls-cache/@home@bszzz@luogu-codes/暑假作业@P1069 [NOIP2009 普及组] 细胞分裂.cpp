#include <bits/stdc++.h>

#define int long long
#pragma clang diagnostic ignored "-Wregister"
#pragma clang diagnostic ignored "-Wshift-op-parentheses"

using namespace std;
using namespace __gnu_cxx;
//using namespace __gnu_pbds;

template <class T> inline void rd(T &x)
{
	x = 0;
	register int f = 1;
	register char c = getchar();
	for (; c < 48 || c > 57; c = getchar())
		c == 45 && (f = ~f + 1);
	for (; c > 47 && c < 58; c = getchar())
		x = (x << 1) + (x << 3) + (c ^ 48);
	x *= f;
}
template <class T, class... S> inline void rd(T &x, S &...y)
{
	rd(x);
	rd(y...);
}

int a[10005];
map<int, int> p;

inline int cel(int a, int b)
{
	return a < b ? 0 : a % b ? a / b + 1 : a / b;
}

signed main()
{
	ios::sync_with_stdio(0);
	int n, m1, m2;
	rd(n, m1, m2);

	if (m1 == 1)
	{
		printf("0");
		return 0;
	}

	for (int i = 1; i <= n; ++i)
		rd(a[i]);

	int m = m1;
	for (int i = 2; i * i <= m; ++i)
		if (m1 % i == 0)
		{
			p[i] = m2;
			m1 /= i;
			while (m1 % i == 0)
			{
				p[i] += m2;
				m1 /= i;
			}
		}
	if (m1 != 1)
		p[m1] = m2;
//	for (auto i : p)
//	{
//		i.second *= m2;
//		printf("%lld %lld\n", i.first, i.second);
//	}
//    printf("\n");

	int res = INT_MAX, pos = 1;
	for (int i = 1; i <= n; ++i)
	{
		m = a[i];
		map<int, int> q;
		for (int j = 2; j * j <= m; ++j)
			if (a[i] % j == 0)
			{
				q[j] = 1;
				a[i] /= j;
				while (a[i] % j == 0)
				{
					++q[j];
					a[i] /= j;
				}
			}
		if (a[i] != 1)
			q[a[i]] = 1;

		bool f = 1;
		int t = INT_MIN, pt = 1;
		for (auto j : p)
		{
			if (!q.count(j.first))
			{
				f = 0;
				break;
			}
//            printf("%lld %lld %lld %lld\n", j.first, j.second, q[j.first], cel(j.second, q[j.first]));
			t = max(t, cel(j.second, q[j.first]));
		}
		if (f)
		{
			if(res > t)
			{
				res = t;
				pos = m;
			}
		}
	}
	if (res == INT_MAX)
		printf("-1");
	else
		printf("%lld", res);
	return 0;
}
