#ifndef EXPERIMENT_CHARSTRINGLINK_H
#define EXPERIMENT_CHARSTRINGLINK_H

#include "CharString.h"

class CharStringLink {
private:
    struct StringNode{
        CharString* data;
        StringNode* next;
        StringNode* prev;
        ~StringNode(){ delete data; }
    };
    StringNode* head;
    StringNode* tail;
    int length;
    StringNode* current;
public:
    CharStringLink() { head = nullptr; tail = nullptr; length = 0; }
    ~CharStringLink();

	CharString* front() { if(head != nullptr) return head->data; else return nullptr; }
	CharString* back() { if(tail != nullptr) return tail->data; else return nullptr; };
	void clear();
    int size(){ return length; }

    void add(CharString&);
    CharString remove(CharString*);
	void remove();
    int search(CharString*);
	CharString* nextNode(bool direction) { if(direction) {CharString* temp = current->data; current = current->next; return temp;} else{CharString* temp = current->data; current = current->prev; return temp;} }
    friend std::wostream& operator<<(std::wostream&, CharStringLink&);
};


#endif //EXPERIMENT_CHARSTRINGLINK_H
