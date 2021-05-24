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
	int mask = arr[1].trim().to_integer();


	unsigned int ip = arr[0].trim().to_integer();

	int n = 32 - mask;
	delete[] arr;

	if(n<0 || n>32){
		return false;
	}
	/*unsigned int bit;
	if(mask==32){
		bit = 0xFFFFFFFF;
	}*/
	bottom = ip - ip%(2^n);
	top = ip | (2^n-1);
	/*else	bit = ((unsigned int)1 << n) - 1;

	top = ip | bit;
	bottom = ip & (~bit);
	return true;
}	*/

bool Ip::match_value(String val) const{
	unsigned int retVal = (unsigned int)val.trim().to_integer();
	return ((bottom <= retVal) && (retVal <= top));
}
