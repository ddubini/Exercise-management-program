#include "WeightTraining.h"
 
WorkOut::WorkOut(string t_cat, string t_name, string t_link) :set(0), rep(0)
{
category = t_cat;
name = t_name;
link = t_link;
}
void WorkOut::SetRep(int m, int n)
{
	set = m;
	rep = n;
}
string WorkOut::getCategory()
{
	return tolowerString(category);
}
string WorkOut::getLink()
{
	return link;
}
string WorkOut::getName()				// returs name of the workout in lower cases
{
	return tolowerString(name);
}
int WorkOut::getSet()
{
	return set;
}
int WorkOut::getRep()
{
	return rep;
}
void WorkOut::ShowInfo() const
{
	cout << setw(15) << left << category;
	cout << setw(15) << left << name;
	cout << left << link << endl;
}


WorkOutManager::WorkOutManager()
{
	ifstream workoutfile;
	workoutfile.open("workout.txt");
	if (!workoutfile.is_open())
	{
		cout << "Unable to open file" << endl;
	}
	string line;
	while (getline(workoutfile, line))
	{
		//read category
		int tab = line.find_first_of('\t', 0);				// all elements divided by tab
		string r_cat = line.substr(0, tab);					//cut off the category string from line and save
		tab = line.find_first_not_of('\t', tab);			//find the position of the first letter of name
		int name_end = line.find_first_of('\t', tab);		//find the position of the last letter of name
		string r_name = line.substr(tab, name_end - tab);	//cut off the name string from line and save
		tab = line.find_first_not_of('\t', name_end);		//find the position of the first letter of link
		int link_end = line.find_first_of('\n', tab);		//find the position of the last letter of link
		string r_link = line.substr(tab, link_end - tab);	//cut of the link string form line and save

		WorkOut workout(r_cat, r_name, r_link);				//save three strings into WorkOut object

		if (r_cat == "chest")
		{
			chest.push_back(workout);
		}
		else if (r_cat == "abs")
		{
			abs.push_back(workout);
		}
		else if (r_cat == "arms")
		{
			arms.push_back(workout);
		}
		else if (r_cat == "lower_body")
		{
			lower_body.push_back(workout);
		}
		else if (r_cat == "back")
		{
			back.push_back(workout);
		}
		else if (r_cat == "shoulder")
		{
			shoulder.push_back(workout);
		}
		else
		{
			cout << "Unidentified Category in the File!" << endl;
		}
	}

}
void WorkOutManager::ShowTop() const
{
	cout << setw(15) << left << "Category";
	cout << setw(15) << left << "Name";
	cout << setw(15) << left << "Video Link" << endl;;
}
void WorkOutManager::ShowAbsWO()
{
	vector<WorkOut>::iterator it;
	for (it = abs.begin(); it != abs.end(); it++)
	{
		it->ShowInfo();
	}
}
void WorkOutManager::ShowArmsWO()
{
	vector<WorkOut>::iterator it;
	for (it = arms.begin(); it != arms.end(); it++)
	{
		it->ShowInfo();
	}
}
void WorkOutManager::ShowBackWO()
{
	vector<WorkOut>::iterator it;
	for (it = back.begin(); it != back.end(); it++)
	{
		it->ShowInfo();
	}
}
void WorkOutManager::ShowChestWO()
{
	vector<WorkOut>::iterator it;
	for (it = chest.begin(); it != chest.end(); it++)
	{
		it->ShowInfo();
	}
}
void WorkOutManager::ShowLowerBodyWO()
{
	vector<WorkOut>::iterator it;
	for (it = lower_body.begin(); it != lower_body.end(); it++)
	{
		it->ShowInfo();
	}
}
void WorkOutManager::ShowShoulderWO()
{
	vector<WorkOut>::iterator it;
	for (it = shoulder.begin(); it != shoulder.end(); it++)
	{
		it->ShowInfo();
	}
}
void WorkOutManager::ShowAllWorkOut()
{
	ShowAbsWO();
	ShowArmsWO();
	ShowBackWO();
	ShowChestWO();
	ShowLowerBodyWO();
	ShowShoulderWO();
}
void WorkOutManager::SearchByName()			// Search Workouts by Name
{
	string line;
	cout << "Enter Workout Name: "; cin >> line;
	line = tolowerString(line);
	cout << endl;
	ShowTop();
	vector<WorkOut>::iterator it;
	for (it = abs.begin(); it != abs.end(); it++)
	{
		if (line == it->getName())
			it->ShowInfo();
	}
	for (it = arms.begin(); it != arms.end(); it++)
	{
		if (line == it->getName())
			it->ShowInfo();
	}
	for (it = back.begin(); it != back.end(); it++)
	{
		if (line == it->getName())
			it->ShowInfo();
	}
	for (it = chest.begin(); it != chest.end(); it++)
	{
		if (line == it->getName())
			it->ShowInfo();
	}
	for (it = lower_body.begin(); it != lower_body.end(); it++)
	{
		if (line == it->getName())
			it->ShowInfo();
	}
	for (it = shoulder.begin(); it != shoulder.end(); it++)
	{
		if (line == it->getName())
			it->ShowInfo();
	}
}
void WorkOutManager::SearchByCategory()		// Search Workouts by Categories
{
	int choice;
	cout << "--------------Category--------------" << endl;
	cout << "             1. Abs				 " << endl;
	cout << "             2. Arms				 " << endl;
	cout << "             3. Back				 " << endl;
	cout << "             4. Chest				 " << endl;
	cout << "             5. Lower-body			 " << endl;
	cout << "             6. Shoulder			 " << endl;
	cout << "             7. Show All			 " << endl;
	cout << "------------------------------------" << endl;
	cout << "           > "; cin >> choice;

	cout << endl << endl;
	ShowTop();

	switch (choice)
	{
	case 1:
		ShowAbsWO();
		break;
	case 2:
		ShowArmsWO();
		break;
	case 3:
		ShowBackWO();
		break;
	case 4:
		ShowChestWO();
		break;
	case 5:
		ShowLowerBodyWO();
		break;
	case 6:
		ShowShoulderWO();
		break;
	case 7:
		ShowAllWorkOut();
		break;
	default:
		cout << "Wrong Input" << endl;
		break;
	}
}
void WorkOutManager::SearchWO()			// Search Workouts
{
	int option;
	cout << "---------------Search---------------" << endl;
	cout << "       1. Search by Category        " << endl;
	cout << "       2. Search by Name			 " << endl;
	cout << "------------------------------------" << endl;
	cout << "       >"; cin >> option;

	switch (option)
	{
	case 1:
		SearchByCategory();
		break;
	case 2:
		SearchByName();
		break;
	default:
		cout << "Wrong Input" << endl;
		break;
	}
	cout << endl << endl;
}
WorkOut WorkOutManager::SearchAndReturn(string name_str)
{
	vector<WorkOut>::iterator it;
	for (it = chest.begin(); it != chest.end(); it++)
	{
		if (tolowerString(name_str) == it->getName())
			return *it;
	}
	for (it = back.begin(); it != back.end(); it++)
	{
		if (tolowerString(name_str) == it->getName())
			return *it;
	}
	for (it = arms.begin(); it != arms.end(); it++)
	{
		if (tolowerString(name_str) == it->getName())
			return *it;
	}
	for (it = abs.begin(); it != abs.end(); it++)
	{
		if (tolowerString(name_str) == it->getName())
			return *it;
	}
	for (it = lower_body.begin(); it != lower_body.end(); it++)
	{
		if (tolowerString(name_str) == it->getName())
			return *it;
	}
	for (it = shoulder.begin(); it != shoulder.end(); it++)
	{
		if (tolowerString(name_str) == it->getName())
			return *it;
	}
	WorkOut wo("N/A", "N/A", "N/A");
	return wo;
}


Routine::Routine(WorkOutManager& wo_man)
{
	mngr = wo_man;
}
void Routine::SplitDay()
{
	int day;
	cout << "----------------------------------------------" << endl;
	cout << "Enter a number of days to split your routine: "; cin >> day;
	max_day = day;
}
void Routine::AddWorkOut(int day_idx)
{
	mngr.SearchByCategory();
	string name;
	cout << "Enter the name of the workout: "; cin >> name;
	name = tolowerString(name);

	WorkOut temp = mngr.SearchAndReturn(name);

	if (temp.getCategory() == "n/a" && temp.getName() == "n/a" && temp.getLink() == "N/A")
	{
		cout << "Invalide WorkOut Input!" << endl;
		return;
	}

	int set, rep;
	cout << "Enter number of Sets: "; cin >> set;
	cout << "Enter number of Reps: "; cin >> rep;
	temp.SetRep(set, rep);
	/*
	if (temp.getCategory() == "chest")
	{
		chest.push_back(temp);
	}
	else if(temp.getCategory() == "arms")
	{
		arms.push_back(temp);
	}
	else if(temp.getCategory() == "abs")
	{
		abs.push_back(temp);
	}
	else if(temp.getCategory() == "back")
	{
		back.push_back(temp);
	}
	else if(temp.getCategory() == "lower_body")
	{
		lower_body.push_back(temp);
	}
	else if(temp.getCategory() == "shoulder")
	{
		shoulder.push_back(temp);
	}*/
	day[day_idx - 1].push_back(temp);

	cout << endl << endl;
}
void Routine::setRoutine(string file_name)
{
	if (max_day == 0)
		SplitDay();
	while (1)
	{
		int option;
		int day_num;

		file_name.append("_·çÆ¾.txt");
		string str;
		ifstream in(file_name);
		cout << "-------------Set Routine------------" << endl;
		cout << "           1. Add Workout           " << endl;
		cout << "           2. Show Split Number     " << endl;
		cout << "           3. Show Routine     " << endl;
		cout << "           4. Exit                  " << endl;
		cout << "------------------------------------" << endl;
		cout << "           >"; cin >> option;

		switch (option)
		{
		case 1:
			cout << "day number? :"; cin >> day_num;
			if (day_num > max_day)
			{
				cout << "the number you have entered exceeds the maximum split day" << endl;
				break;
			}
			AddWorkOut(day_num);
			break;
		case 2:
			cout << "Your Routine is splitted into " << max_day << " day(s)" << endl;
			break;

		case 3:
			cout << endl;
			for (int i = 0; i < max_day; i++) {
				cout << "day " << (i + 1) << ": ";
				for (int j = 0; j < day[i].size(); j++) {
					cout << day[i].at(j).getName() << "(" << day[i].at(j).getSet() << "X" << day[i].at(j).getRep() << ")" << " ";
				}
				cout << endl;
			}
			break;
		case 4:
			cout << "Exiting Set Routine Menu..." << endl;
			return;
		default:
			cout << "Invalid Input" << endl;
			break;
		}
		cout << endl << endl;
	}
}
void Routine::showRoutine()
{
	vector<WorkOut>::iterator it;
	/*
	for (it = abs.begin(); it != abs.end(); it++)
	{
		cout << setw(15) << left << it->getName() << '(' << it->getSet() << 'X' << it->getRep() << ')' << endl;
	}
	for (it = arms.begin(); it != arms.end(); it++)
	{
		cout << setw(15) << left << it->getName() << '(' << it->getSet() << 'X' << it->getRep() << ')' << endl;
	}
	for (it = back.begin(); it != back.end(); it++)
	{
		cout << setw(15) << left << it->getName() << '(' << it->getSet() << 'X' << it->getRep() << ')' << endl;
	}
	for (it = chest.begin(); it != chest.end(); it++)
	{
		cout << setw(15) << left << it->getName() << '(' << it->getSet() << 'X' << it->getRep() << ')' << endl;
	}
	for (it = lower_body.begin(); it != lower_body.end(); it++)
	{
		cout << setw(15) << left << it->getName() << '(' << it->getSet() << 'X' << it->getRep() << ')' << endl;
	}
	for (it = shoulder.begin(); it != shoulder.end(); it++)
	{
		cout << setw(15) << left << it->getName() << '(' << it->getSet() << 'X' << it->getRep() << ')' << endl;
	}
	*/
	for (int i = 0; i < max_day; i++)
	{
		cout << "day " << i + 1 << ':' << endl;
		for (it = day[i].begin(); it != day[i].end(); it++)
			cout << setw(15) << left << it->getName() << '(' << it->getSet() << 'X' << it->getRep() << ')' << endl;
		cout << endl;
	}
	cout << endl << endl;
}
int Routine::getMaxDay() {
	return max_day;
}
vector<WorkOut>* Routine::getDay() {
	return day;
}

