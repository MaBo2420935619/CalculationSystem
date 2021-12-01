#pragma warning(disable:4996)
#include"view.h"
#include"userdao.h"
#include"title.h"
#define HightMax 10 
#define HightMin 1
#define LowMax 5
#define LowMin 1
#define LimitTime 200
bool loginOn = false;
string name;
int timeUsed = 0;
DWORD threadID;
HANDLE hThread;
bool isAnswer = true;
//��������
void initSystem();    //ϵͳ��ʼ�������������֤ģ��
void mainSystem();     //ϵͳ��ģ��
void lookHistory();    //�鿴ģ��
void exitOrLogOut();    //�˳���ע��ģ��������Ŀ����
void getTitle(string name, int n, int m, int level);      //������Ŀ(string �û���, int ������������Ŀ����,int �������,int �û������Ѷ�)
void startAnswer(string name);//��ʼ����ǰѡ����Ŀ����
int isGrade(string grade);   //ע��ʱ���꼶�Ƿ��ǷǷ��ַ�������֤
int initView();        //�����֤�Ľ���
DWORD WINAPI getMsg(LPVOID lpParam);//��ʱ���߳�



int main() {
	initSystem();
	/*lookFirstlGrade();*/
	/*exitOrLogOut();*/
	/*getTitle("mr",10, 3, 3);*/
	/*selectMaxFreq("mr");*/
	/*cout<<getBestGrade("mr");*/
	//setFreqScore("sda",79,1);
	

	
	

	return 0;
}
void initSystem() {
	clearAll();
	int initViewReturn = initView();
	if (initViewReturn == 1) {
		cout << "                                    " << "�������û���" << endl;
		cin >> name;
		cout << "                                    " << "����������" << endl;
		string pwd;
		cin >> pwd;
		connectDatabase();
		loginOn = loginDao(name, pwd);
		if (loginOn) {
			/*cout << "����������" << endl;*/
			mainSystem();
		}
		else
		{
			/*cout << "                                    " << "��¼ʧ��" << endl;*/
			stop();
			initSystem();
		}

	}
	if (initViewReturn == 2) {
		cout << "                                    " << "�������û���" << endl;
		cin >> name;
		cout << "                                    " << "����������" << endl;
		string pwd;
		cin >> pwd;
		string ggrade;
		cout << "                                    " << "�������꼶1-6�����֣�" << endl;
		cin >> ggrade;
		int grade;
		grade = isGrade(ggrade);
		string school;
		cout << "                                    " << "����������ѧУ����" << endl;
		cin >> school;
		if (registerDao(name, pwd, grade, school)) {
			cout << "                                    " << "ע��ɹ�" << endl;
			stop();
			/*cout << "����������" << endl;*/
			mainSystem();
			
		}
		else
		{
			cout << "                                    " << "ע��ʧ��" << endl;
			cout << "                                    " << "��������Ƿ��ַ�" << endl;
			stop();
			initSystem();
		}
	}
	else
	{
		initSystem();
	}
}
void mainSystem() {
	
	TerminateThread(hThread, threadID);
	isAnswer = true;
	clearAll();
	mainView(name);
	string nnum;
	cin >> nnum;
	int num = toInt(nnum);
	if (num == 1) {
		/*cout << "�������" << endl;*/
		startAnswer(name);
	}
	else if (num == 2) {
		lookHistory();
	}
	else if (num == 3) {
		exitOrLogOut();
	}
	else
	{
		choiseError();
		stop();
		mainSystem();
	}
	
}
void lookHistory() {
	clearAll();
	lookHistoryView(name);
	string nnum;
	cin >> nnum;
	int num = toInt(nnum);
	if (num == 1) {
		lookPersonalHistory(name);
		stop();
	}
	else if (num ==2) {
		lookFirstlGrade();
		stop();
	}
	else
	{
		choiseError();
		stop();
	}
	mainSystem();
}
void exitOrLogOut() {
	clearAll();
	exitOrLogOutView(name);
	string nnum;
	cin >> nnum;
	int num = toInt(nnum);
	if (num == 1) {
		initSystem();
	}
	else if (num == 2) {
		exit(0);
	}
	else
	{
		choiseError();
		stop();
		exitOrLogOut();
	}

}
void startAnswer(string name) {
	chioseTitleNumberView(name);
	cout << "                 " << "�������������:" << endl;
	string n ;
	string m;
	cin >> n;
	int nn = toInt(n);
	cout << "                 " << "��������������:" << endl;
	cin >> m;
	int mm = toInt(m);
	if (nn > 0&&mm>0) {
		
		getTitle(name, nn, mm, getUserLevel(name));
	}
	else
	{
		choiseError();
	}
	mainSystem();
}
void getTitle(string name, int n, int m, int level) {//����������Ŀ
	hThread = CreateThread(NULL, 0, getMsg, NULL, 0, &threadID);//��ʼ��ʱ
	int num = level + 1;
	int max;
	int min;
	int score = 100;
	int titleNumber = 1;
	int lastTitleScore = 0;
	int freqMax = 0;
	int bestScore =getBestGrade(name);
	if (selectMaxFreq(name) != NULL) {
		freqMax = selectMaxFreq(name);//��ʾ�������
	}
	welcomeView();
	freqMax++;
	if (num == 2) {
		max =LowMax;
		min =LowMin;
	}
	if (num == 3 || num == 4) {
		max = HightMax;
		min = HightMin;
	}
	//��������㿪ʼ
	for (int i = 0; i < n; i++) {
		if (isAnswer) {
			startAnswerView();
			answerView(name, score, titleNumber, lastTitleScore, timeUsed);
			int number[5];
			//����level+1�������
			for (int j = 0; j < num + 1; j++) {
				number[j] = getRandm(max, min);

			}
			/*
			�Ӽ��˳�����˼·
			���������ֹ�������������ɼӷ��任
			���������ֹ�������ɳ˷��任

			*/
			if (level == 1) {
				string result = "-1";
				if (operationSymbol(false)) {
					/*answerView();*/
					cout << "      " << number[0] << " + " << number[1] << endl;
					cout << "      ��������ȷ��";
					cin >> result;
					int rs = atoi(result.c_str());

					if (rs == (number[0] + number[1])) {
						score += 5, lastTitleScore = 5;
					}
					else
					{
						score -= 5, lastTitleScore = -5;
					}
				}
				else
				{
					int rss = number[0] + number[1];

					cout << "      " << rss << " - " << number[1] << endl;
					cout << "      ��������ȷ��";
					cin >> result;
					int rs = atoi(result.c_str());

					if (rs == number[0]) {
						score += 5, lastTitleScore = 5;
					}
					else
					{
						score -= 5, lastTitleScore = -5;
					}
				}
			}//����Ѷȵȼ�Ϊ2
			if (level == 2) {
				string result = "-1";
				bool opSympl[2];
				bool flag = false;
				if (operationSymbol(false)) {//�Ƿ�Ϊ�Ӽ���
					flag = true;
				}
				if (flag) {
					if (operationSymbol(false)) {//�ӷ�����
						int rss = number[0] + number[1];
						number[0] = rss - number[1] + number[2];
						cout << "      " << rss << " + " << number[2] << " - " << number[1] << endl;
						cout << "      ��������ȷ��";
						cin >> result;
						int rs = atoi(result.c_str());

						if (rs == number[0]) {
							score += 5, lastTitleScore = 5;
						}
						else
						{
							score -= 5, lastTitleScore = -5;
						}
					}
					else//��������
					{
						int rss = number[0] + number[1];
						number[0] = rss - number[1] + number[2];
						cout << "      " << rss << " - " << number[1] << " + " << number[2] << endl;
						cout << "      ��������ȷ��";
						cin >> result;
						int rs = atoi(result.c_str());

						if (rs == number[0]) {
							score += 5, lastTitleScore = 5;
						}
						else
						{
							score -= 5, lastTitleScore = -5;
						}
					}
				}
				else//�˳�������
				{
					if (operationSymbol(false)) {//�˷�����
						int rss = number[0] * number[1];
						number[0] = rss / number[1] * number[2];

						cout << "      " << rss << " * " << number[2] << " / " << number[1] << endl;
						cout << "      ��������ȷ��";
						cin >> result;
						int rs = atoi(result.c_str());

						if (rs == number[0]) {
							score += 5, lastTitleScore = 5;
						}
						else
						{
							score -= 5, lastTitleScore = -5;
						}
					}
					else//��������
					{
						int rss = number[0] * number[1];
						number[0] = rss / number[1] * number[2];
						cout << "      " << rss << " / " << number[1] << " * " << number[2] << endl;
						cout << "      ��������ȷ��";
						cin >> result;
						int rs = atoi(result.c_str());

						if (rs == number[0]) {
							score += 5, lastTitleScore = 5;
						}
						else
						{
							score -= 5, lastTitleScore = -5;
						}
					}
				}
			}
			if (level == 3) {
				string result = "-1";
				bool f = false;
				if (operationSymbol(false)) {//�Ƿ�Ϊ�Ӽ���
					f = true;
				}
				if (f) {
					int rss1 = number[0] + number[1];
					int rss2 = number[2] + number[3];
					int rss = rss1 - number[1] + rss2 - number[3];
					int flag = operationSymbol(true);
					if (flag == 0) {//�ӷ�����
						cout << "      " << rss1 << " - " << number[1] << " + " << rss2 << " - " << number[3] << endl;
					}
					if (flag == 1)//��������
					{
						cout << "      " << rss1 << " - " << number[1] << " - " << number[3] << " + " << rss2 << endl;

					}
					if (flag == 2 || flag == 3 || flag == 4)//��������
					{
						cout << "      " << rss1 << " + " << rss2 << " - " << number[1] << " - " << number[3] << endl;

					}
					cout << "      ��������ȷ��";
					cin >> result;
					int rs = atoi(result.c_str());

					if (rs == rss) {
						score += 5, lastTitleScore = 5;
					}
					else
					{
						score -= 5, lastTitleScore = -5;
					}
				}
				else//�˳�������
				{
					int rss1 = number[0] * number[1];
					int rss2 = number[2] * number[3];
					number[0] = rss1 / number[1];
					number[2] = rss2 / number[3];
					int rss = rss1 / number[1] * rss2 / number[3];
					int f = operationSymbol(true);
					if (f == 0) {
						cout << "      " << rss1 << " / " << number[1] << " * " << rss2 << " / " << number[3] << endl;


					}
					if (f == 1)
					{
						cout << "      " << rss1 << " * " << rss2 << " / " << number[3] << " / " << number[1] << endl;

					}
					if (f == 2 || f == 3 || f == 4)
					{
						cout << "      " << rss1 << " / " << number[3] << " / " << number[1] << " * " << rss2 << endl;
					}
					cout << "      ��������ȷ��";
					cin >> result;
					int rs = atoi(result.c_str());

					if (rs == rss) {
						score += 5, lastTitleScore = 5;
					}
					else
					{
						score -= 5, lastTitleScore = -5;
					}
				}
			}

			setPracticeInfo(name, titleNumber, lastTitleScore, score, freqMax, timeUsed);
			titleNumber++;
		}
		else
		{
			TerminateThread(hThread, threadID);
		}
	}
	//���������㿪ʼ
	for (int i = 0; i < m; i++) {
		if (isAnswer) {
			startAnswerView();
			answerView(name, score, titleNumber, lastTitleScore, timeUsed);
			int number[5];
			//����level+1�������
			for (int j = 0; j < num + 1; j++) {
				number[j] = getRandm(max, min);

			}
			/*
			�Ӽ��˳�����˼·
			���������ֹ�������������ɼӷ��任
			���������ֹ�������ɳ˷��任

			*/

			if (level == 1) {
				string result = "-1";
				bool opSympl[2];
				bool flag = false;
				if (operationSymbol(false)) {//�ӷ�����
					int rss = number[0] + number[1];
					number[0] = rss - number[1] + number[2];
					cout << "      " << rss << " + " << number[2] << " - " << number[1] << endl;
					cout << "      ��������ȷ��";
					cin >> result;
					int rs = atoi(result.c_str());

					if (rs == number[0]) {
						score += 10, lastTitleScore = 10;
					}
					else
					{
						score -= 10, lastTitleScore = -10;
					}
				}
				else//��������
				{
					int rss = number[0] + number[1];
					number[0] = rss - number[1] + number[2];
					cout << "      " << rss << " - " << number[1] << " + " << number[2] << endl;
					cout << "      ��������ȷ��";
					cin >> result;
					int rs = atoi(result.c_str());

					if (rs == number[0]) {
						score += 10, lastTitleScore = 10;
					}
					else
					{
						score -= 10, lastTitleScore = -10;
					}
				}

			}
			else if (level == 2) {
				string result = "-1";
				bool flag = false;
				if (operationSymbol(false)) {//�Ӽ�������

					int rss1 = number[0] + number[1];
					int rss2 = number[2] * number[3];
					number[2] = rss2 / number[3];
					/*number[0] = rss1 - number[1];*/
					if (operationSymbol(false)) {//�ӷ�����
						if (operationSymbol(false)) {//�˷�����
							cout << "      " << number[0] << " + " << number[1] << " * " << number[2] << endl;
							cout << "      ��������ȷ��";
							cin >> result;
							int rs = atoi(result.c_str());
							if (rs == rss1) {
								score += 10, lastTitleScore = 10;
							}
							else
							{
								score -= 10, lastTitleScore = -10;
							}
						}
						else
						{
							cout << "      " << number[0] << " + " << rss2 << " / " << number[3] << endl;
							cout << "      ��������ȷ��";
							cin >> result;
							int rs = atoi(result.c_str());
							if (rs == number[0] + number[2]) {
								score += 10, lastTitleScore = 10;
							}
							else
							{
								score -= 10, lastTitleScore = -10;
							}
						}
					}
					else//��������
					{
						int rss4 = number[2] * number[3];
						int rss3 = number[0] + rss4;

						number[3] = rss4 / number[2];
						number[0] = rss3 - rss4;
						if (operationSymbol(false)) {//�˷�����
							cout << "      " << rss3 << " - " << number[2] << " * " << number[3] << endl;
							cout << "      ��������ȷ��";
							cin >> result;
							int rs = atoi(result.c_str());
							if (rs == number[0]) {
								score += 10, lastTitleScore = 10;
							}
							else
							{
								score -= 10, lastTitleScore = -10;
							}
						}
						/*int rss4 = number[2] * number[3];
						int rss3 = number[0] + rss4;

						number[3] = rss4 / number[2];
						number[0] = rss3 - rss4;*/
						/*= number[0] - rss4 / number[2];*/
						else//�������Ⱥ��������
						{
							cout << "      " << number[0] + number[3] << " - " << rss4 << " / " << number[2] << endl;
							cout << "      ��������ȷ��";
							cin >> result;
							int rs = atoi(result.c_str());
							if (rs == number[0]) {
								score += 10, lastTitleScore = 10;
							}
							else
							{
								score -= 10, lastTitleScore = -10;
							}
						}

					}


				}
				else//�˳�����
				{
					int rss1 = number[0] + number[1];
					int rss2 = number[2] * number[3];

					if (operationSymbol(false)) {//�˷�����
						if (operationSymbol(false)) {//�ӷ�����
							cout << "      " << number[2] << " * " << number[3] << " + " << number[0] << endl;
							cout << "      ��������ȷ��";
							cin >> result;
							int rs = atoi(result.c_str());
							if (rs == rss2 + number[0]) {
								score += 10, lastTitleScore = 10;
							}
							else
							{
								score -= 10, lastTitleScore = -10;
							}
						}

						else//�˷����ȼ�������
						{
							int rss3 = number[1] + number[2];
							cout << "      " << rss3 << " * " << number[3] << " - " << number[1] * number[3] << endl;
							cout << "      ��������ȷ��";
							cin >> result;
							int rs = atoi(result.c_str());
							if (rs == number[2] * number[3]) {
								score += 10, lastTitleScore = 10;
							}
							else
							{
								score -= 10, lastTitleScore = -10;
							}
						}
					}
					else//��������
					{
						int rss4 = number[2] * number[3];
						int rss3 = number[0] + rss4;

						number[3] = rss4 / number[2];
						number[0] = rss3 - rss4;
						if (operationSymbol(false)) {//�������ȼӷ����� 
							cout << "      " << rss4 << " / " << number[2] << " + " << number[1] << endl;
							cout << "      ��������ȷ��";
							cin >> result;
							int rs = atoi(result.c_str());
							if (rs == number[1] + number[3]) {
								score += 10, lastTitleScore = 10;
							}
							else
							{
								score -= 10, lastTitleScore = -10;
							}
						}

						else//�������ȼ�������
						{
							int reee1 = number[0] * (number[1]+ number[2]);
							number[1] = reee1 / number[0] - number[2];
						
							cout << "      " << reee1 << " / " << number[0]<< " - " << number[2] << endl;
							cout << "      ��������ȷ��";
							cin >> result;
							int rs = atoi(result.c_str());
							if (rs == number[1]) {
								score += 10, lastTitleScore = 10;
							}
							else
							{
								score -= 10, lastTitleScore = -10;
							}
						}

					}
				}

			}
			else if (level == 3) {
				string result = "-1";
				int operSymbol = getRandm(2, 0);
				/*
				a +  b * c  -  d          �൱��  (a+d)   +    b    *   c   -    d
				a +  b / c -    d         �൱�� (a+d)    +   ( b*c)   /     c    -    d
				a -  b * c +  d           �൱��  (a + b * c)   -    b    *    c   +  d
				a -  b / c +	d		  �൱��   (a+b*c/c)   -   (b*c)    /     c    +      d
				a *  b + c / d            �൱��    a     *     b    +    (c*d)    /    d
				a *  b - c / d            �൱��   a *  (b+c)     -   (a*c*d)     /    d
				a / b  + c * d            �൱��   (a*b)    /    b    +   c    *    d
				a / b  - c *  d           �൱��  (a*b)    /     b+(c*d)    -   c    *     d



				*/
				int a = number[0];
				int b = number[1];
				int c = number[2];
				int d = number[3];
				if (operSymbol == 0) {
					//a + b * c - d          �൱��(a + d) + b * c - d
					cout << "      " << (a + d) << " + " << b << " * " << c << " - " << d << endl;
					cout << "      ��������ȷ��";
					cin >> result;
					int rs = atoi(result.c_str());
					if (rs == (a + b * c)) {
						score += 10, lastTitleScore = 10;
					}
					else
					{
						score -= 10, lastTitleScore = -10;
					}
				}
				else if (operSymbol == 1) {
					//a + b / c - d         �൱��(a + d) + (b*c) / c - d
					cout << "      " << (a + d) << " + " << b * c << " / " << c << " - " << d << endl;
					cout << "      ��������ȷ��";
					cin >> result;
					int rs = atoi(result.c_str());
					if (rs == (a + b)) {
						score += 10, lastTitleScore = 10;
					}
					else
					{
						score -= 10, lastTitleScore = -10;
					}
				}
				else if (operSymbol == 2) {
					//	a - b * c + d           �൱��(a + b * c) - b * c + d
					cout << "      " << (a + b * c) << " - " << b << " * " << c << " + " << d << endl;
					cout << "      ��������ȷ��";
					cin >> result;
					int rs = atoi(result.c_str());
					if (rs == (a + d)) {
						score += 10, lastTitleScore = 10;
					}
					else
					{
						score -= 10, lastTitleScore = -10;
					}
				}
				else if (operSymbol == 3) {
					//	a -  b / c +	d		  �൱��   (a+b*c/c)   -   (b*c)    /     c    +      d	
					cout << "      " << (a + b) << " - " << b * c << " / " << c << " + " << d << endl;
					cout << "      ��������ȷ��";
					cin >> result;
					int rs = atoi(result.c_str());
					if (rs == (a + d)) {
						score += 10, lastTitleScore = 10;
					}
					else
					{
						score -= 10, lastTitleScore = -10;
					}
				}
				else if (operSymbol == 4) {
					//	a *  b + c / d            �൱��    a     *     b    +    (c*d)    /    d 
					cout << "      " << a << " * " << b << " + " << c * d << " / " << d << endl;
					cout << "      ��������ȷ��";
					cin >> result;
					int rs = atoi(result.c_str());
					if (rs == (a * d + c)) {
						score += 10, lastTitleScore = 10;
					}
					else
					{
						score -= 10, lastTitleScore = -10;
					}
				}
				else if (operSymbol == 5) {
					//	a *  b - c / d            �൱��   a *  (b+c)     -   (a*c*d)     /    d 
					cout << "      " << a << " * " << (b + c) << " - " << (a*c*d) << " / " << d << endl;
					cout << "      ��������ȷ��";
					cin >> result;
					int rs = atoi(result.c_str());
					if (rs == a * b) {
						score += 10, lastTitleScore = 10;
					}
					else
					{
						score -= 10, lastTitleScore = -10;
					}
				}
				else if (operSymbol == 7) {
					//		a / b  - c *  d           �൱��  a*b*c*d    /    b    -   c    *     d   
					cout << "      " << a * b*c*d << " / " << b << " - " << c << " * " << d << endl;
					cout << "      ��������ȷ��";
					cin >> result;
					int rs = atoi(result.c_str());
					if (rs == (a - 1)*c*d) {
						score += 10, lastTitleScore = 10;
					}
					else
					{
						score -= 10, lastTitleScore = -10;
					}
				}
			}



			setPracticeInfo(name, titleNumber, lastTitleScore, score, freqMax, timeUsed);
			titleNumber++;
		}
		}
		if (!isAnswer) {
			TerminateThread(hThread, threadID);
		}
		
	if (score > bestScore) {
		setBestGrade(name, score);
		
	}
	
	
	setFreqScore(name, score, freqMax);
	timeUsed = 0;
	TerminateThread(hThread, threadID);
	cout << "      �ܹ��÷�:" << score << endl;
	stop();
}
		
int isGrade( string grade) {
	int g = toInt(grade);
	while (!(g <= 6 && g >= 1)) {
		choiseError();
		stop();
		string gg;
		cout << "                                    " << "�������꼶1-6�����֣�" << endl;
		cin >> g;
		int cg = toInt(grade);
		if ((cg <= 6 && cg >= 1)) {
			return cg;
		}
	}
	return g;
	
}

int initView() {
	welcomeView();
	cout << "                 " << "��ѡ�����֡���>" << endl;
	cout << "                 " << "���밴�س�������" << endl;
	cout << "                                    " << "1.��¼" << endl;
	cout << "                                    " << "2.ע��" << endl;

	string nnum;
	cin >> nnum;
	int num = toInt(nnum);
	if (num == 1)
	{
		clearAll();
		//��ת��¼ҳ-�����������֤
		//��ʾ��¼ҳ
		loginView();
		return num;
	}
	else if (num == 2) {
		clearAll();
		//��ע��ҳ-������ע��
		//��ʾע��ҳ
		registerView();
		return num;
	}
	else
	{
		clearAll();
		cout << "                                    " << "\033[32m��ѡ����ȷ��ѡ��\033[0m" << endl;
		stop();
		return 0;

	}

}
DWORD WINAPI getMsg(LPVOID lpParam)
{
	while (1)
	{
		Sleep(1000);
		timeUsed++;
		if (timeUsed >= LimitTime) {
			cout << "                                    " << "\033[32m���ⳬʱ\033[0m" << endl;
			stop();
			timeUsed = 0;
			isAnswer = false;
			mainSystem();
			break;
		}
	}
	return NULL;

}