#include<stdio.h>
#include<malloc.h>
#include<windows.h>

/*数据结构*/
typedef struct LNode {
	int data;					//数据域
	struct LNode *next; 		//指针域
}LNode,*LinkList;

int flag;

/*函数声明*/
LinkList ListCreat_1(LNode *L);				    	//链表灵活创建
LinkList ListCreat_2(int len);						//链表指定元素创建		
LinkList ListInitiate(LinkList head);				//链表初始化
LinkList ListInsert(LinkList head,int i,int x);		//元素插入
LinkList ListDelete(LinkList head,int i);			//节点删除
LinkList ListModify(LNode* head,int index, int data);//元素修改
int Linklength(LinkList L);							//求取链表长度
LinkList ListSort(LinkList head);					//排序
LinkList ListUnion(LNode * L1,LNode * L2,LNode *L3);//合并
void DisPlay(LNode *L);								//打印
void Save(LinkList L,int flag);						//数据上传
LinkList Loadin_A(LNode*L);							//A文件导入
LinkList Loadin_B(LNode*L);							//B导文件入

LinkList Loadin_A(LNode*L){
	L = (LinkList)malloc(sizeof(LNode));	//头节点
	LNode *p,*r = L;	
		FILE *fp = fopen("A.txt","r");
		int data;

	while(fscanf(fp,"%d",&data)!=EOF){
		p = (LinkList)malloc(sizeof(LNode));			//生成新节点p
		p->data=data;									//赋值给p的data域
													
		p->next=NULL;								
		r->next=p;								    	//p节点插入到尾节点r后	
		r=p;											//r指向新尾节点
	}	
	fclose(fp);
		flag=1;
		Save(L,flag);
	return L;	
}
LinkList Loadin_B(LNode*L){
	L = (LinkList)malloc(sizeof(LNode));	//头节点
	LNode *p,*r = L;	
		FILE *fp = fopen("B.txt","r");
		int data;

	while(fscanf(fp,"%d",&data)!=EOF){
		p = (LinkList)malloc(sizeof(LNode));			//生成新节点p
		p->data=data;									//赋值给p的data域									
		p->next=NULL;								
		r->next=p;								    	//p节点插入到尾节点r后	
		r=p;											//r指向新尾节点
	}	
	fclose(fp);
	flag=1;
	Save(L,flag);
	return L;	
}
void Save(LinkList L,int flag){
	FILE* fp = fopen("nlist.txt", "a");
	if (fp == NULL){
		printf("\t\t\t\t\t打开存档文件失败！\n");
		return ;
	}
	L=L->next;
	
	switch (flag) {
		case 1:{char s[20]="链表创建:";fprintf(fp,"%s",s);break;}
		case 2:{char s[20]="节点插入:";fprintf(fp,"%s",s);break;}
		case 3:{char s[20]="节点删除:";fprintf(fp,"%s",s);break;}
		case 4:{char s[20]="节点修改:";fprintf(fp,"%s",s);break;}
		case 5:{char s[20]="交叉合并:";fprintf(fp,"%s",s);break;}
		case 6:{char s[20]="排序输出:";fprintf(fp,"%s",s);break;}
		case 7:{char s[20]="初始化";fprintf(fp,"%s",s);break;}
		case 8:{char s[20]="打印:";fprintf(fp,"%s",s);break;}
	}
    while(L!=NULL)
    {
    	
      fprintf(fp,"%d ",L->data);
      L=L->next;
 
    }
    fprintf(fp,"\n");
	fclose(fp);
	return;
}

LinkList ListCreat_1(LNode *L){ //灵活创建链表
	printf("\t\t\t\t\t正在建立链表，请输入数据（-1结束）：\n\t\t\t\t\t");
	L=(LinkList)malloc(sizeof(LNode));	
	LNode *s,*r;
	r=L;
	int t;
	scanf("%d",&t);
	while(t!=-1) {
		s=(LinkList)malloc(sizeof(LNode));	//新节点
		s->data=t;							//赋值
		r->next=s;							//连接
		r=s;								//标致指针后移
		scanf("%d",&t);
	}
	r->next=NULL;
		flag=1;
	Save(L,flag);
	
	return L;
}

LinkList ListCreat_2(int len){	//固定元素创建
	
	printf("\t\t\t\t\t正在建立链表：");
	LNode *head = (LinkList)malloc(sizeof(LNode));	//头节点
	LNode *p,*r = head;	
	int x;
	for(int i = 0;i < len;i++){
		p = (LinkList)malloc(sizeof(LNode));			//生成新节点p
		scanf("%d",&x);									//输入元素值
		p->data=x;									//x赋值给p的data域
		p->next=NULL;								
		r->next=p;									//p节点插入到尾节点r后	
		r=p;											//r指向新尾节点
	}
	flag=1;
	
	Save(head,flag);
	
	
	return head;
}

LinkList ListInitiate(LinkList head){			//初始化
	
	head = (LinkList)malloc(sizeof(LNode));	
	head->next = NULL;
	flag=7;
	
	Save(head,flag);							//头节点指针域指空
	return head;
}
LinkList ListInsert(LinkList head,int i,int x){	 //i为插入的位置，x为插入元素的值
	LNode *p,*q;
	int j = 0;
	p = head;
	/*查找到i-1个节点*/
	while(p->next != NULL && j < i-1){			//p指向i-1节点		
		p = p->next;
		j++;
	}
	q = (LinkList)malloc(sizeof(LNode));		//创建新的节点
	q->data = x;								//data域置x
	q->next = p->next;							//新节点naxt域指向ai
	p->next = q;								//p的next域指向新节点
	printf("\t\t\t\t\t插入完成\n");
	flag=2;
	Save(head,flag);
	
	return head;
	
}

LinkList ListDelete(LinkList head,int i){
	LNode *p,*q;
	
	int j = 0;
	p = head;
	/*查找第i-1个节点*/
	while(p->next != NULL && j < i-1){			//p指向i-1节点
		p = p->next;
		j++;
	}
	q = p->next;								//q指向要被删除的节点
	p->next = p->next->next; 					//置i-1节点的next为i+1节点
	free(q);									//释放
	printf("\t\t\t\t\t删除完成\n");
	flag=3;
	Save(head,flag);
	
	return head;
}
int Linklength(LinkList L)//求单链表长度
{
    int k=0;
    while(L!=NULL)
    { 
        k++;					//计数加1
        L=L->next;				//指向下一节点
    }
    return k;
}

LinkList ListModify(LNode* head,int index, int data)//元素修改
{
	
    if(head == NULL || index < 0)		//链表判断
        return head;
        
    LNode* node = head;
    for (int i = 0; i < index; ++i)		//循环找需求节点
    {
        if (node == NULL)				//所选节点超出实际范围
            return head;
        node = node->next;	//指针后移
    }
    node->data =  data;		//data域赋值
    flag=4;
    Save(head,flag);
    return head;
    
}

LinkList ListSort(LinkList head){
		
	LinkList p,pre,q;
	p = head->next->next;		  
	head->next->next = NULL;	// 变成只有一个元素的有序表
								
	while(p != NULL){		
		q = p->next;	//因为p若插入，则
		pre = head;	
		while(pre->next !=NULL && pre->next->data < p->data) // 遍历pre所指向的有序表，直至找到比p大的节点
			pre = pre->next; 	
		p->next = pre->next;	//p的next和pre的next节点连接
		pre->next = p;			//前驱连接
		p = q;	
	} 
	flag=6;
	Save(head,flag);
	
	return head;
	
}


void DisPlay(LNode *L) {		//打印链表
	LNode *p=L->next;			//指向首元节点	
	while(p!=NULL) {
		printf ("%d ",p->data);	//打印
		p=p->next;				//指针后移
	}
	printf("\n");
}
LinkList ListUnion(LNode *l1,LNode *l2,LNode *l3){
	LinkList p,q,r,s;				    //工具指针
	l3=(LinkList)malloc(sizeof(LNode)); //L3头节点
	p=l1->next;
	q=l2->next;
	r=l3;

	while(p&&q){
		s=(LinkList)malloc(sizeof(LNode));	//尾插法
		s->data=p->data;					//赋值
		r->next=s;							//连接
			r=s;							//后移
		p=p->next;							//被操作链表工具指针后移
		
		s=(LinkList)malloc(sizeof(LNode));	//尾插法
		s->data=q->data;
		r->next=s;
			r=s;
		q=q->next;
	}
		r->next=NULL;						//尾指针置空
		
	if (p) {								//p之后还有元素
		while(p){
		s=(LinkList)malloc(sizeof(LNode));	//尾插
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

void Menu(){
	printf("\t\t\t\t\t╔—————————————————╗\n");
	printf("\t\t\t\t\t丨               菜单              丨\n");
	printf("\t\t\t\t\t丨         （1）创建链表           丨\n");
	printf("\t\t\t\t\t丨         （2）节点插入           丨\n");	
	printf("\t\t\t\t\t丨         （3）节点删除           丨\n");
	printf("\t\t\t\t\t丨         （4）节点修改           丨\n");
	printf("\t\t\t\t\t丨         （5）交叉合并           丨\n");
	printf("\t\t\t\t\t丨         （6）排序输出           丨\n");
	printf("\t\t\t\t\t丨         （7）初始化             丨\n");
	printf("\t\t\t\t\t丨         （8）打印               丨\n");
	printf("\t\t\t\t\t丨         （9）退出               丨\n");
	printf("\t\t\t\t\t╚—————————————————╝\n");
	printf("\t\t\t\t\t请输入您的选项:");	
}
int main (){
	
	LNode *L1,*L2,*L3,*L4;
	int long1,long2;		
	int choice;
	
	Menu();
	scanf("%d",&choice);
	
	while(choice>=1&&choice<=100){
		switch (choice) {
			case 1:
				{
					printf("\t\t\t\t\t选择创建方式(1-灵活创建，2-特定元素数目创建，3-文件导入)");
					int choic_;
					scanf("%d",&choic_);
					if(choic_==1){
						printf("\t\t\t\t\t是否初次创建（1--是，0--否）");
						int n1;
						scanf("%d",&n1);
						if(n1==1){
							L1=ListCreat_1(L1);			//创建链表1
								printf("\t\t\t\t\t链表1已经建立\n");
								long1 = Linklength(L1);	//链表1长度		
								
							L2=ListCreat_1(L2);			//创建链表2
								printf("\t\t\t\t\t链表2已经建立\n");
								long2 = Linklength(L2);	//链表2长度								
						}
						
						else if(n1==0){
							printf("\t\t\t\t\t选择要创建的链表（1--L1，2--L2）");
							int xx;
							scanf("%d",&xx);
							if(xx==1){ 
								L1=ListCreat_1(L1);	//创建链表1
								printf("\t\t\t\t\t链表1已经建立\n");
								long1 = Linklength(L1);	//链表1长度		
							}
							else{	
							L2=ListCreat_1(L2);   	//创建链表2
								printf("\t\t\t\t\t链表2已经建立\n");
								long2 = Linklength(L2);	//链表2长度								
							}
							
						}						
					}
					else if(choic_==2){
						printf("\t\t\t\t\t是否初次创建（1--是，0--否）");
						int d1;
						scanf("%d",&d1);
						if(d1==1){
							printf("\t\t\t\t\t请输入链表1元素个数:");
							int m;
							scanf("%d",&m);
							L1=ListCreat_2(m);	//创建链表1
							long1 = Linklength(L1);	
							printf("\t\t\t\t\t链表1已经建立\n");
							
								
							printf("\t\t\t\t\t请输入链表2元素个数:");
							int n;
							scanf("%d",&n);	
							L2=ListCreat_2(n);	//创建链表2
							long2 = Linklength(L2);	//链表2长度	
							printf("\t\t\t\t\t链表2已经建立\n");
														
				
						}
						
						else if(d1==0){
							printf("\t\t\t\t\t选择要创建的链表（1--L1，2--L2）");
							int m;
							scanf("%d",&m);
							
							if(m==1){
								printf("\t\t\t\t\t请输入链表1元素个数:");
								int m;
								scanf("%d",&m);
								L1=ListCreat_2(m);	//创建链表1
								printf("\t\t\t\t\t链表1已经建立\n");
								long1 = Linklength(L1);	//链表1长度		
							}		
							else{		
								printf("\t\t\t\t\t请输入链表2元素个数:");
								int n;
								scanf("%d",&n);	
								L2=ListCreat_2(n);   	//创建链表2
								printf("\t\t\t\t\t链表2已经建立\n");
								long2 = Linklength(L2);	//更新链表2长度								
							}	
						}					
					}	
					else{
						L1=Loadin_A(L1);
						long1 = Linklength(L1);//长度更新
						L2=Loadin_B(L2);
						long2 = Linklength(L2);//长度更新
						printf("\t\t\t\t\t数据导入完成！\n");
					}
					break;
				}
			case 2:
				{
					printf("\n\t\t\t\t\t选择要插入的链表（1--L1，2--L2）");
					int n,i,x;
					
					scanf("%d",&n);
					if(n==1){
						printf("\n\t\t\t\t\t请输入插入的位置及元素：");
				
						scanf("%d%d",&i,&x);
						L1=ListInsert(L1,i,x);
						long1 = Linklength(L1);		//更新链表长度			
					}
					else{
						printf("\n\t\t\t\t\t请输入插入的位置及元素：");
					
						scanf("%d%d",&i,&x);	
				    	L2=ListInsert(L2,i,x);	
						long2 = Linklength(L2);		//更新链表长度			
					}
	
					break;
				}
			case 3:
				{
					printf("\t\t\t\t\t选择要进行删除的链表（1--L1，2--L2）");
					int n;
					scanf("%d",&n);
					if(n==1){
						printf("\t\t\t\t\t请输入要删除的节点：");
						int a;
				     	scanf("%d",&a);
				   	L1=ListDelete(L1,a);	
					   long1 = Linklength(L1);	
					}
					else{
						printf("\t\t\t\t\t请输入要删除的节点：");
						int a;
						scanf("%d",&a);
					 L2=ListDelete(L2,a);
					 	long2 = Linklength(L2);					
					}
						
				break;
				}
				
			case 4:
				{
			    	printf("\n\t\t\t\t\t选择要修改的链表（1--L1，2--L2）");
			    	int a;
			    	scanf("%d",&a);
			    	if(a==1){
						printf("\t\t\t\t\t请输入要修改的节点位置:");
						int aw;
						scanf("%d",&aw);
						printf("\t\t\t\t\t请输入修改后的值:");
						int count;
						scanf("%d",&count);
					L1=	ListModify(L1,aw,count);
							
					}
					else{
						printf("\t\t\t\t\t请输入要修改的节点位置:");
						int aw;
						scanf("%d",&aw);
						printf("\t\t\t\t\t请输入修改后的值:");
						int count;
						scanf("%d",&count);
					L2=	ListModify(L2,aw,count);						
	
					}
					break;
					
				}

			case 5:
				{
					printf("\t\t\t\t\t链表1：");
					DisPlay(L1);
					printf("\t\t\t\t\t链表2：");
					DisPlay(L2);
					printf("\n\t\t\t\t\t打印交叉合并后的链表：\n");
					printf("\t\t\t\t\t");
					
					if(long1>=long2){
						
						L3 = ListUnion(L1,L2,L3);
						DisPlay(L3);				
					}
					else{
						L3 = ListUnion(L2,L1,L3);

						DisPlay(L3);
					}	
					break;
				}
				
			case 6:
					printf("\t\t\t\t\t排序输出：");
					L4 = ListSort(L3);
					DisPlay(L4);
					printf("\n");
					break;
			case 7:
				{
					printf("\t\t\t\t\t选择要初始化的链表(1--L1,2--L2)");
					int n;
					scanf("%d",&n);
					if(n==1){
						L1=ListInitiate(L1);				//链表1的初始化
						printf("\t\t\t\t\t链表1初始化完成\n");	
					}
					else{
						L2=ListInitiate(L2);				//链表2的初始化
						printf("\t\t\t\t\t链表2初始化完成\n");	
					}
									
					L3=ListInitiate(L3);					//默认链表3,4初始化
					L4=ListInitiate(L4);
					
					break;
				}
			case 8:
				{
					printf("\t\t\t\t\t选择要打印的链表(L1,L2,L3,L4)：");
					int l;
					scanf("%d",&l);
					printf("\t\t\t\t\t");
					switch (l) {
						case 1:
								DisPlay(L1);
							break;
						case 2:
								DisPlay(L2);	
							break;
						case 3:
								DisPlay(L3);
							break;
						case 4:
								DisPlay(L4);
							break;
					}
						
					break;
				}
			case 9:
					exit(0);	
					break;			
						
		}
			system("pause");
			system("CLS");
			Menu();
			scanf("%d",&choice);
	}

	return 0;
}
