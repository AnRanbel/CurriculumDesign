#ifndef NODE_H
#define NODE_H

//类模板的定义
template<class T>
class Node
{
private:
	Node<T> *next;			//指向后继结点的指针
	Node<T> *last;			//指向前面结点的指针
public:
	T data;					//数据域
	Node();					//默认构造函数
	Node(const T &data,Node<T> *next=0);		//构造函数
	Node(const Node & p);						//复制构造函数
	void insertAfter(Node<T>*p);				//在本结点之后插入一个同类节点p
	Node<T>*deleteAfter();						//删除本结点的后继结点，并返回其地址
	void setNextNode();							//设置后继结点
	void setNextNode(Node<T>* n);
	void setLastNode(Node<T>* n);				//设置前面的结点
	void setLastNode();
	Node<T>*nextNode() const;					//获取后继结点的地址
	Node<T>*lastNode() const;					//获取前面结点的地址
	void copyNode(Node<T>* p);				//复制本结点
};

//类的实现部分
//默认构造函数
template<class T>
Node<T>::Node()
{
	;
}

//构造函数,初始化数据和指针成员
template<class T>
Node<T>::Node(const T& data,Node<T>*next):data(data),next(next)
{
	this->last=NULL;
}

//复制构造函数
template<class T>
Node<T>::Node(const Node<T> & p):data(p.data),next(p.nextNode())
{
	;
}

//复制本结点
template<class T>
void Node<T>::copyNode(Node<T>* p)
{
	data=p->data;
	next=p->nextNode();
}

//在本结点之后插入一个同类节点p
template<class T>
void Node<T>::insertAfter(Node<T>*p)
{
	p->next=next;		//p结点指针域指向当前结点的后继结点
	next=p;				//当前结点的指针域指向p
}

//删除本结点的后继结点，并返回其地址
template<class T>
Node<T>* Node<T>::deleteAfter()
{
	Node<T> *tempPtr=next;		//将欲删除的结点地址存储到tempPtr中
	if(next==0)					//如果当前结点没有后继结点,则返回空指针
	{
		return 0;
	}
	next=tempPtr->next;			//使当前结点的指针域指向tempPtr的后继结点
	return tempPtr;
}

//设置后继结点
template<class T>
void Node<T>::setNextNode()
{
	next=NULL;
}

//设置后继结点
template<class T>
void Node<T>::setNextNode(Node<T>* n)
{
	next=n;
}

//设置后继结点
template<class T>
void Node<T>::setLastNode()
{
	last=NULL;
}

//设置前面结点
template<class T>
void Node<T>::setLastNode(Node<T>* n)
{
	last=n;
}

//返回后继结点的指针
template<class T>
Node<T>* Node<T>::nextNode() const
{
	return next;
}

template<class T>

//返回前面结点的指针
Node<T>* Node<T>::lastNode() const
{
	return last;
}

#endif				//NODE_H