#pragma once
//#ifndef UI_H
//#define UI_H
#include "serv.h"

class Usi
{
public:

	/*
	* Constructor pentru UI
	*/
	Usi(Service& serv) noexcept;

	/*
	* Ruleaza aplicatia
	*/
	void run();

	/*
	* Citeste date de la tastatura si adauga disciplina in lista de discipline
	*/
	void Adauga_disciplina();

	/*
	* Afiseaza toate disciplinele din lista
	*/
	void Afisare_discipline() const;

	/*
	* Citeste de la tastatura un Id si sterge disciplina cu acel id
	*/
	void Sterge_disciplina();

	/*
	* Cisteste de la tastatura un id de disciplina si datele disciplinei cu care vor fi schimbate
	*/
	void Modifica_disciplina();

	/*
	* Citeste de la tastatura un id si afiseaza disciplina cu acel id
	*/
	void Cauta_disciplina() const;

	/*
	* Deschide meniul de filtrare
	*/
	void Filtrare() const;

	/*
	* Citeste de la tastatura un nr de ore si afiseaza disciplinele cu acel nr de ore
	*/
	void Filtrare_ore() const;

	/*
	* Citeste de la tastatura un cadru si afiseaza disciplinele cu acel cadru
	*/
	void Filtrare_cadru() const;

	/*
	* Deschide meniul de sortari
	*/
	void Sortare() const;
	
	/*
	* Afiseaza lista de discipline sortata dupa ore
	*/
	void Sortare_ore() const;

	/*
	* Afiseaza lista de discipline sortata dupa nume
	*/
	void Sortare_nume() const;

	/*
	* Afiseaza lista de discipline sortata dupa cadru si tip
	*/
	void Sortare_else() const;

	/*
	* Exporteaza datele din contact in fisierul dat de utilizator
	*/
	void Export() const;

	/*
	* Citeste un nume de disciplina de la tastatura si, daca exista,adauga disciplina in contract
	*/
	void Adauga_disciplina_ctr() const;

	/*
	* Elibereaza contractul de toate disciplinele
	*/
	void Clear() const;

	/*
	* Genereaza o lista aleatorie de discipline existente si le baga in contract
	*/
	void Genereaza() const;
 
	void Raport() const;

private:
	Service& serv;
};


//#endif // !UI_H
