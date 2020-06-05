#ifndef NPC_H
#define NPC_H
#include"Pokemon.h"
#include"Attacks.h"

class npc
{
public:
	npc(int i)
	{
		set_default_npc(i); //設置13個NPC
	}
	~npc()
	{

	}
	Monster* getCurrentMonster() //確認哪一隻怪物戰鬥	
	{
		for (int i = 1; i < 4; i++)
		{
			if (Mo[i]->getHP() > 0)
				return Mo[i];
		}
		return nullptr;
	}
	Monster* getMonster(int i)
	{
		if (Mo[i] != nullptr)
			return Mo[i];
		else
			return nullptr;
	}
	void restore(int i)
	{
		if (i == 1)
			set_npc_1();
		else if (i == 2)
			set_npc_2();
		else if (i == 3)
			set_npc_3();
		else if (i == 4)
			set_npc_4();
		else if (i == 5)
			set_npc_5();
		else if (i == 6)
			set_npc_6();
		else if (i == 7)
			set_npc_7();
		else if (i == 8)
			set_npc_8();
		else if (i == 9)
			set_npc_9();
		else if (i == 10)
			set_npc_10();
		else if (i == 11)
			set_npc_11();
		else if (i == 12)
			set_npc_12();
		else if (i == 13)
			set_npc_13();

	}
	void set_default_npc(int i)//設置13個NPC
	{
		if (i == 1)
			set_npc_1();
		if (i == 2)
			set_npc_2();
		if (i == 3)
			set_npc_3();
		if (i == 4)
			set_npc_4();
		if (i == 5)
			set_npc_5();
		if (i == 6)
			set_npc_6();
		if (i == 7)
			set_npc_7();
		if (i == 8)
			set_npc_8();
		if (i == 9)
			set_npc_9();
		if (i == 10)
			set_npc_10();
		if (i == 11)
			set_npc_11();
		if (i == 12)
			set_npc_12();
		if (i == 13)
			set_npc_13();
		
	}
	void set_npc_1()
	{
		set_MO(1, 1);
		set_MO(2, 4);
		set_MO(3, 7);
		NPC_name = "垃圾諮";
	}
	void set_npc_2()
	{
		set_MO(1, 14);
		set_MO(2, 25);
		set_MO(3, 6);
		NPC_name = "草皮哥";
	}
	void set_npc_3()
	{
		set_MO(1, 20);
		set_MO(2, 7);
		set_MO(3, 3);
		NPC_name = "師大刷存仔";
	}
	void set_npc_4()
	{
		set_MO(1, 8);
		set_MO(2, 4);
		set_MO(3, 16);
		NPC_name = "說好的幸福呢";
	}
	void set_npc_5()
	{
		set_MO(1, 11);
		set_MO(2, 2);
		set_MO(3, 28);
		NPC_name = "林丫頭";
	}
	void set_npc_6()
	{
		set_MO(1, 29);
		set_MO(2, 32);
		set_MO(3, 33);
		NPC_name = "邊緣俊儀";
	}
	void set_npc_7()
	{
		set_MO(1, 10);
		set_MO(2, 20);
		set_MO(3, 30);
		NPC_name = "新竹馬子狗";
	}
	void set_npc_8()
	{
		set_MO(1, 13);
		set_MO(2, 19);
		set_MO(3, 23);
		NPC_name = "沈壁虎";
	}
	void set_npc_9()
	{
		set_MO(1, 21);
		set_MO(2, 17);
		set_MO(3, 27);
		NPC_name = "苗栗阿胖";
	}
	void set_npc_10()
	{
		set_MO(1, 18);
		set_MO(2, 5);
		set_MO(3, 15);
		NPC_name = "台中飆仔";
	}
	void set_npc_11()
	{
		set_MO(1, 24);
		set_MO(2, 12);
		set_MO(3, 15);
		NPC_name = "台中飆仔";
	}
	void set_npc_12()
	{
		set_MO(1, 34);
		set_MO(2, 9);
		set_MO(3, 6);
		NPC_name = "King Roberson";
	}
	void set_npc_13()
	{
		set_MO(1, 22);
		set_MO(2, 26);
		set_MO(3, 31);
		NPC_name = "會長大人幫幫我";
	}
	void set_MO(int i, int no)
	{
		if (no == 1)
		{
			Bulbasaur *a = new Bulbasaur;
			Mo[i] = a;
		}
		else if (no == 2)
		{
			Ivysaur*a = new Ivysaur;
			Mo[i] = a;
		}
		else if (no == 3)
		{
			Venusaur*a = new Venusaur;
			Mo[i] = a;
		}
		else if (no == 4)
		{
			Charmander*a = new Charmander;
			Mo[i] = a;
		}
		else if (no == 5)
		{
			Charmeleon*a = new Charmeleon;
			Mo[i] = a;
		}
		else if (no == 6)
		{
			Charizard*a = new Charizard;
			Mo[i] = a;
		}
		else if (no == 7)
		{
			Squirtle*a = new Squirtle;
			Mo[i] = a;
		}
		else if (no == 8)
		{
			Wartortle*a = new Wartortle;
			Mo[i] = a;
		}
		else if (no == 9)
		{
			Blastoise*a = new Blastoise;
			Mo[i] = a;
		}
		else if (no == 10)
		{
			Caterpie*a = new Caterpie;
			Mo[i] = a;
		}
		else if (no == 11)
		{
			Metapod*a = new Metapod;
			Mo[i] = a;
		}
		else if (no == 12)
		{
			Butterfree*a = new Butterfree;
			Mo[i] = a;
		}
		else if (no == 13)
		{
			Weedle*a = new Weedle;
			Mo[i] = a;
		}
		else if (no == 14)
		{
			Kakuna*a = new Kakuna;
			Mo[i] = a;
		}
		else if (no == 15)
		{
			Beedrill*a = new Beedrill;
			Mo[i] = a;
		}
		else if (no == 16)
		{
			Pidgey*a = new Pidgey;
			Mo[i] = a;
		}
		else if (no == 17)
		{
			Pidgeotto*a = new Pidgeotto;
			Mo[i] = a;
		}
		else if (no == 18)
		{
			Pidgeot*a = new Pidgeot;
			Mo[i] = a;
		}
		else if (no == 19)
		{
			Rattata*a = new Rattata;
			Mo[i] = a;
		}
		else if (no == 20)
		{
			Raticate*a = new Raticate;
			Mo[i] = a;
		}
		else if (no == 21)
		{
			Spearow*a = new Spearow;
			Mo[i] = a;
		}
		else if (no == 22)
		{
			Fearow*a = new Fearow;
			Mo[i] = a;
		}
		else if (no == 23)
		{
			Ekans*a = new Ekans;
			Mo[i] = a;
		}
		else if (no == 24)
		{
			Arbok*a = new Arbok;
			Mo[i] = a;
		}
		else if (no == 25)
		{
			Pikachu*a = new Pikachu;
			Mo[i] = a;
		}
		else if (no == 26)
		{
			Raichu*a = new Raichu;
			Mo[i] = a;
		}
		else if (no == 27)
		{
			Sandshrew*a = new Sandshrew;
			Mo[i] = a;
		}
		else if (no == 28)
		{
			Sandslash*a = new Sandslash;
			Mo[i] = a;
		}
		else if (no == 29)
		{
			Nidoran_W*a = new Nidoran_W;
			Mo[i] = a;
		}
		else if (no == 30)
		{
			Nidorina*a = new Nidorina;
			Mo[i] = a;
		}
		else if (no == 31)
		{
			Nidoqueen*a = new Nidoqueen;
			Mo[i] = a;
		}
		else if (no == 32)
		{
			Nidoran_M*a = new Nidoran_M;
			Mo[i] = a;
		}
		else if (no == 33)
		{
			Nidorino*a = new Nidorino;
			Mo[i] = a;
		}
		else if (no == 34)
		{
			Nidoking*a = new Nidoking;
			Mo[i] = a;
		}
	}
	string get_NPC_Name()
	{
		return NPC_name;
	}
private:
	Monster* Mo[4];
	string NPC_name;
};

#endif // !NPC_H
