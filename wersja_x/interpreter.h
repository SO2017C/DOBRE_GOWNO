#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Pipeline.h"
#include "Procesy.h"
#include "MemoryManager.h"
#include "Planista.h"
#include "HDD.h"

extern class HDD;
extern class MemoryManager;
extern class PCB;
extern class Pipe;
extern class Pipeline;
extern class Tree;
extern class Planista;

class interpreter
{
public:
	int PID;
	int rejA;
	int rejB;
	int rejC;
	int rejD;
	int liczRoz;




	void PobierzRejestry(Planista &planista, PCB &pcb, Tree &tree);  //pobieranie rejestrów z procesu który jest w stanie running

	std::string pobierzRozkaz(MemoryManager &mm, PCB &pcb);

	void StanRej();

	void zapiszRejestry(PCB &pcb);
	void WykonajProgram(MemoryManager &mm, PCB &pcb, Planista &planista, Tree &tree, Pipeline &pipeline, HDD &dysk);
private:
};