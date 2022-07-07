#pragma once
#ifndef USER_H
#define USER_H
#include <string>

using namespace std;

typedef struct user
{
	string user_name;
	string user_passwd;
	
	user* next_user;  //����
}user;

class User
{
public:
	User();
	~User();
	
	user* find_By_Name(const string& name) const;  //�����ļ��е��û���
	
	void read_File();  //��ȡ�ļ�
	void save_File();  //�����ļ�
	
	void login();  //ע�ắ��
	bool logon();  //��½����
	
	unsigned headCount();  //�ṹ��������
	bool insert(const user& astu);  //���뺯��
	void delete_By_Name();  //ɾ������
	void show_User();   //��ʾ����
private:
	user* head;
};

#endif
