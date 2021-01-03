#include "Diet.h"

dietMenu::dietMenu() {
	string buf;
	foodf = "food.txt";
	cfoodf = "cfood.txt";
	pfoodf = "pfood.txt";
	foodl = new Food("", 0, 0, 0);
	cfoodl = new Food("", 0, 0, 0);
	pfoodl = new Food("", 0, 0, 0);
	foodT = 0;
	cfoodT = 0;
	pfoodT = 0;
	srand((unsigned int)time(NULL));
	ifstream file(foodf);
	if (!file.is_open()) {
		cout << foodf << "File open error";
		return;
	}
	while (getline(file, buf)) {
		int name = buf.find(" ");
		int cal = buf.find(" ", name + 1);
		int pro = buf.find(" ", cal + 1);
		Food* pt = new Food(buf.substr(0, name), stof(buf.substr(name + 1, cal - name - 1)), stof(buf.substr(cal + 1, pro - cal - 1)), stoi(buf.substr(pro + 1)));
		push(foodl, pt);
		foodT++;
		buf.clear();
	}
	file.close();
	file.open(cfoodf, ios_base::in);
	if (!file.is_open()) {
		cout << cfoodf << "File open error";
		return;
	}
	while (getline(file, buf)) {
		int name = buf.find(" ");
		int cal = buf.find(" ", name + 1);
		int pro = buf.find(" ", cal + 1);
		Food* pt = new Food(buf.substr(0, name), stof(buf.substr(name + 1, cal - name - 1)), stof(buf.substr(cal + 1, pro - cal - 1)), stoi(buf.substr(pro + 1)));
		push(cfoodl, pt);
		cfoodT++;
		buf.clear();
	}
	file.close();
	file.open(pfoodf, ios_base::in);
	if (!file.is_open()) {
		cout << pfoodf << "File open error";
		return;
	}
	while (getline(file, buf)) {
		int name = buf.find(" ");
		int cal = buf.find(" ", name + 1);
		int pro = buf.find(" ", cal + 1);
		Food* pt = new Food(buf.substr(0, name), stof(buf.substr(name + 1, cal - name - 1)), stof(buf.substr(cal + 1, pro - cal - 1)), stoi(buf.substr(pro + 1)));
		push(pfoodl, pt);
		pfoodT++;
		buf.clear();
	}
	file.close();
}

string dietMenu::recommend(int RMR, int hard, bool purpose, int ptime){
	switch (hard) {
	case 0:
		RMR *= 1.2;
		break;
	case 1:
		RMR *= 1.375;
		break;
	case 2:
		RMR*= 1.55;
		break;
	case 3:
		RMR *= 1.725;
		break;
	case 4:
		RMR *= 1.9;
		break;
	}
	if (purpose)
		RMR *= 1.15;
	else
		RMR *= 0.85;
	switch (ptime) {
	case 1:
		RMR /=4;
		break;
	case 2:
		RMR /= 3;
		break;
		break;
	case 3:
		RMR /= 3;
		break;
	case 4:
		return "[아침]" + recommend(RMR, hard, purpose, 1) + "\n[점심]" + recommend(RMR, hard, purpose, 2) + "\n[저녁]" + recommend(RMR, hard, purpose, 3);
	}
	string result;
	int goalprotg = (RMR / 3) /4;

	Food* pt = foodl;
	vector<Food*>list;
	while (pt->getnext()!=nullptr) {
		float i = pt->getnext()->getcalorie();
		float tempcal = pt->getcalorie();
		float temppro = pt->getprotein();
		if ((tempcal>RMR/2&&tempcal<RMR)&&(temppro>goalprotg/2&&temppro<goalprotg))
			list.push_back(pt);
		pt = pt->getnext();
	}
	if (!list.size())
		return "No data base";
	for (int i = rand() % (list.size()); i > 0; i--)
		list.pop_back();
	pt = list.back();
	// 메인메뉴 결정 완료 pt;
	
	float mcal = pt->getcalorie();
	float mpro = pt->getprotein();
	result += pt->getname();
	if (mcal < 500 && mpro < 20) {
		mcal *= 2;
		mpro *= 2;
		result += "*2";
	}
	float missprot = goalprotg - mpro;
	float misscal = RMR - mcal;
	int index = 0;
	while (missprot > 45.7) {
		index++;
		missprot =- 45.7;
	}
	if (index) {
		result += "/단백질보충제*";
		result += to_string(index);
	}

	pt = findprot(missprot * 0.9, missprot * 1.1);
	if (pt)
		result += "/"+pt->getname();
	pt = findcal(misscal * 0.9, misscal * 1.1);
	if (pt)
		result += "/"+pt->getname();
	return result;
}

Food* dietMenu::findcal(float min, float max) {
	Food* pt = cfoodl;
	vector<Food*>list;
	while (pt->getnext()!=nullptr) {
		float i = pt->getnext()->getprotein();
		if (i >= min && i <= max)
			list.push_back(pt);
		pt = pt->getnext();
	}
	if (list.size() == 0)
		return nullptr;
	for (int i = rand() % (list.size()); i > 0; i--)
		list.pop_back();
	return list.back();
}

Food* dietMenu::findprot(float min, float max) {
	Food* pt = pfoodl;
	vector<Food*>list;
	while (pt->getnext()!=nullptr) {
		float i = pt->getnext()->getprotein();
		if (i >= min && i <= max)
			list.push_back(pt);
		pt = pt->getnext();
	}
	if (list.size() == 0)
		return nullptr;
	for (int i = rand() % (list.size()); i > 0; i--)
		list.pop_back();
	return list.back();
}

void dietMenu::push(Food* to,Food*what) {
	Food* pt = to;
	while (pt->getnext() != nullptr)
		pt = pt->getnext();
	pt->setnext(what);
}
Food* dietMenu::find(string name) {
	Food* pt;
	for(pt = foodl;pt->getnext()!=nullptr;pt=pt->getnext())
		if (!pt->getnext()->getname().compare(name))
			return pt->getnext();
	for (pt = pfoodl; pt->getnext() != nullptr; pt = pt->getnext())
		if (!pt->getnext()->getname().compare(name))
			return pt->getnext();
	for (pt = cfoodl; pt->getnext() != nullptr; pt = pt->getnext())
		if (!pt->getnext()->getname().compare(name))
			return pt->getnext();
	return nullptr;
}
int dietMenu::cal_calorie(string meals) {
	string temp;
	Food* pt;
	int n = meals.size();
	int result = 0;
	for (int i = 0; i < n+1; i++) {
		if (meals[i] == '/'||meals[i]==NULL) {
			if ((pt = find(temp)) != nullptr)
				result += pt->getcalorie();
			temp.clear();
			continue;
		}
		temp += meals[i];
	}
	return result;
}
float dietMenu::cal_protein(string meals) {
	string temp;
	Food* pt;
	int n = meals.size();
	float result = 0;
	for (int i = 0; i < n+1; i++) {
		if (meals[i] == '/'||meals[i]==NULL) {
			if ((pt = find(temp)) != nullptr)
				result += pt->getprotein();
			temp.clear();
			continue;
		}
		temp += meals[i];
	}
	return result;
}

Food::Food(string iname, float ical,float iprot,int igram ) {
	name = iname;
	calorie = ical;
	protein = iprot;
	gram = igram;
	next = nullptr;
}