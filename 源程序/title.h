#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include<random>

int getRandm(int max, int min); //���������������[b,a]������
int operationSymbol(bool multy);//�������true��false
string toString(int n);   //��int ��������תΪstring����
int toInt(string a);      //��string ��������תΪint ����
int getRandm(int max,int min) {       //���������������[b,a]������
	std::random_device rd;
	std::mt19937 mt(rd());
	/*for (int n = 0; n < 10; n++)
		std::cout << mt() << std::endl;*/
	int random_val = mt();//������������
	if (random_val < 0)
		getRandm(max, min);
	else
	{
		return random_val % (max + 1) + min;
	}
	
}
int operationSymbol(bool multy) {
	int result;
	if (multy == true) {
		result=getRandm(4, 0);
	}
	if (multy == false) {
		result = getRandm(2, 0);
	}
	return result;
}

string toString(int n) {

	std::string s = std::to_string(n);
	return s;
}
int toInt(string a){
	int c = atoi(a.c_str());
	return  c;
}
