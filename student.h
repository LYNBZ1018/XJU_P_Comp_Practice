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
	unsigned long long stu_id;  // ѧ��
 	string stu_name;  // ����
 	unsigned stu_age;  // ����
 	string stu_sex;  // �Ա�
 	string stu_birth;  // ��������
 	string stu_tel;  // �绰
 	map<string, double> stu_course;  // �γ�
 	string stu_class;  // �༶
 	string stu_depart;  // ѧԺ
 	
	student* stu_next;  // ��������
}student;

class Student
{
public:
	Student();  //���캯��
	~Student();  //��������

	//¼��ѧ����Ϣ
	student* input_Stu(int method, student& tmp);  // method == 1 ����ȡѧ��; == 2 ����ȡ����
	void input_Stus();  //����¼��ѧ����Ϣ

	//����
	void query_Stu() const;
	student* find_By_Id(const unsigned long long& id) const;  // ����ѧ�Ų���
	student* find_By_Name(const string& name) const;  // ������������
	void find_By_Depart(const string& depart) const; // ����ѧԺ����
	void find_By_Class(const string& _class) const; // ���ݰ༶����
	void find_Class_CourseRank(const string& _class) const;  // ��ѯ�༶�γ�����

	//ɾ��
	void delete_Stu();  //ɾ��
	bool delete_By_Id(unsigned long long& id);  //����ѧ��ɾ��
	bool delete_By_Name(string& name);  //��������ɾ��

	//�޸�
	void modify();  //�޸�
	bool modify_By_Id();  //����ѧ���޸�
	bool modify_By_Name();  //���������޸�

	//���
	void show_Stu() const;  //���ѧ����Ϣ

	//�ļ���д
	void save_To_File();  //���浽�ļ�
	void read_File();  //��ȡ�ļ�
	bool insert(const student& astu);

	unsigned headCount() const;
	
	student* getHead()
	{
		return head;
	}
	
private:
	student* head;  // ѧ����Ϣ�������ͷ���
};

#endif
