#ifndef _SHARED_RECURSIVE_MUTEX_H_
#define _SHARED_RECURSIVE_MUTEX_H_

#include <mutex>
#include <shared_mutex>
#include <atomic>
#include <thread>
#include <chrono>

class SharedRecursiveMutex : public std::shared_timed_mutex {
public:
    /**
     * @brief Copying the mutex is not allowed
     *
     */
    // SharedRecursiveMutex(const SharedRecursiveMutex &) = delete;
    SharedRecursiveMutex &operator=(const SharedRecursiveMutex &) = delete;

    void lock(void) {
        if (unique) {
            return;
        }
        std::thread::id this_id = std::this_thread::get_id();
        if (owner == this_id) {
            ++count;
        } else {
            shared_timed_mutex::lock();
            owner = this_id;
            count = 1;
        }
    }

    bool try_unique_lock() {
        bool ok = shared_timed_mutex::try_lock_for(std::chrono::microseconds(3000));
        if (!ok) {
            return false;
        }
        count++;
        unique = true;
        return true;
    }

    void unlock(void) {
        unique = false;
        if (count > 1) {
            --count;
        } else {
            owner = std::thread::id();
            count = 0;
            shared_timed_mutex::unlock();
        }
    }

    bool try_lock(void) {
        if (unique) {
            return false;
        }
        std::thread::id this_id = std::this_thread::get_id();
        if (owner == this_id) {
            ++count;
            return true;
        } else {
            bool ok = shared_timed_mutex::try_lock_for(std::chrono::microseconds(3000));
            if (!ok) {
                return false;
            }
            owner = this_id;
            count = 1;
        }
        return true;
    }

private:
    std::atomic<std::thread::id> owner;
    int count;
    std::atomic<bool> unique;
};

#endif /* _SHARED_RECURSIVE_MUTEX_H_ */
