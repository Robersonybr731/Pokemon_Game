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
		show_map(); //顯示地圖
		configure_player_map(); //修改第二章地圖(方便取得元素)
		set_pokemon(); //copy寶可夢
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
	void configure_player_map() { player_map.configure(); } //修改第二張預設地圖
	void save_current_element() { current_element = player_map.get_map_element(y_value, x_value); }//儲存現在位置的元素
	void show_map() { create_map.show(); }//顯示地圖
	int show_exit_message() //按空白的時候出現的提示
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
		cout << "☆Point: " << point;
		resetColor();
		while (1)
		{
			char k = getkey();
			if (k == '1') //繼續
			{
				cls();//清除所有內容
				show_map(); //重畫地圖

				mouse_locate();
				break;
			}
			else if (k == '2') //離開
				return 2;
		}
	}
	void run() //主架構
	{
		save_current_element();//current_element得到目前位置的元素
		mouse_locate();	//顯示@的位置
		while (1)
		{
			if (kbhit())
			{
				char get_keyboard = getkey(); //取得從鍵盤打入的值
				int oldx = x_value, oldy = y_value; //取得現在的位置
				if (get_keyboard == 'a') { --x_value; }//左
				else if (get_keyboard == 'd') { ++x_value; }//右
				else if (get_keyboard == 'w') { --y_value; }//上
				else if (get_keyboard == 's') { ++y_value; }//下
				if (get_keyboard == ' ')
				{
					if (show_exit_message() == 2) //離開
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
						create_map.show(); //重新畫圖
						mouse_locate();
					}
				} //跳出提示
				else
				{
					char next_element = player_map.get_map_element(y_value, x_value); //下一個位置的元素
					/*判斷可不可以抓寶,只有在按鍵為wasd且下個位置的元素為可通過的情況下觸發*/
					if ((get_keyboard == 'a' || get_keyboard == 'w' || get_keyboard == 's' || get_keyboard == 'd') && get_through(next_element) == true && next_element != '#')
					{
						int rand_number = rand() % 10 + 1; //顯示1~10
						int pokemon_num; //設定哪一隻寶可夢出現
						if (rand_number == 7) //10%機率可以抓寶
						{
							if (current_element == ';') //特殊地形,草系50%
								pokemon_num = grass_persent();
							else if (current_element == '~') //特殊地形,水系50%
								pokemon_num = water_persent();
							else if (current_element = ' ') //一般道路,隨機出現一隻寶可夢
								pokemon_num = rand() % 34 + 1;
							catcher.captural_Interface(pokemon_num, Pokemons); //顯示抓寶介面
							int selection = catcher.get_catch_selection();//得到抓或不抓的決定 1.抓 2.不抓
							if (selection == 1)//抓
							{
								if (catcher.get_catch_success(selection) == true) //有抓到
									configure_bag_Full(pokemon_num); //判斷背包有沒有滿,改變背包的寶可夢
								else //逃跑
								{
									catcher.show_escape_messages(pokemon_num); //展示逃跑訊息
									show_continue_message();//怪物逃跑後需要按甚麼鍵繼續的訊息
								}
							}
							cls();
							create_map.show(); //重新畫圖
						}
					}
					if (get_through(next_element) == false) //代表不能通過
					{
						x_value = oldx, y_value = oldy; //座標回歸原本的位置
						mouse_locate();	//一樣的位置
					}
					else //代表能通過
					{
						mouse_locate(); //跑到下一格的位置
						restore_element_locate(oldx, oldy); //恢復原本的元素
						current_element = next_element; //把下一格的元素放到暫存
					}
					if (next_element == '#') //battle
					{
						cls();
						npc npc(find_gate(x_value, y_value)); //預設哪一個NPC
						for (int i = 1; i < 4; i++)
							set_catcher_MO(i, oweners_bag.get_Pokemons_num(i)); //cathcher的所有寶可夢
						while (1)
						{
							if (getCurrentMonsters() == nullptr) //如果玩家沒怪獸
							{
								NO_pokemon_message();
								break;
							}
							show_battle(npc);//展示對戰狀態
							if (npc.getCurrentMonster()->getSpeed() > getCurrentMonsters()->getSpeed()) //判斷誰速度大 (NPC大)
							{
								setColor(BROWN);
								npc.getCurrentMonster()->attack(*getCurrentMonsters()); //NPC攻擊玩家
								resetColor();
								if (npc.getCurrentMonster() == nullptr) //玩家勝利
								{
									wait();
									npc.restore(1);
									restore();
									victory();
									break;
								}
								else if (getCurrentMonsters() == nullptr) //電腦勝利
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
								npc.getCurrentMonster()->showStats(82, 40); //展示NPC狀態
								getCurrentMonsters()->showStats(40, 40); //展示玩家狀態
								resetColor();
								wait();
								cls();

								show_battle(npc);//展示對戰狀態
								setColor(BROWN);
								getCurrentMonsters()->attack(*npc.getCurrentMonster()); //玩家攻擊npc
								resetColor();
								if (npc.getCurrentMonster() == nullptr) //玩家勝利
								{
									wait();
									npc.restore(1);
									restore();
									victory();
									break;
								}
								else if (getCurrentMonsters() == nullptr) //電腦勝利
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
								npc.getCurrentMonster()->showStats(82, 40); //展示NPC狀態
								getCurrentMonsters()->showStats(40, 40); //展示玩家狀態
								resetColor();
							}
							else
							{
								setColor(BROWN);
								getCurrentMonsters()->attack(*npc.getCurrentMonster()); //玩家攻擊npc
								resetColor();
								if (npc.getCurrentMonster() == nullptr) //玩家勝利
								{
									wait();
									npc.restore(1);
									restore();
									victory();
									break;
								}
								else if (getCurrentMonsters() == nullptr) //電腦勝利
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
								npc.getCurrentMonster()->showStats(82, 40); //展示NPC狀態
								getCurrentMonsters()->showStats(40, 40); //展示玩家狀態
								wait();
								cls();
								resetColor();
								show_battle(npc);//展示對戰狀態
								setColor(BROWN);
								npc.getCurrentMonster()->attack(*getCurrentMonsters()); //NPC攻擊玩家
								resetColor();
								if (npc.getCurrentMonster() == nullptr) //玩家勝利
								{
									wait();
									npc.restore(1);
									restore();
									victory();
									break;
								}
								else if (getCurrentMonsters() == nullptr) //電腦勝利
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
								npc.getCurrentMonster()->showStats(82, 40); //展示NPC狀態
								getCurrentMonsters()->showStats(40, 40); //展示玩家狀態
								resetColor();
							}
							wait();
							cls();
						}
						cls();
						create_map.show(); //重新畫圖
						mouse_locate();
					}
				}
			}
		}
	}
	void print_s() //印符號
	{
		for (int i = 0; i < 140; i++)
		{
			locate(1 + i, 38);
			cout << "*";
		}
	}
	void point_class() //印階級
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
			a = "Class: ☆☆☆☆☆☆";
			cout<< a;
		}
		else if (point >= 1200)
		{
			a = "Class: ☆☆☆☆☆";
			cout << a;
		}
		else if (point >= 1000)
		{
			a = "Class: ☆☆☆☆";
			cout << a;
		}
		else if (point >= 900)
		{
			a = "Class: ☆☆☆";
			cout << a;
		}
		else if (point >= 800)
		{
			a = "Class: ☆☆";
			cout << a;
		}
		else if (point >= 700)
		{
			a = "Class: ☆";
			cout << a;
		}
		else if (point >= 600)
		{
			a = "Class: ◆◆◆◆◆◆";
			cout << a;
		}
		else if (point >= 500)
		{
			a = "Class: ◆◆◆◆◆";
			cout << a;
		}
		else if (point >= 400)
		{
			a = "Class: ◆◆◆◆";
			cout << a;
		}
		else if (point >= 300)
		{
			a = "Class: ◆◆◆";
			cout << a;
		}
		else if (point >= 200)
		{
			a = "Class: ◆◆";
			cout << a;
		}
		else
		{
			a = "Class: ◆";
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
	int find_gate(int x, int y) //找座標 換NPC
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
	void restore() //恢復
	{
		for (int i = 1; i < 4; i++)
			set_catcher_MO(i, oweners_bag.get_Pokemons_num(i)); //cathcher的所有寶可夢
	}
	void fail() //失敗
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
	void victory() //勝利
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
		catcher.display_pokemons(getCurrentMonsters()->getNo(), npc.getCurrentMonster()->getNo()); //展示圖案
		NPC_having(npc); //NPC的怪物清單
		player_having(); //player的怪物清單
		NPC_currentProperty(npc); //NPC現在怪獸的屬性
		player_currentProperty(); //player現在怪獸的屬性
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
	void NPC_currentProperty(npc &npc) //獲得現在寶可夢的屬性
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
	void NPC_having(npc &npc) //NPC寶可夢清單
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
	void player_having() //玩家寶可夢清單
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
	void show_continue_message() //怪物逃跑後需要按甚麼鍵繼續的訊息
	{
		locate(51, 33);
		setColor(YELLOW);
		cout << "You need Input Blank key to continue the game !";
		wait();
	}
	void configure_bag_Full(int pokemon_num) //判斷背包有沒有滿
	{
		if (oweners_bag.configure_Full() == false) //背包還沒滿
		{
			oweners_bag.set_BagPokemons_num(pokemon_num); //直接放編號
			locate(51, 33);
			setColor(YELLOW);
			cout << "Catch Success!! Please Input Blank key to continue. ";
			resetColor();
			wait();
		}
		else //背包滿了
		{
			cls();
			catcher.captural_Interface(pokemon_num, Pokemons); //顯示抓寶介面
			locate(51, 30);
			setColor(LIGHTRED);
			cout << "Please Input 1 or 2 or 3 to give up one Pokemon  ";
			resetColor();
			int i = oweners_bag.get_substitute(); //得到哪一個要被替換
			oweners_bag.set_BagPokemons_num_Full(i, pokemon_num); //滿了要丟一隻替換
			locate(51, 31);
			setColor(YELLOW);
			cout << "Success!! Please Input Blank key to continue. ";
			wait();
		}
		catcher.assign_bag(oweners_bag); //改變背包的寶可夢
	}
	int  grass_persent() //草系的機率
	{
		int rand_number = rand() % 4; //顯示0~3
		if (rand_number == 0 || rand_number == 1) //選擇草系
		{
			int arrays[3] = { 1,2,3 }; //草系的編號
			rand_number = arrays[rand() % 3];
		}
		else if (rand_number == 2 || rand_number == 3) //草系以外的寶可夢
		{
			do
			{
				rand_number = rand() % 34 + 1;//1~34
			} while (rand_number == 1 || rand_number == 2 || rand_number == 3);
		}
		return rand_number;
	}
	int  water_persent() //水系的機率
	{
		int rand_number = rand() % 4; //顯示0~3
		if (rand_number == 0 || rand_number == 1) //選擇水系
		{
			int arrays[3] = { 7,8,9 }; //水系的編號
			rand_number = arrays[rand() % 3];
		}
		else if (rand_number == 2 || rand_number == 3) //水系以外的寶可夢
		{
			do
			{
				rand_number = rand() % 34 + 1;//1~34
			} while (rand_number == 7 || rand_number == 8 || rand_number == 9);
		}
		return rand_number;
	}
	bool get_through(char element)//判斷可不可以走過去
	{
		const char notThrough[16] = { '1','2','3','4','5','6','7','8','9','A','B','C','D','*','!' };
		for (int i = 0; i < 16; i++)
		{
			if (element == notThrough[i])
				return false;
		}
		return true;
	}
	void mouse_locate() //@的位置設定
	{
		locate(x_value, y_value); //private 的座標
		setColor(RED);
		cout << "@";
		resetColor();
		fflush(stdout);
	}
	void restore_element_locate(int x, int y) //@走過的元素的位置重置
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
	int get_color_num(char current_element) //判斷走過的元素是哪種顏色
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
		int color[5] = { 2,1,0,0 };// 顏色的代表數字
		return color[record];
	}
	void set_pokemon()  //存34隻寶可夢
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
	vector<monster> Pokemons; //複製所有寶可夢資訊
	Pokemon Pokemon; //把所有寶可夢的素質放進去
	catching catcher; //捕捉介面
	bag oweners_bag; //目前背包擁有的怪物
	mapping create_map; //顯示的地圖
	mapping player_map; //玩家的地圖(多一行.一排)
	int x_value = 20;//20 預設座標
	int y_value = 25;//25 預設座標
	char current_element; //儲存現在位置的元素
	int point = 0;
};

#endif // !PLAYER_H
