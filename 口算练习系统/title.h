#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include<random>

int getRandm(int max, int min); //用来生成随机数在[b,a]区间内
int operationSymbol(bool multy);//随机生成true或false
string toString(int n);   //将int 类型数据转为string类型
int toInt(string a);      //将string 类型数据转为int 类型
int getRandm(int max,int min) {       //用来生成随机数在[b,a]区间内
	std::random_device rd;
	std::mt19937 mt(rd());
	/*for (int n = 0; n < 10; n++)
		std::cout << mt() << std::endl;*/
	int random_val = mt();//用来存放随机数
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
