#ifndef SC_H
#define SC_H

#include "CreditCard.h"

class SilverCard : public CreditCard {
public:
	virtual std::string getName();
	virtual void visit(OfferVisitor*);
};
#endif