/*
    对于哈密顿路径这种np完全问题来说，主要思考方向是暴力+优化
    我们使用dfs或者dp直接做的话，走过的路径就是状态，有(20-2)!种
    18!=10^16，显然不能这么做，所以我们需要通过找到哈密顿路径的一些性质优化状态数量

    对于两条路径:

    0 -> 1 -> 2 -> 3    v = 18
    0 -> 2 -> 1 -> 3    v = 20

    我们可以发现，都经过了 0 1 2 3 四个点，且最后一个点都在 3 上
    于是对于基于 路径2 的任意路径 0 -> 2 -> 1 -> 3 -> i -> j -> ... -> k    v = 20 + n
    我们都可以转移到 路径1 上 ：0 -> 1 -> 2 -> 3 -> i -> j -> ... -> k      v = 18 + n
    我们可以发现，路径1 始终是优于 路径2 的，路径2 可以舍去

    故我们可以这样总结：
    状态转移过程中我们只需要关注两点:
    1. 我们走过了哪些点 - state
    2. 停留在了哪个点 - j

    据此我们可以列出状态集合:f [state] [j]
    state:2^20  j:20
    f大小：2^20 * 20 = 2*10^7   显然已经优化了一大截

    我们推导一下状态转移方程（其实我们只用枚举一下f [state] [j]怎么来的就好）
    f [state] [j] = f [state_k] [k] + weight[k][j];
    state_k = state 去掉 j 之后的状态。并且要合法，所以要包含k
*/
#include <cstring> // memset()
#include <iostream>
using namespace std;

#define MAX_STATE (1 << 20)
#define MAX_N 21

int f[MAX_STATE][MAX_N], weight[MAX_N][MAX_N];
int n;

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            cin >> weight[i][j];
        }

    // 初始化状态数组
    memset(f, 0x3f, sizeof f);
    f[1][0] = 0;

    for (int state = 0; state < (1 << n); state++)
    {
        for (int j = 0; j < n; j++)
        {
            // 判断state是否合法
            if (!((state >> j) & 1))
                continue;
            for (int k = 0; k < n; k++)
            {
                int state_k = state - (1 << j);
                // 判断state_k是否合法
                if ((state_k >> k) & 1)
                {
                    // 状态转移
                    f[state][j] = min(f[state][j], f[state_k][k] + weight[k][j]);
                }
            }
        }
    }

    cout << f[(1 << n) - 1][n - 1];
    return 0;
}