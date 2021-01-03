#ifndef DIET_H
#define DIET_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;
class Food {
private:
	string name;			// 음식이름
	float calorie;			// 음식 칼로리(kcal)
	float protein;			// 음식 단백질
	int gram;				// 음식 량
	Food* next;				// list용
public:
	Food(string, float, float, int);
	Food* getnext() { return next; }
	void setnext(Food* in) { next = in; }
	string getname() { return name; }
	float getcalorie() { return calorie; }
	float getprotein() { return protein; }
	int getgram() { return gram; }
};

class dietMenu {
private:
	// food.txt 파일 이름 생성자에서 설정
	string foodf, cfoodf, pfoodf;
	Food* foodl;		// 일반 음식 list
	Food* cfoodl;		// 일반 사이드 list
	Food* pfoodl;		// 일반 단백질 list
	int foodT, cfoodT, pfoodT;
	// list에 음식 넣기
	void push(Food*, Food*);
	// 음식 이름에 따라 Food 찾기
	Food* find(string name);
public:
	dietMenu();

	/*
	// 추천 받기
	// RMR = 기초대사량, hard = 운동강도(0~4)
	// time = 추천시간대 아,점,저,전체(1~4)
	// purpose 증량 = true, 감량 = false
	*/
	string recommend(int RMR, int hard, bool purpose, int time = 4);

	// 사이드 음식에서 맞는 칼로리 음식 가져오기 없으면 null
	Food* findcal(float min, float max);

	// 단백질 사이드에서 맞는 단백질 가져오기 없으면 null
	Food* findprot(float min, float max);

	// "음식/음식/음식" 의 스트링에서 칼로리,단백질 계산 
	int cal_calorie(string meals); // 총 칼로리 계산
	float cal_protein(string meals);	// 총 단백질 계산
};
#endif