#pragma once

#include<iostream>
#include<string>
#include<set>
#include "Patient.h"

using namespace std;


class Payment {
    int payment_id;
    string payment_type;
    int payment_amount;
    string doctor_name;
    string payment_date;

public:
    Payment();
    Payment(int id, string n, string payamt,string docname,string paydate);
    void showPaymentDetails();
    void showPaymentDetails(Patient*);
};

