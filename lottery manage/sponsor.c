#include"lottery.h"

//发行方登录
int sponsor_login(sponsor_t* sponsor){
	char account[20] = {0};
	char pswd[50] = {0};
	printf("登录账号:");
	getstring(account,20);
	
	if(strcmp(sponsor->account,account)!=0){
		printf("账号错误，登录失败！\n");
		return 0;
	}
	
	printf("登录密码:");
	getpswd(pswd);
	if(strcmp(sponsor->pswd,pswd)!=0){
		printf("密码错误，登录失败！\n");	//若不换行，光标停在该行，调用清屏函数后，改行不会被清掉
		return 0;
	}
	
	printf("登录成功\n");
	return 1;
}

//发行方界面
char sponsor_interface(sponsorLottery_t* head2,customer_t* head){
	while(1){
		char ch = 0;
		printf("\t      中国福利彩票\n");
		printf("---------------发行方界面-------------------\n");
		printf("1.发行彩票\t\t2.查询彩民信息\n");
		printf("3.排序\n");
		printf("\n");
		printf("0:返回到首页\n");
		printf("q:退出程序\n");
		printf("--------------------------------------------\n");
		
		printf("请选择:");
		while(1){
			ch = getch();
			if((ch>='0' && ch<='3') || ch=='q'){
				break;
			}
		}
		
		switch(ch){
			case '1':
				system("clear");
				issue_lottery(head,head2);
				save_sponsorLottery(head2);
				save_customer(head);
				sleep(1);
				system("clear");
				break;
			case '2':
				system("clear");
				check_customer(head);
				break;
			case '3':
				system("clear");
				bubble_sort(head);
				break;
			case '0':
				system("clear");
				return '0';
			case 'q':
				system("clear");
				return 'q';
			default:
				system("clear");
				break;
			
		}
	}
}

//发行彩票
void issue_lottery(customer_t* head,sponsorLottery_t* head2){
	sponsorLottery_t* tail = head2->pre;//找到尾节点---上一期彩票
	
	//已开奖，发行新一期的彩票
	if(tail->data.openingStatus==1){
		sponsorLottery_t* new = malloc(sizeof(sponsorLottery_t));
		memset(new,0,sizeof(sponsorLottery_t));
		
		new->data.price = 2;
		//new->data.openingStatus = 1;
		//static int date = 2019001;//2019年可有999期，??自动生成 ???要从文件中加载一下吗
		int date = tail->data.date + 1;
		new->data.date = date;
		new->data.totalBonus = tail->data.totalBonus;//上一期未发完的奖金，累加到下一期的奖池中 
		//date++;
		
		tail->next = new;
		new->next = head2;
		head2->pre = new;
		new->pre = tail;
		
		//发行新一期彩票后，客户链表更新
		customer_t* p1 = head->next;
		while(p1!=head){	//对所有客户的一二三等奖中奖的注数重置为0，以使其保存最新一期的中奖情况
			for(int i=0;i<3;i++){
				p1->data.prizeStatus[i] = 0;
			}
		
			p1 = p1->next;
		}
		
		printf("成功发行%d期彩票\n",date);
	}else{
		printf("上一期彩票未开奖,发行失败！\n");
	}
	
}

//查询彩民信息
void check_customer(customer_t* head){
	int min = 0,max = 0;
	printf("请输入要查询的账户余额区间\n");
	printf("最小值:");
	scanf("%d",&min);
	while(getchar()!=10);
	printf("最大值:");
	scanf("%d",&max);
	while(getchar()!=10);
	
	printf("\n查询结果:\n");
	customer_t* p = head->next;
	while(p!=head){
		if(p->data.balance >= min && p->data.balance <=max){
			printf("账户:%s\t\t余额:%g\n",p->data.account,p->data.balance);//?打印格式对不齐
		}
		p = p->next;
	}
	
	go_back();
}

//排序
void bubble_sort(customer_t* head){
	customer_t* p = head->next;
	customer_t* q = head->next;
	data_t temp = {0};
	
	while(p->next!=head){
		q = head->next;
		while(q->next!=head){
			if((q->data.balance) > (q->next->data.balance)){
				temp = q->data;
				q->data = q->next->data;
				q->next->data = temp;
			}
			q = q->next;
		}
		p = p->next;
	}
	
	printf("根据彩民账户余额升序排列,结果:\n");
	print_customer(head);
	go_back();
}
void print_customer(customer_t* head){
	customer_t* p = head->next;
	while(p!=head){
		printf("账号:%s\t余额:%g\n",p->data.account,p->data.balance);
		p = p->next;
	}
}






