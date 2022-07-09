# Merging-linked-list
链表合并交叉合并
## 数据结构课程设计

#### 题目一

要求：1.建立两个链表A和B，链表元素分别为m个和n个

​		   2.设元素分别为（x1，x2，x3.....xm）和（y1,y2,y3.....yn），把他们合并成一个线性表C

​			 当 m>=n 时，C=x1,y1,x2,y2,x3,y3.....xn,yn....xm

​			 当 m<n 时，C=y1,x1,y2,x2.y3,x3.....ym.xm....yn

​		   3.输出线性表C

​		   4.直接插入法对C链表排序，生成链表D，输出

------

### 数据结构

```c
typedef struct LNode {
	int data;				//数据域
	struct LNode *next;		 	//指针域
}LNode,*LinkList;

int flag;					//标志变量			
```

### 函数

```c
LinkList ListCreat_1(LNode *L);				    	  //链表灵活创建
LinkList ListCreat_2(int len);					  //链表指定元素创建		
LinkList ListInitiate(LinkList head);				  //链表初始化
LinkList ListInsert(LinkList head,int i,int x);		   	  //元素插入
LinkList ListDelete(LinkList head,int i);			  //节点删除
LinkList ListModify(LNode* head,int index, int data);   	  //元素修改
int Linklength(LinkList L);					  //求取链表长度
LinkList ListSort(LinkList head);			          //排序
LinkList ListUnion(LNode * L1,LNode * L2,LNode *L3);              //合并
void DisPlay(LNode *L);						  //打印
void Save(LinkList L,int flag);				          //数据上传
LinkList Loadin_A(LNode*L);					  //A文件导入
LinkList Loadin_B(LNode*L);					  //B导文件入
```

### 核心功能详解

1.根据要求链表合并

```c
LinkList ListUnion(LNode *l1,LNode *l2,LNode *l3){//主函数调用时已经判断链表A和B的长度，将长的传给l1
	LinkList p,q,r,s;				    		//工具指针
	l3=(LinkList)malloc(sizeof(LNode));  //L3头节点
	p=l1->next;							//p指向长链表的首元节点
	q=l2->next;							//p指向短链表的首元节点
	r=l3;								//r指向l3头节点
    
    
	//先将长链表的data域值赋给新链表的节点，后将短链表的data域的值赋值给下一个节点，直到q指向空，即短链表已经无元素可赋
	while(p&&q){
		s=(LinkList)malloc(sizeof(LNode));	 		//尾插法，生成新节点
		s->data=p->data;				    	//赋值
		r->next=s;						//连接
			r=s;						//后移
		p=p->next;						//被操作链表工具指针后移
		
		s=(LinkList)malloc(sizeof(LNode));		//尾插法（同上）
		s->data=q->data;
		r->next=s;
			r=s;
		q=q->next;
	}
		r->next=NULL;						//尾指针置空
	
    //将长链表未经合并的元素尾插至新链表之后
	if (p) {							//p之后还有元素
		while(p){							
		s=(LinkList)malloc(sizeof(LNode));		//尾插（过程同上）
		s->data=p->data;
		r->next=s;
		r=s;
		p=p->next;
		}
		r->next=NULL;
	}
	flag=5;
	Save(l3,flag);
	return l3;
}
```



2.直接插入排序

```c
LinkList ListSort(LinkList head){
		
LinkList p,pre,q;
// 使用指针p先保存下L中未排序元素（无序区中）的信息
p = L->next->next;
// 使用原链表L构造了一个有序区，有序区中只有一个元素，
// 这个元素是链表L的开始节点(头节点之后的那个节点)
L->next->next = NULL;
// 由于为了构造有序区，已经将待排序元素的第一个元素放在有序区中了，
// 所以从第二个元素开始遍历，也就是p = L->next->next。 
while(p != NULL){
	// 每循环一次p后移一位，直至p == NULL.
	// 进行插入有序区的操作时会改变p->next的值所以需要选保存一下
	q = p->next; 
	// 为方便比较，用一个指针pre,每次循环其都指向头节点，指向有序区。
	pre = L;  
	// 遍历有序区中的所有元素，直至有序区末尾或者找到:
	// p所指的元素 大于 pre的next所指的元素为止，
	while(pre->next != NULL && pre->next->data < p->data)
		pre = pre->next;
	// 找到比p大的节点后，执行插入操作，因为插入操作需要用到
	// 被插入节点的前驱节点，所以在比较时，用了pre->next来和p比较
	p->next = pre->next;
	pre->next = p;
	// 用q把p的值恢复过来，使得循环继续指向无序区的下一个节点
	p = q;  
}
```

### 扩展功能

见源代码
