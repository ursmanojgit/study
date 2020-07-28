#ifndef HOV_H
#define HOV_H

#include "OfferVisitor.h"

class HotelOfferVisitor :public OfferVisitor {
public:
	virtual void visitCreditCard(SilverCard* cc);
};
#endif