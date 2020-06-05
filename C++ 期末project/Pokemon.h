#ifndef POKEMON_H
#define POKEMON_H
#include<string>
#include<iostream>
#include<vector>
#include<sstream>
#include"rlutil.h"

using namespace std;
using namespace rlutil;

struct monster
{
	string No;
	string Name;
	string Type;
	int HP;
	int ATK;
	int DEF;
	int Speed;
	int Ability;
};


class Pokemon
{
public:
	Pokemon() { load_information(); } //constructor
	~Pokemon() {} //destructor
	monster get_monster(int i) { return Pokemon_infos[i]; }//return 這個位置的寶可夢(monster型態)
	string get_Name(int i) { return Pokemon_infos[i].Name; } //return 這個位置的寶可夢名稱
	string get_No(int i) { return Pokemon_infos[i].No; } //return 這個位置的寶可夢編號
	string get_type(int i) { return Pokemon_infos[i].Type; } //return 這個位置的寶可夢屬性
	int get_HP(int i) { return Pokemon_infos[i].HP; } //return 這個位置的寶可夢血量
	int get_ATK(int i) { return Pokemon_infos[i].ATK; } //return 這個位置的寶可夢攻擊值
	int get_DEF(int i) { return Pokemon_infos[i].DEF; } //return 這個位置的寶可夢防禦值
	int get_Speed(int i) { return Pokemon_infos[i].Speed; } //return 這個位置的寶可夢速度
	int get_Ability(int i) { return Pokemon_infos[i].Ability; } //return 這個位置的寶可夢技能編號
	int get_size() { return Pokemon_infos.size(); }
	void assign_Pokemon_Infos(vector<monster> &left) { left = Pokemon_infos; }
	void load_information() //讀進所有寶可夢的能力值
	{
		ifstream inFile;
		inFile.open("pokemons.csv");
		monster Pokemon_info;
		string HP, ATK, DEF, Speed, Ability;
		while (getline(inFile, Pokemon_info.No, ','))
		{
			getline(inFile, Pokemon_info.Name, ',');
			getline(inFile, Pokemon_info.Type, ',');
			getline(inFile, HP, ',');
			getline(inFile, ATK, ',');
			getline(inFile, DEF, ',');
			getline(inFile, Speed, ',');
			getline(inFile, Ability, '\n');
			istringstream is1(HP);
			istringstream is2(ATK);
			istringstream is3(DEF);
			istringstream is4(Speed);
			istringstream is5(Ability);
			is1 >> Pokemon_info.HP;
			is2 >> Pokemon_info.ATK;
			is3 >> Pokemon_info.DEF;
			is4 >> Pokemon_info.Speed;
			is5 >> Pokemon_info.Ability;
			Pokemon_infos.push_back(Pokemon_info);
		}
		monster Nothing;
		Pokemon_infos.insert(Pokemon_infos.begin(), Nothing); //故意空一格
	}
	void show_pokemon() //展示所有的值 (測試用)
	{
		for (int i = 0; i < Pokemon_infos.size(); i++)
		{
			cout << Pokemon_infos[i].No << " ";
			cout << Pokemon_infos[i].Name << " ";
			cout << Pokemon_infos[i].Type << " ";
			cout << Pokemon_infos[i].HP << " ";
			cout << Pokemon_infos[i].ATK << " ";
			cout << Pokemon_infos[i].DEF << " ";
			cout << Pokemon_infos[i].Speed << " ";
			cout << Pokemon_infos[i].Ability << " ";
			cout << endl;
		}
	}
private:
	vector<monster> Pokemon_infos; //所有寶可夢的值
};
#endif // !POKEMON_H
