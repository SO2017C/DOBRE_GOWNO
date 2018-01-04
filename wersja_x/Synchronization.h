#ifndef Synchronization_h
#define Synchronization_h
#pragma once
#include"Biblioteki.h"

class Sync {

private:
	bool lock; //zmienna uzywana do sprawdzenia warunku 

public:
	Sync(); //konstruktor

	void unlock(); //odblokowanie sekcji krytycznej

				   /* Sposob uzycia:
				   Sync lock;
				   //...
				   while(lock.test_and_set());
				   //sekcja krytyczna
				   lock.free();
				   */
	bool test_and_set();

	/* Sposob uzycia:
	Sync lock;
	//...
	while(lock.compare_and_swap(0,1) != 0));
	//sekcja krytyczna
	lock.free();
	*/
	bool compare_and_swap(bool expected, bool new_value);

};

#endif