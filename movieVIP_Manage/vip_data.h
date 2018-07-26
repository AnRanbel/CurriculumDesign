#ifndef _VIP_DATA
#define _VIP_DATA

#include<string>
#include"dvd_data.h"

using std::string;

const int MAXNUM = 13;		//会员编号最大字节数

typedef class MemberInfo			//会员信息类
{
private:
	char num[13];			//会员编号
	char password[13];	//会员密码
	double balance;		//账户余额
	int state;			//表示租用DVD的数目,取值为0-3
	DI borrowDVD[3];	//所借DVD信息
public:
	char name[19];		//用户名
	data enroll;		//注册日期
	MemberInfo() {;}		//默认构造函数
	MemberInfo(string n,string nu,string p,string y,string m,string d,double bal=0.0,int sta=0);			//一般构造函数
	MemberInfo(const MemberInfo &p);		//复制构造函数
	~MemberInfo() {;}			//析构函数
	void display() const;							//输出函数
	int edit(const int order);							//修改数据
	int buy();					//还可购买的DVD数量
	double getBalance() const;				//获得用户余额
	string getPassword() const;				//获得密码
	string getEnrollTime() const;			//获得注册日期
	int getState() const;					//获得租用数
	string getNum() const;					//获得编号
	void setDVDInfo_rent(DI p);				//设置租用的DVD信息
	void setDVDInfo_return(const DI &p);	//设置归还的DVD信息
	void setBalance(double b);				//设置账户余额
	void setPassword(string p);				//重设账户密码
	bool isExist(string name);			//通过影名判断租用信息中是否存在
	bool isExist(int num);			//通过编号判断租用信息中是否存在
}MI;

#endif				//_VIP_DATA