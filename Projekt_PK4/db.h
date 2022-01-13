/**
* @file db.h
* @brief plik z klasa db sluzacej do agregacji danych aplikacji
*/
#pragma once
#include<iostream>
#include<map>
#include<list>
#include "Product.h"
#include "Client.h"
#include "Worker.h"
#include "Manager.h"
class DB
{

public:
    /**
    * Enum eventype jest wykorzystywany do pokazywania co sie w programie wydarzylo
    */
    enum class EventType
    {
        order,
        complaintLodged,
        considerationOfComplaint,
        createClientAccount,
        addWorker
    };
    /**
    * Kontenery STL w ktorych sa przechowywane dane aplikacji 
    */
    std::list<Product>shop;
    std::map<std::string, std::unique_ptr<Client>> clients;
    std::map<std::string, std::unique_ptr<Worker>> workers;
    Manager manager;
    std::multimap<std::string, std::string>complaints;
    std::multimap<EventType, std::string>event;
    
    /**
    * Wzorzec projektowy Singleton gwarantuje istnienie tylko jednego obiektu danego rodzaju,
    * udostepnia pojedyczny punkt dostepowy do takiego obiektu z dowolnego miejsca w programie
    */
    static DB& Instance()
    {
        static DB instance;
        return instance;
    }
    DB(DB const&) = delete;
    DB& operator=(DB const&) = delete;
    DB(DB&&) = delete;
    DB& operator=(DB&&) = delete;


    /**
    * Metoda wypisujaca wszystkie produkty z sklepu 
    */
    void printAllProduct();
    /**
    * Metoda przeznaczona do kupowania produktow
    * @param iterator w liscie z produktami
    */
    void buy(std::list<Product>::iterator);

    std::string enum2str(EventType);
    /**
    * Domyslny przychod sklepu, oczywiscie zmieniajacy sie odpowiednio po sprzedazy, wyplacaniu pensji, wyslaniu rekompensaty
    */
    int income;
private:
    DB() : income(100000) {};

};