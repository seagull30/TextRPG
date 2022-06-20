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
		std::cout << "========== �÷��̾� ==========\n";
		
		std::cout << "���� : " << _level << "\t����ġ : " << _exp << "\t���� �������� : "<< _nextExp <<"\n";
		std::cout << "���ݷ� : " << _attackMax << "\t���� : " << _armorMax << "\n";
		std::cout << "ü�� : " << _hp << " / " << _hpMax << "\t���� : " << _mp << " / " << _mpMax << "\n";
		
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
	void Enforse()
	{
		
		std::cout << "���絷 : " << _inventory.gold << "��ȭ Ȯ�� : 10%\n";
		std::cout << "��ȭ��� : 1000gold\n";
		std::cout << "��ȭ�ϱ� : 1\n ���ư��� : 2\n";
		int input;
		std::cin >> input;
		switch (input)
		{
		case 1:
			if (_inventory.gold < 0) 
			{
				std::cout << "���� ���ڶ��ϴ�.\n";
			}
			else
			{
				_inventory.gold -= 1000;
				if (rand() % 100 + 1 > 10)
				{
					std::cout << "��ȭ�� �����ϼ̽��ϴ�.\n";
					_attackMin *= 2;
					_attackMax *= 2;
					_armorMin *= 2;
					_armorMax *= 2;
				}
				else
					"��ȭ�� �����߽��ϴ�.";
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