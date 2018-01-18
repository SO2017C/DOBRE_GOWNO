#include "Synchronization.h"

Sync::Sync() {
	this->lock = false; //wolny dostep do sekcji krytycznej
}

void Sync::unlock() {
	std::cout << "Odblokowalem zasob" << std::endl;
	this->lock = false; //odblokuj dostep do sekcji krytycznej
}

void Sync::unlockFile(std::string file)
{
	filelocks.erase(file);
	std::cout << "Zwalniam dostep do pliku" << std::endl;
}

bool Sync::test_and_set() {
	std::cout << "Zablokowalem zasob" << std::endl;
	bool returnValue = this->lock; // przechowaj wartosc aby sprawdzic zamek
	this->lock = true; //zablokuj sekcje krytyczna dla tego procesu 
	return returnValue; //zwroc poprzednia wartosc zmiennej do sprawdzenia warunku
}

bool Sync::test_and_set(bool& lock) {
	bool returnValue = lock; // przechowaj wartosc aby sprawdzic zamek
	lock = true; //zablokuj sekcje krytyczna dla tego procesu 
	return returnValue; //zwroc poprzednia wartosc zmiennej do sprawdzenia warunku
}

bool Sync::test_and_set_file(std::string file)
{
	if (filelocks.count(file) < 1) {
		filelocks[file] = false;
		std::cout << "Opening file" << std::endl;
	}
	else {
		std::cout << "Access to file denied" << std::endl;
	}
	return test_and_set(filelocks[file]);
}

bool Sync::compare_and_swap(bool expected, bool new_value) {
	std::cout << "Zablokowalem zasob" << std::endl;
	bool returnValue = this->lock; //przechowaj wartosc aby sprawdzic zamek
	if (this->lock == expected) //sprawdz czy wartosc jest oczekiwana
		this->lock = new_value; //zablokuj/odblokuj zamek na podstawie nowej wartosci

	return returnValue; //zwroc stara wartosc zmiennej do sprawdzenia warunku
}