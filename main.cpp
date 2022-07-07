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
		cout << "请输入访问模式, 1:访客身份, 2:管理员用户身份\n输入0:结束程序\n";
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
				cout << "请输入正确的选项!" << endl;
				cout << "请输入访问模式, 1:访客身份, 2:管理员用户身份\n输入0:结束程序\n";
				cin >> model;
				break;
		}
	} while(model);
	
	return 0;
}

void show_Vistor_Menu() {
	cout << "+***********************************************+\n";
	cout << "|              学生信息管理系统    Vistor       |\n";
	cout << "+***********************************************+\n";
	cout << "|  1、读取学生信息          2、显示学生信息     |\n";
	cout << "|  3、查询学生信息         11、显示菜单         |\n";
	cout << "+***********************************************+\n";
	cout << "|   0、退出                 计算机20-1  刘宇诺  |\n";
	cout << "+***********************************************+\n";
}

void show_User_Menu() {
	cout << "+***********************************************+\n";
	cout << "|              学生信息管理系统    Manage_User  |\n";
	cout << "+***********************************************+\n";
	cout << "|  1、读取学生信息        2、显示学生信息       |\n";
	cout << "|  3、查询学生信息        4、保存学生信息       |\n";
	cout << "|  5、修改学生信息        6、添加学生信息       |\n";
	cout << "|  7、删除学生信息                              |\n";
	cout << "|  8、查看管理员账号      9、注册管理员账号     |\n";
	cout << "|  10、删除管理员账号     11、显示菜单          |\n";
	cout << "+***********************************************+\n";
	cout << "|   0、退出                 计算机20-1  刘宇诺  |\n";
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
			cout << "请输入指令：";
			cin >> choice;
			while (!cin)  
			{
				cin.clear();  
				cin >> str;   
				cout << "请输入正确的指令：" << endl;
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
				cout << "请输入正确的选项!" << endl;
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
		cout << "请输入指令：";
		cin >> choice;
		while (!cin)  
		{
			cin.clear();  
			cin >> str;   
			cout << "请输入正确的指令：" << endl;
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
			cout << "请输入正确的选项!" << endl;
			show_User_Menu();
			break;
		}
	} while (choice);
}
