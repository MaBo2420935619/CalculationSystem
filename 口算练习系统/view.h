#pragma once
#pragma once
#include<iostream>
#include<string>
#include<conio.h>
using namespace std;
void welcomeView();//系统初始化欢迎页面

int initView();
void loginView();//注册页面
void registerView(); //注册页面
void mainView(string name); //主页面
void choiseError();//选择错误提示页面
void startAnswerView();//开始答题页面
void  exitOrLogOutView(string name);//注销登录或者退出选择页面
void answerView(string name, int score, int titleNumber, int lastTitleScore, int time);//答题分数提示页面
void chioseTitleNumberView(string name);//选择题目数量提示页面
void stop();//暂停页面




bool isNumber(char num);//判断输入类型是否为数字

void welcomeView() {
	cout << "************************************************************************************" << endl;
	cout << "******************************欢迎使用数学口算练习系统******************************" << endl;
	cout << "************************************************************************************" << endl;
	cout << endl;

}
bool isNumber(char num) {
	bool isNumber = false;
	if ((num >= 'a'&&num <= 'z') || (num >= 'A'&&num <= 'Z')) {
		isNumber = false;
	}
	else if (num >= '0'&&num <= '9') {
		isNumber = true;
	}
	else {
		isNumber = false;
	}

	return isNumber;
}
void loginView() {
	cout << "                 " << "请选择输入用户名和密码——>" << endl;
	cout << "                 " << "输入按回车键结束" << endl;

}
void registerView() {
	cout << "                 " << "请依次输入用户名、密码、年级（数字）、学校——>" << endl;
	cout << "                 " << "输入按回车键结束" << endl;

}
void mainView(string name) {
	welcomeView();
	cout << "      " << "当前用户为：" ;
	cout << name;
	cout << endl;
	cout << "                 " << "请选择数字——>" << endl;
	cout << "                 " << "输入按回车键结束" << endl;
	cout << "                                    " << "1.开始答题" << endl;
	cout << "                                    " << "2.查看" << endl;
	cout << "                                    " << "3.注销登录或退出程序" << endl;
}
void lookHistoryView(string name) {
	welcomeView();
	cout << "      " << "当前用户为：";
	cout << name;
	cout << endl;
	cout << "                 " << "请选择数字——>" << endl;
	cout << "                 " << "输入按回车键结束" << endl;
	cout << "                                    " << "1.查看个人答题历史" << endl;//个人历史答题记录
	cout << "                                    " << "2.查看排行榜" << endl;
}
void choiseError() {
	cout << "                                    " << "\033[32m请重新输入正确合法的内容\033[0m" << endl;
}
void startAnswerView() {
	cout << "        " << "\033[32m请开始答题\033[0m" << endl;
	cout << "        " << "\033[32m输入按回车键结束\033[0m" << endl;
}
void  exitOrLogOutView(string name) {
	welcomeView();
	cout << "      " << "当前用户为：";
	cout << name;
	cout << endl;
	cout << "                 " << "请选择数字——>" << endl;
	cout << "                 " << "输入按回车键结束" << endl;
	cout << "                                    " << "1.注销当前用户" << endl;//个人历史答题记录
	cout << "                                    " << "2.退出程序" << endl;
}
void answerView(string name ,int score,int titleNumber,int lastTitleScore,int time) {
	cout << "      " << "当前用户为：" <<name<< "       累计得分：" << score<<"       累计用时"<<time<<endl;
	cout << endl;
	cout << "      " << "当前题号："<< titleNumber << "       上一题得分：" << lastTitleScore << endl;
}
void chioseTitleNumberView(string name) {
	cout << "      " << "当前用户为：" << name << endl;
	cout << "                 " << "请依次输入题目数量——>" << endl;
	cout << "                 " << "输入按回车键结束" << endl;
}
void querySuccess() {
	cout << "      " << "登录成功" << endl;
}

void stop() {
	int a;
	//cout << "                 " << "按任意键继续" << endl;
	system("pause");
}