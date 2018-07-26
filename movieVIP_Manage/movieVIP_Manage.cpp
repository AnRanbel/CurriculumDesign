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

extern void enroll();//ע��
extern void loginVIP();//��¼����VIP
extern void loginManager();//��¼��������Ա

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
	cout<<" ��������������������������������ӭ������Ӱ���ֲ�������������������������������"<<endl;
	while(true)
	{
		
		cout<<setw(31)<<" "<<"�ǡ���¼����1"<<endl;
		cout<<setw(31)<<" "<<"ע�����ᡪ��2"<<endl;
		cout<<setw(31)<<" "<<"�˳�ϵͳ����3"<<endl;
		do
		{
			if(!temp)
			{
				cout<<setw(31)<<" "<<"�������\n";
				cin.clear();
				cin.sync();
			}
			cout<<setw(31)<<" "<<"������:";
			cin>>order;
			temp=false;
		}while(order<1||order>3||cin.fail()||isFloat(order));
		temp=true;
		system("cls");
		if(order==2)				//ע��
		{
			system("cls");
			enroll();
		}
		else if(order==1)			//��¼
		{
			cout<<setw(31)<<" "<<"ѡ���������:"<<endl;
			cout<<setw(31)<<" "<<"��  Ա����1"<<endl;
			cout<<setw(31)<<" "<<"����Ա����2"<<endl;
			do
			{
				if(!temp)
				{
					cout<<setw(31)<<" "<<"�������\n";
					cin.clear();
					cin.sync();
				}
				cout<<setw(31)<<" "<<"������:";
				cin>>order;
				temp=false;
			}while(order!=1&&order!=2||cin.fail());
			if(order==1)		//��Ա��¼ҳ��
			{
				loginVIP();
			}
			else if(order==2)	//����Ա��¼ҳ��
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

//�ж��ַ��������Ƿ�Ϸ�
bool judgeNum(const string &s,int n)
{
	if(s.length()>n)
	{
		cout<<setw(31)<<" "<<"���Ȳ�Ӧ����"<<n<<"���ֽ�!"<<endl;
		cout<<setw(31)<<" "<<"����������:";
		return false;
	}
	else
	{
		return true;
	}
}

//�ж��Ƿ�ΪС��
bool isFloat(double n)
{
	return (n-floor(n)!=0);
}