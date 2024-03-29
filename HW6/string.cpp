#include "string.h"
#include <iostream>
#include <cstring>
#include "ip.h" 

#define MIN_INT 0
#define MAX_INT 255
#define MAX_SHIFT 24
#define BITS_IN_BYTE 8
#define MAX_POWER 24

String::String(){
	data = NULL;
	length = 0;
}
String::String(const String &str) {
    length = str.length;
    if (0 == length)
	{
		data = NULL;
	} else{
    data = new char[length+1];
    if(NULL != data){
			strncpy(data, str.data, length + 1);
		}else{
			length = 0;
		}
	}
}
String::String(const char *str) {
	if (str == NULL){
			data = NULL;
			length = 0;
			return;
	}
    length = strlen(str);
    if(length == 0){
    	data = NULL;
    }
    else{
		data = new char[length + 1];
		
		if(NULL != data){
			strncpy(data, str, length + 1);
		}else{
			length = 0;
		}
	}
}

String::~String(){
	if(NULL != data) {
		delete[] data;
	}
}

String& String::operator=(const String &rhs){
	if(this == &rhs) {
		return *this;
	}
	if(data != NULL) {
		delete[] data;
	}

	length = rhs.length;
	if(!length){
		data = NULL;
	}else{
		data = new char[length + 1];

		if(NULL != data){
			strcpy(data, rhs.data);
		}else{
			length = 0;
		}
	}

	return *this;
}

String& String::operator=(const char *str){
	//Free old string
	if(NULL != data) {
		delete[] data;
	}
	if(NULL == str)
	{
		data = NULL;
		length = 0;
		return *this;
	}

	length = strlen(str);
	if(0 == length){
		data = NULL;
	}else{
		data = new char[length + 1];
		
		if(NULL != data){
			strcpy(data, str);
		}else{
			length = 0;
		}
	}

	return *this;
}

bool String::equals(const String &rhs) const {
	if((this == &rhs) || (this->data == rhs.data)) {
		return true;
	}
	if(length != rhs.length){
		return false;
	}

	if(0 == strcmp(data, rhs.data)){
		return true;
	}

	return false;
}

bool String::equals(const char *rhs) const {
	if(this->data == rhs) {
		if(this->data == NULL){
			return false;
		}
		return true;
	}
	if((rhs == NULL) || (this->data == NULL)){
		return false;
	}
	if(length != strlen(rhs)){
		return false;
	}

	if(0 == strcmp(data, rhs)){
		return true;
	}
	return false;
}

void String::split(const char *delimiters, String **output, size_t *size) const {
	int start = 0, substr = 0;
	unsigned int delimiter = 0, delimiters_num = 0;
	unsigned int num_subs_trings = 0; 
	char dataCopy1[length + 1] = {0};
	char dataCopy2[length + 1] = {0};

	if(NULL == size){
		return;
	}

	*size = 0;

	if(NULL == delimiters || NULL == data){ 
	return;
	}
	strcpy(dataCopy1, data);
	strcpy(dataCopy2, data);
	delimiters_num = strlen(delimiters);
	
	for(unsigned int i = 0; i < length; i++){
		for(delimiter = 0; delimiter < delimiters_num; delimiter++){
			if(dataCopy1[i] == delimiters[delimiter]) {
				if(i == 0){
					dataCopy1[i] = '\0';
					break;
				}
				else if(dataCopy1[i-1] == '\0'){
					dataCopy1[i] = '\0';
					break;
				}
				else {
					dataCopy1[i] = '\0';
					num_subs_trings++;
					break;
				}

			}
			if((i == length-1) && (delimiter == delimiters_num -1)){
				num_subs_trings++;
			}
		} 
	}
	*size = num_subs_trings;
	if(NULL == output){
		return;
	}

	*output = new String[num_subs_trings];


	for(unsigned int i = 0; i < length; i++){
		for(delimiter = 0; delimiter < delimiters_num; delimiter++){
			if(dataCopy2[i] == delimiters[delimiter]){
				if(i == 0){
					dataCopy2[i] = '\0';
					start = i + 1;
					break; //we found one delimiter
				}
				else if(dataCopy2[i-1] == '\0'){
					dataCopy2[i] = '\0';
					start = i + 1;
					break; //we found one delimiter
				}
				else{
				 	dataCopy2[i] = '\0';
				 	(*output)[substr] = String(&dataCopy2[start]);
				 	start = i + 1;
				 	substr++;
				 	break;
				}

			}
			if((i == length-1) && (delimiter == delimiters_num -1)){
				(*output)[substr] = String(&dataCopy2[start]);
			}
		} 
	}
	return;
}
 



int String::to_integer() const {
    int convert = 0;
    String* sub_strings = NULL;
    size_t size = 0;

    split(".", &sub_strings, &size);

 
    if(size == IP_NUM) {

        for(size_t i=0; i < size; i++) {
            int place = sub_strings[i].trim().to_integer();
            if ((place > MAX_INT) || (place < MIN_INT)) {
                delete[] sub_strings;
                return 0;  
            }
            int power = MAX_POWER - (i * BITS_IN_BYTE);
            place = place*(2^(power));
            convert += place;
        }
    }
    else {    
        convert = atoi(data);
    }
    delete[] sub_strings;
    return convert;
}
 
String String::trim() const {
    int space_start = 0;
    int space_end = length;
    if(NULL == data){
		return String();
	}
    for (size_t i=space_start; i<length; i++) {    // Leading white-spaces 
        if (data[i] == ' ') {
            space_start += 1;
        } else {
            break;
        }
    }
    for (int j=space_end; j>=0; j--) {    // Trailing white-spaces 
        if (data[j] == ' ') {
            space_end -= 1;
        } else {
            break;
        }
    }
    size_t new_length = space_end - space_start + 1;
    char temp[new_length + 1];
    strcpy(temp, &data[space_start]);
    temp[new_length] = '\0';
    return String(temp);
}
