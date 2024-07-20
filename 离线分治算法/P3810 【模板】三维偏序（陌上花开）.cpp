#import <cstdio>
#import <algorithm>

using std::pair;
using std::sort;
pair<pair<int, int>, pair<int, int>> pr[100005];
int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d%d", &pr[i].first.first, &pr[i].first.second, &pr[i].second.first);
    sort(pr + 1, pr + n + 1);
    return 0;
}
