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
	mapping() //construct 讀地圖
	{
		loadMap();
	}
	void loadMap() //讀地圖
	{
		char mark[150];
		ifstream inFile("yzumap.txt", ios::in);
		while (inFile.getline(mark, sizeof(mark), '\n'))
		{
			maps.push_back(string(mark));
		}
		
	}
	void show() //展示地圖
	{
		for (int i = 0; i < maps.size(); i++)
		{
			for (int j = 0; j < maps[i].size(); j++)
			{
				if (maps[i][j] == ';') //草地
				{
					//setColor(GREEN);
					setBackgroundColor(GREEN);
					cout << maps[i][j];
				}
				else if (maps[i][j] == '!') //樹木
				{
					//setColor(BROWN);
					setBackgroundColor(BROWN);
					cout << maps[i][j];
				}
				else if (maps[i][j] == '~') //水池
				{
					//setColor(BLUE);
					setBackgroundColor(BLUE);
					cout << maps[i][j];
				}
				else if (maps[i][j] == '#') //門口
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
	void configure() //修改地圖(為了方便)
	{
		char con[2] = " ";
		maps.insert(maps.begin(), con);
		for (int i = 0; i < maps.size(); i++)
			maps[i].insert(maps[i].begin(), con[0]);
	}
	char get_map_element(int i,int j) //取得元素
	{
		return maps[i][j];
	}
	
private:
	vector<string> maps;
};

#endif // MAP_H
