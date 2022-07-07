#include "user.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// ���캯��
User::User()
{
	head = new user;
	head->user_name = "admin";
	head->user_passwd = "123";
	head->next_user = nullptr;
}

// ��������
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
		cout << "�ļ���ʧ��........." << endl;
		return;
	}
	int len = 0;
	file >> len;
	if (!len)
	{
		cout << "���½�����Ա�����ļ�����ע�����Ա�˺�....." << endl;
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
	
	cout << "���������Ա�˺��Ե�½......." << endl;
	return;
}

void User::save_File()
{
	string new_file = "user";
	fstream file;
	file.open(new_file.c_str(), ios::out);
	if (file.bad())
	{
		cout << "�ļ���ʧ��.........." << endl;
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
	if (p->next_user == nullptr)  //��û����һ���ѣ����½�һ�����������޸�����
	{
		p->next_user = new user(_user);  //�ô�������޸Ľṹ��ʼ��
		p->next_user->next_user = nullptr;  //nullptr��������һ����
		return true;
	}
	while (p->next_user)  //��������һ����
	{
		if (p->next_user->user_name == _user.user_name)  //����
		{
			cout << "�û����ظ�������ʧ��......." << endl;
			return false;
		}
		p = p->next_user;  //�Ȳ�����Ҳ���ظ��ͺ������
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
	cout << "������ע���õ��û�����";
	cin >> tmp.user_name;
	if (find_By_Name(tmp.user_name) == nullptr)
	{
		cout << "������ע���õ����룺";
		cin >> tmp.user_passwd;
		insert(tmp);
	}
	else
	{
		cout << "��������û�����" << tmp.user_name << "�Ѵ��ڣ������������û���" << endl;
		login();
	}
	save_File();
}

bool User::logon()
{
	cout << "��½" << endl;
	cout << "�������½�û�����";
	string name;
	cin >> name;
	user* p = nullptr;
	if (find_By_Name(name))
	{
		p = find_By_Name(name);
		cout << "�������½���룺";
		string password;
		for (int i = 0; i < 3; i ++ ) {
			cin >> password;
			if (p->next_user->user_passwd == password)
			{
				cout << "��½�ɹ�.........." << endl;
				return true;
			}
			else 
			{
				cout << "�������x" << (i + 1) << "........." << endl;
				if (i != 2)cout << "��������������:";
				if (i == 2)
				{
					cout << "���Ѿ�����3�Σ������µ�¼.........." << endl;
					return false;
				}
			}
		}
	}
	else
	{
		cout << "û���ҵ����û�����" << endl;
		logon();
	}
	return false;
}

void User::delete_By_Name()
{
	user* p = nullptr;
	user* q = nullptr;
	cout << "������Ҫɾ�����û�����" << endl;
	string name;
	cin >> name;
	p = find_By_Name(name);
	if (p == nullptr)
	{
		cout << "û���ҵ��˺� \"" << name << "\", ɾ��ʧ��....." << endl;
	}
	q = p->next_user;
	p->next_user = nullptr;
	delete q;
	cout << "�ɹ�ɾ�� \"" << name << "\"���˺�......." << endl;
	save_File();
}

void User::show_User()
{
	user* p = nullptr;
	cout << "------------------------------------\n" << endl;
	for (p = head->next_user; p; p = p->next_user)
	{
		cout << "�û�����" << p->user_name << "	���룺" << p->user_passwd << endl;
	}
	cout << "------------------------------------\n" << endl;
}

