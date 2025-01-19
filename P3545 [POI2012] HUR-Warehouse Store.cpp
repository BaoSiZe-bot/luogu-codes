#include <queue>
#include <stdio.h>
#include <vector>
using std::vector;
using std::priority_queue;
using ll = long long;
const int N = 2.5e5 + 5;
int a[N], b[N];
template <typename _Tp> struct mycmp
{
    bool operator()(const _Tp &x, const _Tp &y) const
    {
        return b[x] < b[y];
    }
};
priority_queue<int, vector<int>, mycmp<int>> pq;
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", a + i);
    for (int i = 1; i <= n; ++i)
        scanf("%d", b + i);
    ll tot = 0;
    for (int i = 1; i <= n; ++i)
    {
        tot += a[i];
        if (tot < b[i] && !pq.empty())
        {
            int top = pq.top();
            if (b[top] > b[i])
            {
                pq.pop();
                tot += b[top];
            }
        }
        if (tot >= b[i])
        {
            pq.push(i);
            tot -= b[i];
        }
    }
    printf("%zu\n", pq.size());
    while (!pq.empty())
    {
        printf("%d ", pq.top());
        pq.pop();
    }
    return 0;
}
