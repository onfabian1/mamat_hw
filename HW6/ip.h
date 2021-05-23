#ifndef IP_H
#define IP_H

#include "field.h"
#include "string.h"
#define IP_NUM (4)
#define IP_MASK (2)

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