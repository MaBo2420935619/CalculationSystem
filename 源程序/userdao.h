#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<Windows.h>
#include<mysql.h>
#include<string>
#include"title.h"
using namespace std;
#define QUERYSUCCESS "�������ݳɹ�\n"    //
#define CONNECTSUCCESS "�������ݿ�ɹ�\n"      //
const char *host = "127.0.0.1";
const char *user = "root";
const char *pass = "368542";
const char *db = "practicesystem"; // ���ݿ����ƣ��Ѵ��ڣ�
MYSQL mysql; //mysql����
MYSQL_FIELD *fd;  //�ֶ�������

char field[32][32];  //���ֶ�����ά����

MYSQL_RES *res; //����ṹ�������е�һ����ѯ�����

MYSQL_ROW column; //һ�������ݵ����Ͱ�ȫ(type-safe)�ı�ʾ����ʾ�����е���
char query[150]; //��ѯ���
bool connectDatabase();   //�������ݿ�
bool QueryDatabase1();
bool QueryDatabase2();
bool InsertData();
bool ModifyData();
bool DeleteData();
bool loginDao(string name, string pwd);    //�����ݿ������¼��Ϣ
bool registerDao(string name, string pwd, int grade, string school);  //�����ݿ�д��ע����Ϣ
bool lookPersonalHistory(string name);   //�����ݿ�������˴�����ʷ��Ϣ
bool lookFirstlGrade();          //�����ݿ��������а��������
bool setPracticeInfo(string name, int titleNumber, int titleScore, int freqScore, int freq, int time);//�����ݿ�д����˴�����ʷ��Ϣ
int selectMaxFreq(string name);   //��ѯ�û���ǰ�������
int getUserLevel(string name);    //�����û����������ݿ��ѯ�꼶
int getBestGrade(string name);    //�����ݿ�����ǰ�û�����ʷ��ѳɼ�
bool setBestGrade(string name, int grade);  //���������ʷ��ѳɼ�
bool setFreqScore(string name, int grade, int freq); //�����ݿ�д�뵱�δ����ܳɼ�
void clearAll();   //�����Ļ

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
	//��ʼ��mysql
	mysql_init(&mysql);  //����mysql�����ݿ�
	//����false������ʧ�ܣ�����true�����ӳɹ�

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
//�ͷ���Դ

void FreeConnect()

{

	//�ͷ���Դ

	mysql_free_result(res);

	mysql_close(&mysql);

}
/***************************���ݿ����***********************************/

//��ʵ���е����ݿ����������д��sql��䣬Ȼ����mysql_query(&mysql,query)����ɣ������������ݿ�����ɾ�Ĳ�

//��ѯ����

bool QueryDatabase1()


{
	if (connectDatabase()) {
		sprintf(query, "select * from userinfo"); //ִ�в�ѯ��䣬�����ǲ�ѯ���У�user�Ǳ��������ü����ţ���strcpyҲ����

		mysql_query(&mysql, "set names gbk"); //���ñ����ʽ��SET NAMES GBKҲ�У�������cmd����������

		//����0 ��ѯ�ɹ�������1��ѯʧ��

		if (mysql_query(&mysql, query))        //ִ��SQL���

		{

			printf("Query failed (%s)\n", mysql_error(&mysql));

			return false;

		}

		else

		{

			printf(QUERYSUCCESS);

		}

		//��ȡ�����

		if (!(res = mysql_store_result(&mysql)))    //���sql�������󷵻صĽ����

		{

			printf("Couldn't get result from %s\n", mysql_error(&mysql));

			return false;

		}



		//��ӡ��������

		printf("number of dataline returned: %d\n", mysql_affected_rows(&mysql));



		//��ȡ�ֶε���Ϣ

		char *str_field[32];  //����һ���ַ�������洢�ֶ���Ϣ

		for (int i = 0; i < 2; i++)   //����֪�ֶ�����������»�ȡ�ֶ���

		{

			str_field[i] = mysql_fetch_field(res)->name;

		}

		for (int i = 0; i < 2; i++)   //��ӡ�ֶ�

			printf("%10s\t", str_field[i]);

		printf("\n");
		clearAll();
		//��ӡ��ȡ������
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

		//����0 ��ѯ�ɹ�������1��ѯʧ��

		if (mysql_query(&mysql, "select * from userinfo"))        //ִ��SQL���

		{

			printf("Query failed (%s)\n", mysql_error(&mysql));

			return false;

		}

		else

		{

			printf(QUERYSUCCESS);

		}

		res = mysql_store_result(&mysql);

		//��ӡ��������

		printf("number of dataline returned: %d\n", mysql_affected_rows(&mysql));

		for (int i = 0; fd = mysql_fetch_field(res); i++)  //��ȡ�ֶ���

			strcpy(field[i], fd->name);

		int j = mysql_num_fields(res);  // ��ȡ����

		for (int i = 0; i < j; i++)  //��ӡ�ֶ�

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

//��������

bool InsertData()

{

	sprintf(query, "insert into userinfo values ('ddd', 'ddd');");  //������취ʵ���ֶ��ڿ���̨�ֶ�����ָ��
	clearAll();
	if (mysql_query(&mysql, query))        //ִ��SQL���

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

//�޸�����

bool ModifyData()

{

	sprintf(query, "update userinfo set password='111' where name='ddd'");
	clearAll();
	if (mysql_query(&mysql, query))        //ִ��SQL���

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

//ɾ������

bool DeleteData()

{

	/*sprintf(query, "delete from user where id=6");*/

	char query[100];

	printf("please input the sql:\n");
	sprintf(query, "delete from userinfo where name='ddd'");

	clearAll();
	if (mysql_query(&mysql, query))        //ִ��SQL���
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
		//sprintf(query, "select * from userinfo where name= '%s' and pwd='%s'",name,pwd ); //ִ�в�ѯ��䣬�����ǲ�ѯ���У�user�Ǳ��������ü����ţ���strcpyҲ����
		sprintf(query, c_s);
		char * q = "set names \'GBK\'";
		mysql_query(&mysql,q); //���ñ����ʽ��SET NAMES GBKҲ�У�������cmd����������

		//����0 ��ѯ�ɹ�������1��ѯʧ��
		clearAll();
		if (mysql_query(&mysql, query))        //ִ��SQL���

		{

			printf("Query failed (%s)\n", mysql_error(&mysql));

			return false;

		}

		else

		{

			printf(QUERYSUCCESS);

		}

		//��ȡ�����

		if (!(res = mysql_store_result(&mysql)))    //���sql�������󷵻صĽ����

		{

			printf("Couldn't get result from %s\n", mysql_error(&mysql));
			clearAll();
			return false;

		}



		//��ӡ��������

		printf("number of dataline returned: %d\n", mysql_affected_rows(&mysql));

	
		//��ȡ�ֶε���Ϣ

		char *str_field[32];  //����һ���ַ�������洢�ֶ���Ϣ

		for (int i = 0; i < 2; i++)   //����֪�ֶ�����������»�ȡ�ֶ���

		{

			str_field[i] = mysql_fetch_field(res)->name;

		}

		for (int i = 0; i < 2; i++)   //��ӡ�ֶ�

			printf("%10s\t", str_field[i]);
		clearAll();

		printf("\n");

		//��ӡ��ȡ������
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
			cout << "��¼ʧ��" << endl;
		}
		return success;

	}
}
bool registerDao(string name,string pwd,int grade,string school) {
	if (connectDatabase()) {
		string sql = "insert into userinfo values ('" + name + "','" + pwd + "'," + toString(grade)+ ",'" + school + "',0 );";
		cout << sql << endl;
		const char* c_s = sql.c_str();
		sprintf(query, c_s);  //������취ʵ���ֶ��ڿ���̨�ֶ�����ָ��
		mysql_query(&mysql, "SET NAMES UTF8"); //���ñ����ʽ��SET NAMES GBKҲ�У�������cmd����������
		clearAll();
		if (mysql_query(&mysql, query))        //ִ��SQL���

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
	
		mysql_query(&mysql, "SET NAMES UTF8"); //���ñ����ʽ��SET NAMES GBKҲ�У�������cmd����������

		//����0 ��ѯ�ɹ�������1��ѯʧ��
		clearAll();
		if (mysql_query(&mysql, query))        //ִ��SQL���

		{

			printf("Query failed (%s)\n", mysql_error(&mysql));

			return false;

		}

		else

		{

			printf(QUERYSUCCESS);

		}

		//��ȡ�����

		if (!(res = mysql_store_result(&mysql)))    //���sql�������󷵻صĽ����

		{

			printf("Couldn't get result from %s\n", mysql_error(&mysql));

			return false;

		}



		//��ӡ��������

		printf("number of dataline returned: %d\n", mysql_affected_rows(&mysql));

		clearAll();

		//��ȡ�ֶε���Ϣ

		char *str_field[32];  //����һ���ַ�������洢�ֶ���Ϣ

		for (int i = 0; i < 6; i++)   //����֪�ֶ�����������»�ȡ�ֶ���

		{

			str_field[i] = mysql_fetch_field(res)->name;

		}

		//for (int i = 0; i < 6; i++)   //��ӡ�ֶ�

		//	printf("%10s\t", str_field[i]);

		//printf("\n");
		printf("%10s\t", "����");
		printf("%10s\t", "�������");
		printf("%10s\t", "���δ������");
		printf("%10s\t", "��Ŀ���");
		printf("%10s\t", "��Ŀ�÷�");
		printf("%10s\t", "������ʱ");
		printf("\n");
		//��ӡ��ȡ������
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
			cout << "��¼ʧ��" << endl;
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
		mysql_query(&mysql, "SET NAMES gbk"); //���ñ����ʽ��SET NAMES GBKҲ�У�������cmd����������
		clearAll();
		//����0 ��ѯ�ɹ�������1��ѯʧ��

		if (mysql_query(&mysql, query))        //ִ��SQL���

		{

			printf("Query failed (%s)\n", mysql_error(&mysql));

			return false;

		}

		else

		{

			printf(QUERYSUCCESS);

		}

		//��ȡ�����

		if (!(res = mysql_store_result(&mysql)))    //���sql�������󷵻صĽ����

		{

			printf("Couldn't get result from %s\n", mysql_error(&mysql));

			return false;

		}



		//��ӡ��������

		printf("number of dataline returned: %d\n", mysql_affected_rows(&mysql));



		//��ȡ�ֶε���Ϣ

		char *str_field[32];  //����һ���ַ�������洢�ֶ���Ϣ

		for (int i = 0; i < 4; i++)   //����֪�ֶ�����������»�ȡ�ֶ���

		{

			str_field[i] = mysql_fetch_field(res)->name;

		}
		clearAll();
		//for (int i = 0; i < 4; i++)   //��ӡ�ֶ�

		//	printf("%10s\t", str_field[i]);

		printf("\n");
		printf("%10s\t", "����");
		printf("%10s\t", "�꼶");
		printf("%10s\t", "����ѧУ");
		printf("%10s\t", "��ʷ��ѳɼ�");
		
		printf("\n");
		//��ӡ��ȡ������
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
			/*cout << "��¼�ɹ�" << endl;*/
			cout << QUERYSUCCESS;
		}
		else
		{
			cout << "��¼ʧ��" << endl;
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
		sprintf(query, c_s);  //������취ʵ���ֶ��ڿ���̨�ֶ�����ָ��
		clearAll();
		if (mysql_query(&mysql, query))        //ִ��SQL���

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
		sprintf(query, c_s);  //������취ʵ���ֶ��ڿ���̨�ֶ�����ָ��
		mysql_query(&mysql, "set names gbk"); //���ñ����ʽ��SET NAMES GBKҲ�У�������cmd����������

		//����0 ��ѯ�ɹ�������1��ѯʧ��
		
		if (mysql_query(&mysql, query))        //ִ��SQL���

		{

			printf("Query failed (%s)\n", mysql_error(&mysql));
			return false;
		}
		else
		{
			printf(QUERYSUCCESS);
		}

		//��ȡ�����

		if (!(res = mysql_store_result(&mysql)))    //���sql�������󷵻صĽ����

		{

			printf("Couldn't get result from %s\n", mysql_error(&mysql));

			return false;

		}



		//��ӡ��������

		printf("number of dataline returned: %d\n", mysql_affected_rows(&mysql));


		
		//��ȡ�ֶε���Ϣ

		char *str_field[32];  //����һ���ַ�������洢�ֶ���Ϣ

		for (int i = 0; i < 1; i++)   //����֪�ֶ�����������»�ȡ�ֶ���

		{

			str_field[i] = mysql_fetch_field(res)->name;

		}

		for (int i = 0; i < 1; i++)   //��ӡ�ֶ�
		{
			printf("%10s\t", str_field[i]);
		
		}
			
		
		printf("\n");

		//��ӡ��ȡ������
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
		sprintf(query, c_s);  //������취ʵ���ֶ��ڿ���̨�ֶ�����ָ��
		mysql_query(&mysql, "set names gbk"); //���ñ����ʽ��SET NAMES GBKҲ�У�������cmd����������
		clearAll();
		//����0 ��ѯ�ɹ�������1��ѯʧ��

		if (mysql_query(&mysql, query))        //ִ��SQL���

		{

			printf("Query failed (%s)\n", mysql_error(&mysql));
			return false;
		}
		else
		{
			printf(QUERYSUCCESS);
		}

		//��ȡ�����

		if (!(res = mysql_store_result(&mysql)))    //���sql�������󷵻صĽ����

		{

			printf("Couldn't get result from %s\n", mysql_error(&mysql));

			return false;

		}



		//��ӡ��������

		printf("number of dataline returned: %d\n", mysql_affected_rows(&mysql));


		clearAll();
		//��ȡ�ֶε���Ϣ

		char *str_field[32];  //����һ���ַ�������洢�ֶ���Ϣ

		for (int i = 0; i < 1; i++)   //����֪�ֶ�����������»�ȡ�ֶ���

		{

			str_field[i] = mysql_fetch_field(res)->name;

		}

		for (int i = 0; i < 1; i++)   //��ӡ�ֶ�
		{
			printf("%10s\t", str_field[i]);

		}


		printf("\n");

		//��ӡ��ȡ������
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
		sprintf(query, c_s);  //������취ʵ���ֶ��ڿ���̨�ֶ�����ָ��
		mysql_query(&mysql, "set names gbk"); //���ñ����ʽ��SET NAMES GBKҲ�У�������cmd����������

		//����0 ��ѯ�ɹ�������1��ѯʧ��
		clearAll();
		if (mysql_query(&mysql, query))        //ִ��SQL���

		{

			printf("Query failed (%s)\n", mysql_error(&mysql));
			return false;
		}
		else
		{
			printf(QUERYSUCCESS);
		}

		//��ȡ�����

		if (!(res = mysql_store_result(&mysql)))    //���sql�������󷵻صĽ����

		{

			printf("Couldn't get result from %s\n", mysql_error(&mysql));

			return false;

		}



		//��ӡ��������

		printf("number of dataline returned: %d\n", mysql_affected_rows(&mysql));
		clearAll();


		//��ȡ�ֶε���Ϣ

		char *str_field[32];  //����һ���ַ�������洢�ֶ���Ϣ

		for (int i = 0; i < 1; i++)   //����֪�ֶ�����������»�ȡ�ֶ���
		{
			str_field[i] = mysql_fetch_field(res)->name;
		}

		for (int i = 0; i < 1; i++)   //��ӡ�ֶ�
		{
			printf("%10s\t", str_field[i]);

		}


		printf("\n");

		//��ӡ��ȡ������
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
		sprintf(query, c_s);  //������취ʵ���ֶ��ڿ���̨�ֶ�����ָ��
		clearAll();
		if (mysql_query(&mysql, query))        //ִ��SQL���

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
		sprintf(query, c_s);  //������취ʵ���ֶ��ڿ���̨�ֶ�����ָ��
		clearAll();
		if (mysql_query(&mysql, query))        //ִ��SQL���

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