#include "AnimalFlow.h"



AnimalFlow::AnimalFlow() { base = ""; name = ""; howTo = ""; time = 0; calorie = 0; difficulty = ""; }
AnimalFlow::AnimalFlow(string ibase, string iname, string ihowTo, int itime, int ical, string idif) //����� �Է¿� ���� ���ο� �÷ο� ����
{
    base = ibase;
    name = iname;
    howTo = ihowTo;
    time = itime;
    calorie = ical;
    difficulty = idif;
}
AnimalFlow ::~AnimalFlow() {}
void AnimalFlow::showLink()      //howTo�� ���
{
    cout << name << howTo << endl;
}
string AnimalFlow::getName()      //name�� ����   
{
    return name;
}
void AnimalFlow::setlevel(int level) {
    time = time * level;
    calorie = calorie * level;
}
int AnimalFlow::getTime() {
    return time;
}

FlowManager::FlowManager(){
    srand((unsigned int)time(NULL));      //���� ����
    ifstream file("animalflow.txt");
    string fbase;
    string fname;
    string fhowTo;
    string ftime;
    string fcal;
    string fdif;
    string fhowToLink;
    string fhowToTime;
    if (file.peek() != EOF) {
        while (!file.eof()) {
            // ������ �Էµ� ������� ����
            getline(file, fbase, ' ');
            getline(file, fname, ' ');
            getline(file, fhowToLink, ' ');
            getline(file, fhowToTime, ' ');
            getline(file, ftime, ' ');
            getline(file, fcal, ' ');
            fhowTo = fhowToLink + " " + fhowToTime;
            getline(file, fdif, '\n');

            flow_list.push_back(AnimalFlow(fbase, fname, fhowTo, stoi(ftime), stoi(fcal), fdif));
            if (fbase == "Beast" && fname != "Static_Beast") { // base�� name�� ���� �ش�Ǵ� next_to�� push
                next_to_beast.push_back(AnimalFlow(fbase, fname, fhowTo, stoi(ftime), stoi(fcal), fdif));

            }
            else if (fbase == "Ape" && fname != "Static_Ape") {
                next_to_ape.push_back(AnimalFlow(fbase, fname, fhowTo, stoi(ftime), stoi(fcal), fdif));

            }
            else if (fbase == "Crab" && fname != "Static_Crab") {
                next_to_crab.push_back(AnimalFlow(fbase, fname, fhowTo, stoi(ftime), stoi(fcal), fdif));
            }
            else if (fbase == "Loaded_Beast" && fname != "Loaded_Beast") {
                next_to_loaded_beast.push_back(AnimalFlow(fbase, fname, fhowTo, stoi(ftime), stoi(fcal), fdif));
            }
            else if (fname == "Static_Beast") {
                next_to_loaded_beast.push_back(AnimalFlow(fbase, fname, fhowTo, stoi(ftime), stoi(fcal), fdif));
                next_to_ape.push_back(AnimalFlow(fbase, fname, fhowTo, stoi(ftime), stoi(fcal), fdif));
            }
            else if (fname == "Static_Ape") {
                next_to_beast.push_back(AnimalFlow(fbase, fname, fhowTo, stoi(ftime), stoi(fcal), fdif));
                next_to_crab.push_back(AnimalFlow(fbase, fname, fhowTo, stoi(ftime), stoi(fcal), fdif));
            }
            else if (fname == "Static_Crab") {
                next_to_ape.push_back(AnimalFlow(fbase, fname, fhowTo, stoi(ftime), stoi(fcal), fdif));
            }
            else if (fname == "Loaded_Beast") {
                next_to_beast.push_back(AnimalFlow(fbase, fname, fhowTo, stoi(ftime), stoi(fcal), fdif));
            }
        }
    }
    else
        cout << "Unable to open file" << endl; // ������ �������, �����޽���
    file.close();
}




void FlowManager:: showMenu()               //1.���ۼ����� 2.�����߰��ϱ� 3. Flow�ڵ����� 4. ����
{
    int option = 0;
    while (option != 3)
    {
        cout << "----------------Menu----------------" << endl;
        cout << "          1. Show Motion - HowTo       " << endl;
        cout << "          2. Put New Motion         " << endl;
        cout << "          3. Exit                 " << endl;
        cout << "------------------------------------" << endl;
        cout << "          >"; cin >> option;
        cout << endl << endl;

        switch (option)
        {
        case 1:
            showMotion();
            break;
        case 2:
            putNewFlow();
            break;
        case 3:
            break;
        default:
            cout << "Invalide Input" << endl;
            break;
        }
    }
}

void FlowManager::putNewFlow()               //����ڰ� �߰��� AnimalFlow�� animalflow.txt�� �߰�
{
    string nbase;
    string nname;
    string nhowTo;
    int ntime;
    int ncal;
    string ndif;


    cout << "      Enter the Base of New Motion.(beast, loaded_beast, ape, crap)" << endl;
    cout << "          >"; cin >> nbase;
    cout << "      Enter the Name of New Motion." << endl;
    cout << "          >"; cin >> nname;
    getchar();
    cout << "      Enter the Video Link & its Time for How to Do.(Form : \"Link\" \"0:00(time)\")" << endl;
    cout << "          >"; getline(cin, nhowTo);
    cout << "      Enter How many Times to Do." << endl;
    cout << "          >"; cin >> ntime;
    cout << "      Enter How much calories burn." << endl;
    cout << "          >"; cin >> ncal;
    cout << "      Enter the difficulty(easy, normal, hard)" << endl;
    cout << "          >"; cin >> ndif;
    int i = 0;
    int count = 0;
    while (nhowTo[i]) {         //howTo�� ����üũ. ������ �ݵ�� �ϳ������Ѵ�.
        if (nhowTo[i] == ' ') {
            count++;
        }
        i++;
    }
    if ((tolowerString(nbase) == "beast" || tolowerString(nbase) == "loaded_beast" || tolowerString(nbase) == "ape" || tolowerString(nbase) == "crab") //���̽� �ڼ� �Է°� Ȯ��
        && (tolowerString(ndif) == "easy" || tolowerString(ndif) == "normal" || tolowerString(ndif) == "hard")          //���̵� �Է°� Ȯ��
        && (count == 1 && nhowTo.size() >= 3))       //howTo �Է°� Ȯ��(���� �ϳ� üũ, ���� 3�̻�) nname�� ���� 0���� Ŀ����
    {
        flow_list.push_back(AnimalFlow(nbase, nname, nhowTo, ntime, ncal, ndif)); // �Էµ� �� flow_list�� ����

        ofstream ofile;
        ofile.open("animalflow.txt", ios::app);
        ofile << '\n' << nbase << ' ' << nname << ' ' << nhowTo << ' '
            << ntime << ' ' << ncal << ' ' << ndif;
        ofile.close();
        cout << " >>> User input flow generated!!" << endl << endl;
    }
    else
    {
        if (!(tolowerString(nbase) == "beast" || tolowerString(nbase) == "loaded_beast" || tolowerString(nbase) == "ape" || tolowerString(nbase) == "crab"))
        {
            cout << " >>> Base of New Motion must be [beast or loaded_beast or ape or crab]" << endl;
            cout << " >>> No flow generated!" << endl << endl;
        }
        else if (!(tolowerString(ndif) == "easy" || tolowerString(ndif) == "normal" || tolowerString(ndif) == "hard"))
        {
            cout << " >>> Difficulty of New Motion must be [easy or normal or hard]" << endl;
            cout << " >>> No flow generated!" << endl << endl;
        }
        else if (count != 1 || nhowTo.size() < 3) {
            cout << " >>> Vedio LInk & its Time input form is invalid : (Spacing must be done once)" << endl;
            cout << " >>> No flow generated!" << endl << endl;
        }
    }

}

void FlowManager::showMotion()               //���ۺ� �������ֱ�
{
    string name;
    int count = 0;         //animalflow �̸��� �˻����� �� �ش簪�� �ִ��� ������ �Ǻ�
    for (int i = 0; i < flow_list.size(); i++) {      //���۵��� 3���� ���ٿ� ���
        cout.setf(ios::left);
        cout << "|" << setw(30) << flow_list.at(i).name;
        if (((i + 1) % 3) == 0 || i == (flow_list.size() - 1))
            cout << "|" << endl;
    }
    cout << endl;
    cout << "Enter the name of the animalflow :"; cin >> name;
    for (int i = 0; i < flow_list.size(); i++) {
        if (tolowerString(flow_list.at(i).name).find(tolowerString(name)) != string::npos)
        {
            cout << flow_list.at(i).name << "\t" << flow_list.at(i).howTo << endl;
            count++;
        }
    }
    if (count == 0) {
        cout << "Invalid input : No animalflow in file" << endl;
    }
    cout << endl << endl;
}
void FlowManager::MakeFlow(int num, int dif)            //���Ϳ� �÷ο���� �����鼭 ����, num�� �÷ο� ����
{
    mk_flow.erase(mk_flow.begin(), mk_flow.end());
    if (num < 0) {
        cout << "number of motion must exceed zero! : No flow generated.";
        return;
    }
    AnimalFlow temp;
    int rand_n;
    rand_n = rand() % 4;   // 0-3 ����
    mk_flow.push_back(flow_list.at(rand_n)); //[0]�� static_beast, [1]�� static_Ape, [2]�� Loaded_Beast, [3]�� Crab
    switch (dif) {
    case 0:
        for (int i = 0; i < num - 1; i++)
        {
            while (true) {
                temp = flow_next(mk_flow.at(i));
                if (tolowerString(temp.difficulty) != "hard")   //���̵��� hard�� �Ÿ���.
                    break;
            }
            mk_flow.push_back(temp);
        }
        break;
    case 1:
        for (int i = 0; i < num - 1; i++)
        {
            mk_flow.push_back(flow_next(mk_flow.at(i)));
        }
        break;
    case 2:
        for (int i = 0; i < num - 1; i++)
        {
            temp = flow_next(mk_flow.at(i));
            temp.setlevel(dif);         //AnimalFlow�� Ƚ���� time�� time*dif�� ����
            mk_flow.push_back(temp);
        }
        break;
    case 3:
        for (int i = 0; i < num - 1; i++)
        {
            temp = flow_next(mk_flow.at(i));
            temp.setlevel(dif);         //AnimalFlow�� Ƚ���� time�� time*dif�� ����
            mk_flow.push_back(temp);
        }
        break;
    default:
        cout << "Incorrect Difficulty Input: No flow generated.";
        break;
    }
    /* ������� �÷ο츦 Ȯ���ϴ� �κ�.
    for (int i = 0; i < mk_flow.size(); i++) {
       cout << mk_flow.at(i).name << endl;
    }
    */

}
int FlowManager::CalorieConsumption()         //�Ҹ��� Į�θ����� ����(mk_flow�� �� �Ҹ� Į�θ���)
{
    int ret_cal = 0;
    for (int i = 0; i < mk_flow.size(); i++) {
        ret_cal += mk_flow.at(i).calorie;
    }
    return ret_cal;
}
vector<AnimalFlow> FlowManager::getFlow()      //�ϼ��� �÷ο� ����
{
    return mk_flow;
}
AnimalFlow FlowManager::flow_next(AnimalFlow now)                  //������ �� �� �ִ� ���� ����
{
    int rand_num = 0;         //������ �� ����(next_to_[base]�� ���� �ε����� ����)
    if (tolowerString(now.base) == "beast")
    {
        if (tolowerString(now.name).find("under_switch") != string::npos) {  //�ڼ��� �ٲ�� under_switch�� ���
            rand_num = rand() % (next_to_crab.size());      //base�� beast�� Underswitch������ ���� ��� ���� �ڼ��� Crab�̴�.
            return next_to_crab.at(rand_num);
        }
        rand_num = rand() % (next_to_beast.size());
        return next_to_beast.at(rand_num);
    }
    else if (tolowerString(now.base) == "loaded_beast")
    {
        rand_num = rand() % (next_to_loaded_beast.size());
        return next_to_loaded_beast.at(rand_num);
    }
    else if (tolowerString(now.base) == "crab")
    {
        if (tolowerString(now.name).find("under_switch") != string::npos) {  //�ڼ��� �ٲ�� under_switch�� ���
            rand_num = rand() % (next_to_beast.size());      //base�� crab�� Under_switch������ ���� ��� ���� �ڼ��� Beast�̴�.
            return next_to_beast.at(rand_num);
        }
        rand_num = rand() % (next_to_crab.size());
        return next_to_crab.at(rand_num);
    }
    else if (tolowerString(now.base) == "ape")
    {
        rand_num = rand() % (next_to_ape.size());
        return next_to_ape.at(rand_num);
    }
    else {
        cout << "This case is not allowed : No matching bases found.";
        return AnimalFlow("**", "**", "**", 0, 0, "**");   //base�� ���Ŀ� ���� ������ 
    }
}