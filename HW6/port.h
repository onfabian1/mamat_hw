#ifndef PORT_H
#define PORT_H
#include "field.h"
#include "string.h"
#define MAX_SIZE (2)

class Port: public Field{
private:
	int low;
	int high;
	
public:
    Port(String pattern);
    virtual bool set_value(String val);
    virtual bool match_value(String val) const;
};
#endif