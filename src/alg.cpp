// Copyright 2025 NNTU-CS
#include <string>
#include <cctype>
#include "tstack.h"

int priority(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

int calc(int a, int b, char op) {
    if (op == '+')
        return a + b;
    if (op == '-')
        return a - b;
    if (op == '*')
        return a * b;
    if (op == '/')
        return a / b;
    return 0;
}

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> stack;
    std::string result = "";

    for (size_t i = 0; i < inf.length(); i++) {

        if (isdigit(inf[i])) {
            while (i < inf.length() && isdigit(inf[i])) {
                result += inf[i];
                i++;
            }
            result += ' ';
            i--;
        }

        else if (inf[i] == '(') {
            stack.Push('(');
        }

        else if (inf[i] == ')') {
            while (!stack.IsEmpty() && stack.Top() != '(') {
                result += stack.Top();
                result += ' ';
                stack.Pop();
            }
            stack.Pop();
        }

        else if (inf[i] == '+' || inf[i] == '-' ||
                 inf[i] == '*' || inf[i] == '/') {

            while (!stack.IsEmpty() &&
                   priority(stack.Top()) >= priority(inf[i])) {

                result += stack.Top();
                result += ' ';
                stack.Pop();
            }

            stack.Push(inf[i]);
        }
    }

    while (!stack.IsEmpty()) {
        result += stack.Top();
        result += ' ';
        stack.Pop();
    }

    if (!result.empty())
        result.pop_back();

    return result;
}

int eval(const std::string& post) {
    TStack<int, 100> stack;

    for (size_t i = 0; i < post.length(); i++) {

        if (isdigit(post[i])) {
            int num = 0;

            while (i < post.length() && isdigit(post[i])) {
                num = num * 10 + (post[i] - '0');
                i++;
            }

            stack.Push(num);
        }

        else if (post[i] == '+' || post[i] == '-' ||
                 post[i] == '*' || post[i] == '/') {

            int b = stack.Top();
            stack.Pop();

            int a = stack.Top();
            stack.Pop();

            stack.Push(calc(a, b, post[i]));
        }
    }

    return stack.Top();
}
