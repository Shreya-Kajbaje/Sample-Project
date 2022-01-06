#pragma once
#include<iostream>
#include<string>
using namespace std;

class Department{
int dept_id;
string dept_name;


public:
Department();
Department(int ,string);

void showDepartment();

int getDepartment_id();
string getDepartment_name();


};