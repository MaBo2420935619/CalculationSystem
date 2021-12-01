#pragma once
#include <string>
using namespace std;
class Student {
private:
	string name;
	string pwd;
	int grade;
	string school;
	int bestScore;
public:
	
	/*string getName(string &sname) {
		sname = name;
		return sname;
	}

	string getPwd() {
		return pwd;
	}

	int getGrade() {
		return grade;
	}

	string getSchool() {
		return school;
	}

	int getBestScore() {
		return bestScore;
	}*/

	void setName(string sname) {
		name = sname;
	}
	void setPwd(string spwd) {
		pwd = spwd;
	}
	void setGrade(int  sgrade) {
		grade = sgrade;
	}
	void setSchool(string sschool) {
		school = sschool;
	}
	void setBestScore(int  sbestScore) {
		bestScore = sbestScore;
	}
	Student() {

	}
	Student(string sname, string spwd, int sgrade, string sschool) {
		name = sname;
		pwd = spwd;
		grade = sgrade;
		school = sschool;
	}
};