#include "db.h"
std::ostream& operator<< (std::ostream& os, const Product& it)
{
	os << "nazwa: " << it.name << "  cena: " << it.price << "  szt: " << it.quantity << std::endl;
	return os;
}

void DB::printAllProduct()
{
	std::cout << "Lista wszystkich dostepnych produktow:" << std::endl;
	int i = 0;
	for (const auto& it : shop)
	{
		std::cout << "nr " << i << ":  " << it;
		++i;
	}
}

void DB::buy(std::list<Product>::iterator it)
{
	income += it->price;
	if (!(--it->quantity))
	{
		shop.erase(it);
	}
}

std::string DB::enum2str(DB::EventType type)
{
	switch (type)
	{
	case EventType::order:return "{order}:	";
	case EventType::complaintLodged:return"{complaintLodged}:	";
	case EventType::considerationOfComplaint:return"{considerationOfComplaint}:	";
	case EventType::createClientAccount:return"{createClientAccount}:	";
	case EventType::addWorker:return "{addWorker}:	";
	default: return"";
	}
}