#pragma once
#include <list>
#include "Procesy.h"
extern class PCB;

struct PageTableData // tablica stronic indeks->nrStronicy tworze dla kaødego procesu
{
	int frame; // ramka w ktorej znajduje sie stronica
	bool bit; // bit sprawdzajacy czy stronica jest w pamieci

	PageTableData(int frame, bool bit) {
		this->frame = frame;
		this->bit = bit;
	}
};

class MemoryManager
{
private:
	struct Page //stronica
	{
		char data[16]; // dane stronicy
		Page(std::string data) {
			while (data.size() < 16)
				data += " ";

			for (int i = 0; i < 16; i++) {
				this->data[i] = data[i];
			}
		}
		Page() {};

		void print() {
			for (auto x : data)
				std::cout << x;
			std::cout << std::endl;
		}
	};
	struct FramelistData // struktura znajdujaca sie w liscie ramek ulatwiajaca wymiane stronic (nie trzeba przeszukiwac listy procesow);
	{
		bool free; // zajetosc ramki
		int PID; // PID
		int pageN; // numer_strony
		std::vector<PageTableData> *page_table; // wskaznik na tablice stronic
		FramelistData(bool free, int PID, int pageN, std::vector<PageTableData> *page_table) {
			this->free = free;
			this->PID = PID;
			this->pageN = pageN;
			this->page_table = page_table;
		};
	};

	//Ramki w pamieci fizycznej
	std::vector<FramelistData> Frames;

	//Lista LRU ostani element wskazuje na najdluzej nieuzywana ramke
	std::list<int> LRU{ 0,1,2,3,4,5,6,7 };

	//Plik stronicowania vector par<PID,vector Stron>>>;
	//std::vector<std::pair<int, std::vector<Page>>> PageFile; // zamiana na MAPE
	//Plik stronicowania mapa<ID , Stronice tego procesu>;
	std::map<int, std::vector<Page> > PageFile;

	//Ustawia na poczatek listy wybrana ramke
	void FrameOrder(int Frame);

	//Laduje dana stronice w podana ramke w pamieci fizycznej
	//Arg: Strona ≥adowana do pamiecie , Ramka w ktorej ma zostac umieszczona,numer stronicy,PID, tablica stronic
	int LoadtoMemory(Page page, int pageN, int PID, std::vector<PageTableData> *page_table);

	//Zamienia stronice zgodnie z algorytmem LRU
	//zwraca numer ramki podmienionej
	int SwapPages(std::vector<PageTableData> *page_table, int pageN, int PID);

	//Szuka wolnej ramki
	int seekForFreeFrame();

public:
	// pamiec fizyczna 
	char RAM[128];

	// Tworze wskaünik do tablicy stronic z odpowiedniπ iloúciπ stronic 
	// frame -1 oraz bit 0 oznacza ze stronica nie znajduje sie w pamieci
	// Page_table znajduje sie w PCB
	std::vector<PageTableData> *createPageTable(int mem, int PID);

	//proces beczynnosci umieszany w pamieci przy starcie systemu wypelnianie RAMu spacjami
	void start();

	//funkcja wyswietlajaca pamiec od podanego miejsca i ilosci
	void showPMemory(int start, int amount);

	//cala pamiec fizyczna
	void showPMemory();

	//wyswietla plik wymiany
	void ShowPageFile();

	//wyswietlam tablice stronic
	static void showPageTable(std::vector<PageTableData> *page_table);

	// pokazuje liste ostatnio uzytych ramek w kolejnosci uzycia
	void ShowLRUList();

	//pokazuje liste ramek wraz z informacja kogo dane znajduja sie w pamieci
	void showFrameList();

	//usuwa z pamieci dane wybranego procesu
	void Remove(int PID);

	//Procedura ladujaca program`
	//Pierwsza stronica dla programu zostaje zaladowana do RAMU reszta jest w pliku wymiany
	int LoadProgram(std::string path, int mem, int PID);

	//WRITE TO MEMORY
	int Write(int adress, int PID, char ch, std::vector<PageTableData> *page_table);

	//Pobiera rozkaz z danego adresu
	std::string Get(PCB *process, int LR);

	~MemoryManager() {}
	MemoryManager() {
		for (int i = 0; i < 8; i++)
			Frames.push_back(FramelistData(1, -1, -1, NULL));
	}
};

