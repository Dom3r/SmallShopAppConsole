/**
* @file Client.h
* @brief plik z klasa Klient dziedziczacej po Person
*/
#pragma once
#include<iostream>
#include "Person.h"
class Client : public Person
{
public:
    /**
    * Konstruktor przyjmujacy login i haslo jako stringi
    */
    Client(std::string, std::string);
    /**
    * Nadpisana metoda run 
    */
    void run() override;
    friend std::ostream& operator<< (std::ostream& out, const Client& x);
private:
    /**
    * Metoda zezwalajaca na wyswietlenie listy oferowanych produktow i dokonanie zakupu
    */
    void showShop();
    /**
    * Metoda pozwalajaca na zlozenie skargi przez klienta
    */
    void addComplaints();
    /**
    * Pole reprezentujace ilosc zlozonych zamowien przez danego klienta
    */
    int numOfOrders;
};