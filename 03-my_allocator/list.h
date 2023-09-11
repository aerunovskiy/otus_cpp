#pragma once

template<class T, class Allocator = std::allocator<T>>
class List {
    struct Node {
        explicit Node(T data) : data(data), next(nullptr) {}

        T data;
        Node* next;
    };
public:
    List() = default;

    ~List() {
        while (_first != nullptr) {
            typename Allocator::template rebind<Node>::other nodeAllocator;
            Node* p = _first;
            _first = _first->next;
            nodeAllocator.destroy(p);
            nodeAllocator.deallocate(p, 1);
        }
    }

    void push_back(const T& value) {
        typename Allocator::template rebind<Node>::other nodeAllocator;
        Node* new_node = nodeAllocator.allocate(1);

        if (!empty()) {
            nodeAllocator.construct(new_node, std::move(value));
            _last->next = new_node;
            _last = _last->next;
        } else {
            nodeAllocator.construct(new_node, std::move(value));
            _first = new_node;
            _last = _first;
        }

        ++_size;
    }

    [[nodiscard]] bool empty() const {
        return _first == nullptr;
    }

    void print() const {
        if (empty()) return;

        Node* p = _first;

        while (p) {
            std::cout << p->data << ' ';
            p = p->next;
        }

        std::cout << std::endl;
    }

    [[nodiscard]] size_t size() const {
        return _size;
    }

    Node* operator[] (const size_t index) {
        if (empty()) return nullptr;

        Node* node = _first;

        for (size_t i {0}; i < index; ++i) {
            node = node->next;
            if (!node) return nullptr;
        }

        return node;
    }

private:
    Node* _first {nullptr};
    Node* _last {nullptr};
    size_t _size {0};
};
