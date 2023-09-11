#pragma once

template<typename T, size_t size>
class Allocator {
public:
    using value_type = T;

    Allocator() {
        data = reinterpret_cast<T*>(std::malloc(size * sizeof(T)));
        if (data == nullptr)
            throw std::bad_alloc();
        memory_map.fill(false);
    }

    ~Allocator() {
        std::free(data);
    }

    template<class U>
    struct rebind {
        using other = Allocator<U, size>;
    };

    T* allocate(size_t n) {
        if (size - allocated_size < n)
            throw std::bad_alloc();

        std::size_t from = 0, to = 0;
        for (std::size_t i = 0; i < size; ++i)
        {
            if (memory_map[i])
                continue;
            std::size_t j = i + 1;
            for (; j < size && !memory_map[j] && j - i + 1 <= n; ++j) {}
            if (j - i == n)
            {
                from = i;
                to = j;
                break;
            }
        }
        if (from == 0 && to == 0)
            throw std::bad_alloc();

        for (std::size_t i = from; i < to; ++i)
            memory_map[i] = true;
        allocated_size += n;
        return data + from;
    }

    void deallocate(T* p, std::size_t n) {
        std::size_t from = p - data;
        for (size_t i {0}; i < n; ++i, ++p) {
            memory_map[from + i] = false;
        }
        allocated_size -= n;
    }

    template<class U, typename... Args>
    void construct(U* p, Args&&... args) {
        new (p) U(std::forward<Args>(args)...);
    }

    void destroy(T* p) {
        p->~T();
    }

private:
    size_t allocated_size {0};
    T* data {nullptr};
    std::array<bool, size> memory_map;

};
