#include<iostream>
#include"Accountant.h"
#include"Payment.h"
#include "sqlite3.h"
#include <sstream>
#include <thread>
#include <mutex>

using namespace std;

extern sqlite3* db;

void Accountant::viewPaymentofAllPatients()
{
    char* zErrMsg = 0;
    const char* sql;
    int rc;
    const char* data = "Callback function called";
    int callback(void* data, int argc, char** argv, char** azColName);

    stringstream ss, ss2;
    string query, query2;

    sqlite3_stmt* stmt;
    
    string paydate;

    cout << "\nEnter date for Payment Details :" << endl;
    cin >> paydate;

    std::stringstream sql2;
    sql2 << "select * from PAYMENT where Payment_date ='" + paydate + "';";
    query = sql2.str();
    sql = query.c_str();
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        // fprintf("error: ", sqlite3_errmsg(sqlite3->db));
    }

    int flag=0;
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
        cout << "No Payment Entries Found!!" << endl;

    sqlite3_finalize(stmt);

    return;
}

void Accountant::createPaymentDetails() {

    char* zErrMsg = 0;
    const char* sql;
    int rc;
    const char* data = "Callback function called";
    int callback(void* data, int argc, char** argv, char** azColName);

    stringstream ss, ss2;
    string query, query2;

    string patientname,docname,paytype,paydate,accname;
    float amt;

    cout << "\nEnter Patient Name for Payment Details :" << endl;
    getline(cin,patientname);
    getline(cin, patientname);
    cout << "\nEnter Doctor Name for Payment Details :" << endl;
    getline(cin, docname);
    cout << "\nEnter Payment Type for Payment Details :" << endl;
    getline(cin,paytype);
    cout << "\nEnter Payment Date for Payment Details :" << endl;
    getline(cin,paydate);
    cout << "\nEnter Payment Amount for Payment Details :" << endl;
    cin >> amt;

    ss << "INSERT INTO PAYMENT (Accountant_name,Patient_name,Doctor_name,Payment_type,Payment_amount,Payment_date) VALUES ('"<<accountant_name<<"','" <<patientname<<"','"<<docname<<"','"<< paytype<<"','"<<amt<<"','"<<paydate<<"');";
    
    query = ss.str();
    sql = query.c_str();

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
    {
        fprintf(stdout, "Payment Created Successfully!!\n");
    }
}