#include<iostream>
#include<cstdlib>
#include"vip_data.h"
#include"dvd_data.h"
#include"manager.h"
#include<string>
#include<iomanip>
#include<atltime.h>
#include<fstream>
#include<sstream>
#include"node.h"
#include"linked_list.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::setw;
using std::ofstream;
using std::ifstream;
using std::ios_base;
using std::left;

extern bool judgeNum(const string &s,int n);//�ж��ַ��������Ƿ�Ϸ�
extern bool isFloat(double n);				//�ж��Ƿ�ΪС��

struct DVDNUM		//DVD���������
{
	int n;
	DVDNUM *next;
};

//��¼
void loginManager()
{
	bool addDVD();
	bool deleteDVD();
	bool checkDVD();
	bool vipInfo();
	bool rentInfo();
	bool editManaInfo();
	bool editDVDInfo();
	bool temp=true;
	string manaName;
	string password;
	ManaInfo m;
	float order=-1;
	char year[5];
	char month[3];
	char day[3];
	CTime t=CTime::GetCurrentTime();
	ifstream is_0("MANAGER.txt",ios_base::in|ios_base::binary);
	if(!is_0)
	{
		cout<<setw(31)<<" "<<"�ļ���ʧ��!"<<endl;
		exit(1);
	}
	is_0.read(reinterpret_cast<char *>(&m),sizeof(ManaInfo));
	while(true)
	{

		cout<<setw(31)<<" "<<"�û���:";
		cin>>manaName;
		cout<<setw(31)<<" "<<"����:";
		cin>>password;
		if(m.name==manaName&&m.getPassword()==password)
		{
			system("cls");
			cout<<" ������������������������������Hi���װ��Ĺ���Ա������������������������������"<<endl;
			sprintf_s(year,5,"%4d",t.GetYear());
			sprintf_s(month,3,"%02d",t.GetMonth());
			sprintf_s(day,3,"%02d",t.GetDay());
			ManaInfo manager(manaName,password,year,month,day);
			while(true)
			{
				system("cls");
				cout<<setw(31)<<" "<<"���DVD����1"<<endl;
				cout<<setw(31)<<" "<<"ɾ��DVD����2"<<endl;
				cout<<setw(31)<<" "<<"�鿴DVD����3"<<endl;
				cout<<setw(31)<<" "<<"��Ա��Ϣ����4"<<endl;
				cout<<setw(31)<<" "<<"������Ϣ����5"<<endl;
				cout<<setw(31)<<" "<<"�޸���Ϣ����6"<<endl;
				cout<<setw(31)<<" "<<"�༭DVD����7"<<endl;
				cout<<setw(31)<<" "<<"�˳�ϵͳ����8"<<endl;
				do
				{
					temp=true;
					do
					{
						if(!temp)
						{
							cout<<setw(31)<<" "<<"��������!"<<endl;
							cin.clear();
							cin.sync();
						}
						cout<<setw(31)<<" "<<"������:";
						cin>>order;
						temp=false;
					}while(order<0||order>8||cin.fail()||isFloat(order));
					temp=true;
					switch((int)order)
					{
					case 1:
						addDVD();
						break;
					case 2:
						deleteDVD();
						break;
					case 3:
						checkDVD();
						break;
					case 4:
						vipInfo();
						break;
					case 5:
						rentInfo();
						break;
					case 6:
						editManaInfo();
						break;
					case 7:
						editDVDInfo();
						break;
					case 8:
						exit(0);
						break;
					}
					break;
				}while(!temp);
				cout<<setw(31)<<" "<<"�ص���ҳ����1"<<endl;
				cout<<setw(31)<<" "<<"�˳�ϵͳ����2"<<endl;
				do
				{
					if(!temp)
					{
						cout<<setw(31)<<" "<<"�������!\n";
						cin.clear();
						cin.sync();
					}
					cout<<setw(31)<<" "<<"������:";
					cin>>order;
					temp=false;
				}while(order<1||order>2||cin.fail()||isFloat(order));
				temp=true;
				if(order==1)
				{
					continue;	//�ص���ҳ
				}
				else
				{
					exit(0);
				}
			}
		}
		else
		{
			cout<<setw(31)<<" "<<"�û������������!\n"<<endl;
		}
	}
	is_0.close();
}

//�ж������������Ƿ�Ϸ�
bool judgeData(int y,int m,int d)
{
	CTime t=CTime::GetCurrentTime();
	int nowy=t.GetYear();
	int nowm=t.GetMonth();
	int nowd=t.GetDay();
	bool leapyear=(y%4==0&&y%100!=0||y%400==0);		//�ж��Ƿ�Ϊ����
	int noLeap[12]={31,28,31,30,31,30,31,31,30,31,30,31};	//ƽ��
	int Leap[12]={31,29,31,30,31,30,31,31,30,31,30,31};		//����
	if(y>nowy||y<1985)
	{
		return false;
	}
	else if(y==nowy)
	{
		if(m>nowm||d>nowd)
		{
			return false;
		}
	}
	else if(m<0||m>12||d<0||d>31)
	{
		return false;
	}
	else if(leapyear&&d>Leap[m-1])
	{
		return false;
	}
	else if(!leapyear&&d>noLeap[m-1])
	{
		return false;
	}
	return true;
}

//���DVD
bool addDVD()
{
	system("cls");
	bool isExistDVDName(string s);		//�ж�dvd�Ƿ����
	string name;	//Ӱ��
	float num;	//DVD���
	data t_show;	//��ӳ����
	string role;	//����
	float stock;		//���
	float score;	//��������
	float year;		//��
	float month;		//��
	float day;		//��
	struct DVDNUM *h=NULL;			//�������ͷָ��
	struct DVDNUM *k=NULL;
	h=new struct DVDNUM;
	struct DVDNUM *q=h;
	h->next=NULL;
	bool temp=true;
	double seat;
	Node<DI> *r=NULL;	//ͷ���
	Node<DI> *p=NULL;
	LinkedList<DI> dvdList(r);	//������
	DI buf;		//��ʱ�洢��
	//����ӰƬ��Ϣ
	cout<<setw(31)<<" "<<"��Ӱ��:";
	do
	{
		cin.get();		//��ȡ�س���
		getline(cin,name);
	}while(!judgeNum(name,24)||isExistDVDName(name));
	cout<<setw(31)<<" "<<"����(xx/xxx):";
	do
	{
		//cin.get();		//��ȡ�س���
		getline(cin,role);
	}while(!judgeNum(role,26));
	do
	{
		if(!temp)
		{
			cout<<setw(31)<<" "<<"�������!������������"<<endl;
			cin.clear();
			cin.sync();
		}
		cout<<setw(31)<<" "<<"��ӳ����(��):";
		cin>>year;
		cout<<setw(31)<<" "<<"��ӳ����(��):";
		cin>>month;
		cout<<setw(31)<<" "<<"��ӳ����(��):";
		cin>>day;
		temp=false;
	}while(isFloat(year)||isFloat(month)||isFloat(day)||!judgeData(year,month,day)||cin.fail());
	sprintf_s(t_show.year,5,"%04d",(int)year);
	sprintf_s(t_show.month,3,"%02d",(int)month);
	sprintf_s(t_show.day,3,"%02d",(int)day);
	temp=true;
	cout<<setw(31)<<" "<<"���:";
	do
	{
		if(!temp)
		{
			cout<<setw(31)<<" "<<"�������!"<<endl;
			cin.clear();
			cin.sync();
			cout<<setw(31)<<" "<<"����������:";
		}
		cin>>stock;
		temp=false;
	}while(stock<0||cin.fail()||isFloat(stock));
	temp=true;
	cout<<setw(31)<<" "<<"��������(0<x<=10.0):";
	do
	{
		if(!temp)
		{
			cout<<setw(31)<<" "<<"�������!"<<endl;
			cin.clear();
			cin.sync();
			cout<<setw(31)<<" "<<"����������:";
		}
		cin>>score;
		temp=false;
	}while(score<0||score>10||cin.fail());
	temp=true;
	//������д���ļ�
	ifstream is_0("DVD.txt",ios_base::in|ios_base::binary);
	if(!is_0)
	{
		cout<<setw(31)<<" "<<"�ļ���ʧ��!"<<endl;
		exit(1);
	}
	if(is_0.peek()==EOF)	//�ļ�Ϊ��
	{
		is_0.close();
		DI dvd_info(name,1,role,t_show.year,t_show.month,t_show.day,stock,score);
		ofstream os_0("DVD.txt",ios_base::out|ios_base::binary);
		os_0.write(reinterpret_cast<char*>(&dvd_info),sizeof(dvd_info));
		os_0.close();
		cout<<setw(31)<<" "<<"��ӳɹ�!\n";
		return true;
	}
	//�򿪴��ԭ���Ѿ�ɾ����dvd��ŵ��ļ�dvdNum
	ifstream is_1("dvdNum.txt",ios_base::in|ios_base::binary);
	if(!is_1)
	{
		cout<<setw(31)<<" "<<"�ļ���ʧ��!"<<endl;
		exit(1);
	}
	//�ļ�dvdNum��û������
	if(is_1.peek()==EOF)
	{
		seat=sizeof(buf);
		is_0.seekg(-seat,ios_base::end);
		is_0.read(reinterpret_cast<char*>(&buf),sizeof(buf));
		is_0.close();
		num=buf.getNum()+1;
		DI dvd_info(name,num,role,t_show.year,t_show.month,t_show.day,stock,score);
		ofstream os_0("DVD.txt",ios_base::app|ios_base::binary);
		if(!os_0)
		{
			cout<<setw(31)<<" "<<"�ļ���ʧ��!"<<endl;
			exit(1);
		}
		os_0.write(reinterpret_cast<char*>(&dvd_info),sizeof(dvd_info));
		os_0.close();
		is_1.close();
		cout<<setw(31)<<" "<<"��ӳɹ�!\n";
		system("pause");
		system("cls");
		return true;
	}
	//dvd�ı��Ϊԭ���Ѿ�ɾ����DVD���
	is_1.read(reinterpret_cast<char*>(&num),sizeof(num));
	while(is_1.peek()!=EOF)
	{
		k=new struct DVDNUM;
		is_1.read(reinterpret_cast<char*>(&k->n),sizeof(k->n));
		k->next=NULL;
		q->next=k;
		q=k;
	}
	is_1.close();
	if(h->next==NULL)
	{
		ofstream os_2("dvdNum.txt",ios_base::trunc|ios_base::binary);//����ļ�
		os_2.close();
	}
	else
	{
		ofstream os_2("dvdNum.txt",ios_base::out|ios_base::binary);
		while(h->next!=NULL)
		{
			k=h;
			h=h->next;
			os_2.write(reinterpret_cast<char*>(&h->n),sizeof(h->n));
			delete k;
		}
		os_2.close();
	}
	DI dvd_info(name,num,role,t_show.year,t_show.month,t_show.day,stock,score);
	while(is_0.peek()!=EOF)
	{
		if(dvdList.getPosition()+1==num)
		{
			dvdList.insertRear(dvd_info);
			dvdList.next();
		}
		is_0.read(reinterpret_cast<char*>(&buf),sizeof(buf));
		dvdList.insertRear(buf);
		dvdList.next();
	}
	is_0.close();
	ofstream os_1("DVD.txt",ios_base::out|ios_base::binary);
	if(!os_1)
	{
		cout<<setw(31)<<" "<<"�ļ���ʧ��!"<<endl;
		exit(1);
	}
	dvdList.reset(0);
	p=r->nextNode();
	while(!dvdList.endOfList())
	{
		os_1.write(reinterpret_cast<char*>(&p->data),sizeof(p->data));
		dvdList.next();
		p=p->nextNode();
	}
	os_1.close();
	cout<<setw(31)<<" "<<"��ӳɹ�!\n";
	system("cls");
	return true;
}

//ɾ��DVD
bool deleteDVD()
{
	system("cls");
	struct DVDNUM *h=NULL;		//�������ͷָ��
	struct DVDNUM *k=NULL;
	h=new struct DVDNUM;
	struct DVDNUM *q=h;
	struct DVDNUM *s=NULL;
	h->next=NULL;
	Node<DI> *r=NULL;	//ͷ���
	Node<DI> *p=NULL;
	LinkedList<DI> dvdList(r);	//������
	DI buf;		//��ʱ�洢��
	int i;
	float order=-1;
	float num;
	string name;
	bool temp=true;
	ifstream is_0("DVD.txt",ios_base::in|ios_base::binary);
	if(!is_0)
	{
		cout<<setw(31)<<" "<<"�ļ���ʧ��!"<<endl;
		exit(1);
	}
	if(is_0.peek()==EOF)
	{
		cout<<setw(31)<<" "<<"��������!�޷�ɾ��!"<<endl;
		is_0.close();
		return false;
	}
	while(is_0.peek()!=EOF)
	{
		is_0.read(reinterpret_cast<char*>(&buf),sizeof(buf));
		dvdList.insertRear(buf);
	}
	is_0.close();
	while(true)
	{
		do
		{
			if(!temp)
			{
				cout<<setw(31)<<"�������!"<<endl;
				cin.clear();
				cin.sync();
			}
			cout<<setw(31)<<" "<<"��ѡ����ҷ�ʽ:��š���1"<<endl;
			cout<<setw(46)<<" "<<"��Ӱ������2"<<endl;
			cout<<setw(31)<<" "<<"�����뷽ʽ:";
			cin>>order;
			temp=false;
		}while(order!=1&&order!=2||cin.fail()||isFloat(order));
		temp=true;
		//�ñ�Ų���
		p=r->nextNode();
		dvdList.next();
		if(order==1)
		{
			do
			{
				if(!temp)
				{
					cout<<setw(31)<<" "<<"�������!"<<endl;
					cin.clear();
					cin.sync();
				}
				cout<<setw(31)<<" "<<"��������:";
				cin>>num;
				temp=false;
			}while(cin.fail()||isFloat(num));
			temp=true;
			for(i=0;i<dvdList.getSize()&&(p->data.getNum())!=num;i++)
			{
				dvdList.next();
				p=p->nextNode();
			}
			if(i==dvdList.getSize())
			{
				cout<<setw(31)<<" "<<"û���ҵ�!\n";
				continue;
			}
			else
			{
				dvdList.deleteCurrent();	//ɾ����ǰ���
				break;
			}
		}
		//�õ�Ӱ������
		else
		{
			cout<<setw(31)<<" "<<"�������Ӱȫ��:";
			cin>>name;
			for(i=0;i<dvdList.getSize()&&p->data.name!=name;i++)
			{
				dvdList.next();
				p=p->nextNode();
			}
			if(i==dvdList.getSize())
			{
				cout<<setw(31)<<" "<<"û���ҵ�!\n";
				continue;
			}
			else
			{
				num=p->data.getNum();
				dvdList.deleteCurrent();	//ɾ����ǰ���
				break;
			}
		}
	}
	//�����ļ�
	ofstream os_0("DVD.txt",ios_base::out|ios_base::binary);
	for(i=0;i<dvdList.getSize();i++)
	{
		r=r->nextNode();
		os_0.write(reinterpret_cast<char*>(&r->data),sizeof(r->data));
	}
	os_0.close();
	cout<<setw(31)<<" "<<"ɾ���ɹ�!\n";
	//��ɾ����DVD��Ŵ����ļ�
	ifstream is_1("dvdNum.txt",ios_base::in|ios_base::binary);
	if(!is_1)
	{
		cout<<setw(31)<<" "<<"�ļ���ʧ��!"<<endl;
		exit(1);
	}
	if(is_1.peek()==EOF)
	{
		is_1.close();
		ofstream os_1("dvdNum.txt",ios_base::in|ios_base::binary);
		os_1.write(reinterpret_cast<char*>(&num),sizeof(num));
		os_1.close();
	}
	else
	{
		//��ȡ����
		while(is_1.peek()!=EOF)
		{
			k=new struct DVDNUM;
			is_1.read(reinterpret_cast<char*>(&k->n),sizeof(k->n));
			k->next=NULL;
			if(k->n>=num)
			{
				s=new struct DVDNUM;
				s->n=num;
				s->next=NULL;
				q->next=s;
				q=s;
			}
			q->next=k;
			q=k;
		}
		is_1.close();
		//�����ļ�
		ofstream os_1("dvdNum.txt",ios_base::out|ios_base::binary);
		if(!os_1)
		{
			cout<<setw(31)<<" "<<"�ļ���ʧ��!"<<endl;
			exit(1);
		}
		while(h->next!=NULL)
		{
			q=h;
			h=h->next;
			os_1.write(reinterpret_cast<char*>(&h->n),sizeof(h->n));
			delete q;
		}
		os_1.close();
	}
	return true;
}

//�鿴DVD
bool checkDVD()
{
	system("cls");
	Node<DI> *r=NULL;	//ͷ���
	Node<DI> *sortNum_r=NULL;
	Node<DI> *sortData_r=NULL;
	Node<DI> *sortScore_r=NULL;
	Node<DI> *p=NULL;
	Node<DI> *q=NULL;
	Node<DI> *k=NULL;
	Node<DI> *h=NULL;
	Node<DI> *max=NULL;
	LinkedList<DI> dvdList(r);	//������
	DI buf;		//��ʱ�洢��
	int i;
	int j;
	float order=-1;
	bool temp=true;
	ifstream is_0("DVD.txt",ios_base::in|ios_base::binary);
	if(!is_0)
	{
		cout<<setw(31)<<" "<<"�ļ���ʧ��!"<<endl;
		exit(1);
	}
	if(is_0.peek()==EOF)
	{
		cout<<setw(31)<<" "<<"��������!"<<endl;
		is_0.close();
		return false;
	}
	while(is_0.peek()!=EOF)
	{
		is_0.read(reinterpret_cast<char*>(&buf),sizeof(buf));
		dvdList.insertRear(buf);
	}
	is_0.close();
	LinkedList<DI> sortNum_dvdList(dvdList);
	sortNum_r=sortNum_dvdList.getFront();
	LinkedList<DI> sortScore_dvdList(dvdList);
	sortScore_r=sortScore_dvdList.getFront();
	LinkedList<DI> sortData_dvdList(dvdList);
	sortData_r=sortData_dvdList.getFront();
	cout<<setw(31)<<" "<<"������鿴��ʽ:��    ��(����)����1"<<endl;
	cout<<setw(46)<<" "<<"��    ��(����)����2"<<endl;
	cout<<setw(46)<<" "<<"��Ӱ����(����)����3"<<endl;
	//ѡ������(����sortScore��������)
	for(i=0;i<sortScore_dvdList.getSize()-1;i++)
	{
		max=sortScore_r->nextNode();
		p=max->nextNode();
		for(j=0;j<sortScore_dvdList.getSize()-i-1;j++)
		{
			if(p->data.getScore()>max->data.getScore())
			{
				max=p;
			}
			q=p;
			p=p->nextNode();
		}
		if(max!=q)
		{
			if(max->nextNode()==NULL)		//max������β
			{
				if(q->nextNode()==max)		//q��max����
				{
					q->lastNode()->setNextNode(max);
					max->setLastNode(q->lastNode());
					max->setNextNode(q);
					q->setLastNode(max);
					q->setNextNode();
				}
				else
				{
					h=max->lastNode();
					q->lastNode()->setNextNode(max);
					max->setLastNode(q->lastNode());
					q->nextNode()->setLastNode(max);
					max->setNextNode(q->nextNode());
					h->setNextNode(q);
					q->setLastNode(h);
					q->setNextNode();
				}
			}
			else if(q->nextNode()==NULL)	//q������β
			{
				if(max->nextNode()==q)		//q��max����
				{
					max->lastNode()->setNextNode(q);
					q->setLastNode(max->lastNode());
					q->setNextNode(max);
					max->setLastNode(q);
					max->setNextNode();
				}
				else
				{
					h=q->lastNode();
					max->lastNode()->setNextNode(q);
					q->setLastNode(max->lastNode());
					max->nextNode()->setLastNode(q);
					q->setNextNode(max->nextNode());
					h->setNextNode(max);
					max->setLastNode(h);
					max->setNextNode();
				}
			}
			else							
			{
				if(max->nextNode()==q||q->nextNode()==max)		//q��max����
				{
					h=q->nextNode();
					max->lastNode()->setNextNode(q);
					q->setLastNode(max->lastNode());
					q->setNextNode(max);
					max->setLastNode(q);
					max->setNextNode(h);
					h->setLastNode(max);
				}
				else
				{
					h=q->lastNode();
					k=q->nextNode();
					max->lastNode()->setNextNode(q);
					q->setLastNode(max->lastNode());
					q->setNextNode(max->nextNode());
					max->nextNode()->setLastNode(q);
					h->setNextNode(max);
					max->setLastNode(h);
					k->setLastNode(max);
					max->setNextNode(k);
				}
			}
			if(i==0)
			{
				sortScore_dvdList.setRear(max);
			}
		}
	}
	cout<<setw(46)<<" "<<"��Ӱ����(����)����4"<<endl;
	cout<<setw(46)<<" "<<"��ӳ����(����)����5"<<endl;
	//ð������(����sortData��������)
	for(i=0;i<sortData_dvdList.getSize()-1;i++)
	{
		p=sortData_r->nextNode();
		for(j=0;j<sortData_dvdList.getSize()-i-1;j++)
		{
			q=p->nextNode();
			if(p->data.getShowTime()>q->data.getShowTime())
			{
				if(q->nextNode()==NULL)
				{
					h=p->lastNode();
					h->setNextNode(q);
					q->setNextNode(p);
					p->setNextNode();
					q->setLastNode(h);
					p->setLastNode(q);
					sortData_dvdList.setRear(p);
				}
				else
				{
					h=p->lastNode();
					h->setNextNode(q);
					k=q->nextNode();
					p->setNextNode(q->nextNode());
					q->setNextNode(p);
					q->setLastNode(h);
					p->setLastNode(q);
					k->setLastNode(p);
				}
			}
			else
			{
				p=q;
			}
		}
	}
	cout<<setw(46)<<" "<<"��ӳ����(����)����6"<<endl;
	cout<<setw(46)<<" "<<"�ص���ҳ����7"<<endl;
	cout<<setw(31)<<" "<<"������:";
	do
	{
		if(!temp)
		{
			cout<<setw(31)<<" "<<"�������!"<<endl;
			cin.clear();
			cin.sync();
			cout<<setw(31)<<" "<<"����������:";
		}
		cin>>order;
		temp=false;
	}while(cin.fail()||isFloat(order)||order>7||order<1);
	temp=true;
	switch((int)order)
	{
	case 1:
		{
			system("cls");
			//�������
			p=sortNum_r->nextNode();
			cout<<left<<setw(7)<<"���"<<left<<setw(26)<<"ӰƬ��"<<left<<setw(28)<<"����"<<left<<setw(10)<<"��ӳʱ��"<<left<<setw(6)<<"����"<<"��"<<endl;
			for(i=0;i<sortNum_dvdList.getSize();i++)
			{
				p->data.display();
				p=p->nextNode();
			}
			break;
		}
	case 2:
		{
			system("cls");
			//�������
			p=sortNum_dvdList.getRear();
			cout<<left<<setw(7)<<"���"<<left<<setw(26)<<"ӰƬ��"<<left<<setw(28)<<"����"<<left<<setw(10)<<"��ӳʱ��"<<left<<setw(6)<<"����"<<"��"<<endl;
			for(i=0;i<sortNum_dvdList.getSize();i++)
			{
				p->data.display();
				p=p->lastNode();
			}
			break;
		}
	case 3:
		{
			system("cls");
			p=sortScore_r->nextNode();
			cout<<left<<setw(7)<<"���"<<left<<setw(26)<<"ӰƬ��"<<left<<setw(28)<<"����"<<left<<setw(10)<<"��ӳʱ��"<<left<<setw(6)<<"����"<<"��"<<endl;
			for(i=0;i<sortScore_dvdList.getSize();i++)
			{
				p->data.display();
				p=p->nextNode();
			}
			break;
		}
	case 4:
		{
			system("cls");
			//�������
			p=sortScore_dvdList.getRear();
			cout<<left<<setw(7)<<"���"<<left<<setw(26)<<"ӰƬ��"<<left<<setw(28)<<"����"<<left<<setw(10)<<"��ӳʱ��"<<left<<setw(6)<<"����"<<"��"<<endl;
			for(i=0;i<sortScore_dvdList.getSize();i++)
			{
				p->data.display();
				p=p->lastNode();
			}
			break;
		}
	case 5:
		{
			system("cls");
			//�������
			p=sortData_r->nextNode();
			cout<<left<<setw(7)<<"���"<<left<<setw(26)<<"ӰƬ��"<<left<<setw(28)<<"����"<<left<<setw(10)<<"��ӳʱ��"<<left<<setw(6)<<"����"<<"��"<<endl;
			for(i=0;i<sortData_dvdList.getSize();i++)
			{
				p->data.display();
				p=p->nextNode();
			}
			break;
		}
	case 6:
		{
			system("cls");
			//�������
			p=sortData_dvdList.getRear();
			cout<<left<<setw(7)<<"���"<<left<<setw(26)<<"ӰƬ��"<<left<<setw(28)<<"����"<<left<<setw(10)<<"��ӳʱ��"<<left<<setw(6)<<"����"<<"��"<<endl;
			for(i=0;i<sortData_dvdList.getSize();i++)
			{
				p->data.display();
				p=p->lastNode();
			}
			break;
		}
	case 7:
		return true;
	}
	return true;
}

//�鿴��Ա��Ϣ
bool vipInfo()
{
	system("cls");
	Node<MI> *r=NULL;	//ͷ���
	LinkedList<MI> vipList(r);	//������
	MI buf;		//��ʱ�洢��
	ifstream is_0("VIP.txt",ios_base::in|ios_base::binary);
	float order=-1;
	bool temp=true;
	if(!is_0)
	{
		cout<<setw(31)<<" "<<"���ļ�ʧ��!\n";
		exit(1);
	}
	if(is_0.peek()==EOF)
	{
		cout<<setw(31)<<" "<<"��ʱû����Ϣ!\n";
		is_0.close();
		return false;
	}
	do
	{
		if(!temp)
		{
			cout<<setw(31)<<" "<<"�������"<<endl;
			cin.clear();
			cin.sync();
		}
		cout<<setw(31)<<" "<<"������鿴��ʽ:���򡪡�1"<<endl;
		cout<<setw(46)<<" "<<"���򡪡�2"<<endl;
		cout<<setw(31)<<" "<<"������:";
		cin>>order;
		temp=false;
	}while(order!=1&&order!=2||cin.fail()||isFloat(order));
	temp=true;
	if(order==1)		//����
	{
		while(is_0.peek()!=EOF)
		{
			is_0.read(reinterpret_cast<char*>(&buf),sizeof(buf));
			vipList.insertFront(buf);
		}
	}
	else				//����
	{
		while(is_0.peek()!=EOF)
		{
			is_0.read(reinterpret_cast<char*>(&buf),sizeof(buf));
			vipList.insertRear(buf);
		}
	}
	is_0.close();
	cout<<setw(4)<<" ";
	cout<<left<<setw(14)<<"���"<<left<<setw(24)<<"�û���"<<left<<setw(12)<<"���"<<left<<setw(9)<<"state"<<"ע������"<<endl;
	while(!vipList.endOfList())
	{
		r=r->nextNode();
		r->data.display();
		vipList.next();
	}
	return true;
}

//�鿴������Ϣ
bool rentInfo()
{
	system("cls");
	Node<MI> *r=NULL;	//ͷ���
	LinkedList<MI> vipList(r);	//������
	MI buf;		//��ʱ�洢��
	ifstream is_0("VIP.txt",ios_base::in|ios_base::binary);
	if(!is_0)
	{
		cout<<setw(31)<<" "<<"���ļ�ʧ��!\n";
		exit(1);
	}
	if(is_0.peek()==EOF)
	{
		cout<<setw(31)<<" "<<"��ʱû����Ϣ!\n";
		is_0.close();
		return false;
	}
	while(is_0.peek()!=EOF)
	{
		is_0.read(reinterpret_cast<char*>(&buf),sizeof(buf));
		if(buf.getState()!=0)
		{
			vipList.insertFront(buf);
		}
	}
	is_0.close();
	cout<<setw(8)<<" ";
	cout<<left<<setw(14)<<"���"<<left<<setw(24)<<"�û���"<<left<<setw(12)<<"���"<<left<<setw(5)<<"state\n";
	while(!vipList.endOfList())
	{
		r=r->nextNode();
		r->data.display();
		vipList.next();
	}
	return true;
}

//�޸���Ϣ
bool editManaInfo()
{
	system("cls");
	float order=-1;
	char c;
	bool temp=true;
	string name;
	string password;
	ManaInfo mana;
	while(true)
	{
		do
		{
			if(!temp)
			{
				cout<<setw(31)<<" "<<"�������!\n";
				cin.clear();
				cin.sync();
			}
			cout<<setw(31)<<" "<<"�޸�:�ǳơ���1"<<endl;
			cout<<setw(36)<<" "<<"���롪��2"<<endl;
			cout<<setw(31)<<" "<<"������:";
			cin>>order;
			temp=false;
		}while(order!=1&&order!=2||cin.fail()||isFloat(order));
		temp=true;
		ifstream is_0("MANAGER.txt",ios_base::in|ios_base::binary);
		is_0.read(reinterpret_cast<char *>(&mana),sizeof(mana));
		is_0.close();
		if(order==1)
		{
			cout<<setw(31)<<" "<<"���ǳ�:";
			do
			{
				cin>>name;
			}while(!judgeNum(name,18));
			strcpy_s(mana.name,19,name.c_str());
			cout<<setw(31)<<" "<<"�޸ĳɹ�!\n";
			ofstream os_0("MANAGER.txt",ios_base::out|ios_base::binary);
			os_0.write(reinterpret_cast<char *>(&mana),sizeof(mana));
			os_0.close();
		}
		else
		{
			cout<<setw(31)<<" "<<"������:";
			do
			{
				cin>>password;
			}while(!judgeNum(password,12));
			mana.setPassword(password);
			cout<<setw(31)<<" "<<"�޸ĳɹ�!\n";
			ofstream os_0("MANAGER.txt",ios_base::out|ios_base::binary);
			os_0.write(reinterpret_cast<char *>(&mana),sizeof(mana));
			os_0.close();
		}
		cout<<setw(31)<<" "<<"�Ƿ�����޸�(Y/N)?"<<endl;
		do
		{
			if(!temp)
			{
				cout<<setw(31)<<" "<<"�������,����������!\n";
				cin.sync();
			}
			cout<<setw(31)<<" "<<"������:";
			cin>>c;
			temp=false;
		}while(c!='y'&&c!='Y'&&c!='n'&&c!='N');
		temp=true;
		if(c=='n'||c=='N')
		{
			break;
		}
	}
	return true;
}

//�༭DVD��Ϣ
bool editDVDInfo()
{
	system("cls");
	Node<DI>* r=NULL;	//ͷ���
	LinkedList<DI> dvdList(r);		//DVD����
	Node<DI>* p=NULL;
	Node<DI>* q=NULL;
	DI buf;		//��ʱ�洢��
	float order=-1;
	float t=-1;
	int i;
	float dvdNum; 
	string dvdName;
	string dvdRole;
	bool temp=true;
	bool isFind=false;
	while(true)
	{
		do
		{
			if(!temp)
			{
				cout<<setw(31)<<" "<<"��������!"<<endl;
				cin.clear();
				cin.sync();
			}
			cout<<setw(31)<<" "<<"��������ҷ�ʽ:��š���1"<<endl;
			cout<<setw(46)<<" "<<"��Ӱ������2"<<endl;
			cout<<setw(31)<<" "<<"������:";
			cin>>order;
			temp=false;
		}while(order!=1&&order!=2||cin.fail()||isFloat(order));
		temp=true;
		//��DVD��Ϣ���ļ����뵽����
		ifstream is_0("DVD.txt",ios_base::in|ios_base::binary);
		if(!is_0)
		{
			cout<<setw(31)<<" "<<"�ļ���ʧ��!\n";
			exit(1);
		}
		if(is_0.peek()==EOF)
		{
			cout<<setw(31)<<" "<<"��ʱû������!"<<endl;
			return false;
		}
		while(is_0.peek()!=EOF)
		{
			is_0.read(reinterpret_cast<char*>(&buf),sizeof(buf));
			dvdList.insertRear(buf);
		}
		is_0.close();
		//��ʼ����
		//�ñ�Ų���
		if(order==1)
		{
			cout<<setw(31)<<" "<<"��������:";
			cin>>dvdNum;
			p=r->nextNode();
			for(i=0;i<dvdList.getSize()&&(p->data.getNum())!=dvdNum;i++)
			{
				p=p->nextNode();
				isFind=true;
			}
			if(i==dvdList.getSize())
			{
				cout<<setw(31)<<" "<<"û���ҵ��������!\n";
			}
			else
			{
				isFind=true;
			}
		}
		//�õ�Ӱ������
		else
		{
			cout<<setw(31)<<" "<<"�������Ӱȫ��:";
			cin>>dvdName;
			p=r->nextNode();
			for(i=0;i<dvdList.getSize()&&p->data.name!=dvdName;i++)
			{
				p=p->nextNode();
			}
			if(i==dvdList.getSize())
			{
				cout<<setw(31)<<" "<<"û���ҵ��������!\n";
			}
			else
			{
				isFind=true;
			}
		}
		if(isFind==true)
		{
			cout<<setw(31)<<" "<<"DVD��Ϣ����:"<<endl;
			cout<<left<<setw(7)<<"���"<<left<<setw(26)<<"ӰƬ��"<<left<<setw(28)<<"����"<<left<<setw(10)<<"��ӳʱ��"<<left<<setw(6)<<"����"<<"��"<<endl;
			p->data.display();
			system("pause");
			p->data.editInfo();
			//���޸ĺ��dvd��������������ļ�
			ofstream os_0("DVD.txt",ios_base::out|ios_base::binary);
			if(!os_0)
			{
				cout<<setw(31)<<" "<<"�ļ���ʧ��!\n";
				exit(1);
			}
			q=r->nextNode();
			dvdList.reset(0);
			while(!dvdList.endOfList())
			{
				os_0.write(reinterpret_cast<char *>(&q->data),sizeof(q->data));
				q=q->nextNode();
				dvdList.next();
			}
			os_0.close();
		}
		do
		{
			if(!temp)
			{
				cout<<setw(31)<<" "<<"��������!����������!"<<endl;
				cin.clear();
				cin.sync();
			}
			cout<<setw(31)<<" "<<"�����޸ġ���1"<<endl;
			cout<<setw(31)<<" "<<"�ص���ҳ����2"<<endl;
			cin>>t;
			temp=false;
		}while(t!=1&&t!=2||cin.fail()||isFloat(t));
		temp=true;
		if(t==2)
		{
			break;	//�ص���ҳ
		}
		isFind=false;
	}
	return true;
}

//�ж�DVD�Ƿ����
bool isExistDVDName(string s)
{
	Node<DI> *r=NULL;	//ͷ���
	Node<DI> *p=NULL;
	Node<DI> *q=NULL;
	LinkedList<DI> dvdList(r);	//������
	DI buf;
	ifstream is_0("DVD.txt",ios_base::in|ios_base::binary);
	while(is_0.peek()!=EOF)
	{
		is_0.read(reinterpret_cast<char*>(&buf),sizeof(buf));
		if(buf.name==s)
		{
			cout<<setw(31)<<" "<<"��DVD�Ѵ���!\n"<<endl;
			cout<<setw(31)<<" "<<"����������:";
			is_0.close();
			return true;
		}
	}
	is_0.close();
	return false;
}