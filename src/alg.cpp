// Copyright 2025 NNTU-CS
#include <string>
#include <cctype>
#include "tstack.h"

int priority(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

int calc(int a, int b, char op) {
    if (op == '+') {
        return a + b;
    } else if (op == '-') {
        return a - b;
    } else if (op == '*') {
        return a * b;
    } else if (op == '/') {
        return a / b;
    }
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
        } else if (inf[i] == '(') {
            stack.push('(');
        } else if (inf[i] == ')') {
            while (!stack.empty() && stack.top() != '(') {
                result += stack.top();
                result += ' ';
                stack.pop();
            }
            stack.pop();
        } else if (inf[i] == '+' || inf[i] == '-' ||
                   inf[i] == '*' || inf[i] == '/') {
            while (!stack.empty() &&
                   priority(stack.top()) >= priority(inf[i])) {
                result += stack.top();
                result += ' ';
                stack.pop();
            }
            stack.push(inf[i]);
        }
    }
    while (!stack.empty()) {
        result += stack.top();
        result += ' ';
        stack.pop();
    }
    if (!result.empty()) {
        result.pop_back();
    }
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
            stack.push(num);
        } else if (post[i] == '+' || post[i] == '-' ||
                   post[i] == '*' || post[i] == '/') {
            int b = stack.top();
            stack.pop();
            int a = stack.top();
            stack.pop();
            stack.push(calc(a, b, post[i]));
        }
    }
    return stack.top();
}
