
#ifndef ATTACKS_H
#define ATTACKS_H
#include"Pokemon.h"
int values[35][6];
const char* types[19];
double type_num[19][19];


class Monster {
public:
	Monster(int hp, int mxhp, int atk, int def, int speed, int ability, int no, string type)
		:HP(hp), MaxHP(mxhp), Attack(atk), Defense(def), Speed(speed), Ability(ability), No(no), Type(type) {} //constructer
	void setHP(int hp) { HP = hp; } //�]�m��q
	void setAttack(int atk) { Attack = atk; } //�]�m����
	void setDefense(int def) { Defense = def; } //�]�m���m
	void setSpeed(int speed) { Speed = speed; } //�]�m�t��
	void setusingful(int usingfuls) { usingful = usingfuls; } //�]�m���S���ϥιL
	void setsituation(int situation) { situations = situation; } //�]�m���A
	int getHP() const { return HP; } //���o�ثe��q
	int getMaxHP() const { return MaxHP; } //���o�쥻�̤j��q
	int getAttack() const { return Attack; } //��e�Ǫ���������
	int getDefense() const { return Defense; } //��e�Ǫ������m��
	int getSpeed() const { return Speed; } //��e�Ǫ����t��
	int getAbility() const { return Ability; } //��e�Ǫ����ޯ�
	int getsituation() const { return situations; }	//���o���S���ϥιL
	int getusingful() const { return usingful; }	//���o���A
	int getNo() const { return No; }	//���o�s��
	int gettype_num(string type) const
	{
		for (int i = 1; i < 19; i++)
		{
			if (type == types[i])
				return i;
		}
	}	//���o�ݩʽs��
	string getName(int i) { return poke.get_Name(i); } //���o�W��
	string getType() const { return Type; } //���o�ݩ�
	virtual void attack(Monster &m) {}
	virtual void showStats(int x, int y) {}
	void attack_information(Monster &attacker, Monster &attacked, int attack_value)
	{
		locate(50, 42);
		cout << attacker.getName(attacker.getNo()) << "����" << attacked.getName(attacked.getNo()) << " ,"
			<< attacked.getName(attacked.getNo()) << "�l���F" << attack_value << "�I��q";
	}
	void attack_link(Monster &attacker, Monster &attacked, int attack_value)
	{
		if (attacker.getAbility() == 0) //normal
			set_normal(attacker, attacked, attack_value);
		else if (attacker.getAbility() == 1) //headl �ͩR��_
			set_heal_ability(attacker, attacked, attack_value);
		else if (attacker.getAbility() == 2) //burning �U�N�ˮ`
			set_Burning_ability(attacker, attacked, attack_value);
		else if (attacker.getAbility() == 3) //������O
			attack_information(attacker, attacked, attack_value);
		else if (attacker.getAbility() == 4) //�K�̯�O
			attack_information(attacker, attacked, attack_value);
		else if (attacker.getAbility() == 5) //�l���O
			set_Leech_Life(attacker, attacked, attack_value);
		else if (attacker.getAbility() == 6) //�{�ׯ�O
			attack_information(attacker, attacked, attack_value);
		else if (attacker.getAbility() == 7) //��������
			set_Double_Attack(attacker, attacked, attack_value);
		else if (attacker.getAbility() == 8) //���r 
		{
			if (attacker.getusingful() == 0) //�Ĥ@���W��
			{
				attacker.setusingful(1); //�N��n�ιL
				set_Poison(attacker, attacked, attack_value); //�]�m���A2
			}
			attack_information(attacker, attacked, attack_value);
		}
		else if (attacker.getAbility() == 9) //���C�t��
		{
			if (attacked.getAbility() == 4) //�K��
			{
				attack_information(attacker, attacked, attack_value);
				if (attacker.getusingful() != 1)
					set_Immunology(attacker, attacked, attack_value);
			}
			else
			{
				if (attacker.getusingful() != 1)
					set_Lower_Speed(attacker, attacked, attack_value);
				attack_information(attacker, attacked, attack_value);
			}
			attacker.setusingful(1);
		}
		else if (attacker.getAbility() == 10) //��˯�O
			attack_information(attacker, attacked, attack_value);
		else if (attacker.getAbility() == 11) //���C���m
		{
			if (attacked.getAbility() == 4) //�K��
			{
				attack_information(attacker, attacked, attack_value);
				if (attacker.getusingful() != 1)
					set_Immunology(attacker, attacked, attack_value);
			}
			else
			{
				if (attacker.getusingful() != 1)
					set_Lower_Defence(attacker, attacked, attack_value);
				attack_information(attacker, attacked, attack_value);
			}
			attacker.setusingful(1); //�N��n�ιL
		}
		else if (attacker.getAbility() == 12) //���C����
		{
			if (attacked.getAbility() == 4) //�K��
			{
				attack_information(attacker, attacked, attack_value);
				if (attacker.getusingful() != 1)
					set_Immunology(attacker, attacked, attack_value);
			}
			else
			{
				if (attacker.getusingful() != 1)
					set_Lower_Attack(attacker, attacked, attack_value);
				attack_information(attacker, attacked, attack_value);
			}
			attacker.setusingful(1); //�N��n�ιL
		}
	}
	void use_ability(Monster &attacker, Monster &attacked, int attack_value)
	{
		if (attacked.getAbility() == 0) //normal
			attack_link(attacker, attacked, attack_value);
		else if (attacked.getAbility() == 1) //headl �ͩR��_
			attack_link(attacker, attacked, attack_value);
		else if (attacked.getAbility() == 2) //burning �U�N�ˮ`
			attack_link(attacker, attacked, attack_value);
		else if (attacked.getAbility() == 3) //������O
		{
			attack_link(attacker, attacked, attack_value);
			set_Counter_Attack_ability(attacker, attacked, attack_value);
		}
		else if (attacked.getAbility() == 4) //�K�̯�O
			attack_link(attacker, attacked, attack_value);
		else if (attacked.getAbility() == 5) //�l���O
			attack_link(attacker, attacked, attack_value);
		else if (attacked.getAbility() == 6) //�{�ׯ�O
		{
			int avoid = 0;
			set_Avoid(attacker, attacked, attack_value, avoid); //���g�{�׸�T
			if (avoid == 1)
				avoid = 0;
			else
				attack_link(attacker, attacked, attack_value);
		}
		else if (attacked.getAbility() == 7) //��������
			attack_link(attacker, attacked, attack_value);
		else if (attacked.getAbility() == 8) //���r
			attack_link(attacker, attacked, attack_value);
		else if (attacked.getAbility() == 9) //���C�t��
			attack_link(attacker, attacked, attack_value);
		else if (attacked.getAbility() == 10) //���
			set_Rock_Skin(attacker, attacked, attack_value);
		else if (attacked.getAbility() == 11) ////���C���m
			attack_link(attacker, attacked, attack_value);
		else if (attacked.getAbility() == 12) ////���C����
			attack_link(attacker, attacked, attack_value);


	}
	void set_Immunology(Monster &attacker, Monster &attacked, int attack_value)
	{
		locate(50, 46);
		cout << attacked.getName(attacked.getNo()) << "�o�ʧK�̯�O,"
			<< attacker.getName(attacker.getNo()) << "�ҵo�ʪ��t����O�L��";
	}
	void set_normal(Monster &attacker, Monster &attacked, int attack_value)
	{
		attack_information(attacker, attacked, attack_value);
	}
	void set_Lower_Attack(Monster &attacker, Monster &attacked, int attack_value)
	{
		//attacked.setsituation(5);
		attacked.setAttack(attacked.getAttack() - 2);
		locate(50, 44);
		cout << attacked.getName(attacked.getNo()) << "����" << attacker.getName(attacker.getNo())
			<< "�ޯ઺�v�T,�����O�U��2";
	}
	void set_Lower_Defence(Monster &attacker, Monster &attacked, int attack_value)
	{
		//attacked.setsituation(4);
		attacked.setDefense(attacked.getDefense() - 2);
		locate(50, 44);
		cout << attacked.getName(attacked.getNo()) << "����" << attacker.getName(attacker.getNo())
			<< "�ޯ઺�v�T,���m�O�U��2";
	}
	void set_Lower_Speed(Monster &attacker, Monster &attacked, int attack_value)
	{
		//attacked.setsituation(3);
		attacked.setSpeed(attacked.getSpeed() - 2);
		locate(50, 44);
		cout << attacked.getName(attacked.getNo()) << "����" << attacker.getName(attacker.getNo())
			<< "�ޯ઺�v�T,�t�פU��2";
	}
	void set_Poison(Monster &attacker, Monster &attacked, int attack_value) //���r
	{
		attacked.setsituation(2); //�}�l���r
	}
	void set_heal_ability(Monster &attacker, Monster &attacked, int attack_value) //�ͩR��_
	{
		if (attacker.getHP() != attacker.getMaxHP())
		{
			if (attacker.getHP() < attacker.getMaxHP())
			{
				attacker.setHP(attacker.getHP() + 3);
				if (attacker.getHP() > attacker.getMaxHP())
					attacker.setHP(attacker.getMaxHP());
			}
			locate(55, 43);
			cout << attacker.getName(attacker.getNo()) << "�ϥΧޯ�,��_�F " << "3 �I�ͩR��";
		}
		attack_information(attacker, attacked, attack_value);
	}
	void set_Burning_ability(Monster &attacker, Monster &attacked, int attack_value) //�U�N�ˮ`
	{
		int ran = rand() % 3 + 1;
		attacked.setHP(attacked.getHP() - ran);
		if (attacked.getHP() < 0)
			attacked.setHP(0);
		locate(55, 44);
		cout << attacked.getName(attacked.getNo()) << "�]�N�˷l���F " << ran << " �I��q";
		attack_information(attacker, attacked, attack_value);
	}
	void set_Counter_Attack_ability(Monster &attacker, Monster &attacked, int attack_value) //������O
	{
		attacker.setHP(attacker.getHP() - attack_value / 5);
		if (attacker.getHP() < 0)
			attacker.setHP(0);
		locate(55, 45);
		cout << attacked.getName(attacked.getNo()) << "�ϼu�F " << attack_value / 5
			<< " �I�ˮ`��" << attacker.getName(attacker.getNo());
		attack_information(attacker, attacked, attack_value);
	}
	void set_Leech_Life(Monster &attacker, Monster &attacked, int attack_value) //�l���O
	{
		int bleed = rand() % 2 + 2; //�l�h�֦�
		attacker.setHP(attacker.getHP() + bleed);
		if (attacker.getHP() > attacker.getMaxHP())
			attacker.setHP(attacker.getMaxHP());

		attacked.setHP(attacked.getHP() - bleed);
		if (attacked.getHP() < 0)
			attacked.setHP(0);
		locate(50, 44);
		cout << attacker.getName(attacker.getNo()) << "�l���F " << bleed
			<< " �I��q ," << attacked.getName(attacked.getNo()) << "���h�F" << bleed << "�I��q";
		attack_information(attacker, attacked, attack_value);
	}
	void set_Rock_Skin(Monster &attacker, Monster &attacked, int attack_value) //��˯�O
	{
		if (attack_value > 2) //�N������Ȥj��2
		{
			attacked.setHP(attacked.getHP() + 2);
			locate(55, 45);
			cout << attacked.getName(attacked.getNo()) << "�o�ʤF��˯�O,���쪺�ˮ`-2";
			attack_link(attacker, attacked, attack_value);
		}
		else
		{
			attacked.setHP(attacked.getHP() + attack_value);
			locate(50, 45);
			cout << attacked.getName(attacked.getNo()) << "�o�ʤF��˯�O,���쪺�ˮ`-" << attack_value;
			attack_link(attacker, attacked, attack_value);
		}

	}
	void set_Avoid(Monster &attacker, Monster &attacked, int attack_value, int &avoid) //�{�ׯ�O
	{
		int ran = rand() % 5 + 1;
		if (ran == 3) //�o�ʰ{��
		{
			attacked.setHP(attacked.getHP() + attack_value);
			avoid = 1;
			locate(55, 45);
			cout << attacked.getName(attacked.getNo()) << " �{�פF " << attacker.getName(attacker.getNo()) << " ������";
		}
	}
	void set_Double_Attack(Monster &attacker, Monster &attacked, int attack_value) //��������
	{
		int ran = rand() % 5 + 1;
		if (ran == 1) //�o����������
		{
			locate(55, 45);
			cout << attacker.getName(attacker.getNo()) << "�o�ʤF�ޯ�,��������!!";
			if (is_Avoid() == false) //���o�ʰ{��
			{
				attacked.setHP(attacked.getHP() - attack_value);
				if (attacked.getHP() < 0)
					attacked.setHP(0);
				locate(50, 46);
				cout << attacker.getName(attacker.getNo()) << "����" << attacked.getName(attacked.getNo()) << " ,"
					<< attacked.getName(attacked.getNo()) << "�l���F" << attack_value << "�I��q";
			}
			else //�o�ʰ{��
			{
				locate(55, 46);
				cout << attacked.getName(attacked.getNo()) << "�{�פF"<< attacker.getName(attacker.getNo()) <<"����������" << endl;
			}
		}
		attack_information(attacker, attacked, attack_value);
	}
	bool is_Avoid() //�O�_�{��
	{
		int ran = rand() % 5 + 1;
		if (ran == 1)
			return true;
		else
			return false;
	}
	void poison_location()
	{
		setHP(getHP() - 2);
		locate(55, 47);
		cout << getName(getNo()) << "�]�����r,�l���F" << 2 << "�I��q";
	}
	void situation_location(int x, int y)
	{
		if (getsituation() == 2)
		{
			if (x == 82)
			{
				locate(x+20, y-15);
				cout << "���r�F (�ѡ\��)";
			}
			else if (x == 40)
			{
				locate(x - 20, y - 15);
				cout << "���r�F (�ѡ\��)";
			}
		}
	}
private:
	int HP;
	int MaxHP;
	int Attack;
	int Defense;
	int Speed;
	int Ability;
	string Type;
	int No;
	int situations = 0;
	int usingful = 0;
	Pokemon poke;
};

class Bulbasaur :public Monster
{
public:
	Bulbasaur() : Monster(values[1][1], values[1][1], values[1][2], values[1][3],
		values[1][4], values[1][5], 1, types[5]) {}
	void attack(Monster &left) //left�Q������
	{
		int i = gettype_num(getType());
		int j = left.gettype_num(left.getType());
		int attack_value = (getAttack() - left.getDefense())*type_num[i][j]; //���o������
		if (getsituation() == 2)
			poison_location();
		if (getHP() > 0)
		{
			left.setHP(left.getHP() - attack_value); //����
			use_ability(*this, left, attack_value); //�ϥί�O
		}
	}
	void showStats(int x, int y)
	{
		locate(x, y);
		cout << "Bulbasaur( " << getHP() << " / " << getMaxHP() << " )";
		if (getsituation() != 1)
			situation_location(x, y);
	}

private:
	int No;
};


class Ivysaur :public Monster
{
public:
	Ivysaur() :Monster(values[2][1], values[2][1], values[2][2],
		values[2][3], values[2][4], values[2][5], 2, types[5]) {};
	void attack(Monster &left) //left�Q������
	{
		int i = gettype_num(getType());
		int j = left.gettype_num(left.getType());
		int attack_value = (getAttack() - left.getDefense())*type_num[i][j]; //���o������
		if (getsituation() == 2)
			poison_location();
		if (getHP() > 0)
		{
			left.setHP(left.getHP() - attack_value); //����
			use_ability(*this, left, attack_value); //�ϥί�O
		}
	}
	void showStats(int x, int y)
	{
		locate(x, y);
		cout << "Ivysaur( " << getHP() << " / " << getMaxHP() << " )";
		if (getsituation() != 1)
			situation_location(x, y);

	}
private:
	int No;
};

class Venusaur :public Monster
{
public:
	Venusaur() :Monster(values[3][1], values[3][1], values[3][2],
		values[3][3], values[3][4], values[3][5], 3, types[5]) {};
	void attack(Monster &left) //left�Q������
	{
		int i = gettype_num(getType());
		int j = left.gettype_num(left.getType());
		int attack_value = (getAttack() - left.getDefense())*type_num[i][j]; //���o������
		if (getsituation() == 2)
			poison_location();
		if (getHP() > 0)
		{
			left.setHP(left.getHP() - attack_value); //����
			use_ability(*this, left, attack_value); //�ϥί�O
		}
	}
	void showStats(int x, int y)
	{
		locate(x, y);
		cout << "Venusaur( " << getHP() << " / " << getMaxHP() << " )";
		if (getsituation() != 1)
			situation_location(x, y);

	}
private:
	int No;
};

class Charmander :public Monster
{
public:
	Charmander()
		:Monster(values[4][1], values[4][1], values[4][2],
			values[4][3], values[4][4], values[4][5], 4, types[2]) {};
	void attack(Monster &left) //left�Q������
	{
		int i = gettype_num(getType());
		int j = left.gettype_num(left.getType());
		int attack_value = (getAttack() - left.getDefense())*type_num[i][j]; //���o������
		if (getsituation() == 2)
			poison_location();
		if (getHP() > 0)
		{
			left.setHP(left.getHP() - attack_value); //����
			use_ability(*this, left, attack_value); //�ϥί�O
		}
	}
	void showStats(int x, int y)
	{
		locate(x, y);
		cout << "Charmander( " << getHP() << " / " << getMaxHP() << " )";
		if (getsituation() != 1)
			situation_location(x, y);

	}
private:
	int No;
};

class Charmeleon
	:public Monster
{
public:
	Charmeleon()
		:Monster(values[5][1], values[5][1], values[5][2],
			values[5][3], values[5][4], values[5][5], 5, types[2]) {};
	void attack(Monster &left) //left�Q������
	{
		int i = gettype_num(getType());
		int j = left.gettype_num(left.getType());
		int attack_value = (getAttack() - left.getDefense())*type_num[i][j]; //���o������
		if (getsituation() == 2)
			poison_location();
		if (getHP() > 0)
		{
			left.setHP(left.getHP() - attack_value); //����
			use_ability(*this, left, attack_value); //�ϥί�O
		}
	}
	void showStats(int x, int y)
	{
		locate(x, y);
		cout << "Charmeleon( " << getHP() << " / " << getMaxHP() << " )";
		if (getsituation() != 1)
			situation_location(x, y);

	}
private:
	int No;
};

class Charizard
	:public Monster
{
public:
	Charizard()
		:Monster(values[6][1], values[6][1], values[6][2],
			values[6][3], values[6][4], values[6][5], 6, types[2]) {};
	void attack(Monster &left) //left�Q������
	{
		int i = gettype_num(getType());
		int j = left.gettype_num(left.getType());
		int attack_value = (getAttack() - left.getDefense())*type_num[i][j]; //���o������
		if (getsituation() == 2)
			poison_location();
		if (getHP() > 0)
		{
			left.setHP(left.getHP() - attack_value); //����
			use_ability(*this, left, attack_value); //�ϥί�O
		}
	}
	void showStats(int x, int y)
	{
		locate(x, y);
		cout << "Charizard( " << getHP() << " / " << getMaxHP() << " )";
		if (getsituation() != 1)
			situation_location(x, y);

	}
private:
	int No;
};

class Squirtle
	:public Monster
{
public:
	Squirtle()
		:Monster(values[7][1], values[7][1], values[7][2],
			values[7][3], values[7][4], values[7][5], 7, types[3]) {};
	void attack(Monster &left) //left�Q������
	{
		int i = gettype_num(getType());
		int j = left.gettype_num(left.getType());
		int attack_value = (getAttack() - left.getDefense())*type_num[i][j]; //���o������
		if (getsituation() == 2)
			poison_location();
		if (getHP() > 0)
		{
			left.setHP(left.getHP() - attack_value); //����
			use_ability(*this, left, attack_value); //�ϥί�O
		}
	}
	void showStats(int x, int y)
	{
		locate(x, y);
		cout << "Squirtle( " << getHP() << " / " << getMaxHP() << " )";
		if (getsituation() != 1)
			situation_location(x, y);

	}
private:
	int No;
};

class Wartortle
	:public Monster
{
public:
	Wartortle()
		:Monster(values[8][1], values[8][1], values[8][2],
			values[8][3], values[8][4], values[8][5], 8, types[3]) {};
	void attack(Monster &left) //left�Q������
	{
		int i = gettype_num(getType());
		int j = left.gettype_num(left.getType());
		int attack_value = (getAttack() - left.getDefense())*type_num[i][j]; //���o������
		if (getsituation() == 2)
			poison_location();
		if (getHP() > 0)
		{
			left.setHP(left.getHP() - attack_value); //����
			use_ability(*this, left, attack_value); //�ϥί�O
		}
	}
	void showStats(int x, int y)
	{
		locate(x, y);
		cout << "Wartortle( " << getHP() << " / " << getMaxHP() << " )";
		if (getsituation() != 1)
			situation_location(x, y);
	}
private:
	int No;
};

class Blastoise
	:public Monster
{
public:
	Blastoise()
		:Monster(values[9][1], values[9][1], values[9][2],
			values[9][3], values[9][4], values[9][5], 9, types[3]) {};
	void attack(Monster &left) //left�Q������
	{
		int i = gettype_num(getType());
		int j = left.gettype_num(left.getType());
		int attack_value = (getAttack() - left.getDefense())*type_num[i][j]; //���o������
		if (getsituation() == 2)
			poison_location();
		if (getHP() > 0)
		{
			left.setHP(left.getHP() - attack_value); //����
			use_ability(*this, left, attack_value); //�ϥί�O
		}
	}
	void showStats(int x, int y)
	{
		locate(x, y);
		cout << "Blastoise( " << getHP() << " / " << getMaxHP() << " )";
		if (getsituation() != 1)
			situation_location(x, y);

	}
private:
	int No;
};

class Caterpie
	:public Monster
{
public:
	Caterpie()
		:Monster(values[10][1], values[10][1], values[10][2],
			values[10][3], values[10][4], values[10][5], 10, types[12]) {};
	void attack(Monster &left) //left�Q������
	{
		int i = gettype_num(getType());
		int j = left.gettype_num(left.getType());
		int attack_value = (getAttack() - left.getDefense())*type_num[i][j]; //���o������
		if (getsituation() == 2)
			poison_location();
		if (getHP() > 0)
		{
			left.setHP(left.getHP() - attack_value); //����
			use_ability(*this, left, attack_value); //�ϥί�O
		}
	}
	void showStats(int x, int y)
	{
		locate(x, y);
		cout << "Caterpie( " << getHP() << " / " << getMaxHP() << " )";
		if (getsituation() != 1)
			situation_location(x, y);

	}
private:
	int No;
};

class Metapod
	:public Monster
{
public:
	Metapod()
		:Monster(values[11][1], values[11][1], values[11][2],
			values[11][3], values[11][4], values[11][5], 11, types[12]) {};
	void attack(Monster &left) //left�Q������
	{
		int i = gettype_num(getType());
		int j = left.gettype_num(left.getType());
		int attack_value = (getAttack() - left.getDefense())*type_num[i][j]; //���o������
		if (getsituation() == 2)
			poison_location();
		if (getHP() > 0)
		{
			left.setHP(left.getHP() - attack_value); //����
			use_ability(*this, left, attack_value); //�ϥί�O
		}
	}
	void showStats(int x, int y)
	{
		locate(x, y);
		cout << "Metapod( " << getHP() << " / " << getMaxHP() << " )";
		if (getsituation() != 1)
			situation_location(x, y);

	}
private:
	int No;
};

class Butterfree
	:public Monster
{
public:
	Butterfree()
		:Monster(values[12][1], values[12][1], values[12][2],
			values[12][3], values[12][4], values[12][5], 12, types[12]) {};
	void attack(Monster &left) //left�Q������
	{
		int i = gettype_num(getType());
		int j = left.gettype_num(left.getType());
		int attack_value = (getAttack() - left.getDefense())*type_num[i][j]; //���o������
		if (getsituation() == 2)
			poison_location();
		if (getHP() > 0)
		{
			left.setHP(left.getHP() - attack_value); //����
			use_ability(*this, left, attack_value); //�ϥί�O
		}
	}
	void showStats(int x, int y)
	{
		locate(x, y);
		cout << "Butterfree( " << getHP() << " / " << getMaxHP() << " )";
		if (getsituation() != 1)
			situation_location(x, y);

	}
private:
	int No;
};

class Weedle
	:public Monster
{
public:
	Weedle()
		:Monster(values[13][1], values[13][1], values[13][2],
			values[13][3], values[13][4], values[13][5], 13, types[12]) {};
	void attack(Monster &left) //left�Q������
	{
		int i = gettype_num(getType());
		int j = left.gettype_num(left.getType());
		int attack_value = (getAttack() - left.getDefense())*type_num[i][j]; //���o������
		if (getsituation() == 2)
			poison_location();
		if (getHP() > 0)
		{
			left.setHP(left.getHP() - attack_value); //����
			use_ability(*this, left, attack_value); //�ϥί�O
		}
	}
	void showStats(int x, int y)
	{
		locate(x, y);
		cout << "Weedle( " << getHP() << " / " << getMaxHP() << " )";
		if (getsituation() != 1)
			situation_location(x, y);

	}
private:
	int No;
};

class Kakuna
	:public Monster
{
public:
	Kakuna()
		:Monster(values[14][1], values[14][1], values[14][2],
			values[14][3], values[14][4], values[14][5], 14, types[12]) {};
	void attack(Monster &left) //left�Q������
	{
		int i = gettype_num(getType());
		int j = left.gettype_num(left.getType());
		int attack_value = (getAttack() - left.getDefense())*type_num[i][j]; //���o������
		if (getsituation() == 2)
			poison_location();
		if (getHP() > 0)
		{
			left.setHP(left.getHP() - attack_value); //����
			use_ability(*this, left, attack_value); //�ϥί�O
		}
	}
	void showStats(int x, int y)
	{
		locate(x, y);
		cout << "Kakuna( " << getHP() << " / " << getMaxHP() << " )";
		if (getsituation() != 1)
			situation_location(x, y);

	}
private:
	int No;
};

class Beedrill
	:public Monster
{
public:
	Beedrill()
		:Monster(values[15][1], values[15][1], values[15][2],
			values[15][3], values[15][4], values[15][5], 15, types[12]) {};
	void attack(Monster &left) //left�Q������
	{
		int i = gettype_num(getType());
		int j = left.gettype_num(left.getType());
		int attack_value = (getAttack() - left.getDefense())*type_num[i][j]; //���o������
		if (getsituation() == 2)
			poison_location();
		if (getHP() > 0)
		{
			left.setHP(left.getHP() - attack_value); //����
			use_ability(*this, left, attack_value); //�ϥί�O
		}
	}
	void showStats(int x, int y)
	{
		locate(x, y);
		cout << "Beedrill( " << getHP() << " / " << getMaxHP() << " )";
		if (getsituation() != 1)
			situation_location(x, y);

	}
private:
	int No;
};

class Pidgey
	:public Monster
{
public:
	Pidgey()
		:Monster(values[16][1], values[16][1], values[16][2],
			values[16][3], values[16][4], values[16][5], 16, types[10]) {};
	void attack(Monster &left) //left�Q������
	{
		int i = gettype_num(getType());
		int j = left.gettype_num(left.getType());
		int attack_value = (getAttack() - left.getDefense())*type_num[i][j]; //���o������
		if (getsituation() == 2)
			poison_location();
		if (getHP() > 0)
		{
			left.setHP(left.getHP() - attack_value); //����
			use_ability(*this, left, attack_value); //�ϥί�O
		}
	}
	void showStats(int x, int y)
	{
		locate(x, y);
		cout << "Pidgey( " << getHP() << " / " << getMaxHP() << " )";
		if (getsituation() != 1)
			situation_location(x, y);

	}
private:
	int No;
};

class Pidgeotto
	:public Monster
{
public:
	Pidgeotto()
		:Monster(values[17][1], values[17][1], values[17][2],
			values[17][3], values[17][4], values[17][5], 17, types[10]) {};
	void attack(Monster &left) //left�Q������
	{
		int i = gettype_num(getType());
		int j = left.gettype_num(left.getType());
		int attack_value = (getAttack() - left.getDefense())*type_num[i][j]; //���o������
		if (getsituation() == 2)
			poison_location();
		if (getHP() > 0)
		{
			left.setHP(left.getHP() - attack_value); //����
			use_ability(*this, left, attack_value); //�ϥί�O
		}
	}
	void showStats(int x, int y)
	{
		locate(x, y);
		cout << "Pidgeotto( " << getHP() << " / " << getMaxHP() << " )";
		if (getsituation() != 1)
			situation_location(x, y);

	}
private:
	int No;
};

class Pidgeot
	:public Monster
{
public:
	Pidgeot()
		:Monster(values[18][1], values[18][1], values[18][2],
			values[18][3], values[18][4], values[18][5], 18, types[10]) {};
	void attack(Monster &left) //left�Q������
	{
		int i = gettype_num(getType());
		int j = left.gettype_num(left.getType());
		int attack_value = (getAttack() - left.getDefense())*type_num[i][j]; //���o������
		if (getsituation() == 2)
			poison_location();
		if (getHP() > 0)
		{
			left.setHP(left.getHP() - attack_value); //����
			use_ability(*this, left, attack_value); //�ϥί�O
		}
	}
	void showStats(int x, int y)
	{
		locate(x, y);
		cout << "Pidgeot( " << getHP() << " / " << getMaxHP() << " )";
		if (getsituation() != 1)
			situation_location(x, y);

	}
private:
	int No;
};

class Rattata
	:public Monster
{
public:
	Rattata()
		:Monster(values[19][1], values[19][1], values[19][2],
			values[19][3], values[19][4], values[19][5], 19, types[1]) {};
	void attack(Monster &left) //left�Q������
	{
		int i = gettype_num(getType());
		int j = left.gettype_num(left.getType());
		int attack_value = (getAttack() - left.getDefense())*type_num[i][j]; //���o������
		if (getsituation() == 2)
			poison_location();
		if (getHP() > 0)
		{
			left.setHP(left.getHP() - attack_value); //����
			use_ability(*this, left, attack_value); //�ϥί�O
		}
	}
	void showStats(int x, int y)
	{
		locate(x, y);
		cout << "Rattata( " << getHP() << " / " << getMaxHP() << " )";
		if (getsituation() != 1)
			situation_location(x, y);

	}
private:
	int No;
};

class Raticate
	:public Monster
{
public:
	Raticate()
		:Monster(values[20][1], values[20][1], values[20][2],
			values[20][3], values[20][4], values[20][5], 20, types[1]) {};
	void attack(Monster &left) //left�Q������
	{
		int i = gettype_num(getType());
		int j = left.gettype_num(left.getType());
		int attack_value = (getAttack() - left.getDefense())*type_num[i][j]; //���o������
		if (getsituation() == 2)
			poison_location();
		if (getHP() > 0)
		{
			left.setHP(left.getHP() - attack_value); //����
			use_ability(*this, left, attack_value); //�ϥί�O
		}
	}
	void showStats(int x, int y)
	{
		locate(x, y);
		cout << "Raticate( " << getHP() << " / " << getMaxHP() << " )";
		if (getsituation() != 1)
			situation_location(x, y);

	}
private:
	int No;
};

class Spearow
	:public Monster
{
public:
	Spearow()
		:Monster(values[21][1], values[21][1], values[21][2],
			values[21][3], values[21][4], values[21][5], 21, types[10]) {};
	void attack(Monster &left) //left�Q������
	{
		int i = gettype_num(getType());
		int j = left.gettype_num(left.getType());
		int attack_value = (getAttack() - left.getDefense())*type_num[i][j]; //���o������
		if (getsituation() == 2)
			poison_location();
		if (getHP() > 0)
		{
			left.setHP(left.getHP() - attack_value); //����
			use_ability(*this, left, attack_value); //�ϥί�O
		}
	}
	void showStats(int x, int y)
	{
		locate(x, y);
		cout << "Spearow( " << getHP() << " / " << getMaxHP() << " )";
		if (getsituation() != 1)
			situation_location(x, y);
	}
private:
	int No;
};

class Fearow
	:public Monster
{
public:
	Fearow()
		:Monster(values[22][1], values[22][1], values[22][2],
			values[22][3], values[22][4], values[22][5], 22, types[10]) {};
	void attack(Monster &left) //left�Q������
	{
		int i = gettype_num(getType());
		int j = left.gettype_num(left.getType());
		int attack_value = (getAttack() - left.getDefense())*type_num[i][j]; //���o������
		if (getsituation() == 2)
			poison_location();
		if (getHP() > 0)
		{
			left.setHP(left.getHP() - attack_value); //����
			use_ability(*this, left, attack_value); //�ϥί�O
		}
	}
	void showStats(int x, int y)
	{
		locate(x, y);
		cout << "Fearow( " << getHP() << " / " << getMaxHP() << " )";
		if (getsituation() != 1)
			situation_location(x, y);

	}
private:
	int No;
};

class Ekans
	:public Monster
{
public:
	Ekans()
		:Monster(values[23][1], values[23][1], values[23][2],
			values[23][3], values[23][4], values[23][5], 23, types[8]) {};
	void attack(Monster &left) //left�Q������
	{
		int i = gettype_num(getType());
		int j = left.gettype_num(left.getType());
		int attack_value = (getAttack() - left.getDefense())*type_num[i][j]; //���o������
		if (getsituation() == 2)
			poison_location();
		if (getHP() > 0)
		{
			left.setHP(left.getHP() - attack_value); //����
			use_ability(*this, left, attack_value); //�ϥί�O
		}
		use_ability(*this, left, attack_value); //�ϥί�O
	}
	void showStats(int x, int y)
	{
		locate(x, y);
		cout << "Ekans( " << getHP() << " / " << getMaxHP() << " )";
		if (getsituation() != 1)
			situation_location(x, y);
	}
private:
	int No;
};

class Arbok
	:public Monster
{
public:
	Arbok()
		:Monster(values[24][1], values[24][1], values[24][2],
			values[24][3], values[24][4], values[24][5], 24, types[8]) {};
	void attack(Monster &left) //left�Q������
	{
		int i = gettype_num(getType());
		int j = left.gettype_num(left.getType());
		int attack_value = (getAttack() - left.getDefense())*type_num[i][j]; //���o������
		if (getsituation() == 2)
			poison_location();
		if (getHP() > 0)
		{
			left.setHP(left.getHP() - attack_value); //����
			use_ability(*this, left, attack_value); //�ϥί�O
		}
	}
	void showStats(int x, int y)
	{
		locate(x, y);
		cout << "Arbok( " << getHP() << " / " << getMaxHP() << " )";
		if (getsituation() != 1)
			situation_location(x, y);
	}
private:
	int No;
};

class Pikachu
	:public Monster
{
public:
	Pikachu()
		:Monster(values[25][1], values[25][1], values[25][2],
			values[25][3], values[25][4], values[25][5], 25, types[4]) {};
	void attack(Monster &left) //left�Q������
	{
		int i = gettype_num(getType());
		int j = left.gettype_num(left.getType());
		int attack_value = (getAttack() - left.getDefense())*type_num[i][j]; //���o������
		if (getsituation() == 2)
			poison_location();
		if (getHP() > 0)
		{
			left.setHP(left.getHP() - attack_value); //����
			use_ability(*this, left, attack_value); //�ϥί�O
		}
	}
	void showStats(int x, int y)
	{
		locate(x, y);
		cout << "Pikachu( " << getHP() << " / " << getMaxHP() << " )";
		if (getsituation() != 1)
			situation_location(x, y);
	}
private:
	int No;
};

class Raichu
	:public Monster
{
public:
	Raichu()
		:Monster(values[26][1], values[26][1], values[26][2],
			values[26][3], values[26][4], values[26][5], 26, types[4]) {};
	void attack(Monster &left) //left�Q������
	{
		int i = gettype_num(getType());
		int j = left.gettype_num(left.getType());
		int attack_value = (getAttack() - left.getDefense())*type_num[i][j]; //���o������
		if (getsituation() == 2)
			poison_location();
		if (getHP() > 0)
		{
			left.setHP(left.getHP() - attack_value); //����
			use_ability(*this, left, attack_value); //�ϥί�O
		}
	}
	void showStats(int x, int y)
	{
		locate(x, y);
		cout << "Raichu( " << getHP() << " / " << getMaxHP() << " )";
		if (getsituation() != 1)
			situation_location(x, y);
	}
private:
	int No;
};

class Sandshrew
	:public Monster
{
public:
	Sandshrew()
		:Monster(values[27][1], values[27][1], values[27][2],
			values[27][3], values[27][4], values[27][5], 27, types[9]) {};
	void attack(Monster &left) //left�Q������
	{
		int i = gettype_num(getType());
		int j = left.gettype_num(left.getType());
		int attack_value = (getAttack() - left.getDefense())*type_num[i][j]; //���o������
		if (getsituation() == 2)
			poison_location();
		if (getHP() > 0)
		{
			left.setHP(left.getHP() - attack_value); //����
			use_ability(*this, left, attack_value); //�ϥί�O
		}
	}
	void showStats(int x, int y)
	{
		locate(x, y);
		cout << "Sandshrew( " << getHP() << " / " << getMaxHP() << " )";
		if (getsituation() != 1)
			situation_location(x, y);
	}
private:
	int No;
};

class Sandslash
	:public Monster
{
public:
	Sandslash()
		:Monster(values[28][1], values[28][1], values[28][2],
			values[28][3], values[28][4], values[28][5], 28, types[9]) {};
	void attack(Monster &left) //left�Q������
	{
		int i = gettype_num(getType());
		int j = left.gettype_num(left.getType());
		int attack_value = (getAttack() - left.getDefense())*type_num[i][j]; //���o������
		if (getsituation() == 2)
			poison_location();
		if (getHP() > 0)
		{
			left.setHP(left.getHP() - attack_value); //����
			use_ability(*this, left, attack_value); //�ϥί�O
		}
	}
	void showStats(int x, int y)
	{
		locate(x, y);
		cout << "Sandslash( " << getHP() << " / " << getMaxHP() << " )";
		if (getsituation() != 1)
			situation_location(x, y);
	}
private:
	int No;
};

class Nidoran_W
	:public Monster
{
public:
	Nidoran_W()
		:Monster(values[29][1], values[29][1], values[29][2],
			values[29][3], values[29][4], values[29][5], 29, types[8]) {};
	void attack(Monster &left) //left�Q������
	{
		int i = gettype_num(getType());
		int j = left.gettype_num(left.getType());
		int attack_value = (getAttack() - left.getDefense())*type_num[i][j]; //���o������
		if (getsituation() == 2)
			poison_location();
		if (getHP() > 0)
		{
			left.setHP(left.getHP() - attack_value); //����
			use_ability(*this, left, attack_value); //�ϥί�O
		}
	}
	void showStats(int x, int y)
	{
		locate(x, y);
		cout << "Nidoran_W( " << getHP() << " / " << getMaxHP() << " )";
		if (getsituation() != 1)
			situation_location(x, y);
	}
private:
	int No;
};

class Nidorina
	:public Monster
{
public:
	Nidorina()
		:Monster(values[30][1], values[30][1], values[30][2],
			values[30][3], values[30][4], values[30][5], 30, types[8]) {};
	void attack(Monster &left) //left�Q������
	{
		int i = gettype_num(getType());
		int j = left.gettype_num(left.getType());
		int attack_value = (getAttack() - left.getDefense())*type_num[i][j]; //���o������
		if (getsituation() == 2)
			poison_location();
		if (getHP() > 0)
		{
			left.setHP(left.getHP() - attack_value); //����
			use_ability(*this, left, attack_value); //�ϥί�O
		}
	}
	void showStats(int x, int y)
	{
		locate(x, y);
		cout << "Nidorina( " << getHP() << " / " << getMaxHP() << " )";
		if (getsituation() != 1)
			situation_location(x, y);
	}
private:
	int No;
};

class Nidoqueen
	:public Monster
{
public:
	Nidoqueen()
		:Monster(values[31][1], values[31][1], values[31][2],
			values[31][3], values[31][4], values[31][5], 31, types[8]) {};
	void attack(Monster &left) //left�Q������
	{
		int i = gettype_num(getType());
		int j = left.gettype_num(left.getType());
		int attack_value = (getAttack() - left.getDefense())*type_num[i][j]; //���o������
		if (getsituation() == 2)
			poison_location();
		if (getHP() > 0)
		{
			left.setHP(left.getHP() - attack_value); //����
			use_ability(*this, left, attack_value); //�ϥί�O
		}
	}
	void showStats(int x, int y)
	{
		locate(x, y);
		cout << "Nidoqueen( " << getHP() << " / " << getMaxHP() << " )";
		if (getsituation() != 1)
			situation_location(x, y);
	}
private:
	int No;
};

class Nidoran_M
	:public Monster
{
public:
	Nidoran_M()
		:Monster(values[32][1], values[32][1], values[32][2],
			values[32][3], values[32][4], values[32][5], 32, types[8]) {};
	void attack(Monster &left) //left�Q������
	{
		int i = gettype_num(getType());
		int j = left.gettype_num(left.getType());
		int attack_value = (getAttack() - left.getDefense())*type_num[i][j]; //���o������
		if (getsituation() == 2)
			poison_location();
		if (getHP() > 0)
		{
			left.setHP(left.getHP() - attack_value); //����
			use_ability(*this, left, attack_value); //�ϥί�O
		}
	}
	void showStats(int x, int y)
	{
		locate(x, y);
		cout << "Nidoran_M( " << getHP() << " / " << getMaxHP() << " )";
		if (getsituation() != 1)
			situation_location(x, y);
	}
private:
	int No;
};

class Nidorino
	:public Monster
{
public:
	Nidorino()
		:Monster(values[33][1], values[33][1], values[33][2],
			values[33][3], values[33][4], values[33][5], 33, types[8]) {};
	void attack(Monster &left) //left�Q������
	{
		int i = gettype_num(getType());
		int j = left.gettype_num(left.getType());
		int attack_value = (getAttack() - left.getDefense())*type_num[i][j]; //���o������
		if (getsituation() == 2)
			poison_location();
		if (getHP() > 0)
		{
			left.setHP(left.getHP() - attack_value); //����
			use_ability(*this, left, attack_value); //�ϥί�O
		}
	}
	void showStats(int x, int y)
	{
		locate(x, y);
		cout << "Nidorino( " << getHP() << " / " << getMaxHP() << " )";
		if (getsituation() != 1)
			situation_location(x, y);
	}
private:
	int No;
};

class Nidoking

	:public Monster
{
public:
	Nidoking()
		:Monster(values[34][1], values[34][1], values[34][2],
			values[34][3], values[34][4], values[34][5], 34, types[8]) {};
	void attack(Monster &left) //left�Q������
	{
		int i = gettype_num(getType());
		int j = left.gettype_num(left.getType());
		int attack_value = (getAttack() - left.getDefense())*type_num[i][j]; //���o������
		if (getsituation() == 2)
			poison_location();
		if (getHP() > 0)
		{
			left.setHP(left.getHP() - attack_value); //����
			use_ability(*this, left, attack_value); //�ϥί�O
		}
	}
	void showStats(int x, int y)
	{
		locate(x, y);
		cout << "Nidoking( " << getHP() << " / " << getMaxHP() << " )";
		if (getsituation() != 1)
			situation_location(x, y);
	}
private:
	int No;
};
#endif // !ATTACKS_H




