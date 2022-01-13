#include "application.h"
#include "db.h"

void Application::run()
{
    while (true)
    {
        std::cout << "Wybierz opcje:" << std::endl;
        std::cout << "1 : Okno logowania" << std::endl;
        std::cout << "2 : Zaladuj dane z plikow txt" << std::endl;
        std::cout << "3 : Pokaz liste eventow" << std::endl;
        std::cout << "4 : Wyjscie z programu" << std::endl;
        char choice;
        std::cin >> choice;

        switch (choice)
        {
        case '1':
            login();
            break;
        case '2':
            load();
            break;
        case '3':
            showEvent();
            break;
        case '4':
            return;
        default:
            std::cout << "Nieznana opcja, wybierz poprawny klawisz!" << std::endl << std::endl << std::endl;
        }
    }
}

void Application::login()
{
    std::cout << "Podaj nazwe uzytkownika" << std::endl;
    std::string temp;
    std::cin >> temp;
    auto it = DB::Instance().clients.find(temp); // sprawdzanie w klientach
    if (it != DB::Instance().clients.end())
    {
        std::cout << "Podaj haslo" << std::endl;
        std::cin >> temp;
        if (temp == it->second->password)
        {
            std::cout << "Zalogowano" << std::endl;
            it->second->run();
        }
        else
        {
            std::cout << "Bledne haslo" << std::endl;
        }
    }
    else
    {
        auto itp = DB::Instance().workers.find(temp); // sprawdzanie w pracownikach
        if (itp != DB::Instance().workers.end())
        {
            std::cout << "Podaj haslo" << std::endl;
            std::cin >> temp;
            if (temp == itp->second->password)
            {
                std::cout << "Zalogowano" << std::endl;
                itp->second->run();
            }
            else
            {
                std::cout << "Bledne haslo" << std::endl;
            }
        }
        else if (temp == DB::Instance().manager.login)  // sprawdzanie managera
        {
            std::cout << "Podaj haslo" << std::endl;
            std::cin >> temp;
            if (temp == DB::Instance().manager.password)
            {
                std::cout << "Zalogowano" << std::endl;
                DB::Instance().manager.run();
            }
            else
            {
                std::cout << "Bledne haslo" << std::endl;
            }
        }
        else {
            std::cout << "Nie istnieje uzytkownik o podanym loginie" << std::endl;
        }
    }
}



void Application::load() {
    loadClient();
    loadWorker();
    loadProduct();
}

void Application::loadWorker() {
    std::fstream f;
    f.open("worker.txt", std::ios::in);

    if (!f.good())
    {
        std::cout << "Blad przy wczytaniu danych z worker.txt" << std::endl;
        return;
    }

    std::string l = "";
    std::string p = "";
    std::string pos = "";
    std::string s = "";

    while (!f.eof())
    {
        getline(f, l);
        getline(f, p);
        getline(f, pos);
        getline(f, s);
        if ((l != "") && (p != "") && (pos != "") && (s != ""))
        {
            int ss = std::stoi(s);
            DB::Instance().workers.insert(std::make_pair(l, std::make_unique<Worker>(l, p, pos, ss)));
        }
    }
    f.close();
}

void Application::loadClient() {
    std::fstream f;
    f.open("client.txt", std::ios::in);

    if (!f.good())
    {
        std::cout << "Blad przy wczytaniu danych z client.txt" << std::endl;
        return;
    }

    std::string l = "";
    std::string p = "";
    while (!f.eof())
    {
        getline(f, l);
        getline(f, p);
        if ((l != "") && (p != ""))
        {
            DB::Instance().clients.insert(std::make_pair(l, std::make_unique<Client>(l, p)));
        }
    }
    f.close();
}

void Application::loadProduct() {
    std::fstream f;
    f.open("product.txt", std::ios::in);

    if (!f.good())
    {
        std::cout << "Blad przy wczytaniu danych z product.txt" << std::endl;
        return;
    }

    std::string n = "";
    std::string q = "";
    std::string p = "";

    while (!f.eof())
    {
        getline(f, n);
        getline(f, q);
        getline(f, p);
        if ((n != "") && (p != "") && (q != ""))
        {
            int qq = std::stoi(q);
            float pp = std::stof(p);
            DB::Instance().shop.emplace_back(n, qq, pp);
        }
    }
    f.close();
}

void Application::showEvent() {
    std::cout << "\nWybierz opcje:" << std::endl;
    std::cout << "1 : Pokaz wszystkie eventy" << std::endl;
    std::cout << "2 : Pokaz eventy z zamowieniami" << std::endl;
    std::cout << "3 : Pokaz eventy z tworzeniem klientow" << std::endl;
    std::cout << "4 : Pokaz eventy z zatrudniania pracownikow" << std::endl;
    std::cout << "5 : Pokaz eventy z zlozeniami skarg" << std::endl;
    std::cout << "6 : Pokaz eventy z rozpatrywania skarg" << std::endl;

    char choice;
    std::cin >> choice;
    std::cout << std::endl;
    switch (choice)
    {
    case '1':
        for (const auto& elem : DB::Instance().event)
        {
            std::cout << DB::Instance().enum2str(elem.first) << elem.second << std::endl;
        }
        break;
    case '2':
        for (const auto& elem : DB::Instance().event)
        {
            if (elem.first == DB::EventType::order)
                std::cout << DB::Instance().enum2str(elem.first) << elem.second << std::endl;
        }
        break;
    case '3':
        for (const auto& elem : DB::Instance().event)
        {
            if (elem.first == DB::EventType::createClientAccount)
                std::cout << DB::Instance().enum2str(elem.first) << elem.second << std::endl;
        }
        break;
    case '4':
        for (const auto& elem : DB::Instance().event)
        {
            if (elem.first == DB::EventType::addWorker)
                std::cout << DB::Instance().enum2str(elem.first) << elem.second << std::endl;
        }
        break;
    case '5':
        for (const auto& elem : DB::Instance().event)
        {
            if (elem.first == DB::EventType::complaintLodged)
                std::cout << DB::Instance().enum2str(elem.first) << elem.second << std::endl;
        }
        break;
    case '6':
        for (const auto& elem : DB::Instance().event)
        {
            if (elem.first == DB::EventType::considerationOfComplaint)
                std::cout << DB::Instance().enum2str(elem.first) << elem.second << std::endl;
        }
        break;
    default:
        std::cout << "Nieznana opcja! Powrot" << std::endl << std::endl;
    }
}



