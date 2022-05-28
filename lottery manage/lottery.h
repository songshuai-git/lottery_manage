#ifndef LOTTERY_H //lottery_h lottery_h_ _LOTTERY_H
#define LOTTERY_H 

#include<stdio.h>
#include<user.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<time.h>

typedef struct data data_t;
typedef struct customer customer_t;
typedef struct sponsor sponsor_t;
typedef struct data2 data2_t;
typedef struct sponsorLottery sponsorLottery_t;
typedef struct customerLottery customerLottery_t;
typedef struct data3 data3_t;
typedef void (*free_t)(void*);
typedef void (*chooseWay_t)(int,customerLottery_t*);

//彩民链表
struct data{
	char account[20];
	char pswd[20];
	float balance;
	int prizeStatus[3];//彩民中奖情况，一二三等奖分别中了多少注
	int firstPrize;
	int secondPrize;
};
struct customer{
	data_t data;
	customer_t* pre;
	customer_t* next;
};
//期号彩票链表
struct data2{
	int date;	//期号
	int price;	//单价
	int openingStatus;//开奖状态
	int winningNum[5];//中奖号码
	int saleNum;//售出总数(总注数)
	int totalBonus;//本期奖池总额
};
struct sponsorLottery{
	data2_t data;
	sponsorLottery_t* pre;
	sponsorLottery_t* next;
};
//购买彩票链表
struct data3{
	int date;
	int id;	//单张彩票唯一表示id
	int betNum[5][5];	//最多五注,每一注上有五个号码
	char customerAccount[20];	//购买者的账号
	int number;	//已购买某一彩票号的注数
	int winningStatus;	//中奖状态
	int winningBonus;	//中奖金额
};
struct customerLottery{
	data3_t data;
	customerLottery_t* pre;
	customerLottery_t* next;
};
//彩票发行方
struct sponsor{
	char account[20];
	char pswd[20];
};

//客户端函数
char customer_entrance(customer_t* head,sponsorLottery_t* head2,customerLottery_t* head3);
customer_t* initail_customer();
void free_heap(void* head,free_t p);	//释放对空间，函数指针+回调函数
void customer_type(void* head);
void sponsorLottery_type(void* head);
void customerLottery_type(void* head);

customer_t* find_account(customer_t* head,char* account);
void customer_regist(customer_t* head);
customer_t* customer_login(customer_t* head);
void save_customer(customer_t* head);
void load_customer(customer_t* head);
char customer_interface(customer_t* pos,customer_t* head,sponsorLottery_t* head2,customerLottery_t* head3);
//客户功能实现函数
void check_account(customer_t* pos);
void change_pswd(customer_t* pos);
void charge_account(customer_t* pos);
int remove_account(customer_t* pos,customerLottery_t* head3);
void check_history(customer_t* pos,customerLottery_t* head3);
//购买彩票
customerLottery_t* initail_customerLottery();
void load_customerLottery(customerLottery_t* head3);
void save_customerLottery(customerLottery_t* head3);
void buy_lottery(customer_t* pos,sponsorLottery_t* head2,customerLottery_t* head3);
void single_purchase(customer_t* pos,sponsorLottery_t* pos2,customerLottery_t* head3);
void choose_way(int number,customerLottery_t* new,chooseWay_t p);
void machine_choose(int number,customerLottery_t* new);
void customer_choose(int number,customerLottery_t* new);
void bulk_purchase(customer_t* pos,sponsorLottery_t* pos2,customerLottery_t* head3);
void once_buy(customer_t* pos,sponsorLottery_t* pos2,customerLottery_t* head3,int number,int ch);

//发行方端函数
void load_sponsor(sponsor_t* sponsor);
int sponsor_login(sponsor_t* sponsor);
sponsorLottery_t* initail_sponsorLottery();
//发行方功能实现函数
char sponsor_interface(sponsorLottery_t* head2,customer_t* head);
void issue_lottery(customer_t* head,sponsorLottery_t* head2);
void save_sponsorLottery(sponsorLottery_t* head2);
void load_sponsorLottery(sponsorLottery_t* head2);
void check_customer(customer_t* head);
void bubble_sort(customer_t* head);
void print_customer(customer_t* head);

//公证员端功能实现函数
int notory_login();
char notory_interface(customer_t* head,sponsorLottery_t* head2,customerLottery_t* head3);
void check_sponsorLottery(sponsorLottery_t* head2);
void draw_lottery(customer_t* head,sponsorLottery_t* head2,customerLottery_t* head3);
void convert_lottery(customer_t* head,sponsorLottery_t* pos2,customerLottery_t* head3);
customerLottery_t* find_this_date(sponsorLottery_t* pos2,customerLottery_t* head3);

//超级管理员
void admin(customer_t* head,sponsor_t* sponsor,sponsorLottery_t* head2,customerLottery_t* head3);

//其他辅助函数
void go_back();
int end_program();
void getpswd(char* pswd);
void get_idenCode(char* code);
void game();

//全局变量

#endif









