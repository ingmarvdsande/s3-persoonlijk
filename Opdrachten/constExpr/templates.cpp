#include <iostream>
#include <string>

template <typename T>
class Pair {
public:
    T data1;
    T data2;

    Pair (T data1, T data2) : data1(data1), data2(data2) {}

    void setFirst(T data) {
        data1 = data;
    }

    void setSecond(T data) {
        data2 = data;
    }

    T getFirst() {
        return data1;
    }

    T getSecond() {
        return data2;
    }

    void print() {
        std::cout << "Data1: " << data1 << ", Data2: " << data2 << std::endl;
    }
};

template <typename T>
void swapValues(Pair<T>& pair) {
    T temp = pair.data1;
    pair.data1 = pair.data2;
    pair.data2 = temp;
}

int main() {
    Pair<int> pair1(1, 2);
    pair1.print();
    swapValues(pair1);
    pair1.print();
    return 0;
}