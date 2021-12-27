#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <vector>
using namespace std;

#define TRUE	1
#define FALSE	0
//날짜 입력 형식이 맞지 않는 경우 o
//있지 않은 날짜가 입력된 경우 1) 현재 날짜보다 더 뒤  2) 2월 30일 등 있지 않은 날짜 o
//문자열에 숫자가 있는 경우 o
//숫자에 문자가 있는 경우 o
//입력 시 , 안붙였을 때 o

//column이 월이라 0번째 index는 비워둔다.
int calender[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

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

int valid_birth(int bth[3], Date today)
{
	//현재 날짜 기준으로 뒤의 날짜이면
	if ((bth[0] > today.getYear()) || (bth[0] == today.getYear() && bth[1] > today.getMonth()) || 
	(bth[0] == today.getYear() && bth[1] == today.getMonth() && bth[2] > today.getDate()))
	{
		return (FALSE);
	}
	if (bth[1] < 0 || bth[1] > 12)
	{
		return (FALSE);
	}
	//있지 않은 날짜이면(ex 3월 32일 등), 윤년 고려에 주의한다.
	//4로 나누어 떨어지고 100으로 나누어 떨어지지 않는 년도, 4로 나누어 떨어지고 100으로 나누어 떨어지는데 400으로 나누어서 떨어지는 년도도 윤년
	if ((bth[0] % 4 == 0 && bth[0] % 100 != 0) || (bth[0] % 4 == 0 && bth[0] % 100 == 0 && bth[0] % 400 == 0))
	{
		if (bth[1] == 2 && bth[2] > 29)//2월인 경우 예외처리함.
		{
			return (FALSE);
		}
		else if (bth[1] != 2)
		{
			if(calender[bth[1]] < bth[2])
				return (FALSE);
		}
	}
	else//윤년 아닐 때
	{
		if (calender[bth[1]] < bth[2])
		{
			return (FALSE);
		}
	}
	return (TRUE);
}	

int getAge(Date today, int birth[3])
{
    int age = today.getYear() - birth[0] - 1;

    //생일 지났음
    if ((today.getMonth() > birth[1]) || (today.getMonth() == birth[1] && today.getDate() >= birth[2]))
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
	int success = 0;//valid input이면 1

    time_t timer;
    struct tm* t;
    timer = time(NULL);//1970년 1월 1일 0시 0분 0초에서 시작해 현재까지의 초
    t = localtime(&timer);//formatting
    Date today = Date(t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);

	while(success == 0)
	{
		cout << "환영합니다! 학과명, 학번, 이름, 생년월일(yyyy/mm/dd)을 입력하세요> ";
		cin >> department >> number >> name >> birth;

		try
		{
			//맨 뒤에 , 붙어있는지 확인 후 없애주기. , 없으면 invalid input
			if (department[department.length() - 1] != ',')
			{
				throw department;
			}
			department.erase(department.length() - 1);//뒤에 ','없애기
			if (number[number.length() - 1] != ',')
			{
				throw number;
			}
			number.erase(number.length() - 1);
			if (name[name.length() - 1] != ',')//뒤에 ','없애기
			{
				throw name;
			}
			name.erase(name.length() - 1);//뒤에 ','없애기

			//잘못된 값 들어있는지 검사
			for(int i = 0; i < department.length(); i++)
			{
				if (isnumber(department[i]) == 1)//string인데 숫자들어옴
					throw department;
			}
			for(int i = 0; i < number.length(); i++)
			{
				if (isnumber(number[i]) != 1)//숫자가 아닌 다른 것 들어오면
					throw number;
			}
			for(int i = 0; i < name.length(); i++)
			{
				if (isnumber(name[i]) == 1)//숫자들어오면
					throw name;
			}
			for(int i = 0; i < birth.length(); i++)
			{
				if (i == 4 || i == 7)
				{
					if(birth[i] != '/')
						throw birth;
				}
				if (i != 4 && i != 7)
				{
					if (isnumber(birth[i]) != 1)
						throw birth;
				}
			}
			bth_parsing(birth, bth);
			if (valid_birth(bth, today) == FALSE)//있지 않은 생일 날짜 형식
			{
				throw birth;
			}
			success = 1; //valid input
		}
		catch(string str)
		{
			cout << "잘못된 인자가 있습니다! 잘못된 인자 : " << str << endl;
			success = 0;
		}
	}

    cout << department << " " << number << " " << name << "님 " << bth[0] << "년" << bth[1] << "월"
    << bth[2] << "일생 " << today.getYear() << "년" << today.getMonth() << "월"
    << today.getDate() << "일 현재 " << getAge(today, bth) << "세입니다." << endl;

    return (0);
}