#pragma once
//#ifndef REPO_H
//#define REPO_H
#include <iostream>
#include "dom.h"
#include <vector>
#include <map>
/*
* clasa repository-ului
*/

class Repo
{
public:
	virtual ~Repo() = default;

	virtual void Add(const Disciplina& disc) = 0;

	virtual void Del(const int& id) = 0;

	virtual void Mod(const Disciplina& disc) = 0;

	virtual int Nr_elemente() const = 0;

	virtual std::vector<Disciplina> get_all()	=	0;

	friend class Usi;
	friend class GUI;
	friend class Service;
};


class Repository:public Repo
{
public:

	/*
	* Constructor pentru repo
	*/
	Repository() noexcept;

	/*
	* Functia add adauga disciplina disc in vectorul de discipline
	* const Disciplina& disc - referinta constanta la o disciplina de adaugat
	* Pre - Disciplina valida
	* Post - Disciplina a fost adaugata
	*/
	virtual void Add(const Disciplina& disc) override;

	/*
	* Sterge disciplina cu id-ul id de tip int
	* arunca eroare in cazul in care nu exista id-ul
	*/
	virtual void Del(const int& id) override;

	/*
	* Functia Mod modifica disciplina cu id-ul disciplinei disc in vectorul de discipline
	* const Disciplina& disc - referinta constanta la o disciplina de adaugat
	* Pre - Disciplina valida
	* Post - Disciplina a fost modificata
	*/
	virtual void Mod(const Disciplina& disc) override;

	/*
	* Returneaza numarul elementelor din repo
	*/
	int Nr_elemente() const override{
		return static_cast<int>(discipline.size());
	}

	/*
	* Returneaza o referinta la vectorul dinamic de discipline din repo
	*/
	std::vector<Disciplina> get_all() override;


	friend class Usi;
	friend class Service;
	friend class GUI;

	virtual ~Repository() = default;


protected:
	std::vector<Disciplina> discipline;
};


class RepositoryF :public Repository {
private:
	void storeToFile() const;
	void loadFromFile();
	std::string filename;
public:

	RepositoryF(std::string filename) :Repository(), filename{ filename }{
		loadFromFile();
	}


	void Add(const Disciplina& disc) override {
		Repository::Add(disc);
		storeToFile();
	}

	void Del(const int& id) override {
		Repository::Del(id);
		storeToFile();
	}

	void Mod(const Disciplina& disc) override {
		Repository::Mod(disc);
		storeToFile();
	 }
};

class RepoLab:public Repo
{
public:
	RepoLab(const float& sansa):sansa{sansa} {}
	virtual void Add(const Disciplina& disc) override {
		const double r = ((double)rand() / (RAND_MAX));
		if (r < sansa) {
			MyError err{ "Nu ai nimerit bine\n" };
			throw(err);
		}
		std::map<int, Disciplina>::iterator itr;
		itr = discipline.find(disc.get_id());
		if (itr != discipline.end()) {
			MyError er{ "ID existent\n" };
			throw(er);
		}
		discipline.insert(std::pair<int, Disciplina>(disc.get_id(), disc));
	}

	virtual void Del(const int& id) override {
		const double r = ((double)rand() / (RAND_MAX));
		if (r < sansa) {
			MyError err{ "Nu ai nimerit bine\n" };
			throw(err);
		}
		std::map<int, Disciplina>::iterator itr;
		itr = discipline.find(id);
		if (itr == discipline.end()) {
			MyError er{ "ID inexistent\n" };
			throw(er);
		}
		discipline.erase(id);
	}

	virtual void Mod(const Disciplina& disc) override {
		const double r = ((double)rand() / (RAND_MAX));
		if (r < sansa) {
			MyError err{ "Nu ai nimerit bine\n" };
			throw(err);
		}
		std::map<int, Disciplina>::iterator itr;
		itr = discipline.find(disc.get_id());
		if (itr == discipline.end()) {
			MyError er{ "ID inexistent\n" };
			throw(er);
		}
		else {
			itr->second.set_ore(disc.get_ore());
			itr->second.set_nume(disc.get_nume());
			itr->second.set_tip(disc.get_tip());
			itr->second.set_cadru(disc.get_cadru());
		}
	}

	virtual int Nr_elemente() const override {
		const double r = ((double)rand() / (RAND_MAX));
		if (r < sansa) {
			MyError err{ "Nu ai nimerit bine\n" };
			throw(err);
		}
		return static_cast<int>(discipline.size());
	}

	virtual std::vector<Disciplina> get_all() override {
		std::vector<Disciplina> rez;
		std::map<int, Disciplina>::iterator itr;
		for (itr = discipline.begin(); itr != discipline.end(); itr++) {
			rez.push_back(itr->second);
		}
		return rez;
	}

private:
	double sansa;
	std::map<int, Disciplina> discipline;
};
//#endif // !REPO_H
