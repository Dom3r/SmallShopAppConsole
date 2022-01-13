/**
* @file Manager.h
* @brief plik z klasa Menadzera sklepu dziedziczacej po Pracowniku
*/
#pragma once
#include "Worker.h"
class Manager : public Worker
{
public:
    /**
    * Konstruktor tworzacy Managera jako przypadek pracownika z predefiniowanym loginem i haslem
    */
    Manager();
    /**
    * Nadpisana metoda run 
    */
    void run() override;

private:
    /**
    * Metoda zezwalajaca na pokazanie listy istniejacych kont pracownikow 
    */
    void showWorkers();
    /**
    * Metoda sluzaca do wyplacania pensji pracownikom 
    */
    void paySalary();
    /**
    * Metoda pozwalajaca dodac konto nowo zatrudnionego pracownika
    */
    void addWorker();
    /**
    * Metoda zezwalajaca na pokazanie aktualnego przychodu 
    */
    void showIncome();
};
