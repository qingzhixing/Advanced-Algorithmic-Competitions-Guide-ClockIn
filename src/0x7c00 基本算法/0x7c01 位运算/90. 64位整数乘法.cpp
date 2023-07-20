// 我们这里采用和快速幂类似的思路的快速乘积，拆成二进制位相乘求和
// 快速乘：https://www.cnblogs.com/812-xiao-wen/p/10543023.html
// 当然，STL也提供了一个足够优秀的类型：__int128，可以直接使用
#include <iostream>
using namespace std;
uint64_t a, b, p;
int main()
{
    cin >> a >> b >> p;
    uint64_t ans = 0;

    if (a == 0 || b == 0)
    {
        cout << 0;
        return 0;
    }

    while (b)
    {
        if (b & 1)
        {
            ans = (ans + a) % p;
        }
        b >>= 1;
        a = (a << 1) % p;
    }

    cout << ans;
    return 0;
}