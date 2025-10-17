#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000000007, N = 100055;
int n, m, tcnt;
long long inv[N], ifac[N];
char opt[N];
struct DP {
	long long poolf[N*3], fgm, sum, ssum, poolt[N*3], clr0t, _time, *f, *t, addv, clr0v;
	inline void Init() {
		_time = clr0t = 1;
		f = poolf + 180000;
		t = poolt + 180000;
		fgm = ssum = sum = addv = 0;
	}
	inline void Pushdown(int idx) {
		if (t[idx] < clr0t) {
			f[idx] = clr0v;
			t[idx] = clr0t;
		}
	}
	inline void Add(int idx, long long val) {
		Pushdown(idx);
		_time++;
		t[idx] = _time;
		f[idx] = (f[idx] + val) % mod;
		sum = (sum + val) % mod;
		ssum = (ssum + (idx - 1) * val % mod + mod) % mod;
	}
	inline long long qVal(int idx) {
		Pushdown(idx);
		return (f[idx] + addv) % mod;
	}
	inline void Shift() {
		sum = (sum - qVal(m) + mod) % mod;
		ssum = (ssum - qVal(m) * (m - 1) % mod + mod) % mod;
		fgm = (fgm + qVal(m)) % mod;
		f--;
		t--;
		ssum = (ssum + sum) % mod;
		_time++;
		t[0] = _time;
		f[0] = (mod - addv) % mod;
	}
	inline void Clr0() {
		_time++;
		clr0v = (mod - addv) % mod;
		clr0t = _time;
		sum = 0;
		ssum = 0;
	}
	inline void totAdd(long long x) {
		addv = (addv + x) % mod;
		sum = (sum + (m + 1) * x) % mod;
		ssum = (ssum + 1ll * (m + 1) * (m - 2) / 2 % mod * x) % mod;
		_time++;
	}
	inline long long Sum() {
		return sum;
	}
	inline long long SSum() {
		return (ssum + qVal(0)) % mod;
	}
};
DP dp;
pair <long long, long long> tr[2005];

inline void Prefix() {
	inv[1] = ifac[0] = ifac[1] = 1;
	for (int i = 2;i <= m + 5;i++) ifac[i] = ifac[i - 1] * (inv[i] = (mod - mod / i) * inv[mod % i] % mod) % mod;
}

inline long long Power(long long x, long long y) {
	long long ans = 1;
	while (y) {
		if (y & 1) ans = ans * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ans;
}

inline void Solve() {
	dp.Init();
	for (int i = 1;i <= m;i++) dp.Add(i, 1);
	for (int i = 1;i < n - 1;i++) {
		long long add = dp.qVal(1);
		if (opt[i] == 'A') {
			tr[++tcnt] = make_pair(0, (dp.SSum() + m * dp.fgm) % mod);
			tr[++tcnt] = make_pair(1, dp.qVal(0) * m % mod);
			long long fac = 1;
			for (int i = 2;i <= m;i++) {
				fac *= i;
				if (fac > m) break;
				long long tmp = fac, v = dp.qVal(i);
				for (int j = i;tmp <= m;j++) {
					tr[++tcnt] = make_pair(tmp, v);
					tmp = tmp / (j - i + 1) * (j + 1);
				}
			}
			dp.Clr0();
		} else {
			tr[++tcnt] = make_pair(0, (dp.SSum() + m * dp.fgm + mod) % mod);
			tr[++tcnt] = make_pair(1, (dp.Sum() + (m - 2) * dp.qVal(0) - dp.qVal(1) + 2 * mod) % mod);
			tr[++tcnt] = make_pair(2, (mod - dp.qVal(1)) % mod);
			for (int i = 2;i <= m;i++) {
				long long cob = 1ll * (i + 2) * (i + 1) / 2;
				if (cob > m) break;
				long long v = dp.qVal(i);
				for (int j = 3;cob <= m;j++) {
					tr[++tcnt] = make_pair(cob, v);
					cob = cob * (i + j) / j;
				}
			}
			dp.Shift();
		}
		dp.totAdd(add);
		dp.Add(0, (mod - add) % mod);
		while (tcnt) {
			dp.Add(tr[tcnt].first, tr[tcnt].second);
			tcnt--;
		}
		dp.fgm = (Power(m, i + 1) - dp.Sum() + mod) % mod;
	}
	long long ans = m * dp.qVal(0) % mod, ffp = m + 1;
	for (int i = 1;i <= m;i++) {
		ffp = ffp * (m - i + 1) % mod;
		if (opt[n - 1] == 'A') ans = (ans + ffp * inv[i + 1] % mod * dp.qVal(i)) % mod;
		else ans = (ans + ffp * ifac[i + 1] % mod * dp.qVal(i)) % mod;
	}
	cout << ans << endl;
}

int main() {
    freopen("gl.in", "r", stdin);
    freopen("gl.out", "w", stdout);
	cin >> n >> m >> opt + 1;
	Prefix();
	Solve();
	return 0;
}