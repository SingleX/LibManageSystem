#include"stdio.h"
#include"string.h"
#include"conio.h"
#include"stdlib.h"
int N;
FILE *fpa;               //ָ�����Ա��Ϣ�ļ���ָ��
char administor[40],passward[50];//�����˻���������
//����ͼ��ṹ������book
struct book
{
	long num;
	char name[20];
	char publish[20];//������
	struct time
	{
		int day;
		int month;
		int year;
	}t;
	int jie;//����
}bk[20];
struct car /*���鿨����������*/
{
	int carnum;
	char studentname[10];
	int studentclass;
}car[100];
struct student /*����ѧ�����ͣ����ڴ�Ž�����鼮*/
{
	int carnum;
	char lendbook[10];
}student[1000];
delcar()//ɾ�����鿨
	{
		FILE *fp,*fp2;
		int i;
		int carnum;
		char choice;
		fp=fopen("car.txt","r");
		fp2=fopen("car_l.txt","w");
		printf("��������Ҫɾ���Ŀ���\n");
		printf("���������Ŀ��Ŵ��ڣ�ϵͳ�Զ�ɾ������Ϣ����������ڣ�ϵͳ�����κθĶ���\n");
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
		printf("�Ƿ����Ҫɾ���ÿ���ɾ������鼮��������Ϣ���޷��ָ���Y/N��\n");
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
			printf("�����������\n");
			getch();
			return 0;
		}
		else
		{
			printf("�����������\n");
			getch();
			return 0;
		}
	}
int addcar()//���ӽ��鿨
	{
		FILE *fp;
		int i=0,n;
		fp=fopen("car.txt","a+");
		system("CLS");
	printf("\n\n\n\n");
	printf("\t\t����������������������������������������������\n");
	printf("\t\t��                                          ��\n");
	printf("\t\t��               ¼���û���Ϣ               ��\n");
	printf("\t\t��                                          ��\n");
	printf("\t\t����������������������������������������������\n");
	printf("\n\t\t��������Ҫ¼���������");
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		printf("�������뿨��\n");
		scanf("%d",&car[i].carnum);
		printf("��������ѧ������\n");
		scanf("%s",car[i].studentname);
		printf("��������༶\n");
		scanf("%d",&car[i].studentclass);
		fwrite(&car[i],sizeof(struct car),1,fp);
	}
		fclose(fp);
		printf("������ϣ����������\n");
		getch();
		return 0;
	}
void carcount()//ͼ�鿨ͳ��
	{
		FILE *fp;
		int i,n=0;
		fp=fopen("car.txt","r");
		for(i=0;fread(&car[i],sizeof(struct car),1,fp)!=0;i++)
		{
			printf("��%d�ſ�<���ţ�%d ������%s �༶��%d>\n",i+1,car[i].carnum,car[i].studentname,car[i].studentclass);
			n=n+1;
		}
		fclose(fp);
		printf("Ŀǰ����%d������\n",n);
		printf("�������\n");
		getch();
	}
//����Ա������֤
int welcome()
{
	int num=3;             //ͳ���������
	int sign=2;            //��Ǵ�������
	char F_administor[40],F_passward[50];//��ȡ�ļ��д�����˻�������
    system("color 1F");
	printf("----------------------------------------------------------------------------\n");
    printf("|                                                                          |\n");
    printf("|                       ��ӭʹ�üƿ�׿Խͼ�����ϵͳ                       |\n");
    printf("|                                                                          |\n");
    printf("----------------------------------------------------------------------------\n");
	if((fpa=fopen("����Ա��Ϣ.txt","rt"))==NULL)
	{
		printf("�״�ʹ�ø�ϵͳ����ע�����Ա�˻�\n");  //�˻��������������
		fpa=fopen("����Ա��Ϣ.txt","wb+");
		printf("���������Ա�˺ţ�");
		scanf("%4s",administor);
		getchar();
		printf("���������룺");
		scanf("%4s",passward);
		getchar();
		if((fpa=fopen("����Ա��Ϣ.txt","wb+"))==NULL)
		{
			printf("ע��ʧ�ܣ��������Ժ�����\n");
			return 0;
		}
		else
		{
			fprintf(fpa,"%40s%50s",administor,passward);//������Ա�˻�����������ļ�
			fclose(fpa);
			printf("ע��ɹ����밴���������...");
			getch();
		}
		return 1;
	}
	fclose(fpa);
	if((fpa=fopen("����Ա��Ϣ.txt","rb"))==NULL) //��ֻ����ʽ���ļ����ж�����������Ƿ���ȷ
	{
		printf("�ļ���ʧ�ܣ����Ժ����ԣ���");
		return 0;
	}
	else
	{
		while(num)                              //�жϴ�������
		{
			if(sign==1)
			{
				printf("\n�ù���Ա�˻������ڣ�������%d���������\n",num);
			}
			else if(sign==0)
			{
				printf("\n�����������������%d���������\n",num);
			}
			printf("���������Ա�˺ţ�");
			scanf("%40s",administor);
			getchar();
			printf("���������룺");
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
		printf("������������������3�Σ���������˳�ϵͳ��\n");
		fclose(fpa);
		return 0;
	}
}
//�޸�����
void xiugaimima()
{
	char F_administor[40],F_passward[50],key1[50],key2[50],admin[40];//��ȡ�ļ��д�����˻�������
	printf("\n\n\n\n");
	printf("\t\t����������������������������������������������\n");
	printf("\t\t��                                          ��\n");
	printf("\t\t��                  �޸�����                ��\n");
	printf("\t\t��                                          ��\n");
	printf("\t\t����������������������������������������������\n");
	printf("\n");
	if((fpa=fopen("����Ա��Ϣ.txt","rt"))==NULL) //��ֻ����ʽ���ļ����ж�����������Ƿ���ȷ
        {
            printf("�ļ���ʧ�ܣ����Ժ����ԣ���");
        }
	while(1)
	{
	    printf("\t\t������ԭʼ���룺");
	    scanf("%50s",passward);
        getchar();
        fscanf(fpa,"%40s%50s",F_administor,F_passward);
        strcpy(admin,F_administor);
		if(strcmp(F_passward,passward)==0)
		{
			printf("\t�����������룺");
			scanf("%50s",key1);
			printf("\t���ٴ����������룺");
			scanf("%50s",key2);
			if(strcmp(key1,key2)==0)
			{
				printf("\t�����޸ĳɹ����˳�ϵͳ��Ч!!  ���������...");
                fpa=fopen("����Ա��Ϣ.txt","w");
				fprintf(fpa,"%40s%50s",admin,key1);
				fclose(fpa);
				getch();break;
			}
			else
			{
				printf("\t�������벻ͬ���޸�ʧ�ܣ�   ���������...");
				getch();
				break;
			}
		}
		else
		{
			printf("\t������� ���������...");
			getch();
			break;
		}
	}

}
//����ͼ����Ϣ��
void xinxi()
{
	FILE *fp;
	int i;
	fp=fopen("�ܵ�ͼ���¼�ļ�.txt","at");
	system("CLS");
	printf("\n\n\n\n");
	printf("\t\t����������������������������������������������\n");
	printf("\t\t��                                          ��\n");
	printf("\t\t��               ¼��ͼ����Ϣ               ��\n");
	printf("\t\t��                                          ��\n");
	printf("\t\t����������������������������������������������\n");
	printf("\n\t\t��������Ҫ¼���������");
	scanf("%d",&N);
	for(i=0;i<N;i++)
	{
		printf("\t\t�������%d����ı��:",i+1);
		scanf("%d",&bk[i].num);
		printf("\t\t�������%d���������:",i+1);
		scanf("%s",bk[i].name);
		printf("\t\t�������%d����ĳ�����:",i+1);
		scanf("%s",bk[i].publish);
		printf("\t\t�������%d����ĳ���ʱ��(��ʽ��:2011.5.1):",i+1);
		scanf("%d.%d.%d",&bk[i].t.year,&bk[i].t.month,&bk[i].t.day);
		printf("\t\t�����Ƿ��ѱ����ģ��ѱ�����������1��δ������������0��");
		scanf("%d",&bk[i].jie);
		printf("\t--------------------------------------------------------------------------\n");
		fwrite(&bk[i],sizeof(struct book),1,fp);
	}
	rewind(fp);
	fclose(fp);
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t����������������������������������������������\n");
	printf("\t\t��                                          ��\n");
	printf("\t\t��                ��Ϣ¼�����              ��\n");
	printf("\t\t��                                          ��\n");
	printf("\t\t����������������������������������������������\n");
	printf("\n\t\t�����������...");
}


//����Աģʽ
int adm()
{
	int x;
	printf("\n\n\n\n");
	printf("\t\t����������������������������������������������\n");
	printf("\t\t��                                          ��\n");
	printf("\t\t��                ����Աģʽ                ��\n");
	printf("\t\t��                                          ��\n");
	printf("\t\t����������������������������������������������\n");
	printf("\n");
	printf("\t\t\t\t1.¼��ͼ����Ϣ\n");
	printf("\t\t\t\t2.�鿴ͼ����Ϣ\n");
	printf("\t\t\t\t3.�޸Ļ�ɾ��ͼ��\n");
	printf("\t\t\t\t4.¼���û���Ϣ\n");
	printf("\t\t\t\t5.ɾ����Ϣ\n");
	printf("\t\t\t\t6.�û�ͳ��\n");
	printf("\t\t\t\t7.����ͳ��\n");
	printf("\t\t\t\t8.�޸Ĺ�������\n");
	printf("\t\t\t\t9.����\n");
	printf("\t\t\t\t10.����\n");
	printf("\t\t\t\t11.�˳�����Աģʽ\n");
	printf("\n\t\t����������ѡ��");
	scanf("%d",&x);
	return x;
}

//�鿴����ͼ��
void show_all_book()
{
	FILE *fp;
	int i;
	fp=fopen("�ܵ�ͼ���¼�ļ�.txt","r");
		printf("\t���\tͼ������\t������\t\t����ʱ��\t״̬\n");
		for(i=0;fread(&bk[i],sizeof(struct book),1,fp)!=0;i++)
		{
			    printf("\t%-7d %-8s	%-12s    %4d��%d��%d��",bk[i].num,bk[i].name,bk[i].publish,bk[i].t.year,bk[i].t.month,bk[i].t.day);
			if(bk[i].jie==0)
				printf("    δ����\n");
			else
				printf("    �ѽ���\n");
		}

	fclose(fp);
}
//�������鿴
void showbook_name()
{
	FILE *fp;
	int i,k=0,n;
	char book_name[20];
	fp=fopen("�ܵ�ͼ���¼�ļ�.txt","r");
	printf("\n\n\n\n");
	printf("\t\t����������������������������������������������\n");
	printf("\t\t��                                          ��\n");
	printf("\t\t��                 ��������ѯ               ��\n");
	printf("\t\t��                                          ��\n");
	printf("\t\t����������������������������������������������\n");
	printf("\n\t\t��������Ҫ�鿴��ͼ�����ƣ�");
	scanf("%s",book_name);
	for(i=0;fread(&bk[i],sizeof(struct book),1,fp)!=0;i++)
	{
		if(strcmp(book_name,bk[i].name)==0)
		{
			n=i;
			if(k==0)
				printf("\t���\tͼ������\t������\t\t����ʱ��\t״̬\n");
			    printf("\t%-7d %-8s	%-12s    %4d��%d��%d��",bk[n].num,bk[n].name,bk[n].publish,bk[n].t.year,bk[n].t.month,bk[n].t.day);
			if(bk[n].jie==1)
				printf("    �ѱ�����\n");
			else
				printf("    ���Խ���\n");
			printf("\t\t��ѯ�ɹ�!�����������...");
			k++;
		}
	}
	   fclose(fp);
		if(k==0)
			printf("\t\t�����ڸ�ͼ��!�����������...");

}
//����Ų鿴
void showbook_num()
{
	FILE *fp;
	int n,book_num,i,k=0;
	fp=fopen("�ܵ�ͼ���¼�ļ�.txt","r");
	printf("\n\n\n\n");
	printf("\t\t����������������������������������������������\n");
	printf("\t\t��                                          ��\n");
	printf("\t\t��                ����Ų鿴                ��\n");
	printf("\t\t��                                          ��\n");
	printf("\t\t����������������������������������������������\n");
	printf("\n\t\t��������Ҫ�鿴��ͼ���ţ�");
	scanf("%d",&book_num);
	for(i=0;fread(&bk[i],sizeof(struct book),1,fp)!=0;i++)
	{
		if(book_num==bk[i].num)
		{
			n=i;
			if(k==0)
				printf("\t���\tͼ������\t������\t\t����ʱ��\t״̬\n");
			    printf("\t%-7d %-8s	%-12s    %4d��%d��%d��",bk[n].num,bk[n].name,bk[n].publish,bk[n].t.year,bk[n].t.month,bk[n].t.day);
			if(bk[n].jie==1)
				printf("    �ѱ�����\n");
			else
				printf("    ���Խ���\n");
			k++;
			printf("\t\t�����������...");
		}
	}
	fclose(fp);
		if(k==0)
			printf("\t\t�����ڸ�ͼ�顣�����������...");
}
//��ʾȫ���ѽ���ͼ��
void yijieyue()
{
	FILE *fp;
	int i,k=0;
	fp=fopen("�ܵ�ͼ���¼�ļ�.txt","r");
		for(i=0;fread(&bk[i],sizeof(struct book),1,fp)!=0;i++)
		{
			if(bk[i].jie==1)
			{
				if(k==0)
				{
				printf("\t���\tͼ������\t������\t\t����ʱ��\n");
				}
			    printf("\n\t%-7d %-8s	%-12s    %4d��%d��%d��",bk[i].num,bk[i].name,bk[i].publish,bk[i].t.year,bk[i].t.month,bk[i].t.day);//???
				k++;
			}
		}
		fclose(fp);
			if(k==0)
				printf("\n\t\tĿǰû���κ������������������...");

}
//��ʾȫ��δ����ͼ��
void weijieyue()
{
	FILE *fp;
	int i,k=0;
	fp=fopen("�ܵ�ͼ���¼�ļ�.txt","r");

		for(i=0;fread(&bk[i],sizeof(struct book),1,fp)!=0;i++)
		{
			if(bk[i].jie==0)
			{
				if(k==0)
				{
				printf("\t���\tͼ������\t������\t\t����ʱ��\n");
				}
			    printf("\n\t%-7d %-8s	%-12s    %4d��%d��%d��",bk[i].num,bk[i].name,bk[i].publish,bk[i].t.year,bk[i].t.month,bk[i].t.day);//???
				k++;
			}
		}
		fclose(fp);
			if(k==0)
				printf("\n\t\t��ǸĿǰ���е��鶼�ѱ�����������������...");

}
//�鿴ͼ��˵�
void show()
{
	int x;
	do
	{
		system("cls");
		printf("\n\n\n\n");
		printf("\t\t����������������������������������������������\n");
		printf("\t\t��                                          ��\n");
		printf("\t\t��              �鿴ͼ����Ϣ                ��\n");
		printf("\t\t��                                          ��\n");
		printf("\t\t����������������������������������������������\n");
		printf("\n");
		printf("\t\t\t\t1.����������\n");
		printf("\t\t\t\t2.����Ų���\n");
		printf("\t\t\t\t3.�鿴����δ����ͼ��\n");
		printf("\t\t\t\t4.�鿴�����ѽ���ͼ��\n");
		printf("\t\t\t\t5.�鿴����ͼ��\n");
		printf("\t\t\t\t6.�������˵�\n");
		printf("\n\t\t����������ѡ��");
		scanf("%d",&x);
		switch(x)
		{
		case 1:system("cls");showbook_name();getch();break;//�������鿴
		case 2:system("cls");showbook_num();getch();break;//����Ų鿴
		case 3:system("cls");weijieyue();getch();break;//�鿴δ����ͼ��
		case 4:system("cls");yijieyue();getch();break;//�鿴�ѽ���ͼ��
		case 5:system("cls");show_all_book();getch();break;//�鿴����ͼ��
		}
	}while(x!=6);
}

//���������в��Ҳ��޸���Ϣ
void xiugai_name()
{
	FILE *fp,*fp2;
	int i,book_xb,k=0;
	char temp[20];
	fp=fopen("�ܵ�ͼ���¼�ļ�.txt","r");
	fp2=fopen("�м���ʱ�ļ�.txt","w");
	while(1)
	{
		system("cls");
		printf("\n\n\n\n");
		printf("\t\t����������������������������������������������\n");
		printf("\t\t��                                          ��\n");
		printf("\t\t��             �����������޸�               ��\n");
		printf("\t\t��                                          ��\n");
		printf("\t\t����������������������������������������������\n");
		printf("\n");
		printf("\n\t\t��������׼���޸ĵ�ͼ������ƣ�����'exit'�˳���");
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
					printf("\t�������ϢΪ��\n");
					printf("\t���\tͼ������\t������\t\t����ʱ��\t״̬\n");
				    printf("\t%-7d %-8s	%-12s    %4d��%d��%d��",bk[i].num,bk[i].name,bk[i].publish,bk[i].t.year,bk[i].t.month,bk[i].t.day);
					if(bk[book_xb].jie==1)
						printf("�ѱ�����\n");
					else
						printf("���Խ���\n");
					k++;
					printf("\t\t��������������Ϣ��\n");
					printf("\t\t�����뱾��ı�ţ�\n");
					scanf("%d",&bk[book_xb].num);
					printf("\t\t�����뱾������ƣ�\n");
					scanf("%s",bk[book_xb].name);
					printf("\t\t�����뱾��ĳ����磺\n");
					scanf("%s",bk[book_xb].publish);
					printf("\t\t�����뱾��ĳ���ʱ�䣨��2011,5,1����\n");
					scanf("%d,%d,%d",&bk[book_xb].t.year,&bk[book_xb].t.month,&bk[book_xb].t.day);
					printf("\t\t�����Ƿ��ѱ����ģ��ѱ���������1��δ����������0 ��");
					scanf("%d",&bk[book_xb].jie);
					fwrite(&bk[i],sizeof(struct book),1,fp2);
					continue;
				}
				fwrite(&bk[i],sizeof(struct book),1,fp2);
			}

			fclose(fp);
			fclose(fp2);
			fp=fopen("�ܵ�ͼ���¼�ļ�.txt","w");
	        fp2=fopen("�м���ʱ�ļ�.txt","r");
			for(i=0;fread(&bk[i],sizeof(struct book),1,fp2)!=0;i++)
			{
				 fwrite(&bk[i],sizeof(struct book),1,fp);
			}
			fclose(fp);
	    	fclose(fp2);
			fp2=fopen("bookl.txt","w");
			  if(k==0)
				{
					printf("\t\t����������������ڡ������������...");
					getch();
					continue;
				}
				printf("\t\t��ϲ����Ϣ�޸ĳɹ��������������...");
				getch();
				break;
		}
	}
}
//����Ž��в��Ҳ��޸���Ϣ
void xiugai_num()
{
	FILE *fp,*fp2;
	int i,book_xb,k=0;
	long temp;
	fp=fopen("�ܵ�ͼ���¼�ļ�.txt","r");
	fp2=fopen("�м���ʱ�ļ�.txt","w");
	do
	{
		system("cls");
		printf("\n\n\n\n");
		printf("\t\t����������������������������������������������\n");
		printf("\t\t��                                          ��\n");
		printf("\t\t��             ����Ž����޸�               ��\n");
		printf("\t\t��                                          ��\n");
		printf("\t\t����������������������������������������������\n");
		printf("\n");
		printf("\n\t\t��������׼���޸ĵ�ͼ�����ţ�����'0'�˳���");
		scanf("%ld",&temp);
		if(temp==0) break;
		else
		{
			for(i=0;fread(&bk[i],sizeof(struct book),1,fp)!=0;i++)
			{
				if(temp==bk[i].num)
				{
					book_xb=i;
					printf("\t�������ϢΪ��\n");
					printf("\t���\tͼ������\t������\t\t����ʱ��\t״̬\n");
				    printf("\t%-7d %-8s	%-12s    %4d��%d��%d��",bk[i].num,bk[i].name,bk[i].publish,bk[i].t.year,bk[i].t.month,bk[i].t.day);
					k++;
					if(bk[book_xb].jie==1)
						printf("    �ѱ�����\n");
					else
						printf("    ���Խ���\n");
					printf("\t\t��������������Ϣ��\n");
					printf("\t\t�����뱾��ı�ţ�\n");
					scanf("%d",&bk[book_xb].num);
					printf("\t\t�����뱾������ƣ�\n");
					scanf("%s",bk[book_xb].name);
					printf("\t\t�����뱾��ĳ����磺\n");
					scanf("%s",bk[book_xb].publish);
					printf("\t\t�����뱾��ĳ���ʱ�䣨��2011,5,1����\n");
					scanf("%d,%d,%d",&bk[book_xb].t.year,&bk[book_xb].t.month,&bk[book_xb].t.day);
					printf("\t\t�����Ƿ��ѱ����ģ��ѱ���������1��δ����������0 ��");
					scanf("%d",&bk[book_xb].jie);
					fwrite(&bk[i],sizeof(struct book),1,fp);
					continue;
				}
				fwrite(&bk[i],sizeof(struct book),1,fp);
			}
			fclose(fp);
			fclose(fp2);
			fp=fopen("�ܵ�ͼ���¼�ļ�.txt","w");
	        fp2=fopen("�м���ʱ�ļ�.txt","r");
			for(i=0;fread(&bk[i],sizeof(struct book),1,fp2)!=0;i++)
			{
				 fwrite(&bk[i],sizeof(struct book),1,fp);
			}
				if(k==0)
				{
					printf("\t\t����������������ڡ������������...");
					getch();
					continue;
				}
				printf("\t\t��ϲ����Ϣ�޸ĳɹ��������������...");
				getch();
				break;
		}
	}while(temp!=0);
}
//ɾ������ͼ��
void dele_all()
{

	char queren[4];
	printf("\n\n\n\n\t\t����������ɾ��������Ϣ���Ƿ������y ������n ����...");
	scanf("%s",queren);
	if(strcmp(queren,"y")==0)
	{
		fopen("�ܵ�ͼ���¼�ļ�.txt","w");
		printf("\t\tɾ���ɹ�\n");
	}
	else
	{
		printf("\t\t�������û�ȡ���������������...");
		getch();
	}
}
//������ɾ��
void dele_name()
{
	FILE *fp,*fp2;
	int i,book_xb,k=0,j;
	char queren[4],temp_name[20];
    fp=fopen("�ܵ�ͼ���¼�ļ�.txt","r");
	fp2=fopen("�м���ʱ�ļ�.txt","w");
	printf("\n\n\n\n\t\t��������Ҫɾ����������ƣ�����0�˳���");
	scanf("%s",temp_name);
	if(strcmp(temp_name,"0")!=0)
	{
		for(i=0;fread(&bk[i],sizeof(struct book),1,fp2)!=0;i++)
		{
			if(strcmp(temp_name,bk[i].name)==0)
			{
				book_xb=i;
				printf("\t\t�������ϢΪ��\n");
				printf("\t���\tͼ������\t������\t\t����ʱ��\t״̬\n");
			    printf("\t%-7d %-8s	%-12s    %4d��%d��%d��",bk[i].num,bk[i].name,bk[i].publish,bk[i].t.year,bk[i].t.month,bk[i].t.day);
				if(bk[i].jie==0)
					printf("    δ����\n");
				else
					printf("    �ѽ���\n");
				k++;
				printf("\t\t�Ƿ�Ҫɾ�����飿�� y���� n ��");
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
					fp=fopen("�ܵ�ͼ���¼�ļ�.txt","w");
                	fp2=fopen("�м���ʱ�ļ�.txt","r");
					for(j=0;fread(&bk[j],sizeof(struct book),1,fp2)!=0;j++)
                    {
						fwrite(&bk[i],sizeof(struct book),1,fp);
					}
					fclose(fp);
					fclose(fp2);
					fopen("�м���ʱ�ļ�.txt","r");
					printf("\t\tɾ���ɹ�\n");
				}
				else
					printf("\t\t�������û�ȡ���������������...");
			}
		}
			if(k==0)
				printf("\t\tδ�ҵ����飬���ʵ���ٲ����������������...");
			getch();
	}
}
//����Ų��Ҳ�ɾ��
void dele_num()
{
	FILE *fp,*fp2;
	int i,book_xb,k=0,temp_num,j;
	char queren[4];
	fp=fopen("�ܵ�ͼ���¼�ļ�.txt","r");
	fp2=fopen("�м���ʱ�ļ�.txt","w");
	while(1)
	{
		printf("\t\t������Ҫɾ���������ţ�����0���˳���");
		scanf("%d",&temp_num);
		if(temp_num==0) break;
		else
		{
			for(i=0;fread(&bk[i],sizeof(struct book),1,fp)!=0;i++)
			{
			   if(temp_num==bk[i].num)
			   {
				  book_xb=i;
				  printf("\t\t�������ϢΪ��\n");
				  printf("\t���\tͼ������\t������\t\t����ʱ��\t״̬\n");
			       printf("\t%-7d %-8s	%-12s    %4d��%d��%d��",bk[i].num,bk[i].name,bk[i].publish,bk[i].t.year,bk[i].t.month,bk[i].t.day);
				 if(bk[i].jie==0)
					printf("δ����\n");
				else
					printf("�ѽ���\n");
				k++;
				printf("\t\t�Ƿ�Ҫɾ�����飿�� y���� n ��");
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
					fp=fopen("�ܵ�ͼ���¼�ļ�.txt","w");
                	fp2=fopen("�м���ʱ�ļ�.txt","r");
					for(j=0;fread(&bk[j],sizeof(struct book),1,fp2)!=0;j++)
                    {
						fwrite(&bk[i],sizeof(struct book),1,fp);
					}
					fclose(fp);
					fclose(fp2);
					fopen("�м���ʱ�ļ�.txt","r");
					printf("\t\tɾ���ɹ�\n");
				}
				else
					printf("\t\t�������û�ȡ���������������...");
			}
          }
			if(k==0)
				printf("\t\tδ�ҵ����飬���ʵ���ٲ����������������...");
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
		printf("\t\t����������������������������������������������\n");
		printf("\t\t��                                          ��\n");
		printf("\t\t��               ɾ��ͼ����Ϣ               ��\n");
		printf("\t\t��                                          ��\n");
		printf("\t\t����������������������������������������������\n");
		printf("\n");
		printf("\t\t\t\t1.������ɾ��\n");
		printf("\t\t\t\t2.�����ɾ��\n");
		printf("\t\t\t\t3.ɾ������ͼ��\n");
		printf("\t\t\t\t4.�������˵�\n");
		printf("\n\t\t����������ѡ��");
		scanf("%d",&x);
		switch(x)
		{
		case 1:system("cls");dele_name();break;
		case 2:system("cls");dele_num();break;//
		case 3:system("cls");dele_all();getch();break;//
		}
	}while(x!=4);
}
//�޸�ͼ��
void xiugai()
{
	int x;
	do
	{
		system("cls");
		printf("\n\n\n\n");
		printf("\t\t����������������������������������������������\n");
		printf("\t\t��                                          ��\n");
		printf("\t\t��              �޸�ͼ����Ϣ                ��\n");
		printf("\t\t��                                          ��\n");
		printf("\t\t����������������������������������������������\n");
		printf("\n");
		printf("\t\t\t\t1.�������޸�\n");
		printf("\t\t\t\t2.������޸�\n");
		printf("\t\t\t\t3.ɾ��ͼ��\n");
		printf("\t\t\t\t4.�������˵�\n");
		printf("\n\t\t����������ѡ��");
		scanf("%d",&x);
		switch(x)
		{
		case 1:system("cls");xiugai_name();break;
		case 2:system("cls");xiugai_num();break;//
		case 3:system("cls");dele();break;//
		}
	}while(x!=4);
}
huanbook() /*���麯��*/
{
	FILE *fp,*fp2; /*���������ļ�ָ�룬fp2�����޸�����ʱ������ʱ�ļ��ã���ֹ�������ƻ�*/
	int i,n;
	int carnum;
	char lendbook[10];
	printf("����������Ŀ���\n");
	scanf("%d",&carnum);
	fp=fopen("car.txt","r"); /*��ȡ���ż�¼*/
	for(i=0;fread(&car[i],sizeof(struct car),1,fp)!=0;i++) /*forѭ���жϿ����Ƿ����*/
	{
		if(car[i].carnum==carnum) /*���Ŵ��ڣ�������һѭ��*/
			{
				n=i;
				fclose(fp);
				printf("��������Ҫ�����������\n");
				scanf("%s",lendbook);
				fp=fopen("record.txt","r");

				for(i=0;fread(&student[i],sizeof(struct student),1,fp)!=0;i++) /*�ж��Ƿ�������������*/
				{
					if(strcmp(student[i].lendbook,lendbook)==0) /*�����˸��飬������һѭ�������������ʾ*/
					{
						fclose(fp);
						fp=fopen("record.txt","r");
						fp2=fopen("bookl.txt","w");
						for(i=0;fread(&student[i],sizeof(struct student),1,fp)!=0;i++)
						{
							if(strcmp(student[i].lendbook,lendbook)==0)
							{
								continue; /*ɾ����������Ľ����¼*/
							}
							fwrite(&student[i],sizeof(struct student),1,fp2); /*д��ԭ��û������ļ�¼*/
						}
						fclose(fp);
						fclose(fp2);
						fp=fopen("record.txt","w");
						fp2=fopen("bookl.txt","r");
						for(i=0;fread(&student[i],sizeof(struct student),1,fp2)!=0;i++)
						{
							fwrite(&student[i],sizeof(struct student),1,fp); /*�������¼��Ϣд��*/
						}
						fclose(fp);
						fclose(fp2);
						fopen("bookl.txt","w"); /*����ʱ�ļ��ļ�¼*/
						fclose(fp2);
						fp=fopen("�ܵ�ͼ���¼�ļ�.txt","r");
						fp2=fopen("bookl.txt","w");
						for(i=0;fread(&bk[i],sizeof(struct book),1,fp)!=0;i++) /*����ļ�¼д����ʱ�ļ�����ֹ��Ϊ�޸���Ϣ�ƻ���ǰ�ļ�¼*/
						{
							if(i==n)
							{
								bk[i].jie=1;
								fwrite(&bk[i],sizeof(struct book),1,fp2); /*���������ԭ��״̬��Ϊ���˽��ĵ�*/
								continue;
							}
							fwrite(&bk[i],sizeof(struct book),1,fp2);
						}
						fclose(fp);
						fclose(fp2);
						fp=fopen("�ܵ�ͼ���¼�ļ�.txt","w");
						fp2=fopen("bookl.txt","r");
						for(i=0;fread(&bk[i],sizeof(struct book),1,fp2)!=0;i++)
						{
							fwrite(&bk[i],sizeof(struct book),1,fp); /*����ʱ�ļ�д��*/
						}
						fclose(fp);
						fclose(fp2);
						fopen("bookl.txt","w"); /*����ʱ�ļ�*/
						fclose(fp2);
						printf("������ϣ������������\n");
						getch();
						return 1;
					}
				}
				printf("��û�н��������飬���������\n"); /*������ʾ*/
				fclose(fp);
				getch();
				return 0;
			}
	}
	printf("ϵͳû�����Ŀ�,�����������\n"); /*������ʾ*/
	fclose(fp);
	getch();
	return 0;
}
lendbook()
	{
		FILE *fp,*fp2;
		int i,n;
		int carnum;
		printf("����������Ŀ���\n");
		scanf("%d",&carnum);
		fp=fopen("car.txt","r");
		for(i=0;fread(&car[i],sizeof(struct car),1,fp)!=0;i++)
		{
		   if(car[i].carnum==carnum)
		   {
			   n=i;
			   fclose(fp);
               printf("��������Ҫ���ĵ��������\n");
			   scanf("%s",student[n].lendbook);
			   fp=fopen("�ܵ�ͼ���¼�ļ�.txt","r");
			   for(i=0;fread(&bk[i],sizeof(struct book),1,fp)!=0;i++)
			   {
				   if(strcmp(bk[i].name,student[n].lendbook)==0)
				   {
					   if(bk[i].jie==1) {printf("�Բ��𣬴������˽�������������\n");fclose(fp);getch();return 0;}
				       else
	 				   fclose(fp);
					   fp=fopen("record.txt","a+");
					   student[n].carnum=carnum;
					   fwrite(&student[n],sizeof(struct student),1,fp);
					   fclose(fp);
 				       fp=fopen("�ܵ�ͼ���¼�ļ�.txt","r");
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
				       fp=fopen("�ܵ�ͼ���¼�ļ�.txt","w");
					   fp2=fopen("bookl.txt","r");
					   for(i=0;fread(&bk[i],sizeof(struct book),1,fp2)!=0;i++)
					   {
						   fwrite(&bk[i],sizeof(struct book),1,fp);
					   }
				       fclose(fp);
				       fclose(fp2);
				       fopen("bookl.txt","w");
				       fclose(fp2);
					   printf("������ϣ������������\n");
					   getch();
					   return 0;
				   }
			   }
			   printf("�������������飬���������\n");
			   fclose(fp);
			   getch();
			   return 0;
		   }
		}
		printf("��Ŀ��Ų����ڣ��������¿�,�����������\n");
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

		   printf("���ţ�%d ������鼮��%s \n",student[i].carnum,student[i].lendbook);
		   n=n+1;
		}
		fclose(fp);
		printf("Ŀǰ����%d������\n",n);
		printf("�������\n");
		getch();
		return n;
	}
//���˵�
int mymainmenu()
{
	int x;
	printf("\n\n\n\n");
	printf("\t\t����������������������������������������������\n");
	printf("\t\t��                                          ��\n");
	printf("\t\t��            ��ӭʹ��ͼ�����ϵͳ          ��\n");
	printf("\t\t��                                          ��\n");
	printf("\t\t����������������������������������������������\n");
	printf("\n\t\t\t\t1.����Ա��½\n");
	printf("\t\t\t\t2.����ģʽ\n");
	printf("\t\t\t\t3.�˳�ϵͳ\n");
	printf("\n\t\t����������ѡ��");
	scanf("%d",&x);
	return x;
}
//������
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
		case 1://���ù���Աģʽ����
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
					printf("\n\t\t�������!!\t�����������...");
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
	    printf("\t\t����������������������������������������������\n");
	    printf("\t\t��                                          ��\n");
	    printf("\t\t��            �˳��ɹ���ллʹ��!           ��\n");
	    printf("\t\t��                                          ��\n");
	    printf("\t\t����������������������������������������������\n");
}
