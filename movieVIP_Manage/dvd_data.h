#ifndef _DVD_DATA
#define _DVD_DATA

#include<string>

using std::string;

struct data					//日期结构体
{
	char year[5];
	char month[3];
	char day[3];
};

typedef class DVDInfo			//DVD信息类
{
private:
	char role[27];				//主演
	data t_rent;				//被租用日期
	int stock;					//存货
	double score;				//豆瓣评分
public:
	char name[25];			//DVD名字
	unsigned int num;			//DVD编号
	data t_show; 				//上映日期
	DVDInfo() {};				//默认构造函数
	DVDInfo(string na,unsigned n,string r,string y_sh,string m_sh,string d_sh,int sto,double soc,string y_re="",string m_re="",string d_re="");					//一般构造函数
	DVDInfo(const DVDInfo & p);						//复制构造函数
	~DVDInfo() {}									//析构函数
	void display() const;							//输出函数
	bool isEmpty() const;							//判断存货是否为空
	unsigned int getNum() const;								//获得编号
	string getShowTime() const;							//获得上映日期
	string getRentTime() const;							//获得被租用日期
	int getStock() const;							//获得存货
	void setRentData(string y,string m,string d);		//设置被租用日期
	void setStock(int n);								//修改存货
	double getScore()const;							//获得分数
	bool editInfo();								//修改信息
}DI;

#endif				//_DVD_DATA