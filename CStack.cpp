#include "CStack.h"
#include "Factory.h"
#include "fstream"


CStack::CStack()
    : container(nullptr)
    , capacity(0)
    , top(-1) {

//    cout << this << " - called default constructor " << endl;
}


CStack::CStack(size_t length)
    : container(new int[length])
    , capacity(length)
    , top(-1) {

//    cout << this << " - called constr w 1 par" << endl;
}


CStack::CStack(size_t length, char* file)
        : container(new int[length])
        , capacity(length)
        , top(-1) {

    filename = file;
    file = nullptr;
//    cout << this << " - called constr w 2 param" << endl;
}


CStack::CStack(size_t length, char* file, int* container)
        : capacity(length)
        , top(length - 1) {

    filename = file;
    file = nullptr;

    this->container = container;
    container = nullptr;
//    cout << this << " - called constr w 3 parameters" << endl;
}


CStack::CStack(const CStack& other)
    : container(new int[other.capacity])
    , capacity(other.capacity)
    , top(-1) {

//    cout << this << " - called copy constr" << endl;

    delete [] filename;
    filename = new char[256];
    strcpy(filename, other.filename);

    for (int i = 0; i < other.top + 1; ++i)
        push(other.container[i]);
}


CStack::CStack(CStack&& other) noexcept {

//    cout << this << " - called move constr " << endl;
    container = other.container;
    capacity = other.capacity;
    top = other.top;
    filename = other.filename;

    other.container = nullptr;
    other.capacity = 0;
    other.top = -1;
    other.filename = nullptr;
}


int CStack::push(int x) {

    if (isFull()) {
        cout << "Impossible to push value" << endl;
        return 1;
    }
    container[++top] = x;
    return 0;
}


int CStack::pop(int& result) {

    if (isEmpty()) {
        cout << "Cannot pop" << endl;
        return 0;
    }
    result = container[top--];
    return 1;
}


int CStack::peek(int& result) {

    if (isEmpty()) {
        cout << "Cannot peek" << endl;
        return 0;
    }
    result = container[top];
    return 1;
}


size_t CStack::size() {

    return top + 1;
}


bool CStack::isEmpty() {

    if (top == -1) {
        cout << "Stack is empty" << endl;
        return true;
    }
    return false;
}

 bool CStack::isFull() {

    if (size() == capacity) {
        cout << "Stack is full" << endl;
        return true;
    }
    return false;
}


CStack* CStack::create_by_Factory(char* str, Factory** f) {

    int CDataType, pos, x;

    pos = get_int(str, CDataType);
    if((CDataType != 0 && CDataType != 1) || pos < 1)
        throw -1; // incorrect type
    str += pos;
    char* filename = new char[256];
    pos = get_word(str, filename);
    if (pos < 1)
        throw -2;

    str += pos;
    int* container = nullptr;
    size_t lenOfContainer = 0;
    // while a number is being read
    while (pos = get_int(str, x), pos) { // if pos == 1 exit
        if (pos < 1) {
            delete [] filename;
            delete [] container;
            throw -2;
        }
        // create a copy of old container
        int* tmpContainer = new int[lenOfContainer];
        for (size_t i = 0; i < lenOfContainer; ++i)
            tmpContainer[i] = container[i];

        // delete old container and create new
        delete [] container;
        container = new int[lenOfContainer + 1];
        // copy elements except last element
        for (size_t i = 0; i < lenOfContainer; ++i)
            container[i] = tmpContainer[i];
        container[lenOfContainer++] = x;

        delete [] tmpContainer;
        str += pos;
    }

    if (CDataType == 0)
        return f[0]->create(lenOfContainer, filename, container);
    if (CDataType == 1)
        return f[1]->create(lenOfContainer, filename, container);

    return nullptr;
}


CStack& CStack::operator=(const CStack& other) {

//    cout << this << " - called copy oper=" << endl;

    delete [] filename;
    filename = new char[256];
    strcpy(filename, other.filename);

    delete [] container;

    container = new int[other.capacity];
    capacity = other.capacity;
    top = -1;
    for (size_t i = 0; i < capacity; ++i) {
        push(other.container[i]);
    }
    return (*this);
}


CStack& CStack::operator=(CStack&& other) {

//    cout << this << " - called copy oper=" << endl;

    if (this != &other) {

        delete [] filename;
        filename = other.filename;
        other.filename = nullptr;

        delete[] container;

        container = other.container;
        capacity = other.capacity;
        top = other.top;

        other.container = nullptr;
        other.capacity = 0;
        other.top = -1;
    }
    return (*this);
}


CStack& CStack::operator++() { // prefix increment

    push(0);
    return (*this);
}


CStack& CStack::operator--() { // prefix decrement

    int tmp;
    int& ref_tmp = tmp;
    pop(ref_tmp);
    return (*this);
}


ostream& operator<<(ostream& stream, const CStack& s) {

    CStack& tmp(s);

    stream << "[";
    for (int i = 0; i < s.top + 1; i++) {
        if (i != 0) {
            stream << ", ";
        }
        stream << s.container[i];
    }
    stream << "]";
    return stream;
}


int CData0::output() {

//    cout << this << " " << *this << " CData0::output" << endl;
    ofstream File(filename);
    for (size_t i = 0; i < capacity; ++i) {
        File << container[i] << " ";
    }
    File.close();
    return 0;
}


int CData1::output() {

//    cout << this << " " << *this << " CData1::output" << endl;
    ofstream File(filename);
    for (size_t i = 0; i < capacity; ++i) {
        File << container[i] << endl;
    }
    File.close();

    return 0;
}


CData0 operator++(CStack& a, int) {

    CData0 tmp(a);
    ++a;
    return tmp;
}


CData0 operator--(CStack& a, int) {

    CData0 tmp(a);
    --a;
    return tmp;
}


CData0 operator+(const CStack& a, const CStack& b) {

    CData0 result(a.capacity + b.capacity);

    for (size_t i = 0; i < a.capacity; ++i)
        result.container[++result.top] = a.container[i];

    for (size_t i = 0; i < b.capacity; ++i)
        result.container[++result.top] = b.container[i];

    if (a.filename != nullptr) {
        result.filename = new char[256];
        strcpy(result.filename, a.filename);
    }

    return result;
}
