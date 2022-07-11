#include<stdio.h>
#include<malloc.h>
#include<windows.h>

/*���ݽṹ*/
typedef struct LNode {
	int data;					//������
	struct LNode *next; 		//ָ����
}LNode,*LinkList;

int flag;

/*��������*/
LinkList ListCreat_1(LNode *L);				    	//��������
LinkList ListCreat_2(int len);						//����ָ��Ԫ�ش���		
LinkList ListInitiate(LinkList head);				//�����ʼ��
LinkList ListInsert(LinkList head,int i,int x);		//Ԫ�ز���
LinkList ListDelete(LinkList head,int i);			//�ڵ�ɾ��
LinkList ListModify(LNode* head,int index, int data);//Ԫ���޸�
int Linklength(LinkList L);							//��ȡ������
LinkList ListSort(LinkList head);					//����
LinkList ListUnion(LNode * L1,LNode * L2,LNode *L3);//�ϲ�
void DisPlay(LNode *L);								//��ӡ
void Save(LinkList L,int flag);						//�����ϴ�
LinkList Loadin_A(LNode*L);							//A�ļ�����
LinkList Loadin_B(LNode*L);							//B���ļ���

LinkList Loadin_A(LNode*L){
	L = (LinkList)malloc(sizeof(LNode));	//ͷ�ڵ�
	LNode *p,*r = L;	
		FILE *fp = fopen("A.txt","r");
		int data;

	while(fscanf(fp,"%d",&data)!=EOF){
		p = (LinkList)malloc(sizeof(LNode));			//�����½ڵ�p
		p->data=data;									//��ֵ��p��data��
													
		p->next=NULL;								
		r->next=p;								    	//p�ڵ���뵽β�ڵ�r��	
		r=p;											//rָ����β�ڵ�
	}	
	fclose(fp);
		flag=1;
		Save(L,flag);
	return L;	
}
LinkList Loadin_B(LNode*L){
	L = (LinkList)malloc(sizeof(LNode));	//ͷ�ڵ�
	LNode *p,*r = L;	
		FILE *fp = fopen("B.txt","r");
		int data;

	while(fscanf(fp,"%d",&data)!=EOF){
		p = (LinkList)malloc(sizeof(LNode));			//�����½ڵ�p
		p->data=data;									//��ֵ��p��data��									
		p->next=NULL;								
		r->next=p;								    	//p�ڵ���뵽β�ڵ�r��	
		r=p;											//rָ����β�ڵ�
	}	
	fclose(fp);
	flag=1;
	Save(L,flag);
	return L;	
}
void Save(LinkList L,int flag){
	FILE* fp = fopen("nlist.txt", "a");
	if (fp == NULL){
		printf("\t\t\t\t\t�򿪴浵�ļ�ʧ�ܣ�\n");
		return ;
	}
	L=L->next;
	
	switch (flag) {
		case 1:{char s[20]="������:";fprintf(fp,"%s",s);break;}
		case 2:{char s[20]="�ڵ����:";fprintf(fp,"%s",s);break;}
		case 3:{char s[20]="�ڵ�ɾ��:";fprintf(fp,"%s",s);break;}
		case 4:{char s[20]="�ڵ��޸�:";fprintf(fp,"%s",s);break;}
		case 5:{char s[20]="����ϲ�:";fprintf(fp,"%s",s);break;}
		case 6:{char s[20]="�������:";fprintf(fp,"%s",s);break;}
		case 7:{char s[20]="��ʼ��";fprintf(fp,"%s",s);break;}
		case 8:{char s[20]="��ӡ:";fprintf(fp,"%s",s);break;}
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

LinkList ListCreat_1(LNode *L){ //��������
	printf("\t\t\t\t\t���ڽ����������������ݣ�-1��������\n\t\t\t\t\t");
	L=(LinkList)malloc(sizeof(LNode));	
	LNode *s,*r;
	r=L;
	int t;
	scanf("%d",&t);
	while(t!=-1) {
		s=(LinkList)malloc(sizeof(LNode));	//�½ڵ�
		s->data=t;							//��ֵ
		r->next=s;							//����
		r=s;								//����ָ�����
		scanf("%d",&t);
	}
	r->next=NULL;
		flag=1;
	Save(L,flag);
	
	return L;
}

LinkList ListCreat_2(int len){	//�̶�Ԫ�ش���
	
	printf("\t\t\t\t\t���ڽ�������");
	LNode *head = (LinkList)malloc(sizeof(LNode));	//ͷ�ڵ�
	LNode *p,*r = head;	
	int x;
	for(int i = 0;i < len;i++){
		p = (LinkList)malloc(sizeof(LNode));			//�����½ڵ�p
		scanf("%d",&x);									//����Ԫ��ֵ
		p->data=x;									//x��ֵ��p��data��
		p->next=NULL;								
		r->next=p;									//p�ڵ���뵽β�ڵ�r��	
		r=p;											//rָ����β�ڵ�
	}
	flag=1;
	
	Save(head,flag);
	
	
	return head;
}

LinkList ListInitiate(LinkList head){			//��ʼ��
	
	head = (LinkList)malloc(sizeof(LNode));	
	head->next = NULL;
	flag=7;
	
	Save(head,flag);							//ͷ�ڵ�ָ����ָ��
	return head;
}
LinkList ListInsert(LinkList head,int i,int x){	 //iΪ�����λ�ã�xΪ����Ԫ�ص�ֵ
	LNode *p,*q;
	int j = 0;
	p = head;
	/*���ҵ�i-1���ڵ�*/
	while(p->next != NULL && j < i-1){			//pָ��i-1�ڵ�		
		p = p->next;
		j++;
	}
	q = (LinkList)malloc(sizeof(LNode));		//�����µĽڵ�
	q->data = x;								//data����x
	q->next = p->next;							//�½ڵ�naxt��ָ��ai
	p->next = q;								//p��next��ָ���½ڵ�
	printf("\t\t\t\t\t�������\n");
	flag=2;
	Save(head,flag);
	
	return head;
	
}

LinkList ListDelete(LinkList head,int i){
	LNode *p,*q;
	
	int j = 0;
	p = head;
	/*���ҵ�i-1���ڵ�*/
	while(p->next != NULL && j < i-1){			//pָ��i-1�ڵ�
		p = p->next;
		j++;
	}
	q = p->next;								//qָ��Ҫ��ɾ���Ľڵ�
	p->next = p->next->next; 					//��i-1�ڵ��nextΪi+1�ڵ�
	free(q);									//�ͷ�
	printf("\t\t\t\t\tɾ�����\n");
	flag=3;
	Save(head,flag);
	
	return head;
}
int Linklength(LinkList L)//��������
{
    int k=0;
    while(L!=NULL)
    { 
        k++;					//������1
        L=L->next;				//ָ����һ�ڵ�
    }
    return k;
}

LinkList ListModify(LNode* head,int index, int data)//Ԫ���޸�
{
	
    if(head == NULL || index < 0)		//�����ж�
        return head;
        
    LNode* node = head;
    for (int i = 0; i < index; ++i)		//ѭ��������ڵ�
    {
        if (node == NULL)				//��ѡ�ڵ㳬��ʵ�ʷ�Χ
            return head;
        node = node->next;	//ָ�����
    }
    node->data =  data;		//data��ֵ
    flag=4;
    Save(head,flag);
    return head;
    
}

LinkList ListSort(LinkList head){
		
	LinkList p,pre,q;
	p = head->next->next;		  
	head->next->next = NULL;	// ���ֻ��һ��Ԫ�ص������
								
	while(p != NULL){		
		q = p->next;	//��Ϊp�����룬��
		pre = head;	
		while(pre->next !=NULL && pre->next->data < p->data) // ����pre��ָ��������ֱ���ҵ���p��Ľڵ�
			pre = pre->next; 	
		p->next = pre->next;	//p��next��pre��next�ڵ�����
		pre->next = p;			//ǰ������
		p = q;	
	} 
	flag=6;
	Save(head,flag);
	
	return head;
	
}


void DisPlay(LNode *L) {		//��ӡ����
	LNode *p=L->next;			//ָ����Ԫ�ڵ�	
	while(p!=NULL) {
		printf ("%d ",p->data);	//��ӡ
		p=p->next;				//ָ�����
	}
	printf("\n");
}
LinkList ListUnion(LNode *l1,LNode *l2,LNode *l3){
	LinkList p,q,r,s;				    //����ָ��
	l3=(LinkList)malloc(sizeof(LNode)); //L3ͷ�ڵ�
	p=l1->next;
	q=l2->next;
	r=l3;

	while(p&&q){
		s=(LinkList)malloc(sizeof(LNode));	//β�巨
		s->data=p->data;					//��ֵ
		r->next=s;							//����
			r=s;							//����
		p=p->next;							//������������ָ�����
		
		s=(LinkList)malloc(sizeof(LNode));	//β�巨
		s->data=q->data;
		r->next=s;
			r=s;
		q=q->next;
	}
		r->next=NULL;						//βָ���ÿ�
		
	if (p) {								//p֮����Ԫ��
		while(p){
		s=(LinkList)malloc(sizeof(LNode));	//β��
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
	printf("\t\t\t\t\t�X�����������������������������������[\n");
	printf("\t\t\t\t\tح               �˵�              ح\n");
	printf("\t\t\t\t\tح         ��1����������           ح\n");
	printf("\t\t\t\t\tح         ��2���ڵ����           ح\n");	
	printf("\t\t\t\t\tح         ��3���ڵ�ɾ��           ح\n");
	printf("\t\t\t\t\tح         ��4���ڵ��޸�           ح\n");
	printf("\t\t\t\t\tح         ��5������ϲ�           ح\n");
	printf("\t\t\t\t\tح         ��6���������           ح\n");
	printf("\t\t\t\t\tح         ��7����ʼ��             ح\n");
	printf("\t\t\t\t\tح         ��8����ӡ               ح\n");
	printf("\t\t\t\t\tح         ��9���˳�               ح\n");
	printf("\t\t\t\t\t�^�����������������������������������a\n");
	printf("\t\t\t\t\t����������ѡ��:");	
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
					printf("\t\t\t\t\tѡ�񴴽���ʽ(1-������2-�ض�Ԫ����Ŀ������3-�ļ�����)");
					int choic_;
					scanf("%d",&choic_);
					if(choic_==1){
						printf("\t\t\t\t\t�Ƿ���δ�����1--�ǣ�0--��");
						int n1;
						scanf("%d",&n1);
						if(n1==1){
							L1=ListCreat_1(L1);			//��������1
								printf("\t\t\t\t\t����1�Ѿ�����\n");
								long1 = Linklength(L1);	//����1����		
								
							L2=ListCreat_1(L2);			//��������2
								printf("\t\t\t\t\t����2�Ѿ�����\n");
								long2 = Linklength(L2);	//����2����								
						}
						
						else if(n1==0){
							printf("\t\t\t\t\tѡ��Ҫ����������1--L1��2--L2��");
							int xx;
							scanf("%d",&xx);
							if(xx==1){ 
								L1=ListCreat_1(L1);	//��������1
								printf("\t\t\t\t\t����1�Ѿ�����\n");
								long1 = Linklength(L1);	//����1����		
							}
							else{	
							L2=ListCreat_1(L2);   	//��������2
								printf("\t\t\t\t\t����2�Ѿ�����\n");
								long2 = Linklength(L2);	//����2����								
							}
							
						}						
					}
					else if(choic_==2){
						printf("\t\t\t\t\t�Ƿ���δ�����1--�ǣ�0--��");
						int d1;
						scanf("%d",&d1);
						if(d1==1){
							printf("\t\t\t\t\t����������1Ԫ�ظ���:");
							int m;
							scanf("%d",&m);
							L1=ListCreat_2(m);	//��������1
							long1 = Linklength(L1);	
							printf("\t\t\t\t\t����1�Ѿ�����\n");
							
								
							printf("\t\t\t\t\t����������2Ԫ�ظ���:");
							int n;
							scanf("%d",&n);	
							L2=ListCreat_2(n);	//��������2
							long2 = Linklength(L2);	//����2����	
							printf("\t\t\t\t\t����2�Ѿ�����\n");
														
				
						}
						
						else if(d1==0){
							printf("\t\t\t\t\tѡ��Ҫ����������1--L1��2--L2��");
							int m;
							scanf("%d",&m);
							
							if(m==1){
								printf("\t\t\t\t\t����������1Ԫ�ظ���:");
								int m;
								scanf("%d",&m);
								L1=ListCreat_2(m);	//��������1
								printf("\t\t\t\t\t����1�Ѿ�����\n");
								long1 = Linklength(L1);	//����1����		
							}		
							else{		
								printf("\t\t\t\t\t����������2Ԫ�ظ���:");
								int n;
								scanf("%d",&n);	
								L2=ListCreat_2(n);   	//��������2
								printf("\t\t\t\t\t����2�Ѿ�����\n");
								long2 = Linklength(L2);	//��������2����								
							}	
						}					
					}	
					else{
						L1=Loadin_A(L1);
						long1 = Linklength(L1);//���ȸ���
						L2=Loadin_B(L2);
						long2 = Linklength(L2);//���ȸ���
						printf("\t\t\t\t\t���ݵ�����ɣ�\n");
					}
					break;
				}
			case 2:
				{
					printf("\n\t\t\t\t\tѡ��Ҫ���������1--L1��2--L2��");
					int n,i,x;
					
					scanf("%d",&n);
					if(n==1){
						printf("\n\t\t\t\t\t����������λ�ü�Ԫ�أ�");
				
						scanf("%d%d",&i,&x);
						L1=ListInsert(L1,i,x);
						long1 = Linklength(L1);		//����������			
					}
					else{
						printf("\n\t\t\t\t\t����������λ�ü�Ԫ�أ�");
					
						scanf("%d%d",&i,&x);	
				    	L2=ListInsert(L2,i,x);	
						long2 = Linklength(L2);		//����������			
					}
	
					break;
				}
			case 3:
				{
					printf("\t\t\t\t\tѡ��Ҫ����ɾ��������1--L1��2--L2��");
					int n;
					scanf("%d",&n);
					if(n==1){
						printf("\t\t\t\t\t������Ҫɾ���Ľڵ㣺");
						int a;
				     	scanf("%d",&a);
				   	L1=ListDelete(L1,a);	
					   long1 = Linklength(L1);	
					}
					else{
						printf("\t\t\t\t\t������Ҫɾ���Ľڵ㣺");
						int a;
						scanf("%d",&a);
					 L2=ListDelete(L2,a);
					 	long2 = Linklength(L2);					
					}
						
				break;
				}
				
			case 4:
				{
			    	printf("\n\t\t\t\t\tѡ��Ҫ�޸ĵ�����1--L1��2--L2��");
			    	int a;
			    	scanf("%d",&a);
			    	if(a==1){
						printf("\t\t\t\t\t������Ҫ�޸ĵĽڵ�λ��:");
						int aw;
						scanf("%d",&aw);
						printf("\t\t\t\t\t�������޸ĺ��ֵ:");
						int count;
						scanf("%d",&count);
					L1=	ListModify(L1,aw,count);
							
					}
					else{
						printf("\t\t\t\t\t������Ҫ�޸ĵĽڵ�λ��:");
						int aw;
						scanf("%d",&aw);
						printf("\t\t\t\t\t�������޸ĺ��ֵ:");
						int count;
						scanf("%d",&count);
					L2=	ListModify(L2,aw,count);						
	
					}
					break;
					
				}

			case 5:
				{
					printf("\t\t\t\t\t����1��");
					DisPlay(L1);
					printf("\t\t\t\t\t����2��");
					DisPlay(L2);
					printf("\n\t\t\t\t\t��ӡ����ϲ��������\n");
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
					printf("\t\t\t\t\t���������");
					L4 = ListSort(L3);
					DisPlay(L4);
					printf("\n");
					break;
			case 7:
				{
					printf("\t\t\t\t\tѡ��Ҫ��ʼ��������(1--L1,2--L2)");
					int n;
					scanf("%d",&n);
					if(n==1){
						L1=ListInitiate(L1);				//����1�ĳ�ʼ��
						printf("\t\t\t\t\t����1��ʼ�����\n");	
					}
					else{
						L2=ListInitiate(L2);				//����2�ĳ�ʼ��
						printf("\t\t\t\t\t����2��ʼ�����\n");	
					}
									
					L3=ListInitiate(L3);					//Ĭ������3,4��ʼ��
					L4=ListInitiate(L4);
					
					break;
				}
			case 8:
				{
					printf("\t\t\t\t\tѡ��Ҫ��ӡ������(L1,L2,L3,L4)��");
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
