// スタックを実装し、逆ポーランド記法パーサーを作る企画

#include <iostream>

constexpr int n_buffer = 1024;
int buffer[n_buffer];
int top;

bool is_full()
{
    return top == n_buffer - 1;
}

bool is_empty()
{
    return top == 0;
}

void push(int value)
{
    if (is_full())
        exit(1);
    top++;
    buffer[top] = value;
}

int pop()
{
    if (is_empty())
        exit(1);
    int value = buffer[top];
    top--;
    return value;
}

int main()
{
    auto math = "1 2 + 3 4 - *";

    while (*math)
    {
        if (*math == ' ')
        {
            ++math;
            continue;
        }

        if (isdigit(*math))
        {
            push(strtol(math, (char**)&math, 10));
            continue;
        }

        if (*math == '*')
        {
            ++math;
            int r = pop();
            int l = pop();
            push(l * r);
            continue;
        }

        if (*math == '/')
        {
            ++math;
            int r = pop();
            int l = pop();
            push(l / r);
            continue;
        }

        if (*math == '+')
        {
            ++math;
            int r = pop();
            int l = pop();
            push(l + r);
            continue;
        }

        if (*math == '-')
        {
            ++math;
            int r = pop();
            int l = pop();
            push(l - r);
            continue;
        }

        exit(1);
    }

    std::cout << pop() << std::endl;
}
