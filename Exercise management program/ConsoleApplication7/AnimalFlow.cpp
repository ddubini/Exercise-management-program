#include "AnimalFlow.h"



AnimalFlow::AnimalFlow() { base = ""; name = ""; howTo = ""; time = 0; calorie = 0; difficulty = ""; }
AnimalFlow::AnimalFlow(string ibase, string iname, string ihowTo, int itime, int ical, string idif) //사용자 입력에 따라 새로운 플로우 생성
{
    base = ibase;
    name = iname;
    howTo = ihowTo;
    time = itime;
    calorie = ical;
    difficulty = idif;
}
AnimalFlow ::~AnimalFlow() {}
void AnimalFlow::showLink()      //howTo를 출력
{
    cout << name << howTo << endl;
}
string AnimalFlow::getName()      //name을 리턴   
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
    srand((unsigned int)time(NULL));      //난수 설정
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
            // 정보가 입력된 순서대로 저장
            getline(file, fbase, ' ');
            getline(file, fname, ' ');
            getline(file, fhowToLink, ' ');
            getline(file, fhowToTime, ' ');
            getline(file, ftime, ' ');
            getline(file, fcal, ' ');
            fhowTo = fhowToLink + " " + fhowToTime;
            getline(file, fdif, '\n');

            flow_list.push_back(AnimalFlow(fbase, fname, fhowTo, stoi(ftime), stoi(fcal), fdif));
            if (fbase == "Beast" && fname != "Static_Beast") { // base와 name을 보고 해당되는 next_to에 push
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
        cout << "Unable to open file" << endl; // 파일이 없을경우, 에러메시지
    file.close();
}




void FlowManager:: showMenu()               //1.동작설명보기 2.동작추가하기 3. Flow자동생성 4. 종료
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

void FlowManager::putNewFlow()               //사용자가 추가한 AnimalFlow를 animalflow.txt에 추가
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
    while (nhowTo[i]) {         //howTo의 공백체크. 공백은 반드시 하나여야한다.
        if (nhowTo[i] == ' ') {
            count++;
        }
        i++;
    }
    if ((tolowerString(nbase) == "beast" || tolowerString(nbase) == "loaded_beast" || tolowerString(nbase) == "ape" || tolowerString(nbase) == "crab") //베이스 자세 입력값 확인
        && (tolowerString(ndif) == "easy" || tolowerString(ndif) == "normal" || tolowerString(ndif) == "hard")          //난이도 입력값 확인
        && (count == 1 && nhowTo.size() >= 3))       //howTo 입력값 확인(공백 하나 체크, 길이 3이상) nname도 길이 0보다 커야함
    {
        flow_list.push_back(AnimalFlow(nbase, nname, nhowTo, ntime, ncal, ndif)); // 입력된 값 flow_list에 저장

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

void FlowManager::showMotion()               //동작별 설명보여주기
{
    string name;
    int count = 0;         //animalflow 이름을 검색했을 때 해당값이 있는지 없는지 판별
    for (int i = 0; i < flow_list.size(); i++) {      //동작들을 3개씩 한줄에 출력
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
void FlowManager::MakeFlow(int num, int dif)            //벡터에 플로우들을 넣으면서 생성, num은 플로우 갯수
{
    mk_flow.erase(mk_flow.begin(), mk_flow.end());
    if (num < 0) {
        cout << "number of motion must exceed zero! : No flow generated.";
        return;
    }
    AnimalFlow temp;
    int rand_n;
    rand_n = rand() % 4;   // 0-3 랜덤
    mk_flow.push_back(flow_list.at(rand_n)); //[0]은 static_beast, [1]은 static_Ape, [2]는 Loaded_Beast, [3]은 Crab
    switch (dif) {
    case 0:
        for (int i = 0; i < num - 1; i++)
        {
            while (true) {
                temp = flow_next(mk_flow.at(i));
                if (tolowerString(temp.difficulty) != "hard")   //난이도가 hard면 거른다.
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
            temp.setlevel(dif);         //AnimalFlow의 횟수인 time을 time*dif로 설정
            mk_flow.push_back(temp);
        }
        break;
    case 3:
        for (int i = 0; i < num - 1; i++)
        {
            temp = flow_next(mk_flow.at(i));
            temp.setlevel(dif);         //AnimalFlow의 횟수인 time을 time*dif로 설정
            mk_flow.push_back(temp);
        }
        break;
    default:
        cout << "Incorrect Difficulty Input: No flow generated.";
        break;
    }
    /* 만들어진 플로우를 확인하는 부분.
    for (int i = 0; i < mk_flow.size(); i++) {
       cout << mk_flow.at(i).name << endl;
    }
    */

}
int FlowManager::CalorieConsumption()         //소모한 칼로리량을 리턴(mk_flow의 총 소모 칼로리량)
{
    int ret_cal = 0;
    for (int i = 0; i < mk_flow.size(); i++) {
        ret_cal += mk_flow.at(i).calorie;
    }
    return ret_cal;
}
vector<AnimalFlow> FlowManager::getFlow()      //완성된 플로우 리턴
{
    return mk_flow;
}
AnimalFlow FlowManager::flow_next(AnimalFlow now)                  //다음에 올 수 있는 동작 리턴
{
    int rand_num = 0;         //난수가 될 예정(next_to_[base]의 랜덤 인덱스를 위해)
    if (tolowerString(now.base) == "beast")
    {
        if (tolowerString(now.name).find("under_switch") != string::npos) {  //자세가 바뀌는 under_switch일 경우
            rand_num = rand() % (next_to_crab.size());      //base가 beast인 Underswitch동작을 했을 경우 현재 자세는 Crab이다.
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
        if (tolowerString(now.name).find("under_switch") != string::npos) {  //자세가 바뀌는 under_switch일 경우
            rand_num = rand() % (next_to_beast.size());      //base가 crab인 Under_switch동작을 했을 경우 현재 자세는 Beast이다.
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
        return AnimalFlow("**", "**", "**", 0, 0, "**");   //base가 형식에 맞지 않으면 
    }
}