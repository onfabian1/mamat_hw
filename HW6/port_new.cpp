#include <cstdlib>
#include "port_new.h"


Port::Port(String pattern): Field(pattern) {

}

bool Port::set_value(String val){
    String *arr;
    size_t size;
	val.split("-",&arr,&size);
	if(size > MAX_SIZE){
		delete[] arr;
		return false;
	}
    if(!size){
        delete[] arr;
        return false;
    }
	if(MAX_SIZE != size){
		low = arr[0].trim().to_integer();
		high = low;
	}
    else{
    	low = arr[0].trim().to_integer();
    	high = arr[1].trim().to_integer();
	}
	delete[] arr;
	return low && high;
}

bool Port::match_value(String val) const{
    int temp = val.trim().to_integer();
	return (temp >= low) && (temp <= high);
}




