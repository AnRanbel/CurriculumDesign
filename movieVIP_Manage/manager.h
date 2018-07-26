#ifndef _MANAGER_DATA
#define _MANAGER_DATA

#include<string>
#include"dvd_data.h"

using std::string;

class ManaInfo			//����Ա��Ϣ��
{
private:
	char password[13];			//����
	double sum;					//������
	data t_business;			//��ʼӪҵ������
public:
	char name[19];				//����Ա�ǳ�
	ManaInfo() {}				//Ĭ�Ϲ��캯��
	ManaInfo(string n,string p,string y="",string m="",string d="",double s=0.0);		//���캯��
	ManaInfo(const ManaInfo &p);		//���ƹ��캯��
	~ManaInfo() {}				//��������
	int edit(const int order);				//�޸�����
	string getBusinessTime() const;			//��ÿ�ʼӪҵ������
	string getPassword() const;				//�������
	void setPassword(string p);					//��������
	void setGain(double s);				//����������Ϣ
};


#endif					//_MANAGER_DATA