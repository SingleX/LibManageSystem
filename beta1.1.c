#include"stdio.h"
#include"string.h"
#include"conio.h"
#include"stdlib.h"
int N;
FILE *fpa;               //指向管理员信息文件的指针
char administor[40],passward[50];//储存账户名和密码
//定义图书结构体类型book
struct book
{
	long num;
	char name[20];
	char publish[20];//出版社
	struct time
	{
		int day;
		int month;
		int year;
	}t;
	int jie;//借阅
}bk[20];
struct car /*借书卡的数据类型*/
{
	int carnum;
	char studentname[10];
	int studentclass;
}car[100];
struct student /*定义学生类型，用于存放借出的书籍*/
{
	int carnum;
	char lendbook[10];
}student[1000];
delcar()//删除借书卡
	{
		FILE *fp,*fp2;
		int i;
		int carnum;
		char choice;
		fp=fopen("car.txt","r");
		fp2=fopen("car_l.txt","w");
		printf("请输入你要删除的卡号\n");
		printf("如果你输入的卡号存在，系统自动删除该信息！如果不存在，系统不做任何改动！\n");
		scanf("%d",&carnum);
		for(i=0;fread(&car[i],sizeof(struct car),1,fp)!=0;i++)
		{
			if(car[i].carnum!=carnum)
			{

				fwrite(&car[i],sizeof(struct car),1,fp2);
			}
		}
		fclose(fp);
		fclose(fp2);
		printf("是否真的要删除该卡？删除后该书籍的所有信息将无法恢复《Y/N》\n");
		scanf("%s",&choice);
		if(choice=='y'||choice=='Y')
		{
			fp=fopen("car.txt","w");
			fp2=fopen("car_l.txt","r");
			for(i=0;fread(&car[i],sizeof(struct car),1,fp2)!=0;i++)
			{
				fwrite(&car[i],sizeof(struct car),1,fp);
			}
			fclose(fp);
			fclose(fp2);
			fp2=fopen("car_l.txt","w");
			fclose(fp2);
			printf("按任意键返回\n");
			getch();
			return 0;
		}
		else
		{
			printf("按任意键返回\n");
			getch();
			return 0;
		}
	}
int addcar()//增加借书卡
	{
		FILE *fp;
		int i=0,n;
		fp=fopen("car.txt","a+");
		system("CLS");
	printf("\n\n\n\n");
	printf("\t\t※※※※※※※※※※※※※※※※※※※※※※※\n");
	printf("\t\t※                                          ※\n");
	printf("\t\t※               录入用户信息               ※\n");
	printf("\t\t※                                          ※\n");
	printf("\t\t※※※※※※※※※※※※※※※※※※※※※※※\n");
	printf("\n\t\t请输入您要录入的数量：");
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		printf("请你输入卡号\n");
		scanf("%d",&car[i].carnum);
		printf("请你输入学生姓名\n");
		scanf("%s",car[i].studentname);
		printf("请你输入班级\n");
		scanf("%d",&car[i].studentclass);
		fwrite(&car[i],sizeof(struct car),1,fp);
	}
		fclose(fp);
		printf("输入完毕，任意键返回\n");
		getch();
		return 0;
	}
void carcount()//图书卡统计
	{
		FILE *fp;
		int i,n=0;
		fp=fopen("car.txt","r");
		for(i=0;fread(&car[i],sizeof(struct car),1,fp)!=0;i++)
		{
			printf("第%d张卡<卡号：%d 姓名：%s 班级：%d>\n",i+1,car[i].carnum,car[i].studentname,car[i].studentclass);
			n=n+1;
		}
		fclose(fp);
		printf("目前共有%d名读者\n",n);
		printf("按任意键\n");
		getch();
	}
//管理员密码验证
int welcome()
{
	int num=3;             //统计输入次数
	int sign=2;            //标记错误类型
	char F_administor[40],F_passward[50];//读取文件中储存的账户和密码
    system("color 1F");
	printf("----------------------------------------------------------------------------\n");
    printf("|                                                                          |\n");
    printf("|                       欢迎使用计科卓越图书借阅系统                       |\n");
    printf("|                                                                          |\n");
    printf("----------------------------------------------------------------------------\n");
	if((fpa=fopen("管理员信息.txt","rt"))==NULL)
	{
		printf("首次使用该系统，请注册管理员账户\n");  //账户和密码输入界面
		fpa=fopen("管理员信息.txt","wb+");
		printf("请输入管理员账号：");
		scanf("%4s",administor);
		getchar();
		printf("请输入密码：");
		scanf("%4s",passward);
		getchar();
		if((fpa=fopen("管理员信息.txt","wb+"))==NULL)
		{
			printf("注册失败！！！请稍后重试\n");
			return 0;
		}
		else
		{
			fprintf(fpa,"%40s%50s",administor,passward);//将管理员账户和密码存入文件
			fclose(fpa);
			printf("注册成功，请按任意键继续...");
			getch();
		}
		return 1;
	}
	fclose(fpa);
	if((fpa=fopen("管理员信息.txt","rb"))==NULL) //以只读方式打开文件，判断输入的密码是否正确
	{
		printf("文件打开失败，请稍后重试！！");
		return 0;
	}
	else
	{
		while(num)                              //判断错误类型
		{
			if(sign==1)
			{
				printf("\n该管理员账户不存在，您还有%d次输入机会\n",num);
			}
			else if(sign==0)
			{
				printf("\n密码输入错误，您还有%d次输入机会\n",num);
			}
			printf("请输入管理员账号：");
			scanf("%40s",administor);
			getchar();
			printf("请输入密码：");
			scanf("%50s",passward);
			getchar();
			fscanf(fpa,"%40s%50s",F_administor,F_passward);
			if(strcmp(F_administor,administor)==0)
			{
				if(strcmp(F_passward,passward)==0)
				{
				    fclose(fpa);
					return 1;
				}
				else
				{
					sign=0;
				}
			}
			else
			{
				sign=1;
			}
			num--;
		}
		printf("您的输入错误次数超过3次，按任意键退出系统。\n");
		fclose(fpa);
		return 0;
	}
}
//修改密码
void xiugaimima()
{
	char F_administor[40],F_passward[50],key1[50],key2[50],admin[40];//读取文件中储存的账户和密码
	printf("\n\n\n\n");
	printf("\t\t※※※※※※※※※※※※※※※※※※※※※※※\n");
	printf("\t\t※                                          ※\n");
	printf("\t\t※                  修改密码                ※\n");
	printf("\t\t※                                          ※\n");
	printf("\t\t※※※※※※※※※※※※※※※※※※※※※※※\n");
	printf("\n");
	if((fpa=fopen("管理员信息.txt","rt"))==NULL) //以只读方式打开文件，判断输入的密码是否正确
        {
            printf("文件打开失败，请稍后重试！！");
        }
	while(1)
	{
	    printf("\t\t请输入原始密码：");
	    scanf("%50s",passward);
        getchar();
        fscanf(fpa,"%40s%50s",F_administor,F_passward);
        strcpy(admin,F_administor);
		if(strcmp(F_passward,passward)==0)
		{
			printf("\t请输入新密码：");
			scanf("%50s",key1);
			printf("\t请再次输入新密码：");
			scanf("%50s",key2);
			if(strcmp(key1,key2)==0)
			{
				printf("\t密码修改成功，退出系统生效!!  任意键返回...");
                fpa=fopen("管理员信息.txt","w");
				fprintf(fpa,"%40s%50s",admin,key1);
				fclose(fpa);
				getch();break;
			}
			else
			{
				printf("\t两次密码不同，修改失败！   任意键返回...");
				getch();
				break;
			}
		}
		else
		{
			printf("\t密码错误！ 任意键返回...");
			getch();
			break;
		}
	}

}
//建立图书信息库
void xinxi()
{
	FILE *fp;
	int i;
	fp=fopen("总的图书记录文件.txt","at");
	system("CLS");
	printf("\n\n\n\n");
	printf("\t\t※※※※※※※※※※※※※※※※※※※※※※※\n");
	printf("\t\t※                                          ※\n");
	printf("\t\t※               录入图书信息               ※\n");
	printf("\t\t※                                          ※\n");
	printf("\t\t※※※※※※※※※※※※※※※※※※※※※※※\n");
	printf("\n\t\t请输入您要录入的数量：");
	scanf("%d",&N);
	for(i=0;i<N;i++)
	{
		printf("\t\t请输入第%d本书的编号:",i+1);
		scanf("%d",&bk[i].num);
		printf("\t\t请输入第%d本书的名称:",i+1);
		scanf("%s",bk[i].name);
		printf("\t\t请输入第%d本书的出版社:",i+1);
		scanf("%s",bk[i].publish);
		printf("\t\t请输入第%d本书的出版时间(格式如:2011.5.1):",i+1);
		scanf("%d.%d.%d",&bk[i].t.year,&bk[i].t.month,&bk[i].t.day);
		printf("\t\t该书是否已被借阅？已被借阅请输入1，未被借阅请输入0：");
		scanf("%d",&bk[i].jie);
		printf("\t--------------------------------------------------------------------------\n");
		fwrite(&bk[i],sizeof(struct book),1,fp);
	}
	rewind(fp);
	fclose(fp);
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t※※※※※※※※※※※※※※※※※※※※※※※\n");
	printf("\t\t※                                          ※\n");
	printf("\t\t※                信息录入完成              ※\n");
	printf("\t\t※                                          ※\n");
	printf("\t\t※※※※※※※※※※※※※※※※※※※※※※※\n");
	printf("\n\t\t按任意键继续...");
}


//管理员模式
int adm()
{
	int x;
	printf("\n\n\n\n");
	printf("\t\t※※※※※※※※※※※※※※※※※※※※※※※\n");
	printf("\t\t※                                          ※\n");
	printf("\t\t※                管理员模式                ※\n");
	printf("\t\t※                                          ※\n");
	printf("\t\t※※※※※※※※※※※※※※※※※※※※※※※\n");
	printf("\n");
	printf("\t\t\t\t1.录入图书信息\n");
	printf("\t\t\t\t2.查看图书信息\n");
	printf("\t\t\t\t3.修改或删除图书\n");
	printf("\t\t\t\t4.录入用户信息\n");
	printf("\t\t\t\t5.删除信息\n");
	printf("\t\t\t\t6.用户统计\n");
	printf("\t\t\t\t7.借书统计\n");
	printf("\t\t\t\t8.修改管理密码\n");
	printf("\t\t\t\t9.还书\n");
	printf("\t\t\t\t10.借书\n");
	printf("\t\t\t\t11.退出管理员模式\n");
	printf("\n\t\t请输入您的选择：");
	scanf("%d",&x);
	return x;
}

//查看所有图书
void show_all_book()
{
	FILE *fp;
	int i;
	fp=fopen("总的图书记录文件.txt","r");
		printf("\t编号\t图书名称\t出版社\t\t出版时间\t状态\n");
		for(i=0;fread(&bk[i],sizeof(struct book),1,fp)!=0;i++)
		{
			    printf("\t%-7d %-8s	%-12s    %4d年%d月%d日",bk[i].num,bk[i].name,bk[i].publish,bk[i].t.year,bk[i].t.month,bk[i].t.day);
			if(bk[i].jie==0)
				printf("    未借阅\n");
			else
				printf("    已借阅\n");
		}

	fclose(fp);
}
//按书名查看
void showbook_name()
{
	FILE *fp;
	int i,k=0,n;
	char book_name[20];
	fp=fopen("总的图书记录文件.txt","r");
	printf("\n\n\n\n");
	printf("\t\t※※※※※※※※※※※※※※※※※※※※※※※\n");
	printf("\t\t※                                          ※\n");
	printf("\t\t※                 按书名查询               ※\n");
	printf("\t\t※                                          ※\n");
	printf("\t\t※※※※※※※※※※※※※※※※※※※※※※※\n");
	printf("\n\t\t请输入您要查看的图书名称：");
	scanf("%s",book_name);
	for(i=0;fread(&bk[i],sizeof(struct book),1,fp)!=0;i++)
	{
		if(strcmp(book_name,bk[i].name)==0)
		{
			n=i;
			if(k==0)
				printf("\t编号\t图书名称\t出版社\t\t出版时间\t状态\n");
			    printf("\t%-7d %-8s	%-12s    %4d年%d月%d日",bk[n].num,bk[n].name,bk[n].publish,bk[n].t.year,bk[n].t.month,bk[n].t.day);
			if(bk[n].jie==1)
				printf("    已被借阅\n");
			else
				printf("    可以借阅\n");
			printf("\t\t查询成功!按任意键返回...");
			k++;
		}
	}
	   fclose(fp);
		if(k==0)
			printf("\t\t不存在该图书!按任意键返回...");

}
//按书号查看
void showbook_num()
{
	FILE *fp;
	int n,book_num,i,k=0;
	fp=fopen("总的图书记录文件.txt","r");
	printf("\n\n\n\n");
	printf("\t\t※※※※※※※※※※※※※※※※※※※※※※※\n");
	printf("\t\t※                                          ※\n");
	printf("\t\t※                按书号查看                ※\n");
	printf("\t\t※                                          ※\n");
	printf("\t\t※※※※※※※※※※※※※※※※※※※※※※※\n");
	printf("\n\t\t请输入您要查看的图书编号：");
	scanf("%d",&book_num);
	for(i=0;fread(&bk[i],sizeof(struct book),1,fp)!=0;i++)
	{
		if(book_num==bk[i].num)
		{
			n=i;
			if(k==0)
				printf("\t编号\t图书名称\t出版社\t\t出版时间\t状态\n");
			    printf("\t%-7d %-8s	%-12s    %4d年%d月%d日",bk[n].num,bk[n].name,bk[n].publish,bk[n].t.year,bk[n].t.month,bk[n].t.day);
			if(bk[n].jie==1)
				printf("    已被借阅\n");
			else
				printf("    可以借阅\n");
			k++;
			printf("\t\t按任意键返回...");
		}
	}
	fclose(fp);
		if(k==0)
			printf("\t\t不存在该图书。按任意键返回...");
}
//显示全部已借阅图书
void yijieyue()
{
	FILE *fp;
	int i,k=0;
	fp=fopen("总的图书记录文件.txt","r");
		for(i=0;fread(&bk[i],sizeof(struct book),1,fp)!=0;i++)
		{
			if(bk[i].jie==1)
			{
				if(k==0)
				{
				printf("\t编号\t图书名称\t出版社\t\t出版时间\n");
				}
			    printf("\n\t%-7d %-8s	%-12s    %4d年%d月%d日",bk[i].num,bk[i].name,bk[i].publish,bk[i].t.year,bk[i].t.month,bk[i].t.day);//???
				k++;
			}
		}
		fclose(fp);
			if(k==0)
				printf("\n\t\t目前没有任何书借出。按任意键返回...");

}
//显示全部未借阅图书
void weijieyue()
{
	FILE *fp;
	int i,k=0;
	fp=fopen("总的图书记录文件.txt","r");

		for(i=0;fread(&bk[i],sizeof(struct book),1,fp)!=0;i++)
		{
			if(bk[i].jie==0)
			{
				if(k==0)
				{
				printf("\t编号\t图书名称\t出版社\t\t出版时间\n");
				}
			    printf("\n\t%-7d %-8s	%-12s    %4d年%d月%d日",bk[i].num,bk[i].name,bk[i].publish,bk[i].t.year,bk[i].t.month,bk[i].t.day);//???
				k++;
			}
		}
		fclose(fp);
			if(k==0)
				printf("\n\t\t抱歉目前所有的书都已被借出。按任意键返回...");

}
//查看图书菜单
void show()
{
	int x;
	do
	{
		system("cls");
		printf("\n\n\n\n");
		printf("\t\t※※※※※※※※※※※※※※※※※※※※※※※\n");
		printf("\t\t※                                          ※\n");
		printf("\t\t※              查看图书信息                ※\n");
		printf("\t\t※                                          ※\n");
		printf("\t\t※※※※※※※※※※※※※※※※※※※※※※※\n");
		printf("\n");
		printf("\t\t\t\t1.按书名查找\n");
		printf("\t\t\t\t2.按书号查找\n");
		printf("\t\t\t\t3.查看所有未借阅图书\n");
		printf("\t\t\t\t4.查看所有已借阅图书\n");
		printf("\t\t\t\t5.查看所有图书\n");
		printf("\t\t\t\t6.返回主菜单\n");
		printf("\n\t\t请输入您的选择：");
		scanf("%d",&x);
		switch(x)
		{
		case 1:system("cls");showbook_name();getch();break;//按书名查看
		case 2:system("cls");showbook_num();getch();break;//按书号查看
		case 3:system("cls");weijieyue();getch();break;//查看未借阅图书
		case 4:system("cls");yijieyue();getch();break;//查看已借阅图书
		case 5:system("cls");show_all_book();getch();break;//查看所有图书
		}
	}while(x!=6);
}

//按书名进行查找并修改信息
void xiugai_name()
{
	FILE *fp,*fp2;
	int i,book_xb,k=0;
	char temp[20];
	fp=fopen("总的图书记录文件.txt","r");
	fp2=fopen("中间临时文件.txt","w");
	while(1)
	{
		system("cls");
		printf("\n\n\n\n");
		printf("\t\t※※※※※※※※※※※※※※※※※※※※※※※\n");
		printf("\t\t※                                          ※\n");
		printf("\t\t※             按书名进行修改               ※\n");
		printf("\t\t※                                          ※\n");
		printf("\t\t※※※※※※※※※※※※※※※※※※※※※※※\n");
		printf("\n");
		printf("\n\t\t请输入您准备修改的图书的名称，输入'exit'退出：");
		scanf("%s",temp);
		if(strcmp(temp,"exit")==0)
			break;
		else
		{
			for(i=0;fread(&bk[i],sizeof(struct book),1,fp)!=0;i++)
			{
				if(strcmp(temp,bk[i].name)==0)
				{
					book_xb=i;
					printf("\t该书的信息为：\n");
					printf("\t编号\t图书名称\t出版社\t\t出版时间\t状态\n");
				    printf("\t%-7d %-8s	%-12s    %4d年%d月%d日",bk[i].num,bk[i].name,bk[i].publish,bk[i].t.year,bk[i].t.month,bk[i].t.day);
					if(bk[book_xb].jie==1)
						printf("已被借阅\n");
					else
						printf("可以借阅\n");
					k++;
					printf("\t\t现在请输入新信息：\n");
					printf("\t\t请输入本书的编号：\n");
					scanf("%d",&bk[book_xb].num);
					printf("\t\t请输入本书的名称：\n");
					scanf("%s",bk[book_xb].name);
					printf("\t\t请输入本书的出版社：\n");
					scanf("%s",bk[book_xb].publish);
					printf("\t\t请输入本书的出版时间（如2011,5,1）：\n");
					scanf("%d,%d,%d",&bk[book_xb].t.year,&bk[book_xb].t.month,&bk[book_xb].t.day);
					printf("\t\t该书是否已被借阅？已被借阅输入1，未被借阅输入0 ：");
					scanf("%d",&bk[book_xb].jie);
					fwrite(&bk[i],sizeof(struct book),1,fp2);
					continue;
				}
				fwrite(&bk[i],sizeof(struct book),1,fp2);
			}

			fclose(fp);
			fclose(fp2);
			fp=fopen("总的图书记录文件.txt","w");
	        fp2=fopen("中间临时文件.txt","r");
			for(i=0;fread(&bk[i],sizeof(struct book),1,fp2)!=0;i++)
			{
				 fwrite(&bk[i],sizeof(struct book),1,fp);
			}
			fclose(fp);
	    	fclose(fp2);
			fp2=fopen("bookl.txt","w");
			  if(k==0)
				{
					printf("\t\t您输入的书名不存在。按任意键继续...");
					getch();
					continue;
				}
				printf("\t\t恭喜，信息修改成功。按任意键返回...");
				getch();
				break;
		}
	}
}
//按书号进行查找并修改信息
void xiugai_num()
{
	FILE *fp,*fp2;
	int i,book_xb,k=0;
	long temp;
	fp=fopen("总的图书记录文件.txt","r");
	fp2=fopen("中间临时文件.txt","w");
	do
	{
		system("cls");
		printf("\n\n\n\n");
		printf("\t\t※※※※※※※※※※※※※※※※※※※※※※※\n");
		printf("\t\t※                                          ※\n");
		printf("\t\t※             按书号进行修改               ※\n");
		printf("\t\t※                                          ※\n");
		printf("\t\t※※※※※※※※※※※※※※※※※※※※※※※\n");
		printf("\n");
		printf("\n\t\t请输入您准备修改的图书的书号，输入'0'退出：");
		scanf("%ld",&temp);
		if(temp==0) break;
		else
		{
			for(i=0;fread(&bk[i],sizeof(struct book),1,fp)!=0;i++)
			{
				if(temp==bk[i].num)
				{
					book_xb=i;
					printf("\t该书的信息为：\n");
					printf("\t编号\t图书名称\t出版社\t\t出版时间\t状态\n");
				    printf("\t%-7d %-8s	%-12s    %4d年%d月%d日",bk[i].num,bk[i].name,bk[i].publish,bk[i].t.year,bk[i].t.month,bk[i].t.day);
					k++;
					if(bk[book_xb].jie==1)
						printf("    已被借阅\n");
					else
						printf("    可以借阅\n");
					printf("\t\t现在请输入新信息：\n");
					printf("\t\t请输入本书的编号：\n");
					scanf("%d",&bk[book_xb].num);
					printf("\t\t请输入本书的名称：\n");
					scanf("%s",bk[book_xb].name);
					printf("\t\t请输入本书的出版社：\n");
					scanf("%s",bk[book_xb].publish);
					printf("\t\t请输入本书的出版时间（如2011,5,1）：\n");
					scanf("%d,%d,%d",&bk[book_xb].t.year,&bk[book_xb].t.month,&bk[book_xb].t.day);
					printf("\t\t该书是否已被借阅？已被借阅输入1，未被借阅输入0 ：");
					scanf("%d",&bk[book_xb].jie);
					fwrite(&bk[i],sizeof(struct book),1,fp);
					continue;
				}
				fwrite(&bk[i],sizeof(struct book),1,fp);
			}
			fclose(fp);
			fclose(fp2);
			fp=fopen("总的图书记录文件.txt","w");
	        fp2=fopen("中间临时文件.txt","r");
			for(i=0;fread(&bk[i],sizeof(struct book),1,fp2)!=0;i++)
			{
				 fwrite(&bk[i],sizeof(struct book),1,fp);
			}
				if(k==0)
				{
					printf("\t\t您输入的书名不存在。按任意键继续...");
					getch();
					continue;
				}
				printf("\t\t恭喜，信息修改成功。按任意键返回...");
				getch();
				break;
		}
	}while(temp!=0);
}
//删除所有图书
void dele_all()
{

	char queren[4];
	printf("\n\n\n\n\t\t继续操作会删除所有信息，是否继续？y 继续，n 撤销...");
	scanf("%s",queren);
	if(strcmp(queren,"y")==0)
	{
		fopen("总的图书记录文件.txt","w");
		printf("\t\t删除成功\n");
	}
	else
	{
		printf("\t\t操作被用户取消。按任意键返回...");
		getch();
	}
}
//按书名删除
void dele_name()
{
	FILE *fp,*fp2;
	int i,book_xb,k=0,j;
	char queren[4],temp_name[20];
    fp=fopen("总的图书记录文件.txt","r");
	fp2=fopen("中间临时文件.txt","w");
	printf("\n\n\n\n\t\t请输入你要删除的书的名称，输入0退出：");
	scanf("%s",temp_name);
	if(strcmp(temp_name,"0")!=0)
	{
		for(i=0;fread(&bk[i],sizeof(struct book),1,fp2)!=0;i++)
		{
			if(strcmp(temp_name,bk[i].name)==0)
			{
				book_xb=i;
				printf("\t\t该书的信息为：\n");
				printf("\t编号\t图书名称\t出版社\t\t出版时间\t状态\n");
			    printf("\t%-7d %-8s	%-12s    %4d年%d月%d日",bk[i].num,bk[i].name,bk[i].publish,bk[i].t.year,bk[i].t.month,bk[i].t.day);
				if(bk[i].jie==0)
					printf("    未借阅\n");
				else
					printf("    已借阅\n");
				k++;
				printf("\t\t是否要删除该书？是 y，否 n ：");
				scanf("%s",queren);
				if(strcmp(queren,"y")==0)
				{
					for(j=0;fread(&bk[j],sizeof(struct book),1,fp)!=0;j++)
					{
						if(strcmp(bk[i].name,temp_name)!=0)
						{
							fwrite(&bk[i],sizeof(struct book),1,fp2);

						}
					}
					fclose(fp);
					fclose(fp2);
					fp=fopen("总的图书记录文件.txt","w");
                	fp2=fopen("中间临时文件.txt","r");
					for(j=0;fread(&bk[j],sizeof(struct book),1,fp2)!=0;j++)
                    {
						fwrite(&bk[i],sizeof(struct book),1,fp);
					}
					fclose(fp);
					fclose(fp2);
					fopen("中间临时文件.txt","r");
					printf("\t\t删除成功\n");
				}
				else
					printf("\t\t操作被用户取消、按任意键返回...");
			}
		}
			if(k==0)
				printf("\t\t未找到该书，请核实后再操作。按任意键返回...");
			getch();
	}
}
//按书号查找并删除
void dele_num()
{
	FILE *fp,*fp2;
	int i,book_xb,k=0,temp_num,j;
	char queren[4];
	fp=fopen("总的图书记录文件.txt","r");
	fp2=fopen("中间临时文件.txt","w");
	while(1)
	{
		printf("\t\t输入你要删除的书的书号，输入0，退出：");
		scanf("%d",&temp_num);
		if(temp_num==0) break;
		else
		{
			for(i=0;fread(&bk[i],sizeof(struct book),1,fp)!=0;i++)
			{
			   if(temp_num==bk[i].num)
			   {
				  book_xb=i;
				  printf("\t\t该书的信息为：\n");
				  printf("\t编号\t图书名称\t出版社\t\t出版时间\t状态\n");
			       printf("\t%-7d %-8s	%-12s    %4d年%d月%d日",bk[i].num,bk[i].name,bk[i].publish,bk[i].t.year,bk[i].t.month,bk[i].t.day);
				 if(bk[i].jie==0)
					printf("未借阅\n");
				else
					printf("已借阅\n");
				k++;
				printf("\t\t是否要删除该书？是 y，否 n ：");
				scanf("%s",queren);
				if(strcmp(queren,"y")==0)
				{
					for(j=0;fread(&bk[j],sizeof(struct book),1,fp)!=0;j++)
					{
						if(temp_num!=bk[i].num)
						{
							fwrite(&bk[i],sizeof(struct book),1,fp2);

						}
					}
					fclose(fp);
					fclose(fp2);
					fp=fopen("总的图书记录文件.txt","w");
                	fp2=fopen("中间临时文件.txt","r");
					for(j=0;fread(&bk[j],sizeof(struct book),1,fp2)!=0;j++)
                    {
						fwrite(&bk[i],sizeof(struct book),1,fp);
					}
					fclose(fp);
					fclose(fp2);
					fopen("中间临时文件.txt","r");
					printf("\t\t删除成功\n");
				}
				else
					printf("\t\t操作被用户取消、按任意键返回...");
			}
          }
			if(k==0)
				printf("\t\t未找到该书，请核实后再操作。按任意键返回...");
			getch();
			break;
		}
	}
}
void dele()
{
	int x;
	do
	{
		system("cls");
		printf("\n\n\n\n");
		printf("\t\t※※※※※※※※※※※※※※※※※※※※※※※\n");
		printf("\t\t※                                          ※\n");
		printf("\t\t※               删除图书信息               ※\n");
		printf("\t\t※                                          ※\n");
		printf("\t\t※※※※※※※※※※※※※※※※※※※※※※※\n");
		printf("\n");
		printf("\t\t\t\t1.按书名删除\n");
		printf("\t\t\t\t2.按书号删除\n");
		printf("\t\t\t\t3.删除所有图书\n");
		printf("\t\t\t\t4.返回主菜单\n");
		printf("\n\t\t请输入您的选择：");
		scanf("%d",&x);
		switch(x)
		{
		case 1:system("cls");dele_name();break;
		case 2:system("cls");dele_num();break;//
		case 3:system("cls");dele_all();getch();break;//
		}
	}while(x!=4);
}
//修改图书
void xiugai()
{
	int x;
	do
	{
		system("cls");
		printf("\n\n\n\n");
		printf("\t\t※※※※※※※※※※※※※※※※※※※※※※※\n");
		printf("\t\t※                                          ※\n");
		printf("\t\t※              修改图书信息                ※\n");
		printf("\t\t※                                          ※\n");
		printf("\t\t※※※※※※※※※※※※※※※※※※※※※※※\n");
		printf("\n");
		printf("\t\t\t\t1.按书名修改\n");
		printf("\t\t\t\t2.按书号修改\n");
		printf("\t\t\t\t3.删除图书\n");
		printf("\t\t\t\t4.返回主菜单\n");
		printf("\n\t\t请输入您的选择：");
		scanf("%d",&x);
		switch(x)
		{
		case 1:system("cls");xiugai_name();break;
		case 2:system("cls");xiugai_num();break;//
		case 3:system("cls");dele();break;//
		}
	}while(x!=4);
}
huanbook() /*还书函数*/
{
	FILE *fp,*fp2; /*定义两个文件指针，fp2用于修改数据时设立临时文件用，防止数据遭破坏*/
	int i,n;
	int carnum;
	char lendbook[10];
	printf("请你输入你的卡号\n");
	scanf("%d",&carnum);
	fp=fopen("car.txt","r"); /*读取卡号记录*/
	for(i=0;fread(&car[i],sizeof(struct car),1,fp)!=0;i++) /*for循环判断卡号是否存在*/
	{
		if(car[i].carnum==carnum) /*卡号存在，进入下一循环*/
			{
				n=i;
				fclose(fp);
				printf("请输入你要还的书的名字\n");
				scanf("%s",lendbook);
				fp=fopen("record.txt","r");

				for(i=0;fread(&student[i],sizeof(struct student),1,fp)!=0;i++) /*判断是否借阅了输入的书*/
				{
					if(strcmp(student[i].lendbook,lendbook)==0) /*借阅了该书，进入下一循环，否则出错显示*/
					{
						fclose(fp);
						fp=fopen("record.txt","r");
						fp2=fopen("bookl.txt","w");
						for(i=0;fread(&student[i],sizeof(struct student),1,fp)!=0;i++)
						{
							if(strcmp(student[i].lendbook,lendbook)==0)
							{
								continue; /*删除还掉的书的借书记录*/
							}
							fwrite(&student[i],sizeof(struct student),1,fp2); /*写入原来没还的书的记录*/
						}
						fclose(fp);
						fclose(fp2);
						fp=fopen("record.txt","w");
						fp2=fopen("bookl.txt","r");
						for(i=0;fread(&student[i],sizeof(struct student),1,fp2)!=0;i++)
						{
							fwrite(&student[i],sizeof(struct student),1,fp); /*将借书记录信息写回*/
						}
						fclose(fp);
						fclose(fp2);
						fopen("bookl.txt","w"); /*清临时文件的记录*/
						fclose(fp2);
						fp=fopen("总的图书记录文件.txt","r");
						fp2=fopen("bookl.txt","w");
						for(i=0;fread(&bk[i],sizeof(struct book),1,fp)!=0;i++) /*将书的记录写入临时文件，防止因为修改信息破坏以前的记录*/
						{
							if(i==n)
							{
								bk[i].jie=1;
								fwrite(&bk[i],sizeof(struct book),1,fp2); /*将还的书的原来状态设为无人借阅的*/
								continue;
							}
							fwrite(&bk[i],sizeof(struct book),1,fp2);
						}
						fclose(fp);
						fclose(fp2);
						fp=fopen("总的图书记录文件.txt","w");
						fp2=fopen("bookl.txt","r");
						for(i=0;fread(&bk[i],sizeof(struct book),1,fp2)!=0;i++)
						{
							fwrite(&bk[i],sizeof(struct book),1,fp); /*将临时文件写回*/
						}
						fclose(fp);
						fclose(fp2);
						fopen("bookl.txt","w"); /*清临时文件*/
						fclose(fp2);
						printf("还书完毕，按任意键返回\n");
						getch();
						return 1;
					}
				}
				printf("你没有借这样的书，任意键返回\n"); /*出错提示*/
				fclose(fp);
				getch();
				return 0;
			}
	}
	printf("系统没这样的卡,按任意键返回\n"); /*出错提示*/
	fclose(fp);
	getch();
	return 0;
}
lendbook()
	{
		FILE *fp,*fp2;
		int i,n;
		int carnum;
		printf("请你输入你的卡号\n");
		scanf("%d",&carnum);
		fp=fopen("car.txt","r");
		for(i=0;fread(&car[i],sizeof(struct car),1,fp)!=0;i++)
		{
		   if(car[i].carnum==carnum)
		   {
			   n=i;
			   fclose(fp);
               printf("请输入你要借阅的书的名字\n");
			   scanf("%s",student[n].lendbook);
			   fp=fopen("总的图书记录文件.txt","r");
			   for(i=0;fread(&bk[i],sizeof(struct book),1,fp)!=0;i++)
			   {
				   if(strcmp(bk[i].name,student[n].lendbook)==0)
				   {
					   if(bk[i].jie==1) {printf("对不起，此书有人借出，请借其他书\n");fclose(fp);getch();return 0;}
				       else
	 				   fclose(fp);
					   fp=fopen("record.txt","a+");
					   student[n].carnum=carnum;
					   fwrite(&student[n],sizeof(struct student),1,fp);
					   fclose(fp);
 				       fp=fopen("总的图书记录文件.txt","r");
				       fp2=fopen("bookl.txt","w");
				       for(i=0;fread(&bk[i],sizeof(struct book),1,fp)!=0;i++)
					   {
					       if(strcmp(bk[i].name,student[n].lendbook)==0)
					       {
						        bk[i].jie=0;
						        fwrite(&bk[i],sizeof(struct book),1,fp2);
								continue;
						   }
						   fwrite(&bk[i],sizeof(struct book),1,fp2);
					   }
					   fclose(fp);
					   fclose(fp2);
				       fp=fopen("总的图书记录文件.txt","w");
					   fp2=fopen("bookl.txt","r");
					   for(i=0;fread(&bk[i],sizeof(struct book),1,fp2)!=0;i++)
					   {
						   fwrite(&bk[i],sizeof(struct book),1,fp);
					   }
				       fclose(fp);
				       fclose(fp2);
				       fopen("bookl.txt","w");
				       fclose(fp2);
					   printf("借书完毕，按任意键返回\n");
					   getch();
					   return 0;
				   }
			   }
			   printf("不存在这样的书，任意键返回\n");
			   fclose(fp);
			   getch();
			   return 0;
		   }
		}
		printf("你的卡号不存在，请申请新卡,按任意键返回\n");
		fclose(fp);
		getch();
		return 0;
	}
lendcount()
	{
		FILE *fp;
		int i,n=0;
		fp=fopen("record.txt","r");
		for(i=0;fread(&bk[i],sizeof(struct student),1,fp)!=0;i++)
		{

		   printf("卡号：%d 借出的书籍：%s \n",student[i].carnum,student[i].lendbook);
		   n=n+1;
		}
		fclose(fp);
		printf("目前共有%d本书借出\n",n);
		printf("按任意键\n");
		getch();
		return n;
	}
//主菜单
int mymainmenu()
{
	int x;
	printf("\n\n\n\n");
	printf("\t\t※※※※※※※※※※※※※※※※※※※※※※※\n");
	printf("\t\t※                                          ※\n");
	printf("\t\t※            欢迎使用图书管理系统          ※\n");
	printf("\t\t※                                          ※\n");
	printf("\t\t※※※※※※※※※※※※※※※※※※※※※※※\n");
	printf("\n\t\t\t\t1.管理员登陆\n");
	printf("\t\t\t\t2.读者模式\n");
	printf("\t\t\t\t3.退出系统\n");
	printf("\n\t\t请输入您的选择：");
	scanf("%d",&x);
	return x;
}
//主函数
void main()
{
	int x,x2,s;
        system("color 1F");
	do
	{
		system("cls");
		x=mymainmenu();
		switch(x)
		{
		case 1://调用管理员模式函数
				system("cls");
			  s=welcome();
			 do
			{
				if(s==1)
				{
					system("cls");
					x2=adm();
					switch(x2)
					{
					case 1:system("cls");xinxi();break;
					case 2:system("cls");show();break;
					case 3:system("cls");xiugai();break;
					case 4:system("cls");addcar();break;
					case 5:system("cls");delcar();break;
					case 6:system("cls");carcount();break;
					case 7:system("cls");lendcount();break;
					case 8:system("cls");xiugaimima();break;
					case 9:system("cls");huanbook();break;
					case 10:system("cls");lendbook();break;
					}
				}
				else
				{
					printf("\n\t\t密码错误!!\t按任意键返回...");
					getch();
					break;
				}
			}while(x2!=11);break;
		case 2:
			do
			{
				system("cls");
				show();getch();break;
			}while(x2!=3);
		}
	}while(x!=3);
	   system("cls");
	    printf("\n\n\n\n");
	    printf("\t\t※※※※※※※※※※※※※※※※※※※※※※※\n");
	    printf("\t\t※                                          ※\n");
	    printf("\t\t※            退出成功，谢谢使用!           ※\n");
	    printf("\t\t※                                          ※\n");
	    printf("\t\t※※※※※※※※※※※※※※※※※※※※※※※\n");
}
