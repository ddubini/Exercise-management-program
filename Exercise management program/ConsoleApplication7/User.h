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
    string name;      //����ڸ�
    string fileName;     // ����� �ؽ�Ʈ ���� �̸�
    fstream user_info;   //������� txt����
    int age;            // ����
    int gender;         // ����
    int weight;         //������
    int height;         //Ű
    int basic_metabolic;//���ʴ�緮 (�Ĵ� ������ ����)
    int cnt;            // day
    int cal;            // calorie

public:
    User(Routine&, string, int, int, int, int);
    string getName();
    int myRMR(int age, int gender, int height, int weight);     // ���ʴ�緮 ���ϱ� ����, ����(0,1), Ű, ������
    void putInfo();      //���Ͽ� "����"�� �⺻���� �Է�(private�� ������, BMI������ ����ؼ�) - ��¥�� ��� ��¥�� ���ó�¥
    void putRoutine(vector<WorkOut>*, Routine&);   //(��������) ��ƾ�� ���Ͽ� �Է� ��ƾ�� ��ƾ Ŭ�������� ���´�.
    void putTodayWorkOut(WorkOutManager&, Routine&); //������ ��� ���Ͽ� �Է�. ����Ʈ�� ��� ���� ����� ��ƾ�� ���ؼ� ����(����ڿ��� ���� �ߴ��� �����. ���ǵ�, Ƚ�� ���� üũ�� �����ؼ� Į�θ����)(� ��ƾ�� ���Ͽ� ���� ��� �Է¹޾ƾ���)
    void putTodayFlow(FlowManager&);   //���� �� �ִϸ� �÷ο츦 ���, MakeFlow�� ���� ���� Ȯ�ι��� �� �Է�
    void getMyWorkOut();   //Ư�� ��¥ Ȥ�� ������ ������ ������ �����´�.
    void calCalorie(WorkOutManager&, Routine&, FlowManager&); //Ư�� ��¥�� Į�θ� �Ҹ�or������ ������ Į�θ� �Ҹ�
    void putDietMenu(dietMenu&);      //���� �Ĵ��� �Է��Ѵ�.(������ ��ħ/����/����)
    void getByWeek();       // ������ ���
    void getByDate();       // ���ں� ���
    void recommMenu(dietMenu&);
};

#endif //EXERCISE_USER_H