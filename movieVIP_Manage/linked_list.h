#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include"node.h"

template<class T>
class LinkedList
{
private:
	//���ݳ�Ա
	Node<T> *front;		//��ͷָ��
	Node<T> *rear;		//��βָ��
	int size;			//���е�Ԫ�ظ���
	int position;		//��ǰԪ���ڱ��е�λ�����,�ɺ���resetʹ��
public:
	LinkedList(Node<T>* &f,int s=0,int p=0);	//���캯��
	LinkedList(const LinkedList<T>& L);		//���ƹ��캯��
	~LinkedList()		//��������
	{
		clear();
	}
	int getSize() const;			//����������Ԫ�ظ���
	bool isEmpty() const;			//�����Ƿ�Ϊ��
	void reset(int pos);			//��ʼ���α��λ��
	void next();					//ʹ�α��Ƶ���һ�����
	bool endOfList() const;			//�α��Ƿ�����β
	void insertFront(const T &item);	//�ڱ�ͷ������
	void insertRear(const T &item);		//�ڱ�β��ӽ��
	void insertAt(const T &item);		//�ڵ�ǰ���֮ǰ������
	void insertAfter(const T &item);	//�ڵ�ǰ���֮�������
	void deleteCurrent();			//ɾ����ǰ���
	T& data();						//���ضԵ�ǰ����Ա���ݵ�����
	Node<T>* getRear() const;		//������βָ��
	Node<T>* getFront() const;		//������ͷָ��
	int getPosition() const;		//����α�λ��
	void clear();					//�������:�ͷ����н����ڴ�ռ�
	void setRear(Node<T>* &p);		//����β���
};

//���ʵ��
//���ƹ��캯��
template<class T>
//���ƹ��캯��
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

//���캯��
template<class T>
LinkedList<T>::LinkedList(Node<T>* &f,int s,int p):size(s),position(p)
{
	f=new Node<T>;
	front=f;
	rear=new Node<T>;
	rear->setNextNode();
	front->setNextNode(rear);
}

//����������Ԫ�ظ���
template<class T>
int LinkedList<T>::getSize() const
{
	return size;
}

//�����Ƿ�Ϊ��
template<class T>
bool LinkedList<T>::isEmpty() const
{
	return(front->nextNode()==rear);
}

//�����α��λ��
template<class T>
void LinkedList<T>::reset(int pos)
{
	position=pos;
}

//ʹ�α��Ƶ���һ�����
template<class T>
void LinkedList<T>::next()
{
	position++;
}

//�α��Ƿ�����β
template<class T>
bool LinkedList<T>::endOfList() const
{
	return(position==size);
}

//�ڱ�ͷ������
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

//�ڱ�β��ӽ��
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

//�ڵ�ǰ���֮ǰ������
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

//�ڵ�ǰ���֮�������
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

//ɾ����ǰ���
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

//���ضԵ�ǰ����Ա���ݵ�����
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

//������βָ��
template<class T>
Node<T>* LinkedList<T>::getRear() const
{
	return rear;
}

//������ͷָ��
template<class T>
Node<T>* LinkedList<T>::getFront() const
{
	return front;
}

//����α�λ��
template<class T>
int LinkedList<T>::getPosition() const
{
	return position;
}

//�������:�ͷ����н����ڴ�ռ�
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

//����β���
template<class T>
void LinkedList<T>::setRear(Node<T>* &p)
{
	rear=p;
}

#endif		//LINKEDLIST_H