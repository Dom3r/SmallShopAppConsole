/**
* @file Person.h
* @brief plik z klasa abstrakcyjna Person bedaca baza dla innych klas
*/
#pragma once
#include <iostream>

class Person
{
public:
    friend class Application;
    /**
    * Czysto wirtualna metoda run 
    */
    virtual void run() = 0;
protected:
    std::string login;
    std::string password;
    /**
    * Metoda do zmiany hasla 
    */
    void changePassword()
    {
        std::cout << "Podaj nowe haslo" << std::endl;
        std::cin >> password;
    }
  
};