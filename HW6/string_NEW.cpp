#include "string.h"
#include <iostream>
#include <cstring>
#include "ip.h" /* for to_integer() */

/* Default constructor */
String::String(){
	data = NULL;
	length = 0;
}

/* Copy constructor */	
String::String(const String &str) {
    length = str.length;
    if (0 == length)
	{
		data = NULL;
	} else{
    data = new char[length+1];
    strcpy(data,str.data);
	}
}

/* constructor */
String::String(const char *str){
	// check for nullptr
	if(str == NULL){
		length = 0;
		data = NULL;
		return;
	}

	length = strlen(str); //include the \0
	
	// if empty string - return
	if(0 == length){
		data = NULL;
	}else{
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
	/* verify we are not self-asigning */
	if(this == &rhs) {
		return *this;
	}

	//Free old string
	if(NULL != data) {
		delete[] data;
	}

	length = rhs.length;
	
	// if empty string - return
	if(0 == length){
		data = NULL;
	}else{
		data = new char[length + 1];

		if(NULL != data){
			strncpy(data, rhs.data, length + 1);
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

	//check for NULL parameter
	if(NULL == str)
	{
		data = NULL;
		length = 0;
		return *this;
	}

	length = strlen(str);

	// if empty string - return
	if(0 == length){
		data = NULL;
	}else{
		data = new char[length + 1];
		
		if(NULL != data){
			strncpy(data, str, length + 1);
		}else{
			length = 0;
		}
	}

	return *this;
}

bool String::equals(const String &rhs) const {
	if(length != rhs.length){
		return false;
	}

	if(0 != strncmp(data, rhs.data, length)){
		return false;
	}

	return true;
}

bool String::equals(const char *rhs) const {
	// Check nullptr
	/* TODO: Check with TA what is the expected result if rhs == NULL and data == NULL */
	if(NULL == rhs)
	{
		if(data == NULL) {
			return true;
		}
		return false;
	}

	if(length != strlen(rhs)){
		return false;
	}

	if(0 != strncmp(data, rhs, length)){
		return false;
	}

	return true;
}

void String::split(const char *delimiters, String **output, size_t *size) const {
	int start = 0, substr = 0;
	unsigned int delimiter = 0, numDelimiters = 0;
	unsigned int numSubstrings = 0; 
	char dataCopy1[length + 1] = {0};
	char dataCopy2[length + 1] = {0};

	//TODO: check with TA if we have to proceed in case size == NULL
	if(NULL == size){
		return;
	}

	*size = 0;

	//TODO: check with TA regarding expected behaviour on NULL == delimiters (should we allocate 1 substr or not?)
	//TODO: check with TA regarding expected behaviour on NULL == data (should we allocate 1 substr of empty string or not?)
	if(NULL == delimiters || NULL == data){ 
		return;
	}

	//copy original string to temporary value
	strcpy(dataCopy1, data);
	strcpy(dataCopy2, data);
	numDelimiters = strlen(delimiters);
	//count number of substrings
	for(unsigned int i = 0; i < length; i++){
		for(delimiter = 0; delimiter < numDelimiters; delimiter++){
			if(dataCopy1[i] == delimiters[delimiter]) {
				if((dataCopy1[i-1] == '\0') || (i == 0)){
					dataCopy1[i] = '\0';
					break;
				}
				else {
					dataCopy1[i] = '\0';
					numSubstrings++;
					break;
				}

			}
			if((i == length-1) && (delimiter == numDelimiters -1)){
				numSubstrings++;
			}
		} 
	}
	*size = numSubstrings;

	/* checking output for NULL here because we need to update size before exit. otherwise check_args() fails */
	if(NULL == output){
		return;
	}

	//allocate substrings
	*output = new String[numSubstrings];

	//TODO: check with TA if need to allocate empty string in case of 2 following delimiters "aaa,,bbb"
	//copy each substring to output
	for(unsigned int i = 0; i < length; i++){
		for(delimiter = 0; delimiter < numDelimiters; delimiter++){
			if(dataCopy2[i] == delimiters[delimiter]){
				if((dataCopy2[i-1] != '\0') || (i != 0)){
					dataCopy2[i] = '\0';
					(*output)[substr] = String(&dataCopy2[start]);
					start = i + 1;
					substr++;
					break; //we found one delimiter
				}
				else{
				 	dataCopy2[i] = '\0';
				 	start = i + 1;
				 	break;
				}

			}
			if((i == length-1) && (delimiter == numDelimiters -1)){
				(*output)[substr] = String(&dataCopy2[start]);
			}
		} 
	}
	return;
}
 
 /* create integer from string. return 0 in case of error */
int String::to_integer() const { 
	int ret = 0;
	String* substrs;
	size_t size = 0;

	//if our data is a string representing ip
	split(".", &substrs, &size);

	if(IP_SEGMENTS == size) { // if the format is XXX.XXX.XXX.XXX parse as IP

		//trim the each  sub string and build full integer
		for(unsigned int i = 0; i < size; i++){
			int byte = substrs[i].trim().to_integer();
			//if substring is > 255 - the address is not valid
			if((byte > 255) || (byte < 0)){
				delete[] substrs;
				return 0;
			}
			ret |= byte << (24 - (8 * i));
		}

		delete[] substrs;
		return ret;
	
	}else{ // parse as integer
		//we cannot assume that the data is already trimmed, therefore should use: atoi((this->trim()).data)
		//ret = atoi(data);
		/*TODO: check with TA how to treat errors */
		ret = atoi((this->trim()).data);
		if(0 != ret){
			if( NULL != substrs){
				delete[] substrs;
			}
			return ret;
		}
	}

	if( NULL != substrs){
		delete[] substrs;
	}
	return 0;
}

 
String String::trim() const {
	int start = 0;
	int end = length - 1;

	if(NULL == data){
		return String();
	}

	//remove spaces from begining
	while(data[start] == ' '){
		start++;
	}

	//remove spaces from end
	while((data[end] == ' ') && (start != end)){
		end--;
	}
	end++;

	//if no characters in the string - return empty string
	if(start >= end)
	{
		return String();
	}

	char newData[end - start + 1];
	strncpy(newData, &data[start], end - start);
	newData[end - start] = '\0';


	return String(newData);
}
