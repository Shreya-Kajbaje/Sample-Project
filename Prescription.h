#pragma once
#include<iostream>
#include<string>
#include<set>
using namespace std;


class Prescription{
    int prescription_id;
    string prescription_details;
    string prescription_date;

public:
Prescription();
Prescription(int, string, string);
void view_prescription();

string getPrescription_details();
string getPrescription_date();
int getPrescription_id();

};