#pragma once

#ifndef EXERCISE_USER_H
#define EXERCISE_USER_H

#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "WeightTraining.h"
#include "Diet.h"
#include "AnimalFlow.h"



using namespace std;
class User {
private:
    string name;      //사용자명
    string fileName;     // 사용자 텍스트 파일 이름
    fstream user_info;   //사용자의 txt파일
    int age;            // 나이
    int gender;         // 성별
    int weight;         //몸무게
    int height;         //키
    int basic_metabolic;//기초대사량 (식단 조절에 참고)
    int cnt;            // day
    int cal;            // calorie

public:
    User(Routine&, string, int, int, int, int);
    string getName();
    int myRMR(int age, int gender, int height, int weight);     // 기초대사량 구하기 나이, 남녀(0,1), 키, 몸무게
    void putInfo();      //파일에 "오늘"의 기본정보 입력(private의 정보들, BMI같은건 계산해서) - 날짜별 기록 날짜는 오늘날짜
    void putRoutine(vector<WorkOut>*, Routine&);   //(일주일의) 루틴을 파일에 입력 루틴은 루틴 클래스에서 얻어온다.
    void putTodayWorkOut(WorkOutManager&, Routine&); //오늘의 운동을 파일에 입력. 웨이트의 경우 파일 상단의 루틴에 의해서 결정(사용자에게 오늘 했는지 물어본다. 성실도, 횟수 등을 체크해 감안해서 칼로리계산)(운동 루틴이 파일에 없을 경우 입력받아야함)
    void putTodayFlow(FlowManager&);   //오늘 한 애니멀 플로우를 기록, MakeFlow로 만든 것을 확인받은 뒤 입력
    void getMyWorkOut();   //특정 날짜 혹은 일주일 간격의 운동기록을 가져온다.
    void calCalorie(WorkOutManager&, Routine&, FlowManager&); //특정 날짜의 칼로리 소모량or일주일 간격의 칼로리 소모량
    void putDietMenu(dietMenu&);      //나의 식단을 입력한다.(오늘의 아침/점심/저녁)
    void getByWeek();       // 주차별 기록
    void getByDate();       // 일자별 기록
    void recommMenu(dietMenu&);
};

#endif //EXERCISE_USER_H