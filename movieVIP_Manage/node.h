#ifndef NODE_H
#define NODE_H

//��ģ��Ķ���
template<class T>
class Node
{
private:
	Node<T> *next;			//ָ���̽���ָ��
	Node<T> *last;			//ָ��ǰ�����ָ��
public:
	T data;					//������
	Node();					//Ĭ�Ϲ��캯��
	Node(const T &data,Node<T> *next=0);		//���캯��
	Node(const Node & p);						//���ƹ��캯��
	void insertAfter(Node<T>*p);				//�ڱ����֮�����һ��ͬ��ڵ�p
	Node<T>*deleteAfter();						//ɾ�������ĺ�̽�㣬���������ַ
	void setNextNode();							//���ú�̽��
	void setNextNode(Node<T>* n);
	void setLastNode(Node<T>* n);				//����ǰ��Ľ��
	void setLastNode();
	Node<T>*nextNode() const;					//��ȡ��̽��ĵ�ַ
	Node<T>*lastNode() const;					//��ȡǰ����ĵ�ַ
	void copyNode(Node<T>* p);				//���Ʊ����
};

//���ʵ�ֲ���
//Ĭ�Ϲ��캯��
template<class T>
Node<T>::Node()
{
	;
}

//���캯��,��ʼ�����ݺ�ָ���Ա
template<class T>
Node<T>::Node(const T& data,Node<T>*next):data(data),next(next)
{
	this->last=NULL;
}

//���ƹ��캯��
template<class T>
Node<T>::Node(const Node<T> & p):data(p.data),next(p.nextNode())
{
	;
}

//���Ʊ����
template<class T>
void Node<T>::copyNode(Node<T>* p)
{
	data=p->data;
	next=p->nextNode();
}

//�ڱ����֮�����һ��ͬ��ڵ�p
template<class T>
void Node<T>::insertAfter(Node<T>*p)
{
	p->next=next;		//p���ָ����ָ��ǰ���ĺ�̽��
	next=p;				//��ǰ����ָ����ָ��p
}

//ɾ�������ĺ�̽�㣬���������ַ
template<class T>
Node<T>* Node<T>::deleteAfter()
{
	Node<T> *tempPtr=next;		//����ɾ���Ľ���ַ�洢��tempPtr��
	if(next==0)					//�����ǰ���û�к�̽��,�򷵻ؿ�ָ��
	{
		return 0;
	}
	next=tempPtr->next;			//ʹ��ǰ����ָ����ָ��tempPtr�ĺ�̽��
	return tempPtr;
}

//���ú�̽��
template<class T>
void Node<T>::setNextNode()
{
	next=NULL;
}

//���ú�̽��
template<class T>
void Node<T>::setNextNode(Node<T>* n)
{
	next=n;
}

//���ú�̽��
template<class T>
void Node<T>::setLastNode()
{
	last=NULL;
}

//����ǰ����
template<class T>
void Node<T>::setLastNode(Node<T>* n)
{
	last=n;
}

//���غ�̽���ָ��
template<class T>
Node<T>* Node<T>::nextNode() const
{
	return next;
}

template<class T>

//����ǰ�����ָ��
Node<T>* Node<T>::lastNode() const
{
	return last;
}

#endif				//NODE_H