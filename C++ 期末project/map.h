#ifndef MAP_H
#define MAP_H
#include<iostream>
#include<vector>
#include<fstream>
#include"rlutil.h"
using namespace std;
using namespace rlutil;
class mapping
{
public:
	mapping() //construct Ū�a��
	{
		loadMap();
	}
	void loadMap() //Ū�a��
	{
		char mark[150];
		ifstream inFile("yzumap.txt", ios::in);
		while (inFile.getline(mark, sizeof(mark), '\n'))
		{
			maps.push_back(string(mark));
		}
		
	}
	void show() //�i�ܦa��
	{
		for (int i = 0; i < maps.size(); i++)
		{
			for (int j = 0; j < maps[i].size(); j++)
			{
				if (maps[i][j] == ';') //��a
				{
					//setColor(GREEN);
					setBackgroundColor(GREEN);
					cout << maps[i][j];
				}
				else if (maps[i][j] == '!') //���
				{
					//setColor(BROWN);
					setBackgroundColor(BROWN);
					cout << maps[i][j];
				}
				else if (maps[i][j] == '~') //����
				{
					//setColor(BLUE);
					setBackgroundColor(BLUE);
					cout << maps[i][j];
				}
				else if (maps[i][j] == '#') //���f
				{
					setColor(YELLOW);
					cout << maps[i][j];
				}
				else
					cout << maps[i][j];
				resetColor();
				setBackgroundColor(0);
			}
			cout << endl;
		}
	}
	void configure() //�ק�a��(���F��K)
	{
		char con[2] = " ";
		maps.insert(maps.begin(), con);
		for (int i = 0; i < maps.size(); i++)
			maps[i].insert(maps[i].begin(), con[0]);
	}
	char get_map_element(int i,int j) //���o����
	{
		return maps[i][j];
	}
	
private:
	vector<string> maps;
};

#endif // MAP_H
