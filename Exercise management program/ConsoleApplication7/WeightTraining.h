#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include "AnimalFlow.h"
using namespace std;

class WorkOut {
private:
	string category;				//Ÿ�� ������ ū ī�װ� (����, ��, ��ü, ��, ���, ����)  string���� 10
	string name;					//���� �̸�
	string link;					// ����(����� ��ũ - 00:00(�ð�))
	int set;
	int rep;
public:
	WorkOut(string t_cat, string t_name, string t_link);
	void SetRep(int m, int n);
	string getCategory();
	string getLink();
	string getName();
	int getSet();
	int getRep();
	void ShowInfo() const;
};

class WorkOutManager
{
private:
	vector<WorkOut> chest;
	vector<WorkOut> abs;
	vector<WorkOut> arms;
	vector<WorkOut> lower_body;
	vector<WorkOut> back;
	vector<WorkOut> shoulder;
public:
	WorkOutManager();
	void ShowTop() const;
	void ShowAbsWO();
	void ShowArmsWO();
	void ShowBackWO();
	void ShowChestWO();
	void ShowLowerBodyWO();
	void ShowShoulderWO();
	void ShowAllWorkOut();
	void SearchByName();
	void SearchByCategory();
	void SearchWO();
	WorkOut SearchAndReturn(string name_str);
};

class Routine
{
private:
	/*
	vector<WorkOut> abs;
	vector<WorkOut> arms;
	vector<WorkOut> back;
	vector<WorkOut> chest;
	vector<WorkOut> lower_body;
	vector<WorkOut> shoulder;
	*/
	vector<WorkOut> day[7];
	int max_day;
public:
	Routine(WorkOutManager& wo_man);
	WorkOutManager mngr;
	void SplitDay();
	void AddWorkOut(int day_idx);
	void setRoutine(string file_name);
	void showRoutine();
	int getMaxDay();
	vector<WorkOut>* getDay();
};
