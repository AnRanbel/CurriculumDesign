#include"linked_list.h"

//构造函数
template<class T>
LinkedList<T>::LinkedList(Node<T>* &f,Node<T>* r,int s,int p):rear(r),size(s),position(p)
{
	f=new Node<T>;
	front=f;
	front->next=rear;
	rear->next=NULL;
}

//释放结点
template<class T>
void LinkedList<T>::freeNode(Node<T> *p)
{
	Node<T> *k=front;
	Node<T> *h=k->nextNode();
	while(h!=p&&h!=NULL)
	{
		k=h;
		h=k->nextNode();
	}
	if(h==p)
	{
		k->next=p->next;
		delete p;
	}
	else
	{
		cout<<"查找失败!\n";
	}
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
	return(front->next==rear);
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

//返回游标的当前位置
template<class T>
int LinkedList<T>::currentPosition(void) const
{
	return position;
}

//在表头插入结点
template<class T>
void LinkedList<T>::insertFront(const T &item)
{
	Node<T> *p=NULL;
	p=new Node<T>;
	p->data=item;
	p->next=front->next;
	front->next=p;
	size++;
}

//在表尾添加结点
template<class T>
void LinkedList<T>::insertRear(const T &item)
{
	Node<T> *p=NULL;
	p=new Node<T>;
	p->data=item;
	rear->next=p;
	p->next=NULL;
	rear=p;
	size++;
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
		k=k->next;
	}
	p->next=k;
	h->next=p;
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
		k=k->next;
	}
	p->next=k->next;
	k->next=p;
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
		k=k->next;
	}
	h->next=k->next;
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
		k=k->next;
	}
	return k->data;
}

//返回对当前结点成员数据的常引用
template<class T>
const T& LinkedList<T>::data() const
{
	int i;
	Node<T> *k=front;
	for(i=0;i<position;i++)
	{
		k=k->next;
	}
	return k->data;
}

//清空链表:释放所有结点的内存空间，被析构函数和"operator="调用
template<class T>
void LinkedList<T>::clear()
{
	int i;
	Node<T> *k=front;
	for(i=0;i<=size;i++)
	{
		delete k;
		size--;
		k=k->next;
	}
}