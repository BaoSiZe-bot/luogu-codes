#include <set>
#include <stdio.h>
inline int max(int far, int sar)
{
    return far < sar ? sar : far;
}
int arr[1000005];
int main()
{
    freopen("escape.in", "r", stdin);
    freopen("escape.out", "w", stdout);
    int len, mnl;
    scanf("%d%d", &len, &mnl);
    for (int itr = 1; itr <= len; ++itr)
        scanf("%d", arr + itr);
    if (mnl == 0)
    {
        int res = 0, t = 0;
        for (int i = 1; i <= len; ++i)
        {
            t = max(0, t) + arr[i];
            res = max(res, t);
        }
        printf("%d", res);
        return 0;
    }
    if (len <= 1000)
    {
        int res = 0xc0c0c0c0;
        for (int lft = 1; lft <= len - mnl + 1; ++lft)
        {
            std::set<int> prs;
            int sum = 0;
            for (int rgt = lft; rgt <= lft + mnl - 1; ++rgt)
                prs.insert(arr[rgt]);
            int obsolved = 0;
            for (int rgt = lft + mnl; rgt <= len; ++rgt)
                if (*prs.rbegin() > arr[rgt])
                {
                    prs.insert(arr[rgt]);
                    obsolved = *prs.begin();
                    sum += arr[rgt];
                    res = max(res, sum);
                }
                else if (obsolved)
                {
                    sum += obsolved;
                    obsolved = *prs.begin();
                    res = max(res, sum);
                }
        }
        printf("%d", res);
    }
    return 0;
}
