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
	MM_EXIT
};

enum MAP_TYPE
{
	MT_NONE,
	MT_EASY,
	MT_NORMAL,
	MT_HARD,
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



	while (true)
	{

		// 몬스터 생성
		_tagMonster	monsterArr[MT_BACK - 1] = {};

		// 고블린 생성
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

		// 트롤
		monsterArr[1].name = "트롤";
		monsterArr[1].attackMin = 80;
		monsterArr[1].attackMax = 130;
		monsterArr[1].armorMin = 60;
		monsterArr[1].armorMax = 90;
		monsterArr[1].hpMax = 2000;
		monsterArr[1].hp = 2000;
		monsterArr[1].mpMax = 100;
		monsterArr[1].mp = 100;
		monsterArr[1].level = 5;
		monsterArr[1].exp = 80;
		monsterArr[1].goldMin = 4000;
		monsterArr[1].goldMax = 7000;

		// 드래곤
		monsterArr[2].name = "드래곤";
		monsterArr[2].attackMin = 250;
		monsterArr[2].attackMax = 500;
		monsterArr[2].armorMin = 200;
		monsterArr[2].armorMax = 400;
		monsterArr[2].hpMax = 30000;
		monsterArr[2].hp = 30000;
		monsterArr[2].mpMax = 20000;
		monsterArr[2].mp = 20000;
		monsterArr[2].level = 10;
		monsterArr[2].exp = 30000;
		monsterArr[2].goldMin = 30000;
		monsterArr[2].goldMax = 70000;

		// 상점에서 판매할 아에팀 목록을 생성한다.

		// 무기 리스트



		// 메인 화면
		while (true)
		{
			system("cls");
			cout << endl << "========== 메인 메뉴 ==========" << endl << endl;
			cout << "1. 지도 " << endl;
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
					cout << endl << "========== 맵 종류 ==========" << endl << endl;
					cout << "1. 쉬움" << endl;
					cout << "2. 보통" << endl;
					cout << "3. 어려움" << endl;
					cout << "4. 뒤로가기" << endl;
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
						// 맵 선택 화면에서 빠져나간다
						break;
					}

					// 선택한 메뉴에서 1을 빼주면 몬스터 배열의 인덱스가 된다.
						// 이렇게 해당 맵의 몬스터를 설정
					_tagMonster monster = monsterArr[menu - 1];

					// 전투
					while (true)
					{
						system("cls");
						switch (menu)
						{
						case MT_EASY:
							cout << "********** 쉬움 **********" << endl;
							break;
						case MT_NORMAL:
							cout << "********** 보통 **********" << endl;
							break;
						case MT_HARD:
							cout << "********** 어려움 **********" << endl;
							break;
						}

						// 플레이어 정보를 출력
						player.ShowStats();

						// 몬스터 정보를 출력
						cout << "========== 몬스터 ==========" << endl;
						cout << "이름 : " << monster.name << "\t레벨 : " << monster.level << endl;
						cout << "공격력 : " << monster.attackMin << " ~ " << monster.attackMax << endl;
						cout << "방어력 : " << monster.armorMin << " ~ " << monster.armorMax << endl;
						cout << "체력 : " << monster.hp << " / " << monster.hpMax << "\t마나 : " << monster.mp << " / " << monster.mpMax << endl;
						cout << "획득 경험치 : " << monster.exp << "\t획득 골드 : " << monster.goldMin << " ~ " << monster.goldMax << endl << endl;

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

							// 몬스터가 죽음
							if (monster.hp <= 0)
							{
								player.Win(&monster);

								// 몬스터 스탯을 초기화
								monster.hp = monster.hpMax;
								monster.mp = monster.mpMax;

								system("pause");
								break;
							}

							// 몬스터가 살아있으면 플레이어를 공격
							player.defense(&monster);

							// 플레이어가 죽었을 경우
							player.Defeat(&monster);

							system("pause");

							break;
						}
					}
				}
				break;

			}


		}
		return 0;
	}
}