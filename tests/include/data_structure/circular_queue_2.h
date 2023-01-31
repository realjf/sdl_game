#ifndef _CIRCULAR_QUEUE_2_H_
#define _CIRCULAR_QUEUE_2_H_

#include <iostream>

template <class T>
class CircularQueue {
private:
    int front;
    int rear;
    T arr[5];
    int itemCount;

public:
    CircularQueue() {
        itemCount = 0;
        front = -1;
        rear = -1;
        for (int i = 0; i < 5; i++) {
            arr[i] = 0;
        }
    }
    bool isEmpty() {
        if (front == -1 && rear == -1)
            return true;
        else
            return false;
    }
    bool isFull() {
        if ((rear + 1) % 5 == front)
            return true;
        else
            return false;
    }
    void enqueue(int val) {
        if (isFull()) {
            cout << "Queue full" << endl;
            return;
        } else if (isEmpty()) {
            rear = 0;
            front = 0;
            arr[rear] = val;

        } else {
            rear = (rear + 1) % 5;
            arr[rear] = val;
        }
        itemCount++;
    }

    int dequeue() {
        int x = 0;
        if (isEmpty()) {
            cout << "Queue is Empty" << endl;
            return x;
        } else if (rear == front) {
            x = arr[rear];
            rear = -1;
            front = -1;
            itemCount--;
            return x;
        } else {
            cout << "front value: " << front << endl;
            x = arr[front];
            arr[front] = 0;
            front = (front + 1) % 5;
            itemCount--;
            return x;
        }
    }

    int count() {
        return (itemCount);
    }
};

#endif /* _CIRCULAR_QUEUE_2_H_ */
