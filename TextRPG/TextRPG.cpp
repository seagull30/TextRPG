#include <iostream>
#include "time.h"
#include "stdlib.h"

#include "Player.h"
#include "Monster.h"



using namespace std;

enum MAIN_MENU
{
	MM_NONE,
	MM_MAP,
	MM_ENFORSE,
	MM_EXIT
};

enum MAP_TYPE
{
	MT_NONE,
	MT_FORST,
	MT_DARKWOOD,
	MT_ROCK,
	MT_BACK
};

enum BATTLE
{
	BATTLE_NONE,
	BATTLE_ATTACK,
	BATTLE_BACK
};

int main()
{
	srand((unsigned int)time(0));

	// 플레이어 정보 설정
	Player player;

	cout << "이름 : ";
	std::string playername;
	cin >> playername;
	player.Create(playername);




	_tagMonster	monsterArr[MT_BACK - 1] = {};

	monsterArr[0].name = "고블린";
	monsterArr[0].attackMin = 20;
	monsterArr[0].attackMax = 30;
	monsterArr[0].armorMin = 2;
	monsterArr[0].armorMax = 5;
	monsterArr[0].hpMax = 100;
	monsterArr[0].hp = 100;
	monsterArr[0].mpMax = 10;
	monsterArr[0].mp = 10;
	monsterArr[0].level = 1;
	monsterArr[0].exp = 10;
	monsterArr[0].goldMin = 500;
	monsterArr[0].goldMax = 800;

	monsterArr[1].name = "트롤";
	monsterArr[1].attackMin = 80;
	monsterArr[1].attackMax = 130;
	monsterArr[1].armorMin = 60;
	monsterArr[1].armorMax = 90;
	monsterArr[1].hpMax = 200;
	monsterArr[1].hp = 200;
	monsterArr[1].mpMax = 100;
	monsterArr[1].mp = 100;
	monsterArr[1].level = 5;
	monsterArr[1].exp = 80;
	monsterArr[1].goldMin = 4000;
	monsterArr[1].goldMax = 7000;

	monsterArr[2].name = "드래곤";
	monsterArr[2].attackMin = 250;
	monsterArr[2].attackMax = 500;
	monsterArr[2].armorMin = 200;
	monsterArr[2].armorMax = 400;
	monsterArr[2].hpMax = 3000;
	monsterArr[2].hp = 3000;
	monsterArr[2].mpMax = 2000;
	monsterArr[2].mp = 2000;
	monsterArr[2].level = 10;
	monsterArr[2].exp = 30000;
	monsterArr[2].goldMin = 30000;
	monsterArr[2].goldMax = 70000;

	while (true)
	{
		system("cls");
		cout << endl << "========== 메인 메뉴 ==========" << endl << endl;
		cout << "1. 지도 " << endl;
		cout << "2. 강화 " << endl;
		cout << "메뉴를 선택하세요 : ";
		int menu;
		cin >> menu;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}

		if (menu == MM_EXIT)
		{
			break;
		}

		switch (menu)
		{
		case MM_MAP:
			while (true)
			{
				system("cls");
				cout << endl << "========== 맵 종류 ==========\n\n";
				cout << "1. 숲\n";
				cout << "2. 검은숲\n";
				cout << "3. 바위산\n";
				cout << "4. 뒤로가기\n";
				cout << "맵을 선택하세요 : ";
				cin >> menu;

				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}

				if (menu == MT_BACK)
				{
					break;
				}

				_tagMonster monster = monsterArr[menu - 1];

				while (true)
				{
					system("cls");
					switch (menu)
					{
					case MT_FORST:
						cout << "**********  숲  **********" << endl;
						break;
					case MT_DARKWOOD:
						cout << "********** 검은숲 **********" << endl;
						break;
					case MT_ROCK:
						cout << "********** 바위산 **********" << endl;
						break;
					}

					player.ShowStats();

					cout << "========== 몬스터 ==========" << endl;
					cout << "이름 : " << monster.name << "\t레벨 : " << monster.level << endl;
					cout << "체력 : " << monster.hp << " / " << monster.hpMax << "\t마나 : " << monster.mp << " / " << monster.mpMax << endl;


					cout << "========== 행동 ==========" << endl;
					cout << "1. 공격" << endl;
					cout << "2. 도망가기" << endl;
					cout << "행동을 선택하세요." << endl;
					cin >> menu;

					if (cin.fail())
					{
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}

					else if (menu == BATTLE_BACK)
					{
						break;
					}

					switch (menu)
					{
					case BATTLE_ATTACK:
						player.Attak(&monster);

						if (monster.hp <= 0)
						{
							player.Win(&monster);

							monster.hp = monster.hpMax * player.GetPlayerLV();
							monster.mp = monster.mpMax * player.GetPlayerLV();

							system("pause");
							break;
						}

						player.defense(&monster);

						player.Defeat(&monster);

						system("pause");

						break;
					}
				}
			}
			break;
		case MM_ENFORSE:
			system("cls");
			player.Enforse();
			break;
		}
	}
	return 0;
}