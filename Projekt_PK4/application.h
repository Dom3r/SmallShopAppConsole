/**
* @file application.h
* @brief plik z glowna klasa obslugujaca caly program
*/
#pragma once
#include <iostream>
#include <fstream>
#include <string>

class Application
{
public:
    /**
    * Metoda ktora jest odlozona na stosie przez caly czas uzytkowania programu
    * Nieskonczona petla, ktora bedzie przerywana w trakcie wybierania opcji z menu
    */
    void run();

private:
    /**
    * Metoda ta pozwoli nam na zalogowanie sie na konto istniejace w aplikacji 
    */
    void login();
    /**
    * Metody wczytujace dane z plikow txt do aplikacji
    */
    void load();
    void loadWorker();
    void loadClient();
    void loadProduct();
    /**
    * Metoda pozwalajaca wyswietlic wszystkie eventy(db EvenType) jakie wydarzyly sie w aplikacji
    */
    void showEvent();

};
