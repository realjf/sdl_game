#ifndef _SHAREDLOCK_H_
#define _SHAREDLOCK_H_

#include <mutex>
#include <shared_mutex>
#include <thread>

class SharedLock {
public:
    SharedLock() = default;
    ~SharedLock() = default;

    void setThreadID() {
        id = std::this_thread::get_id();
    }

    auto getThreadID() -> decltype(auto) {
        return id;
    }

    bool isOwner() {
        if (id == std::this_thread::get_id()) {
            return true;
        }
        return false;
    }

    mutable std::shared_timed_mutex mutex_;

private:
    decltype(std::this_thread::get_id()) id;
};

#endif /* _SHAREDLOCK_H_ */
