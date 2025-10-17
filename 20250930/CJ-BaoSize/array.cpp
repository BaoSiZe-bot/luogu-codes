// 人心之邪，落井下石！ *你**
// 不让用 scanf，你居然还把把数据范围开到 O(n^2) 极限还只开 1s 时限
#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::max;
using std::min;

namespace Fujiwara
{
using ll = long long;
const int N = 1e4 + 5;
const int P = 1e9 + 7;

int n, l[N], r[N];

static int Azusa()
{
    ll s = 0;
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> l[i] >> r[i];
    int ml = 0, mr = 0;
    for (int i = 1; i <= n; ++i)
    {
        ml = max(ml, l[i]);
        mr = max(mr, r[i]);
    }
    for (int i = ml; i <= mr; ++i)  // 枚举最大值
    {
        ll t1 = 1, t2 = 1;
        for (int j = 1; j <= n; ++j)  // 钦定最大值已经取到，计算贡献
        {
            int mx = min(r[j], i);  // 限制取值不能大于最大值
            int rl = i - mx + 1;
            int rr = i - l[j] + 1;
            (t1 *= (rr - rl + 1) * (rl + rr) / 2) %= P;
        }
        for (int j = 1; j <= n; ++j)  // 减去最大值没有被取到的错误贡献
        {
            int mx = min(r[j], i - 1);  // 限制取值必须小于最大值
            if (mx < l[j])
            {
                t2 = 0;
                break;
            }
            int rl = i - mx + 1;
            int rr = i - l[j] + 1;
            (t2 *= (rr - rl + 1) * (rl + rr) / 2) %= P;
        }
        (s += ((t1 - t2) % P + P) % P) %= P;
    }
    cout << s;
    return 0;
}
}  // namespace Fujiwara
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    return Fujiwara::Azusa();
}
