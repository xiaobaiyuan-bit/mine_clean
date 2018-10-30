#include "mine.h"


void menu()
{
	printf("***** mine-clean *****\n");
	printf("**********************\n");
	printf("***1.play   2.exit ***\n");
	printf("**********************\n");
	printf(" Enter your select<1,2>: ");
}

int main()
{
	int select = 0;
	menu();//打印菜单
	scanf("%d", &select);//选择游戏与否
	switch (select)
	{
	case 1:
		game();
		break;
	case 2:
		exit(0);//退出成功
		break;
	default:
		break;
	}
	system("pause");
	return 0;
}