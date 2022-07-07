#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include "student.h"
#include "user.h"

using namespace std;

void show_Vistor_Menu();
void show_User_Menu();
void user_Vist();
void vistor_Vist();

int main()
{
	int model = 0;
	do 
	{
		cout << "���������ģʽ, 1:�ÿ����, 2:����Ա�û����\n����0:��������\n";
		cin >> model;
		switch (model) {
			case 1:
				vistor_Vist();
				break;
				
			case 2:
				user_Vist();
				break;
				
			case 0:
				break;
				
			default:
				cout << "��������ȷ��ѡ��!" << endl;
				cout << "���������ģʽ, 1:�ÿ����, 2:����Ա�û����\n����0:��������\n";
				cin >> model;
				break;
		}
	} while(model);
	
	return 0;
}

void show_Vistor_Menu() {
	cout << "+***********************************************+\n";
	cout << "|              ѧ����Ϣ����ϵͳ    Vistor       |\n";
	cout << "+***********************************************+\n";
	cout << "|  1����ȡѧ����Ϣ          2����ʾѧ����Ϣ     |\n";
	cout << "|  3����ѯѧ����Ϣ         11����ʾ�˵�         |\n";
	cout << "+***********************************************+\n";
	cout << "|   0���˳�                 �����20-1  ����ŵ  |\n";
	cout << "+***********************************************+\n";
}

void show_User_Menu() {
	cout << "+***********************************************+\n";
	cout << "|              ѧ����Ϣ����ϵͳ    Manage_User  |\n";
	cout << "+***********************************************+\n";
	cout << "|  1����ȡѧ����Ϣ        2����ʾѧ����Ϣ       |\n";
	cout << "|  3����ѯѧ����Ϣ        4������ѧ����Ϣ       |\n";
	cout << "|  5���޸�ѧ����Ϣ        6�����ѧ����Ϣ       |\n";
	cout << "|  7��ɾ��ѧ����Ϣ                              |\n";
	cout << "|  8���鿴����Ա�˺�      9��ע�����Ա�˺�     |\n";
	cout << "|  10��ɾ������Ա�˺�     11����ʾ�˵�          |\n";
	cout << "+***********************************************+\n";
	cout << "|   0���˳�                 �����20-1  ����ŵ  |\n";
	cout << "+***********************************************+\n";
}       

void user_Vist() {
	User user;
	user.read_File();
	if (user.logon()) {
		Student stu;
		int choice; 
		char str[20];
		show_User_Menu();
		do {
			cout << "������ָ�";
			cin >> choice;
			while (!cin)  
			{
				cin.clear();  
				cin >> str;   
				cout << "��������ȷ��ָ�" << endl;
				cin >> choice;
			}
			switch (choice) {
			case 1:
				stu.read_File();
				break;
				
			case 2:
				stu.show_Stu();
				break;
				
			case 3:
				stu.query_Stu();
				break;
				
			case 4:
				stu.save_To_File();
				break;
				
			case 5:
				stu.modify();
				break;
				
			case 6:
				stu.input_Stus();
				break;
				
			case 7:
				stu.delete_Stu();
				break;
				
			case 8:
				user.show_User();
				break;
				
			case 9:
				user.login();
				break;
				
			case 10:
				user.delete_By_Name();
				break;
				
			case 11:
				show_User_Menu();
				break;
				
			case 0:
				break;
				
			default:
				cout << "��������ȷ��ѡ��!" << endl;
				show_User_Menu();
				break;
			}
		} while (choice);
	}
}              

void vistor_Vist() {
	Student stu;
	int choice;
	char str[20];
	show_Vistor_Menu();
	do {
		cout << "������ָ�";
		cin >> choice;
		while (!cin)  
		{
			cin.clear();  
			cin >> str;   
			cout << "��������ȷ��ָ�" << endl;
			cin >> choice;
		}
		switch (choice) {
		case 1:
			stu.read_File();
			break;
			
		case 2:
			stu.show_Stu();
			break;
			
		case 3:
			stu.query_Stu();
			break;
		
		case 11:
			show_Vistor_Menu();
			break;
			
		case 0:
			break;
			
		default:
			cout << "��������ȷ��ѡ��!" << endl;
			show_User_Menu();
			break;
		}
	} while (choice);
}
