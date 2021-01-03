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
	string name;			// �����̸�
	float calorie;			// ���� Į�θ�(kcal)
	float protein;			// ���� �ܹ���
	int gram;				// ���� ��
	Food* next;				// list��
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
	// food.txt ���� �̸� �����ڿ��� ����
	string foodf, cfoodf, pfoodf;
	Food* foodl;		// �Ϲ� ���� list
	Food* cfoodl;		// �Ϲ� ���̵� list
	Food* pfoodl;		// �Ϲ� �ܹ��� list
	int foodT, cfoodT, pfoodT;
	// list�� ���� �ֱ�
	void push(Food*, Food*);
	// ���� �̸��� ���� Food ã��
	Food* find(string name);
public:
	dietMenu();

	/*
	// ��õ �ޱ�
	// RMR = ���ʴ�緮, hard = �����(0~4)
	// time = ��õ�ð��� ��,��,��,��ü(1~4)
	// purpose ���� = true, ���� = false
	*/
	string recommend(int RMR, int hard, bool purpose, int time = 4);

	// ���̵� ���Ŀ��� �´� Į�θ� ���� �������� ������ null
	Food* findcal(float min, float max);

	// �ܹ��� ���̵忡�� �´� �ܹ��� �������� ������ null
	Food* findprot(float min, float max);

	// "����/����/����" �� ��Ʈ������ Į�θ�,�ܹ��� ��� 
	int cal_calorie(string meals); // �� Į�θ� ���
	float cal_protein(string meals);	// �� �ܹ��� ���
};
#endif