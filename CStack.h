#ifndef CSTACK_CSTACK_H
#define CSTACK_CSTACK_H

#include <iostream>
#include <cstring>
//#include "Factory.h"
#include "Functions.h"

struct Factory;

using namespace std;

struct CStack {
    int* container; // array of integers
    size_t capacity; // capacity of stack
    int top; // top element
    char* filename = nullptr; // name of file
//public:
    CStack();
    CStack(size_t);
    CStack(size_t, char*);
    CStack(size_t, char*, int*);
    CStack(const CStack&);
    CStack(CStack&&) noexcept;
    virtual ~CStack() { delete [] container; delete [] filename;};

    int push(int);
    int pop(int&);
    int peek(int&);
    size_t size();
    bool isEmpty();
    bool isFull();

    virtual int output() = 0; // pure virtual function

    static CStack *create_by_Factory(char *str, Factory **f);

    CStack& operator=(const CStack&);
    CStack& operator=(CStack&&);
    CStack& operator++();
    CStack& operator--();
//    CStack operator++(int); // return abstract
//    CStack operator--(int); // return abstract
//    CStack operator+(const CStack&); // return abstract
    friend ostream& operator<<(ostream&, const CStack&);
};


struct CData0 : public CStack {
//public:
    CData0(size_t length) : CStack(length) {}
    CData0(size_t length, char* file) : CStack(length, file) {}
    CData0(size_t length, char* file, int* container) : CStack(length, file, container) {

//        cout << "capacity = " << capacity;
//        cout << " and top = " << top << endl;
//        for (int i = 0; i <= top; ++i)
//            cout << container[i] << " ";
//        cout << "\n\n";
    }
    CData0(const CStack& other) : CStack(other) {}
    CData0(CStack&& other) : CStack(other) {}

    int output() override;
};

CData0 operator++(CStack& a, int);
CData0 operator--(CStack& a, int);
CData0 operator+(const CStack&, const CStack&);

struct CData1 : public CStack {
//public:
    CData1(size_t length) : CStack(length) {}
    CData1(size_t length, char* file) : CStack(length, file) {}
    CData1(size_t length, char* file, int* container) : CStack(length, file, container) {}
    CData1(const CStack& other) : CStack(other) {}
    CData1(CStack&& other) : CStack(other) {}

    int output() override;
};

//CData1 operator++(CStack& a, int);
//CData1 operator--(CStack& a, int);
//CData1 operator+(const CData1&);


#endif //CSTACK_CSTACK_H
