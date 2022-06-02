#include <iostream>
#include <iterator>
#include <algorithm>

template<typename T>
class DoubleLinkedList {
public:
    class DoubleListIterator;
    class DoubleListReverseIterator;
private:
    typedef DoubleListIterator iterator;
    typedef DoubleListReverseIterator reverse_iterator;
    typedef size_t size_type;
    typedef T value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    class DoubleListNode;
    size_type count;
    DoubleListNode* head;
    DoubleListNode* tail;
    void copy(const DoubleLinkedList&);//correct

public:
    DoubleLinkedList();
    DoubleLinkedList(const DoubleLinkedList&);
    ~DoubleLinkedList();

    reference front() {
        iterator p(head);
        return *p;
    }//correct
    const_reference front() const {
        iterator p(head);
        return *p;
    }//correct
    reference back() {
        iterator p(tail);
        return *p;
    }//correct
    const_reference back() const {
        iterator p(tail);
        return *p;
    }//correct

    iterator begin() {
        iterator it_b(head);
        return it_b;
    }//correct
    iterator end() {
        iterator it_e(tail);
        ++it_e;
        return it_e;
    }//correct
    reverse_iterator rbegin() {
        reverse_iterator it_rb(tail);
        return it_rb;
    }//correct
    reverse_iterator rend() {
        reverse_iterator it_re(head);
        ++it_re;
        return it_re;
    }//correct

    iterator insert(iterator it, size_type n, T v) {
        if (it == nullptr) it = end();
        resize(count + n);
        iterator p = it;
        iterator l = it + n;
        for (size_type i = 0; i < n; i++) {
            *l = *p;
            *p = v;
            ++p;
            ++l;
        }
        return p;
    }//correct

    iterator erase(iterator first, iterator last) {
        iterator f = first;
        iterator l = ++last;
        iterator p = first;
        int n = 0;
        while (p != last) {
            if (n > count) {
                return first;
            }
            ++p;
            ++n;
        }
        p = first;
        if (--p == nullptr) {
            for (size_type i = 0; i < n; i++) {
                pop_front();
            }
        }
        else if (l == nullptr) {
            for (size_type i = 0; i < n; i++) {
                pop_back();
            }
        }
        else {
            while (f != last) {
                if (l == nullptr) {
                    resize(count - n);
                    return ++first;
                }
                else {
                    *f = *l;
                    ++f;
                    ++l;
                }
            }
            resize(count - n);
        }
        return ++first;
    }//correct

    void pop_back();//correct
    void push_back(const T&);//correct
    void pop_front();//correct
    void push_front(const T&);//correct

    void resize(size_type);//correct
    void swap(DoubleLinkedList&);//correct
    void assign(size_type, T);//correct
    bool empty() const;//correct
    size_type size() const;//correct
    void clear();//correct

    void reverse();//correct

    void print();//correct
    void print(iterator);//correct

    DoubleLinkedList& operator =(const DoubleLinkedList& other) {//correct
        if (this != &other) copy(other);
        return *this;
    }
};

template<typename T>
class DoubleLinkedList<T>::DoubleListNode {
    template<typename T>
    friend class DoubleLinkedList;

    template<typename T>
    friend class DoubleListIterator;

    template<typename T>
    friend class DoubleListReverseIterator;

    T value;
    DoubleListNode* next;
    DoubleListNode* prev;
public:
    DoubleListNode();
    DoubleListNode(const T&);
};

template<typename T>
class DoubleLinkedList<T>::DoubleListIterator {
    template<typename T>
    friend struct std::iterator_traits;
    friend class DoubleLinkedList;
public:
    typedef std::ptrdiff_t difference_type;
    typedef typename DoubleLinkedList<T>::value_type value_type;
    typedef typename DoubleLinkedList<T>::value_type* pointer;
    typedef typename DoubleLinkedList<T>::value_type& reference;
    typedef std::forward_iterator_tag iterator_category;
private:
    typename DoubleLinkedList<T>::DoubleListNode* node;

public:
    DoubleListIterator() :node(nullptr) {}

    DoubleListIterator(typename DoubleLinkedList<T>::DoubleListNode* n) :node(n) {}

    bool operator==(const DoubleListIterator& other) const {
        return this->node == other.node;
    }

    bool operator!=(const DoubleListIterator& other) const {
        return this->node != other.node;
    }

    /*bool operator>(const DoubleListIterator& other) const {
        return this->node > other.node;
    }*/

    bool operator>(const DoubleListIterator& other) const {
        return this - other > 0;
    }

    /*bool operator<(const DoubleListIterator& other) const {
        return this->node < other.node;
    }*/

    bool operator<(const DoubleListIterator& other) const {
        return this - other < 0;
    }

    /*bool operator>=(const DoubleListIterator& other) const {
        return this->node >= other.node;
    }*/

    bool operator>=(const DoubleListIterator& other) const {
        return this - other >= 0;
    }

    /*bool operator<=(const DoubleListIterator& other) const {
        return this->node <= other.node;
    }*/

    bool operator<=(const DoubleListIterator& other) const {
        return this - other <= 0;
    }

    typename DoubleLinkedList<T>::reference operator*() {
        return node->value;
    }

    typename DoubleLinkedList<T>::const_reference operator*() const {
        return node->value;
    }

    DoubleListIterator operator++() {
        if (node) node = node->next;
        return *this;
    }

    DoubleListIterator operator --() {
        if (node) node = node->prev;
        return *this;
    }

    DoubleListIterator operator+(int n) {
        for (int i = 0; i < n; i++) {
            if (node) node = node->next;
            else break;
        }
        return *this;
    }

    DoubleListIterator operator-(int n) {
        for (int i = 0; i < n; i++) {
            if (node) node = node->prev;
            else break;
        }
        return *this;
    }

    DoubleListIterator operator+=(int n) {
        if (n > 0) {
            for (int i = 0; i < n; i++) {
                if (node) node = node->next;
                else break;
            }
        }
        else if (n < 0) {
            for (int i = 0; i < n; i++) {
                if (node) node = node->prev;
                else break;
            }
        }
        return *this;
    }

    DoubleListIterator operator-=(int n) {
        if (n < 0) {
            for (int i = 0; i < n; i++) {
                if (node) node = node->next;
                else break;
            }
        }
        else if (n > 0) {
            for (int i = 0; i < n; i++) {
                if (node) node = node->prev;
                else break;
            }
        }
        return *this;
    }

    difference_type operator-(const DoubleListIterator& other) const {
        DoubleListIterator p = *this;
        difference_type n1 = 0, n2 = 0;
        while (p.node != nullptr) {
            --p;
            ++n1;
        }
        p = other;
        while (p.node != nullptr) {
            --p;
            ++n2;
        }
        return n2 - n1;
    }

    value_type operator[](int n) {
        DoubleListIterator it = this;
        it += n;
        return *it;
    }

    void operator()(T* v){
        node->value = v;
    }

    DoubleListIterator operator=(const DoubleListIterator& other) {
        this->node = other.node;
        return *this;
    }

    DoubleListIterator operator--(int n) {
        DoubleListIterator it = this;
        --this;
        return it;
    }

    DoubleListIterator operator++(int n) {
        DoubleListIterator it = this;
        ++this;
        return it;
    }
    
    friend DoubleListIterator operator+(int n, DoubleListIterator& it) {
        it = it + n;
        return it;
    }
};

template<typename T>
class DoubleLinkedList<T>::DoubleListReverseIterator {
    template<typename T>
    friend struct std::iterator_traits;

    typedef std::ptrdiff_t difference_type;
    typedef typename DoubleLinkedList<T>::value_type value_type;
    typedef typename DoubleLinkedList<T>::value_type* pointer;
    typedef typename DoubleLinkedList<T>::value_type& reference;
    typedef std::forward_iterator_tag iterator_category;

    typename DoubleLinkedList<T>::DoubleListNode* node;

public:
    DoubleListReverseIterator() :node(nullptr) {}

    DoubleListReverseIterator(typename DoubleLinkedList<T>::DoubleListNode* n) :node(n) {}

    bool operator==(const DoubleListReverseIterator& other) const {
        return this->node == other.node;
    }

    bool operator!=(const DoubleListReverseIterator& other) const {
        return this->node != other.node;
    }

    bool operator>(const DoubleListReverseIterator& other) const {
        return this->node > other.node;
    }

    bool operator<(const DoubleListReverseIterator& other) const {
        return this->node < other.node;
    }

    bool operator>=(const DoubleListReverseIterator& other) const {
        return this->node >= other.node;
    }

    bool operator<=(const DoubleListReverseIterator& other) const {
        return this->node <= other.node;
    }

    typename DoubleLinkedList<T>::reference operator*() {
        return node->value;
    }

    typename DoubleLinkedList<T>::const_reference operator*() const {
        return node->value;
    }

    DoubleListReverseIterator operator++() {
        if (node) node = node->prev;
        return *this;
    }

    DoubleListReverseIterator operator --() {
        if (node) node = node->next;
        return *this;
    }

    DoubleListReverseIterator operator+(int n) {
        for (int i = 0; i < n; i++) {
            if (node) node = node->prev;
            else break;
        }
        return *this;
    }

    DoubleListReverseIterator operator-(int n) {
        for (int i = 0; i < n; i++) {
            if (node) node = node->next;
            else break;
        }
        return *this;
    }

    DoubleListReverseIterator operator+=(int n) {
        if (n > 0) {
            for (int i = 0; i < n; i++) {
                if (node) node = node->prev;
                else break;
            }
        }
        else if (n < 0) {
            for (int i = 0; i < n; i++) {
                if (node) node = node->next;
                else break;
            }
        }
        return *this;
    }

    DoubleListReverseIterator operator-=(int n) {
        if (n < 0) {
            for (int i = 0; i < n; i++) {
                if (node) node = node->prev;
                else break;
            }
        }
        else if (n > 0) {
            for (int i = 0; i < n; i++) {
                if (node) node = node->next;
                else break;
            }
        }
        return *this;
    }
};

template<typename T>
DoubleLinkedList<T>::DoubleListNode::DoubleListNode() : value(), next(0), prev(0) {}

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList() : count(0), head(0), tail(0) {}

template<typename T>
DoubleLinkedList<T>::DoubleListNode::DoubleListNode(const T& val) : value(val), next(0), prev(0) {}

template<typename T>
DoubleLinkedList<T>::~DoubleLinkedList() {}

template<typename T>
void DoubleLinkedList<T>::copy(const DoubleLinkedList& other) {
    if (other.count) {
        DoubleListNode* cur1 = new DoubleListNode(other.front());
        DoubleListNode* cur2 = other.head->next;
        DoubleListNode* cur3 = nullptr;
        head = cur1;
        for (count = 1; count < other.count; ++count) {
            cur1->prev = cur3;
            cur1->next = new DoubleListNode(cur2->value);
            cur2->prev = cur1;
            cur3 = cur1;
            cur1 = cur1->next;
            cur2 = cur2->next;
        }
        tail = cur1;
    }
}

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList& other) :count(0), head(0), tail(0) {
    copy(other);
}

template<typename T>
bool DoubleLinkedList<T>::empty() const {
    return count == 0;
}

template<typename T>
typename DoubleLinkedList<T>::size_type DoubleLinkedList<T>::size() const {
    return count;
}

template<typename T>
void DoubleLinkedList<T>::clear() {
    while (count) pop_front();
    head = 0;
    tail = 0;
}

template<typename T>
void DoubleLinkedList<T>::pop_front() {
    if (count == 1) {
        delete head;
    }
    else {
        DoubleListNode* cur = head->next;
        delete head;
        cur->prev = new DoubleListNode;
        head = cur;
    }
    --count;
}

template<typename T>
void DoubleLinkedList<T>::pop_back() {
    if (count == 1) {
        delete tail;
    }
    else {
        DoubleListNode* cur = tail->prev;
        delete tail;
        cur->next = new DoubleListNode;
        tail = cur;
    }
    --count;
}

template<typename T>
void DoubleLinkedList<T>::swap(DoubleLinkedList<T>& other) {
    DoubleListNode* n = head;
    head = other.head;
    other.head = n;
    n = tail;
    tail = other.tail;
    other.tail = n;
    size_type c = count;
    count = other.count;
    other.count = c;
}

template<typename T>
void DoubleLinkedList<T>::resize(size_type size) {
    DoubleListNode* cur1;
    if (count == 0 && size > 0) {
        head = new DoubleListNode;
        count = 1;
        cur1 = head;
        for (size_type i = count; i < size; ++i) {
            cur1->next = new DoubleListNode;
            cur1->prev = cur1;
            cur1 = cur1->next;
        }
        tail = cur1;
    }
    else {
        if (size <= count) {
            if (size == 0) {
                clear();
                return;
            }
            cur1 = head;
            for (size_type i = 0; i < size - 1; ++i)
                cur1 = cur1->next;
            tail = cur1;
            cur1 = cur1->next;
            tail->next = nullptr;
            DoubleListNode* cur2;
            for (size_type i = size; i < count; ++i) {
                cur2 = cur1->next;
                delete cur1;
                cur1 = cur2;
            }
        }
        else {
            cur1 = tail;
            for (size_type i = count; i < size; ++i) {
                cur1->next = new DoubleListNode;
                cur1->prev = cur1;
                cur1 = cur1->next;
            }
            tail = cur1;
        }
    }
    count = size;
}

template<typename T>
void DoubleLinkedList<T>::push_back(const T& v) {
    DoubleListNode* cur = new DoubleListNode(v);
    cur->next = new DoubleListNode;
    if (tail != nullptr) {
        cur->prev = tail;
        cur->prev->next = cur;
        tail = tail->next;
        tail = cur;
    }
    else {
        cur->prev = new DoubleListNode;
        head = tail = cur;
    }
    ++count;
}

template<typename T>
void DoubleLinkedList<T>::push_front(const T& v) {
    DoubleListNode* cur = new DoubleListNode(v);
    cur->prev = new DoubleListNode;
    if (head != nullptr) {
        cur->next = head;
        cur->next->prev = cur;
        head = head->prev;
        head = cur;
    }
    else {
        cur->next = new DoubleListNode;
        head = tail = cur;
    }
    ++count;
}

template<typename T>
void DoubleLinkedList<T>::assign(size_type num, T v) {
    clear();
    for (size_type i = 0; i < num; i++) {
        push_front(v);
    }
}

template<typename T>
void DoubleLinkedList<T>::reverse() {
    DoubleListNode* cur1 = head,* cur2 = tail;
    value_type p;
    for (size_type i = 0; i < size() / 2; i++) {
        p = cur1->value;
        cur1->value = cur2->value;
        cur2->value = p;
        cur1 = cur1->next;
        cur2 = cur2->prev;
    }
}

template<typename T>
void DoubleLinkedList<T>:: print() {
    DoubleListNode* cur = head;
    for (size_type i = 0; i < count; ++i) {
        std::cout << cur->value << " ";
        cur = cur->next;
    }
    std::cout << std::endl;
}

template<typename T>
void DoubleLinkedList<T>::print(iterator p) {
    while (p != end()) {
        std::cout << *p << " ";
        ++p;
    }
    std::cout << std::endl;
}

int main() {
    int node;
    DoubleLinkedList<int>::DoubleListIterator p;
    DoubleLinkedList<int> list;
    DoubleLinkedList<int> list_0;
    for (int i = 0; i < 10; i++) {
        std::cin >> node;
        list.push_front(node);
    }

    list.print();

    std::sort(list.begin(), list.end());
    list.print();
    //list.print(list.begin());
    /*list.pop_back();
    list.pop_front();
    list.print();

    list.reverse();
    list.print();

    std::cout << list.front() << " " << list.back() << std::endl;

    list_0 = list;

    std::cout << list_0.size() << std::endl;

    list_0.clear();

    list_0.print();

    std::cout << list_0.empty() << std::endl;

    list_0.push_back(222);
    list_0.print();

    list.resize(5);
    std::cout << list.size() << std::endl;
    list.print();

    list.resize(10);
    std::cout << list.size() << std::endl;
    list.print();

    list.swap(list_0);
    list.print();
    list_0.print();

    list.assign(3, 2);
    list.print();

    p = list.begin();
    p += 1;
    p = list.insert(p, 2, 5);
    list.print();

    DoubleLinkedList<int>::DoubleListIterator k = list.begin();
    p = list.erase(k, p);
    list.print();*/

    return 0;
}