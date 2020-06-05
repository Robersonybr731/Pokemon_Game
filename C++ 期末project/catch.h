#ifndef CATCH_H
#define CATCH_H
#include<iostream>
#include<vector>
#include"bag.h"

using namespace std;
class catching
{
public:
	catching() {}
	~catching() {}
	int get_catch_selection() //選擇抓或不抓
	{
		setColor(YELLOW);
		locate(51, 35);
		cout << "Please input value to determine which action !";
		locate(58, 36);
		cout << "1. Catching";
		locate(77, 36);
		cout << "2. Give up\n";
		while (1)
		{
			char k = getkey();
			if (k == '1')
				return 1;
			else if (k == '2')
				return 2;
		}
		resetColor();
	}
	void captural_Interface(int pokemon_num, vector<monster> &pokemons) //顯示抓寶介面
	{
		cls();
		display_pokemon(pokemon_num,25); //展示圖案
		setColor(YELLOW);
		locate(81, 5);
		cout << "NO. " << pokemons[pokemon_num].No;
		locate(81, 7);
		cout << "Name: " << pokemons[pokemon_num].Name;
		locate(81, 9);
		cout << "TYPE: " << pokemons[pokemon_num].Type;
		locate(81, 11);
		cout << "HP: " << pokemons[pokemon_num].HP;
		locate(81, 13);
		cout << "ATK: " << pokemons[pokemon_num].ATK;
		locate(81, 15);
		cout << "DEF: " << pokemons[pokemon_num].DEF;
		locate(81, 17);
		cout << "SPEED: " << pokemons[pokemon_num].Speed;
		locate(81, 19);
		cout << "Ability: " << pokemons[pokemon_num].Ability;
		setColor(LIGHTCYAN);
		locate(65, 25);
		cout << "Have Pokemon: ";
		show_having_pokemon();
		resetColor();
	}
	void show_having_pokemon() //展示所有擁有的寶可夢
	{
		catcher_bag.show_having_pokemon();
	}
	void show_escape_messages(int pokemon_num) //顯示逃跑訊息
	{
		locate(51, 32);
		setColor(DARKGREY);
		cout << catcher_bag.get_Pokempn_name(pokemon_num)<<" Escape ◢▆▅▄▃崩╰(〒皿〒)╯潰▃▄▅▇◣" << endl;
		resetColor();
	}
	void assign_bag(bag &right) //copy Pokemon
	{
		right.assign_bag(catcher_bag);
	}
	void display_pokemon(int pokemon_num,int x) //把圖示展現出來(抓寶)
	{
		string graph;
		string txt_num;
		stringstream num;
		num << pokemon_num;
		num >> txt_num;
		if (pokemon_num < 10)
			txt_num = "0" + txt_num;
		graph = "assets/icons/color/0" + txt_num + ".txt";
		ifstream inFile(graph, ios::in);
		string pokemon;
		for (int i = 0; getline(inFile, pokemon); i++)
		{
			locate(x, 1 + i);
			cout << pokemon;
		}
	}
	void display_pokemons(int pokemon_num1,int pokemon_num2) //圖示展現出來(戰鬥時呼叫)
	{
		string graph;
		string txt_num;
		stringstream num;
		num << pokemon_num1;
		num >> txt_num;
		if (pokemon_num1 < 10)
			txt_num = "0" + txt_num;
		graph = "assets/icons/color/0" + txt_num + ".txt";
		ifstream inFile(graph, ios::in);
		string pokemon;
		for (int i = 0; getline(inFile, pokemon); i++)
		{
			locate(20, 1 + i);
			cout << pokemon;
		}
		display_pokemon(pokemon_num2,75);
	}
	bool get_catch_success(int i)
	{
		int selection = rand() % 2; //50%機率可以抓到
		if (selection == 0)
			return false;
		else if (selection == 1)
			return true;
	}
private:
	bag catcher_bag;
};
#endif // !CATCH_H
