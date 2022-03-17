#include <iostream>
#include <string>
#include <cstdlib>
#include <map>
#include "ui.h"


Usi::Usi(Service& serv) noexcept :serv{ serv } {
}

void Usi::Afisare_discipline() const{

	try {
		std::vector<Disciplina> lista = serv.repo.get_all();
		std::cout << "============================================================================\n";
		if (lista.size() == 0)
			std::cout << "Nu sunt discipline de afisat\r\n";
		else {
			for (const Disciplina& dis : lista) {
				std::cout << "|| ID: " << dis.get_id() << " || Nume: " << dis.get_nume() << " || Ore: " << dis.get_ore() << " || Tip: " << dis.get_tip() << " || Cadru: " << dis.get_cadru() << " ||\n";
			}
		}
		std::cout << "============================================================================\n";
	}
	catch (const MyError& err) { std::cout << err.get_mesaj(); }
}

void Usi::Adauga_disciplina(){
	std::string nume, tip, cadru,idi,orei;
	int id = -1, ore = -1;
	try {
		std::cout << "Introduceti ID-ul disciplinei: ";
		std::cin >> idi;
		std::cin.get();
		id = serv.validator.Validare_nr(idi);
		std::cout << "Introduceti numele disciplinei: ";
		std::getline(std::cin, nume);
		std::cout << "Introduceti orele pe saptamana a disciplinei: ";
		std::cin >> orei;
		std::cin.get();
		ore = serv.validator.Validare_nr(orei);
		std::cout << "Introduceti tipul disciplinei: ";
		std::getline(std::cin, tip);
		std::cout << "Introduceti cadrul disciplinei: ";
		std::getline(std::cin, cadru);
		try {
			serv.Add_dis(id, nume, ore, tip, cadru);
			std::cout << "Disciplina adaugata cu succes!\n";
		}
		catch (const MyError& err) { std::cout << err.get_mesaj(); }
	}
	catch (const MyError& err) { std::cout << err.get_mesaj(); }
}

void Usi::Sterge_disciplina(){
	std::string id;
	int idi;
	std::cout << "Introduceti id-ul disciplinei pe care doriti sa o stergeti: ";
	std::cin >> id;
	idi = atoi(id.c_str());
	if (idi != 0 || id=="0") {
		try {
			serv.Del_dis(idi);
			std::cout << "Disciplina stearsa cu succes!\n";
		}
		catch (const MyError& err) { std::cout << err.get_mesaj(); }
	}
}

void Usi::Modifica_disciplina(){
	int id=-1, ore=-1;
	std::string nume, tip, cadru,orei,idi;
	try {
		std::cout << "Introduceti ID-ul disciplinei pe care doriti sa o modificati: ";
		std::cin >> idi;
		std::cin.get();
		id = serv.validator.Validare_nr(idi);
		std::cout << "Introduceti numele nou al disciplinei: ";
		std::getline(std::cin, nume);
		std::cout << "Introduceti orele noi pe saptamana ale disciplinei: ";
		std::cin >> orei;
		std::cin.get();
		ore = serv.validator.Validare_nr(orei);
		std::cout << "Introduceti tipul nou al disciplinei: ";
		std::getline(std::cin, tip);
		std::cout << "Introduceti cadrul nou al disciplinei: ";
		std::getline(std::cin, cadru);
		try {
			serv.Mod_dis(id, nume, ore, tip, cadru);
			std::cout << "Disciplina modificata cu succes!\n";
		}
		catch (const MyError& err) { std::cout << err.get_mesaj(); }
	}
	catch (const MyError& err) { std::cout << err.get_mesaj(); }
}

void Usi::Cauta_disciplina() const{
	std::string idi;
	int id;
	std::cout << "Introduceti id-ul disciplinei cautate: ";
	std::cin >> idi;
	try {
		id = serv.validator.Validare_nr(idi);
		std::cout << "============================================================================\n";
		std::vector<Disciplina> lista = serv.Caut_dis(id);
		if (lista.size() == 0)
			std::cout << "Nu s-a gasit disciplina\r\n";
		else {
			for (const Disciplina& dis: lista) {
				std::cout << "|| ID: " << dis.get_id() << " || Nume: " << dis.get_nume() << " || Ore: " << dis.get_ore() << " || Tip: " << dis.get_tip() << " || Cadru: " << dis.get_cadru() << " ||\n";
			}
		}
		std::cout << "============================================================================\n";
	}
	catch (const MyError& err) { std::cout << err.get_mesaj(); }
}

void Usi::Filtrare_ore() const {
	std::string orei;
	int ore;
	std::cout << "Introduceti nr de ore dorit: ";
	std::cin >> orei;
	try {
		ore = serv.validator.Validare_nr(orei);
		std::cout << "============================================================================\n";
		std::vector<Disciplina> lista = serv.Filtr_ore(ore);
		if (lista.size() == 0)
			std::cout << "Nu s-a gasit disciplina\r\n";
		else {
			for (const Disciplina& dis : lista) {
				std::cout << "|| ID: " << dis.get_id() << " || Nume: " << dis.get_nume() << " || Ore: " << dis.get_ore() << " || Tip: " << dis.get_tip() << " || Cadru: " << dis.get_cadru() << " ||\n";
			}
		}
		std::cout << "============================================================================\n";
	}
	catch (const MyError& err) { std::cout << err.get_mesaj(); }
}

void Usi::Filtrare_cadru() const {
	std::string cadru;
	std::cout << "Introduceti numele cadrului didactic dorit: ";
	std::cin >> cadru;
	try {
		std::cout << "============================================================================\n";
		std::vector<Disciplina> lista = serv.Filtr_cadru(cadru);
		if (lista.size() == 0)
			std::cout << "Nu s-a gasit disciplina\r\n";
		else {
			for (const Disciplina& dis : lista) {
				std::cout << "|| ID: " << dis.get_id() << " || Nume: " << dis.get_nume() << " || Ore: " << dis.get_ore() << " || Tip: " << dis.get_tip() << " || Cadru: " << dis.get_cadru() << " ||\n";
			}
		}
		std::cout << "============================================================================\n";
	}
	catch (const MyError& err) { std::cout << err.get_mesaj(); }
}

void Usi::Filtrare() const {
	std::cout << "Dupa ce doriti sa filtrati?:\n1 - Nr de ore\n2 - Cadru didactic\n";
	int comanda = -1;
	std::string comandai;
	std::cin >> comandai;
	try {
		comanda = serv.validator.Validare_nr(comandai);
	}
	catch (const MyError& err) { std::cout << err.get_mesaj(); }
	if (comanda == 1)
		Filtrare_ore();
	else if (comanda == 2)
		Filtrare_cadru();
	else
		std::cout << "Comanda invalida!\n";
}

void Usi::Sortare_ore() const {
	try {
		std::cout << "============================================================================\n";
		std::vector<Disciplina> lista = serv.Sort_ore();
		if (lista.size() == 0)
			std::cout << "Nu sunt discipline de afisat\r\n";
		else {
			for (const Disciplina& dis : lista) {
				std::cout << "|| ID: " << dis.get_id() << " || Nume: " << dis.get_nume() << " || Ore: " << dis.get_ore() << " || Tip: " << dis.get_tip() << " || Cadru: " << dis.get_cadru() << " ||\n";
			}
		}
		std::cout << "============================================================================\n";
	}
	catch (const MyError& err) { std::cout << err.get_mesaj(); }
}

void Usi::Sortare_nume() const {
	try {
		std::cout << "============================================================================\n";
		std::vector<Disciplina> lista = serv.Sort_nume();
		if (lista.size() == 0)
			std::cout << "Nu sunt discipline de afisat\r\n";
		else {
			for (const Disciplina& dis : lista) {
				std::cout << "|| ID: " << dis.get_id() << " || Nume: " << dis.get_nume() << " || Ore: " << dis.get_ore() << " || Tip: " << dis.get_tip() << " || Cadru: " << dis.get_cadru() << " ||\n";
			}
		}
		std::cout << "============================================================================\n";
	}
	catch (const MyError& err) { std::cout << err.get_mesaj(); }
}

void Usi::Sortare_else() const {
	try {
		std::cout << "============================================================================\n";
		std::vector<Disciplina> lista = serv.Sort_else();
		if (lista.size() == 0)
			std::cout << "Nu sunt discipline de afisat\r\n";
		else {
			for (const Disciplina& dis : lista) {
				std::cout << "|| ID: " << dis.get_id() << " || Nume: " << dis.get_nume() << " || Ore: " << dis.get_ore() << " || Tip: " << dis.get_tip() << " || Cadru: " << dis.get_cadru() << " ||\n";
			}
		}
		std::cout << "============================================================================\n";
	}
	catch (const MyError& err) { std::cout << err.get_mesaj(); }
}

void Usi::Sortare() const {
	std::cout << "Dupa ce doriti sa sortati?:\n1 - Nr de ore\n2 - Numele disciplinelor\n3 - Cadru didactic si mai apoi dupa tip\n";
	int comanda = -1;
	std::string comandai;
	std::cin >> comandai;
	try {
		comanda = serv.validator.Validare_nr(comandai);
	}
	catch (const MyError& err) { std::cout << err.get_mesaj(); }
	if (comanda == 1)
		Sortare_ore();
	else if (comanda == 2)
		Sortare_nume();
	else if (comanda == 3)
		Sortare_else();
	else
		std::cout << "Comanda invalida!\n";
}

void Usi::Adauga_disciplina_ctr() const {
	std::cout << "Introduceti numele disciplinei pe care doriti sa o adaugati: ";
	std::string nume;
	std::cin >> nume;
	try {
		serv.adauga_ctr(nume);
	}
	catch (const MyError& err) { std::cout << err.get_mesaj(); }
}

void Usi::Genereaza() const {
	int nr;
	std::string nri;
	try {
		std::cout << "Introduceti nr de discipline care doriti sa fie in contractul nou generat: ";
		std::cin >> nri;
		std::cin.get();
		nr = serv.validator.Validare_nr(nri);
		serv.genereaza(nr);
	}
	catch (const MyError& err) { std::cout << err.get_mesaj(); }
}

void Usi::Clear() const {
	serv.contract.goleste();
}

void Usi::Export() const {
	std::cout << "Introduceti numele fisierului in care doriti sa exportati: ";
	std::string nume;
	std::cin >> nume;
	try {
		serv.contract.export_ctr(nume);
	}
	catch (const MyError& err) { std::cout << err.get_mesaj(); }
}

void Usi::Raport() const {
	std::map<std::string, DTO> dictionar;
	dictionar = serv.genereaza_rap();
	std::map<std::string, DTO>::iterator itr;
	std::cout << "Tip/nraparitii\n";
	for (itr = dictionar.begin(); itr != dictionar.end(); itr++) {
		std::cout << itr->first << ' ' << itr->second.get_count() << '\n';
	}
}

void Usi::run(){
	while (true) {
		int comanda=-1;
		std::string comandai;
		std::cout << "1 - Afisare discipline\n2 - Adaugare disciplina\n3 - Stergere disciplina\n4 - Modificare disciplina\n5 - Cauta disciplina\n6 - Filtrare discipline\n7 - Sortare discipline\n8 - Adauga in contract\n9 - Genereaza contract\n10 - Goleste Contract\n11 - Export la contract\n12 - Generare raport\n13 - Undo\n14 - Iesire\n";
		std::cin >> comandai;
		try {
			comanda = serv.validator.Validare_nr(comandai);
		}
		catch (const MyError& err) { std::cout << err.get_mesaj(); }
		if (comanda == 1) {
			Afisare_discipline();
		}
		else if (comanda == 2) {
			Adauga_disciplina();
		}
		else if (comanda == 3) {
			Sterge_disciplina();
		}
		else if (comanda == 4) {
			Modifica_disciplina();
		}
		else if (comanda == 5) {
			Cauta_disciplina();
		}
		else if (comanda == 6) {
			Filtrare();
		}
		else if (comanda == 7) {
			Sortare();
		}
		else if (comanda == 8) {
			Adauga_disciplina_ctr();
			std::cout << "Nr de discipline in contract: " << serv.contract.nr_dis()<< "\n";
		}
		else if (comanda == 9) {
			Genereaza();
			std::cout << "Nr de discipline in contract: " << serv.contract.nr_dis()<< "\n";
		}
		else if (comanda == 10) {
			Clear();
			std::cout << "Nr de discipline in contract: " << serv.contract.nr_dis()<< "\n";
		}
		else if (comanda == 11) {
			Export();
			std::cout << "Nr de discipline in contract: " << serv.contract.nr_dis()<< "\n";
		}
		else if (comanda == 12) {
			Raport();
		}
		else if (comanda == 13) {
			try {
				serv.undo();
			}
			catch (const MyError& err) { std::cout << err.get_mesaj(); }
		}
		else if (comanda == 14) {
			std::cout << "By By!!!";
			break;
		}
		else {
			std::cout << "Comanda invalida!\n";
		}
	}
}