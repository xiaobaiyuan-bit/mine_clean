#include "mine.h"

//����
void mineput(char mineboard[][COLS], int rows, int cols)
{
	int x, y;
	static int num = 1;
	srand((unsigned long)time(NULL));//����һ������
	int minenum = MAX_MINE;//��������ΪMAX_MINE
	while (minenum)
	{
		if (!num)//num��0��ִ��//��ֹ��һ�ξ͵㵽����
		{
			mineboard[rows][cols] = '0';
			for (x = 1; x <= ROWS - 2; x++)
			{
				for (y = 1; y <= COLS - 2; y++)
				{
					if ((mineboard[x][y] == '0') && ((x != rows) || (y != cols)))
					{
						mineboard[x][y] = '1';//��=��==һ��Ҫ���⵱�ģ���������
						break;
					}
				}
				break;
			}
			break;
		}
		x = (rand() % (rows - 2) + 1);//���׵�ʱ��ע�⣺����ʼ��С������-2 ����(rows-2)
		y = (rand() % (cols - 2) + 1);//����Ҳ��һ����
		if (mineboard[x][y] != '1')
		{
			mineboard[x][y] = '1';
			minenum--;
		}
	}
	num--;
}

//��ӡ���̺�������ʾ�Ͳ���ʾ�������̶�ʹ�øú���
void show(char board[][COLS], int rows, int cols)
{
	int i = 0;
	int j = 0;
	printf("   ");
	for (i = 1; i <= cols - 2; i++)
	{
		printf("%2d", i);
	}
	printf("\n");
	printf("----");
	for (i = 1; i <= cols - 2; i++)
	{
		printf("--");
	}
	printf("\n");
	//�����Ǵ�ӡ�����̵�����ָʾ����ռ�����̿ռ�
	//���濪ʼ�ӵ�1�д�ӡ������ָʾ��ռ�����̿ռ䣬��*��ʼռ�����̿ռ�
	for (i = 1; i <= rows - 2; i++)
	{
		printf("%2d|", i);
		for (j = 1; j <= cols - 2; j++)
		{
			printf("%2c", board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

static int total(char mineboard[][COLS], int x, int y)
{
	int count = 0;
	if (mineboard[x - 1][y - 1] == '1')
	{
		count++;
	}
	if (mineboard[x - 1][y] == '1')
	{
		count++;
	}
	if (mineboard[x - 1][y + 1] == '1')
	{
		count++;
	}
	if (mineboard[x][y - 1] == '1')
	{
		count++;
	}
	if (mineboard[x][y + 1] == '1')
	{
		count++;
	}
	if (mineboard[x + 1][y - 1] == '1')
	{
		count++;
	}
	if (mineboard[x + 1][y] == '1')
	{
		count++;
	}
	if (mineboard[x + 1][y + 1] == '1')
	{
		count++;
	}
	return count;
}

//total_itoa() ͳ���׵ĸ�����������ת��Ϊ��Ӧ���ַ� //5 -> '5'
void total_itoa(char mineboard[][COLS], char showboard[][COLS], int x, int y)
{
	int tmp = total(mineboard, x, y);//ͳ����Χ�׵ĸ���
	//5 -> '5'
	char buff[10] = { 0 };
	itoa(tmp, buff, 10);//����Ҫ����//5 -> '5'
	showboard[x][y] = *buff;
}


//������չ
void LongExplode1(char mineboard[][COLS], char showboard[][COLS], int x, int y)
{
	if ((mineboard[x][y - 1] == '1') || (y <= 1))
	{
		return;
	}
	else
	{
		total_itoa(mineboard, showboard, x, y - 1);
		LongExplode1(mineboard, showboard, x, y - 1);//�������
	}
}

void LongExplode2(char mineboard[][COLS], char showboard[][COLS], int x, int y)
{
	if (mineboard[x - 1][y] == '1' || (x <= 1))
	{

		return;
	}
	else
	{
		total_itoa(mineboard, showboard, x - 1, y);
		LongExplode2(mineboard, showboard, x - 1, y);//�����ϱ�
	}
}

void LongExplode3(char mineboard[][COLS], char showboard[][COLS], int x, int y)
{
	if (mineboard[x][y + 1] == '1' || (y >= COLS - 2))
	{

		return;
	}
	else
	{
		total_itoa(mineboard, showboard, x, y + 1);
		LongExplode3(mineboard, showboard, x, y + 1);//�����ұ�
	}
}

void LongExplode4(char mineboard[][COLS], char showboard[][COLS], int x, int y)
{
	if (mineboard[x + 1][y] == '1' || (x >= ROWS - 2))
	{
		return;
	}
	else
	{
		total_itoa(mineboard, showboard, x + 1, y);
		LongExplode4(mineboard, showboard, x + 1, y);//�����±�
	}
}

int play(char mineboard[][COLS], char showboard[][COLS], int rows, int cols/*, int *NoMine*/)
{
	int x, y;
	int i = 0;
	int j = 0;
	static int count = 0;
	while (1)
	{
		printf("please select<x,y>: ");
		scanf("%d%d", &x, &y);
		count++;
		system("cls");//����������̨��
		if ((x > 0) && (x <= rows - 2) && ((y > 0) && (y <= cols - 2)))
		{
			if (showboard[x][y] == '*')//��ֹ��һ�Ѿ��ж��ظ���ͬһ����
			{
				if (mineboard[x][y] != '1')
				{
					total_itoa(mineboard, showboard, x, y);
					LongExplode1(mineboard, showboard, x, y);
					LongExplode2(mineboard, showboard, x, y);
					LongExplode3(mineboard, showboard, x, y);
					LongExplode4(mineboard, showboard, x, y);
					for (x = 1; x <= ROWS - 2; x++)
					{
						for (y = 1; y <= COLS - 2; y++)
						{
							if (showboard[x][y] == '*')
							{
								i++;
							}
						}
					}
					if (i == MAX_MINE)
					{
						return 0;
					}
					//(*NoMine)--;//����ע��Ҫ�������ţ�������ǵ�ַ��1
					//return *NoMine;
					return 1;
				}
				else if (count == 1)
				{
					mineput(mineboard, x, y);//��һ�δ��ף����²���
					total_itoa(mineboard, showboard, x, y);
					LongExplode1(mineboard, showboard, x, y);
					LongExplode2(mineboard, showboard, x, y);
					LongExplode3(mineboard, showboard, x, y);
					LongExplode4(mineboard, showboard, x, y);
					return 1;
				}
				else
				{
					return -1;
				}
			}
			else
			{
				printf("Re-enter, try again\n");
			}
		}
		else
		{
			printf("Enter Error, try again!>\n");
		}
	}
}

void game()//����Ϸ
{
	//�������̣�'0'��ȫ '1'��  '*'�����׵��ַ���
	char mineboard[ROWS][COLS] = { 0 };//����ʾ������
	char showboard[ROWS][COLS] = { 0 };//��ʾ������
	//��ʼ������
	memset(mineboard, '0', sizeof(mineboard));//����������Ŀ��ռ�  ��ʼ����~  Ҫ��ʼ���Ŀռ��ֽڴ�С    
	memset(showboard, '*', sizeof(showboard));
	//����
	mineput(mineboard, ROWS, COLS);
	//int NoMine = ((ROWS - 2) * (COLS - 2) - MAX_MINE);//ע�⴫��ʱҪ��������ַ��
	//���򵱵��ú�������ʱ���ñ�������û���κθı䡣
	while (1)
	{
		//��ӡ����
		//show(mineboard, ROWS, COLS);
		show(showboard, ROWS, COLS);
		//��ʼ����Ϸ
		int ret = play(mineboard, showboard, ROWS, COLS/*, &NoMine*/);
		if (ret > 0)
		{
			;
		}
		else if (0 == ret)
		{
			printf("you win!!!\n");
			show(mineboard, ROWS, COLS);
			break;
		}
		else
		{
			printf("Explode !!!\n");
			show(mineboard, ROWS, COLS);
			break;
		}
	}
}