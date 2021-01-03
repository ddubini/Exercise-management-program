#include <iostream>
#include "User.h"
#include "WeightTraining.h"
#include "Diet.h"
#include "AnimalFlow.h"

int main(void) {
	string name;
	int age;
	int gender; 
	int weight;
	int height;
	int basic_metabolic;
	
	WorkOutManager msg;
	Routine rt(msg);
	FlowManager fm;
	dietMenu menu;

	while (1) {
		int checkBit = 0;
		int option = 0;
		int exitOpt = 0;
		
		cout << "---------------- Enter User Info ------------" << endl;
		cout << "name > "; cin >> name;
		cout << "age > "; cin >> age;
		cout << "gender(Man : 0   Woman : 1) > "; cin >> gender;
		cout << "weight > "; cin >> weight;
		cout << "height > "; cin >> height;
		

		User user(rt, name, age, gender, weight, height);

		
		while (option != 8)
		{
			cout << "------------------Set Routine-----------------" << endl;
			cout << "        1. Add Today's Workout      " << endl;
			cout << "        2. Add Diet Menu   " << endl;
			cout << "        3. Add Today's Animal Flow   " << endl;
			cout << "        4. Manage Animal Flow   " << endl;
			cout << "        5. Search My Workout   " << endl;
			cout << "        6. Get Menu Recommendation   " << endl;
			cout << "        7. Calculate calorie consumption   " << endl;
			cout << "        8. Exit   " << endl;
			cout << "----------------------------------------------" << endl;
			cout << "           >"; cin >> option;

			switch (option)
			{
			case 1:
				user.putTodayWorkOut(msg, rt);
				break;
			case 2:
				user.putDietMenu(menu);
				break;
			case 3:
				user.putTodayFlow(fm);
				break;
			case 4:
				fm.showMenu();
				break;
			case 5:
				user.getMyWorkOut();
				break;
			case 6:
				user.recommMenu(menu);
				break;
			case 7:
				user.calCalorie(msg, rt, fm);
				break;
			case 8:
				cout << "------------------Set Routine-----------------" << endl;
				cout << "        1. Change User      " << endl;
				cout << "        2. Exit Program   " << endl;
				cout << "----------------------------------------------" << endl;
				cout << "           >"; cin >> exitOpt;
				if (exitOpt == 1) {
					cout << "\nExit " << name << "\'s health management" << endl;
					break;
				}
				else if (exitOpt == 2) {
					cout << "\nExit Program" << endl;
					return 0;
				}

			default:
				cout << "Invalid Input" << endl;
				break;
			}
			cout << endl << endl;
		}
	}
}