#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<cstdlib>
#include<atltime.h>
#include"dvd_data.h"
#include"vip_data.h"
#include"manager.h"

using std::cout;
using std::cin;
using std::left;
using std::setw;
using std::string;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::ios_base;

extern void enroll();//注册
extern void loginVIP();//登录——VIP
extern void loginManager();//登录——管理员

int main(void)
{
	bool isFloat(double n);
	/*string a;
	string b;
	cin>>a;
	cin>>b;
	ManaInfo c(a,b);
	c.setGain(3);
	ofstream s("MANAGER.txt",ios_base::out|ios_base::binary);
	s.write(reinterpret_cast<char*>(&c),sizeof(c));
	s.close();*/
	float order=0;
	bool temp=true;
	cout<<" ———————————————欢迎来到电影俱乐部———————————————"<<endl;
	while(true)
	{
		
		cout<<setw(31)<<" "<<"登　　录——1"<<endl;
		cout<<setw(31)<<" "<<"注　　册——2"<<endl;
		cout<<setw(31)<<" "<<"退出系统——3"<<endl;
		do
		{
			if(!temp)
			{
				cout<<setw(31)<<" "<<"输入错误！\n";
				cin.clear();
				cin.sync();
			}
			cout<<setw(31)<<" "<<"请输入:";
			cin>>order;
			temp=false;
		}while(order<1||order>3||cin.fail()||isFloat(order));
		temp=true;
		system("cls");
		if(order==2)				//注册
		{
			system("cls");
			enroll();
		}
		else if(order==1)			//登录
		{
			cout<<setw(31)<<" "<<"选择您的身份:"<<endl;
			cout<<setw(31)<<" "<<"会  员——1"<<endl;
			cout<<setw(31)<<" "<<"管理员——2"<<endl;
			do
			{
				if(!temp)
				{
					cout<<setw(31)<<" "<<"输入错误！\n";
					cin.clear();
					cin.sync();
				}
				cout<<setw(31)<<" "<<"请输入:";
				cin>>order;
				temp=false;
			}while(order!=1&&order!=2||cin.fail());
			if(order==1)		//会员登录页面
			{
				loginVIP();
			}
			else if(order==2)	//管理员登录页面
			{
				loginManager();
			}
		}
		else
		{
			break;
		}
		temp=true;
	}
	system("pause");
	return 0;
}

//判断字符串长度是否合法
bool judgeNum(const string &s,int n)
{
	if(s.length()>n)
	{
		cout<<setw(31)<<" "<<"长度不应超过"<<n<<"个字节!"<<endl;
		cout<<setw(31)<<" "<<"请重新输入:";
		return false;
	}
	else
	{
		return true;
	}
}

//判断是否为小数
bool isFloat(double n)
{
	return (n-floor(n)!=0);
}