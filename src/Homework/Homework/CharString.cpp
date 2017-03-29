#include "CharString.h"
#include "HashTable.h"
#include <Windows.h>


CharString::CharString(int cap):ex_len(1000) {
	capacity = cap + ex_len + 1;
    data = new myChar [capacity];
    length = 0;
    data[0] = L'\0';
}

CharString::CharString(CharString& s):ex_len(1000){
    capacity = ex_len;
    length = 0;
    data = new myChar [ex_len];
    data[0] = L'\0';
    resetString(s);
}

CharString::CharString(const myChar * s):ex_len(1000) {
    capacity = ex_len;
    length = 0;
    data = new myChar [ex_len];
    data[0] = L'\0';
    resetString(s);
}

void CharString::operator=(CharString& s){
    resetString(s);
}

void CharString::operator=(const myChar * s){
    resetString(s);
}

void CharString::resetString(CharString& s) {
    if(capacity < s.capacity){
        delete [] data;
        data = new myChar [s.capacity + ex_len];
		capacity = s.capacity + ex_len;
    }
    for(int i = 0; i < s.length; ++i){
        data[i] = s.data[i];
    }
    data[s.length] = L'\0';
	length = s.length;
}

void CharString::resetString(const myChar * s){
    int len = std::wcslen(s);
    if(len >= capacity){
        delete [] data;
        data = new myChar [len + 1 + ex_len];
        capacity = len + 1 + ex_len;
    }
    for(int i = 0; i < len; i++){
        data[i] = s[i];
    }
    data[len] = L'\0';
    length = len;
}

void CharString::append(const myChar * s){
    int len = std::wcslen(s);
    int sum_len = len + length;
    while(sum_len >= capacity){
        expand();
    }

    for(int i = length; i < sum_len; i++){
        data[i] = s[i - length];
    }
    data[sum_len] = L'\0';
    length = sum_len;
}

void CharString::expand() {
    myChar * temp = data;
    capacity *= 2;
	capacity += ex_len;
    data = new myChar [capacity];
    for(int i = 0; i < length; i++){
        data[i] = temp[i];
    }
}

int CharString::indexOf(myChar t, int pos){
    if(pos < length){
        for(int i = pos; i < length; i++){
            if(data[i] == t) {
                return i;
            }
        }
        return -1;
    }
    else{
        return -1;
    }
}

int CharString::indexOf(const myChar * c, int pos, int len){
    if(pos < length){
        for(int i = pos; i < length; i++) {
            for (int j = 0; j < len; j++) {
                if (data[i] == c[j]) {
                    return i;
                }
            }
        }
        return -1;
    }
    else{
        return -1;
    }
}

int CharString::indexOf(CharString& p, int pos){
    int m, n, q;
    int* pi;
    if(pos < length){
        n = length - pos;
        m = p.length;
		if(n < m || m <= 0){
            return -1;
        }
        else{
            pi = compute_prefix(p);
            q = 0;
            for(int i = 1; i <= n; i++){
                while(q > 0 && p.data[q] != data[pos+i-1]){
                    q = pi[q-1];
                }
                if(p.data[q] == data[pos+i-1]){
                    q++;
                }
                if(q == m){
                    return i - m + pos;
                }
            }
        }
        return -1;
    }
    else{
        return -1;
    }
}

int CharString::indexOf(const myChar * p, int pos){
    int m, n, q;
    int* pi;
    if(pos < length){
        n = length - pos;
        m = wcslen(p);
        if(n < m || m <= 0){
            return -1;
        }
        else{
            pi = compute_prefix(p, m);
            q = 0;
            for(int i = 1; i <= n; i++){
                while(q > 0 && p[q] != data[pos+i-1]){
                    q = pi[q-1];
                }
                if(p[q] == data[pos+i-1]){
                    q++;
                }
                if(q == m){
					delete [] pi;
                    return i - m + pos;
                }
            }
        }
		delete [] pi;
        return -1;
    }
    else{
        return -1;
    }
}

int* CharString::compute_prefix(CharString& p){
    return compute_prefix(p.data, p.length);
}


int* CharString::compute_prefix(const myChar * p, int m){
	if (m <= 0){
		std::cout << "empty pattern" << std::endl;
		return nullptr;
	}
    int* pi = new int[m];
    pi[0] = 0;
    int k = 0;
    for(int q = 2; q <= m; q++){
        while (k > 0 && p[k] != p[q-1]){
            k = pi[k-1];
        }
        if(p[k] == p[q-1]){
            k++;
        }
        pi[q-1] = k;
    }
    return pi;
}

void CharString::strip(){
	int s_nospace;
	int e_nospace;

	s_nospace = -1;
	e_nospace = length;
	for(int i = 0; i < length; i++){
		if(iswalnum(data[i])){
			s_nospace = i;
			break;
		}
	}
	for(int i = length-1; i >= 0; i--){
		if(iswalnum(data[i])){
			e_nospace = i+1;
			break;
		}
	}	
	if(s_nospace < 0){
		data[0] = L'\0';
		length = 0;
	}
	else{
		for(int i = s_nospace; i < e_nospace; i++){
			data[i-s_nospace] = data[i];
		}
		length = e_nospace - s_nospace;
		data[length] = L'\0';
	}
}

void CharString::stripChinese(){
	int s_nospace;
	int e_nospace;

	s_nospace = -1;
	e_nospace = length;
	for(int i = 0; i < length; i++){
		if(!(iswspace(data[i]) || data[i] == L'£¬' || data[i] == L'£º' || data[i] == L'¡£' || data[i] == L'£»' || data[i] == L'£¿' || data[i] == L'£¡')){
			s_nospace = i;
			break;
		}
	}
	for(int i = length-1; i >= 0; i--){
		if(!(iswspace(data[i]) || data[i] == L'£¬' || data[i] == L'£º' || data[i] == L'¡£' || data[i] == L'£»' || data[i] == L'£¿' || data[i] == L'£¡')){
			e_nospace = i+1;
			break;
		}
	}	
	if(s_nospace < 0){
		data[0] = L'\0';
		length = 0;
	}
	else{
		for(int i = s_nospace; i < e_nospace; i++){
			data[i-s_nospace] = data[i];
		}
		length = e_nospace - s_nospace;
		data[length] = L'\0';
	}
}

CharString* CharString::substring(int index1, int index2){
    if(index1 < index2 && index1 >= 0 && index2 <= length){
        CharString* sub_string = new CharString(index2 - index1+1);
        for(int i = index1; i < index2; i++){
            sub_string->data[i - index1] = data[i];
        }
        sub_string->data[index2-index1] = L'\0';
        sub_string->length = index2 - index1;
        return sub_string;
    }
    else{
		std::cout << "Warning: index out of range" << std::endl;
        CharString* sub_string = new CharString;
        return sub_string;
    }
}

CharString* CharString::concat(CharString& back){
    int sum_len = length + back.length;
    CharString* sum_string = new CharString(sum_len);
    int i;
    for(i = 0; i < length; i++){
        sum_string->data[i] = data[i];
    }
    for(i = length; i < sum_len; i++){
        sum_string->data[i] = back.data[i-length];
    }
    sum_string->data[sum_len] = '\0';
    sum_string->length = sum_len;
    return sum_string;
}

bool CharString::operator==(CharString& s) {
    if(s.length == length){
        for(int i = 0; i < length; i++){
            if(data[i] != s.data[i]){
                return false;
            }
        }
        return true;
    }
    else{
        return false;
    }
}

bool CharString::operator==(const myChar* s) {
    int slength = wcslen(s);
    if(slength == length){
        for(int i = 0; i < length; i++){
            if(data[i] != s[i]){
                return false;
            }
        }
        return true;
    }
    else{
        return false;
    }
}

myChar CharString::operator[](int index) {
	if(index < length && index >= 0){
		return data[index];
	}
	else{
		std::cout << "Warning: index out of range" << std::endl;
		return L'\0';
	}
	 
}

std::wostream& operator<<(std::wostream& os, CharString* s){
    os << s->data;
    return os;
}

int CharString::htmlHash(){
    unsigned int hash = 0;
    for(int i = 0; i < length; i++){
        hash += 10000000 + data[i];
    }
    return hash;
}

unsigned int CharString::tableHash(){
	return WordTable::hashFunction(data, length);
    /*unsigned int number = 0;
    for(int i = 0; i < length; i++){
        number += data[i];
		number <<= (4 * (i+1));
    }
    return number % 40000000;*/
}

void CharString::spaceToSpace(const wchar_t * s){
    int len = wcslen(s);
    int i;
	wchar_t temp_cha;

    i = 0;
    while(i < len){
		if(iswspace(s[i])){
			temp_cha = L' ';
		}
		else{
			temp_cha = s[i];
		}
		i+=1;
		data[length] = temp_cha;
        length += 1;
        if(length == capacity){
            expand();
        }
    }
}

void CharString::utf8ToWchar(const char * s){
    int len;

	len = ::MultiByteToWideChar(CP_UTF8, NULL, s, strlen(s), NULL, 0); 
	while(len + length >= capacity){
		expand();
	}
	::MultiByteToWideChar(CP_UTF8, NULL, s, strlen(s), data + length, len);
	data[len + length] = L'\0';
	length += len;
}