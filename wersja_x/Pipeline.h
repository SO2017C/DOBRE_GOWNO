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
	void createPipe(PCB &p1, PCB &p2); //funkcja tworz¹ca pokot gdzie p1 to referencja do procesu wysy³aj¹cego a p2 do odbieraj¹cego
	void deletePipe(PCB& p1);	// funckja usuwaj¹ca potok 
	bool Pipe_exist(PCB& p1, PCB &p2);

	std::vector<Pipe*> pipes;	//wektor przechowuj¹cy wszystkie aktywne potoki
private:

};

struct Pipe
{
public:
	Pipe(PCB& p1, PCB& p2, Pipeline& pl);
	~Pipe();
	std::string read(unsigned int l);	//funkcja odczytu z parametrem d³ugoœci wiadomoœci któr¹ chcemy zapisaæ
	void write(const std::string& msg);	//funkcja zapisu z parametrem wiadomoœci do przes³ania
private:
	std::queue<char> buffer; //potok jako kolejka
	PCB  *p1;	//wskaŸnik na proces wysy³aj¹cy komunikaty
	PCB  *p2;	//wskaŸnik na proces odczytuj¹cy
	Pipeline *pl;	//wskaŸnik do klasy nadrzêdnej
	Sync sync;
};




