//LAST UPDATE 201801171615
#include "Shell.h"
#include "HDD.h"
#include <fstream>


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
	tree.Pname = *Init;

	mm.start();
	tree.Pname.page_table = mm.createPageTable(32, 1);

	SHELL shell(interp, mm, pcb, plan, tree, pipeline, disk);
}