#ifndef QUEUELIST_H
#define QUEUELIST_H

#include <string>
#include <stdexcept>
#include <new>

class QueueUnderflow : public std::runtime_error {
public:
    explicit QueueUnderflow(const std::string& message) 
        : std::runtime_error(message) {}
};

class QueueOverflow : public std::runtime_error {
public:
    explicit QueueOverflow(const std::string& message) 
        : std::runtime_error(message) {}
};

template <class T>
class Queue {
public:
    virtual ~Queue() = default;
    virtual void enQueue(const T& e) = 0;
    virtual T deQueue() = 0;
    virtual bool isEmpty() const = 0;
    virtual T peekFront() const = 0;
    virtual size_t getSize() const = 0;
};

template <class T>
class QueueList : public Queue<T> {
private:
    struct Node {
        T data;
        Node* next;
        explicit Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* front;
    Node* rear;
    size_t size;

public:
    QueueList() : front(nullptr), rear(nullptr), size(0) {}

    ~QueueList() override {
        while (!isEmpty()) {
            deQueue();
        }
    }

    void enQueue(const T& e) override {
        try {
            Node* newNode = new Node(e);

            if (isEmpty()) {
                front = rear = newNode;
            } else {
                rear->next = newNode;
                rear = newNode;
            }
            size++;
        } catch (const std::bad_alloc&) {
            throw QueueOverflow("Memory allocation failed");
        }
    }

    T deQueue() override {
        if (isEmpty()) {
            throw QueueUnderflow("Queue underflow");
        }

        Node* temp = front;
        T value = temp->data;

        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }

        delete temp;
        size--;
        return value;
    }

    bool isEmpty() const override {
        return front == nullptr;
    }

    T peekFront() const override {
        if (isEmpty()) {
            throw QueueUnderflow("Cannot peek from empty queue");
        }
        return front->data;
    }

    size_t getSize() const override {
        return size;
    }

    QueueList(const QueueList&) = delete;
    QueueList& operator=(const QueueList&) = delete;
};

#endif