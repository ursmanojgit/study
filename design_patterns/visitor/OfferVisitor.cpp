#include "HotelOfferVisitor.h"
#include <iostream>

using namespace std;

void HotelOfferVisitor::visitCreditCard(SilverCard* cc) {
	cout << "Silver Card Used in Hotel" << endl;
}