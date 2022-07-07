#include "user.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// 构造函数
User::User()
{
	head = new user;
	head->user_name = "admin";
	head->user_passwd = "123";
	head->next_user = nullptr;
}

// 析构函数
User::~User()
{
	user* p = head;
	user* q = nullptr;
	while (p)
	{
		q = p;
		p = q->next_user;
		delete q;
	}
}

user* User::find_By_Name(const string& name) const
{
	user* p = nullptr;
	for (p = head; p->next_user; p = p->next_user)
	{
		if (p->next_user->user_name == name)
		{
			return p;
		}
	}
	return nullptr;
}

void User::read_File()
{
	string new_file = "user";
	fstream file;
	file.open(new_file.c_str(), ios::in);
	if (file.bad())
	{
		cout << "文件打开失败........." << endl;
		return;
	}
	int len = 0;
	file >> len;
	if (!len)
	{
		cout << "已新建管理员数据文件，请注册管理员账号....." << endl;
		login();
		return;
	}
	user pHead;
	file.get();
	while (len--)
	{
		file >> pHead.user_name;
		file >> pHead.user_passwd;
		insert(pHead);
	}
	file.close();
	
	cout << "请输入管理员账号以登陆......." << endl;
	return;
}

void User::save_File()
{
	string new_file = "user";
	fstream file;
	file.open(new_file.c_str(), ios::out);
	if (file.bad())
	{
		cout << "文件打开失败.........." << endl;
		return;
	}
	int len = headCount() - 1;
	file << len << endl;
	user* pHead = head->next_user;
	while (pHead != nullptr)
	{
		file << pHead->user_name << endl;
		file << pHead->user_passwd << endl;
		pHead = pHead->next_user;
	}
	file.close();
	return;
}

bool User::insert(const user& _user)
{
	user* p = head;
	if (p->next_user == nullptr)  //当没有下一个堆，则新建一个堆来储存修改数据
	{
		p->next_user = new user(_user);  //用传入的已修改结构初始化
		p->next_user->next_user = nullptr;  //nullptr处理再下一个堆
		return true;
	}
	while (p->next_user)  //当存在下一个堆
	{
		if (p->next_user->user_name == _user.user_name)  //判重
		{
			cout << "用户名重复，插入失败......." << endl;
			return false;
		}
		p = p->next_user;  //既不大于也不重复就后移添加
	}
	p->next_user = new user(_user);
	p->next_user->next_user = nullptr;
	return true;
}

unsigned User::headCount()
{
	unsigned cnt = 0;
	user* p = nullptr;
	for (p = head; p; p = p->next_user, ++cnt);
	return cnt;
}

void User::login()
{
	user tmp;
	cout << "请输入注册用的用户名：";
	cin >> tmp.user_name;
	if (find_By_Name(tmp.user_name) == nullptr)
	{
		cout << "请输入注册用的密码：";
		cin >> tmp.user_passwd;
		insert(tmp);
	}
	else
	{
		cout << "您输入的用户名：" << tmp.user_name << "已存在，请重新输入用户名" << endl;
		login();
	}
	save_File();
}

bool User::logon()
{
	cout << "登陆" << endl;
	cout << "请输入登陆用户名：";
	string name;
	cin >> name;
	user* p = nullptr;
	if (find_By_Name(name))
	{
		p = find_By_Name(name);
		cout << "请输入登陆密码：";
		string password;
		for (int i = 0; i < 3; i ++ ) {
			cin >> password;
			if (p->next_user->user_passwd == password)
			{
				cout << "登陆成功.........." << endl;
				return true;
			}
			else 
			{
				cout << "密码错误x" << (i + 1) << "........." << endl;
				if (i != 2)cout << "请重新输入密码:";
				if (i == 2)
				{
					cout << "你已经错误3次，请重新登录.........." << endl;
					return false;
				}
			}
		}
	}
	else
	{
		cout << "没有找到此用户名！" << endl;
		logon();
	}
	return false;
}

void User::delete_By_Name()
{
	user* p = nullptr;
	user* q = nullptr;
	cout << "请输入要删除的用户名：" << endl;
	string name;
	cin >> name;
	p = find_By_Name(name);
	if (p == nullptr)
	{
		cout << "没有找到账号 \"" << name << "\", 删除失败....." << endl;
	}
	q = p->next_user;
	p->next_user = nullptr;
	delete q;
	cout << "成功删除 \"" << name << "\"的账号......." << endl;
	save_File();
}

void User::show_User()
{
	user* p = nullptr;
	cout << "------------------------------------\n" << endl;
	for (p = head->next_user; p; p = p->next_user)
	{
		cout << "用户名：" << p->user_name << "	密码：" << p->user_passwd << endl;
	}
	cout << "------------------------------------\n" << endl;
}

