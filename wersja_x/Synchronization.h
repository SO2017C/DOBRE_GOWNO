#ifndef Synchronization_h
#define Synchronization_h
#include"Biblioteki.h"

class Sync {

private:
	bool lock; //zmienna uzywana do sprawdzenia warunku 
	std::map<std::string, bool> filelocks;
public:
	Sync(); //konstruktor

	void unlock(); //odblokowanie sekcji krytycznej

	void unlockFile(std::string file);

	bool test_and_set();

	bool test_and_set(bool& lock);

	bool test_and_set_file(std::string file);

	bool compare_and_swap(bool expected, bool new_value);

};

#endif