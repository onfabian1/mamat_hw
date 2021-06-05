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
	size_t size;
	bool val = false;
	String *arr;

	packet.split("=,", &arr, &size);
	if(!size){ //no data
		//delete[] arr;
		return val;
	}
	//src-ip=50-52
	for(int i=0; i<(int)size; i+=2){
	//parser
		if(pattern.equals(arr[i].trim())){
		//mask
			val = match_value(arr[i+1].trim());
			break; // matched rule
		}
	}
	delete[] arr;
	return val;	
}
