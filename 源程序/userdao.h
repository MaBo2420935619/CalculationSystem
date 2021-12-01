#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<Windows.h>
#include<mysql.h>
#include<string>
#include"title.h"
using namespace std;
#define QUERYSUCCESS "请求数据成功\n"    //
#define CONNECTSUCCESS "连接数据库成功\n"      //
const char *host = "127.0.0.1";
const char *user = "root";
const char *pass = "368542";
const char *db = "practicesystem"; // 数据库名称（已存在）
MYSQL mysql; //mysql连接
MYSQL_FIELD *fd;  //字段列数组

char field[32][32];  //存字段名二维数组

MYSQL_RES *res; //这个结构代表返回行的一个查询结果集

MYSQL_ROW column; //一个行数据的类型安全(type-safe)的表示，表示数据行的列
char query[150]; //查询语句
bool connectDatabase();   //连接数据库
bool QueryDatabase1();
bool QueryDatabase2();
bool InsertData();
bool ModifyData();
bool DeleteData();
bool loginDao(string name, string pwd);    //向数据库请求登录信息
bool registerDao(string name, string pwd, int grade, string school);  //向数据库写入注册信息
bool lookPersonalHistory(string name);   //向数据库请求个人答题历史信息
bool lookFirstlGrade();          //向数据库请求排行榜排名情况
bool setPracticeInfo(string name, int titleNumber, int titleScore, int freqScore, int freq, int time);//向数据库写入个人答题历史信息
int selectMaxFreq(string name);   //查询用户当前答题次数
int getUserLevel(string name);    //根据用户姓名在数据库查询年级
int getBestGrade(string name);    //向数据库请求当前用户的历史最佳成绩
bool setBestGrade(string name, int grade);  //填入个人历史最佳成绩
bool setFreqScore(string name, int grade, int freq); //向数据库写入当次答题总成绩
void clearAll();   //清除屏幕

//
//int main()
//{
//	
//	QueryDatabase1();
//	
//
//	QueryDatabase2();
//}
bool connectDatabase()

{
	//初始化mysql
	mysql_init(&mysql);  //连接mysql，数据库
	//返回false则连接失败，返回true则连接成功

	mysql_init(&mysql);

	if (!mysql_real_connect(&mysql, host, user, pass, db, 3306, 0, 0))
	{
		cout << "Connect Database Failed" << endl;
		return false;
	}
	else
	{
		cout << CONNECTSUCCESS << endl;
		return true;
	}


}
//释放资源

void FreeConnect()

{

	//释放资源

	mysql_free_result(res);

	mysql_close(&mysql);

}
/***************************数据库操作***********************************/

//其实所有的数据库操作都是先写个sql语句，然后用mysql_query(&mysql,query)来完成，包括创建数据库或表，增删改查

//查询数据

bool QueryDatabase1()


{
	if (connectDatabase()) {
		sprintf(query, "select * from userinfo"); //执行查询语句，这里是查询所有，user是表名，不用加引号，用strcpy也可以

		mysql_query(&mysql, "set names gbk"); //设置编码格式（SET NAMES GBK也行），否则cmd下中文乱码

		//返回0 查询成功，返回1查询失败

		if (mysql_query(&mysql, query))        //执行SQL语句

		{

			printf("Query failed (%s)\n", mysql_error(&mysql));

			return false;

		}

		else

		{

			printf(QUERYSUCCESS);

		}

		//获取结果集

		if (!(res = mysql_store_result(&mysql)))    //获得sql语句结束后返回的结果集

		{

			printf("Couldn't get result from %s\n", mysql_error(&mysql));

			return false;

		}



		//打印数据行数

		printf("number of dataline returned: %d\n", mysql_affected_rows(&mysql));



		//获取字段的信息

		char *str_field[32];  //定义一个字符串数组存储字段信息

		for (int i = 0; i < 2; i++)   //在已知字段数量的情况下获取字段名

		{

			str_field[i] = mysql_fetch_field(res)->name;

		}

		for (int i = 0; i < 2; i++)   //打印字段

			printf("%10s\t", str_field[i]);

		printf("\n");
		clearAll();
		//打印获取的数据
		MYSQL_ROW row;
		while (row = mysql_fetch_row(res))
		{
			for (int i = 0; i < mysql_affected_rows(&mysql); ++i)
			{
				printf("%10s\t", row[i]);
			}

			cout << endl;
		}

		return true;

	}

}

bool QueryDatabase2()

{
	if (connectDatabase()) {
		mysql_query(&mysql, "set names gbk");

		//返回0 查询成功，返回1查询失败

		if (mysql_query(&mysql, "select * from userinfo"))        //执行SQL语句

		{

			printf("Query failed (%s)\n", mysql_error(&mysql));

			return false;

		}

		else

		{

			printf(QUERYSUCCESS);

		}

		res = mysql_store_result(&mysql);

		//打印数据行数

		printf("number of dataline returned: %d\n", mysql_affected_rows(&mysql));

		for (int i = 0; fd = mysql_fetch_field(res); i++)  //获取字段名

			strcpy(field[i], fd->name);

		int j = mysql_num_fields(res);  // 获取列数

		for (int i = 0; i < j; i++)  //打印字段

			printf("%10s\t", field[i]);

		printf("\n");
		clearAll();
		while (column = mysql_fetch_row(res))

		{

			for (int i = 0; i < j; i++)

				printf("%10s\t", column[i]);

			printf("\n");

		}

		return true;
	}



}

//插入数据

bool InsertData()

{

	sprintf(query, "insert into userinfo values ('ddd', 'ddd');");  //可以想办法实现手动在控制台手动输入指令
	clearAll();
	if (mysql_query(&mysql, query))        //执行SQL语句

	{

		printf("Query failed (%s)\n", mysql_error(&mysql));

		return false;

	}

	else

	{

		printf(QUERYSUCCESS);

		return true;

	}

}

//修改数据

bool ModifyData()

{

	sprintf(query, "update userinfo set password='111' where name='ddd'");
	clearAll();
	if (mysql_query(&mysql, query))        //执行SQL语句

	{

		printf("Query failed (%s)\n", mysql_error(&mysql));

		return false;

	}

	else

	{

		printf(QUERYSUCCESS);

		return true;

	}

}

//删除数据

bool DeleteData()

{

	/*sprintf(query, "delete from user where id=6");*/

	char query[100];

	printf("please input the sql:\n");
	sprintf(query, "delete from userinfo where name='ddd'");

	clearAll();
	if (mysql_query(&mysql, query))        //执行SQL语句
	{
		printf("Query failed (%s)\n", mysql_error(&mysql));
		return false;
	}
	else

	{
		printf(QUERYSUCCESS);
		return true;

	}

}
bool loginDao(string name, string pwd) {
	if (connectDatabase()) {
		string sql = "select * from userinfo where name='" + name + "'and pwd='" + pwd + "';";
		cout << sql<<endl;
		const char* c_s = sql.c_str();
		//sprintf(query, "select * from userinfo where name= '%s' and pwd='%s'",name,pwd ); //执行查询语句，这里是查询所有，user是表名，不用加引号，用strcpy也可以
		sprintf(query, c_s);
		char * q = "set names \'GBK\'";
		mysql_query(&mysql,q); //设置编码格式（SET NAMES GBK也行），否则cmd下中文乱码

		//返回0 查询成功，返回1查询失败
		clearAll();
		if (mysql_query(&mysql, query))        //执行SQL语句

		{

			printf("Query failed (%s)\n", mysql_error(&mysql));

			return false;

		}

		else

		{

			printf(QUERYSUCCESS);

		}

		//获取结果集

		if (!(res = mysql_store_result(&mysql)))    //获得sql语句结束后返回的结果集

		{

			printf("Couldn't get result from %s\n", mysql_error(&mysql));
			clearAll();
			return false;

		}



		//打印数据行数

		printf("number of dataline returned: %d\n", mysql_affected_rows(&mysql));

	
		//获取字段的信息

		char *str_field[32];  //定义一个字符串数组存储字段信息

		for (int i = 0; i < 2; i++)   //在已知字段数量的情况下获取字段名

		{

			str_field[i] = mysql_fetch_field(res)->name;

		}

		for (int i = 0; i < 2; i++)   //打印字段

			printf("%10s\t", str_field[i]);
		clearAll();

		printf("\n");

		//打印获取的数据
		MYSQL_ROW row;
		bool success = false;
		while (row = mysql_fetch_row(res))
		{
			for (int i = 0; i < mysql_affected_rows(&mysql); ++i)
			{
				printf("%10s\t", row[i]);
				success = true;
					
			}

			cout << endl;
		}
		clearAll();

		if (success) {
			cout << QUERYSUCCESS << endl;
		}
		else
		{
			cout << "登录失败" << endl;
		}
		return success;

	}
}
bool registerDao(string name,string pwd,int grade,string school) {
	if (connectDatabase()) {
		string sql = "insert into userinfo values ('" + name + "','" + pwd + "'," + toString(grade)+ ",'" + school + "',0 );";
		cout << sql << endl;
		const char* c_s = sql.c_str();
		sprintf(query, c_s);  //可以想办法实现手动在控制台手动输入指令
		mysql_query(&mysql, "SET NAMES UTF8"); //设置编码格式（SET NAMES GBK也行），否则cmd下中文乱码
		clearAll();
		if (mysql_query(&mysql, query))        //执行SQL语句

		{

			printf("Query failed (%s)\n", mysql_error(&mysql));

			return false;

		}

		else

		{
			printf(QUERYSUCCESS);

			return true;

		}
	}
	
}
bool lookPersonalHistory(string name) {
	if (connectDatabase()) {
		string sql = "select name,freq,freqscore,titleNumber,titleScore,time from practiceinfo where name='" + name + "';";
		cout << sql << endl;
		const char* c_s = sql.c_str();
		sprintf(query, c_s);
	
		mysql_query(&mysql, "SET NAMES UTF8"); //设置编码格式（SET NAMES GBK也行），否则cmd下中文乱码

		//返回0 查询成功，返回1查询失败
		clearAll();
		if (mysql_query(&mysql, query))        //执行SQL语句

		{

			printf("Query failed (%s)\n", mysql_error(&mysql));

			return false;

		}

		else

		{

			printf(QUERYSUCCESS);

		}

		//获取结果集

		if (!(res = mysql_store_result(&mysql)))    //获得sql语句结束后返回的结果集

		{

			printf("Couldn't get result from %s\n", mysql_error(&mysql));

			return false;

		}



		//打印数据行数

		printf("number of dataline returned: %d\n", mysql_affected_rows(&mysql));

		clearAll();

		//获取字段的信息

		char *str_field[32];  //定义一个字符串数组存储字段信息

		for (int i = 0; i < 6; i++)   //在已知字段数量的情况下获取字段名

		{

			str_field[i] = mysql_fetch_field(res)->name;

		}

		//for (int i = 0; i < 6; i++)   //打印字段

		//	printf("%10s\t", str_field[i]);

		//printf("\n");
		printf("%10s\t", "姓名");
		printf("%10s\t", "答题次数");
		printf("%10s\t", "当次答题分数");
		printf("%10s\t", "题目编号");
		printf("%10s\t", "题目得分");
		printf("%10s\t", "答题用时");
		printf("\n");
		//打印获取的数据
		MYSQL_ROW row;
		bool success = false;
		while (row = mysql_fetch_row(res))
		{
			for (int i = 0; i <6; ++i)
			{
				printf("%10s\t", row[i]);
				success = true;

			}

			cout << endl;
		}
		if (success) {
			cout << QUERYSUCCESS << endl;
		}
		/*else
		{
			cout << "登录失败" << endl;
		}*/
		return success;

	}
}
bool lookFirstlGrade() {
	if (connectDatabase()) {
		string sql = "select name,grade,school,bestScore from userinfo group by name order by bestScore desc;";
		cout << sql << endl;
		const char* c_s = sql.c_str();
		sprintf(query, c_s);
		mysql_query(&mysql, "SET NAMES gbk"); //设置编码格式（SET NAMES GBK也行），否则cmd下中文乱码
		clearAll();
		//返回0 查询成功，返回1查询失败

		if (mysql_query(&mysql, query))        //执行SQL语句

		{

			printf("Query failed (%s)\n", mysql_error(&mysql));

			return false;

		}

		else

		{

			printf(QUERYSUCCESS);

		}

		//获取结果集

		if (!(res = mysql_store_result(&mysql)))    //获得sql语句结束后返回的结果集

		{

			printf("Couldn't get result from %s\n", mysql_error(&mysql));

			return false;

		}



		//打印数据行数

		printf("number of dataline returned: %d\n", mysql_affected_rows(&mysql));



		//获取字段的信息

		char *str_field[32];  //定义一个字符串数组存储字段信息

		for (int i = 0; i < 4; i++)   //在已知字段数量的情况下获取字段名

		{

			str_field[i] = mysql_fetch_field(res)->name;

		}
		clearAll();
		//for (int i = 0; i < 4; i++)   //打印字段

		//	printf("%10s\t", str_field[i]);

		printf("\n");
		printf("%10s\t", "姓名");
		printf("%10s\t", "年级");
		printf("%10s\t", "所在学校");
		printf("%10s\t", "历史最佳成绩");
		
		printf("\n");
		//打印获取的数据
		MYSQL_ROW row;
		bool success = false;
		while (row = mysql_fetch_row(res))
		{
			for (int i = 0; i <4; ++i)
			{
			
				printf("%10s\t", row[i]);
				
				success = true;
				
			}

			cout << endl;
		}
		if (success) {
			/*cout << "登录成功" << endl;*/
			cout << QUERYSUCCESS;
		}
		else
		{
			cout << "登录失败" << endl;
		}
		return success;

	}
}
bool setPracticeInfo(string name, int titleNumber, int titleScore,int freqScore, int freq,int time ) {
	if (connectDatabase()) {
		string titNumber = toString(titleNumber);
		string titScore = toString(titleScore);
		string freScore =toString(freqScore);
		
		string fre = toString(freq);
		string tim = toString(time);

		string sql = "insert into practiceinfo values ('" + name + "','" + titNumber + "','" + titScore + "','" + freScore + "','" + fre + "','" + tim+" ');";
		cout << sql << endl;
		const char* c_s = sql.c_str();
		sprintf(query, c_s);  //可以想办法实现手动在控制台手动输入指令
		clearAll();
		if (mysql_query(&mysql, query))        //执行SQL语句

		{

			printf("Query failed (%s)\n", mysql_error(&mysql));

			return false;

		}

		else

		{
			printf(QUERYSUCCESS);

			return true;

		}
	}
}
int selectMaxFreq(string name) {
	if (connectDatabase()) {
		string sql = "SELECT MAX(freq) FROM `practiceinfo` WHERE name='"+name+"'";
		cout << sql << endl;
		const char* c_s = sql.c_str();
		sprintf(query, c_s);  //可以想办法实现手动在控制台手动输入指令
		mysql_query(&mysql, "set names gbk"); //设置编码格式（SET NAMES GBK也行），否则cmd下中文乱码

		//返回0 查询成功，返回1查询失败
		
		if (mysql_query(&mysql, query))        //执行SQL语句

		{

			printf("Query failed (%s)\n", mysql_error(&mysql));
			return false;
		}
		else
		{
			printf(QUERYSUCCESS);
		}

		//获取结果集

		if (!(res = mysql_store_result(&mysql)))    //获得sql语句结束后返回的结果集

		{

			printf("Couldn't get result from %s\n", mysql_error(&mysql));

			return false;

		}



		//打印数据行数

		printf("number of dataline returned: %d\n", mysql_affected_rows(&mysql));


		
		//获取字段的信息

		char *str_field[32];  //定义一个字符串数组存储字段信息

		for (int i = 0; i < 1; i++)   //在已知字段数量的情况下获取字段名

		{

			str_field[i] = mysql_fetch_field(res)->name;

		}

		for (int i = 0; i < 1; i++)   //打印字段
		{
			printf("%10s\t", str_field[i]);
		
		}
			
		
		printf("\n");

		//打印获取的数据
		MYSQL_ROW row;
		string *s;
		while (row = mysql_fetch_row(res))
		{
			for (int i = 0; i <1; ++i)
			{
				
				printf("%10s\t", row[i]);
				char* t;
				t = row[i];
				if (t == NULL)
				{
					clearAll();
					return 0;
				}
					
				string a = t;
				int c = atoi(a.c_str());
				clearAll();
				return  c;
			}

			cout << endl;
		}

		return 0;

	}
}
int getUserLevel(string name) {
	if (connectDatabase()) {
		string sql = "SELECT grade FROM `userinfo` WHERE  name='" + name + "'";
		cout << sql << endl;
		const char* c_s = sql.c_str();
		sprintf(query, c_s);  //可以想办法实现手动在控制台手动输入指令
		mysql_query(&mysql, "set names gbk"); //设置编码格式（SET NAMES GBK也行），否则cmd下中文乱码
		clearAll();
		//返回0 查询成功，返回1查询失败

		if (mysql_query(&mysql, query))        //执行SQL语句

		{

			printf("Query failed (%s)\n", mysql_error(&mysql));
			return false;
		}
		else
		{
			printf(QUERYSUCCESS);
		}

		//获取结果集

		if (!(res = mysql_store_result(&mysql)))    //获得sql语句结束后返回的结果集

		{

			printf("Couldn't get result from %s\n", mysql_error(&mysql));

			return false;

		}



		//打印数据行数

		printf("number of dataline returned: %d\n", mysql_affected_rows(&mysql));


		clearAll();
		//获取字段的信息

		char *str_field[32];  //定义一个字符串数组存储字段信息

		for (int i = 0; i < 1; i++)   //在已知字段数量的情况下获取字段名

		{

			str_field[i] = mysql_fetch_field(res)->name;

		}

		for (int i = 0; i < 1; i++)   //打印字段
		{
			printf("%10s\t", str_field[i]);

		}


		printf("\n");

		//打印获取的数据
		MYSQL_ROW row;
		string *s;
		while (row = mysql_fetch_row(res))
		{
			for (int i = 0; i < 1; ++i)
			{

				printf("%10s\t", row[i]);
				char* t;
				t = row[i];
				string a = t;
				int c = atoi(a.c_str());
				if (c <= 2 && c >= 1)
					return 1;
				if (c <= 4 && c >= 3)
					return 2;
				if (c <= 6 && c >= 5)
					return 3;
				else
				{
					return 0;
				}
			}

			cout << endl;
		}

		return 0;

	}
}
int getBestGrade(string name) {
	if (connectDatabase()) {
		string sql = "SELECT bestScore FROM userinfo WHERE name='" + name + "'";
		cout << sql << endl;
		const char* c_s = sql.c_str();
		sprintf(query, c_s);  //可以想办法实现手动在控制台手动输入指令
		mysql_query(&mysql, "set names gbk"); //设置编码格式（SET NAMES GBK也行），否则cmd下中文乱码

		//返回0 查询成功，返回1查询失败
		clearAll();
		if (mysql_query(&mysql, query))        //执行SQL语句

		{

			printf("Query failed (%s)\n", mysql_error(&mysql));
			return false;
		}
		else
		{
			printf(QUERYSUCCESS);
		}

		//获取结果集

		if (!(res = mysql_store_result(&mysql)))    //获得sql语句结束后返回的结果集

		{

			printf("Couldn't get result from %s\n", mysql_error(&mysql));

			return false;

		}



		//打印数据行数

		printf("number of dataline returned: %d\n", mysql_affected_rows(&mysql));
		clearAll();


		//获取字段的信息

		char *str_field[32];  //定义一个字符串数组存储字段信息

		for (int i = 0; i < 1; i++)   //在已知字段数量的情况下获取字段名
		{
			str_field[i] = mysql_fetch_field(res)->name;
		}

		for (int i = 0; i < 1; i++)   //打印字段
		{
			printf("%10s\t", str_field[i]);

		}


		printf("\n");

		//打印获取的数据
		MYSQL_ROW row;
		string *s;
		while (row = mysql_fetch_row(res))
		{
			for (int i = 0; i < 1; ++i)
			{

				printf("%10s\t", row[i]);
				char* t;
				t = row[i];
				if (t == NULL)
					return 0;
				string a = t;
				int c = atoi(a.c_str());
				return  c;
			}

			cout << endl;
		}

		return 0;
	}
}
bool setBestGrade(string name, int grade) {
	if (connectDatabase()) {
		string sql = "UPDATE userinfo SET bestScore = "+toString(grade)+" WHERE name = '" + name + "'";
		cout << sql << endl;
		const char* c_s = sql.c_str();
		sprintf(query, c_s);  //可以想办法实现手动在控制台手动输入指令
		clearAll();
		if (mysql_query(&mysql, query))        //执行SQL语句

		{
			printf("Query failed (%s)\n", mysql_error(&mysql));
			return false;

		}
		else
		{
			printf(QUERYSUCCESS);
			return true;
		}
	}
}
bool setFreqScore(string name, int grade ,int freq) {
	if (connectDatabase()) {
		string sql = "UPDATE practiceinfo SET freqscore = " + toString(grade) + " WHERE name = '" + name + "'and freq="+ toString(freq);
		cout << sql << endl;
		const char* c_s = sql.c_str();
		sprintf(query, c_s);  //可以想办法实现手动在控制台手动输入指令
		clearAll();
		if (mysql_query(&mysql, query))        //执行SQL语句

		{
			printf("Query failed (%s)\n", mysql_error(&mysql));
			return false;

		}
		else
		{
			printf(QUERYSUCCESS);
			return true;
		}
	}
}
void clearAll() {
	/*system("cls");*/
}