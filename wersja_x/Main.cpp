//LAST UPDATE 201801171615
#include "Shell.h"
#include "HDD.h"
#include <fstream>
PCB *troll = new PCB(1);

int main() {

	Planista plan;
	interpreter interp;
	MemoryManager mm;
	PCB pcb;
	
	Tree tree;
	Pipeline pipeline;
	HDD disk;
	
	PCB *Init = new PCB(1);
	Init->Process_name = "Proces bezczynnosci";
	tree.F_process = NULL;
	tree.Pname = *Init;
	mm.start();
	tree.Pname.page_table = mm.createPageTable(16, 1);
	troll = &tree.Pname;
	SHELL shell(interp,mm,*troll,plan,tree,pipeline,disk);
	
}