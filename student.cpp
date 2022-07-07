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

// 构造函数
Student::Student()
{
	head = new student;
	head->stu_id = 0;
	head->stu_name = "No name";
	head->stu_next = nullptr;
}

// 析构函数
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



//录入学生
student* Student::input_Stu(int method, student& tmp)
{
	if (method == 1)
	{
		cout << "学号：";
		cin >> tmp.stu_id;
	}
	if (method == 2)
	{
		cout << "姓名：";
		cin >> tmp.stu_name;
	}
	
	cout << "年龄：";
	cin >> tmp.stu_age;
	cout << "性别：";
	cin >> tmp.stu_sex;
	cout << "出生日期：";
	cin >> tmp.stu_birth;
	cout << "电话：";
	cin >> tmp.stu_tel;
	for (map<string, double>::iterator iter = tmp.stu_course.begin(); iter != tmp.stu_course.end(); iter ++ ) 
	{
		cout << iter->first << ":";
		cin >> iter->second;
	}
	cout << "班级：";
	cin >> tmp.stu_class;
	cout << "学院：";
	cin >> tmp.stu_depart;
	
	return &tmp;
}

// 连续录入学生
void Student::input_Stus()
{
	student tmp;
	cout << "学号(0结束输入)：";
	cin >> tmp.stu_id;

	while (tmp.stu_id)
	{
		if (find_By_Id(tmp.stu_id) == nullptr)
		{
			cout << "姓名：";
			cin >> tmp.stu_name;
			cout << "年龄：";
			cin >> tmp.stu_age;
			cout << "性别：";
			cin >> tmp.stu_sex;
			cout << "出生日期：";
			cin >> tmp.stu_birth;
			cout << "电话：";
			cin >> tmp.stu_tel;
			int flag = 1;
			do
			{
				string course;
				double score;
				cout << "课程" << "名称:" << endl;
				cin >> 	course;
				cout << "分数:" << endl;
				cin >> score;
				tmp.stu_course.insert(pair<string, double>(course, score));
				cout << "输入0结束输入课程成绩,输入其他数字继续输入:";
				cin >> flag;	
			} while (flag != 0);
			cout << "班级：";
			cin >> tmp.stu_class;
			cout << "学院：";
			cin >> tmp.stu_depart;
			
			insert(tmp);
		}
		else
		{
			cout << "重复的学号：" << tmp.stu_id << endl;
		}
		cout << "学号(0结束输入)：";
		cin >> tmp.stu_id;
	}
}



//查找

void Student::query_Stu() const
{
	int select;
	unsigned long long id;
	string name;
	string depart;
	string _class;
	student* p;
	cout << "1.按学号查询\n2.按姓名查询\n3.按性学院查询\n4.按班级查询\n5.查找班级课程排名\n0.返回\n";
	cin >> select;
	switch (select)
	{
	case 1:
		cout << "请输入要查找的学号：";
		cin >> id;
		if ((p = find_By_Id(id)))
		{
			show(p->stu_next);
		}
		break;
		
	case 2:
		cout << "请输入要查找的姓名：";
		cin >> name;
		if ((p = find_By_Name(name)))
		{
			show(p->stu_next);
		}
		break;
		
	case 3:
		cout << "请输入要查找的学院：";
		cin >> depart;
		find_By_Depart(depart);
		break;
		
	case 4:
		cout << "请输入要查找的班级：";
		cin >> _class;
		find_By_Class(_class);
		break;
	
	case 5:
		cout << "请输入要查找的班级：";
		cin >> _class;
		find_Class_CourseRank(_class);
		
	case 0:
		return;
	default:
		cout << "查找失败，请重新选择查找的方式！" << endl;
	}
}

// 根据学号查找
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
	cout << "没有找到输入的ID！" << endl;
	return nullptr;
}

// 根据姓名查找
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
	cout << "没有找到输入的姓名！" << endl;
	return nullptr;
}

// 根据学院查找
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
			cout << "没有找到输入的学院！" << endl;	
		} else {
			cout << "一共找到该学院学生" << flag << "人" << endl;
		}
}

// 根据班级查找
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
		cout << "没有找到输入的班级！" << endl;	
	} else {
		cout << "一共找到该班级学生" << flag << "人" << endl;
	}
}

// 查询班级课程排名
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
		cout << "没有找到输入的班级！" << endl;	
	} 
	else 
	{
		cout << "该班级共有学生" << flag << "人" << endl;
		student* pHead = _stu.getHead();
		p = pHead->stu_next;
		for (map<string, double>::iterator iter = p->stu_course.begin(); iter != p->stu_course.end(); iter ++ )
		{
			cout << iter->first << ' ';
		}
		cout << endl;
		cout << "请输入要查找的课程名：";
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
			cout << "第" << (i + 1) << "名," << name_course.at(i).first << ": " << name_course.at(i).second << endl;
		}
	} 
}
	
	

//删除
void Student::delete_Stu()
{
	int select;
	unsigned long long id;
	string name;
	cout << "1.按学号删除\n2.按姓名删除\n0.返回\n";
	cin >> select;
	switch (select)
	{
	case 1:
		cout << "请输入您要删除的学号：";
		cin >> id;
		delete_By_Id(id);
		break;
		
	case 2:
		cout << "请输入与您要删除的姓名：";
		cin >> name;
		delete_By_Name(name);
		break;
		
	case 0:
		return;
		
	default:
		cout << "删除失败，请重新选择删除的方式！" << endl;
	}
}

// 根据学号删除
bool Student::delete_By_Id(unsigned long long& id)
{
	student* p = nullptr;
	student* q = nullptr;
	p = find_By_Id(id);
	if (p == nullptr)
	{
		cout << "没有找到学号是：\"" << id << "\"的学生，删除失败！" << endl;
		return false;
	}
	q = p->stu_next;
	p->stu_next = q->stu_next;
	delete q;
	cout << "成功删除学号为：\"" << id << "\"的学生的信息" << endl;
	return true;
}

// 根据姓名删除
bool Student::delete_By_Name(string& name)
{
	student* p = nullptr;
	student* q = nullptr;
	p = find_By_Name(name);
	if (p == nullptr)
	{
		cout << "没有找到姓名为：\"" << name << "\"的学生，删除失败！" << endl;
		return false;
	}
	q = p->stu_next;
	p->stu_next = q->stu_next;
	delete q;
	cout << "成功删除姓名为：\"" << name << "\"的信息\n";
	return true;
}



//修改
void Student::modify()
{
	int select;
	cout << "1.按学号修改\n2.按姓名修改\n0.返回\n";
	cin >> select;
	switch (select)
	{
	case 1:
		if (modify_By_Id())
		{
			cout << "修改成功！\n";
		}
		break;
	case 2:
		if (modify_By_Name())
		{
			cout << "修改成功！\n";
		}
		break;
	case 0:
		return;
	default:
		cout << "修改失败，请重新选择修改的方式！" << endl;
		break;
	}
}

// 根据学号修改
bool Student::modify_By_Id()
{
	student* p = nullptr;
	unsigned id;
	cout << "请输入要修改的学号：" << endl;
	cin >> id;
	p = find_By_Id(id);
	if (p == nullptr)
	{
		cout << "没有找到学号是：\"" << id << "\"的学生，修改失败！\n";
		return false;
	}
	input_Stu(1, *(p->stu_next));
	return true;
}

// 根据姓名修改
bool Student::modify_By_Name()
{
	student* p;
	string name;
	cout << "请输入您要修改的姓名：";
	cin >> name;
	p = find_By_Name(name);
	if (p == nullptr)
	{
		cout << "没有找到姓名为：\"" << name << "\"的学生，修改失败！\n";
		return false;
	}
	input_Stu(2, *(p->stu_next));
	return true;
}


//文件读写
void Student::save_To_File()
{
	string new_file;
	cout << "请输入要保存的文件名：";
	cin >> new_file;
	fstream file;
	file.open(new_file.c_str(), ios::out);
	if (file.bad())
	{
		cout << "文件打开失败！" << endl;
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
	cout << "保存成功！" << endl;
	filename = new_file;
	return;
}

void Student::read_File()
{
	string new_file;
	cout << "请输入要读取的文件名：";
	cin >> new_file;
	fstream file;
	file.open(new_file.c_str(), ios::in);
	if (file.bad())
	{
		cout << "文件打开失败！" << endl;
		return;
	}
	int len = 0;
	file >> len;
	while (!len)
	{
		cout << "文件数据异常！" << endl;
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
	cout << "文件读入成功！" << endl;
	filename = new_file;
	return;
}

bool Student::insert(const student& stu)
{
	student* newnode = nullptr;
	student* p = head;
	if (p->stu_next == nullptr)  //当没有下一个堆，这新建一个堆来存储数据
	{
		p->stu_next = new student(stu);  //用传入的已修改结构初始化
		p->stu_next->stu_next = nullptr;  //nullptr处理再下一个堆
		return true;
	}
	while (p->stu_next)  //当存在下一个堆
	{
		if (p->stu_next->stu_id == stu.stu_id)  //判重
		{
			cout << "学号重复，插入失败！" << endl;
			return false;
		}
		if (p->stu_next->stu_id > stu.stu_id)  //如果下一个堆的id大于传入的id
		{
			newnode = new student(stu);   //newnode指向初始修改结构
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

//显示函数
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
	cout << "  学号： " << p->stu_id << "  姓名： " << p->stu_name << "  年龄： " << p->stu_age;
	cout << "  性别： " << p->stu_sex << "  出生日期： " << p->stu_birth << "  电话： " << p->stu_tel;
	for (map<string, double>::iterator iter = p->stu_course.begin(); iter != p->stu_course.end(); iter ++ ) 
	{
		cout << "  " << iter->first << ":" << iter->second << " ";
	}
	cout << "  班级： " << p->stu_class << "  学院： " << p->stu_depart << endl;
	cout << endl;
}

// 计算链表中有几个学生
unsigned Student::headCount() const
{
	unsigned cnt = 0;
	student* p;
	for (p = head->stu_next; p; p = p->stu_next, ++cnt);
	return cnt;
}
