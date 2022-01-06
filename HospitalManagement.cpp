#include"sqlite3.h"
#include"HospitalMangment.h"
#include<iostream>
#include<sstream>
using namespace std;

extern sqlite3 *db;
mutex m;

void HospitalMangment ::DoctorFunction(Doctor* d1)                 //displaying all doctor functionality
{

    int ch, ch2;
    cout<<"Your name is: ";
    cout<<d1->getDoctor_name();
    string doc_name=d1->getDoctor_name();
    cout<<"\n";
    do
    {
        cout << "**************" << endl;
        cout << "\n1.Create Precription\n2.View Appointments\n3.show previous history of patient\n4.Delete Appointments\n5.Logout" << endl;
        cin >> ch;
    
        switch (ch)
        {
        case 1:
            d1->create_prescription();
            break;
        case 2:
            d1->show_Appointments(doc_name);
            break;
        case 3:
            d1->show_previous_history_of_patient();
            break;
        case 4:
            d1->delete_appointment();
            break;
        case 5:
            delete d1;
            break;
        default:
            cout << "\nInvalid Choice!!" << endl;
            break;
        }
    } while (ch != 5);

}

void HospitalMangment::PatientFunction(Patient* p1)            //displaying all patient functionality
{
    Payment* pay = NULL;

    int ch;
    do
    {
        cout << "****************" << endl;
        cout << "\n1.Create Appointment\n2.View Appointment\n3.View prescriptions \n 4.View Department wise Doctors\n5.Show Payment Details\n6.Logout" << endl;
        cin >> ch;
        switch (ch)
        {
        case 1:
            p1->create_appointment();
            break;
        case 2:
            p1->view_appointmentsDate();
            break;
        case 3:
            p1->view_prescription();
            break;
        case 4:
            
            p1->show_DepartmentWiseDoctor();
            break;
            
        case 5:
            pay->showPaymentDetails(p1);
            break;
        case 6:
            delete p1;
            break;
        default:
            cout << "Invalid Choice!!" << endl;
        }
    } while (ch != 6);


}

Doctor* HospitalMangment::doctorLogin(string username, string password)            //validating login for doctor
{

char* zErrMsg = 0;
    const char* sql;
    int rc;
    const char* data = "Callback function called";
    int callback(void* data, int argc, char** argv, char** azColName);
  
    stringstream ss, ss2;
    string query, query2;

    sqlite3_stmt* stmt;

    //ss2 << "select * from DOCTOR where Doctor_name = 'Ram' and password = 'Pass'";

    query = ss2.str();

    std::string sql2 = "select * from DOCTOR where Doctor_name ='" + username + "' and Doctor_password = '" + password + "'";
    sql = sql2.c_str();
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        // fprintf("error: ", sqlite3_errmsg(sqlite3->db));
    }

    Doctor* docObj = NULL;

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        int docid = sqlite3_column_int(stmt, 0);
        string department = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        string specialization = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        long mobileno = sqlite3_column_int64(stmt, 5);
 
        Doctor* docObj = new Doctor(docid,username,password,department,specialization,mobileno);

        sqlite3_finalize(stmt);
        cout << "\nLogin Successful!!" << endl;
        return docObj;
    }

    sqlite3_finalize(stmt);

    return docObj;

}

//Exception Handling
void HospitalMangment::PatientUserFunction()//Proving options to register as new patient or login as existing patient
{

    int ch;
   
    cout << "\n1.New User \n2.Existing User\n3.Exit" << endl;
    cin >> ch;
    Patient* p1;
       
    switch (ch)
    {
    case 1:
        registerPatient();
        break;
    case 2:
        try {
            p1 = patientLogin();
            if (p1 != NULL)
            {
                PatientFunction(p1);
                break;
            }
            throw 0;
        }
        catch(int x)
        {
            cout << "\nInvalid Credentials! Enter again!" << endl;
        }
        break;
    case 3:
        return;
    default:
        cout << "\nInvalid Choice!!" << endl;
        break;
    }

}

void HospitalMangment::registerPatient()                                   //Registering a new patient into the patient database
{

    string Name,Gender,Password;
    long mobileNo;
    int age;
    cout<<"Enter your Name: \n";
    cin>>Name;
    cout<<"Enter your Password: \n";
    cin>>Password;
    cout<<"Enter your age:\n";
    cin>>age;
    getline(cin,Gender);
    cout<<"Enter your gender(Male/Female): \n";
    cin>>Gender;
    cout<<"Enter your mobile no : \n";
    cin>>mobileNo;

    int callback(void *data, int argc, char **argv, char **azColName);

    char *zErrMsg = 0;
	int rc;
	const char *sql;
	const char *data = "Callback function called";

	stringstream ss, ss2;
	string query, query2;
    


	ss << "INSERT INTO PATIENT (Patient_password,Patient_name,Patient_age,Patient_gender,Patient_mobileno) VALUES  ('"<<Password<<"','"<< Name << "','" << age << "','" << Gender << "','" << mobileNo << "');";
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
		fprintf(stdout, "Patient Record inserted successfully\n");
	}
}

Patient* HospitalMangment::patientLogin()                         //validating existing patient login
{

    Patient* p1;
    string username, password;
    cout << "\nEnter Username" << endl;
    cin >> username;
    cout << "\nEnter Password" << endl;
    cin >> password;
    //p1 = patientLogin(username, password);

    char* zErrMsg = 0;
    const char* sql;
    int rc;
    const char* data = "Callback function called";
    int callback(void* data, int argc, char** argv, char** azColName);

    stringstream ss, ss2;
    string query, query2;

    sqlite3_stmt* stmt;

   // ss2 << "select * from PATIENT where Patient_name = 'Ram' and Patient_password = 'Pass'";

   // query = ss2.str();

    std::string sql2 = "select * from PATIENT where Patient_name ='" + username + "' and Patient_password = '" + password + "'";
    sql = sql2.c_str();
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        // fprintf("error: ", sqlite3_errmsg(sqlite3->db));
    }

    Patient* patObj = NULL;

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        int pid = sqlite3_column_int(stmt, 0);
        
        string gender = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        int age = sqlite3_column_int(stmt, 3);
        long mobileno = sqlite3_column_int64(stmt, 5);

        patObj = new Patient(pid,password,username,age,gender,mobileno);
       
        sqlite3_finalize(stmt);
        cout << "\nLogin Successful!!" << endl;
        return patObj;
    }

    sqlite3_finalize(stmt);

    return patObj;
}

Accountant* HospitalMangment::accountantLogin(string username,string password)            //validating accountant login
{

char* zErrMsg = 0;
    const char* sql;
    int rc;
    const char* data = "Callback function called";
    int callback(void* data, int argc, char** argv, char** azColName);

    stringstream ss, ss2;
    string query, query2;

    sqlite3_stmt* stmt;

    ss2 << "select * from ACCOUNTANT where Accountant_name = 'Ram' and Accountant_password = 'Pass'";

    query = ss2.str();

    std::string sql2 = "select * from ACCOUNTANT where Accountant_name ='" + username + "' and Accountant_password = '" + password + "'";
    sql = sql2.c_str();
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        // fprintf("error: ", sqlite3_errmsg(sqlite3->db));
    }

    Accountant* accObj = NULL;

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        int accid = sqlite3_column_int(stmt, 0);

        Accountant* accObj = new Accountant(accid, username, password);

        sqlite3_finalize(stmt);
        cout << "\nLogin Successful!!" << endl;
        return accObj;
    }

    sqlite3_finalize(stmt);

    return accObj;

}

void HospitalMangment::AccountantFunction(Accountant* a1)                  //displaying all accountants functionality
{
    Payment* pay = NULL;
    int ch;
    do
    {
        cout << "**************Accounant Profile*****************" << endl;
        cout << "\n1.Create Payment Details\n2.View Payment Details of All Patients\n3.View Payment Details of Particular Patient\
            \n4.Logout" << endl;
        cin >> ch;
        switch (ch)
        {
        case 1:
            //Create Payment Details();
            a1->createPaymentDetails();
            break;
        case 2:
            //View Payment Details of All Patients();
            a1->viewPaymentofAllPatients();
            break;
        case 3:
            //View Payment Details of Particular Patient();
            pay->showPaymentDetails();
            break;
        case 4:
            delete a1;
            break;
        default:
            cout << "Invalid Choice!!" << endl;
        }
    } while (ch != 4);
}

void HospitalMangment::menuScreen()                  //Displaying menu screen to hospital management system users
{
    m.lock();
    char ans; 
    int ch;

    string username, password, username1, password1;
    Doctor* d1;
    Accountant* a1;
    cout << "\n\n-------------------------- Hospital Management System ---------------------------" << endl;

    do
    {
        /* code */
        cout << "\nLogin As - \n1.Doctor\n2.Patient\n3.Accountant\n" << endl;
        cout << "Enter Your Choice :" << endl;
        cin >> ch;

        switch (ch)
        {
        case 1:
            cout << "\nEnter Username :" << endl;
            cin >> username;
            cout << "\nEnter Password :" << endl;
            cin >> password;
            d1 = doctorLogin(username,password);
            
            if (d1 != NULL)
            {
                DoctorFunction(d1);
            }
            else
            {
                cout << "\nInvalid Credentials!!" << endl;
            }
            
            break;
        
        case 2:
           PatientUserFunction();
            break;
        
        case 3:
            cout << "\nEnter Username :" << endl;
            cin >> username1;
            cout << "\nEnter Password :" << endl;
            cin >> password1;
            a1 = accountantLogin(username1, password1);

           if (a1 != NULL)
            {
                AccountantFunction(a1);
            }
            else
            {
                cout << "\nInvalid Credentials!!" << endl;
            }
            break;
        
        default:
            cout << "\nINVALID CHOICE!" << endl;
            break;
        }
        cout << "Do You Want To Login Again ? ";
        cin >> ans;


        
    } while (ans == 'y' || ans == 'Y');
       
    m.unlock();
}
