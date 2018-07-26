#ifndef _VIP_H
#define _VIP_H

#include<iostream>
#include<string>
#include<iomanip>
#include<atltime.h>
#include"vip_data.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::left;
using std::setw;

//һ�㹹�캯��
MI::MemberInfo(std::string n,std::string nu,std::string p,string y,string m,string d,double bal,int sta):balance(bal),state(sta)
{
	strcpy_s(password,13,p.c_str());
	strcpy_s(name,19,n.c_str());
	strcpy_s(num,13,nu.c_str());
	strcpy_s(enroll.year,5,y.c_str());
	strcpy_s(enroll.month,3,m.c_str());
	strcpy_s(enroll.day,3,d.c_str());
	for(int i=0;i<3;i++)
	{
		strcpy(borrowDVD[i].name,"");
	}
}

//���ƹ��캯��
MI::MemberInfo(const MemberInfo &p)
{
	strcpy_s(password,13,p.password);
	strcpy_s(name,19,p.name);
	strcpy_s(num,13,p.num);
	strcpy_s(this->enroll.year,5,p.enroll.year);
	strcpy_s(this->enroll.month,3,p.enroll.month);
	strcpy_s(this->enroll.day,3,p.enroll.day);
	for(int i=0;i<3;i++)
	{
		this->borrowDVD[i]=p.borrowDVD[i];
	}
}

//���
void MI::display() const
{
	cout<<setw(4)<<" ";
	cout<<left<<setw(14)<<num;
	cout<<left<<setw(24)<<name;
	cout<<left<<setw(12)<<std::fixed<<std::setprecision(2)<<balance;
	cout<<left<<setw(9)<<state;
	cout<<getEnrollTime()<<endl;
	cout<<setw(4)<<" ";
	cout<<"����DVD��Ϣ:";
	if(strcmp(borrowDVD[0].name,""))
	{
		cout<<" ("<<borrowDVD[0].num<<")";
		cout<<borrowDVD[0].name<<"����"<<borrowDVD[0].getRentTime()<<"\\";
	}
	if(strcmp(borrowDVD[1].name,""))
	{
		cout<<" ("<<borrowDVD[1].num<<")";
		cout<<borrowDVD[1].name<<"����"<<borrowDVD[1].getRentTime()<<"\\";
	}
	if(strcmp(borrowDVD[2].name,""))
	{
		cout<<" ("<<borrowDVD[2].num<<")";
		cout<<borrowDVD[2].name<<"����"<<borrowDVD[2].getRentTime()<<"\\";
	}
	cout<<endl;
}

//�޸�
int MI::edit(const int order)
{
	switch(order)
	{
	case 1:
		cout<<"�û���:";
		cin>>name;
		break;
	case 2:
		cout<<"��  ��:";
		cin>>password;
		break;
	default:
		return 0;
	}
	return 1;
}

//���ɹ����DVD����
int MI::buy()
{
	return (3-state);
}

//����û����
double MI::getBalance() const
{
	return balance;
}

//�������
string MI::getPassword() const
{
	return password;
}

//���ע������
string MI::getEnrollTime() const
{
	string t;
	((t+=enroll.year)+=enroll.month)+=enroll.day;
	return t;
}

//���������
int MI::getState() const
{
	return state;
}

//��ñ��
string MI::getNum() const
{
	return num;
}

//�������õ�DVD��Ϣ
void MI::setDVDInfo_rent(DI p)
{
	char year[5];
	char month[3];
	char day[3];
	CTime t=CTime::GetCurrentTime();
	for(int i=0;i<3;i++)
	{
		if(!(strcmp(borrowDVD[i].name,"")))
		{
			borrowDVD[i]=p;
			sprintf_s(year,5,"%04d",t.GetYear());	//��õ�ǰϵͳ������
			sprintf_s(month,3,"%02d",t.GetMonth());
			sprintf_s(day,3,"%02d",t.GetDay());
			borrowDVD[i].setRentData(year,month,day);
			break;
		}
	}
	state++;
}

//�����˻����
void MI::setBalance(double b)
{
	balance+=b;
}

//���ù黹��DVD��Ϣ
void MI::setDVDInfo_return(const DI &p)
{
	for(int i=0;i<3;i++)
	{
		if(borrowDVD[i].num==p.num)
		{
			borrowDVD[i].num=0;
			strcpy(borrowDVD[i].name,"");
			break;
		}
	}
	state--;
}

//�����˻�����
void MI::setPassword(string p)
{
	strcpy_s(password,13,p.c_str());
}

//ͨ��Ӱ���ж�������Ϣ���Ƿ����
bool MI::isExist(string name)
{
	for(int i=0;i<3;i++)
	{
		if(borrowDVD[i].name==name)
		{
			return true;
		}
	}
	return false;
}

//ͨ������ж�������Ϣ���Ƿ����
bool MI::isExist(int num)
{
	for(int i=0;i<3;i++)
	{
		if(borrowDVD[i].num==num)
		{
			return true;
		}
	}
	return false;
}

#endif
