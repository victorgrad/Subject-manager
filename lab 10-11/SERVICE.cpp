#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#include <fstream>
#include <map>
#include "serv.h"
#include "dom.h"

Validator::Validator() noexcept {
}

Service::Service(Repo& repo, const Validator& val, Contract& contract) noexcept :repo{ repo }, validator{ val }, contract{contract}{
}

int Validator::Validare_nr(const std::string& numar) const{
	int nr;
	nr = atoi(numar.c_str());
	if (nr != 0 || numar == "0") {
		return nr;
	}
	else {
		MyError er{ "Date invalide!!!\n" };
		throw(er);
	}
}

void Validator::Validare_disc(const Disciplina& disc) const{
	if (disc.get_id() < 0 || disc.get_id() > 9999) {
		MyError er{ "Id invalid\n" };
		throw(er);
	}
	if (disc.get_ore() < 0 || disc.get_ore() > 168) {
		MyError er{ "Ore invalide\n" };
		throw(er);
	}
	if (disc.get_cadru() == "") {
		MyError er{ "Cadru invalid\n" };
		throw(er);
	}
	if (disc.get_nume() == "") {
		MyError er{ "Nume invalid\n" };
		throw(er);
	}
	if (disc.get_tip() == "") {
		MyError er{ "Tip invalid\n" };
		throw(er);
	}
}

void Service::Add_dis(const int& id, const std::string& nume, const int& ore, const std::string& tip, const std::string& cadru){
	Disciplina disc{ id,nume,ore,tip,cadru };
	validator.Validare_disc(disc);
	repo.Add(disc);
	undoList.push_back(new UndoAdauga{ repo, disc });
}

void Service::Del_dis(const int& id){
	Disciplina disc;
	std::vector<Disciplina> discipline = repo.get_all();
	for (const Disciplina& dis : discipline) {
		if (dis.get_id() == id) {
			disc=dis ;
			break;
		}
	}
	if(disc.get_id()!=-1)
		undoList.push_back(new UndoSterge{ repo, disc });
	repo.Del(id);
}

void Service::Mod_dis(const int& id, const std::string& nume, const int& ore, const std::string& tip, const std::string& cadru){
	Disciplina disc{ id,nume,ore,tip,cadru };
	std::vector<Disciplina> discipline = repo.get_all();
	validator.Validare_disc(disc);
	Disciplina disci;
	for (const Disciplina& dis : discipline) {
		if (dis.get_id() == id) {
			disci = dis;
			break;
		}
	}
	if (disci.get_id() != -1)
		undoList.push_back(new UndoModifica{ repo, disci });
	repo.Mod(disc);
}

const std::vector<Disciplina> Service::Caut_dis(int idi) const{
	std::vector<Disciplina> discipline = repo.get_all();
	std::vector<Disciplina> lista(discipline.size());
	auto it = std::copy_if(discipline.begin(), discipline.end(), lista.begin(), [idi](const Disciplina& dis) {return dis.get_id() == idi; });
	lista.resize(std::distance(lista.begin(), it));
	return lista;
}

const std::vector<Disciplina> Service::Filtr_ore(int ore) const {
	std::vector<Disciplina> discipline = repo.get_all();
	std::vector<Disciplina> lista(discipline.size());
	auto it = std::copy_if(discipline.begin(), discipline.end(), lista.begin(), [ore](const Disciplina& dis) {return dis.get_ore() == ore; });
	lista.resize(std::distance(lista.begin(), it));
	return lista;
}

const std::vector<Disciplina> Service::Filtr_cadru(std::string cadru) const {
	std::vector<Disciplina> discipline = repo.get_all();
	std::vector<Disciplina> lista(discipline.size());
	auto it = std::copy_if(discipline.begin(), discipline.end(), lista.begin(), [cadru](const Disciplina& dis) {return dis.get_cadru() == cadru; });
	lista.resize(std::distance(lista.begin(), it));
	return lista;
}
/*
bool cmp_ore(const Disciplina& dis1, const Disciplina& dis2) {
	if (dis1.get_ore() > dis2.get_ore())
		return true;
	return false;
}

bool cmp_nume(const Disciplina& dis1, const Disciplina& dis2) {
	if (dis1.get_nume() > dis2.get_nume())
		return true;
	return false;
}

bool cmp_else(const Disciplina& dis1, const Disciplina& dis2) {
	if (dis1.get_cadru() > dis2.get_cadru())
		return true;
	else if (dis1.get_cadru() == dis2.get_cadru() && dis1.get_tip() > dis2.get_tip())
		return true;
	return false;
}

void Service::Sort(std::vector<Disciplina>& vec, bool func(const Disciplina& dis1, const Disciplina& dis2)) const {
	int i=0, j=0;
	bool sorted = false;
	while (sorted == false) {
		sorted = true;
		for (i = 0; i < vec.size() - 1; i++)
		{
			for (j = i+1; j < vec.size(); j++)
			{
				if (func(vec[i], vec[j]))
				{
					Disciplina aux = vec[i];
					vec[i] = vec[j];
					vec[j] = aux;
					sorted = false;
				}
			}
		}
	}
}
*/
const std::vector<Disciplina> Service::Sort_ore() const {
	std::vector<Disciplina> lista = repo.get_all();
	std::sort(lista.begin(), lista.end(), [](const Disciplina& dis1, const Disciplina& dis2) {return dis1.get_ore() < dis2.get_ore(); });
	return lista;
}

const std::vector<Disciplina> Service::Sort_nume() const {
	std::vector<Disciplina> lista = repo.get_all();
	std::sort(lista.begin(), lista.end(), [](const Disciplina& dis1, const Disciplina& dis2) {return dis1.get_nume().compare(dis2.get_nume())<0; });
	return lista;
}
const std::vector<Disciplina> Service::Sort_else() const {
	std::vector<Disciplina> lista = repo.get_all();
	std::sort(lista.begin(), lista.end(), [](const Disciplina& dis1, const Disciplina& dis2) {
	if (dis1.get_cadru().compare(dis2.get_cadru())<0)
		return true;
	else if (dis1.get_cadru().compare(dis2.get_cadru())==0 && dis1.get_tip().compare(dis2.get_tip())<0)
		return true;
	return false; });
	return lista;
}

void Contract::goleste() noexcept {
	while (discipline.size() > 0)
		discipline.pop_back();
	notify();
}

void Contract::adauga(const Disciplina& dis) {
	discipline.push_back(dis);
	notify();
}

const bool Contract::contine(int id) noexcept {
	for (const Disciplina& dis : discipline) {
		if (dis.get_id() == id)
			return true;
	}
	return false;
}


void Service::genereaza(int nr) const{
	std::vector<Disciplina> discipline = repo.get_all();
	if (contract.nr_dis()==0) {
		if (nr <= repo.Nr_elemente()) {
			srand((unsigned int)time(0));
			int nr_adaugate = 0;
			while (nr_adaugate < nr) {
				const int nr_rand = rand() % repo.Nr_elemente();
				if (!contract.contine(discipline[nr_rand].get_id())) {
					contract.adauga(discipline[nr_rand]);
					nr_adaugate++;
				}
			}
		}
		else {
			MyError er{ "Nu se pot genera mai multe discipline decat sunt deja in repo\n" };
			throw(er);
		}
	}
	else {
		MyError er{ "Contractul trebuie sa fie gol\n" };
		throw(er);
	}
}

void Service::adauga_ctr(const std::string& nume) const{
	std::vector<Disciplina> discipline = repo.get_all();
	int gasit = 0;
	for (const Disciplina& dis : discipline) {
		if (dis.get_nume().compare(nume) == 0)
			if (!contract.contine(dis.get_id())) {
				contract.adauga(dis);
				gasit = 1;
			}	
	}
	if (gasit == 0) {
		MyError er{ "A aparut o eroare\n" };
		throw(er);
	}
}


void Contract::export_ctr(const std::string& nume_fisier) const {
	std::ofstream out;
	out.open(nume_fisier,std::ofstream::trunc);
	out << "<!DOCTYPE html>\n<html>\n<body>\n\n";
	for (const Disciplina& dis : discipline) {
		out<<"<p>"<< "|| ID: " << dis.get_id() << " || Nume: " << dis.get_nume() << " || Ore: " << dis.get_ore() << " || Tip: " << dis.get_tip() << " || Cadru: " << dis.get_cadru() << " ||</p>\n";
	}
	out<< "\n</body>\n</html>\n";
	out.close();
}


const int Contract::nr_dis() const noexcept {
	return static_cast<int>(discipline.size());
}

const std::map<std::string, DTO> Service::genereaza_rap() const {
	std::map<std::string, DTO> dictionar;
	std::map<std::string, DTO>::iterator itr;
	std::vector<Disciplina> discipline = repo.get_all();
	for (const Disciplina& dis : discipline) {
		itr = dictionar.find(dis.get_tip());
		if (itr != dictionar.end()) {
			itr->second.set_count(itr->second.get_count() + 1);
		}
		else {//daca nu e in dict
			DTO aux{ dis.get_tip(),1 };
			dictionar.insert(std::pair<std::string, DTO>(dis.get_tip(), aux));
		}
	}
	return dictionar;
}

void Service::undo() {
	if (undoList.empty()) {
		MyError err{ "Nu mai exista operatii!!\n" };
		throw(err);
	}
	ActiuneUndo* act = undoList.back();
	act->doUndo();
	undoList.pop_back();
	delete act;
}

Service::~Service() {
	for (auto act : undoList) {
		delete act;
	}
}