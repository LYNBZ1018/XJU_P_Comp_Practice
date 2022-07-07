#pragma once
#ifndef STUDENT_H
#define STUDENT_H

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <fstream>
using namespace std;

typedef struct student
{
	unsigned long long stu_id;  // 学号
 	string stu_name;  // 姓名
 	unsigned stu_age;  // 年龄
 	string stu_sex;  // 性别
 	string stu_birth;  // 出生日期
 	string stu_tel;  // 电话
 	map<string, double> stu_course;  // 课程
 	string stu_class;  // 班级
 	string stu_depart;  // 学院
 	
	student* stu_next;  // 用于链表
}student;

class Student
{
public:
	Student();  //构造函数
	~Student();  //析构函数

	//录入学生信息
	student* input_Stu(int method, student& tmp);  // method == 1 不读取学号; == 2 不读取姓名
	void input_Stus();  //连续录入学生信息

	//查找
	void query_Stu() const;
	student* find_By_Id(const unsigned long long& id) const;  // 根据学号查找
	student* find_By_Name(const string& name) const;  // 根据姓名查找
	void find_By_Depart(const string& depart) const; // 根据学院查找
	void find_By_Class(const string& _class) const; // 根据班级查找
	void find_Class_CourseRank(const string& _class) const;  // 查询班级课程排名

	//删除
	void delete_Stu();  //删除
	bool delete_By_Id(unsigned long long& id);  //根据学号删除
	bool delete_By_Name(string& name);  //根据姓名删除

	//修改
	void modify();  //修改
	bool modify_By_Id();  //根据学号修改
	bool modify_By_Name();  //根据姓名修改

	//输出
	void show_Stu() const;  //输出学生信息

	//文件读写
	void save_To_File();  //保存到文件
	void read_File();  //读取文件
	bool insert(const student& astu);

	unsigned headCount() const;
	
	student* getHead()
	{
		return head;
	}
	
private:
	student* head;  // 学生信息的链表的头结点
};

#endif
