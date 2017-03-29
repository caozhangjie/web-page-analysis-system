#ifndef EXPERIMENT_HASHTABLE_H
#define EXPERIMENT_HASHTABLE_H

#include <iostream>
#include <fstream>
#include "CharString.h"
#include "CharStringLink.h"

class WordTable;

template <typename ElemType>
class HashTable{
private:
    struct WordStruct{
        ElemType *word_data;
        WordStruct* next;
		~WordStruct(){ delete word_data; }
    };
    WordStruct** data;
    bool* occupation;
	int occupation_num;
    unsigned int capacity;
    int length;
    friend class WordTable;
public:
	HashTable();
    HashTable(unsigned int len);
    ~HashTable() { delete [] data; capacity = 0; length = 0; }

    //void expand();
    void add(ElemType*, unsigned int);
    bool search(ElemType data, unsigned int place);
};


template <typename ElemType>
HashTable<ElemType>::HashTable() {
    data = new WordStruct*[1000];
    occupation = new bool[1000];
    for(int i = 0; i < 1000; i++){
        occupation[i] = false;
        data[i] = nullptr;
    }
    capacity = 1000;
}


template <typename ElemType>
HashTable<ElemType>::HashTable(unsigned int len) {
    data = new WordStruct*[len];
    occupation = new bool[len];
    for(unsigned int i = 0; i < len; i++){
        occupation[i] = false;
        data[i] = nullptr;
    }
    capacity = len;
	occupation_num = 0;
    length = 0;
}

/*
template <typename ElemType>
void HashTable<ElemType>::expand(){
    capacity *= 2;
    WordStruct** temp = data;
    data = new WordStruct*[capacity];
    for(int i = 0; i < length; i++){
        data[i] = temp[i];
    }
    delete [] temp;
}*/

template <typename ElemType>
void HashTable<ElemType>::add(ElemType* a, unsigned int hash){
    WordStruct* temp;

    if(hash >= capacity){
        hash = hash % capacity;
    }  

    if(occupation[hash]){
		temp = data[hash];
        while(temp->next != nullptr){
            temp = temp->next;
        }
        temp->next = new WordStruct;
        temp->next->word_data = a;
        temp->next->next = nullptr;	
    }
    else{
        data[hash] = new WordStruct;
        data[hash]->word_data = a;
        data[hash]->next = nullptr;
        occupation[hash] = true;
		occupation_num += 1;
    }
    length += 1;
}

template <typename ElemType>
bool HashTable<ElemType>::search(ElemType d, unsigned int place){
	if (place >= capacity){
		place %= capacity;
	}
	if(occupation[place]){
		WordStruct* temp;
		temp = data[place];
		while(temp != nullptr){
			if(d == *(temp->word_data)){
				return true;
			}
			temp = temp->next;
		}
		return false;
	}
	else{
		return false;
	}
}

class WordTable{
private:
	HashTable<CharString> word;
    void constructCharacterTable();
    bool word_construct;
    const int capacity;
    int max_length;
public:
    WordTable():capacity(40000000), word(40000000) { word_construct = false; max_length = 10; }
    ~WordTable() { }
	int size() { return word.occupation_num; }
	static unsigned int hashFunction(const myChar * data, int len);
	static unsigned int hashFunction(CharString&);
	bool search(CharString& data) { int hash = data.tableHash(); return word.search(data, hash); }
    void initDictionary(CharString&);
    void divideWords(CharString& data, CharStringLink& result);
};


#endif //EXPERIMENT_HASHTABLE_H
