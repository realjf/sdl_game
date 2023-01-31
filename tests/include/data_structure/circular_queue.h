#ifndef _CIRCULAR_QUEUE_H_
#define _CIRCULAR_QUEUE_H_

#include <iostream>
#include <array>

template <typename T>
class CircularQueue {
public:
    CircularQueue<T>() {
    }
    ~CircularQueue<T>() {
    }

    // 获取队列中的元素数量
    int queueSize {
        return m_iSize;
    }

public:
    /// 元素入队
    void enQueue(T t) {

        addQueueSize();
        setBackToZero();

        data[m_iBack] = t;
        m_iBack++;
        m_iSize++;
    }

public:
    /// 元素出队
    T deQueue() {
        T t = default(T);
        if (m_iSize != 0) {
            setFrontToZero();
            t = data[m_iFont];
            data[m_iFont] = default(T);
            m_iFont++;
            m_iSize--;
        }
        return t;
    }

private:
    // 队列自增长
    void addQueueSize() {
        if (m_iSize >= data.Length) {
            m_iBack = m_iSize;
            T[] newData = new T[data.Length * 2];

            for (int i = 0; i < data.Length; i++) {
                newData[i] = deQueue();
            }
            data = newData;

            m_iSize = m_iBack;
            m_iFont = 0;
        }
    }

private:
    /// 设置出队index
    void setBackToZero() {
        if (m_iBack == data.Length && m_iSize < data.Length) {
            m_iBack = 0;
        }
    }

private:
    /// 设置出队index
    void setFrontToZero() {
        if (m_iFont == data.Length && m_iSize != 0) {
            m_iFont = 0;
        }
    }

private:
    // 队列出队index
    int m_iFront;
    // 队列入队Index
    int m_iBack;
    // 队列中元素数量
    int m_iSize;
    // 队列的初始长度设置为3
    T[] m_data = new T[3];
};

#endif /* _CIRCULAR_QUEUE_H_ */
