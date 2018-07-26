#ifndef _MANAGER_H
#define _MANAGER_H

#include<iostream>
#include<string>
#include<iomanip>
#include"manager.h"

using std::cout;
using std::cin;
using std::setw;
using std::setfill;
using std::right;
using std::endl;

//构造函数
ManaInfo::ManaInfo(string n,string p,string y,string m,string d,double s):sum(s)
{
	strcpy_s(name,19,n.c_str());
	strcpy_s(password,13,p.c_str());
	strcpy_s(t_business.year,5,y.c_str());
	strcpy_s(t_business.month,3,m.c_str());
	strcpy_s(t_business.day,3,d.c_str());
}

//复制构造函数
ManaInfo::ManaInfo(const ManaInfo &p):sum(p.sum)
{
	strcpy_s(name,19,p.name);
	strcpy_s(password,13,p.password);
	strcpy_s(t_business.year,5,p.t_business.year);
	strcpy_s(t_business.month,3,p.t_business.month);
	strcpy_s(t_business.day,3,p.t_business.day);
}

//修改数据
int ManaInfo::edit(const int order)
{
	switch(order)
	{
	case 1:
		cout<<"昵称:";
		cin>>name;
		break;
	case 2:
		cout<<"密  码:";
		cin>>password;
		break;
	default:
		return 0;
	}
	return 1;
}

//获得营业的日期
string ManaInfo::getBusinessTime() const
{
	string t;
	string y=t_business.year;
	string m=t_business.month;
	string d=t_business.day;
	((t+=y)+=m)+=d;
	return t;
}

//获得密码
string ManaInfo::getPassword() const
{
	return password;
}

//重设密码
void ManaInfo::setPassword(string p)
{
	strcpy_s(password,13,p.c_str());
}

//设置收益信息
void ManaInfo::setGain(double s)
{
	sum=+s;
}

#endif