#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <vector>
using namespace std;

class Date 
{
private:
    int year;
    int month;
    int date;
public:
    Date(int year, int month, int date)
    {
        this->year = year;
        this->month = month;
        this->date = date;
    }
    int getYear()
    {
        return year;
    }
    int getMonth()
    {
        return month;
    }
    int getDate()
    {
        return date;
    }
};

void bth_parsing(string birth, int bth[3])
{
    int end = 0;
    int index = 0;

    while ((end = birth.find('/')) != string::npos)
    {
        bth[index++] = stoi(birth.substr(0, end));
        birth = birth.substr(end + 1, birth.length() - 1);
    }
    bth[index] = stoi(birth);
}

int getAge(Date today, int birth[3])
{
    int age = today.getYear() - birth[0] - 1;

    //생일 지났음
    if (today.getMonth() > birth[1] || (today.getMonth() == birth[1] && today.getDate() >= birth[2]))
    {
        age++;
    }
    return (age);
}
int main()
{
    //학생 정보 변수
    string department;//학과
    string number;//학번
    string name;//이름
    string birth;//생일
    int bth[3];//생일을 integer로
    int age;//나이

    time_t timer;
    struct tm* t;
    timer = time(NULL);//1970년 1월 1일 0시 0분 0초에서 시작해 현재까지의 초
    t = localtime(&timer);//formatting
    Date today = Date(t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);

    cout << "환영합니다! 학과명, 학번, 이름, 생년월일(yyyy/mm/dd)을 입력하세요> ";
    cin >> department >> number >> name >> birth;

    department.erase(department.length() - 1);//뒤에 ','없애기
    number.erase(number.length() - 1);
    name.erase(name.length() - 1);

    bth_parsing(birth, bth);

    cout << department << " " << number << " " << name << "님 " << bth[0] << "년" << bth[1] << "월"
    << bth[2] << "일생 " << today.getYear() << "년" << today.getMonth() << "월"
    << today.getDate() << "일 현재 " << getAge(today, bth) << "세입니다." << endl;

    return (0);
}
