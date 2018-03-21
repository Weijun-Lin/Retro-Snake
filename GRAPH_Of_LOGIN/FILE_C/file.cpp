#include"file.h"

typedef struct user
{
	char ID[20] = "";
	char PWD[20] = "";
}USER;

void PutPwd(char* p)
{
	int i = 0;
	for (i = 0; i < 20; i++)
	{
		p[i] = _getch();
		while (true)
		{
			if (p[i] == '\b'&&i >= 0)
			{
				printf("\b \b");
				if (i != 0) i--;
				p[i] = _getch();

			}
			else break;
		}
		if (p[i] == '\r'&&i >= 0) break;
		else
		{
			if (i >= 0) printf("*");
		}
	}
	p[i] = '\0';
	printf("\n");
}

void CreatFile()
{
	FILE* fp;
	if((fp = fopen("user.txt","rb"))==NULL)
	{
		if((fp = fopen("user.txt","wb"))==NULL)
		{
			printf("打开文件失败\n\n");
		}
	}
}

int Register()
{
	USER a,b;
	FILE* fp;
	char again[20];
	lable1:
	printf("请输入您的账号:\n\n");
	scanf("%s",a.ID);
	fp = fopen("user.txt","r");
	fread(&b,sizeof(USER),1,fp);
	while(true)
	{
		if(strcmp(b.ID,a.ID))                            //如果两者不相等 
		{	
			if(!feof(fp)) fread(&b,sizeof(USER),1,fp);
			else break;   //如果未到末尾则继续读 
		}
		else
		{
			printf("此用户名已存在\n请重新输入\n\n");
			fclose(fp);
			goto lable1;
		}
	}
	lable2:
	printf("请输入密码:\n\n");
	PutPwd(a.PWD);
	printf("请在输入您的密码:\n\n");
	PutPwd(again);
	if(strcmp(a.PWD,again)) 
	{
		printf("密码不一致，请重新输入\n\n");
		goto lable2;
	}
	else 
	{
		fclose(fp);
		fp = fopen("user.txt","a");
		fwrite(&a,sizeof(USER),1,fp);
		fclose(fp);
		printf("用户%s注册成功o(*￣▽￣*)o\n\n",a.ID);
	}
	return true;
}

int Login()
{
	USER a,b;
	FILE* fp;
	lable1:
	fp = fopen("user.txt","r");
	printf("请输入用户名:\n\n");
	scanf("%s",a.ID);
	fread(&b,sizeof(USER),1,fp);
	while(true)
	{
		if(strcmp(a.ID,b.ID)==0) break;
		else
		{
			if(!feof(fp)) fread(&b,sizeof(USER),1,fp);
			else 
			{
				printf("用户名不存在请重新输入\n\n");
				fclose(fp);
				goto lable1;
			}
		}
	}
	lable2:
	printf("请输入密码：\n\n");
	PutPwd(a.PWD);
	if(strcmp(a.PWD,b.PWD)==0)
	{
		printf("登陆成功O(∩_∩)O\n\n");
		fclose(fp);
		return true;
	}
	else
	{
		printf("密码输入错误！\n请重新输入\n\n");
		goto lable2;
	}
}

void PrintAllID()
{
	FILE* fp = fopen("user.txt","r");
	USER a;
	fread(&a,sizeof(USER),1,fp);
	while(!feof(fp))
	{
		printf("%s\n",a.ID);
		fread(&a,sizeof(USER),1,fp);
	}
	fclose(fp);
}

int ClearFile()
{
	FILE* fp = fopen("user.txt", "w");
	if (fp == NULL)
	{
		printf("error\n\n");
		return false;
	}
	else return true;
}

