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
	tree.F_process = NULL;
	
	mm.start();
	//Init->page_table = mm.createPageTable(0, 1);
	SHELL shell(interp,mm,pcb,plan,tree,pipeline,disk);
}