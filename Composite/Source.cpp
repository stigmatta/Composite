#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
 *  ������� ��������������, ���������� ������� � ����������� ��������� ��� ������������� �������� �� �������� � ������.
 *  ��������� �������� ������������ ���������� �������������� � ��������� �������.
	������� ���������� �������� �������, ������� ����� �������� �� ����������� � ������� ��������, �������� ����������� �������,
 *  ������ ������� ���������� ����� ����� ������� ����� �������.
 *
 * ���� �� ����� �������� ����������� - �������� �������� �� ������������� �����, �������� �� ��� � �������� ��� ��������� ��������.
 * ��� ���������� ���� ���� ����� Component ������ ������� ��� ����� ������ �������� ������ ��� ������� Composite � Leaf.
 * ������ ����� Component ������������� ��� ���� �������� ���������� �� ���������, � ��������� Composite � Leaf �������� ��.
 *
 * ����������:
 * - ���������� �������� �������, ��������� �� ����������� � ��������� ��������.
 * - �������� ����������� �������.
 * - ��������� ���������� ����� ����� �����������.
 * - ������������ �������� ������ �������
*/

/*
 Component
	- ��������� ��������� ��� ����������� ��������;
	- ������������� ���������� ���������� �������� �� ���������, ����� ��� ���� �������;
	- ��������� ��������� ��� ������� � �������� � ���������� ���;
	- ���������� ��������� ��� ������� � �������� ���������� � ����������� ��������� � ��� ������������� ��������� ���.
 */

class Component abstract
{
protected:
	string name;
	unsigned int price=0;
public: 
	Component(string name)
	{
		this->name = name;
	}
	Component(string name,unsigned int price):name(name),price(price){}

	virtual  void Add(Component *c) abstract;
	virtual  void Remove(Component *c) abstract;
	virtual  void Display(int depth) abstract;
	virtual  unsigned int GetPrice() abstract;
};

/*
 * Composite
 *  - ���������� ��������� �����������, � ������� ���� �������;
	- ������ ����������-�������;
	- ��������� ����������� � ���������� ��������� �������� � ���������� ������ Component;
*/

class Composite : public Component
{
	vector<Component*> components;

public:
	Composite(string name):Component(name){	}

	Composite(string name, unsigned int price): Component(name,price) {}

	void Add(Component * component) override
	{
		components.push_back(component);
	}
	void Remove(Component *component) override
	{
		auto iter = find(components.begin(), components.end(), component);
		components.erase(iter);
	}
	void Display(int depth) override
	{
		string s(depth, '-');
		cout << s + name << endl;

		for(Component *component : components)
		{
			component->Display(depth + 2);
		}
	}

	unsigned int GetPrice() override
	{
		unsigned int price = this->price;
		for (int i = 0; i < components.size(); i++)
			price += components[i]->GetPrice();

		return price;

	}
};
/*
 * Leaf
	- ������������ �������� ���� ���������� � �� ����� ��������;
	- ���������� ��������� ����������� �������� � ����������;
 */
class Leaf : public Component
{
public:
	Leaf(string name, unsigned int price) : Component(name, price){}

	void Add(Component* c) override
	{
		cout << "Cannot add to file\n";
	}
	void Remove(Component* c) override
	{
		cout << "Cannot remove from file\n";
	}
	void Display(int depth) override
	{
		string s(depth, '-');
		cout << s + name << endl;
	}

	unsigned int GetPrice() override
	{
		return price;
	}

};


int main()
{
	setlocale(LC_ALL, "");
	Component *reception = new Composite("��������");

	reception->Add(new Leaf("������ ���� ��������� � ������ �����",0));

	Component* magazine_table = new Composite("���������� ������",10000);
	reception->Add(magazine_table);
	magazine_table->Add(new Leaf("10-20 �������� ���� \"������������ ���\"", 500));
	reception->Add(new Leaf("������ �����", 20000));

	Component* secretary_table = new Composite("���� ���������",10000);
	Component* computer = new Composite("���������",20000);
	secretary_table->Add(computer);
	computer->Add(new Leaf("����� ������� �������� ������ �������� �����",5000));
	secretary_table->Add(new Leaf("������� ��������������", 50000));

	reception->Add(new Leaf("����� � ������ � �������� �����",3000));

	Component* audition1 = new Composite("��������� 1");
	audition1->Add(new Leaf("10 ������", 20000));
	audition1->Add(new Leaf("�����", 5000));

	Component* teacher_table = new Composite("���� �������",10000);
	audition1->Add(teacher_table);
	teacher_table->Add(new Leaf("���������",15000));
	audition1->Add(new Leaf("������� ������� �����������", 1000));

	Component* audition2 = new Composite("��������� 2");
	Component* tables20 = new Composite("20 ������",20000);
	audition2->Add(tables20);

	tables20->Add(new Leaf("����� ������� �����", 0));
	tables20->Add(new Leaf("����� ���������� � ���� ��� ����", 0));

	audition2->Add(new Leaf("�����", 5000));
	audition2->Add(new Leaf("������ �����", 20000));

	Component* comp_audition = new Composite("������������ ���������");
	Component* comps10 = new Composite("10 ������������ ������", 100000);
	comp_audition->Add(comps10);

	Component* computer_in_comp_aud = new Composite("��������� �� ������ �����", 15000);
	comps10->Add(computer_in_comp_aud);

	computer_in_comp_aud->Add(new Leaf("��������� 2.2���", 3000));
	computer_in_comp_aud->Add(new Leaf("��������� �� 80��", 2000));
	computer_in_comp_aud->Add(new Leaf("����������� ������ 1024��", 2000));

	comps10->Add(new Leaf("������� ����� ������� �����", 2000));

	Component* blackboard = new Composite("�����", 5000);
	blackboard->Add(new Leaf("����� ������������ ��������", 200));

	Component* dining_room = new Composite("��������");
	dining_room->Add(new Leaf("�������� �������", 7000));

	Component* dining_table = new Composite("����");
	dining_table->Add(new Leaf("4 �����", 4000));
	
	dining_room->Add(new Leaf("�����������", 12000));
	dining_room->Add(new Leaf("����������", 8000));

	reception->Display(3);
	cout << reception->GetPrice();
	system("pause");
}


