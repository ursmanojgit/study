#ifndef CC_H
#define CC_H

#include "OfferVisitor.h"
#include <string>

class CreditCard {
public:
	virtual std::string getName() = 0;
	virtual void visit(OfferVisitor *) = 0;
};

#endif