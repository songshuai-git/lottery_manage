#include"lottery.h"
              
//进入客户注册登录界面
char customer_entrance(customer_t* head,sponsorLottery_t* head2,customerLottery_t* head3){
	while(1){
		char ch = 0;
		printf("\t      中国福利彩票\n");
		printf("-----------------客户入口------------------\n");
		printf("1.客户注册\n");
		printf("2.客户登录\n\n");
		printf("0:返回首页\n");
		printf("q:退出程序\n");
		printf("-------------------------------------------\n");
	
		printf("请选择:");
		while(1){
			ch = getch();
			if((ch>='0' && ch<='2') || ch=='q'){
				break;
			}
		}
	
		switch(ch){
			case '1':
				system("clear");
				customer_regist(head);
				break;
			case '2':{
				system("clear");
				customer_t* pos = customer_login(head);
				if(pos==head){
					sleep(1);
					system("clear");
				}else if(pos!=head){
					printf("登录成功\n");
					sleep(1);
					system("clear");
					
					char res = customer_interface(pos,head,head2,head3);
					if(res==27){	//界面返回
					}else if(res=='0'){	
						return '0';
					}else if(res=='q'){
						return 'q';
					}
				}
				break;
			}
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

/*链表的基本运算函数实现*/
//查
customer_t* find_account(customer_t* head,char* account){
	customer_t* p = head->next;
	while(p!=head){
		if(strcmp(p->data.account,account)==0){
			return p;
		}
		p = p->next;
	}
	return head;
}
//增，客户注册
void customer_regist(customer_t* head){
	char account[20] = {0};
	char pswd[20] = {0};
	char pswd2[20] = {0};
	
	printf("注册账号:");
	getstring(account,20);
	
	customer_t* pos = find_account(head,account);
	if(pos!=head){
		printf("注册失败,此账号已存在！\n");
		sleep(1);
		system("clear");
		return;
	}
	
	printf("设置密码:");
	getstring(pswd,20);
	printf("确认密码:");
	getstring(pswd2,20);
	
	if(strcmp(pswd,pswd2)!=0){
		printf("两次输入的密码不一致，注册失败！\n");
		sleep(1);
		system("clear");
		return;
	}
	
	customer_t* newCustomer = malloc(sizeof(customer_t));
	memset(newCustomer,0,sizeof(customer_t));
	
	strcpy(newCustomer->data.account,account);
	strcpy(newCustomer->data.pswd,pswd);
	
	customer_t* p = head->pre;
	
	p->next = newCustomer;
	newCustomer->next = head;
	head->pre = newCustomer;
	newCustomer->pre = p;
	
	printf("注册成功\n");
	save_customer(head);
	
	sleep(1);
	system("clear");
}
//查，客户登录
customer_t* customer_login(customer_t* head){
	char account[20] = {0};
	char pswd[50] = {0};
	int i = 0;
	customer_t* pos = NULL;
	
	for(i = 1;i<=3;i++){
		printf("登录账号:");
		getstring(account,20);
		
		pos = find_account(head,account);
		if(pos!=head){
			break;
		}else{
			printf("该账号不存在！\n");
		}
	}
	if(i==4){
		return head;
	}
	
	for(i=1;i<=3;i++){	
		if(i==3){
			for(int i=1;i<=2;i++){
				char code[5] = {0};
				char code2[10] = {0};
				get_idenCode(code);
				printf("验  证  码  :%s\n",code);
				printf("请输入验证码:");
				getstring(code2,10);
				//while(getchar()!=10);//!!! getstring清缓存并不合适,因为大多数情况下它会吸收回车，那么运行到while要再输入一次回车才能跳出循环。所以为了避免多输入的数据存在缓存中的影响，而又不能清缓存，只能把数组定义的大些
			
				if(strcmp(code,code2)==0){
					break;
				}else{
					printf("输入的验证码有误！\n");
				}
				if(i==2){
					printf("\n登录失败！\n");
					return head;
				}
			}
		}
		
		printf("登录密码:");
		getpswd(pswd);
		if(strcmp(pos->data.pswd,pswd)==0){
			return pos;
		}else{
			printf("密码错误！\n");
		}
	}
	if(i==4){
		printf("\n登录失败！\n");
		return head;
	}
	
	return head;//w?
}

//进入客户界面
char customer_interface(customer_t* pos,customer_t* head,sponsorLottery_t* head2,customerLottery_t* head3){	//界面的返回值改为int型，可以利用其返回到多级界面
	while(1){
		char ch = 0;
		printf("\t     中国福利彩票\n");
		printf("---------------客户界面-------------------\n");
		printf("1.查看账户\t\t2.修改密码\n");
		printf("3.账户充值\t\t4.购买彩票\n");
		printf("5.注销账户\t\t6.查看历史记录\n");
		printf("7.小 游 戏\n\n");
		printf("0    :\t返回到首页\n");
		printf("Esc键:\t返回到上一页\n");
		printf("q    :\t退出程序\n");
		printf("------------------------------------------\n");
		
		printf("请选择:");
		while(1){
		ch = getch();
		if((ch>='0' && ch<='7') || ch=='q' || ch==27){
			break;
		}
	}
		
		switch(ch){
			case '1':
				system("clear");
				check_account(pos);
				break;
			case '2':
				system("clear");
				change_pswd(pos);
				save_customer(head);//保存客户链表
				sleep(1);
				system("clear");
				break;
			case '3':
				system("clear");
				charge_account(pos);
				save_customer(head);//保存客户链表
				sleep(1);
				system("clear");
				break;
			case '4':
				system("clear");
				buy_lottery(pos,head2,head3);
				//三张链表发生更新，保存三张链表
				save_customer(head);
				save_sponsorLottery(head2);
				save_customerLottery(head3);
				
				system("clear");
				break;
			case '5':{
				system("clear");
				int res = remove_account(pos,head3);
				save_customer(head);//保存客户链表
				save_customerLottery(head3);
				sleep(1);
				system("clear");
				
				if(res==1){
					return 27;
				}
				break;
			}
			case '6':
				system("clear");
				check_history(pos,head3);
				break;
			case '7':
				system("clear");
				game();
				system("clear");
				break;
			case '0':
				system("clear");
				return '0';
			case 'q':
				system("clear");
				return 'q';
			case 27:
				system("clear");
				return 27;
			default:
				system("clear");
				break;
		}	
	}
}
//查看信息
void check_account(customer_t* pos){
	printf("账号: %s\n",pos->data.account);
	printf("密码: %s\n",pos->data.pswd);
	printf("余额: %g\n",pos->data.balance);
	
	go_back();
}
//修改密码
void change_pswd(customer_t* pos){
	char Pswd[20] = {0};
	char Pswd2[20] = {0};
	int i = 0;
	
	printf("旧密码:");
	getstring(Pswd,20);
	if(strcmp(pos->data.pswd,Pswd)!=0){
		printf("密码错误\n请重新输入密码:");
		getstring(Pswd,20);
		if(strcmp(pos->data.pswd,Pswd)!=0){	//旧密码两次输入错误，退出
			printf("密码错误,修改失败！\n");
			return;
		}
	}

	printf("设置新密码:");
	getstring(Pswd,20);
	for(i=1;i<=3;i++){
		printf("确认新密码:");
		getstring(Pswd2,20);
		if(strcmp(Pswd,Pswd2)==0){
			break;
		}else{
			printf("两次输入的密码不一致\n");
		}
	}
	if(i==4){
		printf("\n修改失败！\n");
		return;
	}
	
	strcpy(pos->data.pswd,Pswd);
	printf("密码修改成功\n");
	return;
	
}
//账户充值
void charge_account(customer_t* pos){
	float num = 0;
	
	printf("请输入要充值的金额:");
	scanf("%f",&num);
	while(getchar()!=10);
	
	if(num<0){
		printf("充值金额不能为负值,充值失败！\n");
		return;
	}
	
	pos->data.balance += num;
	printf("已充值成功\n");
}
//账户注销
int remove_account(customer_t* pos,customerLottery_t* head3){
	char ch = 0;
	printf("确定要注销账户吗(y/n)\n");
	while(1){
		ch = getch();
		if(ch=='y' || ch=='n'){
			break;
		}
	}
	if(ch=='n'){
		printf("注销失败！\n");
		return 0;
	}
	
	//该用户购买的彩票从购买彩票链表中删除	法二:这是成片的删除,也可以用p->next来遍历，free(p->pre),最后释放p
	customerLottery_t* p3 = head3->next;
	while(p3!=head3){
		if(strcmp(pos->data.account,p3->data.customerAccount)==0){
			p3->pre->next = p3->next;
			p3->next->pre = p3->pre;
			
			//free(p3);	//×！！！valgrind运行出错(error summary中)
			customerLottery_t* p4 = p3;//√ 解:不能直接释放p3,因为如果释放了p3,p3指向的空间被释放掉，这块内存空间交还给系统，但此时的指针一般称之为野指针(可能还指向这块内存空间，这块内存空间上的内容也可能还没有改变，但是他是不稳定的)，是很危险的。
			p3 = p3->next;//p3和p4指向同一个内存空间,若释放掉了p4,p3同样会变为野指针，所以要在它变为野指针之前让它指向链表的下一个节点。
			free(p4);	
		}else{
			p3 = p3->next;
		}
	}
	
	//将该用户从客户链表上删除
	pos->pre->next = pos->next;
	pos->next->pre = pos->pre;
	free(pos);
	//pos=NULL;	//在被调用函数里，函数结束就被释放了，不需要在置空。
	
	printf("注销成功！\n");
	return 1;
}
//查看历史记录
void check_history(customer_t* pos,customerLottery_t* head3){
	customerLottery_t* p3 = head3->next;
	while(p3!=head3){
		if(strcmp(pos->data.account,p3->data.customerAccount)==0){
			printf("***************************************\n");
			printf("期    号:%d\n",p3->data.date);
			printf("序    号:%d\n",p3->data.id);
			printf("购 买 者:%s\n",p3->data.customerAccount);
			printf("注    数:%d\n",p3->data.number);
			printf("中奖状态:%d\n",p3->data.winningStatus);
			printf("中奖金额:%d\n",p3->data.winningBonus);
			printf("彩票号码:\n");
			int i = 0,j = 0;
			char letter = 'A';
			for(i=0;i<5;i++){
				printf("%c>",letter);
				for(j=0;j<5;j++){
					printf("%3d",p3->data.betNum[i][j]);
				}
				letter++;
				printf("\n");
			}
		
			}
			p3 = p3->next;
	}
	printf("***************************************\n");
	go_back();
}

//购买彩票
void buy_lottery(customer_t* pos,sponsorLottery_t* head2,customerLottery_t* head3){
	sponsorLottery_t* pos2 = head2->pre;
	if(pos2->data.openingStatus==1){
		printf("本期彩票已开奖，下期彩票还未发行\n无法进行购买！\n");
		sleep(2);
		return;
	}
	
	char ch = 0;
	printf("1.单次购买(一次买一张彩票)\n");	//！不需要while(1)死循环
	printf("2.批量购买(一次可以买多张彩票)\n");
	printf("0.退出\n");
	printf("请选择:");
	printf("\n\n");
	while(1){
		ch = getch();
		if(ch>='0' && ch<='2'){
			break;
		}
	}
	switch(ch){
		case '1':
			single_purchase(pos,pos2,head3);
			break;
		case '2':
			bulk_purchase(pos,pos2,head3);
			break;
		case '0':
			return;
		default:
			break;
	}

}

//单次购买
void single_purchase(customer_t* pos,sponsorLottery_t* pos2,customerLottery_t* head3){
	int number = 0;	//每张彩票的注数
	printf("请输入购买的注数(最多5注):");
	while(1){
		number = getch() - '0';
		if(number>=1 && number<=5){
			break;
		}
	}
	printf("%d\n\n",number);
	
	//余额不足，提示充值
	while(1){
		if(pos->data.balance >= (number * pos2->data.price)){
			break;
		}else{
			printf("账号余额不足，是够充值？(y/n)\n");
			char ch = 0;
			while(1){
				ch = getch();
				if(ch=='y' || ch=='n'){
					break;
				}
			}
			if(ch=='y'){
				charge_account(pos);
				printf("\n");
			}else{
				printf("\n购买彩票失败！\n");
				sleep(1);
				return;
			}
		}
	}
	
	char ch = 0;
	printf("1.彩票号码机选\n");
	printf("2.彩票号码手选\n");
	printf("0.退出\n");
	printf("请选择:\n\n");
	while(1){
		ch = getch();
		if(ch>='0' && ch<='2'){
			break;
		}
	}
	
	if(ch=='0'){return;}
	
	once_buy(pos,pos2,head3,number,ch);
	printf("已成功购买彩票\n");
	sleep(1);
}

//批量购买 ??重复性高，是否可以调用多次单次购买，或者用回调函数简化呢
void bulk_purchase(customer_t* pos,sponsorLottery_t* pos2,customerLottery_t* head3){
	int number = 0;	//彩票张数
	while(1){
		printf("请输入购买的彩票的张数:");
		scanf("%d",&number);
		while(getchar()!=10);
		printf("\n");
		if(number>=1){
			break;
		}else{
			printf("购买的张数不能小于一张,请重新输入\n");
		}
	}
	
	//余额不足，提示充值
	while(1){
		if(pos->data.balance >= (number * 10)){
			break;
		}else{
			printf("账号余额不足，是够充值？(y/n)\n");
			char ch = 0;
			while(1){
				ch = getch();
				if(ch=='y' || ch=='n'){
					break;
				}
			}
			if(ch=='y'){
				charge_account(pos);
				printf("\n");
			}else{
				printf("\n购买彩票失败！\n");
				sleep(1);
				return;
			}
		}
	}
	
	char ch = 0;
	printf("1.彩票号码机选\n");
	printf("2.彩票号码手选\n");
	printf("0.退出\n");
	printf("请选择:\n\n");
	while(1){
		ch = getch();
		if(ch>='0' && ch<='2'){
			break;
		}
	}
	
	if(ch=='0'){return;}

	for(int i=0;i<number;i++){	
		printf("第%d张彩票\n",i+1);
		once_buy(pos,pos2,head3,5,ch);
	}
	
	printf("已成功购买彩票\n");
	sleep(2);
}

//购买彩票链表增加一个节点
void once_buy(customer_t* pos,sponsorLottery_t* pos2,customerLottery_t* head3,int number,int ch){
	customerLottery_t* new = malloc(sizeof(customerLottery_t));
	memset(new,0,sizeof(customerLottery_t));
		
	/*对数据区赋值*/
	//彩票号码 回调函数
	if(ch=='1'){
		choose_way(number,new,machine_choose);
	}else if(ch=='2'){
		choose_way(number,new,customer_choose);
	}
	new->data.date = pos2->data.date;//彩票期号
	//new->data.id = ++(head3->pre->data.id);//×× 自身的id会改变
	strcpy(new->data.customerAccount,pos->data.account);//购买者帐号
	new->data.number = number;//注数
	//中奖状态 中奖金额
		
	customerLottery_t* p = head3->pre;
	//彩票序号
	int date = p->data.id + 1;
	new->data.id = date;
			
	p->next = new;
	new->next = head3;
	head3->pre = new;
	new->pre = p;
		
	//期号彩票链表变化
	pos2->data.saleNum += number;	//售出总数
	pos2->data.totalBonus += number*(pos2->data.price);	//本期奖池总额
		
	pos->data.balance -= number*(pos2->data.price);	//客户余额减少
}

void machine_choose(int number,customerLottery_t* new){
	int i = 0,j = 0;
		for(i=0;i<number;i++){	
			for(j=0;j<5;j++){	  //如一注:1 2 1 3 5
				new->data.betNum[i][j] = rand()%10+1;//1~10
			}
		}
}
void customer_choose(int number,customerLottery_t* new){
	int i = 0,j = 0;
	printf("请输入每一注的彩票号码(1~10)\n");
		for(i=0;i<number;i++){	
			printf("第%d注:",i+1);
			for(j=0;j<5;j++){	  //如一注:1 19 4 30 8
				scanf( "%d",&(new->data.betNum[i][j]) );
				if(new->data.betNum[i][j] <=0 || new->data.betNum[i][j] >10){
					printf("彩票号码为1~10之间，请重新下注\n");
					i--;
					break;
				}	
			}
			while(getchar()!=10);
		}
	printf("\n");
}
void choose_way(int number,customerLottery_t* new,chooseWay_t p){
	p(number,new);
}







