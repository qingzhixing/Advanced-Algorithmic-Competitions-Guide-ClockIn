/*
    看到这题，我们首先想到的一定是暴力枚举 0 ~ m ，每个算 n 次，复杂度为 O(nm)
    我们有没有什么方法优化呢？
    本题切入点:
        所有运算都是按位运算，并且不会进位借位，
        一个二进制位上的数字只受 操作数的对应位 和 操作符 影响。
        故我们可以按位考虑，贪心处理。
    所以我们现在需要:
        按 位 贪心枚举 一个在区间[0,m]内的数字，使其产生攻击力最大。
        我们由原来的 暴力枚举 O(nm) 转变为了 按位枚举 O(n log m)
    贪心思路:
        对于我们最终枚举的数字a, 产生的最大攻击力ans, 第k位 a_k, ans_k:
        我们可以先算出该位真值表, 算出来无非就四种情况:
            1. 1 -> 0, 0 -> 0
            2. 1 -> 1, 0 -> 0
            3. 1 -> 0, 0 -> 1
            4. 1 -> 1, 0 -> 1
        贪心过程中，有两个核心思想:
            1. 产生结果越大越好, 这个是优先考虑的。
            2. 消耗的预算越少越好: 产生结果相同的情况下放 0.
                这不是说 a 越小越好，是有前提的，在不影响结果的情况下尽量使 a 更小，有利于我们枚举.
        故:(下面是贪心代码的规则)
            1. 真值表01产生结果不同时，a_k为 计算后 能使ans_k = 1的那个数字
                如 第3种真值表 情况时(1 -> 0, 0 -> 1), a_k = 0;
            2. 真值表01产生结果相同时, a_k 为 0

    注意：我们依旧要从高位往低位枚举，当 a_k = 1 时，ans_k 必定为 1(根据贪心规则)
        ans_k这一位的大小= ~(1<<(k-1)) + 1 故高位有一个 1 产生的结果收益比 低位所有位
        都为 1 产生的收益还要多。
        如果我们从低位往高位枚举那么有可能 a的低位1 抢占了本应该有的 a的高位1
        这会使得 ans 中高位 1 变少(ans 的 1来自 0->1 或者 1->1)
        例子见代码中从高位枚举的注释处

    贴一篇看题解过程中比较喜欢的: https://www.luogu.com.cn/blog/user58279/solution-p2114
    代码如下:
*/
#include <iostream>
using namespace std;

enum Operator
{
    OR,
    XOR,
    AND
};

struct Gate
{
    Operator op;
    uint32_t value;
    // 对传入的值根据value的digitId位的二进制数进行二进制运算
    bool DoOperate(bool bitValue, uint8_t digitId)
    {
        bool digit = (value >> digitId) & 1;
        switch (op)
        {
        case OR:
            return bitValue | digit;
        case XOR:
            return bitValue ^ digit;
        case AND:
            return bitValue & digit;
        }
    }

    // 作测试用
    void PrintGateln()
    {
        cout << "op: ";
        switch (op)
        {
        case OR:
            cout << "OR ";
            break;
        case XOR:
            cout << "XOR ";
            break;
        case AND:
            cout << "AND ";
            break;
        }
        cout << "value: " << value << endl;
    }
};

#define MAX_N (uint)(1e5 + 10)
#define MAX_M (uint)(1e9 + 10)

// 为了代码方便，直接定义宏设置变量digit位
#define SET_DIGIT_0(var, digit) (var &= (~(1 << digit)))
#define SET_DIGIT_1(var, digit) (var |= (1 << digit))
#define SET_DIGIT(var, digit, value) \
    (value == 1 ? SET_DIGIT_1(var, digit) : SET_DIGIT_0(var, digit))

// 供测试,可以忽略所有在DEBUG()中的语句
#define NDEBUG
#ifdef NDEBUG
#define DEBUG(code) ((void)0)
#else
#define DEBUG(code) (code)
#endif // NDEBUG

uint32_t n, m;
Gate gate[MAX_N];

// 用于计算第 digitId 位 上的真值表(bitValue 传入两次，为 1 和 0 即可)
bool CalculateGateDigitId(bool bitValue, uint8_t digitId)
{
    for (int i = 0; i < n; i++)
    {
        bitValue = gate[i].DoOperate(bitValue, digitId);
    }
    return bitValue;
}

int main()
{
    // 读入数据
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        char buffer[4];
        scanf("\n%s %d", buffer, &gate[i].value);
        if (buffer[0] == 'O')
        {
            gate[i].op = OR;
        }
        else if (buffer[0] == 'X')
        {
            gate[i].op = XOR;
        }
        else
        {
            gate[i].op = AND;
        }
        DEBUG(gate[i].PrintGateln());
    }

    DEBUG(cout << "Out Of Input\n");

    uint32_t ans = 0;
    uint32_t a = 0; // 我们枚举的最大初始攻击伤害

    /*
        从高位按位枚举 a_digitId.
        对于为什么要从高位枚举可以看一下这个样例:
        2 2
        OR 0
        AND 3
        从低位枚举输出1，高位则输出2
    */
    for (int8_t digitId = 31; digitId >= 0; digitId--)
    {
        // 这一位填写 1 时不超过 m 才能继续判断是否要填 1,否则只能填 0
        if ((a | (1 << digitId)) <= m)
        {
            // 计算当前位的真值表
            bool bool_0 = CalculateGateDigitId(0, digitId); // bool_0 表示输入 0的 真值表值
            bool bool_1 = CalculateGateDigitId(1, digitId); // bool_1 表示输入 1的 真值表值

            DEBUG(printf("Digit:%d bool_0:%d bool_1:%d\n", digitId, bool_0, bool_1));

            // 根据贪心规则:
            // 2. 真值表01产生结果相同时, a_k 为 0
            if (bool_0 == bool_1)
            {
                DEBUG(cout << "Same\n");
                SET_DIGIT_0(a, digitId);
                SET_DIGIT(ans, digitId, bool_0);
            }
            // 1. 真值表01产生结果不同时，a_k为 计算后 能使ans_k = 1的那个数字
            else
            {
                DEBUG(cout << "Diff\n");
                // ans_digitId必定为1，这里我们先设置
                SET_DIGIT_1(ans, digitId);
                if (bool_0 == 1)
                {
                    SET_DIGIT_0(a, digitId);
                }
                else
                {
                    SET_DIGIT_1(a, digitId);
                }
            }
        }
        else
        {
            DEBUG(cout << "a_digitId must be 0\n");
            SET_DIGIT_0(a, digitId);
            bool bool_0 = CalculateGateDigitId(0, digitId);
            SET_DIGIT(ans, digitId, bool_0);
        }

        DEBUG(printf("a now is: %d\n", a));
        DEBUG(printf("ans now is: %d\n", ans));
    }

    cout << ans;
    return 0;
}