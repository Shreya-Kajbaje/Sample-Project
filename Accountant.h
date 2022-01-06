#pragma once

#include<iostream>
#include<string>
#include<set>
using namespace std;


class Accountant {
    int accountant_id;
    string accountant_name;
    string password;

public:
    Accountant();
    Accountant(int id, string n, string p) {
        this->accountant_id = id;
        this->accountant_name = n;
        this->password = p;
    }
    void viewPaymentofAllPatients();
    void createPaymentDetails();
};