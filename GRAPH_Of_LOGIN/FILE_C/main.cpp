#include"file.h"
#include<stdio.h>
int main()
{
	char c;
	CreatFile();
	printf("您需要注册还是登陆:\n注册请输入1\n登陆请输入2\n预览所有用户名3\n退出0\n清空4\n\n");
	while ((c = getchar()) != '0')
	{
		if (c == '1') Register();
		if (c == '2') Login();
		if (c == '3') PrintAllID();
		if (c == '4')
		{
			if (!ClearFile())
			{
				printf("清空失败\n\n");
				break;
			}
		}
	}
	system("pause");
	return 0;
}
