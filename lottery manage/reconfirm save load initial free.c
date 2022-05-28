#include"lottery.h"
//密码隐藏函数
void getpswd(char* pswd){
	int i = 0;
	char ch = 0;
	
	while(1){
		ch = getch();
		if(ch=='\n'){
			pswd[i] = 0;//0 '\0' NULL
			break;
		}else if((ch>=48&&ch<=57)||(ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')){
			pswd[i] = ch;
			i++;
			printf("*");
		}else if(ch==127 && i>0){
			printf("\b \b");
			i--;
		}
	}
	printf("\n");
	//printf("显示:%s\n",pswd);
}
//产生四位随机验证码
void get_idenCode(char* code){
	int temp = 0;
	for(int i=0;i<4;i++){
		temp = rand()%75+48;	//48~122
		if((temp>=48&&temp<=57) || (temp>=65&&temp<=90) || (temp>=97&&temp<=122)){
			code[i] = temp;
		}else{
			i--;
		}
	}
}

//再次确认函数
int end_program(){
	char ch = 0;
	//int res = 0;
	printf("确定要退出程序吗(y/n)\n");
	
	while(1){
		ch = getch();
		if(ch=='y' || ch=='n'){
			break;
		}
	}
	
	switch(ch){
		case 'y':{
			/*
			//保存修改
			char ch = 0;
			printf("是否要保存修改(y/n)\n");//?? 每次都由修改保存提示吗
			while(1){
				ch = getch();
				if(ch=='y' || ch=='n'){
					break;
				}
			}
			switch(ch){
				case 'y':
					save_customer(head);//保存客户链表
					break;
				case 'n':
					break;
				default:
					break;
			}	
			*/
			system("clear");
			return 1;
		}
		case 'n':
			system("clear");
			return 0;
		default:
			break;
	}
	return 0;
}
void go_back(){
	printf("\n");
	while(1){
			int ch = 0;
			//int res = 0;
			printf("是否要返回到上一页(y/n)\n");
			
			while(1){
				ch = getch();
				if(ch=='y' || ch=='n'){
					break;
				}
			}
	
			switch(ch){
				case 'y':{
					system("clear");
					return;
				}
				case 'n':
					break;
				default:
					break;
			}
	}
}

/*保存，加载，初始化，释放堆空间函数	???这部分重复性很高，是否可以用回调函数呢*/
//初始化客户链表头结点
customer_t* initail_customer(){
	customer_t* head = malloc(sizeof(customer_t));
	memset(head,0,sizeof(customer_t));
	head->pre = head;
	head->next = head;
	return head;
}
//回调函数 释放客户链表，期号彩票链表，购买彩票链表的堆空间 
void customer_type(void* head){
	customer_t* p = (customer_t*)head;
	while(p->next!=(customer_t*)head){
		p = p->next;
		free(p->pre);
	}
	free(p);
}
void sponsorLottery_type(void* head){
	sponsorLottery_t* p = (sponsorLottery_t*)head;
	while(p->next!=(sponsorLottery_t*)head){	//！释放时，用p->next来遍历会更好，最后的p单独释放，因为在while循环中还用继续用到p,不能直接释放p让他变成野指针。
		p = p->next;
		free(p->pre);	//！释放的是p的前一个节点，p不会变成野指针。
	}
	free(p);
}
void customerLottery_type(void* head){
	customerLottery_t* p = (customerLottery_t*)head;
	while(p->next!=(customerLottery_t*)head){
		p = p->next;
		free(p->pre);
	}
	free(p);
}
void free_heap(void* head,free_t p){
	p(head);
}
//保存客户信息到文件
void save_customer(customer_t* head){
	FILE* fp = fopen("./customerDB.txt","w");
	customer_t* p = head->next;
	while(p!=head){
		fwrite(&(p->data),sizeof(data_t),1,fp);
		p = p->next;
	}
	fclose(fp);
}
//加载客户信息到链表
void load_customer(customer_t* head){
	FILE* fp = fopen("./customerDB.txt","r");
	if(fp==NULL){
		printf("该文件不存在\n");
		sleep(1);
		system("clear");
		return;
	}
	customer_t* p = head->pre;
	data_t temp = {0};
	while(1){
		int res = fread(&temp,sizeof(data_t),1,fp);	//customer_t ×核心已存储
		if(res==0){
			break;
		}
		customer_t* newCustomer = malloc(sizeof(customer_t));
		memset(newCustomer,0,sizeof(customer_t));
		
		newCustomer->data = temp;
		
		p->next = newCustomer;
		newCustomer->next = head;
		head->pre = newCustomer;
		newCustomer->pre = p;
		
		p = newCustomer;
	}
	fclose(fp);
}

//加载发行方信息
void load_sponsor(sponsor_t* sponsor){
	FILE* fp = fopen("./sponsorDB.txt","r");
	if(fp==NULL){
		printf("该文件不存在\n");
		return;
	}
	
	fscanf(fp,"%s%s",sponsor->account,sponsor->pswd);
	
	fclose(fp);
}

//初始化期号彩票链表头指针
sponsorLottery_t* initail_sponsorLottery(){
	sponsorLottery_t* head = malloc(sizeof(sponsorLottery_t));
	memset(head,0,sizeof(sponsorLottery_t));
	head->next = head;
	head->pre = head;
	
	head->data.openingStatus = 1;
	//head->data.totalBonus = 5;
	head->data.date = 2019000;
	return head;//w
}
//保存期号彩票链表
void save_sponsorLottery(sponsorLottery_t* head2){
	FILE* fp = fopen("./sponsorLotteryDB.txt","w");
	sponsorLottery_t* p = head2->next;
	
	while(p!=head2){
		fwrite(&(p->data),sizeof(data2_t),1,fp);
		p = p->next;
	}
	
	fclose(fp);
}
//加载期号彩票链表
void load_sponsorLottery(sponsorLottery_t* head2){
	FILE* fp = fopen("./sponsorLotteryDB.txt","r");
	if(fp==NULL){
		return;
	}
	
	sponsorLottery_t* tail = head2->pre;
	data2_t temp = {0};
	while(1){
		int res = fread(&temp,sizeof(data2_t),1,fp);
		if(res==0){
			break;
		}
		
		sponsorLottery_t* new = malloc(sizeof(sponsorLottery_t));//彩票结构体对应彩票节点，彩票结构体数组对应彩票链表
		memset(new,0,sizeof(sponsorLottery_t));
		
		new->data = temp;
		
		tail->next = new;
		new->next = head2;
		head2->pre = new;
		new->pre = tail;
		
		tail = new;
	}
	
	fclose(fp);
}

//初始化购买彩票链表头指针
customerLottery_t* initail_customerLottery(){
	customerLottery_t* head = malloc(sizeof(customerLottery_t));
	memset(head,0,sizeof(customerLottery_t));
	head->pre = head;
	head->next = head;
	return head;
}
//加载购买彩票链表
void load_customerLottery(customerLottery_t* head3){
	FILE* fp = fopen("./customerLotteryDB.txt","r");
	if(fp==NULL){
		return;
	}
	
	customerLottery_t* tail = head3->pre;
	data3_t temp = {0};
	while(1){
		int res = fread(&temp,sizeof(data3_t),1,fp);
		if(res==0){
			break;
		}
		
		customerLottery_t* new = malloc(sizeof(customerLottery_t));
		memset(new,0,sizeof(customerLottery_t));
		
		new->data = temp;
		
		tail->next = new;
		new->next = head3;
		head3->pre = new;
		new->pre = tail;
		
		tail = new;
	}
	fclose(fp);
}
//保存购买彩票链表
void save_customerLottery(customerLottery_t* head3){
	FILE* fp = fopen("./customerLotteryDB.txt","w");
	
	customerLottery_t* p = head3->next;
	while(p!=head3){
		fwrite(&(p->data),sizeof(data3_t),1,fp);
		p = p->next;
	}
	fclose(fp);
}

//彩票管理系统 代码总共1691行

















