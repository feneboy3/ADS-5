// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
    T data[size];
    int top_index;

 public:
    TStack() {
        top_index = -1;
    }

    void push(T value) {
        top_index++;
        data[top_index] = value;
    }

    void pop() {
        top_index--;
    }

    T top() {
        return data[top_index];
    }

    bool empty() {
        return top_index == -1;
    }
};

#endif
