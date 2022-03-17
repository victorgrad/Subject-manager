#pragma once
//#ifndef SERV_H
//#define SERV_H
#include "repo.h"
#include <map>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qgroupbox.h>
#include <QtWidgets/qcombobox.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets\qformlayout.h>
#include <QtWidgets\qgridlayout.h>



/*
* Clasa validatorului
*/
class Validator
{
public:

	/*
	* Constructor pentru clasa validator
	*/
	Validator() noexcept;

	/*
	* Primeste o disciplina dis si arunca erori in cazul unor date invalide
	*/
	void Validare_disc(const Disciplina& disc) const;

	/*
	* Primeste un string si verifica daca este un numar
	* Daca este ii returneaza valoarea, atlfel ridica o eroare
	*/
	int Validare_nr(const std::string& numar) const;

};


class Observer {
public:
	virtual void update() = 0;
};

class Observable {
private:
	std::vector<Observer*> observers;
public:
	// Adauga un obiect de tip observer(care mosteneste observer) pentru a fi notificat
	// !!! TREBUIE APELATA IN CONSTRUCTORUL OBIECTULUI OBSERVER
	//obs - pointer spre obiect de tip Observer
	void addObserver(Observer* obs) {
		observers.push_back(obs);
	}
	// Sterge un observer pentru a nu a mai fi notificat(unlink)
	// 	   // !!! TREBUIE APELATA IN DECONSTRUCTORUL OBIECTULUI OBSERVERD
	//obs - pointer spre obiect de tip Observer
	void removeObserver(Observer* obs) {
		observers.erase(std::remove(begin(observers), end(observers), obs), observers.end());
	}

protected:
	// Functie care trimite un semnal/ alerteaza toti observerii obiectului observable
	void notify() {
		for (auto obs : observers) {
			obs->update();
		}
	}
};


class Contract: public Observable
{
public:
	/*
	* Goleste contractul de toate disciplinele
	*/
	void goleste() noexcept;

	/*
	* Adauga disciplina existenta in repo dupa nume dupa nume
	* nume - referinta la string
	* ridica eroare daca nu s-a gasit numele
	*/
	void adauga(const Disciplina& nume);

	/*
	* Populeaza fisierul introdus de utilizator cu disciplinele din contract
	* nume_fisier - referinta la string
	*/
	void export_ctr(const std::string& nume_fisier) const;

	/*
	* returneaza numarul de discipline din contract
	*/
	const int nr_dis() const noexcept;

	/*
	* returneaza true daca contractul contine o disciplina cu id-ul id, altfel returneaza false
	*/
	const bool contine(int id) noexcept;
	//friend class Service;
	friend class GUI;
	friend class ContractWindow;
	friend class ContractReadOnlyGui;
	friend class aux;

private:
	std::vector<Disciplina> discipline;
};

class ActiuneUndo
{
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga :public ActiuneUndo {
private:
	Disciplina disAdaugata;
	Repo& repo;
public:
	UndoAdauga(Repo& repo, const Disciplina& dis) :repo{ repo }, disAdaugata{ dis }{}

	void doUndo() override {
		repo.Del(disAdaugata.get_id());
	}
};

class UndoSterge :public ActiuneUndo {
private:
	Disciplina disStearsa;
	Repo& repo;
public:
	UndoSterge(Repo& repo, const Disciplina& dis) :repo{ repo }, disStearsa{ dis }{}

	void doUndo() override {
		repo.Add(disStearsa);
	}
};

class UndoModifica :public ActiuneUndo {
private:
	Disciplina disModificata;
	Repo& repo;
public:
	UndoModifica(Repo& repo, const Disciplina& dis) :repo{ repo }, disModificata{ dis }{}

	void doUndo() override {
		repo.Mod(disModificata);
	}
};

class Service
{
public:
	/*
	* Constructor Service care primeste un Repository repo si un Validator validator
	*/
	Service(Repo& repo, const Validator& val,Contract& contract) noexcept;
	~Service();
	/*
	* Functia Add_dis primeste date despre o disciplina, creeaza disciplina si verifica validitatea datelor
	* Pre - date de intrare disciplina
	* Post - adauga disciplina valida in repo
	*/
	void Add_dis(const int& id, const std::string& nume, const int& ore, const std::string& tip, const std::string& cadru);

	/*
	* Functia Del_dis primeste date despre o disciplina si apeleaza functia din repo coresp
	* Pre - id -id unei discipline int
	* Post - sterge disiciplina din repo
	*/
	void Del_dis(const int& id);


	/*
	* Functia Mod_dis primeste date despre o disciplina, creeaza disciplina si verifica validitatea datelor
	* Pre - date de intrare disciplina
	* Post - modifica disciplina valida in repo
	*/
	void Mod_dis(const int& id, const std::string& nume, const int& ore, const std::string& tip, const std::string& cadru);

	/*
	* Functia Caut_dis cauta disciplina cu id-ul id , o pune intr-un vector si returneaza acel vector
	* Pre - id de tip int
	* Post - lista cu disciplinele cu acel id(doar una)
	*/
	const std::vector<Disciplina> Caut_dis(int id) const;

	/*
	* Functia Filtr_ore cauta disciplinele cu nr de ore ore, le pune intr-un vector si returneaza acel vector
	* Pre - ore de tip int
	* Post - lista cu disciplinele cu acel nr de ore
	*/
	const std::vector<Disciplina> Filtr_ore(int ore) const;

	/*
	* Functia Filtr_cadru cauta disciplinele cu cadrul cadru, le pune intr-un vector si returneaza acel vector
	* Pre -
	* Post - lista cu disciplinele cu acel cadru
	*/
	const std::vector<Disciplina> Filtr_cadru(std::string cadru) const;

	/*
	* Functia Sort_ore preia disciplinele intr-un vector, le sorteaza dupa nr de ore si returneaza acel vector
	* Pre -
	* Post - lista cu disciplinele sortate dupa criteriu
	*/
	const std::vector<Disciplina> Sort_ore() const;

	/*
	* Functia Sort_nume preia disciplinele intr-un vector, le sorteaza dupa nume si returneaza acel vector
	* Pre -
	* Post - lista cu disciplinele sortate dupa criteriu
	*/
	const std::vector<Disciplina> Sort_nume() const;

	/*
	* Functia Sort_else preia disciplinele intr-un vector, le sorteaza dupa cadru si mai apoi dupa tip si returneaza acel vector
	* Pre -
	* Post - lista cu disciplinele sortate dupa criteriu
	*/
	const std::vector<Disciplina> Sort_else() const;

	/*
	* Functie de sortare care primeste o referinta la un vector dinamic si o functie de tip bool pe 2 discipline
	* Pre - vec -VectorDinamic<Disciplina> si func - bool ...(Disciplina d1, Disciplina d2)
	* Post - vec sortat dupa functia de comparare 
	*/
	void Sort(std::vector<Disciplina>& vec,bool func(const Disciplina& dis1, const Disciplina& dis2)) const;

	/*
	* Genereaza un contract aleator cu numarul de discipline introduse de utilizator
	* nr - int : numarul de discipline dorite in contract
	* ridica eroare daca nu sunt destule discipline existente pt a genera contractul
	*/
	void genereaza(int nr) const;

	/*
	* Adauga disciplina existenta in repo dupa nume dupa nume in contract
	* nume - referinta la string
	* ridica eroare daca nu s-a gasit numele
	*/
	void adauga_ctr(const std::string& nume) const;

	const std::map<std::string, DTO> genereaza_rap() const;

	/*
	* Reface ultima actiune(adaugare,stergere,modificare)
	*/
	void undo();

	friend class Usi;
	friend class GUI;
	friend class Contract;
	friend class ContractWindow;
	friend class ContractReadOnlyGui;
	friend class aux;

protected:
	Repo& repo;
	Validator const validator;
	Contract& contract;
	std::vector<ActiuneUndo*> undoList;
};
//#endif // !SERV_H
