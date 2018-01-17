#include "Planista.h"
PCB running;
Planista::Planista()
{
	for (int i = 0; i < 8; i++)
	{
		kolejka_bool.push_back(false);
	}
	gotowe = 0;
}

Planista::~Planista()
{
}

void Planista::dodaj_do_kolejki(PCB &x) {
	if (x.Dynamic_priority == NULL)
	{
		x.Dynamic_priority = x.Priority;
	}
	int nr = x.Dynamic_priority / 4;
	mapa_kolejek[nr].push_back(x);
	kolejka_bool.at(nr) = true;
}

void Planista::dzielnik_cpu() {

  	for (int i = 0; i < 8; i++)												//pêtla sprawdzaj¹ca mape kolejek
	{
		for (std::list<PCB>::iterator it = mapa_kolejek[i].begin(); it != mapa_kolejek[i].end(); it++)
		{
			if (it->PID == 1)
			{

			}
			else
			{
				it->CPU = it->CPU / 2;
			}
			

		}
	}

}
void Planista::powrot_do_kolejki(PCB &x) {
	x.Dynamic_priority = x.Priority + (x.CPU / 2);
	int nr = x.Priority / 4;
	mapa_kolejek[nr].push_back(x);
	kolejka_bool.at(nr) = true;
}


void Planista::run(Tree &t) {
	std::vector<PCB> r = t.Ready_processes();

	
	for (; gotowe < r.size(); gotowe++)
	{
		dodaj_do_kolejki(r[gotowe]);
	}
	int i = 0;
	while (kolejka_bool.at(i) == false)				//sprawdzanie pierwszej dostêpnej kolejki w mapie
	{												//sprawdzanie pierwszej dostêpnej kolejki w mapie
		if (kolejka_bool.at(i) == true)				//sprawdzanie pierwszej dostêpnej kolejki w mapie
		{
													//sprawdzanie pierwszej dostêpnej kolejki w mapie
			break;									//sprawdzanie pierwszej dostêpnej kolejki w mapie
		}											//sprawdzanie pierwszej dostêpnej kolejki w mapie
		i++;
		if (i == 8)
		{
			return;
		}

	}										//sprawdzanie pierwszej dostêpnej kolejki w mapie

	PCB x = mapa_kolejek[i].front();
	mapa_kolejek[i].pop_front();
	if (mapa_kolejek[i].empty())
	{
		kolejka_bool[i] == false;
	}
	running = x;
	running.Change_process_state(Running);
}





void Planista::make_zombie(PCB &actual, Tree &t, MemoryManager &mm) {
	
	actual.Change_process_state(Zombie);
	actual.Change_process_state(Terminated);
	running = actual;
	int nr = running.Priority / 4;
	if (mapa_kolejek[nr].empty())
	{
		kolejka_bool[nr] = false;
	}
	t.Exit_1(running.PID, mm);
}

void Planista::check(PCB &actual, Tree &t) {
	if (actual.State !=Terminated)
	{
		actual.Change_process_state(Ready);
		running = actual;
	}
	if (actual.State == Terminated)
	{
		running.PID = NULL;
	}


	if (running.PID == NULL)
	{
		std::cout << "Start Planisty\n";
		run(t);
		actual = running;
		return;
	}
	if (running.PID != NULL)
	{
		std::cout << "odkladanie procesu\n";
		powrot_do_kolejki(running);
		dzielnik_cpu();
		run(t);
		actual = running;
		return;
	}
//	else
//	{
//		//std::cout << "Proces w Procesorze\n";
//		actual = running;
//		return;
//	}

}
//void Planista::act(PCB &act) {
//	act = running;
//}