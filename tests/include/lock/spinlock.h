#ifndef _SPINLOCK_H_
#define _SPINLOCK_H_

#include <atomic>

class SpinLock {
public:
    SpinLock() : flag_(false) {}

    void lock() {
        bool expect = false;
        while (!flag_.compare_exchange_weak(expect, true)) {
            // reset expect, because if failed, the expect is undefined
            expect = false;
        }
    }

    void unlock() {
        flag_.store(false);
    }

private:
    std::atomic<bool> flag_;
};

#endif /* _SPINLOCK_H_ */
