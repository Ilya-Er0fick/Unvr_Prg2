#include <iostream>
#include "Queue.h"

int main() {
    try {
        QueueList<int> queue;

        std::cout << "Queue is empty: " << (queue.isEmpty() ? "true" : "false") << std::endl;

        queue.enQueue(10);
        queue.enQueue(20);
        queue.enQueue(30);

        std::cout << "Queue size: " << queue.getSize() << std::endl;
        std::cout << "Front element: " << queue.peekFront() << std::endl;

        std::cout << "Dequeued: " << queue.deQueue() << std::endl;
        std::cout << "Dequeued: " << queue.deQueue() << std::endl;

        std::cout << "Queue is empty: " << (queue.isEmpty() ? "true" : "false") << std::endl;
        std::cout << "Front element: " << queue.peekFront() << std::endl;

        try {
            QueueList<int> emptyQueue;
            emptyQueue.deQueue();
        } catch (const QueueUnderflow& ex) {
            std::cout << "Underflow error: " << ex.what() << std::endl;
        }

    } catch (const QueueOverflow& ex) {
        std::cout << "Overflow error: " << ex.what() << std::endl;
    } catch (const std::exception& ex) {
        std::cout << "Error: " << ex.what() << std::endl;
    }

    return 0;
}