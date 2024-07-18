#include <bits/stdc++.h>
using namespace std;
namespace __int256
{
	inline void fft(const vector<int> &r, vector<complex<double>> &A, int type, int limit)
	{
		const double Pi = acos(-1.0);
		for (int i = 0; i < limit; ++i)
			if (i < r[i])
			{
				A[i] += A[r[i]];
				A[r[i]] = A[i] - A[r[i]];
				A[i] -= A[r[i]];
			}
		for (int mid = 1; mid < limit; mid <<= 1)
		{
			complex<double> Wn(cos(Pi / mid), type * sin(Pi / mid));
			for (int R = mid << 1, j = 0; j < limit; j += R)
			{
				complex<double> w(1, 0);
				for (int k = 0; k < mid; ++k)
				{
					complex<double> x = A[j + k], y = w * A[j + mid + k];
					A[j + k] = x + y;
					A[j + mid + k] = x - y;
					w *= Wn;
				}
			}
		}
	}
	string operator*(const string &s1, const string &s2)
	{
		int N, M, l = 0, limit = 1;
		N = s1.size() - 1;
		M = s2.size() - 1;
		while (limit <= N + M)
		{
			limit <<= 1;
			++l;
		}
		vector<complex<double>> aa(3 * limit + 5), bb(3 * limit + 5);
		for (int i = N; ~i; --i)
			aa[i].real(s1[N - i] ^ 48);
		for (int i = M; ~i; --i)
			bb[i].real(s2[M - i] ^ 48);
		vector<int> r(limit + 5);
		for (int i = 0; i < limit; i++)
			r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
		fft(r, aa, 1, limit);
		fft(r, bb, 1, limit);
		for (int i = 0; i <= limit; i++)
			aa[i] *= bb[i];
		fft(r, aa, -1, limit);
		int len = N + M;
		vector<int> res;
		for (int i = 0; i <= len; i++)
			res.push_back(int(aa[i].real() / limit + 0.5));
		for (int i = 0; i < len; i++)
			if (res[i] > 10)
			{
				res[i + 1] += res[i] / 10;
				res[i] %= 10;
			}
		while (res.back() == 0)
			res.pop_back();
		while (res.back() > 10)
		{
			int t = res.back();
			res.back() %= 10;
			res.push_back(t / 10);
		}
		string ans;
		for (int i = res.size() - 1; ~i; --i)
			ans += to_string(res[i]);
		return ans;
	}
	class BigInt
	{
	public:
		string val;
		char f;
		BigInt()
		{
			ios::sync_with_stdio(0);
			cin.tie(0);
			cout.tie(0);
			val = "0";
			f = '+';
		}
		BigInt(const BigInt &x)
		{
			ios::sync_with_stdio(0);
			cin.tie(0);
			cout.tie(0);
			val = x.val;
			f = x.f;
		}
		BigInt(long long x)
		{
			ios::sync_with_stdio(0);
			cin.tie(0);
			cout.tie(0);
			if (x >= 0)
			{
				val = to_string(x);
				f = '+';
			}
			else
			{
				x = ~x + 1;
				val = to_string(x);
				f = '-';
			}
		}
		BigInt(const string &x)
		{
			ios::sync_with_stdio(0);
			cin.tie(0);
			cout.tie(0);
			val = (x.front() == '-' ? x.substr(1) : x);
			f = (x.front() == '-' ? '-' : '+');
		}
		bool operator<(const BigInt &x) const
		{
			if (f == '+' && x.f == '+')
				return val.size() == x.val.size() ? val < x.val : val.size() < x.val.size();
			else if (f == '+' && x.f == '-')
				return false;
			else if (f == '-' && x.f == '+')
				return true;
			else
				return val.size() == x.val.size() ? val > x.val : val.size() > x.val.size();
		}
		bool operator==(const BigInt &x) const
		{
			return val == x.val && f == x.f;
		}
		bool operator>(const BigInt &x) const
		{
			if (f == '+' && x.f == '+')
				return val.size() == x.val.size() ? val > x.val : val.size() > x.val.size();
			else if (f == '-' && x.f == '+')
				return false;
			else if (f == '+' && x.f == '-')
				return true;
			else
				return val.size() == x.val.size() ? val < x.val : val.size() < x.val.size();
		}
		bool operator<=(const BigInt &x) const
		{
			return *this < x || *this == x;
		}
		bool operator>=(const BigInt &x) const
		{
			return *this > x || *this == x;
		}
		bool operator!=(const BigInt &x) const
		{
			return val != x.val || f != x.f;
		}
		BigInt &operator=(const string &x)
		{
			val = (x.front() == '-' ? x.substr(1) : x);
			f = (x.front() == '-' ? '-' : '+');
			return *this;
		}
		BigInt &operator=(const BigInt &x)
		{
			val = x.val;
			f = x.f;
			return *this;
		}
		BigInt &operator=(long long x)
		{
			if (x >= 0)
			{
				val = to_string(x);
				f = '+';
			}
			else
			{
				x = ~x + 1;
				val = to_string(x);
				f = '-';
			}
			return *this;
		}
		BigInt operator-(BigInt x) const
		{
			char flg = '+';
			string a = val, b = x.val, c = "";
			if (*this < x)
			{
				flg = '-';
				swap(a, b);
			}
			if (f == '+' && x.f == '-')
			{
				x.f = '+';
				return *this + x;
			}
			if (f == '-' && x.f == '+')
			{
				BigInt tmp(*this);
				tmp.f = '+';
				tmp += x;
				tmp.f = '-';
				return tmp;
			}
			if (f == '-' && x.f == '-')
			{
				BigInt p(*this), q(x);
				p.f = '+';
				q.f = '+';
				return q - p;
			}
			reverse(a.begin(), a.end());
			reverse(b.begin(), b.end());
			for (int i = 0; i < b.size(); ++i)
			{
				int tmp = a[i] - b[i];
				if (tmp < 0)
				{
					int j = i + 1;
					for (; j < a.size() && a[j] == '0'; ++j)
						a[j] = '9';
					a[j]--;
					tmp += 10;
				}
				c += tmp + '0';
			}
			for (int i = b.size(); i < a.size(); ++i)
				c += a[i];
			while (c.back() == '0' && c.size() > 1)
				c.pop_back();
			reverse(c.begin(), c.end());
			BigInt t(c);
			t.f = flg;
			return t;
		}
		BigInt &operator-=(const BigInt &x)
		{
			return *this = *this - x;
		}
		BigInt operator+(const BigInt &x) const
		{
			if (f == '-' && x.f == '+')
			{
				BigInt tmp(*this);
				tmp.f = '+';
				return x - tmp;
			}
			if (f == '+' && x.f == '-')
			{
				BigInt tmp(x);
				tmp.f = '+';
				return *this - tmp;
			}
			char flg = '+';
			if (f == '-' && x.f == '-')
				flg = '-';
			string a = val, b = x.val, c = "";
			int add = 0, i = 0;
			size_t pm = min(a.size(), b.size());
			reverse(a.begin(), a.end());
			reverse(b.begin(), b.end());
			for (; i < pm; ++i)
			{
				int t = (a[i] ^ 48) + (b[i] ^ 48) + add;
				add = t / 10;
				c += t % 10 + '0';
			}
			if (i < a.size())
				for (; i < a.size(); ++i)
				{
					int t = (a[i] ^ 48) + add;
					add = t / 10;
					c += t % 10 + '0';
				}
			if (i < b.size())
				for (; i < b.size(); ++i)
				{
					int t = (b[i] ^ 48) + add;
					add = t / 10;
					c += t % 10 + '0';
				}
			while (add > 0)
			{
				c += add % 10 + '0';
				add /= 10;
			}
			while (c.back() == '0' && c.size() > 1)
				c.pop_back();
			reverse(c.begin(), c.end());
			BigInt tmp = c;
			tmp.f = flg;
			return tmp;
		}
		BigInt &operator+=(const BigInt &x)
		{
			return *this = *this + x;
		}
		BigInt operator*(const BigInt &x) const
		{
			char flg = '+';
			string a = val, b = x.val, ans;
			if ((f == '-' && x.f == '+') || (f == '+' && x.f == '-'))
				flg = '-';
			ans = a * b;
			BigInt tmp(ans);
			tmp.f = flg;
			return tmp;
		}
		BigInt &operator*=(const BigInt &x)
		{
			return *this = *this * x;
		}
		BigInt operator/(const BigInt &x) const
		{
			if (x == (BigInt)0)
				throw "runtime error:divided by zero.";
			if (*this == x)
				return (BigInt)1;
			if (x == (BigInt)1)
				return *this;
			BigInt r = (BigInt)0;
			if ((f == '-' && x.f == '+') || (f == '+' && x.f == '-'))
			{
				BigInt a = *this, b = x, c;
				a.f = '+';
				b.f = '+';
				c = a / b;
				c.f = '-';
				return c;
			}
			if (x > *this)
				return 0;
			string diver = val, c = "";
			//			exit(114514);
			for (char i : diver)
			{
				if (c == "0" || c.empty())
					c = "0";
				else
					c += "0";
				if (r.val == "0" || r.val.empty())
					r.val = to_string(i ^ 48);
				else
					r.val += i;
				//				cout << c << " " << r << endl;
				while (r >= x)
				{
					r -= x;
					c[c.size() - 1]++;
				}
				//				cout << c << " " << r << endl << endl;
			}
			reverse(c.begin(), c.end());
			while (c.back() == '0' && c.size() > 1)
				c.pop_back();
			reverse(c.begin(), c.end());
			return c;
		}
		BigInt &operator/=(const BigInt &x)
		{
			return *this = *this / x;
		}
		BigInt operator%(const BigInt &x) const
		{
			if (x == (BigInt)0)
				throw "runtime error:mod by zero.";
			if (*this == x || x == (BigInt)1)
				return 0;
			return *this - *this / x * x;
		}
		BigInt &operator%=(const BigInt &x)
		{
			return *this = *this % x;
		}
		friend istream &operator>>(istream &is, BigInt &x)
		{
			x.val = "";
			x.f = '+';
			char ch;
			is >> noskipws >> ch;
			for (; ch < '0' || ch > '9'; is >> ch)
				ch == '-' && (x.f = (x.f == '+') ? '-' : '+');
			for (; ch >= '0' && ch <= '9'; is >> ch)
				x.val += ch;
			is >> skipws;

			return is;
		}
		friend ostream &operator<<(ostream &os, const BigInt &x)
		{
			if (x.f == '-')
				os << '-';
			os << x.val;
			return os;
		}
		operator int()
		{
			int x;
			stringstream ss;
			ss << val;
			ss >> x;
			return f == '-' ? ~x + 1 : x;
		}
		operator long()
		{
			long x;
			stringstream ss;
			ss << val;
			ss >> x;
			return f == '-' ? ~x + 1 : x;
		}
		operator short()
		{
			short x;
			stringstream ss;
			ss << val;
			ss >> x;
			return f == '-' ? ~x + 1 : x;
		}
		operator unsigned short()
		{
			unsigned short x;
			stringstream ss;
			ss << val;
			ss >> x;
			return x;
		}
		operator unsigned()
		{
			unsigned x;
			stringstream ss;
			ss << val;
			ss >> x;
			return x;
		}
		operator unsigned long()
		{
			unsigned long x;
			stringstream ss;
			ss << val;
			ss >> x;
			return x;
		}
		operator long long()
		{
			long long x;
			stringstream ss;
			ss << val;
			ss >> x;
			return f == '-' ? ~x + 1 : x;
		}
		operator unsigned long long()
		{
			size_t x;
			stringstream ss;
			ss << val;
			ss >> x;
			return x;
		}
		operator float()
		{
			float x;
			stringstream ss;
			ss << val;
			ss >> x;
			return f == '-' ? -x : x;
		}
		operator double()
		{
			double x;
			stringstream ss;
			ss << val;
			ss >> x;
			return f == '-' ? -x : x;
		}
		operator long double()
		{
			long double x;
			stringstream ss;
			ss << val;
			ss >> x;
			return f == '-' ? -x : x;
		}
		operator bool()
		{
			return val == "0" ? 0 : 1;
		}
		operator char()
		{
			return (char)(int)*this;
		}
		BigInt operator++()
		{
			return *this += 1;
		}
		BigInt operator--()
		{
			return *this -= 1;
		}
		BigInt operator+()
		{
			return *this;
		}
		BigInt operator-()
		{
			BigInt res(*this);
			res.f = (f == '-' ? '+' : '-');
			return res;
		}
	} zero = 0, one = 1, two = 2, five = 5, eight = 8, ten = 10;
	inline BigInt Abs(const BigInt &a)
	{
		BigInt t = a;
		t.f = '+';
		return t;
	}
	inline BigInt Gcd(BigInt a, BigInt b)
	{
		// Decreases technique
		BigInt t = Abs(a - b);
		t.f = '+';
		while (t != zero)
		{
			a = b;
			b = t;
			t = Abs(a - b);
		}
		return b;
	}
	inline BigInt Lcm(const BigInt &a, const BigInt &b)
	{
		return a * b / Gcd(a, b);
	}
	inline BigInt Pow(BigInt a, BigInt b) // O(b*log10(a)*log2(b))
	{
		BigInt res = 1;
		while (b)
		{
			char ch = b.val.back();
			if ((ch - '0') & 1)
				res *= a;
			a *= a;
			b /= 2;
//			cout << a << " " << b << " " << res << endl;
		}
		return res;
	}
	inline BigInt Fact(const BigInt &x)
	{
		BigInt res = 1;
		for (BigInt i = 1; i <= x; ++i)
			res *= i;
		return res;
	}
	inline BigInt SmallSqrt(const BigInt &x)
	{
		if (x.val == "0")
			return zero;
		if (x < (BigInt)4)
			return one;
		if (x < (BigInt)9)
			return two;
		if (x < (BigInt)16)
			return (BigInt)3;
		if (x < (BigInt)25)
			return (BigInt)4;
		if (x < (BigInt)36)
			return (BigInt)5;
		if (x < (BigInt)49)
			return (BigInt)6;
		if (x < (BigInt)64)
			return (BigInt)7;
		if (x < (BigInt)81)
			return (BigInt)8;
		return (BigInt)9;
	}
	inline BigInt Sqrt(const BigInt &x)
	{
		if (x.f == '-')
		{
			cerr << "没事负数开什么方?!!";
			exit(3);
		}
		if (x.val.size() <= 2)
			return SmallSqrt(x);
		BigInt Twenty = (BigInt)20, res = SmallSqrt((BigInt)x.val.substr(0, 2)), r = (BigInt)x.val.substr(0, 2) - res * res;
		string sqrter = x.val;
		int i;
		if (sqrter.size() % 2 == 0)
			i = 2;
		else
		{
			res = SmallSqrt(BigInt(sqrter[0] ^ 48));
			r = BigInt(sqrter[0] ^ 48) - res * res;
			i = 1;
		}
		while (i < sqrter.size())
		{
			BigInt tmp = res * Twenty;
			r = r * ten * ten + BigInt((sqrter[i] ^ 48) * 10 + (sqrter[i + 1] ^ 48));
			BigInt tmp2 = r / tmp;
			while ((tmp + tmp2) * tmp2 > r)
				--tmp2;
			res = res * ten + tmp2;
			r -= (tmp + tmp2) * tmp2;
			i += 2;
		}
		return res;
	}
	// Cbrt竖式学不费，只能写个二分法草草了事惹。
	inline BigInt Cbrt(const BigInt &x)
	{
		if (x.f == '+')
		{
			BigInt l = one, r = x, ans;
			while (l <= r)
			{
				BigInt mid = (l + r) / two;
				if (mid * mid * mid <= x)
				{
					ans = mid;
					l = mid + one;
				}
				else
					r = mid - one;
			}
			return ans;
		}
		BigInt tmp = x;
		tmp.f = '+';
		tmp = Cbrt(tmp);
		tmp.f = '-';
		return tmp;
	}
} // namespace __int256
using namespace __int256;
BigInt a, b;
int main()
{
    cin >> a >> b;
    cout << a + b << endl << a - b << endl << a * b << endl << a / b << endl << a % b;
    return 0;
}
