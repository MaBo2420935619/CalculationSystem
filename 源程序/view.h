#pragma once
#pragma once
#include<iostream>
#include<string>
#include<conio.h>
using namespace std;
void welcomeView();//ϵͳ��ʼ����ӭҳ��

int initView();
void loginView();//ע��ҳ��
void registerView(); //ע��ҳ��
void mainView(string name); //��ҳ��
void choiseError();//ѡ�������ʾҳ��
void startAnswerView();//��ʼ����ҳ��
void  exitOrLogOutView(string name);//ע����¼�����˳�ѡ��ҳ��
void answerView(string name, int score, int titleNumber, int lastTitleScore, int time);//���������ʾҳ��
void chioseTitleNumberView(string name);//ѡ����Ŀ������ʾҳ��
void stop();//��ͣҳ��




bool isNumber(char num);//�ж����������Ƿ�Ϊ����

void welcomeView() {
	cout << "************************************************************************************" << endl;
	cout << "******************************��ӭʹ����ѧ������ϰϵͳ******************************" << endl;
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
	cout << "                 " << "��ѡ�������û��������롪��>" << endl;
	cout << "                 " << "���밴�س�������" << endl;

}
void registerView() {
	cout << "                 " << "�����������û��������롢�꼶�����֣���ѧУ����>" << endl;
	cout << "                 " << "���밴�س�������" << endl;

}
void mainView(string name) {
	welcomeView();
	cout << "      " << "��ǰ�û�Ϊ��" ;
	cout << name;
	cout << endl;
	cout << "                 " << "��ѡ�����֡���>" << endl;
	cout << "                 " << "���밴�س�������" << endl;
	cout << "                                    " << "1.��ʼ����" << endl;
	cout << "                                    " << "2.�鿴" << endl;
	cout << "                                    " << "3.ע����¼���˳�����" << endl;
}
void lookHistoryView(string name) {
	welcomeView();
	cout << "      " << "��ǰ�û�Ϊ��";
	cout << name;
	cout << endl;
	cout << "                 " << "��ѡ�����֡���>" << endl;
	cout << "                 " << "���밴�س�������" << endl;
	cout << "                                    " << "1.�鿴���˴�����ʷ" << endl;//������ʷ�����¼
	cout << "                                    " << "2.�鿴���а�" << endl;
}
void choiseError() {
	cout << "                                    " << "\033[32m������������ȷ�Ϸ�������\033[0m" << endl;
}
void startAnswerView() {
	cout << "        " << "\033[32m�뿪ʼ����\033[0m" << endl;
	cout << "        " << "\033[32m���밴�س�������\033[0m" << endl;
}
void  exitOrLogOutView(string name) {
	welcomeView();
	cout << "      " << "��ǰ�û�Ϊ��";
	cout << name;
	cout << endl;
	cout << "                 " << "��ѡ�����֡���>" << endl;
	cout << "                 " << "���밴�س�������" << endl;
	cout << "                                    " << "1.ע����ǰ�û�" << endl;//������ʷ�����¼
	cout << "                                    " << "2.�˳�����" << endl;
}
void answerView(string name ,int score,int titleNumber,int lastTitleScore,int time) {
	cout << "      " << "��ǰ�û�Ϊ��" <<name<< "       �ۼƵ÷֣�" << score<<"       �ۼ���ʱ"<<time<<endl;
	cout << endl;
	cout << "      " << "��ǰ��ţ�"<< titleNumber << "       ��һ��÷֣�" << lastTitleScore << endl;
}
void chioseTitleNumberView(string name) {
	cout << "      " << "��ǰ�û�Ϊ��" << name << endl;
	cout << "                 " << "������������Ŀ��������>" << endl;
	cout << "                 " << "���밴�س�������" << endl;
}
void querySuccess() {
	cout << "      " << "��¼�ɹ�" << endl;
}

void stop() {
	int a;
	//cout << "                 " << "�����������" << endl;
	system("pause");
}