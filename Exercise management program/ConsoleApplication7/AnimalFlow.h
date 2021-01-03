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
    string base;         //flow의 베이스 (4가지 중 하나. beast, Loaded_beast, Ape, Crab)
    string name;         //flow이름
    string howTo;         //운동 동작 방법 (링크, 영상이면 시간)
    int time;            //동작별 수행횟수(defualt 기준)
    int calorie;         //동작별 칼로리 소모량(사실 정확한 칼로리 소모는 알기 어려움. 데모임을 감안해 적당한 값을 넣어주거나 삭제 가능)
    string difficulty;         //동작의 난이도(사용자의 선택에 따라 '상'난이도 뺄 수 있게
public:
    AnimalFlow();
    AnimalFlow(string ibase, string iname, string ihowTo, int itime, int ical, string idif); //사용자 입력에 따라 새로운 플로우 생성
    ~AnimalFlow();
    void showLink();      //howTo를 출력
    string getName();     //name을 리턴   
    void setlevel(int level);  //난이도에 따른 time, calorie 조정
    int getTime();         //time을 리턴
    friend class FlowManager;
};
class FlowManager {
private:
    vector<AnimalFlow> flow_list;   //파일에서 읽어와서 저장
    vector<AnimalFlow> mk_flow;      //생성될 플로우 - 완성된 하나의 동작 흐름이며 user에 기입 가능
    vector<AnimalFlow> next_to_beast;      //비스트베이스 다음에 올 수 있는 동작
    vector<AnimalFlow> next_to_ape;         //에잎 다음에 올 수 있는 동작
    vector<AnimalFlow> next_to_loaded_beast;//로디드비스트 다음에 올 수 있는 동작
    vector<AnimalFlow> next_to_crab;      //크랩 다음에 올 수 있는 동작
    fstream file;
public:
    FlowManager();      //FlowManager 생성자. 파일에서 동작들을 불러와 벡터에 저장
    void showMenu();               //1.동작설명보기 2.동작추가하기 3. 종료
    void putNewFlow();               //사용자가 추가한 AnimalFlow를 animalflow.txt에 추가
    void showMotion();              //동작별 설명보여주기
    void MakeFlow(int num, int dif);            //벡터에 플로우들을 넣으면서 생성, num은 플로우 갯수
    int CalorieConsumption();         //소모한 칼로리량을 리턴(mk_flow의 총 소모 칼로리량)
    vector<AnimalFlow> getFlow();      //완성된 플로우 리턴
    AnimalFlow flow_next(AnimalFlow now);                  //다음에 올 수 있는 동작 리턴
};