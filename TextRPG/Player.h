#pragma once
#include <string>
#include <random>

#include "Inventory.h"

#include "monster.h"



class Player
{
public:

	Player() = default;
	~Player() = default;

	void Create(std::string name)
	{
		_name = name;
		_inventory.gold = 0;
	}

	void LevelUp()
	{
		++_level;
		_attackMin += 5;
		_attackMax += 10;
		_armorMin += 15;
		_armorMax += 20;
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
		std::cout << "공격력 : " << _attackMin << " ~ " << _attackMax << "\n";
		std::cout << "방어력 : " << _armorMin << " ~ " << _armorMax << "\n";
		std::cout << "체력 : " << _hp << " / " << _hpMax << "\t마나 : " << _mp << " / " << _mpMax << "\n";
		std::cout << "소지금 : " << _inventory.gold << "\n\n";
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

	int _attackMin = 5;
	int _attackMax = 100;
	int _armorMin = 15;
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