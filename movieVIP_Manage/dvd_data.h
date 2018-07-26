#ifndef _DVD_DATA
#define _DVD_DATA

#include<string>

using std::string;

struct data					//���ڽṹ��
{
	char year[5];
	char month[3];
	char day[3];
};

typedef class DVDInfo			//DVD��Ϣ��
{
private:
	char role[27];				//����
	data t_rent;				//����������
	int stock;					//���
	double score;				//��������
public:
	char name[25];			//DVD����
	unsigned int num;			//DVD���
	data t_show; 				//��ӳ����
	DVDInfo() {};				//Ĭ�Ϲ��캯��
	DVDInfo(string na,unsigned n,string r,string y_sh,string m_sh,string d_sh,int sto,double soc,string y_re="",string m_re="",string d_re="");					//һ�㹹�캯��
	DVDInfo(const DVDInfo & p);						//���ƹ��캯��
	~DVDInfo() {}									//��������
	void display() const;							//�������
	bool isEmpty() const;							//�жϴ���Ƿ�Ϊ��
	unsigned int getNum() const;								//��ñ��
	string getShowTime() const;							//�����ӳ����
	string getRentTime() const;							//��ñ���������
	int getStock() const;							//��ô��
	void setRentData(string y,string m,string d);		//���ñ���������
	void setStock(int n);								//�޸Ĵ��
	double getScore()const;							//��÷���
	bool editInfo();								//�޸���Ϣ
}DI;

#endif				//_DVD_DATA