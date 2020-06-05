#ifndef BAG_H
#define BAG_H
#include"NPC.h"
class bag
{
public:
	bag()
	{
		for (int i = 0; i < 4; i++)
			bag_Pokemons_num[i] = 0; //��l��
		assign_Pokemon(); //�w�˦�vector<monster>���A
	}
	~bag(){}
	int get_Pokemons_num(int i) {return bag_Pokemons_num[i];}//���o�o�Ӧ�m���_�i�ڽs��
	void set_BagPokemons_num(int Pokemon_num) //�I�]�S��,������s����i�h
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
	void set_BagPokemons_num_Full(int i, int pokemon_num) //�I�]���F,���w��m���_�i�ک��I�]
	{
		bag_Pokemons_num[i] = pokemon_num;
	}
	bool configure_Full() //�T�{�I�]���F�S
	{
		int record = 0;
		for (int i = 1; i < 4; i++)
			if (bag_Pokemons_num[i] != 0)
				record++;
		if (record == 3)
			return true; //���F
		return false; //�S��
	}
	void assign_bag(bag &left) //�w�˭I�]
	{
		for (int i = 1; i < 4; i++)
			left.bag_Pokemons_num[i] = bag_Pokemons_num[i];
	}
	int get_substitute() //���o�n��������m
	{
		show_having_pokemon(); //�i�ܩҦ��_�i�ڪ��W�r
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
	string get_Pokempn_name(int pokemon_num) //�o���_�i�ڪ��W�r
	{
		return Pokemon_Inquiry.get_Name(pokemon_num);
	}
	void show_having_pokemon() //�i�ܩҦ��_�i�ڪ��W�r
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
	void assign_Pokemon() //�w���_�i��(�����ϥ�)
	{
		Pokemon_Inquiry.assign_Pokemon_Infos(Pokemon_Inquirys);
	}
private:
	int bag_Pokemons_num[4]; //�s�I�]�_�i�ڪ��s��(�q[1]�}�l��)
	Pokemon Pokemon_Inquiry;
	vector<monster> Pokemon_Inquirys;
};
#endif // !BAG_H
