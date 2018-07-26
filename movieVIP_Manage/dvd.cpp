#ifndef _DVD_H
#define _DVD_H

#include<iostream>
#include<string>
#include<iomanip>
#include"dvd_data.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::left;
using std::setw;
using std::setfill;
using std::right;

extern bool judgeNum(const string &s,int n);
extern bool judgeData(int y,int m,int d);
extern bool isFloat(double n);

DI::DVDInfo(string na,unsigned n,string r,string y_sh,string m_sh,string d_sh,int sto,double sco,string y_re,string m_re,string d_re):num(n),stock(sto),score(sco)
{
	strcpy_s(name,25,na.c_str());
	strcpy_s(role,27,r.c_str());
	strcpy_s(t_show.year,5,y_sh.c_str());
	strcpy_s(t_show.month,3,m_sh.c_str());
	strcpy_s(t_show.day,3,d_sh.c_str());
	strcpy_s(t_rent.year,5,y_re.c_str());
	strcpy_s(t_rent.month,3,m_re.c_str());
	strcpy_s(t_rent.day,3,d_re.c_str());
}

//复制构造函数
DI::DVDInfo(const DVDInfo & p):num(p.num),stock(p.stock),score(p.score)
{
	strcpy_s(name,25,p.name);
	strcpy_s(role,27,p.role);
	strcpy_s(t_rent.year,5,p.t_rent.year);
	strcpy_s(t_rent.month,3,p.t_rent.month);
	strcpy_s(t_rent.day,3,p.t_rent.day);
	strcpy_s(t_show.year,5,p.t_show.year);
	strcpy_s(t_show.month,3,p.t_show.month);
	strcpy_s(t_show.day,3,p.t_show.day);
}

//输出函数
void DI::display() const
{
	cout<<left<<setw(7)<<num;
	cout<<left<<setw(26)<<name;
	cout<<left<<setw(28)<<role;
	cout<<left<<setw(10)<<getShowTime();
	cout<<left<<setw(6)<<std::fixed<<std::setprecision(1)<<score;
	cout<<stock<<"\n";
}

//判断存货是否为空
bool DI::isEmpty() const
{
	if(stock==0)
		return true;
	else
		return false;
}

//获得编号
unsigned int DI::getNum() const
{
	return num;
}

//获得上映日期
string DI::getShowTime() const
{
	string t;
	string y=t_show.year;
	string m=t_show.month;
	string d=t_show.day;
	((t+=y)+=m)+=d;
	return t;
}

//获得被租用日期
string DI::getRentTime() const
{
	string t;
	string y=t_rent.year;
	string m=t_rent.month;
	string d=t_rent.day;
	((t+=y)+=m)+=d;
	return t;
}

//获得存货
int DI::getStock() const
{
	return stock;
}

//获得分数
double DI::getScore() const
{
	return score;
}

//设置被租用日期
void DI::setRentData(string y,string m,string d)
{
	strcpy_s(t_rent.year,5,y.c_str());
	strcpy_s(t_rent.month,3,m.c_str());
	strcpy_s(t_rent.day,3,d.c_str());
}

//设置存货
void DI::setStock(int n)
{
	stock+=n;
}

//修改信息
bool DI::editInfo()
{
	string Role;
	float Year;
	float Month;
	float Day;
	int t=-1;
	char c;
	float Stock;
	double Score;
	bool temp=true;
	while(true)
	{
		system("cls");
		do
		{
			if(!temp)
			{
				cout<<setw(31)<<" "<<"输入有误!"<<endl;
				cin.clear();
				cin.sync();
			}
			cout<<setw(31)<<" "<<"请输入相应编号进行修改:主    演——1"<<endl;
			cout<<setw(54)<<" "<<"上映日期——2"<<endl;
			cout<<setw(54)<<" "<<"存    货——3"<<endl;
			cout<<setw(54)<<" "<<"豆瓣评分——4"<<endl;
			cout<<setw(31)<<" "<<"请输入:";
			cin>>t;
			temp=false;
		}while(t<1||t>4||cin.fail()||isFloat(t));
		temp=true;
		if(t==1)	//修改主演
		{
			system("cls");
			do
			{
				if(temp)
				{
					cout<<setw(31)<<" "<<"请更新:";
				}
				cin>>Role;
				temp=false;
			}while(!judgeNum(Role,26));
			strcpy_s(role,27,Role.c_str());
			temp=true;
			cout<<setw(31)<<" "<<"修改成功!"<<endl;
		}
		else if(t==2)	//修改上映日期
		{
			system("cls");
			do
			{
				if(!temp)
				{
					cout<<setw(31)<<" "<<"输入错误!请您重新输入"<<endl;
					cin.sync();
				}
				cout<<setw(31)<<" "<<"请更新:"<<endl;
				cout<<setw(31)<<" "<<"上映日期(年):";
				cin>>Year;
				cout<<setw(31)<<" "<<"上映日期(月):";
				cin>>Month;
				cout<<setw(31)<<" "<<"上映日期(日):";
				cin>>Day;
				temp=false;
			}while(isFloat(Year)||isFloat(Month)||isFloat(Month)||!judgeData(Year,Month,Day)||cin.fail());
			sprintf_s(t_show.year,5,"%04d",(int)Year);
			sprintf_s(t_show.month,3,"%02d",(int)Month);
			sprintf_s(t_show.day,3,"%02d",(int)Day);
			temp=true;
			cout<<setw(31)<<" "<<"修改成功!"<<endl;
		}
		else if(t==3)	//修改存货
		{
			system("cls");
			do
			{
				if(!temp)
				{
					cout<<setw(31)<<" "<<"输入错误!请您重新输入"<<endl;
					cin.clear();
					cin.sync();
				}
				cout<<setw(31)<<" "<<"请更新(存货):";
				cin>>Stock;
				temp=false;
			}while(Stock<0||cin.fail()||isFloat(Stock));
			temp=true;
			stock=Stock;
			cout<<setw(31)<<" "<<"修改成功!"<<endl;
		}
		else			//修改豆瓣评分
		{
			system("cls");
			do
			{
				if(!temp)
				{
					cout<<setw(31)<<" "<<"输入错误!请您重新输入"<<endl;
					cin.clear();
					cin.sync();
				}
				cout<<setw(31)<<" "<<"请更新(评分):";
				cin>>Score;
				temp=false;
			}while(Score<0||Score>10||cin.fail());
			temp=true;
			score=Score;
			cout<<setw(31)<<" "<<"修改成功!"<<endl;
		}
		do
		{
			if(!temp)
			{
				cout<<setw(31)<<" "<<"输入错误!请您重新输入"<<endl;
				cin.sync();
			}
			cout<<setw(31)<<" "<<"是否继续修改?(Y/N)"<<endl;
			cout<<setw(31)<<" "<<"请输入:";
			cin>>c;
			temp=false;
		}while(c!='y'&&c!='Y'&&c!='n'&&c!='N');
		temp=true;
		if(c=='n'||c=='N')
		{
			return false;
		}
	}
}

#endif