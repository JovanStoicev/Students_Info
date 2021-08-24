#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <fstream>
#include <vector>
using namespace std;

class Calendar {
    //Създаване на клас Календар, където ще се внасят датитие и взимат
protected:
    int day;
    int month;
    int year;
    //Сложил съм protected за да мога да ги използвам в наследяване в кода
public:
    //Създаване на конструктор с параметри и на празен конструктор
    Calendar(int aDay, int aMonth, int aYear) {
        day = aDay;
        month = aMonth;
        year = aYear;
    }
    Calendar() {

    }
    //get и set методи за да можем да взимаме и сетваме датите 
    void setDay(int aDay) {
        day=aDay;
    }
    int getDay() {
        return day;
    }

    void setMonth(int aMonth) {
        month = aMonth;
    }
    int getMonth() {
        return month;
    }

    void setYear(int aYear) {
        year = aYear;
    }
    int getYear() {
        return year;
    }
};
//Съзадаване на клас Студент който наследява класа Календар, където се записва датата на раждане на студент
class Student : public Calendar {
private:
    string name;
    long fNom;
    double avgMark;
public:
    //Създаване на конструктор Студент където се Внасят име, факултетен номер, средна оценка и дата на раждане(чрез класа календар)
    Student(string aName, long aFnom, double aAvgMark, int aDay,int aMonth,int aYear) :Calendar(day,month,year) {
        name = aName;
        fNom = aFnom;
        avgMark = aAvgMark;
        day = aDay;
        month = aMonth;
        year = aYear;
    }
    Student() {

    }
    //get и set методи за студента за сетване и връщане данни за определния студент
    void setName(string aName) {
        name = aName;
    }
    string getName() {
        return name;
    }

    void setFnom(long aFnom) {
        fNom = aFnom;
    }
    long getFnom() {
        return fNom;
    }

    void setAvgMark(int aAvgMark) {
        avgMark = aAvgMark;
    }
    double getAvgMark() {
        return avgMark;
    }
    //предефиниране на << и >> за записване и четене от файл
    friend istream& operator >> (istream& instudent, Student& obj);
    friend ostream& operator <<(ostream& outstudent, const Student& obj);
};

//предефиниране на << и >> за записване и четене от файл
istream& operator >> (istream& instudent, Student& obj) {
    instudent >> obj.name;
    instudent >> obj.fNom;
    instudent >> obj.avgMark;
    instudent >> obj.day;
    instudent >> obj.month;
    instudent >> obj.year;
    return instudent;
}
ostream& operator <<(ostream& outstudent, const Student& obj) {

    outstudent << obj.name << "\n" << obj.fNom << "\n" << obj.avgMark
        << "\n" << obj.day << "\n" << obj.month << "\n" << obj.year << "\n";
    return outstudent;
}

//метод addStudent(), този метод се използва за добавяне на нови студенти, които ще бъдат записани във файл с име "Students.txt"
void addStudent() {
    string name;
    long fnom;
    double avgMark;
    int birthday;
    int birthmonth;
    int birthyear;
    
    //Създаване на studentsFile където ще бъдат записвани данните за студентите
    ofstream studentsFile;
    studentsFile.open("Students.txt", ios_base::app);
    
    cout << "Please input Student name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');//fflush() cisti memorijutu da se ne baguje tekstat
    getline(cin, name);
    while (true) {
        //проверка за внасяне на факултетен номер на студента който трябва да е 8-цифрен
        cout << "Please input Student faculty number (8 digits): ";
        cin>> fnom;
        if (fnom <= 99999999 && fnom >= 10000000) break;
    }
    while (true) {
        //проверка за среден успех на студента и да ли е в рамките на възможните оценки относно 2-6
        cout << "Please input Student average mark: ";
        cin >> avgMark;
        if (avgMark <= 6 && avgMark >= 2) break;
    }
    while (true) {
        //проверка за година ан раждане на студента, да ли е достатъчно стар 
        cout << "Please input Student birth year: ";
        cin >> birthyear;
        if (birthyear >= 1900 && birthyear <= 2005) break;
    }
    while(true) {
        //проверка за месец на раждане на студента, да ли е в рамките от януари до декември
        cout << "Please input Student birth month: ";
        cin >> birthmonth;
        if (birthmonth < 13 && birthmonth > 0) break;
    } 
    while (true)
    {
        //проверка за ден на раждане ена студента, да ли е в рамките на броя на дните в определените месеци
        cout << "Please input Student birth day: ";
        cin >> birthday;
        if (birthmonth == 1 || birthmonth == 3 || birthmonth == 5 || birthmonth == 8 || birthmonth == 10 || birthmonth == 12) {
            if (birthday < 32 && birthday>0) break;
        }
        else if (birthmonth == 4 || birthmonth == 6 || birthmonth == 7 || birthmonth == 9 || birthmonth == 11) {
            if (birthday < 31 && birthday>0) break;
        }
        else if (birthmonth == 2) {
            if (birthday < 29 && birthday>0) break;
        }
    }
    //добавяне и записване на студента във файл
    Student student(name,fnom,avgMark,birthday,birthmonth,birthyear);
    studentsFile << student;
}

//Четене студенти от файл и записване във вектор
vector <Student> readStudents() {
    //string променливи за четене от файл
    string name; 
    string strAvgmark;
    string strFnomer;
    string strDay;
    string strMonth;
    string strYear;
    //променливи които се използват за създаване на Student обект
    float avgmark;
    long fnomer;
    int year;
    int month;
    int day;
    vector <Student> vecStudents;
    //отваряне на файл за четене "Students.txt"
    ifstream studentsFile;
    studentsFile.open("Students.txt");

    while (true) {
        if (studentsFile.eof()) //проверка да чете докато не е EOF
            break;
        //четене на данните за студентите line by line и записване в променливи
        getline(studentsFile, name, '\n');
        getline(studentsFile, strFnomer, '\n');
        getline(studentsFile, strAvgmark, '\n');
        getline(studentsFile, strDay, '\n');
        getline(studentsFile, strMonth, '\n');
        getline(studentsFile, strYear, '\n');
        //конвертиране на стрингове във съответните променливи long, float, int
        fnomer = stol(strFnomer);
        avgmark = stof(strAvgmark);
        day = stoi(strDay);
        month = stoi(strMonth);
        year = stoi(strYear);
        //създаване на студент обект със задаване на данни
        Student tempStudent(name, fnomer, avgmark, day, month, year);
        //вкарване на създадения студенти във вектор от тип Student
        vecStudents.push_back(tempStudent);
    }
    //изтриване на последен елемент от вектор, поради EOF
    vecStudents.pop_back();
    //затваряне на studentsFile
    studentsFile.close();
    return vecStudents;
}
//метод за извеждане на студенти които са между 18 и 26 години
void getStudentByYear(int dd, int mm, int yyyy) {
    readStudents();//функция за четене от файл
    for (Student student : readStudents()) { //for цикъл за проверка за всеки студент от файла
        if (yyyy-student.getYear() > 18 && yyyy- student.getYear() < 26) {
            int yearsold=yyyy-student.getYear();//брой на годините на студента
            if (student.getMonth() > mm || (student.getMonth() == mm && student.getDay() > dd))
                yearsold = yearsold - 1; //проверка за броя на годините спрямо месец и ден
            cout << "Student name: " << student.getName() << endl;
            cout << "Student faculty number: " << student.getFnom() << endl;
            cout << "Student average mark: " << student.getAvgMark() << endl;
            cout << "Student date of birth: " << student.getDay() << "/" << student.getMonth() << "/" << student.getYear()<<endl;
            cout << student.getName() << " is " << yearsold << " old.\n"<<endl;
         
        }
        //проверка за години на 18-годишни спрямо месец и ден на раждане
        else if (yyyy- student.getYear() == 18) {
            if (student.getMonth() < mm || (student.getMonth() == mm && student.getDay() <= dd)) {
                cout << "Student name: " << student.getName() << endl;
                cout << "Student faculty number: " << student.getFnom() << endl;
                cout << "Student average mark: " << student.getAvgMark() << endl;
                cout << "Student date of birth: " << student.getDay() << "/" << student.getMonth() << "/" << student.getYear() << endl;
                cout << student.getName() << " is " << yyyy - student.getYear() << " old.\n"<<endl;
            }
        }
        //проверка за години на 26-годишни спрямо месец и ден на раждане
        else if (yyyy- student.getYear() == 26) {
            if (student.getMonth() > mm|| (student.getMonth() == mm && student.getDay() >= dd)) {
                cout << "Student name: " << student.getName() << endl;
                cout << "Student faculty number: " << student.getFnom() << endl;
                cout << "Student average mark: " << student.getAvgMark() << endl;
                cout << "Student date of birth: " << student.getDay() << "/" << student.getMonth() << "/" << student.getYear() << endl;
                cout << student.getName() << " is " << yyyy - student.getYear() << " old.\n"<<endl;
            }
        }
    }
}
//изписване на всички студенти които са във файл
void showAllStudents() {
    readStudents();
    for (Student student : readStudents()) {
        cout << "Student name: " << student.getName() << endl;
        cout << "Student faculty number: " << student.getFnom() << endl;
        cout << "Student average mark: " << student.getAvgMark() << endl;
        cout << "Student date of birth: " << student.getDay() << "/" << student.getMonth() << "/" << student.getYear() <<"\n"<< endl;
    }
}
//изписване на всички студенти и тяхните години
void getStudentsYearOld(int dd, int mm, int yyyy) {
    readStudents();
    int yearsOld=0;
    for (Student student : readStudents()) {
        yearsOld=yyyy - student.getYear();
        //проверка за години за студентите спрямо годниа на раждане, месец и ден
        if (student.getMonth() > mm||(student.getMonth() == mm && student.getDay() > dd))
            yearsOld = yearsOld - 1;
        cout << "Student name: " << student.getName() << endl;
        cout << "Student faculty number: " << student.getFnom() << endl;
        cout << "Student average mark: " << student.getAvgMark() << endl;
        cout << "Student date of birth: " << student.getDay() << "/" << student.getMonth() << "/" << student.getYear() << endl;
        cout << student.getName() << " is " <<yearsOld << " old.\n" << endl;
    }
}
//изписване на студент/студенти с най-голяма средна оценка 
void getBestAvgMarkStudent() {
    float bestMark=0;
    vector <Student> bestStudent;
    readStudents();
    //for цикъл за проверка за всички студенти във файла
    for (Student student : readStudents()) {
        if (student.getAvgMark() > bestMark) {
            //проверка ако е средната оценка на студента по-голяма от текущата най-голяма оценка
            bestStudent.clear();
            bestMark = student.getAvgMark();
            bestStudent.push_back(student);
        }
        //проверка ако е средната оценка на студента равна на текущата най-голяма оценка
        else if (student.getAvgMark() == bestMark) {
            bestStudent.push_back(student);
        }
    }
    //изписване на студенти с най-голяма средна оценка
    for (Student bestStudent : bestStudent) {
        cout << "Student name: " << bestStudent.getName() << endl;
        cout << "Student faculty number: " << bestStudent.getFnom() << endl;
        cout << "Student average mark: " << bestStudent.getAvgMark() << endl;
        cout << "Birth date: " << bestStudent.getDay() << "/" << bestStudent.getMonth() << "/" << bestStudent.getYear() << endl;
        cout << "***CONGRATULATION!***" << endl;
    }
}

int main()
{
    int day;
    int month;
    int year;
    int choice=99;

    cout << "Please input today date.\n";
    //записване на днешна дата
    cout << "Today day: ";
    cin >> day;
    cout << "Today month: ";
    cin >> month;
    cout << "Today year: ";
    cin >> year;
    cout << "Date: " << day << "/" << month << "/" << year << endl;
    
    while (choice != 0) {
        cout << "1. Add new student\n";
        cout << "2. Show students older then 18 but younger then 26\n";
        cout << "3. Show all students years old\n";
        cout << "4. Show best students\n";
        cout << "9. Show all students\n";
        cout << "0. Exit\n";
        cout << "\nChoise: ";
        cin >> choice;
        cout << "\n\n";
        if (choice == 1) {
            addStudent();
        }
        if (choice == 2) {
            getStudentByYear(day, month, year);
        }
        if (choice == 3) {
            getStudentsYearOld(day, month, year);
        }
        if (choice == 4) {
            getBestAvgMarkStudent();
        }
        if (choice == 9) {
            showAllStudents();
        }
    }
}
