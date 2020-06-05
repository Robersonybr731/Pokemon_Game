#ifndef PLAYER_H
#define PLAYER_H

#include"map.h"
#include"catch.h"
#include"NPC.h"
#include<exception>

class Player
{
public:
	Player() //constructor
	{
		show_map(); //��ܦa��
		configure_player_map(); //�ק�ĤG���a��(��K���o����)
		set_pokemon(); //copy�_�i��
	}
	~Player() {}//destructor
	class classtion : public exception 
	{
	public:
		const char* what() const noexcept override
		{
			return "No class you have";
		}
	};
	void configure_player_map() { player_map.configure(); } //�ק�ĤG�i�w�]�a��
	void save_current_element() { current_element = player_map.get_map_element(y_value, x_value); }//�x�s�{�b��m������
	void show_map() { create_map.show(); }//��ܦa��
	int show_exit_message() //���ťժ��ɭԥX�{������
	{
		for (int i = 0; i < 30; i++)
		{
			locate(69 + i, 17);
			cout << "*";
		}
		for (int i = 0; i < 6; i++)
		{
			locate(69, 18 + i);
			cout << "*";
			locate(98, 18 + i);
			cout << "*";
		}
		for (int i = 0; i < 30; i++)
		{
			locate(69 + i, 24);
			cout << "*";
		}
		setColor(RED);
		locate(77, 18);
		cout << "Please choose:";
		locate(73, 20);
		cout << "1. Continue";
		locate(88, 20);
		cout << "2. Exit";
		setColor(YELLOW);
		locate(77, 22);
		cout << "��Point: " << point;
		resetColor();
		while (1)
		{
			char k = getkey();
			if (k == '1') //�~��
			{
				cls();//�M���Ҧ����e
				show_map(); //���e�a��

				mouse_locate();
				break;
			}
			else if (k == '2') //���}
				return 2;
		}
	}
	void run() //�D�[�c
	{
		save_current_element();//current_element�o��ثe��m������
		mouse_locate();	//���@����m
		while (1)
		{
			if (kbhit())
			{
				char get_keyboard = getkey(); //���o�q��L���J����
				int oldx = x_value, oldy = y_value; //���o�{�b����m
				if (get_keyboard == 'a') { --x_value; }//��
				else if (get_keyboard == 'd') { ++x_value; }//�k
				else if (get_keyboard == 'w') { --y_value; }//�W
				else if (get_keyboard == 's') { ++y_value; }//�U
				if (get_keyboard == ' ')
				{
					if (show_exit_message() == 2) //���}
					{
						cls();
						setColor(BROWN);
						locate(58, 18);
						cout << "END GAME!";
						setColor(YELLOW);
						locate(58, 20);
						cout << "Congratulations! Your Point: " << point;
						resetColor();
						try
						{
							point_class();
						}
						catch(classtion &classes)
						{
							setColor(YELLOW);
							locate(58, 21);
							cout << classes.what();
							resetColor();
						}
						wait();
						return;
					}
					else
					{
						cls();
						create_map.show(); //���s�e��
						mouse_locate();
					}
				} //���X����
				else
				{
					char next_element = player_map.get_map_element(y_value, x_value); //�U�@�Ӧ�m������
					/*�P�_�i���i�H���_,�u���b���䬰wasd�B�U�Ӧ�m���������i�q�L�����p�UĲ�o*/
					if ((get_keyboard == 'a' || get_keyboard == 'w' || get_keyboard == 's' || get_keyboard == 'd') && get_through(next_element) == true && next_element != '#')
					{
						int rand_number = rand() % 10 + 1; //���1~10
						int pokemon_num; //�]�w���@���_�i�ڥX�{
						if (rand_number == 7) //10%���v�i�H���_
						{
							if (current_element == ';') //�S��a��,��t50%
								pokemon_num = grass_persent();
							else if (current_element == '~') //�S��a��,���t50%
								pokemon_num = water_persent();
							else if (current_element = ' ') //�@��D��,�H���X�{�@���_�i��
								pokemon_num = rand() % 34 + 1;
							catcher.captural_Interface(pokemon_num, Pokemons); //��ܧ��_����
							int selection = catcher.get_catch_selection();//�o���Τ��쪺�M�w 1.�� 2.����
							if (selection == 1)//��
							{
								if (catcher.get_catch_success(selection) == true) //�����
									configure_bag_Full(pokemon_num); //�P�_�I�]���S����,���ܭI�]���_�i��
								else //�k�]
								{
									catcher.show_escape_messages(pokemon_num); //�i�ܰk�]�T��
									show_continue_message();//�Ǫ��k�]��ݭn���ƻ����~�򪺰T��
								}
							}
							cls();
							create_map.show(); //���s�e��
						}
					}
					if (get_through(next_element) == false) //�N����q�L
					{
						x_value = oldx, y_value = oldy; //�y�Ц^�k�쥻����m
						mouse_locate();	//�@�˪���m
					}
					else //�N���q�L
					{
						mouse_locate(); //�]��U�@�檺��m
						restore_element_locate(oldx, oldy); //��_�쥻������
						current_element = next_element; //��U�@�檺�������Ȧs
					}
					if (next_element == '#') //battle
					{
						cls();
						npc npc(find_gate(x_value, y_value)); //�w�]���@��NPC
						for (int i = 1; i < 4; i++)
							set_catcher_MO(i, oweners_bag.get_Pokemons_num(i)); //cathcher���Ҧ��_�i��
						while (1)
						{
							if (getCurrentMonsters() == nullptr) //�p�G���a�S���~
							{
								NO_pokemon_message();
								break;
							}
							show_battle(npc);//�i�ܹ�Ԫ��A
							if (npc.getCurrentMonster()->getSpeed() > getCurrentMonsters()->getSpeed()) //�P�_�ֳt�פj (NPC�j)
							{
								setColor(BROWN);
								npc.getCurrentMonster()->attack(*getCurrentMonsters()); //NPC�������a
								resetColor();
								if (npc.getCurrentMonster() == nullptr) //���a�ӧQ
								{
									wait();
									npc.restore(1);
									restore();
									victory();
									break;
								}
								else if (getCurrentMonsters() == nullptr) //�q���ӧQ
								{
									wait();
									npc.restore(1);
									restore();
									fail();
									break;
								}
								setColor(BROWN);
								print_s();
								locate(64, 39);
								cout << "Round Message";
								npc.getCurrentMonster()->showStats(82, 40); //�i��NPC���A
								getCurrentMonsters()->showStats(40, 40); //�i�ܪ��a���A
								resetColor();
								wait();
								cls();

								show_battle(npc);//�i�ܹ�Ԫ��A
								setColor(BROWN);
								getCurrentMonsters()->attack(*npc.getCurrentMonster()); //���a����npc
								resetColor();
								if (npc.getCurrentMonster() == nullptr) //���a�ӧQ
								{
									wait();
									npc.restore(1);
									restore();
									victory();
									break;
								}
								else if (getCurrentMonsters() == nullptr) //�q���ӧQ
								{
									wait();
									npc.restore(1);
									restore();
									fail();
									break;
								}
								setColor(BROWN);
								
								print_s();
								locate(64, 39);
								cout << "Round Message";
								npc.getCurrentMonster()->showStats(82, 40); //�i��NPC���A
								getCurrentMonsters()->showStats(40, 40); //�i�ܪ��a���A
								resetColor();
							}
							else
							{
								setColor(BROWN);
								getCurrentMonsters()->attack(*npc.getCurrentMonster()); //���a����npc
								resetColor();
								if (npc.getCurrentMonster() == nullptr) //���a�ӧQ
								{
									wait();
									npc.restore(1);
									restore();
									victory();
									break;
								}
								else if (getCurrentMonsters() == nullptr) //�q���ӧQ
								{
									wait();
									npc.restore(1);
									restore();
									fail();
									break;
								}
								setColor(BROWN);
								
								print_s();
								locate(64, 39);
								cout << "Round Message";
								npc.getCurrentMonster()->showStats(82, 40); //�i��NPC���A
								getCurrentMonsters()->showStats(40, 40); //�i�ܪ��a���A
								wait();
								cls();
								resetColor();
								show_battle(npc);//�i�ܹ�Ԫ��A
								setColor(BROWN);
								npc.getCurrentMonster()->attack(*getCurrentMonsters()); //NPC�������a
								resetColor();
								if (npc.getCurrentMonster() == nullptr) //���a�ӧQ
								{
									wait();
									npc.restore(1);
									restore();
									victory();
									break;
								}
								else if (getCurrentMonsters() == nullptr) //�q���ӧQ
								{
									wait();
									npc.restore(1);
									restore();
									fail();
									break;
								}
								setColor(BROWN);
								
								print_s();
								locate(64, 39);
								cout << "Round Message";
								npc.getCurrentMonster()->showStats(82, 40); //�i��NPC���A
								getCurrentMonsters()->showStats(40, 40); //�i�ܪ��a���A
								resetColor();
							}
							wait();
							cls();
						}
						cls();
						create_map.show(); //���s�e��
						mouse_locate();
					}
				}
			}
		}
	}
	void print_s() //�L�Ÿ�
	{
		for (int i = 0; i < 140; i++)
		{
			locate(1 + i, 38);
			cout << "*";
		}
	}
	void point_class() //�L����
	{
		if (point == 0)
		{
			classtion a;
			throw a;
		}
		locate(58, 21);
		setColor(YELLOW);
		string a;
		if (point >= 1500)
		{
			a = "Class: ������������";
			cout<< a;
		}
		else if (point >= 1200)
		{
			a = "Class: ����������";
			cout << a;
		}
		else if (point >= 1000)
		{
			a = "Class: ��������";
			cout << a;
		}
		else if (point >= 900)
		{
			a = "Class: ������";
			cout << a;
		}
		else if (point >= 800)
		{
			a = "Class: ����";
			cout << a;
		}
		else if (point >= 700)
		{
			a = "Class: ��";
			cout << a;
		}
		else if (point >= 600)
		{
			a = "Class: ������������";
			cout << a;
		}
		else if (point >= 500)
		{
			a = "Class: ����������";
			cout << a;
		}
		else if (point >= 400)
		{
			a = "Class: ��������";
			cout << a;
		}
		else if (point >= 300)
		{
			a = "Class: ������";
			cout << a;
		}
		else if (point >= 200)
		{
			a = "Class: ����";
			cout << a;
		}
		else
		{
			a = "Class: ��";
			cout << a;
		}
		resetColor();
	}
	void NO_pokemon_message()
	{
		cls();
		for (int i = 0; i < 28; i++)
		{
			locate(54 + i, 19);
			cout << "*";
		}
		for (int i = 0; i < 3; i++)
		{
			locate(54, 20 + i);
			cout << "*";
			locate(81, 20 + i);
			cout << "*";
		}
		for (int i = 0; i < 28; i++)
		{
			locate(54+i, 23);
			cout << "*";
		}
		locate(58, 21);
		setColor(YELLOW);
		cout << "You have not Pokemon.";
		resetColor();
		wait();
		cls();
	}
	int find_gate(int x, int y) //��y�� ��NPC
	{
		if (x == 14)
			return 1;
		else if (x == 35)
			return 2;
		else if (x == 31)
			return 3;
		else if (x == 18)
			return 5;
		else if (x == 10)
			return 6;
		else if (x == 41)
			return 7;
		else if (x == 76 && y == 9)
			return 8;
		else if (x == 77)
			return 9;
		else if (x == 75)
			return 10;
		else if (x == 84)
			return 11;
		else if (x == 76 && y == 7)
			return 12;
		else if (x == 86)
			return 13;

	}
	void restore() //��_
	{
		for (int i = 1; i < 4; i++)
			set_catcher_MO(i, oweners_bag.get_Pokemons_num(i)); //cathcher���Ҧ��_�i��
	}
	void fail() //����
	{
		for (int i = 0; i < 15; i++)
		{
			locate(60 + i, 28);
			cout << "*";
			locate(60 + i, 35);
			cout << "*";
		}
		for (int i = 0; i < 7; i++)
		{
			locate(60, 29+i);
			cout << "*";
			locate(74, 29 + i);
			cout << "*";
		}
		setColor(RED);
		locate(62, 29);
		cout << "Game End !!";
		locate(62, 31);
		setColor(LIGHTMAGENTA);
		cout << "Player lose ";
		setColor(YELLOW);
		locate(62, 33);
		cout << "Point: +0";
		resetColor();
		wait();
		cls();
	}
	void victory() //�ӧQ
	{
		for (int i = 0; i < 15; i++)
		{
			locate(60 + i, 28);
			cout << "*";
			locate(60 + i, 35);
			cout << "*";
		}
		for (int i = 0; i < 7; i++)
		{
			locate(60, 29 + i);
			cout << "*";
			locate(74, 29 + i);
			cout << "*";
		}
		setColor(RED);
		locate(62, 29);
		cout << "Game End !!";
		locate(62, 31);
		setColor(LIGHTMAGENTA);
		cout << "Player win ";
		point += 100;
		setColor(YELLOW);
		locate(62, 33);
		cout << "Point: +100";
		resetColor();
		wait();
		cls();
	}
	void show_battle(npc &npc)
	{
		catcher.display_pokemons(getCurrentMonsters()->getNo(), npc.getCurrentMonster()->getNo()); //�i�ܹϮ�
		NPC_having(npc); //NPC���Ǫ��M��
		player_having(); //player���Ǫ��M��
		NPC_currentProperty(npc); //NPC�{�b���~���ݩ�
		player_currentProperty(); //player�{�b���~���ݩ�
	}
	void wait()
	{
		while (1)
		{
			char k = getkey();
			if (k == ' ')
				return;
		}
	}
	void NPC_currentProperty(npc &npc) //��o�{�b�_�i�ڪ��ݩ�
	{
		setColor(YELLOW);
		locate(88, 27);
		cout << "Name: " << npc.getCurrentMonster()->getName(npc.getCurrentMonster()->getNo());
		locate(88, 28);
		cout << "HP/MaxHP: " << npc.getCurrentMonster()->getHP() << " / " << npc.getCurrentMonster()->getMaxHP();
		locate(88, 29);
		cout << "Attack: " << npc.getCurrentMonster()->getAttack();
		locate(88, 30);
		cout << "Defense: " << npc.getCurrentMonster()->getDefense();
		locate(88, 31);
		cout << "Speed: " << npc.getCurrentMonster()->getSpeed();
		locate(88, 32);
		cout << "Type: " << npc.getCurrentMonster()->getType();
		resetColor();
	}
	void player_currentProperty()
	{
		setColor(YELLOW);
		locate(28, 27);
		cout << "Name: " << getCurrentMonsters()->getName(getCurrentMonsters()->getNo());
		locate(28, 28);
		cout << "HP/MaxHP: " << getCurrentMonsters()->getHP() << " / " << getCurrentMonsters()->getMaxHP();
		locate(28, 29);
		cout << "Attack: " << getCurrentMonsters()->getAttack();
		locate(28, 30);
		cout << "Defense: " << getCurrentMonsters()->getDefense();
		locate(28, 31);
		cout << "Speed: " << getCurrentMonsters()->getSpeed();
		locate(28, 32);
		cout << "Type: " << getCurrentMonsters()->getType();
		resetColor();
	}
	void NPC_having(npc &npc) //NPC�_�i�ڲM��
	{
		setColor(LIGHTCYAN);
		locate(88, 34);
		cout << npc.get_NPC_Name() << " having Pokemons";
		for (int i = 1; i < 4; i++)
		{
			int k = npc.getMonster(i)->getNo();
			locate(88, i + 34);
			cout << i << ". " << npc.getMonster(i)->getName(k);
		}
		resetColor();
	}
	void player_having() //���a�_�i�ڲM��
	{
		setColor(LIGHTMAGENTA);
		locate(28, 34);
		cout << "Player having Pokemons:";
		for (int i = 1; i < 4; i++)
		{
			if (catcher_Mo[i] != nullptr)
			{
				int k = catcher_Mo[i]->getNo();
				locate(28, i + 34);
				cout << i << ". " << catcher_Mo[i]->getName(k);
			}
			else
			{
				locate(28, i + 34);
				cout << i << ". ";
			}

		}
		resetColor();
	}
	void show_continue_message() //�Ǫ��k�]��ݭn���ƻ����~�򪺰T��
	{
		locate(51, 33);
		setColor(YELLOW);
		cout << "You need Input Blank key to continue the game !";
		wait();
	}
	void configure_bag_Full(int pokemon_num) //�P�_�I�]���S����
	{
		if (oweners_bag.configure_Full() == false) //�I�]�٨S��
		{
			oweners_bag.set_BagPokemons_num(pokemon_num); //������s��
			locate(51, 33);
			setColor(YELLOW);
			cout << "Catch Success!! Please Input Blank key to continue. ";
			resetColor();
			wait();
		}
		else //�I�]���F
		{
			cls();
			catcher.captural_Interface(pokemon_num, Pokemons); //��ܧ��_����
			locate(51, 30);
			setColor(LIGHTRED);
			cout << "Please Input 1 or 2 or 3 to give up one Pokemon  ";
			resetColor();
			int i = oweners_bag.get_substitute(); //�o����@�ӭn�Q����
			oweners_bag.set_BagPokemons_num_Full(i, pokemon_num); //���F�n��@������
			locate(51, 31);
			setColor(YELLOW);
			cout << "Success!! Please Input Blank key to continue. ";
			wait();
		}
		catcher.assign_bag(oweners_bag); //���ܭI�]���_�i��
	}
	int  grass_persent() //��t�����v
	{
		int rand_number = rand() % 4; //���0~3
		if (rand_number == 0 || rand_number == 1) //��ܯ�t
		{
			int arrays[3] = { 1,2,3 }; //��t���s��
			rand_number = arrays[rand() % 3];
		}
		else if (rand_number == 2 || rand_number == 3) //��t�H�~���_�i��
		{
			do
			{
				rand_number = rand() % 34 + 1;//1~34
			} while (rand_number == 1 || rand_number == 2 || rand_number == 3);
		}
		return rand_number;
	}
	int  water_persent() //���t�����v
	{
		int rand_number = rand() % 4; //���0~3
		if (rand_number == 0 || rand_number == 1) //��ܤ��t
		{
			int arrays[3] = { 7,8,9 }; //���t���s��
			rand_number = arrays[rand() % 3];
		}
		else if (rand_number == 2 || rand_number == 3) //���t�H�~���_�i��
		{
			do
			{
				rand_number = rand() % 34 + 1;//1~34
			} while (rand_number == 7 || rand_number == 8 || rand_number == 9);
		}
		return rand_number;
	}
	bool get_through(char element)//�P�_�i���i�H���L�h
	{
		const char notThrough[16] = { '1','2','3','4','5','6','7','8','9','A','B','C','D','*','!' };
		for (int i = 0; i < 16; i++)
		{
			if (element == notThrough[i])
				return false;
		}
		return true;
	}
	void mouse_locate() //@����m�]�w
	{
		locate(x_value, y_value); //private ���y��
		setColor(RED);
		cout << "@";
		resetColor();
		fflush(stdout);
	}
	void restore_element_locate(int x, int y) //@���L����������m���m
	{
		locate(x, y);
		setBackgroundColor(get_color_num(current_element));
		if (current_element == '#')
			setColor(YELLOW);
		cout << current_element;
		setBackgroundColor(0);
		resetColor();
		fflush(stdout);
	}
	int get_color_num(char current_element) //�P�_���L�������O�����C��
	{
		int record;
		const char through_element[5] = { ';','~','#',' ' };
		for (int i = 0; i < 5; i++)
		{
			if (current_element == through_element[i])
			{
				record = i;
				break;
			}
		}
		int color[5] = { 2,1,0,0 };// �C�⪺�N��Ʀr
		return color[record];
	}
	void set_pokemon()  //�s34���_�i��
	{
		Pokemon.assign_Pokemon_Infos(Pokemons);
	}
	void set_catcher_MO(int i, int no)
	{
		if (no == 1)
		{
			Bulbasaur *a = new Bulbasaur;
			catcher_Mo[i] = a;
		}
		else if (no == 2)
		{
			Ivysaur*a = new Ivysaur;
			catcher_Mo[i] = a;
		}
		else if (no == 3)
		{
			Venusaur*a = new Venusaur;
			catcher_Mo[i] = a;
		}
		else if (no == 4)
		{
			Charmander*a = new Charmander;
			catcher_Mo[i] = a;
		}
		else if (no == 5)
		{
			Charmeleon*a = new Charmeleon;
			catcher_Mo[i] = a;
		}
		else if (no == 6)
		{
			Charizard*a = new Charizard;
			catcher_Mo[i] = a;
		}
		else if (no == 7)
		{
			Squirtle*a = new Squirtle;
			catcher_Mo[i] = a;
		}
		else if (no == 8)
		{
			Wartortle*a = new Wartortle;
			catcher_Mo[i] = a;
		}
		else if (no == 9)
		{
			Blastoise*a = new Blastoise;
			catcher_Mo[i] = a;
		}
		else if (no == 10)
		{
			Caterpie*a = new Caterpie;
			catcher_Mo[i] = a;
		}
		else if (no == 11)
		{
			Metapod*a = new Metapod;
			catcher_Mo[i] = a;
		}
		else if (no == 12)
		{
			Butterfree*a = new Butterfree;
			catcher_Mo[i] = a;
		}
		else if (no == 13)
		{
			Weedle*a = new Weedle;
			catcher_Mo[i] = a;
		}
		else if (no == 14)
		{
			Kakuna*a = new Kakuna;
			catcher_Mo[i] = a;
		}
		else if (no == 15)
		{
			Beedrill*a = new Beedrill;
			catcher_Mo[i] = a;
		}
		else if (no == 16)
		{
			Pidgey*a = new Pidgey;
			catcher_Mo[i] = a;
		}
		else if (no == 17)
		{
			Pidgeotto*a = new Pidgeotto;
			catcher_Mo[i] = a;
		}
		else if (no == 18)
		{
			Pidgeot*a = new Pidgeot;
			catcher_Mo[i] = a;
		}
		else if (no == 19)
		{
			Rattata*a = new Rattata;
			catcher_Mo[i] = a;
		}
		else if (no == 20)
		{
			Raticate*a = new Raticate;
			catcher_Mo[i] = a;
		}
		else if (no == 21)
		{
			Spearow*a = new Spearow;
			catcher_Mo[i] = a;
		}
		else if (no == 22)
		{
			Fearow*a = new Fearow;
			catcher_Mo[i] = a;
		}
		else if (no == 23)
		{
			Ekans*a = new Ekans;
			catcher_Mo[i] = a;
		}
		else if (no == 24)
		{
			Arbok*a = new Arbok;
			catcher_Mo[i] = a;
		}
		else if (no == 25)
		{
			Pikachu*a = new Pikachu;
			catcher_Mo[i] = a;
		}
		else if (no == 26)
		{
			Raichu*a = new Raichu;
			catcher_Mo[i] = a;
		}
		else if (no == 27)
		{
			Sandshrew*a = new Sandshrew;
			catcher_Mo[i] = a;
		}
		else if (no == 28)
		{
			Sandslash*a = new Sandslash;
			catcher_Mo[i] = a;
		}
		else if (no == 29)
		{
			Nidoran_W*a = new Nidoran_W;
			catcher_Mo[i] = a;
		}
		else if (no == 30)
		{
			Nidorina*a = new Nidorina;
			catcher_Mo[i] = a;
		}
		else if (no == 31)
		{
			Nidoqueen*a = new Nidoqueen;
			catcher_Mo[i] = a;
		}
		else if (no == 32)
		{
			Nidoran_M*a = new Nidoran_M;
			catcher_Mo[i] = a;
		}
		else if (no == 33)
		{
			Nidorino*a = new Nidorino;
			catcher_Mo[i] = a;
		}
		else if (no == 34)
		{
			Nidoking*a = new Nidoking;
			catcher_Mo[i] = a;
		}
	} 
	Monster* getCurrentMonsters()
	{
		for (int i = 1; i < 4; i++)
		{
			if (catcher_Mo[i] == nullptr)
				return nullptr;
			if (catcher_Mo[i]->getHP() > 0)
				return catcher_Mo[i];
		}
		return nullptr;
	}

private:
	Monster* catcher_Mo[4];
	vector<monster> Pokemons; //�ƻs�Ҧ��_�i�ڸ�T
	Pokemon Pokemon; //��Ҧ��_�i�ڪ������i�h
	catching catcher; //��������
	bag oweners_bag; //�ثe�I�]�֦����Ǫ�
	mapping create_map; //��ܪ��a��
	mapping player_map; //���a���a��(�h�@��.�@��)
	int x_value = 20;//20 �w�]�y��
	int y_value = 25;//25 �w�]�y��
	char current_element; //�x�s�{�b��m������
	int point = 0;
};

#endif // !PLAYER_H
