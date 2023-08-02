/*
    这题的递推思路是：锁定第一行，从第二行开始操作，第一行是0的位置第二行就按，
        使之变为1，这样，后面一行就由前面一行确定，整个方案由第一行决定
        我们想要枚举所有答案，我们只需要枚举第一行的初始情况(按法)就行。
        我们发现，最后一行没有下一行，无法改变了，所以我们这样认为：
            若最后一行非全1则该方案非法。
    算法复杂度=第一行所有按法(32)*每种情况递推复杂度(20)*每次按下开关需要的操作数(5)=160,0000
*/
#include <cstring>
#include <iostream>
#include <stdint.h>
using namespace std;

#define NDEBUG
#ifdef NDEBUG
#define DEBUG(code) ((void)0)
#else
#define DEBUG(code) (code)
#endif // NDEBUG

#define MAX_SIZE (5 + 10)
#define INF ((int)1e10)
#define NUM_IDX(number, digit) (number >> digit & 1)

char graph[MAX_SIZE][MAX_SIZE];

int T;

// 五个方位分别为中间，上下左右
const int8_t dx[5] = {0, 0, 0, -1, 1}, dy[5] = {0, -1, 1, 0, 0};

// 模拟按按钮操作
void PushButton(int x, int y)
{
    // 枚举五个方位
    for (int direction = 0; direction < 5; direction++)
    {
        int newX = x + dx[direction];
        int newY = y + dy[direction];
        // 判断按钮位置是否合法
        if (newX < 0 || newX >= 5 || newY < 0 || newY > 5)
            continue;
        // 位运算简化切换状态表达式
        graph[newX][newY] ^= 1;
    }
}

void DebugPrintGraph()
{
#ifdef NDEBUG
    return;
#endif
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            DEBUG(cout << graph[i][j] << ' ');
        }
        DEBUG(puts(""));
    }
}

bool CheckLastLine()
{
    for (int i = 0; i < 5; i++)
    {
        if (graph[4][i] != '1')
            return false;
    }
    return true;
}

int Solution()
{
    int ans = INF;

    // 创建备份，每种情况的枚举都会破坏原数组
    int graphBackup[MAX_SIZE][MAX_SIZE];
    memcpy(graphBackup, graph, sizeof graphBackup);

    // 枚举第一行所有按法
    // 1-按 0-不按
    // 状态压缩5个0/1变成一个int类型变量
    for (int firstLine = 0; firstLine < (1 << 5); firstLine++)
    {
        // 恢复graph
        memcpy(graph, graphBackup, sizeof graph);

        // 本次情况的操作数
        int res = 0;

        // 执行枚举的操作
        for (int digit = 0; digit < 5; digit++)
        {
            if (NUM_IDX(firstLine, digit) == 1)
            {
                res++;
                PushButton(0, digit);
            }
        }

        // 按2~4行
        // 后面一行的状态由前面的行决定，故此处枚举1~3行
        for (int line = 0; line < 4; line++)
        {
            for (int buttonIdx = 0; buttonIdx < 5; buttonIdx++)
            {
                // 上一行为0这一行就按
                if (graph[line][buttonIdx] == '0')
                {
                    res++;
                    PushButton(line + 1, buttonIdx);
                }
            }
        }

        DEBUG(printf("firstLine: %d\n", firstLine));
        DebugPrintGraph();
        DEBUG(printf("res: %d  CheckLastLine: %d\n\n", res, CheckLastLine()));

        // 检查合法性，合法就更新ans
        if (CheckLastLine())
        {
            ans = min(ans, res);
        }
    }

    return ans > 6 ? -1 : ans;
}

int main()
{
    cin >> T;
    while (T--)
    {
        // 输入数据
        for (int i = 0; i < 5; i++)
            cin >> graph[i];
        DEBUG(cout << "Input complete!\n");

        cout << Solution() << endl;
    }
    return 0;
}