#pragma once
#ifndef USER_H
#define USER_H
#include <string>

using namespace std;

typedef struct user
{
	string user_name;
	string user_passwd;
	
	user* next_user;  //链表
}user;

class User
{
public:
	User();
	~User();
	
	user* find_By_Name(const string& name) const;  //查找文件中的用户名
	
	void read_File();  //读取文件
	void save_File();  //保存文件
	
	void login();  //注册函数
	bool logon();  //登陆函数
	
	unsigned headCount();  //结构计数函数
	bool insert(const user& astu);  //插入函数
	void delete_By_Name();  //删除函数
	void show_User();   //显示函数
private:
	user* head;
};

#endif
