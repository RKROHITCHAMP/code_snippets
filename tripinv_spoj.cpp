#include <bits/stdc++.h>
using namespace std;
class BIT{
    vector<int> bit;
public:
    BIT(int n) : bit(n+1) { }
    void update(int i, int val) {
        for(;i <= bit.size(); i += i & -i) bit[i] += val;
    }
    int query(int i) {  // returns number of elements in [0...i]
        int res = 0;
        for(;i > 0; i -= i & -i) res += bit[i];
        return res;
    }
};
int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    vector<int> right(n + 1), left(n + 1);

    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
        right[arr[i]]++;
        update(arr[i], 1, n);
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {

        right[arr[i]]--;
        update(arr[i], -1, n);
        int c1 = sum(arr[i] - 1);
        int c2 = sum2(n) - sum2(arr[i]);
        ans += c1 * c2;

        left[arr[i]]++;
        update2(arr[i], 1, n);
    }
    cout << ans << endl;

    return 0;
}