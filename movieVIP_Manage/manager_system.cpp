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

extern bool judgeNum(const string &s,int n);//判断字符串长度是否合法
extern bool isFloat(double n);				//判断是否为小数

struct DVDNUM		//DVD编号链表结点
{
	int n;
	DVDNUM *next;
};

//登录
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
		cout<<setw(31)<<" "<<"文件打开失败!"<<endl;
		exit(1);
	}
	is_0.read(reinterpret_cast<char *>(&m),sizeof(ManaInfo));
	while(true)
	{

		cout<<setw(31)<<" "<<"用户名:";
		cin>>manaName;
		cout<<setw(31)<<" "<<"密码:";
		cin>>password;
		if(m.name==manaName&&m.getPassword()==password)
		{
			system("cls");
			cout<<" ———————————————Hi，亲爱的管理员———————————————"<<endl;
			sprintf_s(year,5,"%4d",t.GetYear());
			sprintf_s(month,3,"%02d",t.GetMonth());
			sprintf_s(day,3,"%02d",t.GetDay());
			ManaInfo manager(manaName,password,year,month,day);
			while(true)
			{
				system("cls");
				cout<<setw(31)<<" "<<"添加DVD——1"<<endl;
				cout<<setw(31)<<" "<<"删除DVD——2"<<endl;
				cout<<setw(31)<<" "<<"查看DVD——3"<<endl;
				cout<<setw(31)<<" "<<"会员信息——4"<<endl;
				cout<<setw(31)<<" "<<"租用信息——5"<<endl;
				cout<<setw(31)<<" "<<"修改信息——6"<<endl;
				cout<<setw(31)<<" "<<"编辑DVD——7"<<endl;
				cout<<setw(31)<<" "<<"退出系统——8"<<endl;
				do
				{
					temp=true;
					do
					{
						if(!temp)
						{
							cout<<setw(31)<<" "<<"输入有误!"<<endl;
							cin.clear();
							cin.sync();
						}
						cout<<setw(31)<<" "<<"请输入:";
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
				cout<<setw(31)<<" "<<"回到主页——1"<<endl;
				cout<<setw(31)<<" "<<"退出系统——2"<<endl;
				do
				{
					if(!temp)
					{
						cout<<setw(31)<<" "<<"输入错误!\n";
						cin.clear();
						cin.sync();
					}
					cout<<setw(31)<<" "<<"请输入:";
					cin>>order;
					temp=false;
				}while(order<1||order>2||cin.fail()||isFloat(order));
				temp=true;
				if(order==1)
				{
					continue;	//回到主页
				}
				else
				{
					exit(0);
				}
			}
		}
		else
		{
			cout<<setw(31)<<" "<<"用户名或密码错误!\n"<<endl;
		}
	}
	is_0.close();
}

//判断年月日输入是否合法
bool judgeData(int y,int m,int d)
{
	CTime t=CTime::GetCurrentTime();
	int nowy=t.GetYear();
	int nowm=t.GetMonth();
	int nowd=t.GetDay();
	bool leapyear=(y%4==0&&y%100!=0||y%400==0);		//判断是否为闰年
	int noLeap[12]={31,28,31,30,31,30,31,31,30,31,30,31};	//平年
	int Leap[12]={31,29,31,30,31,30,31,31,30,31,30,31};		//闰年
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

//添加DVD
bool addDVD()
{
	system("cls");
	bool isExistDVDName(string s);		//判断dvd是否存在
	string name;	//影名
	float num;	//DVD编号
	data t_show;	//上映日期
	string role;	//主演
	float stock;		//存货
	float score;	//豆瓣评分
	float year;		//年
	float month;		//月
	float day;		//日
	struct DVDNUM *h=NULL;			//编号链表头指针
	struct DVDNUM *k=NULL;
	h=new struct DVDNUM;
	struct DVDNUM *q=h;
	h->next=NULL;
	bool temp=true;
	double seat;
	Node<DI> *r=NULL;	//头结点
	Node<DI> *p=NULL;
	LinkedList<DI> dvdList(r);	//链表类
	DI buf;		//临时存储区
	//输入影片信息
	cout<<setw(31)<<" "<<"电影名:";
	do
	{
		cin.get();		//读取回车符
		getline(cin,name);
	}while(!judgeNum(name,24)||isExistDVDName(name));
	cout<<setw(31)<<" "<<"主演(xx/xxx):";
	do
	{
		//cin.get();		//读取回车符
		getline(cin,role);
	}while(!judgeNum(role,26));
	do
	{
		if(!temp)
		{
			cout<<setw(31)<<" "<<"输入错误!请您重新输入"<<endl;
			cin.clear();
			cin.sync();
		}
		cout<<setw(31)<<" "<<"上映日期(年):";
		cin>>year;
		cout<<setw(31)<<" "<<"上映日期(月):";
		cin>>month;
		cout<<setw(31)<<" "<<"上映日期(日):";
		cin>>day;
		temp=false;
	}while(isFloat(year)||isFloat(month)||isFloat(day)||!judgeData(year,month,day)||cin.fail());
	sprintf_s(t_show.year,5,"%04d",(int)year);
	sprintf_s(t_show.month,3,"%02d",(int)month);
	sprintf_s(t_show.day,3,"%02d",(int)day);
	temp=true;
	cout<<setw(31)<<" "<<"存货:";
	do
	{
		if(!temp)
		{
			cout<<setw(31)<<" "<<"输入错误!"<<endl;
			cin.clear();
			cin.sync();
			cout<<setw(31)<<" "<<"请重新输入:";
		}
		cin>>stock;
		temp=false;
	}while(stock<0||cin.fail()||isFloat(stock));
	temp=true;
	cout<<setw(31)<<" "<<"豆瓣评分(0<x<=10.0):";
	do
	{
		if(!temp)
		{
			cout<<setw(31)<<" "<<"输入错误!"<<endl;
			cin.clear();
			cin.sync();
			cout<<setw(31)<<" "<<"请重新输入:";
		}
		cin>>score;
		temp=false;
	}while(score<0||score>10||cin.fail());
	temp=true;
	//将数据写入文件
	ifstream is_0("DVD.txt",ios_base::in|ios_base::binary);
	if(!is_0)
	{
		cout<<setw(31)<<" "<<"文件打开失败!"<<endl;
		exit(1);
	}
	if(is_0.peek()==EOF)	//文件为空
	{
		is_0.close();
		DI dvd_info(name,1,role,t_show.year,t_show.month,t_show.day,stock,score);
		ofstream os_0("DVD.txt",ios_base::out|ios_base::binary);
		os_0.write(reinterpret_cast<char*>(&dvd_info),sizeof(dvd_info));
		os_0.close();
		cout<<setw(31)<<" "<<"添加成功!\n";
		return true;
	}
	//打开存放原来已经删除的dvd编号的文件dvdNum
	ifstream is_1("dvdNum.txt",ios_base::in|ios_base::binary);
	if(!is_1)
	{
		cout<<setw(31)<<" "<<"文件打开失败!"<<endl;
		exit(1);
	}
	//文件dvdNum中没有数据
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
			cout<<setw(31)<<" "<<"文件打开失败!"<<endl;
			exit(1);
		}
		os_0.write(reinterpret_cast<char*>(&dvd_info),sizeof(dvd_info));
		os_0.close();
		is_1.close();
		cout<<setw(31)<<" "<<"添加成功!\n";
		system("pause");
		system("cls");
		return true;
	}
	//dvd的编号为原来已经删除的DVD编号
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
		ofstream os_2("dvdNum.txt",ios_base::trunc|ios_base::binary);//清空文件
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
		cout<<setw(31)<<" "<<"文件打开失败!"<<endl;
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
	cout<<setw(31)<<" "<<"添加成功!\n";
	system("cls");
	return true;
}

//删除DVD
bool deleteDVD()
{
	system("cls");
	struct DVDNUM *h=NULL;		//编号链表头指针
	struct DVDNUM *k=NULL;
	h=new struct DVDNUM;
	struct DVDNUM *q=h;
	struct DVDNUM *s=NULL;
	h->next=NULL;
	Node<DI> *r=NULL;	//头结点
	Node<DI> *p=NULL;
	LinkedList<DI> dvdList(r);	//链表类
	DI buf;		//临时存储区
	int i;
	float order=-1;
	float num;
	string name;
	bool temp=true;
	ifstream is_0("DVD.txt",ios_base::in|ios_base::binary);
	if(!is_0)
	{
		cout<<setw(31)<<" "<<"文件打开失败!"<<endl;
		exit(1);
	}
	if(is_0.peek()==EOF)
	{
		cout<<setw(31)<<" "<<"暂无数据!无法删除!"<<endl;
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
				cout<<setw(31)<<"输入错误!"<<endl;
				cin.clear();
				cin.sync();
			}
			cout<<setw(31)<<" "<<"请选择查找方式:编号——1"<<endl;
			cout<<setw(46)<<" "<<"电影名——2"<<endl;
			cout<<setw(31)<<" "<<"请输入方式:";
			cin>>order;
			temp=false;
		}while(order!=1&&order!=2||cin.fail()||isFloat(order));
		temp=true;
		//用编号查找
		p=r->nextNode();
		dvdList.next();
		if(order==1)
		{
			do
			{
				if(!temp)
				{
					cout<<setw(31)<<" "<<"输入错误!"<<endl;
					cin.clear();
					cin.sync();
				}
				cout<<setw(31)<<" "<<"请输入编号:";
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
				cout<<setw(31)<<" "<<"没有找到!\n";
				continue;
			}
			else
			{
				dvdList.deleteCurrent();	//删除当前结点
				break;
			}
		}
		//用电影名查找
		else
		{
			cout<<setw(31)<<" "<<"请输入电影全称:";
			cin>>name;
			for(i=0;i<dvdList.getSize()&&p->data.name!=name;i++)
			{
				dvdList.next();
				p=p->nextNode();
			}
			if(i==dvdList.getSize())
			{
				cout<<setw(31)<<" "<<"没有找到!\n";
				continue;
			}
			else
			{
				num=p->data.getNum();
				dvdList.deleteCurrent();	//删除当前结点
				break;
			}
		}
	}
	//存入文件
	ofstream os_0("DVD.txt",ios_base::out|ios_base::binary);
	for(i=0;i<dvdList.getSize();i++)
	{
		r=r->nextNode();
		os_0.write(reinterpret_cast<char*>(&r->data),sizeof(r->data));
	}
	os_0.close();
	cout<<setw(31)<<" "<<"删除成功!\n";
	//将删除的DVD编号存入文件
	ifstream is_1("dvdNum.txt",ios_base::in|ios_base::binary);
	if(!is_1)
	{
		cout<<setw(31)<<" "<<"文件打开失败!"<<endl;
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
		//提取数据
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
		//存入文件
		ofstream os_1("dvdNum.txt",ios_base::out|ios_base::binary);
		if(!os_1)
		{
			cout<<setw(31)<<" "<<"文件打开失败!"<<endl;
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

//查看DVD
bool checkDVD()
{
	system("cls");
	Node<DI> *r=NULL;	//头结点
	Node<DI> *sortNum_r=NULL;
	Node<DI> *sortData_r=NULL;
	Node<DI> *sortScore_r=NULL;
	Node<DI> *p=NULL;
	Node<DI> *q=NULL;
	Node<DI> *k=NULL;
	Node<DI> *h=NULL;
	Node<DI> *max=NULL;
	LinkedList<DI> dvdList(r);	//链表类
	DI buf;		//临时存储区
	int i;
	int j;
	float order=-1;
	bool temp=true;
	ifstream is_0("DVD.txt",ios_base::in|ios_base::binary);
	if(!is_0)
	{
		cout<<setw(31)<<" "<<"文件打开失败!"<<endl;
		exit(1);
	}
	if(is_0.peek()==EOF)
	{
		cout<<setw(31)<<" "<<"暂无数据!"<<endl;
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
	cout<<setw(31)<<" "<<"请输入查看方式:编    号(升序)——1"<<endl;
	cout<<setw(46)<<" "<<"编    号(降序)——2"<<endl;
	cout<<setw(46)<<" "<<"电影评分(升序)——3"<<endl;
	//选择排序(建立sortScore升序链表)
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
			if(max->nextNode()==NULL)		//max处于链尾
			{
				if(q->nextNode()==max)		//q、max相邻
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
			else if(q->nextNode()==NULL)	//q处于链尾
			{
				if(max->nextNode()==q)		//q、max相邻
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
				if(max->nextNode()==q||q->nextNode()==max)		//q、max相邻
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
	cout<<setw(46)<<" "<<"电影评分(降序)——4"<<endl;
	cout<<setw(46)<<" "<<"上映日期(升序)——5"<<endl;
	//冒泡排序(建立sortData升序链表)
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
	cout<<setw(46)<<" "<<"上映日期(降序)——6"<<endl;
	cout<<setw(46)<<" "<<"回到主页——7"<<endl;
	cout<<setw(31)<<" "<<"请输入:";
	do
	{
		if(!temp)
		{
			cout<<setw(31)<<" "<<"输入错误!"<<endl;
			cin.clear();
			cin.sync();
			cout<<setw(31)<<" "<<"请重新输入:";
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
			//输出数据
			p=sortNum_r->nextNode();
			cout<<left<<setw(7)<<"编号"<<left<<setw(26)<<"影片名"<<left<<setw(28)<<"主演"<<left<<setw(10)<<"上映时间"<<left<<setw(6)<<"分数"<<"余"<<endl;
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
			//输出数据
			p=sortNum_dvdList.getRear();
			cout<<left<<setw(7)<<"编号"<<left<<setw(26)<<"影片名"<<left<<setw(28)<<"主演"<<left<<setw(10)<<"上映时间"<<left<<setw(6)<<"分数"<<"余"<<endl;
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
			cout<<left<<setw(7)<<"编号"<<left<<setw(26)<<"影片名"<<left<<setw(28)<<"主演"<<left<<setw(10)<<"上映时间"<<left<<setw(6)<<"分数"<<"余"<<endl;
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
			//输出数据
			p=sortScore_dvdList.getRear();
			cout<<left<<setw(7)<<"编号"<<left<<setw(26)<<"影片名"<<left<<setw(28)<<"主演"<<left<<setw(10)<<"上映时间"<<left<<setw(6)<<"分数"<<"余"<<endl;
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
			//输出数据
			p=sortData_r->nextNode();
			cout<<left<<setw(7)<<"编号"<<left<<setw(26)<<"影片名"<<left<<setw(28)<<"主演"<<left<<setw(10)<<"上映时间"<<left<<setw(6)<<"分数"<<"余"<<endl;
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
			//输出数据
			p=sortData_dvdList.getRear();
			cout<<left<<setw(7)<<"编号"<<left<<setw(26)<<"影片名"<<left<<setw(28)<<"主演"<<left<<setw(10)<<"上映时间"<<left<<setw(6)<<"分数"<<"余"<<endl;
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

//查看会员信息
bool vipInfo()
{
	system("cls");
	Node<MI> *r=NULL;	//头结点
	LinkedList<MI> vipList(r);	//链表类
	MI buf;		//临时存储区
	ifstream is_0("VIP.txt",ios_base::in|ios_base::binary);
	float order=-1;
	bool temp=true;
	if(!is_0)
	{
		cout<<setw(31)<<" "<<"打开文件失败!\n";
		exit(1);
	}
	if(is_0.peek()==EOF)
	{
		cout<<setw(31)<<" "<<"暂时没有信息!\n";
		is_0.close();
		return false;
	}
	do
	{
		if(!temp)
		{
			cout<<setw(31)<<" "<<"输入错误！"<<endl;
			cin.clear();
			cin.sync();
		}
		cout<<setw(31)<<" "<<"请输入查看方式:升序——1"<<endl;
		cout<<setw(46)<<" "<<"降序——2"<<endl;
		cout<<setw(31)<<" "<<"请输入:";
		cin>>order;
		temp=false;
	}while(order!=1&&order!=2||cin.fail()||isFloat(order));
	temp=true;
	if(order==1)		//升序
	{
		while(is_0.peek()!=EOF)
		{
			is_0.read(reinterpret_cast<char*>(&buf),sizeof(buf));
			vipList.insertFront(buf);
		}
	}
	else				//降序
	{
		while(is_0.peek()!=EOF)
		{
			is_0.read(reinterpret_cast<char*>(&buf),sizeof(buf));
			vipList.insertRear(buf);
		}
	}
	is_0.close();
	cout<<setw(4)<<" ";
	cout<<left<<setw(14)<<"编号"<<left<<setw(24)<<"用户名"<<left<<setw(12)<<"余额"<<left<<setw(9)<<"state"<<"注册日期"<<endl;
	while(!vipList.endOfList())
	{
		r=r->nextNode();
		r->data.display();
		vipList.next();
	}
	return true;
}

//查看租用信息
bool rentInfo()
{
	system("cls");
	Node<MI> *r=NULL;	//头结点
	LinkedList<MI> vipList(r);	//链表类
	MI buf;		//临时存储区
	ifstream is_0("VIP.txt",ios_base::in|ios_base::binary);
	if(!is_0)
	{
		cout<<setw(31)<<" "<<"打开文件失败!\n";
		exit(1);
	}
	if(is_0.peek()==EOF)
	{
		cout<<setw(31)<<" "<<"暂时没有信息!\n";
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
	cout<<left<<setw(14)<<"编号"<<left<<setw(24)<<"用户名"<<left<<setw(12)<<"余额"<<left<<setw(5)<<"state\n";
	while(!vipList.endOfList())
	{
		r=r->nextNode();
		r->data.display();
		vipList.next();
	}
	return true;
}

//修改信息
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
				cout<<setw(31)<<" "<<"输入错误!\n";
				cin.clear();
				cin.sync();
			}
			cout<<setw(31)<<" "<<"修改:昵称——1"<<endl;
			cout<<setw(36)<<" "<<"密码——2"<<endl;
			cout<<setw(31)<<" "<<"请输入:";
			cin>>order;
			temp=false;
		}while(order!=1&&order!=2||cin.fail()||isFloat(order));
		temp=true;
		ifstream is_0("MANAGER.txt",ios_base::in|ios_base::binary);
		is_0.read(reinterpret_cast<char *>(&mana),sizeof(mana));
		is_0.close();
		if(order==1)
		{
			cout<<setw(31)<<" "<<"新昵称:";
			do
			{
				cin>>name;
			}while(!judgeNum(name,18));
			strcpy_s(mana.name,19,name.c_str());
			cout<<setw(31)<<" "<<"修改成功!\n";
			ofstream os_0("MANAGER.txt",ios_base::out|ios_base::binary);
			os_0.write(reinterpret_cast<char *>(&mana),sizeof(mana));
			os_0.close();
		}
		else
		{
			cout<<setw(31)<<" "<<"新密码:";
			do
			{
				cin>>password;
			}while(!judgeNum(password,12));
			mana.setPassword(password);
			cout<<setw(31)<<" "<<"修改成功!\n";
			ofstream os_0("MANAGER.txt",ios_base::out|ios_base::binary);
			os_0.write(reinterpret_cast<char *>(&mana),sizeof(mana));
			os_0.close();
		}
		cout<<setw(31)<<" "<<"是否继续修改(Y/N)?"<<endl;
		do
		{
			if(!temp)
			{
				cout<<setw(31)<<" "<<"输入错误,请重新输入!\n";
				cin.sync();
			}
			cout<<setw(31)<<" "<<"请输入:";
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

//编辑DVD信息
bool editDVDInfo()
{
	system("cls");
	Node<DI>* r=NULL;	//头结点
	LinkedList<DI> dvdList(r);		//DVD链表
	Node<DI>* p=NULL;
	Node<DI>* q=NULL;
	DI buf;		//临时存储区
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
				cout<<setw(31)<<" "<<"输入有误!"<<endl;
				cin.clear();
				cin.sync();
			}
			cout<<setw(31)<<" "<<"请输入查找方式:编号——1"<<endl;
			cout<<setw(46)<<" "<<"电影名——2"<<endl;
			cout<<setw(31)<<" "<<"请输入:";
			cin>>order;
			temp=false;
		}while(order!=1&&order!=2||cin.fail()||isFloat(order));
		temp=true;
		//将DVD信息从文件输入到链表
		ifstream is_0("DVD.txt",ios_base::in|ios_base::binary);
		if(!is_0)
		{
			cout<<setw(31)<<" "<<"文件打开失败!\n";
			exit(1);
		}
		if(is_0.peek()==EOF)
		{
			cout<<setw(31)<<" "<<"暂时没有数据!"<<endl;
			return false;
		}
		while(is_0.peek()!=EOF)
		{
			is_0.read(reinterpret_cast<char*>(&buf),sizeof(buf));
			dvdList.insertRear(buf);
		}
		is_0.close();
		//开始查找
		//用编号查找
		if(order==1)
		{
			cout<<setw(31)<<" "<<"请输入编号:";
			cin>>dvdNum;
			p=r->nextNode();
			for(i=0;i<dvdList.getSize()&&(p->data.getNum())!=dvdNum;i++)
			{
				p=p->nextNode();
				isFind=true;
			}
			if(i==dvdList.getSize())
			{
				cout<<setw(31)<<" "<<"没有找到相关数据!\n";
			}
			else
			{
				isFind=true;
			}
		}
		//用电影名查找
		else
		{
			cout<<setw(31)<<" "<<"请输入电影全称:";
			cin>>dvdName;
			p=r->nextNode();
			for(i=0;i<dvdList.getSize()&&p->data.name!=dvdName;i++)
			{
				p=p->nextNode();
			}
			if(i==dvdList.getSize())
			{
				cout<<setw(31)<<" "<<"没有找到相关数据!\n";
			}
			else
			{
				isFind=true;
			}
		}
		if(isFind==true)
		{
			cout<<setw(31)<<" "<<"DVD信息如下:"<<endl;
			cout<<left<<setw(7)<<"编号"<<left<<setw(26)<<"影片名"<<left<<setw(28)<<"主演"<<left<<setw(10)<<"上映时间"<<left<<setw(6)<<"分数"<<"余"<<endl;
			p->data.display();
			system("pause");
			p->data.editInfo();
			//将修改后的dvd链表重新输出到文件
			ofstream os_0("DVD.txt",ios_base::out|ios_base::binary);
			if(!os_0)
			{
				cout<<setw(31)<<" "<<"文件打开失败!\n";
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
				cout<<setw(31)<<" "<<"输入有误!请重新输入!"<<endl;
				cin.clear();
				cin.sync();
			}
			cout<<setw(31)<<" "<<"继续修改——1"<<endl;
			cout<<setw(31)<<" "<<"回到主页——2"<<endl;
			cin>>t;
			temp=false;
		}while(t!=1&&t!=2||cin.fail()||isFloat(t));
		temp=true;
		if(t==2)
		{
			break;	//回到主页
		}
		isFind=false;
	}
	return true;
}

//判断DVD是否存在
bool isExistDVDName(string s)
{
	Node<DI> *r=NULL;	//头结点
	Node<DI> *p=NULL;
	Node<DI> *q=NULL;
	LinkedList<DI> dvdList(r);	//链表类
	DI buf;
	ifstream is_0("DVD.txt",ios_base::in|ios_base::binary);
	while(is_0.peek()!=EOF)
	{
		is_0.read(reinterpret_cast<char*>(&buf),sizeof(buf));
		if(buf.name==s)
		{
			cout<<setw(31)<<" "<<"该DVD已存在!\n"<<endl;
			cout<<setw(31)<<" "<<"请重新输入:";
			is_0.close();
			return true;
		}
	}
	is_0.close();
	return false;
}