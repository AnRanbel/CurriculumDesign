#ifndef _MANAGER_DATA
#define _MANAGER_DATA

#include<string>
#include"dvd_data.h"

using std::string;

class ManaInfo			//管理员信息类
{
private:
	char password[13];			//密码
	double sum;					//总收益
	data t_business;			//开始营业的日期
public:
	char name[19];				//管理员昵称
	ManaInfo() {}				//默认构造函数
	ManaInfo(string n,string p,string y="",string m="",string d="",double s=0.0);		//构造函数
	ManaInfo(const ManaInfo &p);		//复制构造函数
	~ManaInfo() {}				//析构函数
	int edit(const int order);				//修改数据
	string getBusinessTime() const;			//获得开始营业的日期
	string getPassword() const;				//获得密码
	void setPassword(string p);					//重设密码
	void setGain(double s);				//设置收益信息
};


#endif					//_MANAGER_DATA