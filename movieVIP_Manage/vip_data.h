#ifndef _VIP_DATA
#define _VIP_DATA

#include<string>
#include"dvd_data.h"

using std::string;

const int MAXNUM = 13;		//��Ա�������ֽ���

typedef class MemberInfo			//��Ա��Ϣ��
{
private:
	char num[13];			//��Ա���
	char password[13];	//��Ա����
	double balance;		//�˻����
	int state;			//��ʾ����DVD����Ŀ,ȡֵΪ0-3
	DI borrowDVD[3];	//����DVD��Ϣ
public:
	char name[19];		//�û���
	data enroll;		//ע������
	MemberInfo() {;}		//Ĭ�Ϲ��캯��
	MemberInfo(string n,string nu,string p,string y,string m,string d,double bal=0.0,int sta=0);			//һ�㹹�캯��
	MemberInfo(const MemberInfo &p);		//���ƹ��캯��
	~MemberInfo() {;}			//��������
	void display() const;							//�������
	int edit(const int order);							//�޸�����
	int buy();					//���ɹ����DVD����
	double getBalance() const;				//����û����
	string getPassword() const;				//�������
	string getEnrollTime() const;			//���ע������
	int getState() const;					//���������
	string getNum() const;					//��ñ��
	void setDVDInfo_rent(DI p);				//�������õ�DVD��Ϣ
	void setDVDInfo_return(const DI &p);	//���ù黹��DVD��Ϣ
	void setBalance(double b);				//�����˻����
	void setPassword(string p);				//�����˻�����
	bool isExist(string name);			//ͨ��Ӱ���ж�������Ϣ���Ƿ����
	bool isExist(int num);			//ͨ������ж�������Ϣ���Ƿ����
}MI;

#endif				//_VIP_DATA