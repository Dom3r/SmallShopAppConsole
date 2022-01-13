#include "Manager.h"
#include "db.h"
#include<string>
Manager::Manager()
    : Worker("root", "root", "Manager", 15000)
{
}


void Manager::run() {
    while (true) {
        std::cout << "Konto Managera: " << login << std::endl;
        std::cout << "1 : Wyloguj" << std::endl;
        std::cout << "2 : Pokaz wszystkich klientow" << std::endl;
        std::cout << "3 : Pokaz wszystkich pracownikow" << std::endl;
        std::cout << "4 : Wyplac pensje" << std::endl;
        std::cout << "5 : Zmien haslo" << std::endl;
        std::cout << "6 : Zatrudnij pracownika" << std::endl;
        std::cout << "7 : Pokaz przychod" << std::endl;

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
            showWorkers();
            break;
        case '4':
            paySalary();
            break;
        case '5':
            changePassword();
            break;
        case '6':
            addWorker();
            break;
        case '7':
            showIncome();
            break;
        default:
            std::cout << "Nieznana opcja, wybierz poprawny klawisz!" << std::endl << std::endl << std::endl;
            break;
        }
    }

}

void Manager::showWorkers() {
    std::cout << "Lista wszystkich istniejacych kont pracownikow:" << std::endl;
    int i = 0;
    for (auto& it : DB::Instance().workers)
    {
        std::cout << "nr " << i << ":    " << *it.second;
        ++i;
    }
}

void Manager::paySalary() {
    for (auto& it : DB::Instance().workers)
    {
        std::cout << "Wyplacono pensje pracownikowi " << *it.second ;
        DB::Instance().income -= it.second->salary;
    }
}

void Manager::addWorker() {
    std::string login_;
    std::string password_;
    std::string position_;
    int salary_;
    std::cout << "Podaj nazwe nowego konta pracownika" << std::endl;
    std::cin >> login_;
    std::cout << "Podaj haslo dla nowego konta" << std::endl;
    std::cin >> password_;
    std::cout << "Podaj pozycje pracownika" << std::endl;
    std::cin.clear();
    std::cin.sync();
    std::cin.ignore();
    std::getline(std::cin, position_);
    std::cout << "Podaj wysokosc pensji nowego pracownika" << std::endl;
    std::cin >> salary_;
    std::cin.clear();
    DB::Instance().workers.insert(std::make_pair(login_, std::make_unique<Worker>(login_, password_, position_, salary_)));
}

void Manager::showIncome() {
    std::cout << "Przychod: " << DB::Instance().income << std::endl;
}
