#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include"node.h"

template<class T>
class LinkedList
{
private:
	//数据成员
	Node<T> *front;		//表头指针
	Node<T> *rear;		//表尾指针
	int size;			//表中的元素个数
	int position;		//当前元素在表中的位置序号,由函数reset使用
public:
	LinkedList(Node<T>* &f,int s=0,int p=0);	//构造函数
	LinkedList(const LinkedList<T>& L);		//复制构造函数
	~LinkedList()		//析构函数
	{
		clear();
	}
	int getSize() const;			//返回链表中元素个数
	bool isEmpty() const;			//链表是否为空
	void reset(int pos);			//初始化游标的位置
	void next();					//使游标移到下一个结点
	bool endOfList() const;			//游标是否到了链尾
	void insertFront(const T &item);	//在表头插入结点
	void insertRear(const T &item);		//在表尾添加结点
	void insertAt(const T &item);		//在当前结点之前插入结点
	void insertAfter(const T &item);	//在当前结点之后插入结点
	void deleteCurrent();			//删除当前结点
	T& data();						//返回对当前结点成员数据的引用
	Node<T>* getRear() const;		//返回链尾指针
	Node<T>* getFront() const;		//返回链头指针
	int getPosition() const;		//获得游标位置
	void clear();					//清空链表:释放所有结点的内存空间
	void setRear(Node<T>* &p);		//设置尾结点
};

//类的实现
//复制构造函数
template<class T>
//复制构造函数
LinkedList<T>::LinkedList(const LinkedList<T>& L):size(L.size),position(L.position)
{
	Node<T>* p=NULL;
	Node<T>* k=NULL;
	Node<T>* h=NULL;
	front=new Node<T>;
	front->copyNode(L.getFront());
	rear=new Node<T>;
	rear->copyNode(L.getRear());
	k=L.getFront();
	h=this->front;
	h->setLastNode();
	if(size==1)
	{
		front->setNextNode(rear);
		rear->setLastNode(front);
		rear->setNextNode();
	}
	else
	{
		for(int i=0;i<L.getSize()-1;i++)
		{
			k=k->nextNode();
			p=new Node<T>;
			p->copyNode(k);
			p->setLastNode(h);
			h->setNextNode(p);
			p->setNextNode();
			h=p;
		}
		p->setNextNode(this->rear);
		rear->setLastNode(p);
		rear->setNextNode();
	}
}

//构造函数
template<class T>
LinkedList<T>::LinkedList(Node<T>* &f,int s,int p):size(s),position(p)
{
	f=new Node<T>;
	front=f;
	rear=new Node<T>;
	rear->setNextNode();
	front->setNextNode(rear);
}

//返回链表中元素个数
template<class T>
int LinkedList<T>::getSize() const
{
	return size;
}

//链表是否为空
template<class T>
bool LinkedList<T>::isEmpty() const
{
	return(front->nextNode()==rear);
}

//重置游标的位置
template<class T>
void LinkedList<T>::reset(int pos)
{
	position=pos;
}

//使游标移到下一个结点
template<class T>
void LinkedList<T>::next()
{
	position++;
}

//游标是否到了链尾
template<class T>
bool LinkedList<T>::endOfList() const
{
	return(position==size);
}

//在表头插入结点
template<class T>
void LinkedList<T>::insertFront(const T &item)
{
	if(size==0)
	{
		rear->data=item;
		size++;
	}
	else
	{
		Node<T> *p=NULL;
		p=new Node<T>;
		p->data=item;
		p->setNextNode(front->nextNode());
		//p->next=front->next;
		front->setNextNode(p);
		//front->next=p;
		size++;
	}
}

//在表尾添加结点
template<class T>
void LinkedList<T>::insertRear(const T &item)
{
	if(size==0)
	{
		rear->data=item;
		size++;
	}
	else
	{
		Node<T> *p=NULL;
		p=new Node<T>;
		p->data=item;
		p->setNextNode();
		rear->setNextNode(p);
		rear=p;
		size++;
	}
}

//在当前结点之前插入结点
template<class T>
void LinkedList<T>::insertAt(const T &item)
{
	int i;
	Node<T> *k=front;
	Node<T> *h=NULL;
	Node<T> *p=NULL;
	p=new Node<T>;
	p->data=item;
	for(i=0;i<position;i++)
	{
		h=k;
		k->
	}
	p->setNextNode(k);
	h->setNextNode(p);
	size++;
}

//在当前结点之后插入结点
template<class T>
void LinkedList<T>::insertAfter(const T &item)
{
	int i;
	Node<T> *k=front;
	Node<T> *p=NULL;
	p=new Node<T>;
	p->data=item;
	for(i=0;i<position;i++)
	{
		k=k->nextNode();
	}
	p->setNextNode(k->nextNode());
	k->setNextNode(p);
	size++;
}

//删除当前结点
template<class T>
void LinkedList<T>::deleteCurrent()
{
	int i;
	Node<T> *k=front;
	Node<T> *h=NULL;
	for(i=0;i<position;i++)
	{
		h=k;
		k=k->nextNode();
	}
	h->setNextNode(k->nextNode());
	delete k;
	size--;
}

//返回对当前结点成员数据的引用
template<class T>
T& LinkedList<T>::data()
{
	int i;
	Node<T> *k=front;
	for(i=0;i<position;i++)
	{
		k=k->nextNode();
		//k=k->next;
	}
	return k->data;
}

//返回链尾指针
template<class T>
Node<T>* LinkedList<T>::getRear() const
{
	return rear;
}

//返回链头指针
template<class T>
Node<T>* LinkedList<T>::getFront() const
{
	return front;
}

//获得游标位置
template<class T>
int LinkedList<T>::getPosition() const
{
	return position;
}

//清空链表:释放所有结点的内存空间
template<class T>
void LinkedList<T>::clear()
{
	int i;
	int sum=size;
	Node<T> *k=front;
	Node<T> *h=NULL;
	for(i=0;i<=sum;i++)
	{
		h=k->nextNode();
		delete k;
		size--;
		k=h;
	}
}

//设置尾结点
template<class T>
void LinkedList<T>::setRear(Node<T>* &p)
{
	rear=p;
}

#endif		//LINKEDLIST_H