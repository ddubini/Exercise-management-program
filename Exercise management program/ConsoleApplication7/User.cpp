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

    // 파일 이름 
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

    // day 계산
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

void User::putInfo() {	// 기본 정보 입력(날짜, 키, 몸무게, bmi, 기초대사량)
	struct tm* today;
	time_t t;
	t = time(NULL);
	today = localtime(&t);

	double bmi = double(this->weight) / (double(this->height) * double(this->height) * 0.0001);

	user_info.open(fileName, ios::app);
	if (user_info.is_open()) {
		user_info << today->tm_year + 1900 << " - " << today->tm_mon + 1 << " - " << today->tm_mday << endl << endl;
		user_info << "{몸상태}" << endl;
		user_info << "키 : " << this->height << endl;
		user_info << "몸무게 : " << this->weight << endl;
		user_info << "BMI : " << bmi << endl;
		user_info << "기초대사량 : " << this->basic_metabolic << endl << endl;
	}
	cout << "\n++++++++++++++ Complete Writing Information ++++++++++++++\n" << endl;
};

//void putTodayWorkOut(); //오늘의 운동을 파일에 입력. 웨이트의 경우 파일 상단의 루틴에 의해서 결정
// * 사용자에게 오늘 했는지 물어본다. 횟수 등을 체크해 감안해서 칼로리계산)
// * 운동 루틴이 파일에 없을 경우 입력받아야함)
void User::putTodayWorkOut(WorkOutManager& mng, Routine&rt){
    vector<WorkOut>* dayWorkout = rt.getDay();
    vector<WorkOut>::iterator iter;
    int r, s, kg;
	bool opt = 0;

	cout << "Set New Routine? ( Y : 1 / N : 0 )";
	cout << "> "; cin >> opt;
	/*
    // 운동 루틴이 파일에 없을 경우 입력받아야함
    if (dayWorkout.size()== 0) {
		cout << rt.getMaxDay() << endl;

        rt.setRoutine();
        putRoutine(dayWorkout, rt);
    }
	*/

	// 새 루틴을 입력하는 경우
	if (opt == 1 ) {
		rt.setRoutine(name);
		this->putRoutine(rt.getDay(), rt);

		ofstream user_output(fileName, ios::app);
		if (!user_output.is_open())
			cout << "[User]Unable to open file" << endl;
		// 무게를 물어본 후 txt파일에 입력
		int dayInfo = cnt / rt.getMaxDay();
		user_output << "{운동}" << endl;
		for (iter = dayWorkout[dayInfo].begin(); iter != dayWorkout[dayInfo].end(); iter++) {
			cout << iter->getName() << "(" << iter->getSet() << "x" << iter->getRep() << ")\nRepetition : ";
			cin >> r;
			cout << "Set : ";
			cin >> s;
			cout << "Kg : ";
			cin >> kg;;
			user_output << iter->getName() << "(" << s << "x" << r << ") : " << kg << "kg" << endl;
			cal += 7 * ((s - 1) + 0.083 * r * s); //(세트수-1) x 1분 + (횟수 x 5초) x 세트수
		}
	}
	// 기존의 루틴을 사용하는 경우 (루틴 출력해주기)
	else if (opt == 0) {
		string day = "";

		while (1) {
			cout << "Select Day : "; cin >> day;
			break;
		}
		string line;
		string str;
		string routineF = this->name + "_루틴.txt";
		ifstream user_routine(routineF, ios::in);
		while (getline(user_routine, line)) {
			istringstream ss(line);
			cout << line << endl; 
			if (line.substr(0, 4) == "Day" + day) {
				str = line;
			}
		}
		///////////////// 루틴 파일에서 가져오기 /////////////
		vector<string> dayRoutine;
		dayRoutine.clear();
		istringstream ss(str);
		string word;
		while (getline(ss, word, ' ')) {
			dayRoutine.push_back(word);
		}
		//파일에 입력
		ofstream user_output(fileName, ios::app);
		if (!user_output.is_open())
			cout << "[User]Unable to open file" << endl;
		// 무게를 물어본 후 txt파일에 입력
		user_output << "{운동}" << endl;
		for (int i = 2; i < dayRoutine.size(); i++) {
			cout << dayRoutine[i] << "\nRepetition : ";
			cin >> r;
			cout << "Set : ";
			cin >> s;
			cout << "Kg : ";
			cin >> kg;
			user_output << dayRoutine[i] << "(" << s << "x" << r << ") : " << kg << "kg" << endl;
			cal += 7 * ((s - 1) + 0.083 * r * s); //(세트수-1) x 1분 + (횟수 x 5초) x 세트수
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
void putTodayFlow();   //오늘 한 애니멀 플로우를 기록, MakeFlow로 만든 것을 확인받은 뒤 입력
그런데 user파일에 넣는 플로우는 이 동작들의 연속된것을 넣으려한 것입니다.
예를들면 MakeFlow로 num을 20을 받아서 20개의 동작이 연결된 하나의 플로우가 되는거에요.
그게 vector<AnimalFlow> flow;에 저장되게 할 생각이고요.
*/
void User::putTodayFlow(FlowManager &fm) {
    vector<AnimalFlow> dayFlow = fm.getFlow();
	int num, dif;
        
	cout << "  Set the number of motions";
    cout << "  > "; cin >> num;
    cout << "  Set the difficulty ( NoHard : 0, default : 1, hard : 2, harder : 3)"; //NoHard는 난이도 '상' x
    cout << "  > "; cin >> dif;
    fm.MakeFlow(num, dif);
    dayFlow = fm.getFlow();

	// 애니멀 플로우를 출력
	cout << "\n[애니멀 플로우] " << endl;
	for (int i = 0; i < dayFlow.size(); i++) {      //동작들을 3개씩 한줄에 출력
		cout.setf(ios::left);
		cout << "->  " << setw(30) << dayFlow.at(i).getName();
		if (((i + 1) % 3) == 0)
			cout << endl;
	}

    ofstream user_output(fileName, ios::app);
    if (!user_output.is_open())
        cout << "[User]Unable to open file" << endl;

    // 애니멀 플로우를 입력
    user_output << "(애니멀 플로우) : ";
    for (int i = 0; i < dayFlow.size(); i++) {
        if (i == dayFlow.size() - 1) user_output << dayFlow.at(i).getName() << "\n"; // 마지막에는 - 없이 입력
        else user_output << dayFlow.at(i).getName() << " - ";
    }
	user_output << endl;
	cout << "\n++++++++++++++ Complete Writing Animal Flow ++++++++++++++" << endl;
}


//void Calculate_Calorie(); //특정 날짜의 칼로리 소모량or일주일 간격의 칼로리 소모량
void User::calCalorie(WorkOutManager& mng, Routine& rt, FlowManager& fm) {
    ofstream user_output(fileName, ios::app);
	user_output << "총 칼로리 소모량 : " << cal << endl << endl;
	cout << "\n++++++++++++++ Complete Writing Calorie Consumption ++++++++++++++\n" << endl;
}

void User::putRoutine(vector<WorkOut>* weekr, Routine& rt) {
	string routineF = this->name + "_루틴.txt";
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


// 운동기록 가져오기
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

// 날짜별 운동기록
void User::getByDate() {
	string temp[3];
	cout << "Year? "; cin >> temp[0];
	cout << "Month? "; cin >> temp[1];
	cout << "Date? "; cin >> temp[2];
	string startKey = temp[0] + " - " + temp[1] + " - " + temp[2];

	int year = atoi(temp[0].c_str());
	string endKey;
	// 12월 31일
	if (atoi(temp[1].c_str()) == 12 && atoi(temp[2].c_str()) == 31) {
		endKey = to_string(atoi(temp[0].c_str()) + 1) + " - 1 - 1";
	}
	// x월 31일
	else if (atoi(temp[2].c_str()) == 31) {
		endKey = temp[0] + " - " + to_string(atoi(temp[1].c_str()) + 1) + " - 1";
	}
	// 2, 4, 6, 8월 30일
	else if (atoi(temp[1].c_str()) <= 8 && atoi(temp[1].c_str()) % 2 == 0 && atoi(temp[2].c_str()) == 30) {
		endKey = temp[0] + " - " + to_string(atoi(temp[1].c_str()) + 1) + " - 1";
	}
	// 9, 11월 30일
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
// 주차별 운동기록
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

void User::putDietMenu(dietMenu& Menu) {	//나의 식단을 입력한다.(오늘의 아침/점심/저녁)
	// 각 식단 입력(구분점은 '/')
	
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
		user_info << "{식단}" << endl;
		user_info << "아침 : " << breakfast << " (" << Menu.cal_calorie(breakfast) << "kcal)" << " (" << Menu.cal_protein(breakfast) << "g)" << endl;
		user_info << "점심 : " << lunch << " (" << Menu.cal_calorie(lunch) << "kcal)" << " (" << Menu.cal_protein(lunch) << "g)" << endl;
		user_info << "저녁 : " << dinner << " (" << Menu.cal_calorie(dinner) << "kcal)" << " (" << Menu.cal_protein(dinner) << "g)" << endl;
		user_info << "총 섭취 단백질량 : " << Menu.cal_protein(breakfast) + Menu.cal_protein(lunch) + Menu.cal_protein(dinner) << "g" << endl << endl;
	}
	user_info.close();
};

/*
// 추천 받기
// RMR = 기초대사량, hard = 운동강도(0~4)
// time = 추천시간대 아,점,저,전체(1~4)
// purpose 증량 = true, 감량 = false
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