#pragma once
//#ifndef DOM_H
//#define DOM_H
#include <string>

class Disciplina
{
public:
	/*
	* Constructor disciplina care primeste:
	* id - int : un id
	* nume - std::string : numele disciplinei
	* ore - int : numarul de ore pe saptamana
	* tip - std::string : tipul disciplinei
	* cadru - std::string : numele cadrului didactic care preda disciplina
	*/
	Disciplina(const int& id, const std::string& nume, const int& ore, const std::string& tip, const std::string& cadru);

	Disciplina(const Disciplina& ot);

	Disciplina();

	Disciplina& operator=(const Disciplina& ot) {
		id = ot.get_id();
		nume = ot.get_nume();
		ore = ot.get_ore();
		tip = ot.get_tip();
		cadru = ot.get_cadru();
		return *this;
	}

	int get_ore() const noexcept {
		return ore;
	}

	int get_id() const noexcept {
		return id;
	}

	std::string get_tip() const {
		return tip;
	}

	std::string get_nume() const {
		return nume;
	}

	std::string get_cadru() const {
		return cadru;
	}

	void set_ore(const int& orenou) noexcept{
		ore = orenou;
	}
	
	void set_tip(const std::string& tipnou) {
		tip = tipnou;
	}

	void set_nume(const std::string& numenou) {
		nume = numenou;
	}

	void set_cadru(const std::string& cadrunou) {
		cadru = cadrunou;
	}


private:
	std::string tip, nume, cadru;
	int ore, id;

};

class MyError {
public:
	MyError(const std::string& mesaj) :mesaj{ mesaj } {}
	const std::string get_mesaj() const;
private:
	std::string mesaj;
};

class DTO {
public:
	DTO();

	DTO(const std::string& tip, int count);

	std::string get_tip() {
		return tip;
	}
	int get_count() {
		return count;
	}

	void set_count(int nou) {
		count = nou;
	}
private:
	std::string tip;
	int count;
};
//#endif // !DOM_H
