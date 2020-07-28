#include "SilverCard.h"
#include "HotelOfferVisitor.h"

int main(void) {
	SilverCard cc;

	HotelOfferVisitor hofv;
	cc.visit(&hofv);
}