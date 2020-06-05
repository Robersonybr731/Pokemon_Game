#include"player.h"
#include"time.h"
extern int values[35][6];  //34隻寶可夢的屬性
extern const char *types[19] = { "","Normal","Fire","Water","Electric","Grass","Ice","Fighting","Poison","Ground",
						   "Flying","Psychic","Bug","Rock","Ghost","Dragon","Dark","Steel","Fairy" }; //屬性名稱
extern double type_num[19][19]; //抗性倍率
void load(); //讀抗性倍率

int main()
{
	hidecursor(); //隱藏指標
	saveDefaultColor(); //預設顏色(白色)
	srand(time(NULL));
	load(); //讀抗性倍率
	Pokemon information;
	for (int i = 1; i < 35; i++)
	{
		values[i][0] = 0;
		values[i][1] = information.get_HP(i);
		values[i][2] = information.get_ATK(i);
		values[i][3] = information.get_DEF(i);
		values[i][4] = information.get_Speed(i);
		values[i][5] = information.get_Ability(i);
		
	}
	Player player;
	player.run();
}

void load()
{
	ifstream inFile;
	inFile.open("type.csv");
	string value;
	for (int i = 1; i < 19; i++)
	{
		for (int j = 1; j < 19; j++)
		{
			if (j == 18)
				getline(inFile, value, '\n');
			else
				getline(inFile, value, ',');
			istringstream is1(value);
			is1 >> type_num[i][j];
		}
	}
}