#include<iostream>
#include"Accountant.h"
#include"Payment.h"
#include "sqlite3.h"
#include"Patient.h"
#include <sstream>


using namespace std;

extern sqlite3* db;

void Payment::showPaymentDetails()
{
    char* zErrMsg = 0;
    const char* sql;
    int rc;
    const char* data = "Callback function called";
    int callback(void* data, int argc, char** argv, char** azColName);

    stringstream ss, ss2;
    string query, query2;

    sqlite3_stmt* stmt;

    string patientname;

    cout << "\nEnter Patient Name for Payment Details :" << endl;
    cin >> patientname;

    std::stringstream sql2;
    sql2 << "select * from PAYMENT where Patient_name ='" + patientname + "';";
    query = sql2.str();
    sql = query.c_str();
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        //fprintf("error: ", sqlite3_errmsg(sqlite3->db));
    }

    cout << "Payment History of Patient :" << patientname << endl;
    cout << "PaymentID\t" << " " << "AccountantName\t" << " " << "PatientName\t" << " " << "DoctorName\t" << " " << "PaymentType\t" << " " << "PaymentAmount\t" << " " << "PaymentDate\t" << endl;

    int flag = 0;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        int paymentid = sqlite3_column_int(stmt, 0);
        float paymentamount = sqlite3_column_double(stmt, 5);
        string patientname = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        string accountantname = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        string doctorname = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        string paymenttype = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        string paymentdate = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));

            cout << paymentid << "\t\t" << accountantname << "\t\t" << patientname << "\t\t" << doctorname << "\t\t" << paymenttype << "\t\t" << paymentamount << "\t\t" << paymentdate << endl;
            cout << "\n";
            flag=1;
    }
    if(flag==0)
    cout << "No Payment History Found!!" << endl;
    
    sqlite3_finalize(stmt);

    return;
}

 void Payment::showPaymentDetails(Patient* P)
{
    char* zErrMsg = 0;
    const char* sql;
    int rc;
    const char* data = "Callback function called";
    int callback(void* data, int argc, char** argv, char** azColName);

    stringstream ss, ss2;
    string query, query2;

    sqlite3_stmt* stmt;

    string patientname;

    patientname = P->getPatient_name();

    std::stringstream sql2;
    sql2 << "select * from PAYMENT where Patient_name ='" + patientname + "';";
    query = sql2.str();
    sql = query.c_str();
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        // fprintf("error: ", sqlite3_errmsg(sqlite3->db));
    }
    int flag = 0;
    cout<<"payment details of : "<<patientname;
    cout << "PaymentID\t" << " " << "AccountantName\t" << " " << "PatientName\t" << " " << "DoctorName\t" << " " << "PaymentType\t" << " " << "PaymentAmount\t" << " " << "PaymentDate\t" << endl;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        int paymentid = sqlite3_column_int(stmt, 0);
        float paymentamount = sqlite3_column_double(stmt, 5);
        string patientname = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        string accountantname = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        string doctorname = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        string paymenttype = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        string paymentdate = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        

        cout << paymentid << " " << accountantname << " " << patientname << " " << doctorname << " " << paymenttype << " " << paymentamount << " " << paymentdate << endl;
        cout << "\n";
        flag = 1;


    }
    if (flag == 0)
        cout << "No Payment History Found!!" << endl;

    sqlite3_finalize(stmt);

    //cout << "No Payment Details Found!!"<<endl;
    return;
}