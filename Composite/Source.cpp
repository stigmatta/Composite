#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
 *  Паттерн проектирования, объединяет объекты в древовидную структуру для представления иерархии от частного к целому.
 *  Позволяет клиентам единообразно трактовать индивидуальные и составные объекты.
	Паттерн определяет иерархию классов, которые могут состоять из примитивных и сложных объектов, упрощает архитектуру клиента,
 *  делает процесс добавления новых видов объекта более простым.
 *
 * Одна из целей паттерна компоновщик - избавить клиентов от необходимости знать, работают ли они с листовым или составным объектом.
 * Для достижения этой цели класс Component должен сделать как можно больше операций общими для классов Composite и Leaf.
 * Обычно класс Component предоставляет для этих операций реализации по умолчанию, а подклассы Composite и Leaf замещают их.
 *
 * Результаты:
 * - определяет иерархии классов, состоящие из примитивных и составных объектов.
 * - упрощает архитектуру клиента.
 * - облегчает добавление новых видов компонентов.
 * - способствует созданию общего дизайна
*/

/*
 Component
	- объявляет интерфейс для компонуемых объектов;
	- предоставляет подходящую реализацию операций по умолчанию, общую для всех классов;
	- объявляет интерфейс для доступа к потомкам и управления ими;
	- определяет интерфейс для доступа к родителю компонента в рекурсивной структуре и при необходимости реализует его.
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
 *  - определяет поведение компонентов, у которых есть потомки;
	- хранит компоненты-потомки;
	- реализует относящиеся к управлению потомками операции в интерфейсе класса Component;
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
	- представляет листовые узлы композиции и не имеет потомков;
	- определяет поведение примитивных объектов в композиции;
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
	Component *reception = new Composite("Приемная");

	reception->Add(new Leaf("Должна быть выполнена в теплых тонах",0));

	Component* magazine_table = new Composite("Журнальный столик",10000);
	reception->Add(magazine_table);
	magazine_table->Add(new Leaf("10-20 журналов типа \"компьютерный мир\"", 500));
	reception->Add(new Leaf("Мягкий диван", 20000));

	Component* secretary_table = new Composite("Стол секретаря",10000);
	Component* computer = new Composite("Компьютер",20000);
	secretary_table->Add(computer);
	computer->Add(new Leaf("Важно наличие большого объема жесткого диска",5000));
	secretary_table->Add(new Leaf("Офисный инструментарий", 50000));

	reception->Add(new Leaf("Кулер с теплой и холодной водой",3000));

	Component* audition1 = new Composite("Аудитория 1");
	audition1->Add(new Leaf("10 столов", 20000));
	audition1->Add(new Leaf("Доска", 5000));

	Component* teacher_table = new Composite("Стол учителя",10000);
	audition1->Add(teacher_table);
	teacher_table->Add(new Leaf("Компьютер",15000));
	audition1->Add(new Leaf("Плакаты великих математиков", 1000));

	Component* audition2 = new Composite("Аудитория 2");
	Component* tables20 = new Composite("20 столов",20000);
	audition2->Add(tables20);

	tables20->Add(new Leaf("Столы черного цвета", 0));
	tables20->Add(new Leaf("Столы выставлены в овал или круг", 0));

	audition2->Add(new Leaf("Доска", 5000));
	audition2->Add(new Leaf("Мягкий диван", 20000));

	Component* comp_audition = new Composite("Компьютерная аудитория");
	Component* comps10 = new Composite("10 компьютерных столов", 100000);
	comp_audition->Add(comps10);

	Component* computer_in_comp_aud = new Composite("Компьютер на каждом столе", 15000);
	comps10->Add(computer_in_comp_aud);

	computer_in_comp_aud->Add(new Leaf("Процессор 2.2ГРц", 3000));
	computer_in_comp_aud->Add(new Leaf("Винчестер на 80ГБ", 2000));
	computer_in_comp_aud->Add(new Leaf("Оперативная память 1024МБ", 2000));

	comps10->Add(new Leaf("Розетка возле каждого стола", 2000));

	Component* blackboard = new Composite("Доска", 5000);
	blackboard->Add(new Leaf("Набор разноцветных маркеров", 200));

	Component* dining_room = new Composite("Столовая");
	dining_room->Add(new Leaf("Кофейный автомат", 7000));

	Component* dining_table = new Composite("Стол");
	dining_table->Add(new Leaf("4 стула", 4000));
	
	dining_room->Add(new Leaf("Холодильник", 12000));
	dining_room->Add(new Leaf("Умывальник", 8000));

	reception->Display(3);
	cout << reception->GetPrice();
	system("pause");
}


