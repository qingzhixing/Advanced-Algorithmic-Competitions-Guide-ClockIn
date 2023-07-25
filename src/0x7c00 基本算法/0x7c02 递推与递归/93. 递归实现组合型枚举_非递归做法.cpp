/*
    这是本题的思考题
    正常递归做法状态（走过的路径）是存在系统栈中的，由系统自动维护，
    不使用递归我们直接手动维护一下就好了
    如果我们将递归看成DFS,那么非递归做法就是BFS
*/

#include <iostream>
#include <list>
#include <vector>
using namespace std;

#define NDEBUG
#ifdef NDEBUG
#define DEBUG(code) ((void)0)
#else
#define DEBUG(code) (code)
#endif // NDEBUG

typedef vector<int> State;

list<State> states;

int n, m;

void PrintState(const State &state)
{
    for (auto item : state)
    {
        cout << item << ' ';
    }
    puts("");
}

int main()
{
    cin >> n >> m;
    // 初始化
    states.push_back(State());

    // 开始枚举
    while (states.size())
    {
        // 取状态
        State state = states.front();
        states.pop_front();

        DEBUG(PrintState(state));

        // 判断是否枚举完成
        if (state.size() >= m)
        {
            PrintState(state);
            continue;
        }

        // 根据状态枚举
        int lastNumber;
        if (state.size())
        {
            lastNumber = state.back();
        }
        else
        {
            lastNumber = 0;
        }
        int timeLast = m - state.size();

        // 枚举思路与递归方法类似，枚举的数字需要一个范围
        // 范围是 (lastNumber + 1) ~ (n - timeLast + 1)
        // 这样保证枚举合法并且后面还有数字可以选择
        for (int currentNumber = lastNumber + 1; currentNumber <= (n - timeLast + 1); currentNumber++)
        {
            // 这里是深拷贝
            State newState(state);
            newState.push_back(currentNumber);
            states.push_back(newState);
        }
    }
    return 0;
}