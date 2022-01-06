#include "Prescription.h"



Prescription::Prescription() {}

Prescription::Prescription(int id, string details,string date) : prescription_id(id),prescription_details(details),prescription_date(date) {}

void Prescription::view_prescription()
{
    cout<<prescription_date<<"\t"<<prescription_details<<endl;
}

string Prescription::getPrescription_details()
{
    return this->prescription_details;
}

string Prescription::getPrescription_date()
{
    return this->prescription_date;
}

int Prescription::getPrescription_id()
{
    return this->prescription_id;
}