#ifndef IP_H
#define IP_H

#include "field.h"
#include "string.h"

class Ip: public Field{
private:
	int top;
	int bottom;

public:
	Ip(String pattern);
	virtual bool set_value(String val);
    virtual bool match_value(String val) const;
};

#endif