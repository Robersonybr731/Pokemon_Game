#ifndef BAG_H
#define BAG_H
#include"NPC.h"
class bag
{
public:
	bag()
	{
		for (int i = 0; i < 4; i++)
			bag_Pokemons_num[i] = 0; //初始化
		assign_Pokemon(); //安裝成vector<monster>型態
	}
	~bag(){}
	int get_Pokemons_num(int i) {return bag_Pokemons_num[i];}//取得這個位置的寶可夢編號
	void set_BagPokemons_num(int Pokemon_num) //背包沒滿,直接把編號放進去
	{
		for (int i = 1; i < 4; i++)
		{
			if (bag_Pokemons_num[i] == 0)
			{
				bag_Pokemons_num[i] = Pokemon_num;
				return;
			}
		}
	}
	void set_BagPokemons_num_Full(int i, int pokemon_num) //背包滿了,指定位置把寶可夢放到背包
	{
		bag_Pokemons_num[i] = pokemon_num;
	}
	bool configure_Full() //確認背包滿了沒
	{
		int record = 0;
		for (int i = 1; i < 4; i++)
			if (bag_Pokemons_num[i] != 0)
				record++;
		if (record == 3)
			return true; //滿了
		return false; //沒滿
	}
	void assign_bag(bag &left) //安裝背包
	{
		for (int i = 1; i < 4; i++)
			left.bag_Pokemons_num[i] = bag_Pokemons_num[i];
	}
	int get_substitute() //取得要替換的位置
	{
		show_having_pokemon(); //展示所有寶可夢的名字
		string k;
		while (1)
		{
			k = getkey();
			if (k == "1")
				return 1;
			else if (k == "2")
				return 2;
			else if (k == "3")
				return 3;
		}
	}
	string get_Pokempn_name(int pokemon_num) //得到寶可夢的名字
	{
		return Pokemon_Inquiry.get_Name(pokemon_num);
	}
	void show_having_pokemon() //展示所有寶可夢的名字
	{
		setColor(15);
		for (int i = 0; i < 20; i++)
		{
			locate(63+i, 24);
			cout << "*";
			locate(63 + i, 29);
			cout << "*";
		}
		for (int i = 0; i < 5; i++)
		{
			locate(63, 25 + i);
			cout << "*";
			locate(82, 25 + i);
			cout << "*";
		}
		setColor(LIGHTCYAN);
		for (int i = 1; i < 4; i++)
		{
			locate(65, 25 + i);
			cout << i << ". " << Pokemon_Inquirys[bag_Pokemons_num[i]].Name;
		}
		resetColor();
	}
	void assign_Pokemon() //安裝寶可夢(內部使用)
	{
		Pokemon_Inquiry.assign_Pokemon_Infos(Pokemon_Inquirys);
	}
private:
	int bag_Pokemons_num[4]; //存背包寶可夢的編號(從[1]開始算)
	Pokemon Pokemon_Inquiry;
	vector<monster> Pokemon_Inquirys;
};
#endif // !BAG_H
