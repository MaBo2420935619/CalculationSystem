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
//函数声明
void initSystem();    //系统初始化，进入身份验证模块
void mainSystem();     //系统主模块
void lookHistory();    //查看模块
void exitOrLogOut();    //退出或注销模块运算题目数量
void getTitle(string name, int n, int m, int level);      //生成题目(string 用户名, int 简单四则运算题目数量,int 混合四则,int 用户答题难度)
void startAnswer(string name);//开始答题前选择题目数量
int isGrade(string grade);   //注册时对年级是否是非法字符进行验证
int initView();        //身份验证的界面
DWORD WINAPI getMsg(LPVOID lpParam);//计时子线程



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
		cout << "                                    " << "请输入用户名" << endl;
		cin >> name;
		cout << "                                    " << "请输入密码" << endl;
		string pwd;
		cin >> pwd;
		connectDatabase();
		loginOn = loginDao(name, pwd);
		if (loginOn) {
			/*cout << "进入主界面" << endl;*/
			mainSystem();
		}
		else
		{
			/*cout << "                                    " << "登录失败" << endl;*/
			stop();
			initSystem();
		}

	}
	if (initViewReturn == 2) {
		cout << "                                    " << "请输入用户名" << endl;
		cin >> name;
		cout << "                                    " << "请输入密码" << endl;
		string pwd;
		cin >> pwd;
		string ggrade;
		cout << "                                    " << "请输入年级1-6（数字）" << endl;
		cin >> ggrade;
		int grade;
		grade = isGrade(ggrade);
		string school;
		cout << "                                    " << "请输入所在学校名称" << endl;
		cin >> school;
		if (registerDao(name, pwd, grade, school)) {
			cout << "                                    " << "注册成功" << endl;
			stop();
			/*cout << "进入主界面" << endl;*/
			mainSystem();
			
		}
		else
		{
			cout << "                                    " << "注册失败" << endl;
			cout << "                                    " << "请勿输入非法字符" << endl;
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
		/*cout << "进入答题" << endl;*/
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
	cout << "                 " << "四则简单运算数量:" << endl;
	string n ;
	string m;
	cin >> n;
	int nn = toInt(n);
	cout << "                 " << "四则混合运算数量:" << endl;
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
void getTitle(string name, int n, int m, int level) {//用来生成题目
	hThread = CreateThread(NULL, 0, getMsg, NULL, 0, &threadID);//开始计时
	int num = level + 1;
	int max;
	int min;
	int score = 100;
	int titleNumber = 1;
	int lastTitleScore = 0;
	int freqMax = 0;
	int bestScore =getBestGrade(name);
	if (selectMaxFreq(name) != NULL) {
		freqMax = selectMaxFreq(name);//显示答题次数
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
	//四则简单运算开始
	for (int i = 0; i < n; i++) {
		if (isAnswer) {
			startAnswerView();
			answerView(name, score, titleNumber, lastTitleScore, timeUsed);
			int number[5];
			//生形level+1个随机数
			for (int j = 0; j < num + 1; j++) {
				number[j] = getRandm(max, min);

			}
			/*
			加减乘除法的思路
			减法运算防止减不过，可以由加法变换
			除法运算防止除不尽由乘法变换

			*/
			if (level == 1) {
				string result = "-1";
				if (operationSymbol(false)) {
					/*answerView();*/
					cout << "      " << number[0] << " + " << number[1] << endl;
					cout << "      请输入正确答案";
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
					cout << "      请输入正确答案";
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
			}//如果难度等级为2
			if (level == 2) {
				string result = "-1";
				bool opSympl[2];
				bool flag = false;
				if (operationSymbol(false)) {//是否为加减法
					flag = true;
				}
				if (flag) {
					if (operationSymbol(false)) {//加法优先
						int rss = number[0] + number[1];
						number[0] = rss - number[1] + number[2];
						cout << "      " << rss << " + " << number[2] << " - " << number[1] << endl;
						cout << "      请输入正确答案";
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
					else//减法优先
					{
						int rss = number[0] + number[1];
						number[0] = rss - number[1] + number[2];
						cout << "      " << rss << " - " << number[1] << " + " << number[2] << endl;
						cout << "      请输入正确答案";
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
				else//乘除法运算
				{
					if (operationSymbol(false)) {//乘法优先
						int rss = number[0] * number[1];
						number[0] = rss / number[1] * number[2];

						cout << "      " << rss << " * " << number[2] << " / " << number[1] << endl;
						cout << "      请输入正确答案";
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
					else//除法优先
					{
						int rss = number[0] * number[1];
						number[0] = rss / number[1] * number[2];
						cout << "      " << rss << " / " << number[1] << " * " << number[2] << endl;
						cout << "      请输入正确答案";
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
				if (operationSymbol(false)) {//是否为加减法
					f = true;
				}
				if (f) {
					int rss1 = number[0] + number[1];
					int rss2 = number[2] + number[3];
					int rss = rss1 - number[1] + rss2 - number[3];
					int flag = operationSymbol(true);
					if (flag == 0) {//加法优先
						cout << "      " << rss1 << " - " << number[1] << " + " << rss2 << " - " << number[3] << endl;
					}
					if (flag == 1)//减法优先
					{
						cout << "      " << rss1 << " - " << number[1] << " - " << number[3] << " + " << rss2 << endl;

					}
					if (flag == 2 || flag == 3 || flag == 4)//减法优先
					{
						cout << "      " << rss1 << " + " << rss2 << " - " << number[1] << " - " << number[3] << endl;

					}
					cout << "      请输入正确答案";
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
				else//乘除法运算
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
					cout << "      请输入正确答案";
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
	//四则混合运算开始
	for (int i = 0; i < m; i++) {
		if (isAnswer) {
			startAnswerView();
			answerView(name, score, titleNumber, lastTitleScore, timeUsed);
			int number[5];
			//生形level+1个随机数
			for (int j = 0; j < num + 1; j++) {
				number[j] = getRandm(max, min);

			}
			/*
			加减乘除法的思路
			减法运算防止减不过，可以由加法变换
			除法运算防止除不尽由乘法变换

			*/

			if (level == 1) {
				string result = "-1";
				bool opSympl[2];
				bool flag = false;
				if (operationSymbol(false)) {//加法优先
					int rss = number[0] + number[1];
					number[0] = rss - number[1] + number[2];
					cout << "      " << rss << " + " << number[2] << " - " << number[1] << endl;
					cout << "      请输入正确答案";
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
				else//减法优先
				{
					int rss = number[0] + number[1];
					number[0] = rss - number[1] + number[2];
					cout << "      " << rss << " - " << number[1] << " + " << number[2] << endl;
					cout << "      请输入正确答案";
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
				if (operationSymbol(false)) {//加减法优先

					int rss1 = number[0] + number[1];
					int rss2 = number[2] * number[3];
					number[2] = rss2 / number[3];
					/*number[0] = rss1 - number[1];*/
					if (operationSymbol(false)) {//加法优先
						if (operationSymbol(false)) {//乘法优先
							cout << "      " << number[0] << " + " << number[1] << " * " << number[2] << endl;
							cout << "      请输入正确答案";
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
							cout << "      请输入正确答案";
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
					else//减法优先
					{
						int rss4 = number[2] * number[3];
						int rss3 = number[0] + rss4;

						number[3] = rss4 / number[2];
						number[0] = rss3 - rss4;
						if (operationSymbol(false)) {//乘法优先
							cout << "      " << rss3 << " - " << number[2] << " * " << number[3] << endl;
							cout << "      请输入正确答案";
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
						else//减法优先后除法优先
						{
							cout << "      " << number[0] + number[3] << " - " << rss4 << " / " << number[2] << endl;
							cout << "      请输入正确答案";
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
				else//乘除优先
				{
					int rss1 = number[0] + number[1];
					int rss2 = number[2] * number[3];

					if (operationSymbol(false)) {//乘法优先
						if (operationSymbol(false)) {//加法优先
							cout << "      " << number[2] << " * " << number[3] << " + " << number[0] << endl;
							cout << "      请输入正确答案";
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

						else//乘法优先减法优先
						{
							int rss3 = number[1] + number[2];
							cout << "      " << rss3 << " * " << number[3] << " - " << number[1] * number[3] << endl;
							cout << "      请输入正确答案";
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
					else//除法优先
					{
						int rss4 = number[2] * number[3];
						int rss3 = number[0] + rss4;

						number[3] = rss4 / number[2];
						number[0] = rss3 - rss4;
						if (operationSymbol(false)) {//除法优先加法优先 
							cout << "      " << rss4 << " / " << number[2] << " + " << number[1] << endl;
							cout << "      请输入正确答案";
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

						else//除法优先减法优先
						{
							int reee1 = number[0] * (number[1]+ number[2]);
							number[1] = reee1 / number[0] - number[2];
						
							cout << "      " << reee1 << " / " << number[0]<< " - " << number[2] << endl;
							cout << "      请输入正确答案";
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
				a +  b * c  -  d          相当于  (a+d)   +    b    *   c   -    d
				a +  b / c -    d         相当于 (a+d)    +   ( b*c)   /     c    -    d
				a -  b * c +  d           相当于  (a + b * c)   -    b    *    c   +  d
				a -  b / c +	d		  相当于   (a+b*c/c)   -   (b*c)    /     c    +      d
				a *  b + c / d            相当于    a     *     b    +    (c*d)    /    d
				a *  b - c / d            相当于   a *  (b+c)     -   (a*c*d)     /    d
				a / b  + c * d            相当于   (a*b)    /    b    +   c    *    d
				a / b  - c *  d           相当于  (a*b)    /     b+(c*d)    -   c    *     d



				*/
				int a = number[0];
				int b = number[1];
				int c = number[2];
				int d = number[3];
				if (operSymbol == 0) {
					//a + b * c - d          相当于(a + d) + b * c - d
					cout << "      " << (a + d) << " + " << b << " * " << c << " - " << d << endl;
					cout << "      请输入正确答案";
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
					//a + b / c - d         相当于(a + d) + (b*c) / c - d
					cout << "      " << (a + d) << " + " << b * c << " / " << c << " - " << d << endl;
					cout << "      请输入正确答案";
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
					//	a - b * c + d           相当于(a + b * c) - b * c + d
					cout << "      " << (a + b * c) << " - " << b << " * " << c << " + " << d << endl;
					cout << "      请输入正确答案";
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
					//	a -  b / c +	d		  相当于   (a+b*c/c)   -   (b*c)    /     c    +      d	
					cout << "      " << (a + b) << " - " << b * c << " / " << c << " + " << d << endl;
					cout << "      请输入正确答案";
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
					//	a *  b + c / d            相当于    a     *     b    +    (c*d)    /    d 
					cout << "      " << a << " * " << b << " + " << c * d << " / " << d << endl;
					cout << "      请输入正确答案";
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
					//	a *  b - c / d            相当于   a *  (b+c)     -   (a*c*d)     /    d 
					cout << "      " << a << " * " << (b + c) << " - " << (a*c*d) << " / " << d << endl;
					cout << "      请输入正确答案";
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
					//		a / b  - c *  d           相当于  a*b*c*d    /    b    -   c    *     d   
					cout << "      " << a * b*c*d << " / " << b << " - " << c << " * " << d << endl;
					cout << "      请输入正确答案";
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
	cout << "      总共得分:" << score << endl;
	stop();
}
		
int isGrade( string grade) {
	int g = toInt(grade);
	while (!(g <= 6 && g >= 1)) {
		choiseError();
		stop();
		string gg;
		cout << "                                    " << "请输入年级1-6（数字）" << endl;
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
	cout << "                 " << "请选择数字——>" << endl;
	cout << "                 " << "输入按回车键结束" << endl;
	cout << "                                    " << "1.登录" << endl;
	cout << "                                    " << "2.注册" << endl;

	string nnum;
	cin >> nnum;
	int num = toInt(nnum);
	if (num == 1)
	{
		clearAll();
		//跳转登录页-》进行身份验证
		//显示登录页
		loginView();
		return num;
	}
	else if (num == 2) {
		clearAll();
		//跳注册页-》进行注册
		//显示注册页
		registerView();
		return num;
	}
	else
	{
		clearAll();
		cout << "                                    " << "\033[32m请选择正确的选项\033[0m" << endl;
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
			cout << "                                    " << "\033[32m答题超时\033[0m" << endl;
			stop();
			timeUsed = 0;
			isAnswer = false;
			mainSystem();
			break;
		}
	}
	return NULL;

}