#include "interpreter.h"







	void interpreter::PobierzRejestry(Planista &planista, PCB &pcb, Tree &tree)  //pobieranie rejestrów z procesu który jest w stanie running
	{

		planista.check(pcb, tree); //ustawianie procesu running
		PID = pcb.PID;
		rejA = pcb.Reg1;
		rejB = pcb.Reg2;
		rejC = pcb.Reg3;
		rejD = pcb.Reg4;
		liczRoz = pcb.Command_counter;

	}


	void interpreter::StanRej()
	{
		std::cout << "PID: " << PID << std::endl;
		std::cout << "A: " << rejA << std::endl;
		std::cout << "B: " << rejB << std::endl;
		std::cout << "C: " << rejC << std::endl;
		std::cout << "D: " << rejD << std::endl;
		std::cout << "Licznik Rozkazow: " << liczRoz << std::endl;
		std::cout << "--------------------------------" << std::endl << std::endl;
	}

	void interpreter::zapiszRejestry(PCB &pcb)
	{

		pcb.PID = PID;
		pcb.Reg1 = rejA;
		pcb.Reg2 = rejB;
		pcb.Reg3 = rejC;
		pcb.Reg4 = rejD;
		pcb.Command_counter = liczRoz;
		pcb.CPU += liczRoz;                                      // Damian!!!!!!!! dodaje sobie CPU!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	}

	std::string interpreter::pobierzRozkaz(MemoryManager &mm, PCB &pcb)
	{

		std::string rozkaz;
		rozkaz = mm.Get( &pcb , liczRoz);
		liczRoz += rozkaz.size() + 1;
		return rozkaz;

	}

	void interpreter::WykonajProgram(MemoryManager &mm, PCB &pcb, Planista &planista, Tree &tree, Pipeline &pipeline, HDD &dysk)
	{
		/////////////////////////////////////

		PobierzRejestry(planista, pcb, tree);
		std::string operacja;
		operacja.clear();
		operacja = pobierzRozkaz(mm, pcb);
		std::cout << "Rozkaz: " << operacja << " "; 
		std::string rej1 = " ", rej2 = " ";
		int liczba = 0;

		///////////////////////////////////// dodawanie 

		if (operacja == "AD")
		{
			rej1 = pobierzRozkaz(mm, pcb);
			rej2 = pobierzRozkaz(mm, pcb);
			std::cout << rej1 << " " << rej2 << std::endl;
			if (rej2 != "A" && rej2 != "B" && rej2 != "C" && rej2 != "D" )
			{
				liczba = stoi(rej2);
			}

			//////

			if (rej1 == "A" && liczba != 0)
			{
				rejA += liczba;
			}
			else if (rej1 == "A" && rej2 == "B")
			{
				rejA += rejB;
			}
			else if (rej1 == "A" && rej2 == "C")
			{
				rejA += rejC;
			}
			else if (rej1 == "A" && rej2 == "A")
			{
				rejA += rejA;
			}

			//////////////////
			if (rej1 == "B" && liczba != 0)
			{
				rejB += liczba;
			}
			else if (rej1 == "B" && rej2 == "A")
			{
				rejB += rejA;
			}
			else if (rej1 == "B" && rej2 == "C")
			{
				rejB += rejC;
			}
			else if (rej1 == "B" && rej2 == "B")
			{
				rejB += rejB;
			}

			///////////////////
			if (rej1 == "C" && liczba != 0)
			{
				rejC += liczba;
			}
			else if (rej1 == "C" && rej2 == "B")
			{
				rejC += rejB;
			}
			else if (rej1 == "C" && rej2 == "A")
			{
				rejC += rejA;
			}
			else if (rej1 == "C" && rej2 == "C")
			{
				rejC += rejC;
			}
			StanRej();
			zapiszRejestry(pcb);
		}
		////////////////////////////////////////// odejmowanie 
		if (operacja == "SB")
		{

			rej1 = pobierzRozkaz(mm, pcb);
			rej2 = pobierzRozkaz(mm, pcb);
			std::cout << rej1 << " " << rej2 << std::endl;

			if (rej2 != "A" && rej2 != "B" && rej2 != "C" && rej2 != "D" ) liczba = stoi(rej2);

			/////

			if (rej1 == "A" && liczba != 0)
			{
				rejA -= liczba;
			}
			else if (rej1 == "A" && rej2 == "B")
			{
				rejA -= rejB;
			}
			else if (rej1 == "A" && rej2 == "C")
			{
				rejA -= rejC;
			}
			else if (rej1 == "A" && rej2 == "A")
			{
				rejA -= rejA;
			}
			//////////////////
			if (rej1 == "B" && liczba != 0)
			{
				rejB -= liczba;
			}
			else if (rej1 == "B" && rej2 == "A")
			{
				rejB -= rejA;
			}
			else if (rej1 == "B" && rej2 == "C")
			{
				rejB -= rejC;
			}
			else if (rej1 == "B" && rej2 == "B")
			{
				rejB -= rejB;
			}
			///////////////////
			if (rej1 == "C" && liczba != 0)
			{
				rejC -= liczba;
			}
			else if (rej1 == "C" && rej2 == "B")
			{
				rejC -= rejB;
			}
			else if (rej1 == "C" && rej2 == "A")
			{
				rejC -= rejA;
			}
			else if (rej1 == "C" && rej2 == "C")
			{
				rejC -= rejC;
			}
			StanRej();
			zapiszRejestry(pcb);
		}
		////////////////////////////////////////////mnozenie
		if (operacja == "MU")
		{
			rej1 = pobierzRozkaz(mm, pcb);
			rej2 = pobierzRozkaz(mm, pcb);
			std::cout << rej1 << " " << rej2 << std::endl;

			if (rej2 != "A" && rej2 != "B" && rej2 != "C") liczba = stoi(rej2);

			//////

			if (rej1 == "A" && liczba != 0)
			{
				rejA *= liczba;
			}
			else if (rej1 == "A" && rej2 == "B")
			{
				rejA *= rejB;
			}
			else if (rej1 == "A" && rej2 == "C")
			{
				rejA *= rejC;
			}
			else if (rej1 == "A" && rej2 == "A")
			{
				rejA *= rejA;
			}
			//////////////////
			if (rej1 == "B" && liczba != 0)
			{
				rejB *= liczba;
			}
			else if (rej1 == "B" && rej2 == "A")
			{
				rejB *= rejA;
			}
			else if (rej1 == "B" && rej2 == "C")
			{
				rejB *= rejC;
			}
			else if (rej1 == "B" && rej2 == "B")
			{
				rejB *= rejB;
			}
			///////////////////
			if (rej1 == "C" && liczba != 0)
			{
				rejC *= liczba;
			}
			else if (rej1 == "C" && rej2 == "B")
			{
				rejC *= rejB;
			}
			else if (rej1 == "C" && rej2 == "A")
			{
				rejC *= rejA;
			}
			else if (rej1 == "C" && rej2 == "C")
			{
				rejC *= rejC;
			}
			StanRej();
			zapiszRejestry(pcb);
		}
		//////////////////////////////////////dzielenie 
		if (operacja == "DV")
		{
			rej1 = pobierzRozkaz(mm, pcb);
			rej2 = pobierzRozkaz(mm, pcb);
			std::cout << rej1 << " " << rej2 << std::endl;

			if (rej2 != "A" && rej2 != "B" && rej2 != "C" && rej2!="D") liczba = stoi(rej2);

			/////

			if (rej1 == "A" && liczba != 0)
			{
				rejA /= liczba;
			}
			else if (rej1 == "A" && rej2 == "B")
			{
				rejA /= rejB;
			}
			else if (rej1 == "A" && rej2 == "C")
			{
				rejA /= rejC;
			}
			else if (rej1 == "A" && rej2 == "A")
			{
				rejA /= rejA;
			}
			//////////////////
			if (rej1 == "B" && liczba != 0)
			{
				rejB /= liczba;
			}
			else if (rej1 == "B" && rej2 == "A")
			{
				rejB /= rejA;
			}
			else if (rej1 == "B" && rej2 == "C")
			{
				rejB /= rejC;
			}
			else if (rej1 == "B" && rej2 == "B")
			{
				rejB /= rejB;
			}
			///////////////////
			if (rej1 == "C" && liczba != 0)
			{
				rejC /= liczba;
			}
			else if (rej1 == "C" && rej2 == "B")
			{
				rejC /= rejB;
			}
			else if (rej1 == "C" && rej2 == "A")
			{
				rejC /= rejA;
			}
			else if (rej1 == "C" && rej2 == "C")
			{
				rejC /= rejC;
			}
			StanRej();
			zapiszRejestry(pcb);
		}
		/////////////////////////////////////// zapis wartoœci do rejestru 
		if (operacja == "MO")
		{
			rej1 = pobierzRozkaz(mm, pcb);			
			rej2 = pobierzRozkaz(mm, pcb);
			std::cout << rej1 << " " << rej2 << std::endl;

			if (rej2 != "A" && rej2 != "B" && rej2 != "C" && rej2 != "D") liczba = stoi(rej2);

			//////////

			if (rej1 == "A" && liczba != 0)
			{
				rejA = liczba;
			}
			else if (rej1 == "A" && rej2 == "B")
			{
				rejA = rejB;
			}
			else if (rej1 == "A" && rej2 == "C")
			{
				rejA = rejC;
			}
			//////////////////
			if (rej1 == "B" && liczba != 0)
			{
				rejB = liczba;
			}
			else if (rej1 == "B" && rej2 == "A")
			{
				rejB = rejA;
			}
			else if (rej1 == "B" && rej2 == "C")
			{
				rejB = rejC;
			}

			///////////////////
			if (rej1 == "C" && liczba != 0)
			{
				rejC = liczba;
			}
			else if (rej1 == "C" && rej2 == "B")
			{
				rejC = rejB;
			}
			else if (rej1 == "C" && rej2 == "A")
			{
				rejC = rejA;
			}
			////////////////
			else if (rej1 == "D" && rej2 == "A")
			{
				rejD = rejA;
			}
			else if (rej1 == "D" && rej2 == "B")
			{
				rejD = rejB;
			}
			else if (rej1 == "D" && rej2 == "C")
			{
				rejD = rejC;
			}
			else if (rej1 == "D" && liczba != 0)
			{
				rejD = liczba;
			}

			StanRej();
			zapiszRejestry(pcb);
		}
		/////////////////////// inkrementacja i dekrementacja rejestrów

		if (operacja == "IC")
		{
			rej1 = pobierzRozkaz(mm, pcb);
			std::cout << rej1 << std::endl;
			if (rej1 == "A")
				rejA++;
			if (rej1 == "B")
				rejB++;
			if (rej1 == "C")
				rejC++;
			if (rej1 == "D")
				rejD++;
			StanRej();
			zapiszRejestry(pcb);
		}

		if (operacja == "DC")
		{
			rej1 = pobierzRozkaz(mm, pcb);
			std::cout << rej1 << std::endl;
			if (rej1 == "A")
				rejA--;
			if (rej1 == "B")
				rejB--;
			if (rej1 == "C")
				rejC--;
			if (rej1 == "D")
				rejD--;

			StanRej();
			zapiszRejestry(pcb);
		}




		/////////////////////////////// pobieranie wartosci z pamici

		if (operacja == "MV")
		{

			rej1 = pobierzRozkaz(mm, pcb);
			rej2 = pobierzRozkaz(mm, pcb);
			std::cout << rej1 << " " << rej2 << std::endl;
			liczba = stoi(rej2);

			if (rej1 == "A");
			{
				rejA = stoi(mm.Get(&pcb, liczba));
			}
			if (rej1 == "B")
			{
				rejB = stoi(mm.Get(&pcb, liczba));
			}
			if (rej1 == "C")
			{
				rejC = stoi(mm.Get(&pcb, liczba));
			}
			if (rej1 == "D")
				rejD = stoi(mm.Get(&pcb, liczba));

			StanRej();
			zapiszRejestry(pcb);

		}
		/////////////////////////////////////////zapis wartosci do pamiêci

		if (operacja == "MR")
		{
			rej1 = pobierzRozkaz(mm, pcb); //adres gdzie chcemy zapisaæ
			rej2 = pobierzRozkaz(mm, pcb); // co chcemy zapisaæ 
			liczba = stoi(rej1);
			if (rej2 == "A")
			{
				rej1 = std::to_string(rejA);
				mm.Write(&pcb, liczba, rej1 );
			}
			else if (rej2 == "B")
			{
				rej1 = std::to_string(rejB);
				mm.Write(&pcb, liczba, rej1);
			}
			else if (rej2 == "C")
			{
				rej1 = std::to_string(rejC);
				mm.Write(&pcb, liczba, rej1);
			}
			else if (rej2 == "D")
			{
				rej1 = std::to_string(rejD);
				mm.Write(&pcb, liczba, rej1);
			}
			
		}


		////////////////////////////////////////// skoki 

		if (operacja == "JP") //skok do adresu
		{
			rej1 = pobierzRozkaz(mm, pcb);
			std::cout << rej1 << std::endl;
			liczRoz = stoi(rej1);

			StanRej();
			zapiszRejestry(pcb);

		}
		//////

		if (operacja == "JM") // skok do pamiêci pod warunkiem 
		{
			rej1 = pobierzRozkaz(mm, pcb);
			int adres = stoi(rej1);
			std::cout << rej1 << std::endl;
			
			if (rejD >= 0)
			{
				liczRoz = adres;
			}
			rejD--;
			StanRej();
			
			zapiszRejestry(pcb);


		}




		////////////////////////////////////////// potoki i komunikacja

		if (operacja == "SP") // stworzenie potoku 
		{

			int id1, id2;
			rej1 = pobierzRozkaz(mm, pcb);
			rej2 = pobierzRozkaz(mm, pcb);
			pipeline.createPipe(tree.Get_process_1(rej1), tree.Get_process_1(rej2));        
			StanRej();
			zapiszRejestry(pcb);

		}
		////////
		if (operacja == "UP") //usuniecie potoku
		{
			int id;
			id = stoi(pobierzRozkaz(mm, pcb));
			pipeline.deletePipe(tree.Get_process(id));
			StanRej();
			zapiszRejestry(pcb);
		}

		if (operacja == "SM") //wys³anie wiadomosci SM nazwa wiadomosc
		{
			int id;

			
			rej1 = pobierzRozkaz(mm, pcb);
			rej2 = pobierzRozkaz(mm, pcb);
			PCB p1;
			p1 = tree.Get_process_1(rej1);
			if (p1.Descriptor[0] >= 0)
			{
				pipeline.pipes[p1.Descriptor[0]]->write(rej2);
			}
			else
			{
				std::cout << "Proces nie przypisany do potoku" << std::endl;
			}
			StanRej();
			zapiszRejestry(pcb);
		}

		/////

		if (operacja == "RM") //odczytanie wiadomosci RM id ile_chcesz_odczytaæ
		{
			int dlugosc;
			rej2 = pobierzRozkaz(mm, pcb);
			std::string adres;
			adres = pobierzRozkaz(mm, pcb);
			int adr;
			adr = stoi(adres);
			dlugosc = stoi(pobierzRozkaz(mm, pcb));
			PCB p1;
			p1 = tree.Get_process_1(rej2);
			if (p1.Descriptor[0] >= 0)
			{
				rej1 = pipeline.pipes[p1.Descriptor[0]]->read(dlugosc);
				if (mm.Write(&p1, adr, rej1)==-1)
				{
					planista.make_zombie(p1,tree,mm);
					std::cout << "Pamiec pelna!" << std::endl;
				}
				else {
						std::cout << "Odczytana wiadomosc: " << rej1;
				}
				
			}
			else
			{
				std::cout << "Proces nie przypisany do potoku" << std::endl;
			}
			StanRej();
			zapiszRejestry(pcb);
		}

		////////////////////////////////////////

		if (operacja == "CL") //czyszczenie ekranu
		{
			system("cls");
		}

		//////////////////////////////////// dysk

		if (operacja == "WP") //wypisz dysk
		{
			dysk.show_all_info();
			zapiszRejestry(pcb);
		}
		
		if (operacja == "CF") //utworz plik
		{
			rej1 = pobierzRozkaz(mm, pcb);
			rej2 = pobierzRozkaz(mm,pcb);
			dysk.create_file(rej1, stoi(rej2));
			zapiszRejestry(pcb);

		}
		if (operacja == "ZP") // zapisz do pliku
		{
			rej1 = pobierzRozkaz(mm, pcb);
			//rej2 = pobierzRozkaz(mm, pcb);
			std::string tekst;
			tekst = "RejA: " + std::to_string(rejA) + " RejB: " + std::to_string(rejB) + "RejC: " + std::to_string(rejC);
			//tekst = pobierzRozkaz(mm,pcb);
			std::cout << rej1 << "II\n";
			dysk.write_file(rej1, tekst, 0);
			//dysk.save_to_file();
			zapiszRejestry(pcb);
		}
		if (operacja == "CP") //czytaj plik
		{
			rej1 = pobierzRozkaz(mm, pcb);
			std::cout << dysk.read_file(rej1) << std::endl;
			zapiszRejestry(pcb);
		}

		/////////////////////////////pamiec 

		if (operacja == "PP")
		{
			mm.showPMemory();
			std::cout << std::endl;
			StanRej();
			zapiszRejestry(pcb);
		}


		////////////////////////////procesy

		if (operacja == "XW") //wyswietlanie drzewa procesów
		{
			tree.Display_tree();
			std::cout << std::endl;
			StanRej();
			zapiszRejestry(pcb);
		}

		if (operacja == "XP") //tworzenie procesu
		{
			rej1 = pobierzRozkaz(mm, pcb); //nazwa
			liczba = stoi(pobierzRozkaz(mm, pcb)); //rozmiar

			try {
				tree.Fork_1(&(tree.Get_process(1)), rej1, "program10.txt", mm, liczba);
			}
			catch (int e) {
				if (e == 1) {

				}
			}
			zapiszRejestry(pcb);
		}

		//////////////////

		if (operacja == "HT") //koniec pliku, zapis rej do procesu
		{
			zapiszRejestry(pcb);
			planista.make_zombie(pcb,tree,mm);
			//pcb.Change_process_state(Zombie);

		}




	}

		
