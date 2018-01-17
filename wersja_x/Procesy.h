#pragma once
#include "Biblioteki.h"
#include "MemoryManager.h"
#include "Pipeline.h"
extern class MemoryManager;
extern class Pipeline;
extern struct PageTableData;


//extern string blad;									
//					  0		1		2		 3			4		  5
enum Process_state { New, Ready, Running, Waiting, Terminated, Zombie };

class PCB {
public:
	std::string Process_name;										//nazwa procesu
	int PID;													//unikalny identyfikator procesu
	Process_state State;										//stan procesu								
	std::vector<PageTableData>* page_table;
	unsigned int Process_size;									//ile proces bedzie potrzebowal pamieci

	std::array<int, 2>Descriptor;								//descriptor[0] wskazuje miejsce potoku w tablicy potoków
																//descriptor[1] wskazuje czy proces moze zapisywac czy odczytywac

	int Reg1, Reg2, Reg3, Reg4;									//rejestry dla Eryka

	std::string File_name;										//otwarte pliki

	int Priority;												//priorytet bazowy
	int Dynamic_priority;										//priorytet dynamiczny
	int CPU;
	int Command_counter;										//licznik rozkazow

	PCB::PCB() {
		this->State = New;
		this->Priority = 10;
		this->Descriptor[0] = -1;
		this->Descriptor[1] = -1;
		this->Reg1 = 0;
		this->Reg2 = 0;
		this->Reg3 = 0;
		this->Reg4 = 0;
		this->CPU = 0;
		this->Command_counter = 0;
	}
	//konstruktor do init'a
	PCB::PCB(int a) {
		this->PID = a;
		this->State = Ready;
		this->Priority = 31;
		this->Descriptor[0] = -1;
		this->Descriptor[1] = -1;
	}
	PCB::~PCB() {}

	//zmiana statusu procesu
	void Change_process_state(Process_state x);

};

class Tree {
public:
	PCB Pname;										//dane procesu
	PCB* F_process;									//wskaznik na ojca (dla init'a NULL)
	std::vector<Tree*>Children_list;				//lista dzieci

	void Fork(PCB * process, const std::string &name, MemoryManager &mm, const int &mem);
	void Fork_1(PCB *process, const std::string &name, const std::string &file_name, MemoryManager &mm, const int &mem);
	void Up_data(PCB &process, const std::string &name, const std::string &file_name, MemoryManager &mm, const int &mem);
	void Display_tree();
	void Display_PCB(MemoryManager &mm, PCB* proces);
	void Exit(const int &id, MemoryManager &mm, Pipeline &pip);
	void Exit_1(const int &id, MemoryManager &mm);
	PCB &Get_process(const int &id);
	PCB &Get_process_1(const std::string &proces_name);
	std::vector<int>Ready_processes();
};