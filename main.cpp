#include <iostream>
#include <stdexcept>
#include <algorithm>

template<typename T>
class Vector {
private:
    T *data;
    int size;
    int capacity;

    void reallocate(int new_capacity);

public:
    Vector();

    ~Vector();

    void push_back(const T &value);

    void pop_back();

    int getSize() const;

    int getCapacity() const;

    void resize(int new_size);

    T &operator[](int index);

    T &at(int index);

    void clear();

    bool empty() const;
};


template<typename T>
Vector<T>::Vector() : data(nullptr), size(0), capacity(0) {}

template<typename T>
Vector<T>::~Vector() {
    delete[] data;
}

template<typename T>
void Vector<T>::reallocate(int new_capacity) {
    T *new_data = new T[new_capacity];
    if (data) {
        std::copy(data, data + size, new_data);
        delete[] data;
    }
    data = new_data;
    capacity = new_capacity;
}


template<typename T>
void Vector<T>::push_back(const T &value) {
    if (size == capacity) {
        reallocate(capacity == 0 ? 1 : capacity * 2);
    }
    data[size++] = value;
}


template<typename T>
void Vector<T>::pop_back() {
    if (size > 0) {
        --size;
        data[size].~T();
    }
}


template<typename T>
int Vector<T>::getSize() const {
    return size;
}


template<typename T>
int Vector<T>::getCapacity() const {
    return capacity;
}


template<typename T>
void Vector<T>::resize(int new_size) {
    if (new_size > capacity) {
        reallocate(new_size);
    }
    size = new_size;
}


template<typename T>
T &Vector<T>::operator[](int index) {
    return data[index];
}

template<typename T>
T &Vector<T>::at(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    return data[index];
}

template<typename T>
void Vector<T>::clear() {
    while (size > 0) {
        pop_back();
    }
}

template<typename T>
bool Vector<T>::empty() const {
    return size == 0;
}

int main() {
    Vector<int> vec;

    vec.push_back(11);
    vec.push_back(222);
    vec.push_back(3333);

    std::cout << "Elements in the vector: ";
    for (int i = 0; i < vec.getSize(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    vec.pop_back();
    std::cout << "Elements after pop_back: ";
    for (int i = 0; i < vec.getSize(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    vec.resize(5);
    std::cout << "Elements after resize to 5: ";
    for (int i = 0; i < vec.getSize(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    vec.clear();
    std::cout << "Is vector empty ?" << std::boolalpha << vec.empty() << std::endl;

    return 0;
}
