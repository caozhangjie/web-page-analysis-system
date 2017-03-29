#ifndef EXPERIMENT_CHARSTRING_H
#define EXPERIMENT_CHARSTRING_H

#include <iostream>
#include <string>
#include "Vector.h"

class CharString {
private:
    myChar * data;
    int length;
    int capacity;
    const int ex_len;
public:
    CharString():ex_len(1000){ capacity = ex_len; length = 0; data = new myChar [ex_len]; data[0] = '\0'; }
    CharString(int length);
    CharString(CharString&);
    CharString(const myChar *);
    ~CharString(){ capacity = 0; length = 0; delete [] data; }
    void operator=(CharString& s);
    void operator=(const myChar * s);
    myChar* c_str(){ return data; }

    void resetString(CharString&);
    void resetString(const myChar *);
    void append(const myChar *);
    void expand();

    int indexOf(myChar t, int pos);
    int indexOf(const myChar *, int pos, int len);
    int indexOf(CharString& p, int pos);
    int indexOf(const myChar * p, int pos);
    int* compute_prefix(CharString&);
    int* compute_prefix(const myChar *, int);

	void strip();
	void stripChinese();
	void clear() { length = 0; }
    CharString* substring(int index1, int index2);
    CharString* concat(CharString& back);
    CharString* operator+(CharString& s) { return this->concat(s); }

    bool empty(){return length == 0;}
    int size() { return length; }

    bool operator==(CharString& s);
    bool operator==(const myChar* s);
    myChar operator[](int index);
    friend std::wostream& operator<<(std::wostream&, CharString*);

    int htmlHash();
    unsigned int tableHash();
    void utf8ToWchar(const char * s);
	void spaceToSpace(const wchar_t * s);
};

#endif //EXPERIMENT_CHARSTRING_H
