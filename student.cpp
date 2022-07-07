#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "student.h"

using namespace std;

typedef pair<string, double> PAIR;

struct Cmp_By_Value
{
	bool operator()(const PAIR& l, const PAIR& r) 
	{
		return l.second > r.second;
	}
};

void show(student* p);

string filename("untitled");

// ���캯��
Student::Student()
{
	head = new student;
	head->stu_id = 0;
	head->stu_name = "No name";
	head->stu_next = nullptr;
}

// ��������
Student::~Student()
{
	student* p = head;
	student* q = nullptr;
	while (p)
	{
		q = p;
		p = q->stu_next;
		delete q;
	}
}



//¼��ѧ��
student* Student::input_Stu(int method, student& tmp)
{
	if (method == 1)
	{
		cout << "ѧ�ţ�";
		cin >> tmp.stu_id;
	}
	if (method == 2)
	{
		cout << "������";
		cin >> tmp.stu_name;
	}
	
	cout << "���䣺";
	cin >> tmp.stu_age;
	cout << "�Ա�";
	cin >> tmp.stu_sex;
	cout << "�������ڣ�";
	cin >> tmp.stu_birth;
	cout << "�绰��";
	cin >> tmp.stu_tel;
	for (map<string, double>::iterator iter = tmp.stu_course.begin(); iter != tmp.stu_course.end(); iter ++ ) 
	{
		cout << iter->first << ":";
		cin >> iter->second;
	}
	cout << "�༶��";
	cin >> tmp.stu_class;
	cout << "ѧԺ��";
	cin >> tmp.stu_depart;
	
	return &tmp;
}

// ����¼��ѧ��
void Student::input_Stus()
{
	student tmp;
	cout << "ѧ��(0��������)��";
	cin >> tmp.stu_id;

	while (tmp.stu_id)
	{
		if (find_By_Id(tmp.stu_id) == nullptr)
		{
			cout << "������";
			cin >> tmp.stu_name;
			cout << "���䣺";
			cin >> tmp.stu_age;
			cout << "�Ա�";
			cin >> tmp.stu_sex;
			cout << "�������ڣ�";
			cin >> tmp.stu_birth;
			cout << "�绰��";
			cin >> tmp.stu_tel;
			int flag = 1;
			do
			{
				string course;
				double score;
				cout << "�γ�" << "����:" << endl;
				cin >> 	course;
				cout << "����:" << endl;
				cin >> score;
				tmp.stu_course.insert(pair<string, double>(course, score));
				cout << "����0��������γ̳ɼ�,�����������ּ�������:";
				cin >> flag;	
			} while (flag != 0);
			cout << "�༶��";
			cin >> tmp.stu_class;
			cout << "ѧԺ��";
			cin >> tmp.stu_depart;
			
			insert(tmp);
		}
		else
		{
			cout << "�ظ���ѧ�ţ�" << tmp.stu_id << endl;
		}
		cout << "ѧ��(0��������)��";
		cin >> tmp.stu_id;
	}
}



//����

void Student::query_Stu() const
{
	int select;
	unsigned long long id;
	string name;
	string depart;
	string _class;
	student* p;
	cout << "1.��ѧ�Ų�ѯ\n2.��������ѯ\n3.����ѧԺ��ѯ\n4.���༶��ѯ\n5.���Ұ༶�γ�����\n0.����\n";
	cin >> select;
	switch (select)
	{
	case 1:
		cout << "������Ҫ���ҵ�ѧ�ţ�";
		cin >> id;
		if ((p = find_By_Id(id)))
		{
			show(p->stu_next);
		}
		break;
		
	case 2:
		cout << "������Ҫ���ҵ�������";
		cin >> name;
		if ((p = find_By_Name(name)))
		{
			show(p->stu_next);
		}
		break;
		
	case 3:
		cout << "������Ҫ���ҵ�ѧԺ��";
		cin >> depart;
		find_By_Depart(depart);
		break;
		
	case 4:
		cout << "������Ҫ���ҵİ༶��";
		cin >> _class;
		find_By_Class(_class);
		break;
	
	case 5:
		cout << "������Ҫ���ҵİ༶��";
		cin >> _class;
		find_Class_CourseRank(_class);
		
	case 0:
		return;
	default:
		cout << "����ʧ�ܣ�������ѡ����ҵķ�ʽ��" << endl;
	}
}

// ����ѧ�Ų���
student* Student::find_By_Id(const unsigned long long& id) const
{
	student* p;
	for (p = head; p->stu_next; p = p->stu_next)
	{
		if (p->stu_next->stu_id == id)
		{
			return p;
		}
	}
	cout << "û���ҵ������ID��" << endl;
	return nullptr;
}

// ������������
student* Student::find_By_Name(const string& name) const
{
	student* p;
	for (p = head; p->stu_next; p = p->stu_next)
	{
		if (p->stu_next->stu_name == name)
		{
			return p;
		}
	}
	cout << "û���ҵ������������" << endl;
	return nullptr;
}

// ����ѧԺ����
void Student::find_By_Depart(const string& depart) const
{
	student* p;
		int flag = 0;
		for (p = head; p->stu_next; p = p->stu_next)
		{
			if (p->stu_next->stu_depart == depart)
			{
				flag ++ ;
				show(p->stu_next);
			}
		}
		if (flag == 0) {
			cout << "û���ҵ������ѧԺ��" << endl;	
		} else {
			cout << "һ���ҵ���ѧԺѧ��" << flag << "��" << endl;
		}
}

// ���ݰ༶����
void Student::find_By_Class(const string& _class) const 
{
	student* p;
	int flag = 0;
	for (p = head; p->stu_next; p = p->stu_next)
	{
		if (p->stu_next->stu_class == _class)
		{
			flag ++ ;
			show(p->stu_next);
		}
	}
	if (flag == 0) 
	{
		cout << "û���ҵ�����İ༶��" << endl;	
	} else {
		cout << "һ���ҵ��ð༶ѧ��" << flag << "��" << endl;
	}
}

// ��ѯ�༶�γ�����
void Student::find_Class_CourseRank(const string& _class) const
{
	int flag = 0;
	Student _stu;
	student* p;
	for (p = head; p->stu_next; p = p->stu_next)
	{
		if (p->stu_next->stu_class == _class)
		{
			_stu.insert(*p->stu_next);
			flag ++ ;
		}
	}
	if (flag == 0) 
	{
		cout << "û���ҵ�����İ༶��" << endl;	
	} 
	else 
	{
		cout << "�ð༶����ѧ��" << flag << "��" << endl;
		student* pHead = _stu.getHead();
		p = pHead->stu_next;
		for (map<string, double>::iterator iter = p->stu_course.begin(); iter != p->stu_course.end(); iter ++ )
		{
			cout << iter->first << ' ';
		}
		cout << endl;
		cout << "������Ҫ���ҵĿγ�����";
		string course;
		cin >> course;
		vector<PAIR> name_course;
		for (p = pHead; p->stu_next; p = p->stu_next)
		{
			string name;
			double _score;
			name = p->stu_next->stu_name;
			for (map<string, double>::iterator iter = p->stu_next->stu_course.begin(); iter != p->stu_next->stu_course.end(); iter ++ )
			{
				string tmp = iter->first;
				if (course.compare(tmp) == 0)
				{
					_score = iter->second;
					break;	
				}
			}
			name_course.push_back(pair<string, double>(name, _score));
		}
		sort(name_course.begin(), name_course.end(), Cmp_By_Value());
		for (int i = 0; i != name_course.size(); i ++ )
		{
			cout << "��" << (i + 1) << "��," << name_course.at(i).first << ": " << name_course.at(i).second << endl;
		}
	} 
}
	
	

//ɾ��
void Student::delete_Stu()
{
	int select;
	unsigned long long id;
	string name;
	cout << "1.��ѧ��ɾ��\n2.������ɾ��\n0.����\n";
	cin >> select;
	switch (select)
	{
	case 1:
		cout << "��������Ҫɾ����ѧ�ţ�";
		cin >> id;
		delete_By_Id(id);
		break;
		
	case 2:
		cout << "����������Ҫɾ����������";
		cin >> name;
		delete_By_Name(name);
		break;
		
	case 0:
		return;
		
	default:
		cout << "ɾ��ʧ�ܣ�������ѡ��ɾ���ķ�ʽ��" << endl;
	}
}

// ����ѧ��ɾ��
bool Student::delete_By_Id(unsigned long long& id)
{
	student* p = nullptr;
	student* q = nullptr;
	p = find_By_Id(id);
	if (p == nullptr)
	{
		cout << "û���ҵ�ѧ���ǣ�\"" << id << "\"��ѧ����ɾ��ʧ�ܣ�" << endl;
		return false;
	}
	q = p->stu_next;
	p->stu_next = q->stu_next;
	delete q;
	cout << "�ɹ�ɾ��ѧ��Ϊ��\"" << id << "\"��ѧ������Ϣ" << endl;
	return true;
}

// ��������ɾ��
bool Student::delete_By_Name(string& name)
{
	student* p = nullptr;
	student* q = nullptr;
	p = find_By_Name(name);
	if (p == nullptr)
	{
		cout << "û���ҵ�����Ϊ��\"" << name << "\"��ѧ����ɾ��ʧ�ܣ�" << endl;
		return false;
	}
	q = p->stu_next;
	p->stu_next = q->stu_next;
	delete q;
	cout << "�ɹ�ɾ������Ϊ��\"" << name << "\"����Ϣ\n";
	return true;
}



//�޸�
void Student::modify()
{
	int select;
	cout << "1.��ѧ���޸�\n2.�������޸�\n0.����\n";
	cin >> select;
	switch (select)
	{
	case 1:
		if (modify_By_Id())
		{
			cout << "�޸ĳɹ���\n";
		}
		break;
	case 2:
		if (modify_By_Name())
		{
			cout << "�޸ĳɹ���\n";
		}
		break;
	case 0:
		return;
	default:
		cout << "�޸�ʧ�ܣ�������ѡ���޸ĵķ�ʽ��" << endl;
		break;
	}
}

// ����ѧ���޸�
bool Student::modify_By_Id()
{
	student* p = nullptr;
	unsigned id;
	cout << "������Ҫ�޸ĵ�ѧ�ţ�" << endl;
	cin >> id;
	p = find_By_Id(id);
	if (p == nullptr)
	{
		cout << "û���ҵ�ѧ���ǣ�\"" << id << "\"��ѧ�����޸�ʧ�ܣ�\n";
		return false;
	}
	input_Stu(1, *(p->stu_next));
	return true;
}

// ���������޸�
bool Student::modify_By_Name()
{
	student* p;
	string name;
	cout << "��������Ҫ�޸ĵ�������";
	cin >> name;
	p = find_By_Name(name);
	if (p == nullptr)
	{
		cout << "û���ҵ�����Ϊ��\"" << name << "\"��ѧ�����޸�ʧ�ܣ�\n";
		return false;
	}
	input_Stu(2, *(p->stu_next));
	return true;
}


//�ļ���д
void Student::save_To_File()
{
	string new_file;
	cout << "������Ҫ������ļ�����";
	cin >> new_file;
	fstream file;
	file.open(new_file.c_str(), ios::out);
	if (file.bad())
	{
		cout << "�ļ���ʧ�ܣ�" << endl;
		return;
	}
	int len = headCount();
	file << len << endl;
	student* pHead = head->stu_next;
	while (pHead != nullptr)
	{
		file << pHead->stu_id << endl;
		file << pHead->stu_name << endl;
		file << pHead->stu_sex << endl;
		file << pHead->stu_age << endl;
		file << pHead->stu_birth << endl;
		for (map<string, double>::iterator iter = pHead->stu_course.begin(); iter != pHead->stu_course.end(); iter ++ ) 
		{
			file << iter->first << endl;
			file << iter->second << endl;
		}
		file << pHead->stu_depart << endl;
		file << pHead->stu_class << endl;
		pHead = pHead->stu_next;
	}
	file.close();
	cout << "����ɹ���" << endl;
	filename = new_file;
	return;
}

void Student::read_File()
{
	string new_file;
	cout << "������Ҫ��ȡ���ļ�����";
	cin >> new_file;
	fstream file;
	file.open(new_file.c_str(), ios::in);
	if (file.bad())
	{
		cout << "�ļ���ʧ�ܣ�" << endl;
		return;
	}
	int len = 0;
	file >> len;
	while (!len)
	{
		cout << "�ļ������쳣��" << endl;
		return;
	}

	file.get();
	while (len--)
	{
		student pHead;
		file >> pHead.stu_id;
		file >> pHead.stu_name;
		file >> pHead.stu_age;
		file >> pHead.stu_sex;
		file >> pHead.stu_birth;
		file >> pHead.stu_tel;
		for (int i = 0; i < 4; i ++ ) 
		{
			string course;
			double score;
			file >> course;
			file >> score;
			pHead.stu_course.insert(pair<string, double>(course, score));
		}
		file >> pHead.stu_class;
		file >> pHead.stu_depart;
		insert(pHead);
	}
	file.close();
	cout << "�ļ�����ɹ���" << endl;
	filename = new_file;
	return;
}

bool Student::insert(const student& stu)
{
	student* newnode = nullptr;
	student* p = head;
	if (p->stu_next == nullptr)  //��û����һ���ѣ����½�һ�������洢����
	{
		p->stu_next = new student(stu);  //�ô�������޸Ľṹ��ʼ��
		p->stu_next->stu_next = nullptr;  //nullptr��������һ����
		return true;
	}
	while (p->stu_next)  //��������һ����
	{
		if (p->stu_next->stu_id == stu.stu_id)  //����
		{
			cout << "ѧ���ظ�������ʧ�ܣ�" << endl;
			return false;
		}
		if (p->stu_next->stu_id > stu.stu_id)  //�����һ���ѵ�id���ڴ����id
		{
			newnode = new student(stu);   //newnodeָ���ʼ�޸Ľṹ
			newnode->stu_next = p->stu_next;
			p->stu_next = newnode;
			return true;
		}
		p = p->stu_next;
	}
	p->stu_next = new student(stu);
	p->stu_next->stu_next = nullptr;
	return true;
}

//��ʾ����
void Student::show_Stu() const
{
	student* p = nullptr;
		cout << "**************************************" << endl;
		for (p = head->stu_next; p; p = p->stu_next) {
			show(p);
		}
		cout << "**************************************" << endl;
}

void show(student* p) 
{
	cout << "  ѧ�ţ� " << p->stu_id << "  ������ " << p->stu_name << "  ���䣺 " << p->stu_age;
	cout << "  �Ա� " << p->stu_sex << "  �������ڣ� " << p->stu_birth << "  �绰�� " << p->stu_tel;
	for (map<string, double>::iterator iter = p->stu_course.begin(); iter != p->stu_course.end(); iter ++ ) 
	{
		cout << "  " << iter->first << ":" << iter->second << " ";
	}
	cout << "  �༶�� " << p->stu_class << "  ѧԺ�� " << p->stu_depart << endl;
	cout << endl;
}

// �����������м���ѧ��
unsigned Student::headCount() const
{
	unsigned cnt = 0;
	student* p;
	for (p = head->stu_next; p; p = p->stu_next, ++cnt);
	return cnt;
}