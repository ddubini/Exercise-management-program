#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <sstream>
#include <istream>
#include <fstream>
#include <string>
#include "AnimalFlow.h"
#include "WeightTraining.h"
#include "Diet.h"
#include "User.h"

using namespace std;
User::User(Routine& rt, string u_name, int u_age, int u_gender, int u_weight, int u_height) {
    this->name = u_name;
    this->weight = u_weight;
    this->height = u_height;
	this->cal = 0;

	this->basic_metabolic = this->myRMR(u_age, u_gender, u_height, u_weight);

    // ���� �̸� 
    string u_fileName = u_name;
    u_fileName.append(".txt");
    this->fileName = u_fileName;

    ifstream user_info(fileName);
    if (!user_info.is_open()) {
        ofstream user_info(fileName, ios_base :: out);
		rt.setRoutine(name);
		this->putRoutine(rt.getDay(), rt);
    }
    string buf;
    int tcnt = 0;

    // day ���
    while (getline(user_info, buf)) {
        if (buf.find(" - ") != string::npos) tcnt++;
        buf.clear();
    }
    cnt = tcnt;

	this->putInfo();
}

string User::getName(){
	return name;
}


int User::myRMR(int age, int gender, int height, int weight) {
	return gender ? 655.1 + (9.56 * weight) + (1.85 * height) - (4.68 * age) : 66.47 + (13.75 * weight) + (5 * height) - (6.76 * age);
}

void User::putInfo() {	// �⺻ ���� �Է�(��¥, Ű, ������, bmi, ���ʴ�緮)
	struct tm* today;
	time_t t;
	t = time(NULL);
	today = localtime(&t);

	double bmi = double(this->weight) / (double(this->height) * double(this->height) * 0.0001);

	user_info.open(fileName, ios::app);
	if (user_info.is_open()) {
		user_info << today->tm_year + 1900 << " - " << today->tm_mon + 1 << " - " << today->tm_mday << endl << endl;
		user_info << "{������}" << endl;
		user_info << "Ű : " << this->height << endl;
		user_info << "������ : " << this->weight << endl;
		user_info << "BMI : " << bmi << endl;
		user_info << "���ʴ�緮 : " << this->basic_metabolic << endl << endl;
	}
	cout << "\n++++++++++++++ Complete Writing Information ++++++++++++++\n" << endl;
};

//void putTodayWorkOut(); //������ ��� ���Ͽ� �Է�. ����Ʈ�� ��� ���� ����� ��ƾ�� ���ؼ� ����
// * ����ڿ��� ���� �ߴ��� �����. Ƚ�� ���� üũ�� �����ؼ� Į�θ����)
// * � ��ƾ�� ���Ͽ� ���� ��� �Է¹޾ƾ���)
void User::putTodayWorkOut(WorkOutManager& mng, Routine&rt){
    vector<WorkOut>* dayWorkout = rt.getDay();
    vector<WorkOut>::iterator iter;
    int r, s, kg;
	bool opt = 0;

	cout << "Set New Routine? ( Y : 1 / N : 0 )";
	cout << "> "; cin >> opt;
	/*
    // � ��ƾ�� ���Ͽ� ���� ��� �Է¹޾ƾ���
    if (dayWorkout.size()== 0) {
		cout << rt.getMaxDay() << endl;

        rt.setRoutine();
        putRoutine(dayWorkout, rt);
    }
	*/

	// �� ��ƾ�� �Է��ϴ� ���
	if (opt == 1 ) {
		rt.setRoutine(name);
		this->putRoutine(rt.getDay(), rt);

		ofstream user_output(fileName, ios::app);
		if (!user_output.is_open())
			cout << "[User]Unable to open file" << endl;
		// ���Ը� ��� �� txt���Ͽ� �Է�
		int dayInfo = cnt / rt.getMaxDay();
		user_output << "{�}" << endl;
		for (iter = dayWorkout[dayInfo].begin(); iter != dayWorkout[dayInfo].end(); iter++) {
			cout << iter->getName() << "(" << iter->getSet() << "x" << iter->getRep() << ")\nRepetition : ";
			cin >> r;
			cout << "Set : ";
			cin >> s;
			cout << "Kg : ";
			cin >> kg;;
			user_output << iter->getName() << "(" << s << "x" << r << ") : " << kg << "kg" << endl;
			cal += 7 * ((s - 1) + 0.083 * r * s); //(��Ʈ��-1) x 1�� + (Ƚ�� x 5��) x ��Ʈ��
		}
	}
	// ������ ��ƾ�� ����ϴ� ��� (��ƾ ������ֱ�)
	else if (opt == 0) {
		string day = "";

		while (1) {
			cout << "Select Day : "; cin >> day;
			break;
		}
		string line;
		string str;
		string routineF = this->name + "_��ƾ.txt";
		ifstream user_routine(routineF, ios::in);
		while (getline(user_routine, line)) {
			istringstream ss(line);
			cout << line << endl; 
			if (line.substr(0, 4) == "Day" + day) {
				str = line;
			}
		}
		///////////////// ��ƾ ���Ͽ��� �������� /////////////
		vector<string> dayRoutine;
		dayRoutine.clear();
		istringstream ss(str);
		string word;
		while (getline(ss, word, ' ')) {
			dayRoutine.push_back(word);
		}
		//���Ͽ� �Է�
		ofstream user_output(fileName, ios::app);
		if (!user_output.is_open())
			cout << "[User]Unable to open file" << endl;
		// ���Ը� ��� �� txt���Ͽ� �Է�
		user_output << "{�}" << endl;
		for (int i = 2; i < dayRoutine.size(); i++) {
			cout << dayRoutine[i] << "\nRepetition : ";
			cin >> r;
			cout << "Set : ";
			cin >> s;
			cout << "Kg : ";
			cin >> kg;
			user_output << dayRoutine[i] << "(" << s << "x" << r << ") : " << kg << "kg" << endl;
			cal += 7 * ((s - 1) + 0.083 * r * s); //(��Ʈ��-1) x 1�� + (Ƚ�� x 5��) x ��Ʈ��
		}
		user_routine.close();
		user_output.close();
	}
	else {
		cout << "Input Error";
		return;
	}
};

/*
void putTodayFlow();   //���� �� �ִϸ� �÷ο츦 ���, MakeFlow�� ���� ���� Ȯ�ι��� �� �Է�
�׷��� user���Ͽ� �ִ� �÷ο�� �� ���۵��� ���ӵȰ��� �������� ���Դϴ�.
������� MakeFlow�� num�� 20�� �޾Ƽ� 20���� ������ ����� �ϳ��� �÷ο찡 �Ǵ°ſ���.
�װ� vector<AnimalFlow> flow;�� ����ǰ� �� �����̰��.
*/
void User::putTodayFlow(FlowManager &fm) {
    vector<AnimalFlow> dayFlow = fm.getFlow();
	int num, dif;
        
	cout << "  Set the number of motions";
    cout << "  > "; cin >> num;
    cout << "  Set the difficulty ( NoHard : 0, default : 1, hard : 2, harder : 3)"; //NoHard�� ���̵� '��' x
    cout << "  > "; cin >> dif;
    fm.MakeFlow(num, dif);
    dayFlow = fm.getFlow();

	// �ִϸ� �÷ο츦 ���
	cout << "\n[�ִϸ� �÷ο�] " << endl;
	for (int i = 0; i < dayFlow.size(); i++) {      //���۵��� 3���� ���ٿ� ���
		cout.setf(ios::left);
		cout << "->  " << setw(30) << dayFlow.at(i).getName();
		if (((i + 1) % 3) == 0)
			cout << endl;
	}

    ofstream user_output(fileName, ios::app);
    if (!user_output.is_open())
        cout << "[User]Unable to open file" << endl;

    // �ִϸ� �÷ο츦 �Է�
    user_output << "(�ִϸ� �÷ο�) : ";
    for (int i = 0; i < dayFlow.size(); i++) {
        if (i == dayFlow.size() - 1) user_output << dayFlow.at(i).getName() << "\n"; // ���������� - ���� �Է�
        else user_output << dayFlow.at(i).getName() << " - ";
    }
	user_output << endl;
	cout << "\n++++++++++++++ Complete Writing Animal Flow ++++++++++++++" << endl;
}


//void Calculate_Calorie(); //Ư�� ��¥�� Į�θ� �Ҹ�or������ ������ Į�θ� �Ҹ�
void User::calCalorie(WorkOutManager& mng, Routine& rt, FlowManager& fm) {
    ofstream user_output(fileName, ios::app);
	user_output << "�� Į�θ� �Ҹ� : " << cal << endl << endl;
	cout << "\n++++++++++++++ Complete Writing Calorie Consumption ++++++++++++++\n" << endl;
}

void User::putRoutine(vector<WorkOut>* weekr, Routine& rt) {
	string routineF = this->name + "_��ƾ.txt";
	ofstream user_info(routineF, ios::out);
	vector<WorkOut>::iterator it;
	if (rt.getMaxDay()) {
		for (int i = 0; i < rt.getMaxDay(); i++) {
			user_info << "Day" << i + 1 << " : ";
			for (it = weekr[i].begin(); it != weekr[i].end(); it++) {
				user_info << it->getName() << "(" << it->getSet() << "X" << it->getRep() << ")" << " ";
			}
			user_info << "\n";
		}
	}
	user_info << endl;
	user_info.close();
	cout << "\n++++++++++++++ Complete Writing Routine ++++++++++++++\n" << endl;
	return;
};


// ���� ��������
void User::getMyWorkOut() {
	int opt = 0;
	while (1) {
		cout << "-------------- Search --------------" << endl;
		cout << "------------ 1. By date ------------" << endl;
		cout << "------------ 2. By week ------------" << endl;
		cout << "> ";
		cin >> opt;
		switch (opt)
		{
		case 1:
			getByDate();
			return;
		case 2:
			getByWeek();
			return;
		default:
			cout << "Input Error";
			continue;
		}
	}
};

// ��¥�� ����
void User::getByDate() {
	string temp[3];
	cout << "Year? "; cin >> temp[0];
	cout << "Month? "; cin >> temp[1];
	cout << "Date? "; cin >> temp[2];
	string startKey = temp[0] + " - " + temp[1] + " - " + temp[2];

	int year = atoi(temp[0].c_str());
	string endKey;
	// 12�� 31��
	if (atoi(temp[1].c_str()) == 12 && atoi(temp[2].c_str()) == 31) {
		endKey = to_string(atoi(temp[0].c_str()) + 1) + " - 1 - 1";
	}
	// x�� 31��
	else if (atoi(temp[2].c_str()) == 31) {
		endKey = temp[0] + " - " + to_string(atoi(temp[1].c_str()) + 1) + " - 1";
	}
	// 2, 4, 6, 8�� 30��
	else if (atoi(temp[1].c_str()) <= 8 && atoi(temp[1].c_str()) % 2 == 0 && atoi(temp[2].c_str()) == 30) {
		endKey = temp[0] + " - " + to_string(atoi(temp[1].c_str()) + 1) + " - 1";
	}
	// 9, 11�� 30��
	else if (atoi(temp[1].c_str()) >= 9 && atoi(temp[1].c_str()) % 2 == 1 && atoi(temp[2].c_str()) == 30) {
		endKey = temp[0] + " - " + to_string(atoi(temp[1].c_str()) + 1) + " - 1";
	}
	else {
		endKey = temp[0] + " - " + temp[1] + " - " + to_string(atoi(temp[2].c_str()) + 1);
	}
	string line;
	bool flag = false;

	ifstream user_info(fileName);
	if (user_info.is_open()) {
		while (getline(user_info, line)) {
			if (line.find(startKey) == 0) { flag = true; }
			else if (line.find(endKey) == 0) { flag = false; break; }
			if (flag) { cout << line << endl; }
		}
	}
	user_info.close();
};
// ������ ����
void User::getByWeek() {
	string temp[6];
	cout << "Start Year? "; cin >> temp[0];
	cout << "Start Month? "; cin >> temp[1];
	cout << "Start Date? "; cin >> temp[2];
	cout << "End Year? "; cin >> temp[3];
	cout << "End Month? "; cin >> temp[4];
	cout << "End Date? "; cin >> temp[5];

	string startKey = temp[0] + " - " + temp[1] + " - " + temp[2];
	string endKey = temp[3] + " - " + temp[4] + " - " + temp[5];
	string line;
	bool flag = false;

	ifstream user_info(fileName);
	if (user_info.is_open()) {
		while (getline(user_info, line)) {
			if (line.find(startKey) == 0) { flag = true; }
			else if (line.find(endKey) == 0) { flag = false; break; }
			if (flag) { cout << line << endl; }
		}
	}
	user_info.close();
};

void User::putDietMenu(dietMenu& Menu) {	//���� �Ĵ��� �Է��Ѵ�.(������ ��ħ/����/����)
	// �� �Ĵ� �Է�(�������� '/')
	
	string breakfast = "";
	string lunch = "";
	string dinner = "";
		
	cout << "Breakfast Menu : ";
	cin >> breakfast;
	cout << "Lunch Menu : ";
	cin >> lunch;
	cout << "Dinner Menu : ";
	cin >> dinner;

	ofstream user_info(fileName, ios::app);
	if (!user_info.is_open())
		cout << "[User]Unable to open file" << endl;
	else {
		user_info << "{�Ĵ�}" << endl;
		user_info << "��ħ : " << breakfast << " (" << Menu.cal_calorie(breakfast) << "kcal)" << " (" << Menu.cal_protein(breakfast) << "g)" << endl;
		user_info << "���� : " << lunch << " (" << Menu.cal_calorie(lunch) << "kcal)" << " (" << Menu.cal_protein(lunch) << "g)" << endl;
		user_info << "���� : " << dinner << " (" << Menu.cal_calorie(dinner) << "kcal)" << " (" << Menu.cal_protein(dinner) << "g)" << endl;
		user_info << "�� ���� �ܹ����� : " << Menu.cal_protein(breakfast) + Menu.cal_protein(lunch) + Menu.cal_protein(dinner) << "g" << endl << endl;
	}
	user_info.close();
};

/*
// ��õ �ޱ�
// RMR = ���ʴ�緮, hard = �����(0~4)
// time = ��õ�ð��� ��,��,��,��ü(1~4)
// purpose ���� = true, ���� = false
*/
void User::recommMenu(dietMenu& Menu) {
	int hard = 0;
	int time = 0;
	bool purpose = 0;

	cout << "intensity ( 1 ~ 4 ) : "; cin >> hard;
	cout << "Time ( breakfast : 1 / lunch : 2 / dinner : 3 / ShowAll : 4 ) : "; cin >> time;
	cout << "What's your purpose? ( gain weight : 1 / lose weight : 2 ) : "; cin >> purpose;
	cin.clear();
	cout << Menu.recommend(this->basic_metabolic, hard, purpose, time);
};