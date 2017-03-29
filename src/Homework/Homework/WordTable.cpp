#include "HashTable.h"
#include "CharStringLink.h"
#include <locale>
#include <exception>


void WordTable::constructCharacterTable() {

}

unsigned int WordTable::hashFunction(const myChar * data, int len){
    unsigned int number = 0;
    for(int i = 0; i < len; i++){
        number += data[i];
		number *= (i+1);
		number += 123456;
		number *= 1234;
		number <<= (i+2);
    }
    return number % 40000000;
}

unsigned int WordTable::hashFunction(CharString& data1){
    return data1.tableHash();
}

void WordTable::initDictionary(CharString& s) {
    int len1 = s.size();
    CharString* current_word;
    int start;
    int end;

    start = 0;
    for(int i = 0; i < len1; i++){
        while(i < len1 && s[i] != L' '){
            i += 1;
        }
		end = i;
        if(max_length < end - start){
            max_length = end - start;
        }
		if(end > start){
			current_word = s.substring(start, end);
			word.add(current_word, hashFunction(*current_word));
			//delete current_word;
			//current_word = nullptr;
		}
		if(len1 <= i){
			break;
		}
		while(i < len1 && s[i] == L' '){
            i += 1;
        }
		start = i;
    }
	word_construct = true;
}

void WordTable::divideWords(CharString& data, CharStringLink& result) {
	if(!word_construct){
		std::cout << "Warning: initialize word dictionary first" << std::endl;
	}
    int space_data;
    int last_space;
    CharString* sub_string;
    CharString* temp_str;
    int temp_max;
    bool isword;
    int len_substring;
    int current_index;
	std::locale loc;

    space_data = 0;
    while (space_data != -1){
		last_space = space_data;
		space_data = data.indexOf(L' ', space_data+1);
        if(space_data == -1){
            sub_string = data.substring(last_space, data.size());
        }
        else {
            sub_string = data.substring(last_space, space_data);
        }
        len_substring = sub_string->size();
        if(len_substring > max_length){
            temp_max = max_length;
        }
        else{
            temp_max = len_substring;
        }   
		current_index = 0;
		while(len_substring > 0){
			int alpha_length = 0;
			while(len_substring > alpha_length && (*sub_string)[current_index + alpha_length] < 128){
				alpha_length += 1;
			}
			if(alpha_length > 0){
				CharString* raw_string = sub_string->substring(current_index, current_index + alpha_length);
				raw_string->strip();
				if(raw_string->size() > 0){
					result.add(*raw_string);
				}
				delete raw_string;
				len_substring -= alpha_length;
				current_index += alpha_length;	
                if(len_substring < max_length){
                    temp_max = len_substring;
                }
                else{
                    temp_max = max_length;
                }	
				continue;
			}
			int digit_length = 0;
			while(len_substring > digit_length && isdigit((*sub_string)[current_index + digit_length], loc)){
				digit_length += 1;
			}
			if(digit_length > 0){
				CharString* temp_str1 = sub_string->substring(current_index, current_index + digit_length);
				result.add(*temp_str1);
				len_substring -= digit_length;
				current_index += digit_length;	
                if(len_substring < max_length){
                    temp_max = len_substring;
                }
                else{
                    temp_max = max_length;
                }	
				continue;
			}
            for(int i = temp_max; i > 0; i--){
                temp_str = sub_string->substring(current_index, current_index + i);
                isword = word.search(temp_str->c_str(),hashFunction(*temp_str));
                if(isword || i == 1){
                    len_substring -= i;
                    current_index += i;
                    if(len_substring < max_length){
                        temp_max = len_substring;
                    }
                    else{
                        temp_max = max_length;
                    }
					if(!ispunct((*temp_str)[0], loc) && !isspace((*temp_str)[0], loc)){
						CharString* last_word = result.back();
						if(last_word != nullptr && last_word->size() <= 1 && temp_str->size() <= 1){
							last_word = last_word->concat(*temp_str);
							result.remove();
							result.add(*(last_word));
						}
						else{
							result.add(*temp_str);
						}
					}
					break;
                }
				delete temp_str;
            }
        }
    }
}