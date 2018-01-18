#include "Planista.h"
PCB *running;
extern PCB *troll;
Planista::Planista()
{
	for (int i = 0; i < 8; i++)
	{
		kolejka_bool.push_back(false);
	}

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
	mapa_kolejek[nr].push_back(&x);
	kolejka_bool.at(nr) = true;
}

void Planista::dzielnik_cpu() {

  	for (int i = 0; i < 8; i++)												//pêtla sprawdzaj¹ca mape kolejek
	{
		for (std::list<PCB*>::iterator it = mapa_kolejek[i].begin(); it != mapa_kolejek[i].end(); it++)
		{
			if ((*it)->PID == 1)
			{

			}
			else
			{
				(*it)->CPU = (*it)->CPU / 2;
			}
			

		}
	}

}
void Planista::powrot_do_kolejki(PCB &x) {
	x.Dynamic_priority = x.Priority + (x.CPU / 2);
	int nr = x.Priority / 4;
	mapa_kolejek[nr].push_back(&x);
	kolejka_bool.at(nr) = true;
}


void Planista::run(Tree &t) {
	std::vector<int> r = t.Ready_processes();

	
	for (int j = 0; j < r.size(); j++)
	{
		bool go = true;
		for (size_t i = 0; i < r_in_q.size(); i++)
		{
			if (t.Get_process(r[j]).PID == r_in_q[i]) {
				go = false;
			}
		}
		if (go == true) {
			std::cout << &t.Get_process(r[j]).PID << std::endl;
			dodaj_do_kolejki((t).Get_process(r[j]));
			r_in_q.push_back(r[j]);
		}
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

	}												//sprawdzanie pierwszej dostêpnej kolejki w mapie
	//std::cout << &mapa_kolejek[i].front()->PID << "!!!" << std::endl;
	
	PCB *x = mapa_kolejek[i].front();
	//std::cout << &x->PID << "!!!" << std::endl;
	//std::cout << &x->PID << " x " << std::endl;
	mapa_kolejek[i].pop_front();
	if (mapa_kolejek[i].empty())
	{
		kolejka_bool[i] == false;
	}
	running = x;
	running->Change_process_state(Running);
	//std::cout << &running->PID <<" [running run] " <<std::endl;
	troll = running;
	//std::cout << &troll->PID << " [running run troll] " << std::endl;
}





void Planista::make_zombie(PCB &actual, Tree &t, MemoryManager &mm) {
	
	actual.Change_process_state(Zombie);
	actual.Change_process_state(Terminated);
	running = &actual;

	int nr = running->Priority / 4;
	if (mapa_kolejek[nr].empty())
	{
		kolejka_bool[nr] = false;
	}
	t.Exit_1(running->PID, mm);
}

void Planista::check(/*PCB *actual,*/ Tree &t) {

	//std::cout << &running->PID << " [running check]" << std::endl;
	//std::cout << actual->PID << " [actual check] " << std::endl;
	if (troll->State !=Terminated)
	{
		troll->Change_process_state(Ready);
		running = troll;
	/*	running = actual;*/
	}
	//std::cout << &running->PID << " running2 " << std::endl;
	if (troll->State == Terminated)
	{
		running->PID = NULL;
	}


	if (running->PID == NULL)
	{
		std::cout << "Start Planisty\n";
		run(t);
		*troll = *running;
		return;
	}
	if (running->PID != NULL)
	{
		std::cout << "odkladanie procesu\n";
		powrot_do_kolejki(*running);
		dzielnik_cpu();
		run(t);
		*troll = *running;
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