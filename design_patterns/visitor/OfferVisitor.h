#ifndef OV_H
#define OV_H

//#include "SilverCard.h"
class SilverCard;

class OfferVisitor {
public:
	virtual void visitCreditCard(SilverCard* cc) = 0;
};

#endif