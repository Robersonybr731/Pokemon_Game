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
	monster get_monster(int i) { return Pokemon_infos[i]; }//return �o�Ӧ�m���_�i��(monster���A)
	string get_Name(int i) { return Pokemon_infos[i].Name; } //return �o�Ӧ�m���_�i�ڦW��
	string get_No(int i) { return Pokemon_infos[i].No; } //return �o�Ӧ�m���_�i�ڽs��
	string get_type(int i) { return Pokemon_infos[i].Type; } //return �o�Ӧ�m���_�i���ݩ�
	int get_HP(int i) { return Pokemon_infos[i].HP; } //return �o�Ӧ�m���_�i�ڦ�q
	int get_ATK(int i) { return Pokemon_infos[i].ATK; } //return �o�Ӧ�m���_�i�ڧ�����
	int get_DEF(int i) { return Pokemon_infos[i].DEF; } //return �o�Ӧ�m���_�i�ڨ��m��
	int get_Speed(int i) { return Pokemon_infos[i].Speed; } //return �o�Ӧ�m���_�i�ڳt��
	int get_Ability(int i) { return Pokemon_infos[i].Ability; } //return �o�Ӧ�m���_�i�ڧޯ�s��
	int get_size() { return Pokemon_infos.size(); }
	void assign_Pokemon_Infos(vector<monster> &left) { left = Pokemon_infos; }
	void load_information() //Ū�i�Ҧ��_�i�ڪ���O��
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
		Pokemon_infos.insert(Pokemon_infos.begin(), Nothing); //�G�N�Ť@��
	}
	void show_pokemon() //�i�ܩҦ����� (���ե�)
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
	vector<monster> Pokemon_infos; //�Ҧ��_�i�ڪ���
};
#endif // !POKEMON_H
