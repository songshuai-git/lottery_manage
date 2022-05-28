#include"lottery.h"

int main(){
	srand(time(0));
	
	//客户链表头指针
	customer_t* head = initail_customer();//???√可不可以声明成全局变量，解:可以
	load_customer(head);
	
	//期号彩票链表头指针
	sponsorLottery_t* head2 =  initail_sponsorLottery();
	load_sponsorLottery(head2);
	
	//购买彩票链表头指针
	customerLottery_t* head3 = initail_customerLottery();
	load_customerLottery(head3);
	
	//发行方信息载入
	sponsor_t sponsor = {0};
	load_sponsor(&sponsor);
	
	while(1){
		char ch = 0;
		printf("\t   欢迎来到中国福利彩票\n");
		printf("-------------------首页-------------------\n");
		printf("1.客户入口\n");
		printf("2.彩票发行方入口\n");
		printf("3.公证员入口\n");
		printf("4.超级管理员入口\n\n");
		printf("q:退出程序\n");
		printf("------------------------------------------\n");
	
		printf("请选择:");
		while(1){
			ch = getch();
			if((ch>='1' && ch<='4') || ch=='q'){
				break;
			}
		}
		switch(ch){
			case '1':{
				system("clear");
				char res = customer_entrance(head,head2,head3);
				if(res=='0'){	//本界面
				}else if(res=='q'){ //退出程序
					int res = end_program();
					if(res==1){	//确认退出程序
						free_heap(head,customer_type);
						free_heap(head2,sponsorLottery_type);
						free_heap(head3,customerLottery_type);
						return 0;
					}
				}
				break;
			}
			case '2':{
				system("clear");
				int res = sponsor_login(&sponsor);
				sleep(1);
				system("clear");
				
				if(res==1){		//登录成功
					char res = sponsor_interface(head2,head);
					
					//界面选择
					if(res=='0'){	//本界面
						
					}else if(res=='q'){ //退出程序
						int res = end_program();
						if(res==1){	//确认退出程序
							free_heap(head,customer_type);
							free_heap(head2,sponsorLottery_type);
							free_heap(head3,customerLottery_type);
							return 0;
						}
					}
				}
				
				break;
			}
			case '3':{
				system("clear");
				int res = notory_login();
				sleep(1);
				system("clear");
				
				if(res==1){
					char res = notory_interface(head,head2,head3);
					if(res=='0'){
					}else if(res=='q'){
						int res = end_program();
						if(res==1){
							free_heap(head,customer_type);
							free_heap(head2,sponsorLottery_type);
							free_heap(head3,customerLottery_type);
							return 0;
						}
					}
				}
				break;
			}
			case '4':
				system("clear");
				admin(head,&sponsor,head2,head3);
				break;
			case 'q':{
				system("clear");
				int res = end_program();
				if(res==1){	//退出程序
					free_heap(head,customer_type);//???
					free_heap(head2,sponsorLottery_type);
					free_heap(head3,customerLottery_type);
					head = NULL;
					return 0;
				}
				break;
			}
			default:
				system("clear");
				break;
		}

	}	
	
	return 0;
}

//超管，用于系统检测
void admin(customer_t* head,sponsor_t* sponsor,sponsorLottery_t* head2,customerLottery_t* head3){
	//查看客户库
	customer_t* p = head->next;
	printf("客户库:\n");
	while(p!=head){
		printf("***************************************\n");
		printf("账号:%s\t密码:%s\t余额:%g\n",p->data.account,p->data.pswd,p->data.balance);
		printf("%d期彩票中奖情况:\n一等奖:%4d注\n二等奖:%4d注\n三等奖:%4d注\n",head2->pre->data.date,p->data.prizeStatus[0],p->data.prizeStatus[1],p->data.prizeStatus[2]);
		p = p->next;
	}
	printf("***************************************\n");
	//查看发行库
	printf("\n发行方库:\n");
	printf("账号:%s\t密码:%s\n",sponsor->account,sponsor->pswd);

	//查看期号彩票链表
	printf("\n期号彩票链表:\n");
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
	
	//查看购买彩票链表
	
	printf("\n购买彩票链表:\n");
	customerLottery_t* p3 = head3->next;
	int count = 0;
	while(p3!=head3){
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
		
		p3 = p3->next;
		
		count++;
		if(count==100){
			break;
		}
	}
	printf("***************************************\n");
	printf("购买的彩票仅显示100张\n");	
	
	go_back();
}





