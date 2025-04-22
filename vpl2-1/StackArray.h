#ifndef STACKARRAY_H
#define STACKARRAY_H
#include <iostream>
#include <string>

class StackUnderflow {
public:
    StackUnderflow(std::string message): message{message}{}
    std::string getMessage() const {return message;}
private:
    std::string message;
};

class StackOverflow {
public:
    StackOverflow(std::string message): message{message}{}
    std::string getMessage() const {return message;}
private:
    std::string message;
};

class WrongStackSize {
public:
    WrongStackSize(std::string message): message{message}{}
    std::string getMessage() const {return message;}
private:
    std::string message;
};

template <class T>
class Stack {
public:
    virtual ~Stack() {}
    virtual void push(const T& e) = 0;
    virtual T pop() = 0;
    virtual bool isEmpty() const = 0;
    virtual T peek() const = 0;
    virtual size_t getSize() const = 0;
};

template <class T>
class StackArray: public Stack<T> {
private:
    T* array;
    size_t capacity;
    size_t topIndex;

public:
    StackArray(size_t size) : capacity(size), topIndex(0) {
        if (size == 0) {
            throw WrongStackSize{"Invalid stack size specified"};
        }
        array = new T[size];
    }

    ~StackArray() {
        delete[] array;
    }

    void push(const T& e) override {
        if (topIndex >= capacity) {
            throw StackOverflow{"Stack overflow: cannot push element"};
        }
        array[topIndex++] = e;
    }

    T pop() override {
        if (isEmpty()) {
            throw StackUnderflow{"Stack underflow: cannot pop element"};
        }
        return array[--topIndex];
    }

    bool isEmpty() const override {
        return topIndex == 0;
    }

    T peek() const override {
        if (isEmpty()) {
            throw StackUnderflow{"Cannot peek from empty stack"};
        }
        return array[topIndex-1];
    }

    size_t getSize() const override {
        return topIndex;
    }
};
#endif