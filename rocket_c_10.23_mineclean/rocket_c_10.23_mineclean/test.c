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
	menu();//��ӡ�˵�
	scanf("%d", &select);//ѡ����Ϸ���
	switch (select)
	{
	case 1:
		game();
		break;
	case 2:
		exit(0);//�˳��ɹ�
		break;
	default:
		break;
	}
	system("pause");
	return 0;
}