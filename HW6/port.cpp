#include <cstdlib>
#include "port.h"


class Port: public Field{
private:
	int low;
	int high;
	
public:
     Port(String pattern);
     bool set_value(String val){
    	String *arr;
    	size_t size;
    	val.split("-",&arr,&size);
    	if(size > 2){
    		delete[] arr;
    		return false;
    	}
    	if(1 != size){
    		low = arr[0].trim().to_integer();
    		high = low;
     	}else{
    		low = arr[0].trim().to_integer();
    		high = arr[1].trim().to_integer();
    	}
    	delete[] arr;
    	return low && high;
    }
    virtual bool match_value(String val) const{
    	int temp = val.trim().to_integer();
    	return (temp >= low) && (temp <= high);
    }
};



