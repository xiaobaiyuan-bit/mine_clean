#include "mine.h"

//布雷
void mineput(char mineboard[][COLS], int rows, int cols)
{
	int x, y;
	static int num = 1;
	srand((unsigned long)time(NULL));//定义一个种子
	int minenum = MAX_MINE;//定义雷数为MAX_MINE
	while (minenum)
	{
		if (!num)//num是0才执行//防止第一次就点到雷了
		{
			mineboard[rows][cols] = '0';
			for (x = 1; x <= ROWS - 2; x++)
			{
				for (y = 1; y <= COLS - 2; y++)
				{
					if ((mineboard[x][y] == '0') && ((x != rows) || (y != cols)))
					{
						mineboard[x][y] = '1';//对=和==一定要格外当心！！！！！
						break;
					}
				}
				break;
			}
			break;
		}
		x = (rand() % (rows - 2) + 1);//布雷的时候注意：余数始终小于行数-2 即：(rows-2)
		y = (rand() % (cols - 2) + 1);//列数也是一样的
		if (mineboard[x][y] != '1')
		{
			mineboard[x][y] = '1';
			minenum--;
		}
	}
	num--;
}

//打印雷盘函数，显示和不显示的两个盘都使用该函数
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
	//上面是打印了雷盘的坐标指示，不占用雷盘空间
	//下面开始从第1行打印，坐标指示不占用雷盘空间，但*开始占用雷盘空间
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

//total_itoa() 统计雷的个数并将整形转换为相应的字符 //5 -> '5'
void total_itoa(char mineboard[][COLS], char showboard[][COLS], int x, int y)
{
	int tmp = total(mineboard, x, y);//统计周围雷的个数
	//5 -> '5'
	char buff[10] = { 0 };
	itoa(tmp, buff, 10);//真重要啊！//5 -> '5'
	showboard[x][y] = *buff;
}


//向外扩展
void LongExplode1(char mineboard[][COLS], char showboard[][COLS], int x, int y)
{
	if ((mineboard[x][y - 1] == '1') || (y <= 1))
	{
		return;
	}
	else
	{
		total_itoa(mineboard, showboard, x, y - 1);
		LongExplode1(mineboard, showboard, x, y - 1);//遍历左边
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
		LongExplode2(mineboard, showboard, x - 1, y);//遍历上边
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
		LongExplode3(mineboard, showboard, x, y + 1);//遍历右边
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
		LongExplode4(mineboard, showboard, x + 1, y);//遍历下边
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
		system("cls");//清屏（控制台）
		if ((x > 0) && (x <= rows - 2) && ((y > 0) && (y <= cols - 2)))
		{
			if (showboard[x][y] == '*')//防止第一把就判定重复走同一坐标
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
					//(*NoMine)--;//这里注意要带上括号，否则就是地址减1
					//return *NoMine;
					return 1;
				}
				else if (count == 1)
				{
					mineput(mineboard, x, y);//第一次触雷，重新布雷
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

void game()//玩游戏
{
	//定义雷盘（'0'安全 '1'雷  '*'隐藏雷的字符）
	char mineboard[ROWS][COLS] = { 0 };//不显示的雷盘
	char showboard[ROWS][COLS] = { 0 };//显示的雷盘
	//初始化雷盘
	memset(mineboard, '0', sizeof(mineboard));//三个参数：目标空间  初始化成~  要初始化的空间字节大小    
	memset(showboard, '*', sizeof(showboard));
	//布雷
	mineput(mineboard, ROWS, COLS);
	//int NoMine = ((ROWS - 2) * (COLS - 2) - MAX_MINE);//注意传参时要传变量地址，
	//否则当调用函数返回时，该变量内容没有任何改变。
	while (1)
	{
		//打印雷盘
		//show(mineboard, ROWS, COLS);
		show(showboard, ROWS, COLS);
		//开始玩游戏
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