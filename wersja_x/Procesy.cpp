#pragma once
#include "procesy.h"	

unsigned int Free_pid = 2;



//zmiana stanu procesu
void PCB::Change_process_state(Process_state x) {
	State = x;
}

std::string PCB::Display_state(Process_state x) {
	if (x == 0) {
		return "New";
	}
	else if (x == 1) {
		return "Ready";
	}
	else if (x == 2) {
		return "Running";
	}
	else if (x == 3) {
		return "Waiting";
	}
	else if (x == 4) {
		return "Terminated";
	}
	else if (x == 5) {
		return "Zombie";
	}
}

std::string Tree::Display_state(Process_state x) {
	if (x == 0) {
		return "New";
	}
	else if (x == 1) {
		return "Ready";
	}
	else if (x == 2) {
		return "Running";
	}
	else if (x == 3) {
		return "Waiting";
	}
	else if (x == 4) {
		return "Terminated";
	}
	else if (x == 5) {
		return "Zombie";
	}
}

//stworzenie procesu
void Tree::Fork(PCB * process, const std::string &name, MemoryManager &mm, const int &mem) {
	//dodanie dziecka init'a
	if (process->PID == Pname.PID) {
		Tree *temp = new Tree();
		temp->F_process = process;
		Up_data(temp->Pname, name, "", mm, mem);
		Children_list.push_back(temp);
	}
	//dodanie potomka dla dziecka init'a
	else {
		for (Tree *p1 : Children_list) {
			if (p1->Pname.PID == process->PID) {
				Tree *temp = new Tree();
				temp->F_process = process;
				Up_data(temp->Pname, name, "", mm, mem);
				p1->Children_list.push_back(temp);
				break;
			}
			else if (p1->Children_list.size() != 0) {
				for (Tree *p2 : p1->Children_list) {
					if (p2->Pname.PID == process->PID) {
						Tree *temp = new Tree();
						temp->F_process = process;
						Up_data(temp->Pname, name, "", mm, mem);
						p2->Children_list.push_back(temp);
						//wyjscie z pierwszej petli (poziom drugi) -> init jest pierwszym
						p1 = *(Children_list.end() - 1);
						break;
					}
				}
			}
		}
	}
}
//fork z nazwa pliku otwartego
void Tree::Fork_1(PCB *process, const std::string &name, const std::string &file_name, MemoryManager &mm, const int &mem) {
	//dodanie dziecka init'a
	if (process->PID == Pname.PID) {
		Tree *temp = new Tree();
		temp->F_process = process;
		Up_data(temp->Pname, name, file_name, mm, mem);
		Children_list.push_back(temp);
	}
	//dodanie potomka dla dziecka init'a
	else {
		for (Tree *p1 : Children_list) {
			if (p1->Pname.PID == process->PID) {
				Tree *temp = new Tree();
				temp->F_process = process;
				Up_data(temp->Pname, name, file_name, mm, mem);
				p1->Children_list.push_back(temp);
				break;
			}
			else if (p1->Children_list.size() != 0) {
				for (Tree *p2 : p1->Children_list) {
					if (p2->Pname.PID == process->PID) {
						Tree *temp = new Tree();
						temp->F_process = process;
						Up_data(temp->Pname, name, file_name, mm, mem);
						p2->Children_list.push_back(temp);
						//wyjscie z pierwszej petli (poziom drugi) -> init jest pierwszym
						p1 = *(Children_list.end() - 1);
						break;
					}
				}
			}
		}
		//throw 3;
	}
}
//nadanie wartosci pol w PCB
void Tree::Up_data(PCB &process, const std::string &name, const std::string &file_name, MemoryManager &mm, const int &mem) {
	double pages = ceil((double)mem / 16);
	process.Process_name = name;
	process.PID = Free_pid;
	process.Process_size = mem;
	process.File_name = file_name;
	if (mm.LoadProgram(file_name, mem, process.PID) == -1) {
		Exit_1(Free_pid, mm);
		throw 1;
	}
	process.page_table = mm.createPageTable(mem, process.PID);
	process.Change_process_state(Ready);
	process.Process_size = pages * 16;
	Free_pid++;
}
//wyswietlenie drzewa
void Tree::Display_tree() {

	//zmienic
	std::cout << "Wyswietlenie wszystkich procesow\n" << std::endl;
	std::cout << "Proces o nazwie "<<Pname.Process_name<<" o ID: " << Pname.PID << std::endl;
	if (Children_list.size() != 0) {
		std::cout << "Jego procesy potomne" << std::endl;
		for (int i = 0; i < Children_list.size(); i++) {
			std::cout << "->Proces " << Children_list[i]->Pname.Process_name << " o numerze ID: " << Children_list[i]->Pname.PID << std::endl;
			if (Children_list[i]->Children_list.size() != 0) {
				for (int j = 0; j < Children_list[i]->Children_list.size(); j++) {
					std::cout << "-->Proces " << Children_list[i]->Children_list[j]->Pname.Process_name << " o numerze ID: "
						<< Children_list[i]->Children_list[j]->Pname.PID << std::endl;
					if (Children_list[i]->Children_list[j]->Children_list.size() != 0) {
						for (int k = 0; k < Children_list[i]->Children_list[j]->Children_list.size(); k++) {
							std::cout << "--->Proces " << Children_list[i]->Children_list[j]->Children_list[k]->Pname.Process_name << " o numerze ID: "
								<< Children_list[i]->Children_list[j]->Children_list[k]->Pname.PID << std::endl;
						}
					}
				}
			}
		}
	}

}

void Tree::Display_processes() {
	std::cout << "\nWyswietlenie wszystkich procesow" << std::endl;
	std::cout << "Proces o nazwie " << Pname.Process_name << " o PID: " << Pname.PID << std::endl;
	if (Children_list.size() != 0) {
		for (Tree *p1 : Children_list) {
			std::cout << "Nazwa procesu:\t" << p1->Pname.Process_name << "\t PID:\t" << p1->Pname.PID << "\tPPID: \t" << Pname.PID << "\tStatus:\t"<< p1->Display_state(p1->Pname.State)<< std::endl;
			if (p1->Children_list.size() > 0) {
				for (Tree *p2 : p1->Children_list) {
					std::cout << "Nazwa procesu:\t" << p2->Pname.Process_name << "\t PID:\t" << p2->Pname.PID << "\tPPID: \t" << p1->Pname.PID << "\tStatus:\t" << p2->Display_state(p2->Pname.State) << std::endl;
					if (p2->Children_list.size()>0) {
						for (Tree *p3 : p2->Children_list) {
							std::cout << "Nazwa procesu:\t" << p3->Pname.Process_name << "\t PID:\t" << p3->Pname.PID << "\tPPID: \t" << p2->Pname.PID << "\tStatus:\t" << p3->Display_state(p3->Pname.State) << std::endl;
						}
					}
				}
			}
		}
	}
}

//wyswietlenie skladowych procesu
void Tree::Display_PCB(MemoryManager &mm, PCB* proces) {
	std::cout << "Proces o nazwie " << proces->Process_name << " ma ID rowne " << proces->PID << std::endl;
	std::cout << "STATUS:\t\t" << proces->Display_state(proces->State) << std::endl;
	std::cout << "Rejestr A:\t\t" << proces->Reg1 << std::endl;
	std::cout << "Rejestr B:\t\t" << proces->Reg2 << std::endl;
	std::cout << "Rejestr C:\t\t" << proces->Reg3 << std::endl;
	std::cout << "Rejestr D:\t\t" << proces->Reg4 << std::endl;
	std::cout << "Priorytet:\t\t" << proces->Priority << std::endl;
	std::cout << "Priorytet dynamiczny:\t" << proces->Dynamic_priority << std::endl;
	std::cout << "Licznik rozkazow:\t" << proces->Command_counter << std::endl;
	std::cout << "Zajmowana pamiec:\t" << proces->Process_size << std::endl;
	mm.showPageTable(proces->page_table);
	std::cout << std::endl;
}

//usuniecie wybranego procesu
void Tree::Exit(const int &id, MemoryManager &mm, Pipeline &pip) {
	std::cout << "Usuniecie procesu o id " << id << std::endl;
	//proces o id innym niz init
	if (id != Pname.PID) {
		//sprawdzenie dzieci inita
		int length = Children_list.size();
		for (int i = 0; i < length; i++) {
			//usuniecie dziecka jesli lista jego dzieci jest pusta
			if (Children_list[i]->Pname.PID == id &&Children_list[i]->Children_list.size() == 0) {
				//ogarnac usuwanie potoku jak go nie ma
				pip.deletePipe(Children_list[i]->Pname);
				Children_list.erase(Children_list.begin() + i);
				mm.Remove(id);
				break;
			}
			//usuniecie dziecka jesli jego lista dzieci nie jest pusta
			else if (Children_list[i]->Pname.PID == id && Children_list[i]->Children_list.size() != 0) {
				int length1 = Children_list[i]->Children_list.size();
				//przypisanie dzieci do inita
				for (int j = 0; j < length1; j++) {
					//przypisanie dziecka
					Children_list.push_back(Children_list[i]->Children_list[0]);
					//usuniecie przypisanego dziecka
					Children_list[i]->Children_list.erase(Children_list[i]->Children_list.begin());
				}
				pip.deletePipe(Children_list[i]->Pname);
				Children_list.erase(Children_list.begin() + i);
				mm.Remove(id);
				break;
			}
			//usuniecie potomka dziecka
			else if (Children_list[i]->Children_list.size() != 0) {
				int length1 = Children_list[i]->Children_list.size();
				for (int j = 0; j<length1; j++) {
					//jesli jego lista dzieci jest pusta to usun
					if (Children_list[i]->Children_list[j]->Pname.PID == id && Children_list[i]->Children_list[j]->Children_list.size() == 0) {
						pip.deletePipe(Children_list[i]->Children_list[j]->Pname);
						Children_list[i]->Children_list.erase(Children_list[i]->Children_list.begin() + j);
						mm.Remove(id);
						i = 10000;
						break;
					}

					//jesli jego lista dzieci nie jest pusta
					else if (Children_list[i]->Children_list[j]->Pname.PID == id && Children_list[i]->Children_list[j]->Children_list.size() != 0) {
						//przypisanie dzieci do inita
						int length2 = Children_list[i]->Children_list[j]->Children_list.size();
						for (int k = 0; k < length2; k++) {
							Children_list.push_back(Children_list[i]->Children_list[j]->Children_list[k]);
							//Children_list[i]->Children_list[j]->Children_list.erase(Children_list[i]->Children_list[j]->Children_list.begin());
						}
						pip.deletePipe(Children_list[i]->Children_list[j]->Pname);
						Children_list[i]->Children_list.erase(Children_list[i]->Children_list.begin() + j);
						mm.Remove(id);
						i = 10000;
						j = 10000;
						break;
					}
					else if (Children_list[i]->Children_list[j]->Children_list.size() != 0) {
						for (int k = 0; k < Children_list[i]->Children_list[j]->Children_list.size(); k++) {
							if (Children_list[i]->Children_list[j]->Children_list[k]->Pname.PID == id) {
								pip.deletePipe(Children_list[i]->Children_list[j]->Children_list[k]->Pname);
								Children_list[i]->Children_list[j]->Children_list.erase(Children_list[i]->Children_list[j]->Children_list.begin() + k);
								mm.Remove(id);
								i = 10000;
								j = 10000;
								break;
							}
						}
					}
				}
			}
		}
	}
	else {
		std::cout << "Nie da sie usunac inita" << std::endl;
	}
}
//usuniecie procesu jak nie ma potoku
void Tree::Exit_1(const int &id, MemoryManager &mm) {
	std::cout << "Usuniecie procesu o id " << id << std::endl;
	//proces o id innym niz init
	if (id != Pname.PID) {
		//sprawdzenie dzieci inita
		int length = Children_list.size();
		for (int i = 0; i < length; i++) {
			//usuniecie dziecka jesli lista jego dzieci jest pusta
			if (Children_list[i]->Pname.PID == id &&Children_list[i]->Children_list.size() == 0) {
				Children_list.erase(Children_list.begin() + i);
				//pip.deletePipe((Children_list.begin()+i)->Pname);
				mm.Remove(id);
				break;
			}
			//usuniecie dziecka jesli jego lista dzieci nie jest pusta
			else if (Children_list[i]->Pname.PID == id && Children_list[i]->Children_list.size() != 0) {
				int length1 = Children_list[i]->Children_list.size();
				//przypisanie dzieci do inita
				for (int j = 0; j < length1; j++) {
					//przypisanie dziecka
					Children_list.push_back(Children_list[i]->Children_list[0]);
					//usuniecie przypisanego dziecka
					Children_list[i]->Children_list.erase(Children_list[i]->Children_list.begin());
				}
				Children_list.erase(Children_list.begin() + i);
				mm.Remove(id);
				break;
			}
			//usuniecie potomka dziecka
			else if (Children_list[i]->Children_list.size() != 0) {
				int length1 = Children_list[i]->Children_list.size();
				for (int j = 0; j<length1; j++) {
					//jesli jego lista dzieci jest pusta to usun
					if (Children_list[i]->Children_list[j]->Pname.PID == id && Children_list[i]->Children_list[j]->Children_list.size() == 0) {
						Children_list[i]->Children_list.erase(Children_list[i]->Children_list.begin() + j);
						mm.Remove(id);
						i = 10000;
						break;
					}

					//jesli jego lista dzieci nie jest pusta
					else if (Children_list[i]->Children_list[j]->Pname.PID == id && Children_list[i]->Children_list[j]->Children_list.size() != 0) {
						//przypisanie dzieci do inita
						int length2 = Children_list[i]->Children_list[j]->Children_list.size();
						for (int k = 0; k < length2; k++) {
							Children_list.push_back(Children_list[i]->Children_list[j]->Children_list[k]);
							//Children_list[i]->Children_list[j]->Children_list.erase(Children_list[i]->Children_list[j]->Children_list.begin());
						}
						Children_list[i]->Children_list.erase(Children_list[i]->Children_list.begin() + j);
						mm.Remove(id);
						i = 10000;
						j = 10000;
						break;
					}
					else if (Children_list[i]->Children_list[j]->Children_list.size() != 0) {
						for (int k = 0; k < Children_list[i]->Children_list[j]->Children_list.size(); k++) {
							if (Children_list[i]->Children_list[j]->Children_list[k]->Pname.PID == id) {
								Children_list[i]->Children_list[j]->Children_list.erase(Children_list[i]->Children_list[j]->Children_list.begin() + k);
								mm.Remove(id);
								i = 10000;
								j = 10000;
								break;
							}
						}
					}
				}
			}
		}
	}
	else {
		std::cout << "Nie da sie usunac inita" << std::endl;
	}
}
//zwracanie procesu po id
PCB& Tree::Get_process(const int &id) {
	if (id == Pname.PID) return Pname;
	else if (Children_list.size() > 0) {
		for (Tree *p1 : Children_list) {
			if (id == p1->Pname.PID) return p1->Pname;
			if (p1->Children_list.size() > 0) {
				for (Tree *p2 : p1->Children_list) {
					if (id == p2->Pname.PID) return p2->Pname;
					if (p2->Children_list.size()>0) {
						for (Tree *p3 : p2->Children_list) {
							if (id == p3->Pname.PID) return p3->Pname;
						}
					}
				}
			}
		}
	}
	throw 2;
}
//zwracanie procesu po nazwie
PCB &Tree::Get_process_1(const std::string &proces_name) {
	if (proces_name == Pname.Process_name) return Pname;
	else if (Children_list.size() > 0) {
		for (Tree *p1 : Children_list) {
			if (proces_name == p1->Pname.Process_name) return p1->Pname;
			if (p1->Children_list.size() > 0) {
				for (Tree *p2 : p1->Children_list) {
					if (proces_name == p2->Pname.Process_name) return p2->Pname;
					if (p2->Children_list.size()>0) {
						for (Tree *p3 : p2->Children_list) {
							if (proces_name == p3->Pname.Process_name) return p3->Pname;
						}
					}
				}
			}
		}
	}
	throw 1;
}
//lista gotowych procesow
std::vector<int> Tree::Ready_processes() {
	std::vector<int> vec;
	if (Ready == Pname.State) vec.push_back(Pname.PID);
	if (Children_list.size()>0) {
		for (Tree *p1 : Children_list) {
			if (Ready == p1->Pname.State)	vec.push_back(p1->Pname.PID);
			if (p1->Children_list.size() > 0) {
				for (Tree * p2 : p1->Children_list) {
					if (Ready == p2->Pname.State) vec.push_back(p2->Pname.PID);
					if (p2->Children_list.size() > 0) {
						for (Tree * p3 : p2->Children_list) {
							if (Ready == p3->Pname.State) vec.push_back(p3->Pname.PID);
						}
					}
				}
			}
		}
	}
	return vec;
}