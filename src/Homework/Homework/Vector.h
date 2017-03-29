#ifndef EXPERIMENT_VECTOR_H
#define EXPERIMENT_VECTOR_H

#include <iostream>
typedef wchar_t myChar;

template <typename ElemType>
class Vector{
private:
    ElemType* data;
    int length;
    int capacity;
public:
    Vector(){ data = new ElemType[16]; capacity = 16; length = 0; }
	Vector(Vector& v1);
    ~Vector(){ delete [] data; }
    void operator=(Vector& s);

    bool empty() { return length == 0; }
    int size() { return length; }

    void push(ElemType a);
    void pop(){ length -= 1; }

    void expand();
    void clear(){ length = 0; }

    ElemType back();
    ElemType front();
    ElemType operator[](int index);
};

template <typename ElemType>
Vector<ElemType>::Vector(Vector& s) {
    capacity = s.length + 1000;
    data = new ElemType[capacity];
    for (int i = 0; i < s.length; ++i) {
        data[i] = s.data[i];
    }
    length = s.length;
}

template <typename ElemType>
void Vector<ElemType>::operator=(Vector& s) {
    if(capacity < s.length){
        delete [] data;
        capacity = s.length + 1000;
        data = new ElemType[capacity];
    }
    for (int i = 0; i < s.length; ++i) {
        data[i] = s.data[i];
    }
    length = s.length;
}

template <typename ElemType>
void Vector<ElemType>::push(ElemType a) {
    while(length >= capacity){
        expand();
    }
    data[length] = a;
    length+=1;
}

template <typename ElemType>
void Vector<ElemType>::expand(){
    ElemType* temp;

    temp = data;
    capacity *= 2;
    data = new ElemType[capacity];
    for(int i = 0; i < length; i++){
        data[i] = temp[i];
    }
}

template <typename ElemType>
ElemType Vector<ElemType>::back(){
    if(length == 0){
        ElemType temp = ElemType();
        std::cout << "Warning: empty vector" << std::endl;
        return temp;
    }
    else{
        return data[length-1];
    }
}

template <typename ElemType>
ElemType Vector<ElemType>::front(){
    if(length == 0){
        ElemType temp = ElemType();
        std::cout << "Warning: empty vector" << std::endl;
        return temp;
    }
    else{
        return data[0];
    }
}

template <typename ElemType>
ElemType Vector<ElemType>::operator[](int index){

    if(index < length && index >= 0) {
        return data[index];
    }
    else{
		ElemType temp = ElemType();
        std::cout << "Warning: vector index out of range" << std::endl;
        return temp;
    }
}

#endif //EXPERIMENT_VECTOR_H
