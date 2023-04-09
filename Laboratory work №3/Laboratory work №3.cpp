#include <iostream>
#include <windows.h>
using namespace std;

class Human
{
protected:
    string name;
    int birth_year;
    string sex;
public:
    Human(string n, int by, string s) : name(n), birth_year(by), sex(s) {}

    void setName(string n) 
    { 
        name = n; 
    }
    void setBirthYear(int by) 
    { 
        birth_year = by; 
    }
    void setSex(string s) 
    { 
        sex = s; 
    }
    void printInfo()
    {
        cout << "\n\nМене звати " << name << ", я " << sex << ". Мій рік народження це " << birth_year << "-й.";
    }
};

class Student : public Human
{
private:
    int admission_year;
    string scorebook_num;
    string* subjects;
    int num_of_subjects;
    double average_score;
public:
    Student(const Human& obj, int ay, string sn) : Human(obj), admission_year(ay), scorebook_num(sn)
    {
        subjects = nullptr;
        num_of_subjects = 0;
        average_score = 0;
    }

    ~Student() 
    { 
        delete[] subjects; 
    }

    void add_subject(string sbj)
    {
        string* new_subjects = new string[num_of_subjects + 1];

        for (int i = 0; i < num_of_subjects; i++)
            new_subjects[i] = subjects[i];

        new_subjects[num_of_subjects] = sbj;
        num_of_subjects++;

        delete[] subjects;
        subjects = new_subjects;
    }
    void calculate_average_score()
    {
        double sum = 0.0, input;
        bool mistake;
        for (int i = 0; i < num_of_subjects; i++)
        {
            do
            {
                mistake = false;
                cout << "Введіть оцінку з дисципліни \"" << subjects[i] << "\": ";
                cin >> input;
                if (cin.fail() || input < 0.0 || input > 100.0)
                {
                    cin.clear();
                    cin.ignore(32767, '\n');
                    mistake = true;
                    cout << "Неіснуюча оцінка!\n";
                }
            } while (mistake);
            sum += input;
        }

        average_score = sum / num_of_subjects;
    }
    void printInfo()
    {
        Human::printInfo();
        cout << " З " << admission_year << "-го я вчуся в університеті. Мій розклад складається з таких предметів: ";

        bool isFirst = true;
        for (int i = 0; i < num_of_subjects; i++)
        {
            cout << subjects[i];
            if (i != num_of_subjects - 1)
                cout << ", ";
        }
        cout << ". Номер моєї залікової книжки " << scorebook_num << ", а мій середній бал дорівнює " << average_score << '.';
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Human anna("Іваненко Анна Русланівна", 2005, "жінка");
    Human kostya("Саламатін Костянтин Сергійович", 2004, "чоловік");
    Student maxim(Human("Глєбов Максим Максимович", 2005, "чоловік"), 2022, "7-121-2022/9");

    maxim.add_subject("ООП");
    maxim.add_subject("Математичний аналіз");
    maxim.add_subject("АКтаНРП");
    maxim.add_subject("Дискретна математика");
    maxim.add_subject("Філософія");
    maxim.calculate_average_score();
    
    anna.printInfo();
    kostya.printInfo();
    maxim.printInfo();

    cout << endl;
    return 0;
}
