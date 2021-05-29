#include <iostream>
#include "ip_new.h"
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
	
	bottom = ip - ip%(2^n);
	top = ip | ((2^n)-1);
	return true;
}

bool Ip::match_value(String val) const{
	const int ret = (unsigned int)val.trim().to_integer();
	return ((bottom <= ret) && (ret <= top));
}
