/**
* @file Worker.h
* @brief plik z klasa Pracownika sklepu dziedziczacej po Person
*/
#pragma once
#include<iostream>
#include "Person.h"
#include "Product.h"

class Worker :public Person
{
public:
    /**
    * Konstruktor pracownika przyjmujacy login, haslo i stanowisko jako stringi oraz pensje jako integer
    */
    Worker(std::string l, std::string p, std::string pos, int s);
    void run() override;
    friend std::ostream& operator<< (std::ostream& out, const Worker& x);
    friend class Manager;

protected:
    /**
    * Metoda zezwalajaca na pokazanie istniejacych kont klientow 
    */
    void showClients();
    std::string position;
    int salary;

private:
    /**
    * Metoda zezwalajaca na przeczytanie skargi zloznej przez klienta 
    */
    void readComplaint();
    /**
    * Metoda umozliwiajaca dodanie w aplikacji konta dla nowego klienta
    */
    void addClient();
    /**
    * Metoda pozwalajaca dodac produkt do dostepnych produktow w sklepie
    */
    void addProduct();
    /**
    * Metoda ukazujaca jakie produkty aktualnie sa w sklepie
    */
    void showAllProduct();
};