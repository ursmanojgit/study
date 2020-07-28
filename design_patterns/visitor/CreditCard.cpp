#include "SilverCard.h"
#include <iostream>
using namespace std;

string SilverCard::getName() {
	cout << "Silver" << endl;
	return "Silver";
}
void SilverCard::visit(OfferVisitor* ov) {
	ov->visitCreditCard(this);
}