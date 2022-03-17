#include <iostream>
#include <string>
#include <fstream>
#include "repo.h"

Repository::Repository()noexcept {
}

void Repository::Add(const Disciplina& disc) {
	for (const Disciplina& dis: discipline) {
		if (dis.get_id() == disc.get_id()) {
			MyError er{ "ID existent\n" };
			throw(er);
		}
	}
	Repository::discipline.push_back(disc);
}

void Repository::Del(const int& id) {
	int gasit=0,i=0;
	for (const Disciplina& dis : discipline) {
		if (dis.get_id() == id) {
			discipline.erase(discipline.begin()+i);
			gasit = 1;
			break;
		}
		i++;
	}
	if (gasit==0) {
		MyError er{ "ID inexistent\n" };
		throw(er);
	}
}

std::vector<Disciplina> Repository::get_all(){
	return discipline;
}


void Repository::Mod(const Disciplina& disc) {
	int gasit = 0;
	for (Disciplina& dis : discipline) {
		if (dis.get_id() == disc.get_id()) {
			gasit = 1;
			dis.set_ore(disc.get_ore());
			dis.set_nume(disc.get_nume());
			dis.set_tip(disc.get_tip());
			dis.set_cadru(disc.get_cadru());
		}
	}
	if (gasit == 0) {
		MyError er{ "ID inexistent\n" };
		throw(er);
	}
}

void RepositoryF::storeToFile() const{
	std::ofstream out(filename, std::ofstream::trunc);
	if (!out.is_open()) {
		MyError err{ "Eroare la deschidere fisier" };
		throw(err);
	}
	for (auto& dis : discipline) {
		out << dis.get_id() << "\n";
		out << dis.get_nume() << "\n";
		out << dis.get_ore() << "\n";
		out << dis.get_tip() << "\n";
		out << dis.get_cadru() << "\n";
	}
	out.close();
}

void RepositoryF::loadFromFile() {
	std::ifstream in(filename);
	if (!in.is_open()) {
		MyError err{ "Eroare la deschidere fisier" };
		throw(err);
	}
	while (!in.eof()) {
		int id,ore;
		std::string nume,tip,cadru;
		in >> id;
		in >> nume;
		if (in.eof()) break;
		in >> ore;
		in >> tip;
		if (in.eof()) break;
		in >> cadru;
		if (in.eof()) break;
		Disciplina dis{ id,nume,ore,tip,cadru };
		Repository::Add(dis);
	}
	in.close();
}