//my_version
#include"lottery.h"

typedef struct hero hero_t;
typedef struct monster mon_t;
typedef void (*monsterAttackMethod_t)(hero_t*,mon_t*);

void Round(hero_t* hero,mon_t* mon);
void hero_attack(hero_t* hero,mon_t* mon);
void mon_attack(hero_t* hero,mon_t* mon);
mon_t creat_monster();
void print_monster(mon_t );
void print_hero(hero_t hero);
void hero_level_up(hero_t* hero);
void mon_skill2(hero_t* hero,mon_t* mon);
void mon_skill3(hero_t* hero,mon_t* mon);
void hero_skill1(hero_t* hero,mon_t* mon);
void hero_skill2(hero_t* hero,mon_t* mon);
void hero_skill3(hero_t* hero,mon_t* mon);
void hero_skill4(hero_t* hero,mon_t* mon);

struct hero{
	int hp;
	int attack;
	int defense;
	int speed;
	int speedSum;
	int time_a;
	int state_a;
	int time_d;
	int state_d;
	int anger;
};
struct monster{
	int hp;
	int attack;
	int defense;
	int speed;
	int speedSum;
	int neff;
	monsterAttackMethod_t atk_m[5];
	
};

void game(){
	//怪物和英雄的初始化和打印
	char ch = 0;
	printf("1.开始游戏\n");
	printf("2.退出游戏\n");
	while(1){
		ch = getch();
		if(ch=='1'||ch=='2'){break;}
	}
	if(ch=='2'){return;}
	system("clear");
	
	srand(time(0));
	hero_t hero = {20,5,15,5,0,0,0,0,0,0};
	mon_t mon = {0};
	mon = creat_monster();
	int countMon = 1;
	printf("\033[1;31;10m");//红色
	printf("第%d只怪物来袭:\n",countMon);
	print_monster(mon);
	printf("\033[0m");//白色
	print_hero(hero);
	
	while(1){
		Round(&hero,&mon);
		if(hero.hp<=0){
			printf("游戏结束\n");
			break;
		}else if(mon.hp<=0){
			//当一只怪物死亡后，怪物加强，英雄加强
			printf("第%d只怪物死亡\n",countMon);
			
			printf("是否要退出游戏(y/n)\n");
			char ch = 0;
			while(1){
				ch = getch();
				if(ch=='y'||ch=='n'){break;}
			}
			if(ch=='y'){return;}
			
			if(hero.state_a == 1){
				hero.attack += mon.neff;
				hero.state_a = 0;
				hero.time_a = 0;
				printf("英雄攻击力恢复:%d ",hero.attack);
			}
			if(hero.state_d == 1){
				hero.defense += mon.neff;
				hero.state_d = 0;
				hero.time_d = 0;
				printf("英雄防御力恢复:%d",hero.defense);
			}
			printf("\n\n");
			
			countMon++;
			printf("\033[1;31;10m");//红色
			printf("第%d只更强大怪物来袭:\n",countMon);
			mon = creat_monster();
			print_monster(mon);
			
			printf("\033[0m");//白色
			hero_level_up(&hero);
			print_hero(hero);
		}
	}
	
	return;
}

void Round(hero_t* hero,mon_t* mon){
	int pos = rand()%5;
	//英雄攻击怪物
	if(hero->speedSum >= 50){
		printf("\033[0m");//白色
		hero_attack(hero,mon);
		hero->speedSum = 0;//当速度累加过50后，要重新置0，不然会一直打
	}else{
		hero->speedSum+=hero->speed;
	}
	
	if(mon->hp <= 0){
		return;
	}
	
	//怪物攻击英雄
	if(mon->speedSum >= 50){
		printf("\033[1;31;10m");//红色
		mon->atk_m[pos](hero,mon);
		mon->speedSum = 0;
	}else{
		mon->speedSum+=mon->speed;
	}
}

void hero_attack(hero_t* hero,mon_t* mon){
	int ch = 0;
	while(1){
		printf("1.普通攻击\t\t\t2.舍身攻击\n");
		printf("3.吸血攻击\t\t\t");
		if(hero->anger<100){
			printf("\033[1;31;10m");
			printf("4.终结技\n");
			printf("\033[0m");
		}else{
			printf("4.终结技\n");
		}
		printf("5.显示英雄属性\t\t\t6.查看怪物状态\n");
		printf("\n\n");
		while(1){
			ch = getch() - '0';
			if(ch==4 && hero->anger<100){
				printf("怒气不足，无法释放\n");
				continue;
			}
			if(ch>=1 && ch<=6){
				break;
			}
		}
		switch(ch){
			case 1:
				hero_skill1(hero,mon);
				break;
			case 2:
				hero_skill2(hero,mon);
				break;
			case 3:
				hero_skill3(hero,mon);
				break;
			case 4:
				hero_skill4(hero,mon);
				break;
			case 5:
				print_hero(*hero);
				break;
			case 6:
				print_monster(*mon);
				break;
		}
		if(ch>=1 && ch<=4){
			break;
		}
	}
	
	(hero->time_a)--;
	(hero->time_d)--;
	if(hero->time_d == 0){
		hero->state_d = 0;
		hero->defense += mon->neff;
		printf("********英雄防御力恢复:%d*******\n",hero->defense);
	}
	if(hero->time_a == 0){
		hero->state_a = 0;
		hero->attack += mon->neff;
		printf("********英雄攻击力恢复:%d*******\n",hero->attack);
	}
	printf("\n\n");
	sleep(1);
}
void hero_skill1(hero_t* hero,mon_t* mon){
	int damage = 0;
	if( mon->defense >= hero->attack ){
		damage = 1;
	}else{
		damage = hero->attack - mon->defense;
	}
	
	mon->hp -= damage;
	hero->anger += 10;
	printf("英雄攻击了怪物，造成了%d点伤害\n",damage);
	printf("怪物的剩余血量:%d\n",mon->hp);
}
void hero_skill2(hero_t* hero,mon_t* mon){
	int damage = 0;
	int selfDamage = 0;
	if( mon->defense >= hero->attack ){
		damage = 1;
	}else{
		damage = (hero->attack - mon->defense) * 2.5;
	}
	selfDamage = hero->hp * 0.2;
	if(selfDamage<5){
		selfDamage = 5;
	}
	mon->hp -= damage;
	hero->hp -= selfDamage;
	hero->anger += 10;
	printf("英雄对怪物发动了舍身攻击，造成了%d点伤害，并且损失了%d点生命值\n",damage,selfDamage);
}
void hero_skill3(hero_t* hero,mon_t* mon){
	int damage = 0;
	int recovery = 0;
	if( mon->defense >= hero->attack ){
		damage = 1;
	}else{
		damage = (hero->attack - mon->defense) * 0.8;
	}
	recovery = damage * 0.5;
	mon->hp -= damage;
	hero->hp += recovery;
	hero->anger += 10;
	printf("英雄对怪物发动了吸血攻击，造成了%d点伤害，并且恢复了%d点生命值\n",damage,recovery);
}
void hero_skill4(hero_t* hero,mon_t* mon){
	int damage = hero->attack;
	hero->anger = 0;
	mon->hp -= damage;
	printf("英雄释放了终结技，造成了%d点伤害\n",damage);
}

void mon_attack(hero_t* hero,mon_t* mon){
	int damage = 0;
	if( hero->defense >= mon->attack ){
		damage = 1;
	}else{
		damage = mon->attack - hero->defense;
	}
	
	if(damage > hero->hp * 0.2){
		hero->anger += 20;
	}else{
		hero->anger += 5;
	}
	
	hero->hp -= damage;

	printf("怪物攻击了英雄，造成了%d点伤害\n",damage);
	printf("英雄的剩余血量:%d\n",hero->hp);
	printf("\n\n");
	sleep(1);
}
void mon_skill2(hero_t* hero,mon_t* mon){
	if(hero->state_d==0){
		printf("怪物对英雄释放了技能2,降低了英雄%d点防御力\n\n\n",mon->neff);
		hero->defense -= mon->neff;
		hero->state_d = 1;
		hero->time_d = 3;
	}else{
		printf("施法失败\n\n\n");
	}
	sleep(1);
}
void mon_skill3(hero_t* hero,mon_t* mon){
	if(hero->state_a==0){
		printf("怪物对英雄释放了技能3,降低了英雄%d点攻击力\n\n\n",mon->neff);
		hero->attack -= mon->neff;
		hero->state_a = 1;
		hero->time_a = 3;
	}else{
		printf("施法失败\n\n\n");
	}
	sleep(1);
}

mon_t creat_monster(){
	static int hp=15,attack=17,defense=2,speed=2,neff=4;
	static int count = 0;
	int floatHp=0,floatAttack=0,floatDefense=0,floatSpeed=0;
	mon_t newMon = {0};
	
	floatHp = rand()%5+3;//3~7
	floatAttack = rand()%3+1;//1~3
	floatDefense = rand()%3+1;
	floatSpeed = rand()%3;//0~2
	
	count++;
	if((count-1)%3==0 && (count-1)!=0){
		neff += 2;
	}
	
	newMon.hp = hp;
	newMon.attack = attack;
	newMon.defense = defense;
	newMon.speed = speed;
	newMon.neff = neff;
	newMon.atk_m[0] = mon_attack;
	newMon.atk_m[1] = mon_attack;
	newMon.atk_m[2] = mon_attack;
	newMon.atk_m[3] = mon_skill2;
	newMon.atk_m[4] = mon_skill3;
	//newMon.atk_m[5] = {mon_atk,mon_atk,mon_atk,mon_skill2,mon_skill3};//× 已经做过初始化了，要单个进行赋值
	//怪物里的各个类型变量里的值上浮
	hp += floatHp;
	attack += floatAttack;
	defense += floatDefense;
	speed += floatSpeed;
	//neff变化
	
	return newMon;
}

void print_monster(mon_t mon){
	printf("-------怪物属性--------\n");
	printf("h p:%6d\n",mon.hp);
	printf("atk:%6d\n",mon.attack);
	printf("def:%6d\n",mon.defense);
	printf("spd:%6d\n",mon.speed);
	printf("spdSum:%6d\n",mon.speedSum);
	printf("-----------------------\n");
	printf("\n");
}
void print_hero(hero_t hero){
	printf("-------英雄属性--------\n");
	printf("h p:%6d\n",hero.hp);
	printf("atk:%6d\n",hero.attack);
	printf("def:%6d\n",hero.defense);
	printf("spd:%6d\n",hero.speed);
	printf("spdSum:%6d\n",hero.speedSum);
	if(hero.anger>=100){
		printf("ang:%6d\n",100);
	}else{
		printf("ang:%6d\n",hero.anger);
	}
	printf("-----------------------\n");
	printf("\n\n");
	sleep(1);
}

void hero_level_up(hero_t* hero){
	int ch = 0;
	int i = 0;
	hero->hp += 3;
	hero->attack += 1;
	hero->defense += 1;
	
	printf("英雄击败了怪物，获得了2点属性点\n");
	for(i=0;i<2;i++){
		printf("----------------------------\n");
		printf("1: +5生命值\n");
		printf("2: +2攻击力\n");
		printf("3: +2防御力\n");
		printf("4: +1速度\n");
		printf("----------------------------\n");
		printf("请选择:");
		while(1){
			ch = getch() - '0';
			if(ch>=1 && ch<=4)
				break;
		}
		printf("\n");
		switch(ch){
			case 1:
				hero->hp += 5;
				break;
			case 2:
				hero->attack += 2;
				break;
			case 3:
				hero->defense += 2;
				break;
			case 4:
				hero->speed += 1;
				break;
			default:
				break;
		
		}
	}
}















