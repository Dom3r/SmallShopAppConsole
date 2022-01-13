#include "Client.h"
#include <iostream>
#include "db.h"
#include <sstream>

Client::Client(std::string l, std::string h) : numOfOrders(0)
{
    login = l;
    password = h;
    std::stringstream tmp;
    tmp << "Nowy klient: " << *this;
    DB::Instance().event.insert(std::make_pair(DB::EventType::createClientAccount, tmp.str()));
}

void Client::run()
{
    while (true) {
        std::cout << "Konto Klienta: " << login << std::endl;
        std::cout << "1 : Wyloguj" << std::endl;
        std::cout << "2 : Zloz zamowienie" << std::endl;
        std::cout << "3 : Zloz skarge" << std::endl;
        std::cout << "4 : Zmien haslo" << std::endl;
        char choice;
        std::cin >> choice;

        switch (choice)
        {
        case '1':
            return;
        case '2':
            showShop();
            break;
        case '3':
            addComplaints();
            break;
        case '4':
            changePassword();
            break;
        default:
            std::cout << "Nieznana opcja, wybierz poprawny klawisz!" << std::endl << std::endl << std::endl;
            break;
        }
    }
}

void Client::showShop()
{
    if (DB::Instance().shop.empty())
    {
        std::cout << "W sklepie nie ma towaru" << std::endl;
        return;
    }
    DB::Instance().printAllProduct();
    std::cout << "Wybierz nr produktu ktory chcesz zamowic" << std::endl;

    unsigned int choice;
    std::cin >> choice;

    if (choice >= DB::Instance().shop.size())
    {
        std::cout << "Nie ma towaru z takim numerem. Powrot do wczesniejszego menu." << std::endl;
    }
    else
    {
        auto it = DB::Instance().shop.begin();
        std::advance(it, choice);
        std::cout << "Dokonano zakupu towaru: " << it->name<<std::endl;
        std::stringstream tmp;
        tmp << "Dokonano zakupu towaru: " << it->name << " " << " przez klienta: " << *this;
        DB::Instance().event.insert(std::make_pair(DB::EventType::order, tmp.str()));
        ++numOfOrders;
        DB::Instance().buy(it);
    }
}
void Client::addComplaints()
{
    std::cout << "Napisz wiadomosc ze skarga" << std::endl;
    std::string tmp = "";
    std::cin.clear();
    std::cin.sync();
    std::cin.ignore();
    std::getline(std::cin, tmp);
    DB::Instance().complaints.insert(std::make_pair(login, tmp));
    std::cout << "Skarga zostala wyslana do sklepu" << std::endl;
    std::stringstream temp;
    temp << "Zlozenie skargi przez klienta: " << *this << "tresc skargi: " << tmp;
    DB::Instance().event.insert(std::make_pair(DB::EventType::complaintLodged, temp.str()));
}
std::ostream& operator<< (std::ostream& os, const Client& it)
{
    os << "login: " << it.login << "  ilosc wykonanych transakcji: " << it.numOfOrders << std::endl;
    return os;
}