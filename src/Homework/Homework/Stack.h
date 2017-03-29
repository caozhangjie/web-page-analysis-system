#ifndef EXPERIMENT_STACK_H
#define EXPERIMENT_STACK_H

template <typename ElemType>
class Stack{
private:
    ElemType* data;
    int length;
    int capacity;
public:
    Stack(){ capacity = 1; length = 0; data = new ElemType[1]; }
    ~Stack(){ capacity = 0; length = 0; delete [] data; }

    bool empty(){return length == 0;}
    int size() { return length; }

    void pop();
    void push(ElemType);

    ElemType top();
};

template <typename ElemType>
void Stack<ElemType>::push(ElemType elem) {
    ElemType* new_data;
    if(length == capacity){
        new_data = new ElemType[capacity * 2];
        capacity *= 2;
		for(int i = 0; i < length; i++){
            new_data[i] = data[i];
        }
        delete [] data;
        data = new_data;
    }
    data[length] = elem;
    length += 1;
}

template <typename ElemType>
void Stack<ElemType>::pop() {
	if(length > 0){
		length -= 1;
	}
	else{
		std::cout << "Warning: length must be larger than 1 before pop" << std::endl;
	}
}

template <typename ElemType>
ElemType Stack<ElemType>::top() {
    if(length > 0){
        return data[length-1];
    }
    else{
        ElemType temp = ElemType();
        std::cout << "Warning: empty stack" << std::endl;
        return temp;
    }
}

#endif //EXPERIMENT_STACK_H
