#pragma once
#include <map>
#include <list>
#include "procesy.h"
extern class Tree;
extern class MemoryMenager;
class Planista
{
public:
	Planista();
	~Planista();
	void dodaj_do_kolejki(PCB &x);
	void check(/*PCB *actual,*/ Tree &t);
	//void act(PCB &actual);
	void make_zombie(PCB &actual, Tree &t, MemoryManager &mm);
private:
	std::map<int, std::list<PCB*>>mapa_kolejek;			//g��wna kolejka_bool do procesora 8 stopniowa
	std::vector<bool>kolejka_bool;						//dodatkowa kolejka_bool wyboru mapy
														//void spr_kolejki();
	std::vector<int>r_in_q;
	void dzielnik_cpu();
	void powrot_do_kolejki(PCB &X);
	void run(Tree &t);
	bool started = false;
};

