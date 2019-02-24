#pragma once

// ---------------------------------------------------------------------------------------------------------------------

template <class T, class Lock>
std::optional<T> LockedQueue<T, Lock>::Pop()
{
    std::optional<T> item;

    if constexpr (std::is_same_v<Lock, UseMutex>)
    {
        std::unique_lock lock(_lock.mutex);

        _lock.conditionVar.wait(lock, [&] { return (!_queue.empty()) || (!_isActive.load()); });
        if (_isActive.load())
        {
            if constexpr (std::is_copy_assignable_v<T>)
            {
                item = _queue.front();
            }
            else if constexpr (std::is_move_assignable_v<T>)
            {
                item = std::move(_queue.front());
            }
            _queue.pop();
        }
    }
    else
    {
        while (_lock.spinlock.test_and_set(std::memory_order_acquire));
        if (_isActive.load() && !_queue.empty())
        {
            if constexpr (std::is_copy_assignable_v<T>)
            {
                item = _queue.front();
            }
            else if constexpr (std::is_move_assignable_v<T>)
            {
                item = std::move(_queue.front());
            }
            _queue.pop();
        }
        _lock.spinlock.clear();
    }

    return item;
}

// ---------------------------------------------------------------------------------------------------------------------

template <class T, class Lock>
template <class TempType, class TempLock>
typename std::enable_if<std::is_same_v<TempLock, UseMutex>, std::optional<TempType>>::type LockedQueue<T, Lock>::TryPop()
{
    std::optional<T> item;

    std::unique_lock lock(_lock.mutex);

    _lock.conditionVar.wait_for(lock, 100ms, [&] { return (!_queue.empty()) || (!_isActive.load()); });
    if (_isActive.load() && !_queue.empty())
    {
        if constexpr (std::is_copy_assignable_v<T>)
        {
            item = _queue.front();
        }
        else if constexpr (std::is_move_assignable_v<T>)
        {
            item = std::move(_queue.front());
        }
        _queue.pop();
    }

    return item;
}

// ---------------------------------------------------------------------------------------------------------------------

template <class T, class Lock>
void LockedQueue<T, Lock>::Push(const T& item)
{
    if constexpr (std::is_same_v<Lock, UseMutex>)
    {
        std::unique_lock lock(_lock.mutex);
        _queue.push(item);
        lock.unlock();
        _lock.conditionVar.notify_one();
    }
    else
    {
        while (_lock.spinlock.test_and_set(std::memory_order_acquire));
        _queue.push(item);
        _lock.spinlock.clear();
    }
}

// ---------------------------------------------------------------------------------------------------------------------

template <class T, class Lock>
void LockedQueue<T, Lock>::Push(T&& item)
{
    if constexpr (std::is_same_v<Lock, UseMutex>)
    {
        std::unique_lock lock(_lock.mutex);
        _queue.push(std::move(item));
        lock.unlock();
        _lock.conditionVar.notify_one();
    }
    else
    {
        while (_lock.spinlock.test_and_set(std::memory_order_acquire));
        _queue.push(std::move(item));
        _lock.spinlock.clear();
    }
}

// ---------------------------------------------------------------------------------------------------------------------

template <class T, class Lock>
void LockedQueue<T, Lock>::Activate()
{
    _isActive = true;

    if constexpr (std::is_same_v<Lock, UseMutex>)
    {
        _lock.conditionVar.notify_one();
    }
}

// ---------------------------------------------------------------------------------------------------------------------

template <class T, class Lock>
void LockedQueue<T, Lock>::Deactivate()
{
    _isActive = false;

    if constexpr (std::is_same_v<Lock, UseMutex>)
    {
        _lock.conditionVar.notify_one();
    }
}

// ---------------------------------------------------------------------------------------------------------------------
