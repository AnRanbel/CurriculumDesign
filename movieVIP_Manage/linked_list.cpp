#include"linked_list.h"

//���캯��
template<class T>
LinkedList<T>::LinkedList(Node<T>* &f,Node<T>* r,int s,int p):rear(r),size(s),position(p)
{
	f=new Node<T>;
	front=f;
	front->next=rear;
	rear->next=NULL;
}

//�ͷŽ��
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
		cout<<"����ʧ��!\n";
	}
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
	return(front->next==rear);
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

//�����α�ĵ�ǰλ��
template<class T>
int LinkedList<T>::currentPosition(void) const
{
	return position;
}

//�ڱ�ͷ������
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

//�ڱ�β��ӽ��
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
		k=k->next;
	}
	p->next=k;
	h->next=p;
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
		k=k->next;
	}
	p->next=k->next;
	k->next=p;
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
		k=k->next;
	}
	h->next=k->next;
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
		k=k->next;
	}
	return k->data;
}

//���ضԵ�ǰ����Ա���ݵĳ�����
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

//�������:�ͷ����н����ڴ�ռ䣬������������"operator="����
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