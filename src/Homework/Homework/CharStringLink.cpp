#include "CharStringLink.h"

CharStringLink::~CharStringLink(){
    StringNode* temp;
    temp = head;
    while(temp != tail){
        head = temp->next;
        delete temp;
        temp = head;
    }
    delete tail;
    head = nullptr;
    tail = nullptr;
}

void CharStringLink::clear(){
    StringNode* temp;
    temp = head;
    while(temp != tail){
        head = temp->next;
        delete temp;
        temp = head;
    }
    delete tail;
    head = nullptr;
    tail = nullptr;
}

void CharStringLink::add(CharString& s){
    if(head == nullptr){
        head = new StringNode;
		head->data = new CharString;
		*(head->data) = s;
        head->next = head;
        head->prev = head;
        tail = head;
        current = head;
    }
    else{
        tail->next = new StringNode;
        tail->next->data = new CharString;
		*(tail->next->data) = s;
        tail->next->next = head;
        tail->next->prev = tail;
        head->prev = tail->next;
        tail = tail->next;
    }
    length += 1;
}

CharString CharStringLink::remove(CharString* s){
    StringNode* temp;

    temp = head;
    if(head == nullptr){
        std::cout << "Warning: empty string link" << std::endl;
		return CharString();
    }
    else {
        do{
            if(*(temp->data) == *(s)){
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                CharString& temp_string = *(temp->data);
                delete temp;
                return temp_string;
            }
            else{
                temp = temp->next;
            }
        }while(temp != head);
    }
}

void CharStringLink::remove(){
    StringNode* temp;

    temp = head;
    if(head == nullptr){
        std::cout << "Warning: empty string link" << std::endl;
		return;
    }
    else {
		if(temp->next == temp){
			delete temp;
			head = nullptr;
			tail = nullptr;
			return;
		}
		else{
			temp = tail;
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			tail = temp->prev;
			delete temp;
			return;	
		}
    }	
}

int CharStringLink::search(CharString* s){
    StringNode* temp;
    int start;

    start = 0;
    temp = head;
    if(head == nullptr){
        return -1;
    }
    else {
        do{
            if(*(temp->data) == *(s)){
                return start;
            }
            else{
                temp = temp->next;
                start+=1;
            }
        }while(temp != head);
        return -1;
    }
}

std::wostream& operator<<(std::wostream& os, CharStringLink& l){
    CharStringLink::StringNode* temp;
    temp = l.head;
    if(l.head != nullptr){
        do{
            os << temp->data << std::endl;
            temp = temp->next;
        }while(l.head != temp);
    }
	return os;
}