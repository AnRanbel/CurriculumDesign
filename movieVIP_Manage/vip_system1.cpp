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

extern bool judgeNum(const string &s,int n);//�ж��ַ��������Ƿ�Ϸ�
extern bool checkDVD();			//�鿴DVD
extern bool isFloat(double n);				//�ж��Ƿ�ΪС��		

//���ַ���ת��Ϊ��������
template<class Type>
Type stringToNum(const string&str)
{
	std::istringstream iss(str);
	Type num;
	iss>>num;
	return num;
}

//��¼
void loginVIP()
{
	bool isExistVipName(string s);	//�ж��û����Ƿ����
	system("cls");
	Node<DI> *dvd_r=NULL;	//ͷ���
	Node<DI> *dvd_p=NULL;
	Node<DI> *dvd_q=NULL;
	LinkedList<DI> dvdList(dvd_r);	//������
	DI dvdBuf;		//��ʱ�洢��
	void charge(MI & p);	//�ɷ�ϵͳ
	string vipName;
	string password;
	string dvdName;
	string vipPassword;
	int dvdNum;
	Node<MI> *vip_r=NULL;	//ͷ���
	Node<MI> *vip_p=NULL;
	Node<MI> *vip_q=NULL;
	string t_name="";		//��ʱ�洢�ַ�
	string t_pas="";
	bool temp=true;
	bool isFind=false;
	double order=-1;
	double t=-1;
	char c;
	LinkedList<MI> vipList(vip_r);	//������
	MI vipBuf;		//��ʱ�洢��
	ManaInfo manaBuf;
	int i;
	//������Ա��Ϣ���
	ifstream manaFile("MANAGER.txt",ios_base::in|ios_base::binary);
	if(!manaFile)
	{
		cout<<setw(31)<<" "<<"�ļ���ʧ��!"<<endl;
		exit(1);
	}
	manaFile.read(reinterpret_cast<char*>(&manaBuf),sizeof(ManaInfo));
	manaFile.close();
	//����Ա��Ϣ���
	ifstream vipFile("VIP.txt",ios_base::in|ios_base::binary);
	if(!vipFile)
	{
		cout<<setw(31)<<" "<<"�ļ���ʧ��!"<<endl;
		exit(1);
	}
	while(vipFile.peek()!=EOF)
	{
		vipFile.read(reinterpret_cast<char*>(&vipBuf),sizeof(vipBuf));
		vipList.insertAfter(vipBuf);
		vipList.next();
	}
	vipFile.close();
	//��DVD��Ϣ���
	ifstream dvdFile("DVD.txt",ios_base::in|ios_base::binary);
	if(!dvdFile)
	{
		cout<<setw(31)<<" "<<"�ļ���ʧ��!"<<endl;
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
			cout<<setw(31)<<" "<<"�û���:";
			cin>>vipName;
			cout<<setw(31)<<" "<<"����:";
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
				cout<<setw(31)<<" "<<"�鿴DVD����1"<<endl;
				cout<<setw(31)<<" "<<"������Ϣ����2"<<endl;
				cout<<setw(31)<<" "<<"����DVD����3"<<endl;
				cout<<setw(31)<<" "<<"�黹DVD����4"<<endl;
				cout<<setw(31)<<" "<<"�༭���ϡ���5"<<endl;
				cout<<setw(31)<<" "<<"���ɷ��á���6"<<endl;
				cout<<setw(31)<<" "<<"�˳�ϵͳ����7"<<endl;
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
					}while(order<1||order>7||cin.fail()||isFloat(order));
					temp=true;
					system("cls");
					//�鿴DVD
					if(order==1)
					{
						system("cls");
						checkDVD();
					}

					//�鿴������Ϣ
					else if(order==2)
					{
						system("cls");
						cout<<setw(4)<<" ";
						cout<<left<<setw(14)<<"���"<<left<<setw(24)<<"�û���"<<left<<setw(12)<<"���"<<left<<setw(9)<<"state"<<"ע������"<<endl;
						vip_p->data.display();
					}

					//����DVD
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
									cout<<setw(31)<<" "<<"�������!"<<endl;
									cin.clear();
									cin.sync();
								}
								cout<<setw(31)<<" "<<"��ѡ����ҷ�ʽ:��š���1"<<endl;
								cout<<setw(46)<<" "<<"��Ӱ������2"<<endl;
								cout<<setw(31)<<" "<<"�����뷽ʽ:";
								cin>>t;
								temp=false;
							}while(t<1||t>2||cin.fail()||isFloat(t));
							temp=true;
							//�ñ�Ų���
							dvd_p=dvd_r->nextNode();
							if(t==1)
							{
								system("cls");
								cout<<setw(31)<<" "<<"��������:";
								cin>>dvdNum;
								for(i=0;i<dvdList.getSize()&&(dvd_p->data.getNum())!=dvdNum;i++)
								{
									dvd_p=dvd_p->nextNode();
								}
								if(i==dvdList.getSize())
								{
									cout<<setw(31)<<" "<<"û���ҵ��������!\n";
									break;
								}
								//�ҵ�
								else
								{
									if(vip_p->data.getBalance()>=1.5&&vip_p->data.getState()<3&&dvd_p->data.getStock()>0)	//���ÿ�����DVD������
									{
										isFind=true;
									}
								}
							}
							//�õ�Ӱ������
							else
							{
								system("cls");
								cout<<setw(31)<<" "<<"�������Ӱȫ��:";
								cin>>dvdName;
								for(i=0;i<dvdList.getSize()&&dvd_p->data.name!=dvdName;i++)
								{
									dvd_p=dvd_p->nextNode();
								}
								if(i==dvdList.getSize())
								{
									cout<<setw(31)<<" "<<"û���ҵ��������!\n";
									break;
								}
								//�ҵ�
								else
								{
									if(vip_p->data.getBalance()>=1.5&&vip_p->data.getState()<3&&dvd_p->data.getStock()>0)	//���ÿ�����DVD������
									{
										isFind=true;
									}
								}
							}
							if(isFind==true)
							{
								vip_p->data.setBalance(-1.5);		//�޸��˻����
								vip_p->data.setDVDInfo_rent(dvd_p->data);	//�޸�������Ϣ
								dvd_p->data.setStock(-1);			//�޸�DVD���
								manaBuf.setGain(1.5);				//�޸Ĺ���Ա��Ϣ
								cout<<setw(31)<<" "<<"���óɹ�!"<<endl;
								ofstream ovipFile("VIP.txt",ios_base::out|ios_base::binary);
								ofstream odvdFile("DVD.txt",ios_base::out|ios_base::binary);
								ofstream omanaFile("MANAGER.txt",ios_base::out|ios_base::binary);
								if(!odvdFile)
								{
									cout<<setw(31)<<" "<<"�ļ���ʧ��!"<<endl;
									exit(1);
								}
								dvdList.reset(0);
								dvd_q=dvd_r->nextNode();
								//���޸ĺ��dvd��������������ļ�
								while(!dvdList.endOfList())
								{
									odvdFile.write(reinterpret_cast<char *>(&dvd_q->data),sizeof(dvd_q->data));
									dvd_q=dvd_q->nextNode();
									dvdList.next();
								}
								odvdFile.close();
								if(!ovipFile)
								{
									cout<<setw(31)<<" "<<"�ļ���ʧ��!"<<endl;
									exit(1);
								}
								vipList.reset(0);
								vip_q=vip_r->nextNode();
								//���޸ĺ��vip��������������ļ�
								while(!vipList.endOfList())
								{
									ovipFile.write(reinterpret_cast<char *>(&vip_q->data),sizeof(vip_q->data));
									vip_q=vip_q->nextNode();
									vipList.next();
								}
								ovipFile.close();
								//���޸ĺ��mana��������������ļ�
								if(!omanaFile)
								{
									cout<<setw(31)<<" "<<"�ļ���ʧ��!"<<endl;
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
									cout<<setw(31)<<" "<<"�����˻�����1.5����ǰ����ҳ���г�ֵ~~"<<endl;
									break;	//�ص���ҳ
								}
								else if(vip_p->data.getState()==3)
								{
									cout<<setw(31)<<" "<<"���Ѿ�����3��ӰƬ��Ӵ��������ǰ����ҳ�黹һ��DVD~~"<<endl;
									break;	//�ص���ҳ
								}
								else if(dvd_p->data.getStock()==0)
								{
									cout<<setw(31)<<" "<<"�Բ���,��DVD��ʱû��ʣ��~~"<<endl;
								}
								cout<<setw(31)<<" "<<"�Ƿ��������DVD(Y/N)?"<<endl;
								do
								{
									if(!temp)
									{
										cout<<setw(31)<<" "<<"�������,����������!\n";
										cin.ignore('1024','\n');
									}
									cout<<setw(31)<<" "<<"������:";
									cin>>c;
									temp=false;
								}while(c!='y'&&c!='Y'&&c!='n'&&c!='N');
								temp=true;
								if(c=='n'||c=='N')
								{
									break;	//�ص���ҳ
								}
							}
						}
						isFind=false;
					}

					//�黹DVD
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
									cout<<setw(31)<<" "<<"�������!"<<endl;
									cin.clear();
									cin.sync();
								}
								cout<<setw(31)<<" "<<"��ѡ����ҷ�ʽ:��š���1"<<endl;
								cout<<setw(46)<<" "<<"��Ӱ������2"<<endl;
								cout<<setw(31)<<" "<<"�����뷽ʽ:";
								cin>>t;
								temp=false;
							}while(t<1||t>2||cin.fail()||isFloat(t));
							temp=true;
							//�ñ�Ų���
							dvd_p=dvd_r->nextNode();
							if(t==1)
							{
								system("cls");
								cout<<setw(31)<<" "<<"��������:";
								cin>>dvdNum;
								for(i=0;i<dvdList.getSize()&&(dvd_p->data.getNum())!=dvdNum;i++)
								{
									dvd_p=dvd_p->nextNode();
								}
								if(i==dvdList.getSize())
								{
									cout<<setw(31)<<" "<<"û���ҵ��������!\n";
									break;
								}
								//�ҵ�
								else
								{
									if(vip_p->data.isExist(dvdNum))
									{
										isFind=true;
									}
								}
							}
							//�õ�Ӱ������
							else
							{
								system("cls");
								cout<<setw(31)<<" "<<"�������Ӱȫ��:";
								cin>>dvdName;
								for(i=0;i<dvdList.getSize()&&dvd_p->data.name!=dvdName;i++)
								{
									dvd_p=dvd_p->nextNode();
								}
								if(i==dvdList.getSize())
								{
									cout<<setw(31)<<" "<<"û���ҵ��������!\n";
									break;
								}
								//�ҵ�
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
								vip_p->data.setDVDInfo_return(dvd_p->data);	//�޸�������Ϣ
								dvd_p->data.setStock(1);			//�޸�DVD���
								cout<<setw(31)<<" "<<"�黹�ɹ�!"<<endl;
								ofstream ovipFile("VIP.txt",ios_base::out|ios_base::binary);
								ofstream odvdFile("DVD.txt",ios_base::out|ios_base::binary);
								if(!dvdFile)
								{
									cout<<setw(31)<<" "<<"�ļ���ʧ��!"<<endl;
									exit(1);
								}
								dvdList.reset(0);
								dvd_q=dvd_r->nextNode();
								//���޸ĺ��dvd��������������ļ�
								while(!dvdList.endOfList())
								{
									odvdFile.write(reinterpret_cast<char *>(&dvd_q->data),sizeof(dvd_q->data));
									dvd_q=dvd_q->nextNode();
									dvdList.next();
								}
								odvdFile.close();
								if(!vipFile)
								{
									cout<<setw(31)<<" "<<"�ļ���ʧ��!"<<endl;
									exit(1);
								}
								vipList.reset(0);
								vip_q=vip_r->nextNode();
								//���޸ĺ��vip��������������ļ�
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
								cout<<setw(31)<<" "<<"����DVD������Ϣ��˲���,��ǰ����ҳ�鿴~~"<<endl;
								break;
							}
							cout<<setw(31)<<" "<<"�Ƿ�����黹DVD(Y/N)?"<<endl;
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
								break;	//�ص���ҳ
							}
						}
						isFind=false;
					}

					//�༭����
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
									cout<<setw(31)<<" "<<"�������!\n";
									cin.clear();
									cin.sync();
								}
								cout<<setw(31)<<" "<<"�޸�:�ǳơ���1"<<endl;
								cout<<setw(36)<<" "<<"���롪��2"<<endl;
								cout<<setw(31)<<" "<<"������:";
								cin>>t;
								temp=false;
							}while(t<1||t>2||cin.fail()||isFloat(t));
							temp=true;
							if(t==1)
							{
								system("cls");
								cout<<setw(31)<<" "<<"���ǳ�:";
								do
								{
									cin>>vipName;
								}while(!judgeNum(vipName,18)||isExistVipName(vipName));
								strcpy_s(vip_p->data.name,19,vipName.c_str());
								cout<<setw(31)<<" "<<"�޸ĳɹ�!\n";
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
								cout<<setw(31)<<" "<<"������:";
								do
								{
									cin>>vipPassword;
								}while(!judgeNum(vipPassword,12));
								vip_p->data.setPassword(vipPassword);
								cout<<setw(31)<<" "<<"�޸ĳɹ�!\n";
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
							cout<<setw(31)<<" "<<"�Ƿ�����޸�(Y/N)?"<<endl;
							do
							{
								if(!temp)
								{
									cout<<setw(31)<<" "<<"�������,����������!\n";
									cin.ignore(1024,'\n');
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
					}

					//���ɷ���
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

					//�˳�ϵͳ
					else if(order==7)
					{
						exit(0);
					}

					//�������
					else
					{
						temp=false;
					}
				}while(!temp);
				temp=true;
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
				if(order==1)
				{
					continue;	//�ص���ҳ
				}
				else
				{
					vipList.clear();	//�˳���ǰ����
					exit(0);
				}
			}
		}
		vip_p=vip_p->nextNode();
		temp=false;
		if(vip_p==NULL)
		{
			temp=true;
			cout<<setw(31)<<" "<<"�û������������!\n";
			vip_p=vip_r->nextNode();
		}
	}
}

//ע��
void enroll()
{
	bool isExistVipName(string s);			//�ж��û����Ƿ����
	void charge(MI & p);
	MI buf;		//��ʱ�洢��
	string a;	//��ʱ�洢��
	char b[5];	//��ʱ�洢��
	int order;
	int seat;
	bool temp=true;
	string vipName;			//�û���
	string num;				//���
	string password;		//����
	char year[5];			//����
	char month[3];
	char day[3];
	char tailNum[5];
	CTime t=CTime::GetCurrentTime();		//��ȡ��ǰϵͳ��ʱ��
	cout<<setw(31)<<" "<<"�û���:";
	do
	{
		cin>>vipName;
	}while(!judgeNum(vipName,18)||isExistVipName(vipName));
	cout<<setw(31)<<" "<<"����:";
	do
	{
		cin>>password;
	}while(!judgeNum(password,12));
	system("cls");
	sprintf_s(year,5,"%04d",t.GetYear());	//��ȡ���
	sprintf_s(month,3,"%02d",t.GetMonth());	//��ȡ�·�
	sprintf_s(day,3,"%02d",t.GetDay());		//��ȡ��
	//ȷ�����
	((num+=year)+=month)+=day;
	ifstream is_0("VIP.txt",ios_base::in|ios_base::binary);
	if(!is_0)
	{
		cout<<setw(31)<<" "<<"���ļ�ʧ��!\n";
		exit(1);
	}
	if(is_0.peek()==EOF)	//���ļ�Ϊ��
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
		if(a.substr(6,2)!=b)	//����ͬһ��
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
	cout<<setw(31)<<" "<<"�Ƿ��ֵ��"<<endl;
	cout<<setw(31)<<" "<<"�ǡ���1"<<endl;
	cout<<setw(31)<<" "<<"�񡪡�2"<<endl;
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
	}while(order<1||order>2||cin.fail()||isFloat(order));
	if(order==1)
	{
		charge(vip);
	}
	cout<<setw(31)<<" "<<"ע��ɹ�!"<<endl;
	system("pause");
	system("cls");
	//�����ݴ����ļ�
	ofstream os_0("VIP.txt",ios_base::app|ios_base::binary);
	if(!os_0)	//���ļ���ʧ��
	{
		cout<<setw(31)<<" "<<"�ļ���ʧ�ܣ�"<<endl;
		exit(1);//�˳�����
	}
	os_0.write(reinterpret_cast<char *>(&vip),sizeof(vip));
	os_0.close();
}

//�ɷ�
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
			cout<<setw(31)<<" "<<"�������\n";
			cin.clear();			//�ص���������״̬
			cin.sync();				//�����
		}
		cout<<setw(31)<<" "<<"��ֵ���:";
		cin>>money;
		temp=false;
	}while(money<=0||cin.fail());
	p.setBalance(money);
	cout<<setw(31)<<" "<<"��ֵ�ɹ�!"<<endl;
}

//�ж��û����Ƿ����
bool isExistVipName(string s)
{
	Node<MI> *r=NULL;	//ͷ���
	Node<MI> *p=NULL;
	Node<MI> *q=NULL;
	string vipName;
	LinkedList<MI> vipList(r);	//������
	MI buf;
	ifstream is_0("VIP.txt",ios_base::in|ios_base::binary);
	while(is_0.peek()!=EOF)
	{
		is_0.read(reinterpret_cast<char*>(&buf),sizeof(buf));
		if(buf.name==s)
		{
			cout<<setw(31)<<" "<<"�û����Ѵ���!\n"<<endl;
			cout<<setw(31)<<" "<<"����������:";
			is_0.close();
			return true;
		}
	}
	is_0.close();
	return false;
}