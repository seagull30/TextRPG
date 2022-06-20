#pragma once
#include <string>
#include <random>

#include "Inventory.h"

#include "monster.h"
#include <conio.h> 


class Player
{
public:

	Player() = default;
	~Player() = default;

	void Create(std::string name)
	{
		_name = name;
		_inventory.gold = 100000;
	}

	void LevelUp()
	{
		++_level;
		_attackMin *= 2;
		_attackMax *= 2;
		_armorMin *= 2;
		_armorMax *= 2;
		_hpMax *= 1.5;
		_mpMax *= 1.5;
		_hp = _hpMax;
		_mp = _mpMax;
		_exp = 0;
		_nextExp *= 1.5;
	}

	void ShowStats() const
	{
		std::cout << "========== 플레이어 ==========\n";
		
		std::cout << "레벨 : " << _level << "\t경험치 : " << _exp << "\t다음 레벨까지 : "<< _nextExp <<"\n";
		std::cout << "공격력 : " << _attackMax << "\t방어력 : " << _armorMax << "\n";
		std::cout << "체력 : " << _hp << " / " << _hpMax << "\t마나 : " << _mp << " / " << _mpMax << "\n";
		
	}

	int GetPlayerLV()
	{
		return _level;
	}
	void Attak(_tagMonster* monster)
	{
		int attack = rand() % (_attackMax - _attackMin + 1) + (_attackMin);
		int armor = rand() % (monster->armorMax- monster->armorMin + 1) + (monster->armorMin);

		int damage = attack - armor;

		// 삼항연산자 : 조건식 ? true일 때 값, : false 일 때 값이 된다.
		// 최소 데미지를 음수가 되지 않고 1로 설정
		damage = damage < 1 ? 1 : damage;

		// 몬스터 HP를 감소시킨다.
		monster->hp -= damage;

		std::cout << _name << "가 " << monster->name << "에게 " << damage << "의 피해를 입혔습니다.\n";
	}

	void defense(_tagMonster* monster)
	{
		int attack = rand() % (monster->attackMax - monster->attackMin + 1) + (monster->attackMin);
		int armor = rand() % (_armorMax - _armorMin + 1) + (_armorMin);

		int damage = attack - armor;

		damage = damage < 1 ? 1 : damage;

		// 플레이어 HP를 감소시킨다.
		_hp -= damage;

		std::cout << monster->name << "가 " << _name << "에게 " << damage << "의 피해를 입혔습니다.\n";
	}

	void Win(_tagMonster* monster)
	{
		std::cout << monster->name << " 몬스터가 사망하였습니다.\n" ;

		_exp += monster->exp;
		int gold = (rand() % monster->goldMax - monster->goldMin + 1) + monster->goldMin;
		_inventory.gold += gold;

		std::cout << monster->exp << "의 경험치를 획득하였습니다.\n";
		std::cout << gold << "의 골드를 획득하였습니다.\n";
		if (_exp > _nextExp)
		{
			LevelUp();
			std::cout << "레벨 업!!!\n";
		}

	}
	void Enforse()
	{
		
		std::cout << "현재돈 : " << _inventory.gold << "강화 확률 : 10%\n";
		std::cout << "강화비용 : 1000gold\n";
		std::cout << "강화하기 : 1\n 돌아가기 : 2\n";
		int input;
		std::cin >> input;
		switch (input)
		{
		case 1:
			if (_inventory.gold < 0) 
			{
				std::cout << "돈이 모자랍니다.\n";
			}
			else
			{
				_inventory.gold -= 1000;
				if (rand() % 100 + 1 > 10)
				{
					std::cout << "강화에 성공하셨습니다.\n";
					_attackMin *= 2;
					_attackMax *= 2;
					_armorMin *= 2;
					_armorMax *= 2;
				}
				else
					"강화에 실패했습니다.";
			}
			system("pause");
			break;
		case 2:
			return;
			break;
		}
		
		
	}

	void Defeat(_tagMonster* monster)
	{
		if (_hp < 0)
		{
			std::cout << "플레이어가 " << monster->name << "에게 사망하였습니다.\n";

			// 죽으면 경험치와 골드가 10% 깎인다
			std::cout << (_exp * 0.1f) << "경험치를 잃었습니다.\n";
			std::cout << (_inventory.gold * 0.1f) << "골드를 잃었습니다.\n";

			_exp = _exp - (_exp * 0.1f);
			_inventory.gold = _inventory.gold - (_inventory.gold * 0.1f);

			// 플레이어 부활
			_hp = _hpMax;
			_mp = _mpMax;
		}
	}

private:
	std::string	_name = "";

	int _attackMin = 10;
	int _attackMax = 10;
	int _armorMin = 20;
	int _armorMax = 20;

	int _hp = 500;
	int _hpMax = 500;
	int _mp = 100;
	int _mpMax = 100;

	int _exp = 0;
	int _nextExp = 50;
	int _level = 1;

	_tagInventory _inventory;
};