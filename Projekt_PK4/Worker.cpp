#include "Worker.h"
#include "db.h"
#include "client.h"
#include <sstream>

Worker::Worker(std::string l, std::string p, std::string pos, int s)
    : position(pos), salary(s)
{
    login = l;
    password = p;
     try {
        if (s < 2500)
        {
            salary = 2500;
            throw "minimalnej stawce w firmie 2500zl";

        }
        else if (s > 15000) {
            salary = 15000;
            throw "maksymalnej stawce w firmie 15000zl";
         
        }
        else salary = s;
    }
    catch (const char* e) {
        std::cout << "Pracownik otrzymal wynagrodzenie rowne " << e << std::endl;
    }
    

    std::stringstream tmp;
    tmp << "Nowy pracownik: " << *this;
    if (position != "Manager")
        DB::Instance().event.insert(std::make_pair(DB::EventType::addWorker, tmp.str()));
}

void Worker::run() {
    while (true) {
        std::cout << "Konto Pracownika: " << login << std::endl;
        std::cout << "1 : Wyloguj" << std::endl;
        std::cout << "2 : Pokaz wszystkich klientow" << std::endl;
        std::cout << "3 : Stworz konto nowego klienta" << std::endl;
        std::cout << "4 : Przeczytaj nastepna skarge" << std::endl;
        std::cout << "5 : Zmien haslo" << std::endl;
        std::cout << "6 : Dodaj  towar do sklepu" << std::endl;
        std::cout << "7 : Pokaz zawartosc sklepu" << std::endl;
        char choice;
        std::cin >> choice;

        switch (choice)
        {
        case '1':
            return;
        case '2':
            showClients();
            break;
        case '3':
            addClient();
            break;
        case '4':
            readComplaint();
            break;
        case '5':
            changePassword();
            break;
        case '6':
            addProduct();
            break;
        case '7':
            showAllProduct();
            break;
        default:
            std::cout << "Nieznana opcja, wybierz poprawny klawisz!" << std::endl << std::endl;
            break;
        }
    }

}

void Worker::showClients() {
    std::cout << "Lista wszystkich istniejacych kont klientow:" << std::endl;
    int i = 0;
    for (auto& it : DB::Instance().clients)
    {
        std::cout << "nr " << i << ":    " << *it.second;
        ++i;
    }
}

void Worker::readComplaint() {
    if (DB::Instance().complaints.empty())
    {
        std::cout << "W systemie nie ma zadnych skarg" << std::endl;
        return;
    }
    auto it = DB::Instance().complaints.begin();

    std::cout << "Skarga klienta: " << it->first << " Tresc: " << it->second << std::endl;

    std::cout << "Wybierz 1: by odrzucic skarge" << std::endl;
    std::cout << "Wybierz 2: by wyslac rekompensate klientowi " << std::endl;

    int tmp;
    std::cin >> tmp;
    std::stringstream temp;
    switch (tmp)
    {
    case 1:
        temp << "Rozpatrzenie skargi o tresci: " << it->second << " Skarga odrzucona";
        DB::Instance().event.insert(std::make_pair(DB::EventType::considerationOfComplaint, temp.str()));
        DB::Instance().complaints.erase(it);
        break;
    case 2:
        std::cout << "Podaj wartosc rekompensaty jaka nalezy wyslac klientowi" << std::endl;
        int value;
        std::cin >> value;
        if (value > 0 && value < 100)
        {
            std::cout << "Wyslano rekompensate rowna: " << value << "zl klientowi" << std::endl;
            DB::Instance().income -= value;

            temp << "Rozpatrzenie skargi o tresci: " << it->second << " wyslanie rekonpensaty klientowi";
            DB::Instance().event.insert(std::make_pair(DB::EventType::considerationOfComplaint, temp.str()));
        }
        else {
            std::cout << "Masz uprawnienia do wyslania rekompensaty miedzy 0zl a 100zl, operacja anulowana" << std::endl << std::endl;
        }
        break;
    default:
        std::cout << "Nieznana opcja, operacja anulowana" << std::endl << std::endl;
        break;
    }

}

void Worker::addClient() {
    std::string login_;
    std::string password_;
    std::cout << "Podaj nazwe nowego konta" << std::endl;
    std::cin >> login_;
    std::cout << "Podaj haslo dla nowego konta" << std::endl;
    std::cin >> password_;
    DB::Instance().clients.insert(std::make_pair(login_, std::make_unique<Client>(login_, password_)));
}

std::ostream& operator<<(std::ostream& os, const Worker& it) {
    os << "login: " << it.login << "  pozycja: " << it.position << " pensja: " << it.salary << "zl" << std::endl;
    return os;
}

void Worker::addProduct() {
    std::string name_;
    int quantity_;
    float price_;
    std::cout << "Podaj nazwe towaru" << std::endl;
    std::cin.clear();
    std::cin.sync();
    std::cin.ignore();
    std::getline(std::cin, name_);
    std::cout << "Podaj cene towaru" << std::endl;
    std::cin >> price_;
    std::cout << "Podaj ilosc towaru" << std::endl;
    std::cin >> quantity_;
    std::cin.clear();
    DB::Instance().shop.emplace_back(name_, quantity_, price_);
}

void Worker::showAllProduct() {
    if (DB::Instance().shop.empty())
    {
        std::cout << "W sklepie nie ma towaru" << std::endl;
        return;
    }
    DB::Instance().printAllProduct();

}


