#ifndef _CIRCULAR_QUEUE_H_
#define _CIRCULAR_QUEUE_H_

#include <iostream>
#include <vector>

template <class T>
class CircularQueue {
public:
    CircularQueue();

    // 获取队列中的元素数量
    int queueSize();

    /// 元素入队
    void enQueue(T t);

    /// 元素出队
    T deQueue();

private:
    // 队列自增长
    // void addQueueSize();

    /// 设置出队index
    void setBackToZero();

    /// 设置出队index
    void setFrontToZero();

private:
    // 队列出队index
    int m_iFront;
    // 队列入队Index
    int m_iBack;
    // 队列中元素数量
    int m_iSize;
    // 队列的初始长度设置为3
    std::vector<T> m_data;
};

template <class T>
CircularQueue<T>::CircularQueue() {
}

template <class T>
int CircularQueue<T>::queueSize() {
    return m_iSize;
}

template <class T>
void CircularQueue<T>::enQueue(T t) {

    // addQueueSize();
    setBackToZero();

    m_data[m_iBack] = t;
    m_iBack++;
    m_iSize++;
}

template <class T>
T CircularQueue<T>::deQueue() {
    T t = nullptr;
    if (m_iSize != 0) {
        setFrontToZero();
        t = m_data[m_iFront];
        m_data[m_iFront] = nullptr;
        m_iFront++;
        m_iSize--;
    }
    return t;
}

// template <class T>
// void CircularQueue<T>::addQueueSize() {
//     if (m_iSize >= m_data.size()) {
//         m_iBack = m_iSize;
//         int newSize = m_data.size() * 2;
//         std::array<T, newSize> newData = {};

//         for (int i = 0; i < m_data.size(); i++) {
//             newData[i] = deQueue();
//         }
//         m_data = newData;

//         m_iSize = m_iBack;
//         m_iFront = 0;
//     }
// }

template <class T>
void CircularQueue<T>::setBackToZero() {
    if (m_iBack == m_data.size() && m_iSize < m_data.size()) {
        m_iBack = 0;
    }
}

template <class T>
void CircularQueue<T>::setFrontToZero() {
    if (m_iFront == m_data.size() && m_iSize != 0) {
        m_iFront = 0;
    }
}

#endif /* _CIRCULAR_QUEUE_H_ */
