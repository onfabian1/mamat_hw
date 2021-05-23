#include <iostream>
#include "Ip.h"
#include <cstring>

Ip::Ip(String pattern): Field(pattern){

}

bool Ip::set_value(String val){
	String *arr;
	size_t size;

	//mask
	val.split("/",&arr,&size);
	if(size==0 || size>IP_MASK){
		delete[] arr;
		return false;
	}
	int mask = arr[0].trim().to_integer();

	//make substrs ip 
	val.split(".", &arr, &size);
	if(size != IP_NUM){ 
		delete[] arr;
		return false;
	}

	unsigned int ip = arr[0].trim().to_integer(0) <<24 | arr[1].trim().to_integer() << 16 | arr[2].trim().to_integer() << 8 | arr[3].trim().to_integer();
	int n = 32 - mask;
	delete[] arr;

	if(n<0 || n>32){
		return false;
	}
	unsigned int bit;
	if(mask==32){
		bit = 0xFFFFFFFF;
	}
	else	bit = ((unsigned int)1 << n) - 1;

	top = ip & (~bit);
	bottom = ip | bit;
	return true;
}	

bool Ip::match_value(String val) const{
	unsigned int retVal = (unsigned int)val.trim().to_integer();
	return ((low <= retVal) && (retVal <= high));
}
