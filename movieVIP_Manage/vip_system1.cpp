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
extern bool checkDVD();			//查看DVD
extern bool isFloat(double n);				//判断是否为小数		

//将字符串转换为基本类型
template<class Type>
Type stringToNum(const string&str)
{
	std::istringstream iss(str);
	Type num;
	iss>>num;
	return num;
}

//登录
void loginVIP()
{
	bool isExistVipName(string s);	//判断用户名是否存在
	system("cls");
	Node<DI> *dvd_r=NULL;	//头结点
	Node<DI> *dvd_p=NULL;
	Node<DI> *dvd_q=NULL;
	LinkedList<DI> dvdList(dvd_r);	//链表类
	DI dvdBuf;		//临时存储区
	void charge(MI & p);	//缴费系统
	string vipName;
	string password;
	string dvdName;
	string vipPassword;
	int dvdNum;
	Node<MI> *vip_r=NULL;	//头结点
	Node<MI> *vip_p=NULL;
	Node<MI> *vip_q=NULL;
	string t_name="";		//临时存储字符
	string t_pas="";
	bool temp=true;
	bool isFind=false;
	double order=-1;
	double t=-1;
	char c;
	LinkedList<MI> vipList(vip_r);	//链表类
	MI vipBuf;		//临时存储区
	ManaInfo manaBuf;
	int i;
	//将管理员信息提出
	ifstream manaFile("MANAGER.txt",ios_base::in|ios_base::binary);
	if(!manaFile)
	{
		cout<<setw(31)<<" "<<"文件打开失败!"<<endl;
		exit(1);
	}
	manaFile.read(reinterpret_cast<char*>(&manaBuf),sizeof(ManaInfo));
	manaFile.close();
	//将会员信息提出
	ifstream vipFile("VIP.txt",ios_base::in|ios_base::binary);
	if(!vipFile)
	{
		cout<<setw(31)<<" "<<"文件打开失败!"<<endl;
		exit(1);
	}
	while(vipFile.peek()!=EOF)
	{
		vipFile.read(reinterpret_cast<char*>(&vipBuf),sizeof(vipBuf));
		vipList.insertAfter(vipBuf);
		vipList.next();
	}
	vipFile.close();
	//将DVD信息提出
	ifstream dvdFile("DVD.txt",ios_base::in|ios_base::binary);
	if(!dvdFile)
	{
		cout<<setw(31)<<" "<<"文件打开失败!"<<endl;
		exit(1);
	}
	while(dvdFile.peek()!=EOF)
	{
		dvdFile.read(reinterpret_cast<char*>(&dvdBuf),sizeof(dvdBuf));
		dvdList.insertAfter(dvdBuf);
		dvdList.next();
	}
	dvdFile.close();
	vip_p=vip_r->nextNode();
	while(true)
	{
		if(temp)
		{
			cout<<setw(31)<<" "<<"用户名:";
			cin>>vipName;
			cout<<setw(31)<<" "<<"密码:";
			cin>>password;
		}
		t_name=vip_p->data.name;
		t_pas=vip_p->data.getPassword();
		if(t_name==vipName&&t_pas==password)
		{
			system("cls");
			temp=true;
			while(true)
			{
				system("cls");
				cout<<setw(31)<<" "<<"查看DVD——1"<<endl;
				cout<<setw(31)<<" "<<"个人信息——2"<<endl;
				cout<<setw(31)<<" "<<"租用DVD——3"<<endl;
				cout<<setw(31)<<" "<<"归还DVD——4"<<endl;
				cout<<setw(31)<<" "<<"编辑资料——5"<<endl;
				cout<<setw(31)<<" "<<"缴纳费用——6"<<endl;
				cout<<setw(31)<<" "<<"退出系统——7"<<endl;
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
					}while(order<1||order>7||cin.fail()||isFloat(order));
					temp=true;
					system("cls");
					//查看DVD
					if(order==1)
					{
						system("cls");
						checkDVD();
					}

					//查看个人信息
					else if(order==2)
					{
						system("cls");
						cout<<setw(4)<<" ";
						cout<<left<<setw(14)<<"编号"<<left<<setw(24)<<"用户名"<<left<<setw(12)<<"余额"<<left<<setw(9)<<"state"<<"注册日期"<<endl;
						vip_p->data.display();
					}

					//租用DVD
					else if(order==3)
					{
						system("cls");
						while(true)
						{
							system("cls");
							do
							{
								if(!temp)
								{
									cout<<setw(31)<<" "<<"输入错误!"<<endl;
									cin.clear();
									cin.sync();
								}
								cout<<setw(31)<<" "<<"请选择查找方式:编号——1"<<endl;
								cout<<setw(46)<<" "<<"电影名——2"<<endl;
								cout<<setw(31)<<" "<<"请输入方式:";
								cin>>t;
								temp=false;
							}while(t<1||t>2||cin.fail()||isFloat(t));
							temp=true;
							//用编号查找
							dvd_p=dvd_r->nextNode();
							if(t==1)
							{
								system("cls");
								cout<<setw(31)<<" "<<"请输入编号:";
								cin>>dvdNum;
								for(i=0;i<dvdList.getSize()&&(dvd_p->data.getNum())!=dvdNum;i++)
								{
									dvd_p=dvd_p->nextNode();
								}
								if(i==dvdList.getSize())
								{
									cout<<setw(31)<<" "<<"没有找到相关数据!\n";
									break;
								}
								//找到
								else
								{
									if(vip_p->data.getBalance()>=1.5&&vip_p->data.getState()<3&&dvd_p->data.getStock()>0)	//设置可以租DVD的条件
									{
										isFind=true;
									}
								}
							}
							//用电影名查找
							else
							{
								system("cls");
								cout<<setw(31)<<" "<<"请输入电影全称:";
								cin>>dvdName;
								for(i=0;i<dvdList.getSize()&&dvd_p->data.name!=dvdName;i++)
								{
									dvd_p=dvd_p->nextNode();
								}
								if(i==dvdList.getSize())
								{
									cout<<setw(31)<<" "<<"没有找到相关数据!\n";
									break;
								}
								//找到
								else
								{
									if(vip_p->data.getBalance()>=1.5&&vip_p->data.getState()<3&&dvd_p->data.getStock()>0)	//设置可以租DVD的条件
									{
										isFind=true;
									}
								}
							}
							if(isFind==true)
							{
								vip_p->data.setBalance(-1.5);		//修改账户余额
								vip_p->data.setDVDInfo_rent(dvd_p->data);	//修改租用信息
								dvd_p->data.setStock(-1);			//修改DVD存货
								manaBuf.setGain(1.5);				//修改管理员信息
								cout<<setw(31)<<" "<<"租用成功!"<<endl;
								ofstream ovipFile("VIP.txt",ios_base::out|ios_base::binary);
								ofstream odvdFile("DVD.txt",ios_base::out|ios_base::binary);
								ofstream omanaFile("MANAGER.txt",ios_base::out|ios_base::binary);
								if(!odvdFile)
								{
									cout<<setw(31)<<" "<<"文件打开失败!"<<endl;
									exit(1);
								}
								dvdList.reset(0);
								dvd_q=dvd_r->nextNode();
								//将修改后的dvd链表重新输出到文件
								while(!dvdList.endOfList())
								{
									odvdFile.write(reinterpret_cast<char *>(&dvd_q->data),sizeof(dvd_q->data));
									dvd_q=dvd_q->nextNode();
									dvdList.next();
								}
								odvdFile.close();
								if(!ovipFile)
								{
									cout<<setw(31)<<" "<<"文件打开失败!"<<endl;
									exit(1);
								}
								vipList.reset(0);
								vip_q=vip_r->nextNode();
								//将修改后的vip链表重新输出到文件
								while(!vipList.endOfList())
								{
									ovipFile.write(reinterpret_cast<char *>(&vip_q->data),sizeof(vip_q->data));
									vip_q=vip_q->nextNode();
									vipList.next();
								}
								ovipFile.close();
								//将修改后的mana链表重新输出到文件
								if(!omanaFile)
								{
									cout<<setw(31)<<" "<<"文件打开失败!"<<endl;
									exit(1);
								}
								omanaFile.write(reinterpret_cast<char *>(&manaBuf),sizeof(manaBuf));
								omanaFile.close();
								break;
							}
							else
							{
								if(vip_p->data.getBalance()<1.5)
								{
									cout<<setw(31)<<" "<<"您的账户余额不足1.5，请前往主页进行充值~~"<<endl;
									break;	//回到主页
								}
								else if(vip_p->data.getState()==3)
								{
									cout<<setw(31)<<" "<<"您已经租了3张影片了哟，可以先前往主页归还一张DVD~~"<<endl;
									break;	//回到主页
								}
								else if(dvd_p->data.getStock()==0)
								{
									cout<<setw(31)<<" "<<"对不起,该DVD暂时没有剩余~~"<<endl;
								}
								cout<<setw(31)<<" "<<"是否继续租用DVD(Y/N)?"<<endl;
								do
								{
									if(!temp)
									{
										cout<<setw(31)<<" "<<"输入错误,请重新输入!\n";
										cin.ignore('1024','\n');
									}
									cout<<setw(31)<<" "<<"请输入:";
									cin>>c;
									temp=false;
								}while(c!='y'&&c!='Y'&&c!='n'&&c!='N');
								temp=true;
								if(c=='n'||c=='N')
								{
									break;	//回到主页
								}
							}
						}
						isFind=false;
					}

					//归还DVD
					else if(order==4)
					{
						system("cls");
						while(true)
						{
							system("cls");
							do
							{
								if(!temp)
								{
									cout<<setw(31)<<" "<<"输入错误!"<<endl;
									cin.clear();
									cin.sync();
								}
								cout<<setw(31)<<" "<<"请选择查找方式:编号——1"<<endl;
								cout<<setw(46)<<" "<<"电影名——2"<<endl;
								cout<<setw(31)<<" "<<"请输入方式:";
								cin>>t;
								temp=false;
							}while(t<1||t>2||cin.fail()||isFloat(t));
							temp=true;
							//用编号查找
							dvd_p=dvd_r->nextNode();
							if(t==1)
							{
								system("cls");
								cout<<setw(31)<<" "<<"请输入编号:";
								cin>>dvdNum;
								for(i=0;i<dvdList.getSize()&&(dvd_p->data.getNum())!=dvdNum;i++)
								{
									dvd_p=dvd_p->nextNode();
								}
								if(i==dvdList.getSize())
								{
									cout<<setw(31)<<" "<<"没有找到相关数据!\n";
									break;
								}
								//找到
								else
								{
									if(vip_p->data.isExist(dvdNum))
									{
										isFind=true;
									}
								}
							}
							//用电影名查找
							else
							{
								system("cls");
								cout<<setw(31)<<" "<<"请输入电影全称:";
								cin>>dvdName;
								for(i=0;i<dvdList.getSize()&&dvd_p->data.name!=dvdName;i++)
								{
									dvd_p=dvd_p->nextNode();
								}
								if(i==dvdList.getSize())
								{
									cout<<setw(31)<<" "<<"没有找到相关数据!\n";
									break;
								}
								//找到
								else
								{
									if(vip_p->data.isExist(dvd_p->data.getNum()))
									{
										isFind=true;
									}
								}
							}
							if(isFind==true)
							{
								vip_p->data.setDVDInfo_return(dvd_p->data);	//修改租用信息
								dvd_p->data.setStock(1);			//修改DVD存货
								cout<<setw(31)<<" "<<"归还成功!"<<endl;
								ofstream ovipFile("VIP.txt",ios_base::out|ios_base::binary);
								ofstream odvdFile("DVD.txt",ios_base::out|ios_base::binary);
								if(!dvdFile)
								{
									cout<<setw(31)<<" "<<"文件打开失败!"<<endl;
									exit(1);
								}
								dvdList.reset(0);
								dvd_q=dvd_r->nextNode();
								//将修改后的dvd链表重新输出到文件
								while(!dvdList.endOfList())
								{
									odvdFile.write(reinterpret_cast<char *>(&dvd_q->data),sizeof(dvd_q->data));
									dvd_q=dvd_q->nextNode();
									dvdList.next();
								}
								odvdFile.close();
								if(!vipFile)
								{
									cout<<setw(31)<<" "<<"文件打开失败!"<<endl;
									exit(1);
								}
								vipList.reset(0);
								vip_q=vip_r->nextNode();
								//将修改后的vip链表重新输出到文件
								while(!vipList.endOfList())
								{
									ovipFile.write(reinterpret_cast<char *>(&vip_q->data),sizeof(vip_q->data));
									vip_q=vip_q->nextNode();
									vipList.next();
								}
								ovipFile.close();
							}
							else
							{
								cout<<setw(31)<<" "<<"您的DVD租用信息与此不符,请前往主页查看~~"<<endl;
								break;
							}
							cout<<setw(31)<<" "<<"是否继续归还DVD(Y/N)?"<<endl;
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
								break;	//回到主页
							}
						}
						isFind=false;
					}

					//编辑资料
					else if(order==5)
					{
						system("cls");
						while(true)
						{
							system("cls");
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
								cin>>t;
								temp=false;
							}while(t<1||t>2||cin.fail()||isFloat(t));
							temp=true;
							if(t==1)
							{
								system("cls");
								cout<<setw(31)<<" "<<"新昵称:";
								do
								{
									cin>>vipName;
								}while(!judgeNum(vipName,18)||isExistVipName(vipName));
								strcpy_s(vip_p->data.name,19,vipName.c_str());
								cout<<setw(31)<<" "<<"修改成功!\n";
								ofstream ovipFile("VIP.txt",ios_base::out|ios_base::binary);
								vip_q=vip_r->nextNode();
								vipList.reset(0);
								while(!vipList.endOfList())
								{
									ovipFile.write(reinterpret_cast<char *>(&vip_q->data),sizeof(vip_q->data));
									vip_q=vip_q->nextNode();
									vipList.next();
								}
								ovipFile.close();
							}
							else
							{
								system("cls");
								cout<<setw(31)<<" "<<"新密码:";
								do
								{
									cin>>vipPassword;
								}while(!judgeNum(vipPassword,12));
								vip_p->data.setPassword(vipPassword);
								cout<<setw(31)<<" "<<"修改成功!\n";
								ofstream ovipFile("VIP.txt",ios_base::out|ios_base::binary);
								vip_q=vip_r->nextNode();
								vipList.reset(0);
								while(!vipList.endOfList())
								{
									ovipFile.write(reinterpret_cast<char *>(&vip_q->data),sizeof(vip_q->data));
									vip_q=vip_q->nextNode();
									vipList.next();
								}
								ovipFile.close();
							}
							cout<<setw(31)<<" "<<"是否继续修改(Y/N)?"<<endl;
							do
							{
								if(!temp)
								{
									cout<<setw(31)<<" "<<"输入错误,请重新输入!\n";
									cin.ignore(1024,'\n');
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
					}

					//缴纳费用
					else if(order==6)
					{
						system("cls");
						charge(vip_p->data);
						ofstream ovipFile("VIP.txt",ios_base::out|ios_base::binary);
						vip_q=vip_r->nextNode();
						while(!vipList.endOfList())
						{
							ovipFile.write(reinterpret_cast<char *>(&vip_q->data),sizeof(vip_q->data));
							vip_q=vip_q->nextNode();
							vipList.next();
						}
						ovipFile.close();
					}

					//退出系统
					else if(order==7)
					{
						exit(0);
					}

					//输入错误
					else
					{
						temp=false;
					}
				}while(!temp);
				temp=true;
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
				if(order==1)
				{
					continue;	//回到主页
				}
				else
				{
					vipList.clear();	//退出当前程序
					exit(0);
				}
			}
		}
		vip_p=vip_p->nextNode();
		temp=false;
		if(vip_p==NULL)
		{
			temp=true;
			cout<<setw(31)<<" "<<"用户名或密码错误!\n";
			vip_p=vip_r->nextNode();
		}
	}
}

//注册
void enroll()
{
	bool isExistVipName(string s);			//判断用户名是否存在
	void charge(MI & p);
	MI buf;		//临时存储区
	string a;	//临时存储区
	char b[5];	//临时存储区
	int order;
	int seat;
	bool temp=true;
	string vipName;			//用户名
	string num;				//编号
	string password;		//密码
	char year[5];			//日期
	char month[3];
	char day[3];
	char tailNum[5];
	CTime t=CTime::GetCurrentTime();		//获取当前系统的时间
	cout<<setw(31)<<" "<<"用户名:";
	do
	{
		cin>>vipName;
	}while(!judgeNum(vipName,18)||isExistVipName(vipName));
	cout<<setw(31)<<" "<<"密码:";
	do
	{
		cin>>password;
	}while(!judgeNum(password,12));
	system("cls");
	sprintf_s(year,5,"%04d",t.GetYear());	//获取年分
	sprintf_s(month,3,"%02d",t.GetMonth());	//获取月分
	sprintf_s(day,3,"%02d",t.GetDay());		//获取日
	//确定编号
	((num+=year)+=month)+=day;
	ifstream is_0("VIP.txt",ios_base::in|ios_base::binary);
	if(!is_0)
	{
		cout<<setw(31)<<" "<<"打开文件失败!\n";
		exit(1);
	}
	if(is_0.peek()==EOF)	//若文件为空
	{
		sprintf_s(tailNum,5,"%04d",1);
	}
	else
	{
		seat=sizeof(buf);
		is_0.seekg(-seat,ios_base::end);
		is_0.read(reinterpret_cast<char*>(&buf),sizeof(buf));
		a=buf.getNum();
		sprintf_s(b,3,"%02d",t.GetDay());
		if(a.substr(6,2)!=b)	//不是同一天
		{
			sprintf_s(tailNum,5,"%04d",1);
		}
		else
		{
			a=a.substr(8,4);
			sprintf_s(tailNum,5,"%04d",stringToNum<int>(a)+1);
		}
	}
	is_0.close();
	num+=tailNum;
	MI vip(vipName,num,password,year,month,day);
	cout<<setw(31)<<" "<<"是否充值？"<<endl;
	cout<<setw(31)<<" "<<"是——1"<<endl;
	cout<<setw(31)<<" "<<"否——2"<<endl;
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
	}while(order<1||order>2||cin.fail()||isFloat(order));
	if(order==1)
	{
		charge(vip);
	}
	cout<<setw(31)<<" "<<"注册成功!"<<endl;
	system("pause");
	system("cls");
	//将数据传入文件
	ofstream os_0("VIP.txt",ios_base::app|ios_base::binary);
	if(!os_0)	//若文件打开失败
	{
		cout<<setw(31)<<" "<<"文件打开失败！"<<endl;
		exit(1);//退出程序
	}
	os_0.write(reinterpret_cast<char *>(&vip),sizeof(vip));
	os_0.close();
}

//缴费
void charge(MI & p)
{
	system("cls");
	bool temp=true;
	//bool isDigit=true;
	double money=0.0;
	do
	{
		if(!temp)
		{
			cout<<setw(31)<<" "<<"输入错误！\n";
			cin.clear();			//回到正常输入状态
			cin.sync();				//清空流
		}
		cout<<setw(31)<<" "<<"充值金额:";
		cin>>money;
		temp=false;
	}while(money<=0||cin.fail());
	p.setBalance(money);
	cout<<setw(31)<<" "<<"充值成功!"<<endl;
}

//判断用户名是否存在
bool isExistVipName(string s)
{
	Node<MI> *r=NULL;	//头结点
	Node<MI> *p=NULL;
	Node<MI> *q=NULL;
	string vipName;
	LinkedList<MI> vipList(r);	//链表类
	MI buf;
	ifstream is_0("VIP.txt",ios_base::in|ios_base::binary);
	while(is_0.peek()!=EOF)
	{
		is_0.read(reinterpret_cast<char*>(&buf),sizeof(buf));
		if(buf.name==s)
		{
			cout<<setw(31)<<" "<<"用户名已存在!\n"<<endl;
			cout<<setw(31)<<" "<<"请重新输入:";
			is_0.close();
			return true;
		}
	}
	is_0.close();
	return false;
}