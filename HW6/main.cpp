#include <cstring>
#include <iostream>
#include "port.h"
#include "ip.h"
#include "input.h"

/*
extern int check_args(int, char**);
extern void parse_input(Field&);
I did input insted of extern*/

int main(int argc, char** argv){
	
	if(check_args(argc,argv)){
		return 1;
	}

	Field *field;
	String rule(argv[1]);
	String *arr;
	size_t size;
	rule.split("=", &arr, &size);
	//check if valid
	if(!size){
		delete[] arr;
		return 1;
	}

	const char* const str[4] = {"dst-port", "src-port", "dst-ip", "src-ip"};
	if(arr[0].trim().equals(str[0]) || arr[0].trim().equals(str[1])){ 
		field = new Port(arr[0]);
		/*Field *port = new Port(arr[0]);
		port->set_value(arr[1]);
		parse_input(*port);
		delete port;
		delete[] arr;
		return 0;*/
	}

	else if(arr[0].trim().equals(str[2]) || arr[0].trim().equals(str[3])){
		field = new Ip(arr[0]);
		/*Field *ip = new Ip(arr[0]);
		ip->set_value(arr[1]);
		parse_input(*ip);
		delete ip;
		delete[] arr;
		return 0;*/
	}
	
	field->set_value(arr[1]);
	parse_input(*field);
	delete field;
	delete[] arr;
	return 0;
}	
