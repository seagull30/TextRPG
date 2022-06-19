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
		std::cout << "========== �÷��̾� ==========\n";
		
		std::cout << "���� : " << _level << "\t����ġ : " << _exp << "\t���� �������� : "<< _nextExp <<"\n";
		std::cout << "���ݷ� : " << _attackMin << " ~ " << _attackMax << "\n";
		std::cout << "���� : " << _armorMin << " ~ " << _armorMax << "\n";
		std::cout << "ü�� : " << _hp << " / " << _hpMax << "\t���� : " << _mp << " / " << _mpMax << "\n";
		std::cout << "������ : " << _inventory.gold << "\n\n";
	}

	void Attak(_tagMonster* monster)
	{
		int attack = rand() % (_attackMax - _attackMin + 1) + (_attackMin);
		int armor = rand() % (monster->armorMax- monster->armorMin + 1) + (monster->armorMin);

		int damage = attack - armor;

		// ���׿����� : ���ǽ� ? true�� �� ��, : false �� �� ���� �ȴ�.
		// �ּ� �������� ������ ���� �ʰ� 1�� ����
		damage = damage < 1 ? 1 : damage;

		// ���� HP�� ���ҽ�Ų��.
		monster->hp -= damage;

		std::cout << _name << "�� " << monster->name << "���� " << damage << "�� ���ظ� �������ϴ�.\n";
	}

	void defense(_tagMonster* monster)
	{
		int attack = rand() % (monster->attackMax - monster->attackMin + 1) + (monster->attackMin);
		int armor = rand() % (_armorMax - _armorMin + 1) + (_armorMin);

		int damage = attack - armor;

		damage = damage < 1 ? 1 : damage;

		// �÷��̾� HP�� ���ҽ�Ų��.
		_hp -= damage;

		std::cout << monster->name << "�� " << _name << "���� " << damage << "�� ���ظ� �������ϴ�.\n";
	}

	void Win(_tagMonster* monster)
	{
		std::cout << monster->name << " ���Ͱ� ����Ͽ����ϴ�.\n" ;

		_exp += monster->exp;
		int gold = (rand() % monster->goldMax - monster->goldMin + 1) + monster->goldMin;
		_inventory.gold += gold;

		std::cout << monster->exp << "�� ����ġ�� ȹ���Ͽ����ϴ�.\n";
		std::cout << gold << "�� ��带 ȹ���Ͽ����ϴ�.\n";
		if (_exp > _nextExp)
		{
			LevelUp();
			std::cout << "���� ��!!!\n";
		}

	}

	void Defeat(_tagMonster* monster)
	{
		if (_hp < 0)
		{
			std::cout << "�÷��̾ " << monster->name << "���� ����Ͽ����ϴ�.\n";

			// ������ ����ġ�� ��尡 10% ���δ�
			std::cout << (_exp * 0.1f) << "����ġ�� �Ҿ����ϴ�.\n";
			std::cout << (_inventory.gold * 0.1f) << "��带 �Ҿ����ϴ�.\n";

			_exp = _exp - (_exp * 0.1f);
			_inventory.gold = _inventory.gold - (_inventory.gold * 0.1f);

			// �÷��̾� ��Ȱ
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