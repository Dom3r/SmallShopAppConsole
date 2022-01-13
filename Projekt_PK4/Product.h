/**
* @file Product.h
* @brief plik z struktura Produkt stanowiaca reprezentacje produktow ktore sa w sklepie
*/
#pragma once
#include<iostream>
struct Product
{
    /**
    * 3 pola odpowiednio name - nazwa produktu
    * price - cena produktu
    * quantity - ilosc danego produktu w magazynie
    */
    std::string name;
    float price;
    int quantity;
    /**
    * Konstruktor przyjmujacy powyzsze pola jako parametry produktu
    */
    Product(const std::string& name_, int quantity_, float price_)
        :name(name_), quantity(quantity_) {
        if (price_ <= 0) price = 1;
        else price = price_;
    }

    friend std::ostream& operator<<(std::ostream& out, const Product& x);
};