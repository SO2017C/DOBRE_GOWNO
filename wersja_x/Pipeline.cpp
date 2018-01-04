#include "Pipeline.h"

//znaczenia desktryporów:
// -1 - proces nie chce dzia³aæ ju¿ na tym potoku
// 1 - proces ma prawo zapisywaæ
// 0 - proces ma prawo odczytywaæ
//sam dysktyprot jest umieszczony w PCB i przechowuje inkeds potoku w tablicy potoków oraz prawid³owy Descriptor

Sync sync;

Pipe::Pipe(PCB & p1, PCB& p2, Pipeline& pl)
{
	this->p1 = &p1;
	this->p2 = &p2;
	this->pl = &pl;
}

Pipe::~Pipe()
{
	p1->Descriptor[0] = -1;
	p2->Descriptor[0] = -1;
}




std::string Pipe::read(unsigned int l)
{
	while (sync.test_and_set());	//synchronizacaj procesów
	
	std::string temp;
	if (p2->Descriptor[1] != 0)	//sprawdzanie czy dany proces ma prawa do tej funkcji
	{
		std::cout << "Nie mo¿esz tego zrobiæ" << std::endl;
	}
	else if (p2->Descriptor[1] == 0)
	{
		if (buffer.empty())
		{
			p2->Change_process_state(Waiting);
		}
		else 
		{
			if (l > buffer.size())	//sprawdznie czy wiadomoœc która chcemy odczytaæ jest d³u¿sza ni¿ wiadomoœc w potoku
			{
				while(buffer.size()>0)
				{
					temp.push_back(buffer.front());
					buffer.pop();
				}
				pl->deletePipe((*p1));
			}
			else
			{
				for (int i = 0; i < l; i++)
				{
					temp.push_back(buffer.front());
					buffer.pop();
				}
			}
		}

	}

	sync.unlock();
	std::cout << temp << std::endl;
	return temp;
	
}

void Pipe::write(const std::string& msg)
{
	while (sync.test_and_set()); //synchronizacaj procesów
	
	if (p1->Descriptor[1] != 1)	//sprawdzanie czy dany proces ma prawa do tej funkcji
	{
		std::cout << "Nie mo¿esz tego zrobiæ" << std::endl;
	}
	else if (p1->Descriptor[1] == 1)
	{
		for (auto x : msg)	//zapisywanie wiadomoœci do potoku
		{
			buffer.push(x);
		}
	}
	sync.unlock();
	std::cout << msg << std::endl;
	
}

Pipeline::Pipeline()
{
}

void Pipeline::createPipe(PCB& p1, PCB& p2)	//tworzenie potoku
{
	bool check = false;
	int i;
	for (i = 0; i < pipes.size(); i++)	//szukanie pustego miejsca w tablicy potoków
	{
		if (pipes[i] == NULL)
		{
			check = true;
			break;
		}
	}
	if (check)	//dodawanie potoku w puste miejsce
	{
		Pipe* temp = new Pipe(p1, p2, (*this));
		pipes[i] = temp;
		p1.Descriptor[0] = i;
		p1.Descriptor[1] = 1;
		p2.Descriptor[0] = i;
		p2.Descriptor[1] = 0;
	}
	else	//dodawanie potoku na koñcu tablicy
	{
		Pipe* temp = new Pipe(p1, p2, (*this));
		pipes.push_back(temp);
		p1.Descriptor[0] = pipes.size() - 1;
		p1.Descriptor[1] = 1;
		p2.Descriptor[0] = pipes.size() - 1;
		p2.Descriptor[1] = 0;
	}
}

void Pipeline::deletePipe(PCB& p1)	//usuwanie potoku
{
	if (p1.Descriptor[0] != -1) {
		int temp = p1.Descriptor[0];
		delete(pipes[temp]);
		pipes[temp] = NULL;
	}
	else
	{
		std::cout << "Nie moza usunac nie istniejacego pipe" << std::endl;
	}
}

bool Pipeline::Pipe_exist(PCB & p1, PCB & p2)
{
	if (p1.Descriptor[0] == p2.Descriptor[0] && p1.Descriptor[1] == 1 && p1.Descriptor[0] != -1)
	{
		return true;
	}
	else
	{
		createPipe(p1, p2);
		return true;
	}
}
