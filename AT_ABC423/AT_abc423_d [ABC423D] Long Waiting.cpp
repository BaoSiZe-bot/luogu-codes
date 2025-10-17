#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
namespace Fujiwara
{
using std::max;
using std::vector;

struct gr
{
    long long a, b, c, t;
    int x;
    gr() : a(0), b(0), c(0), t(0), x(0) {}
    bool operator<(const gr &nbr) const
    {
        return a < nbr.a;
    }
};
vector<gr> g;
vector<int> q;

static int Azusa()
{
    int n;
    long long K;
    scanf("%d%lld", &n, &K);

    g.resize(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld%lld%lld", &g[i].a, &g[i].b, &g[i].c);
        g[i].x = i;
        g[i].t = 0;
    }

    std::queue<int> q;
    using P = std::pair<long long, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> dep;

    long long t = 0;
    long long s = 0;
    int i = 1;
    int entered = 0;

    while (entered < n)
    {
        // Advance time if needed
        if ((q.empty() && i <= n && t < g[i].a) || (!q.empty() && s + g[q.front()].c > K))
        {
            long long next_t = (long long)4e18;
            if (i <= n)
                next_t = std::min(next_t, g[i].a);
            if (!dep.empty())
                next_t = std::min(next_t, dep.top().first);
            if (next_t == (long long)4e18)
                break;
            t = std::max(t, next_t);
        }

        // Process all departures at time t
        while (!dep.empty() && dep.top().first <= t)
        {
            s -= g[dep.top().second].c;
            dep.pop();
        }
        // Process all arrivals at time t
        while (i <= n && g[i].a <= t)
        {
            q.push(i);
            ++i;
        }
        // Let groups enter as much as possible at time t
        bool entered_any = false;
        while (!q.empty() && s + g[q.front()].c <= K)
        {
            int id = q.front();
            q.pop();
            g[id].t = t;
            s += g[id].c;
            dep.emplace(t + g[id].b, id);
            ++entered;
            entered_any = true;
        }
        if (!entered_any)
        {
            long long next_t = (long long)4e18;
            if (i <= n)
                next_t = std::min(next_t, g[i].a);
            if (!dep.empty())
                next_t = std::min(next_t, dep.top().first);
            if (next_t == (long long)4e18)
                break;
            t = next_t;
        }
    }

    for (int j = 1; j <= n; ++j)
        printf("%lld\n", g[j].t);
    return 0;
}
}  // namespace Fujiwara
int main()
{
    return Fujiwara::Azusa();
}

