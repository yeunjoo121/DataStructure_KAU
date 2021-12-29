#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
using namespace std;

string erase_char(string s, int index)
{
    string res;

    res = s.substr(0, index);
    res += s.substr(index + 1, s.size() - (index + 1));

    return (res);
}

void removeMarks(vector<string> *words)
{
    for(int i = 0; i < words->size(); i++)
    {
        for(int j = 0; j < (*words)[i].length(); j++)
        {
            if (((*words)[i][j] >= 33 && (*words)[i][j] <= 47) || ((*words)[i][j] >= 58 && (*words)[i][j] <= 64) || 
            ((*words)[i][j] >= 91 && (*words)[i][j] <= 96) || ((*words)[i][j] >= 123 && (*words)[i][j] <= 126))//특수문자 다 지우기(아스키코드)
            {
                (*words)[i] = erase_char((*words)[i], j);
            }
        }
    }
    return ;
}

void selectionSort(vector<string> *words)
{
    int minIndex = 0;

    for (int i = 0; i < words->size() - 1; i++)
    {
        minIndex = i;
        for (int j = i + 1; j < words->size(); j++)
        {
            if ((*words)[j] < (*words)[minIndex])
            {
                minIndex = j;
            }
        }
        swap((*words)[i], (*words)[minIndex]);
    }
}

void removeDuplicate(vector<string> *words)
{
    //이전 것과 비교해서 같으면 제거한다.
    int prev = 0;
    for(int i = 1; i < words->size(); i++)
    {
        if ((*words)[prev] == (*words)[i])
        {
            (*words).erase((*words).begin() + i);
        }
        prev = i;
    }
}

void displayWords(vector<string> words)
{
    for(int i = 0; i < words.size(); i++)
    {
        cout << words[i] << endl;
    }
}

int BinarySearch(vector<string> words, string target, int left, int right) {
    if (left > right)
        return (-1);

    int middle = (left + right) / 2;
    if (words[middle] == target)
        return middle;
    else if (words[middle] > target)
        return BinarySearch(words, target, left, middle - 1);
    else
        return BinarySearch(words, target, middle + 1, right);
}

int main(void)
{
    string fileName = ("input.txt");
    vector<string> words;
    string word;
    ifstream inputFile(fileName);

    if (!inputFile.is_open())//open 실패
    {
        cout << "failed to open file" << endl;
        return (0);
    }

    while (inputFile >> word)
    {
        words.push_back(word);
    }
    cout << "<--------------------input.txt------------------->" << endl;
    displayWords(words);//input.txt 내용 출력

    cout << "<------------------removeMarks------------------->" << endl;
    removeMarks(&words);//문장부호 없애기
    displayWords(words);
    
    cout << "<---------------------sort----------------------->" << endl;
    selectionSort(&words);//정렬하기
    displayWords(words);

    cout << "<-----------------removeDuplicate---------------->" << endl;
    removeDuplicate(&words);
    displayWords(words);
    cout << "<-------------------binarySearch----------------->" << endl;
    string target = "";
    int direction = 0;
    while (target != ".")
    {
        cin >> target;
        direction = BinarySearch(words, target, 0, words.size());
        if (direction != -1)
        {
            cout << direction + 1 << endl;
        }
        else
            cout << direction << endl;
        
    }

    inputFile.close();
    return 0; 
}