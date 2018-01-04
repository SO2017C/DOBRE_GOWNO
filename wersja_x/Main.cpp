#include "Shell.h"
#include "HDD.h"


int main() {
	Planista plan;
	interpreter interp;
	MemoryManager mm;
	PCB pcb;
	Tree tree;
	Pipeline pipeline;
	HDD disk;
	PCB *Init = new PCB(1);
	tree.Pname = *Init;
	tree.F_process = NULL;
	mm.start();

	SHELL shell(interp,mm,pcb,plan,tree,pipeline,disk);
}