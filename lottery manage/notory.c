#include"lottery.h"

//公证员登录
int notory_login(){
	 char account[20] = {0};
	 char pswd[50] = {0};
	 
	 printf("登录账号:");
	 getstring(account,20);
	 if(strcmp(account,"123456")!=0){
	 	printf("账号错误，登录失败！\n");
	 	return 0;
	 }
	 
	 printf("登录密码:");
	 getpswd(pswd);
	 if(strcmp(pswd,"123456")!=0){
	 	printf("密码错误，登录失败！\n");
	 	return 0;
	 }
	 
	 printf("登录成功\n");
	 return 1;
	 
}

//公证员界面
char notory_interface(customer_t* head,sponsorLottery_t* head2,customerLottery_t* head3){
	while(1){
		char ch = 0;
		printf("\t      中国福利彩票\n");
		printf("---------------公证员界面-------------------\n");
		printf("1.开        奖\n");
		printf("2.查看彩票信息\n");
		printf("\n");
		printf("0:返回到首页\n");
		printf("q:退出程序\n");
		printf("--------------------------------------------\n");
		printf("请选择:");
		while(1){
			ch = getch();
			if((ch>='0' && ch<='2') || ch=='q'){	//w?
				break;
			}
		}
		
		switch(ch){
			case '1':
				system("clear");
				draw_lottery(head,head2,head3);
				//三张链表发生更新，保存三张链表
				save_customer(head);
				save_sponsorLottery(head2);
				save_customerLottery(head3);
				
				system("clear");
				break;
			case '2':
				system("clear");
				check_sponsorLottery(head2);
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

//开奖
void draw_lottery(customer_t* head,sponsorLottery_t* head2,customerLottery_t* head3){
	sponsorLottery_t* pos2 = head2->pre;	//当前一期彩票
	if(pos2->data.openingStatus==1){
		printf("新一期彩票尚未发行,开奖失败！\n");
		sleep(1);
		return;
	}
	
	printf("1.中奖号码机选\n");
	printf("2.中奖号码手选\n");
	printf("0.退出\n");
	char ch = 0;
	printf("请选择:\n\n");
	while(1){
		ch = getch();
		if(ch>='0' && ch<='2'){
			break;
		}
	}
	
	if(ch=='0'){return;}
	system("clear");
	if(ch=='1'){
		int i = 0,j = 0;
		int temp = 0;
		printf("中国福利彩票%d期彩票,开奖了！\n",pos2->data.date);
		printf("中奖号码:");
		fflush(stdout);
		/*
		for(i=0;i<5;i++){
			sleep(1);	//!== 开奖效果可以做成滚动显示
			pos2->data.winningNum[i] = rand()%10 + 1;	//1~10
			printf("%d  ",pos2->data.winningNum[i]);
			fflush(stdout);
		}
		sleep(1);*/
		for(i=0;i<5;i++){
			for(j=0;j<100;j++){
				temp = rand()%10 + 1;
				printf("%2d",temp);
				fflush(stdout);
				printf("\b\b  \b\b");
				usleep(30000);
			}
			printf("%d",temp);
			printf("  ");
			pos2->data.winningNum[i] = temp;
		}
		printf("\n");
	}
	if(ch=='2'){
		int i = 0;
		printf("中国福利彩票%d期彩票,开奖了！\n",pos2->data.date);
		while(1){
			int flag = 0;
			printf("请输入中奖号码(1~10):");
			for(i=0;i<5;i++){
				scanf("%d",&(pos2->data.winningNum[i]));	
				if(pos2->data.winningNum[i] <=0 || pos2->data.winningNum[i]>10){
					printf("\n中奖号码为1~10之间，请重新输入\n");
					flag = 1;
				}
			}
			while(getchar()!=10);	
			if(flag==0){
				break;
			}
		}
	}
	pos2->data.openingStatus = 1;
	//兑奖
	convert_lottery(head,pos2,head3);
	go_back();
}
//兑奖
void convert_lottery(customer_t* head,sponsorLottery_t* pos2,customerLottery_t* head3){
	customerLottery_t* p = find_this_date(pos2,head3);//购买彩票中找到该期
	
	int i = 0,j = 0;
	int count = 0;
	
	int totalBonus = pos2->data.totalBonus;	//该期彩票奖池累计值
	int firstPrize = totalBonus*(5.0/100);	//一等奖 金额:奖池的5%
	int secondPrize = totalBonus*(1.0/1000);//二等奖 金额:奖池的千分之一
	if(firstPrize<30){firstPrize = 30;}	//一等奖最少30元
	if(secondPrize<20){secondPrize = 20;}	//二等奖最少20元
	
	/*
	customer_t* pl = head->next; 
	while(pl!=head){
		pl->data.firstPrize = firstPrize;
		pl->data.secondPrize = secondPrize;
		pl = pl->next;
	}*/
	
	while(p!=head3){	//从最新一期，遍历购买彩票链表
		int betCount[5] = {0};//记录每张彩票中每一注中了几位
		for(i=0;i<(p->data.number);i++){
			count = 0;
			for(j=0;j<5;j++){
				if(p->data.betNum[i][j] == pos2->data.winningNum[j]){
					count++;	//每一注中了几位
				}
			}
			betCount[i] = count;
		}
		
		//兑奖后，三张链表的更新
		customer_t* pos = find_account(head,p->data.customerAccount);//找到该张彩票的用户
		for(i=0;i<5;i++){	//这张彩票总的中奖金额
			if(betCount[i]>=3){
				p->data.winningStatus = 1;
			}
			if(betCount[i]==5){	
				p->data.winningBonus += firstPrize;
				(pos->data.prizeStatus[0])++;	//该用户中的一等奖数+1
			}else if(betCount[i]==4){	
				p->data.winningBonus += secondPrize;
				(pos->data.prizeStatus[1])++;	//该用户中的二等奖数+1
			}else if(betCount[i]==3){	//三等奖 金额:10
				p->data.winningBonus += 10;
				(pos->data.prizeStatus[2])++;	//该用户中的三等奖数+1
			}
		}
		
		pos->data.balance += p->data.winningBonus;//将该彩票的中奖金额转给该用户
		//printf("%s中了%d奖金\n",pos->data.customerAccount,p->data.winningBonus);
		
		pos2->data.totalBonus -= p->data.winningBonus;//从该期奖池中扣除该张彩票的中奖金额
		//printf("奖池减了%d奖金,奖池还剩:%d\n",p->data.winningBonus,pos2->data.totalBonus);
		
		p = p->next;
	}
	int profit = totalBonus*(20.0/100);	//盈利 金额:奖池的20%
	if(profit<0){profit=0;}
	pos2->data.totalBonus -= profit;//从该期奖池扣除盈利
	printf("\n发行方从该期彩票中盈利:%d元\n",profit);
	printf("\n");
	
	customer_t* pl = head->next;
	printf("中国福利彩票%d期彩票,中奖结果:\n",pos2->data.date);
	printf("************************************\n");
	printf("恭喜以下彩民！\n");
	printf("一等奖(金额:%d元),中奖账号有:\n",firstPrize);
		while(pl!=head){
			if(pl->data.prizeStatus[0]>0){
				printf("    %s(%d注)\n",pl->data.account,pl->data.prizeStatus[0]);
			}
			pl = pl->next;
		}
	pl = head->next;
	printf("二等奖(金额:%d元),中奖账号有:\n",secondPrize);
		while(pl!=head){
			if(pl->data.prizeStatus[1]>0){
				printf("    %s(%d注)\n",pl->data.account,pl->data.prizeStatus[1]);
			}
			pl = pl->next;
		}
	pl = head->next;
	printf("三等奖(金额:10元),中奖账号有:\n");
		while(pl!=head){
			if(pl->data.prizeStatus[2]>0){
				printf("    %s(%d注)\n",pl->data.account,pl->data.prizeStatus[2]);
			}
			pl = pl->next;
		}
	printf("************************************\n");
	printf("预告:下一期彩票,奖池至少%d元\n",pos2->data.totalBonus);
}
customerLottery_t* find_this_date(sponsorLottery_t* pos2,customerLottery_t* head3){
	customerLottery_t* p = head3->next;
	while(p!=head3){
		if(p->data.date == pos2->data.date){
			return p;
		}
		p = p->next;
	}
	return head3;
}

//查看彩票信息
void check_sponsorLottery(sponsorLottery_t* head2){
	printf("所有彩票信息:\n");
	sponsorLottery_t* p2 = head2->next;
	while(p2!=head2){
		printf("***************************************\n");
		printf("期    号:%d\n单    价:%d\n开奖状态:%d\n",p2->data.date,p2->data.price,p2->data.openingStatus);
		printf("中奖号码:");
		for(int i=0;i<5;i++){
			printf("%d ",p2->data.winningNum[i]);
		}
		printf("\n");
		printf("售出总数:%d\n奖池累计:%d\n",p2->data.saleNum,p2->data.totalBonus);
		
		p2 = p2->next;
	}
	printf("***************************************\n");
	
	go_back();
}












