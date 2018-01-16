#pragma once
#include <queue>
#include <vector>
#include "Procesy.h"
#include "Synchronization.h"
 
extern class PCB;
class Pipe;

class Pipeline
{
public:
	Pipeline();
	void createPipe(PCB &p1, PCB &p2); //funkcja tworz�ca pokot gdzie p1 to referencja do procesu wysy�aj�cego a p2 do odbieraj�cego
	void deletePipe(PCB& p1);	// funckja usuwaj�ca potok 
	bool Pipe_exist(PCB& p1, PCB &p2);

	std::vector<Pipe*> pipes;	//wektor przechowuj�cy wszystkie aktywne potoki
private:

};

struct Pipe
{
public:
	Pipe(PCB& p1, PCB& p2, Pipeline& pl);
	~Pipe();
	std::string read(unsigned int l);	//funkcja odczytu z parametrem d�ugo�ci wiadomo�ci kt�r� chcemy zapisa�
	void write(const std::string& msg);	//funkcja zapisu z parametrem wiadomo�ci do przes�ania
private:
	std::queue<char> buffer; //potok jako kolejka
	PCB  *p1;	//wska�nik na proces wysy�aj�cy komunikaty
	PCB  *p2;	//wska�nik na proces odczytuj�cy
	Pipeline *pl;	//wska�nik do klasy nadrz�dnej
	Sync sync;
};




