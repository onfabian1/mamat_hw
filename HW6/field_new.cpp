#include <iostream>
#include <cstring>
#include "field.h"


//constructor:
Field::Field(String pattern){
	this->pattern = pattern;
}

//distructor:
Field::~Field(){

}

bool Field::match(String packet){
	size_t size = 0;
	bool val = false;
	String *arr;

	packet.split("=,", &arr, &size);
	if(!size){ //no data
		delete[] arr;
		return val;
	}
	
	for(int i=0; i<(int)size; i+=2){
		if(pattern.equals(arr[i].trim())){
			val = match_value(arr[i+1].trim());
			delete[] arr;
			return val;
		}
	}
	delete[] arr;
	return val;	
}
