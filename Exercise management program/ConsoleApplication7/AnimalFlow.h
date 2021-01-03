#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<ctime>
#include<iomanip>
#include<stdlib.h>
using namespace std;

inline string tolowerString(string& str)   // a function that gets a string as a parameter and returns the string with lower cases
{
    int i = 0;
    string temp;
    while (str[i])
    {
        temp += tolower(str[i]);
        i++;
    }
    return temp;
}

class AnimalFlow {
private:
    string base;         //flow�� ���̽� (4���� �� �ϳ�. beast, Loaded_beast, Ape, Crab)
    string name;         //flow�̸�
    string howTo;         //� ���� ��� (��ũ, �����̸� �ð�)
    int time;            //���ۺ� ����Ƚ��(defualt ����)
    int calorie;         //���ۺ� Į�θ� �Ҹ�(��� ��Ȯ�� Į�θ� �Ҹ�� �˱� �����. �������� ������ ������ ���� �־��ְų� ���� ����)
    string difficulty;         //������ ���̵�(������� ���ÿ� ���� '��'���̵� �� �� �ְ�
public:
    AnimalFlow();
    AnimalFlow(string ibase, string iname, string ihowTo, int itime, int ical, string idif); //����� �Է¿� ���� ���ο� �÷ο� ����
    ~AnimalFlow();
    void showLink();      //howTo�� ���
    string getName();     //name�� ����   
    void setlevel(int level);  //���̵��� ���� time, calorie ����
    int getTime();         //time�� ����
    friend class FlowManager;
};
class FlowManager {
private:
    vector<AnimalFlow> flow_list;   //���Ͽ��� �о�ͼ� ����
    vector<AnimalFlow> mk_flow;      //������ �÷ο� - �ϼ��� �ϳ��� ���� �帧�̸� user�� ���� ����
    vector<AnimalFlow> next_to_beast;      //��Ʈ���̽� ������ �� �� �ִ� ����
    vector<AnimalFlow> next_to_ape;         //���� ������ �� �� �ִ� ����
    vector<AnimalFlow> next_to_loaded_beast;//�ε���Ʈ ������ �� �� �ִ� ����
    vector<AnimalFlow> next_to_crab;      //ũ�� ������ �� �� �ִ� ����
    fstream file;
public:
    FlowManager();      //FlowManager ������. ���Ͽ��� ���۵��� �ҷ��� ���Ϳ� ����
    void showMenu();               //1.���ۼ����� 2.�����߰��ϱ� 3. ����
    void putNewFlow();               //����ڰ� �߰��� AnimalFlow�� animalflow.txt�� �߰�
    void showMotion();              //���ۺ� �������ֱ�
    void MakeFlow(int num, int dif);            //���Ϳ� �÷ο���� �����鼭 ����, num�� �÷ο� ����
    int CalorieConsumption();         //�Ҹ��� Į�θ����� ����(mk_flow�� �� �Ҹ� Į�θ���)
    vector<AnimalFlow> getFlow();      //�ϼ��� �÷ο� ����
    AnimalFlow flow_next(AnimalFlow now);                  //������ �� �� �ִ� ���� ����
};