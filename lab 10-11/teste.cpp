#include<assert.h>
#include<vector>
#include<fstream>
#include <iostream>
#include <map>
#include "dom.h"
#include "repo.h"
#include "serv.h"
#include "ui.h"
#include "teste.h"

class aux :public Observer
{
public:
	int& nr;
	Service& service;
	aux(int& nr,Service& serv) :nr{ nr }, service{ serv } {
		service.contract.addObserver(this);
	}
	~aux() {
		service.contract.removeObserver(this);
	}

private:
	void update() override {
		nr = 1;
	}
};

void test_repoLab() {
	RepoLab repo{ 0 };
	Disciplina dis{ 1,"numee",3,"tipp","cadru" };
	Disciplina dis1{ 2,"numee",3,"tipp","cadru" };
	repo.Add(dis);
	repo.Add(dis1);
	assert(repo.Nr_elemente() == 2);

	try {
		repo.Add(dis);
		assert(1 == 0);
	}
	catch (const MyError& err) { std::string msj = err.get_mesaj(); }

	RepoLab repof{ 1 };
	try {
		repof.Add(dis);
		assert(1 == 0);
	}
	catch (const MyError& err) { std::string msj = err.get_mesaj(); }
	try {
		repof.Del(1);
		assert(1 == 0);
	}
	catch (const MyError& err) { std::string msj = err.get_mesaj(); }
	try {
		repof.Mod(dis);
		assert(1 == 0);
	}
	catch (const MyError& err) { std::string msj = err.get_mesaj(); }
	int wow;
	try {
		wow = repof.Nr_elemente();
		assert(1 == 0);
	}
	catch (const MyError& err) { std::string msj = err.get_mesaj(); }

	repo.Del(2);
	std::vector<Disciplina> rez = repo.get_all();
	assert(rez[0].get_id() == 1);
	Disciplina dis2{ 1,"1",1,"1","1" };
	repo.Mod(dis2);
	std::vector<Disciplina> rez2 = repo.get_all();
	assert(rez2[0].get_id() == 1);
	assert(rez2[0].get_ore()==1);

	try {
		repo.Del(5);
		assert(1 == 0);
	}
	catch (const MyError& err) { std::string msj = err.get_mesaj(); }
	Disciplina dis3{ 4,"1",1,"1","1" };
	try {
		repo.Mod(dis3);
		assert(1 == 0);
	}
	catch (const MyError& err) { std::string msj = err.get_mesaj(); }
}

void test_add() {
	Repository repo;
	Validator const validator;
	Contract contract;
	Service serv{ repo ,validator,contract };
	Disciplina dis{ 1,"numee",3,"tipp","cadru" };
	repo.Add(dis);
	serv.Add_dis(2, "nume", 2, "tip", "cadru");
	assert(repo.Nr_elemente() == 2);
	try {
		Disciplina dis2{ 1,"numee",3,"tipp","cadru" };
		repo.Add(dis2);
		assert(1 == 0);
	}
	catch (const MyError& err) { std::string msj = err.get_mesaj(); }
}

void test_val() {
	Validator const validator;

	Disciplina dis{ -1,"numee",3,"tipp","cadru" };
	try {
		validator.Validare_disc(dis);
		assert(1 == 0);
	}
	catch (const MyError& err) { std::string msj = err.get_mesaj(); }

	Disciplina dis2{ 1,"numee",1233,"tipp","cadru" };
	try {
		validator.Validare_disc(dis2);
		assert(1 == 0);
	}
	catch (const MyError& err) { std::string msj = err.get_mesaj(); }

	Disciplina dis3{ 1,"",13,"tipp","cadru" };
	try {
		validator.Validare_disc(dis3);
		assert(1 == 0);
	}
	catch (const MyError& err) { std::string msj = err.get_mesaj(); }

	Disciplina dis4{ 1,"fffr",13,"","cadru" };
	try {
		validator.Validare_disc(dis4);
		assert(1 == 0);
	}
	catch (const MyError& err) { std::string msj = err.get_mesaj(); }

	Disciplina dis5{ 1,"fffr",13,"dwad","" };
	try {
		validator.Validare_disc(dis5);
		assert(1 == 0);
	}
	catch (const MyError& err) { std::string msj = err.get_mesaj(); }

	Disciplina dis6{ 1,"numee",3,"tipp","cadru" };
	validator.Validare_disc(dis6);

	std::string numar1{ "23" };
	int const nur = validator.Validare_nr(numar1);
	assert(nur == 23);

	try {
		std::string numar2{ "aa" };
		int const nre = validator.Validare_nr(numar2);
		assert(1 == 0);
	}
	catch (const MyError& err) { std::string msj = err.get_mesaj(); }
}


void test_del() {
	Repository repo;
	const Validator validator;
	Contract contract;
	Service serv{ repo ,validator,contract };
	Disciplina dis{ 1,"numee",3,"tipp","cadru" };
	repo.Add(dis);
	serv.Add_dis(2, "nume", 2, "tip", "cadru");
	assert(repo.Nr_elemente() == 2);
	serv.Del_dis(1);
	assert(repo.Nr_elemente() == 1);
	try {
		repo.Del(1);
		assert(1 == 0);
	}
	catch (const MyError& err) { std::string msj = err.get_mesaj(); }

}

void test_mod() {
	Repository repo;
	const Validator validator;
	Contract contract;
	Service serv{ repo ,validator,contract };
	Disciplina dis{ 1,"numee",3,"tipp","cadru" };
	repo.Add(dis);
	std::vector<Disciplina> disciplin = repo.get_all();
	assert(disciplin[0].get_id() == 1);
	assert(disciplin[0].get_nume() == "numee");
	assert(disciplin[0].get_ore() == 3);
	assert(disciplin[0].get_tip() == "tipp");
	assert(disciplin[0].get_cadru() == "cadru");
	serv.Mod_dis(1, "wo", 4, "bu", "a");
	std::vector<Disciplina> discipline = repo.get_all();
	assert(discipline[0].get_id() == 1);
	assert(discipline[0].get_nume() == "wo");
	assert(discipline[0].get_ore() == 4);
	assert(discipline[0].get_tip() == "bu");
	assert(discipline[0].get_cadru() == "a");
	try {
		serv.Mod_dis(2, "wo", 4, "bu", "a");
		assert(1 == 0);
	}
	catch (const MyError& err) { std::string msj = err.get_mesaj(); }


}

void test_cauta() {
	Repository repo;
	Validator const validator;
	Contract contract;
	Service serv{ repo ,validator,contract };
	serv.Add_dis(1, "a", 2, "aa", "aa");
	serv.Add_dis(2, "c", 3, "bb", "bb");
	serv.Add_dis(3, "b", 3, "cc", "aa");
	serv.Add_dis(4, "d", 2, "dd", "cc");
	std::vector<Disciplina> lista = serv.Caut_dis(2);
	assert(lista.size() == 1);
	assert(lista[0].get_id() == 2);
	assert(lista[0].get_nume() == "c");
	assert(lista[0].get_ore() == 3);
	assert(lista[0].get_tip() == "bb");
	assert(lista[0].get_cadru() == "bb");

}

void test_filtr() {
	Repository repo;
	Validator const validator;
	Contract contract;
	Service serv{ repo ,validator,contract };
	serv.Add_dis(1, "a", 2, "aa", "aa");
	serv.Add_dis(2, "c", 3, "bb", "bb");
	serv.Add_dis(3, "b", 3, "cc", "aa");
	serv.Add_dis(4, "d", 2, "dd", "cc");
	std::vector<Disciplina> lista = serv.Filtr_ore(2);
	assert(lista.size() == 2);
	assert(lista[0].get_id() == 1);
	assert(lista[1].get_id() == 4);

	std::string cadru{ "aa" };
	std::vector<Disciplina> lista2 = serv.Filtr_cadru(cadru);
	assert(lista.size() == 2);
	assert(lista2[0].get_id() == 1);
	assert(lista2[1].get_id() == 3);
}

void test_sort() {
	Repository repo;
	Validator const validator;
	Contract contract;
	Service serv{ repo ,validator,contract };
	serv.Add_dis(1, "a", 2, "cc", "aa");
	serv.Add_dis(4, "d", 2, "dd", "cc");
	serv.Add_dis(2, "c", 3, "bb", "bb");
	serv.Add_dis(3, "b", 3, "aa", "aa");
	std::vector<Disciplina> lista1 = serv.Sort_ore();
	std::vector<Disciplina> lista2 = serv.Sort_nume();
	std::vector<Disciplina> lista3 = serv.Sort_else();
	assert(lista1[0].get_ore() == 2);
	assert(lista1[1].get_ore() == 2);
	assert(lista1[2].get_ore() == 3);
	assert(lista1[3].get_ore() == 3);

	assert(lista2[0].get_nume() == "a");
	assert(lista2[1].get_nume() == "b");
	assert(lista2[2].get_nume() == "c");
	assert(lista2[3].get_nume() == "d");

	assert(lista3[0].get_cadru() == "aa");
	assert(lista3[0].get_tip() == "aa");

	assert(lista3[1].get_cadru() == "aa");
	assert(lista3[1].get_tip() == "cc");

	assert(lista3[2].get_cadru() == "bb");
	assert(lista3[2].get_tip() == "bb");

	assert(lista3[3].get_cadru() == "cc");
	assert(lista3[3].get_tip() == "dd");

}

void test_contract() {
	Repository repo;
	Validator const validator;
	Contract contract;
	Service serv{ repo ,validator,contract };
	serv.Add_dis(1, "a", 2, "cc", "aa");
	serv.Add_dis(4, "d", 2, "dd", "cc");
	serv.Add_dis(2, "c", 3, "bb", "bb");
	serv.Add_dis(3, "b", 3, "aa", "aa");

	serv.adauga_ctr("d");
	assert(contract.nr_dis() == 1);
	try {
		serv.adauga_ctr("d");
	}
	catch (const MyError& err) { std::string msj = err.get_mesaj(); }
	contract.goleste();
	assert(contract.nr_dis() == 0);

	serv.genereaza(3);
	assert(contract.nr_dis() == 3);
	try {
		serv.genereaza(1);
		assert(1 == 0);
	}
	catch (const MyError& err) { std::string msj = err.get_mesaj(); }
	contract.goleste();

	try {
		serv.genereaza(5);
		assert(1 == 0);
	}
	catch (const MyError& err) { std::string msj = err.get_mesaj(); }
	contract.goleste();

	serv.adauga_ctr("a");
	serv.adauga_ctr("b");
	serv.adauga_ctr("c");
	serv.adauga_ctr("d");
	contract.export_ctr("test.htm");
	std::string string1, string2;
	int j = 0;
	std::ifstream in1("test.htm");
	std::ifstream in2("test-result.htm");
	while (!in1.eof())
	{
		std::getline(in1, string1);
		std::getline(in2, string2);
		j++;
		if (string1.compare(string2) != 0)
		{
			assert(1 == 0);
		}
	}
}

void test_lff() {
	RepositoryF repo{ "test_lff.txt" };
	assert(repo.Nr_elemente() == 2);
	std::vector<Disciplina> discipline = repo.get_all();
	assert(discipline[0].get_id() == 1);
	assert(discipline[0].get_nume() == "aa");
	assert(discipline[0].get_ore() == 22);
	assert(discipline[0].get_tip() == "c");
	assert(discipline[0].get_cadru() == "a");

	assert(discipline[1].get_id() == 2);
	assert(discipline[1].get_nume() == "c");
	assert(discipline[1].get_ore() == 3);
	assert(discipline[1].get_tip() == "bb");
	assert(discipline[1].get_cadru() == "bb");

}

void test_file() {
	test_lff();
	std::ofstream out("test.txt", std::ofstream::trunc);
	out.close();
	RepositoryF repo{"test.txt"};
	Validator const validator;
	Contract contract;
	Service serv{ repo ,validator,contract };
	serv.Add_dis(1, "a", 2, "cc", "aa");
	serv.Add_dis(2, "c", 3, "bb", "bb");
	serv.Add_dis(3, "b", 3, "aa", "aa");

	repo.Del(3);
	serv.Mod_dis(1, "aa", 22, "c", "a");

	std::ifstream in1("test.txt");
	std::ifstream in2("test-result.txt");
	std::string string1, string2;
	while (!in1.eof())
	{
		std::getline(in1, string1);
		std::getline(in2, string2);
		if (string1.compare(string2) != 0)
		{
			assert(1 == 0);
		}
	}
}

void test_rap() {
	Repository repo;
	Validator const validator;
	Contract contract;
	Service serv{ repo ,validator,contract };
	serv.Add_dis(1, "a", 2, "cc", "aa");
	serv.Add_dis(4, "d", 2, "dd", "cc");
	serv.Add_dis(2, "c", 3, "bb", "bb");
	serv.Add_dis(3, "b", 3, "aa", "aa");
	serv.Add_dis(5, "b", 3, "aa", "aa");
	serv.Add_dis(6, "b", 3, "aa", "aa");
	serv.Add_dis(7, "c", 3, "bb", "bb");

	std::map<std::string, DTO> dictionar;
	dictionar = serv.genereaza_rap();
	std::map<std::string, DTO>::iterator itr;

	assert(dictionar.find("ee") == dictionar.end());
	assert(dictionar.find("aa")->second.get_tip().compare("aa") == 0);
	assert(dictionar.find("aa")->second.get_count() == 3);
	assert(dictionar.find("bb")->second.get_count() == 2);
	assert(dictionar.find("cc")->second.get_count() == 1);
	assert(dictionar.find("dd")->second.get_count() == 1);
}
void test_undo() {
	Repository repo;
	Validator const validator;
	Contract contract;
	Service serv{ repo ,validator,contract };
	serv.Add_dis(1, "a", 2, "cc", "aa");
	std::vector<Disciplina> cautarez = serv.Caut_dis(1);
	assert(cautarez[0].get_ore() == 2);
	serv.Mod_dis(1, "1", 1, "1", "1");
	cautarez = serv.Caut_dis(1);
	assert(cautarez[0].get_ore() == 1);
	serv.undo();
	cautarez = serv.Caut_dis(1);
	assert(cautarez[0].get_ore() == 2);
	serv.undo();
	cautarez = serv.Caut_dis(1);
	assert(cautarez.size() == 0);
	serv.Add_dis(1, "a", 2, "cc", "aa");
	serv.Del_dis(1);
	cautarez = serv.Caut_dis(1);
	assert(cautarez.size() == 0);
	serv.undo();
	cautarez = serv.Caut_dis(1);
	assert(cautarez.size() == 1);
	serv.undo();
	try {
		serv.undo();
		assert(1 == 0);
	}
	catch (const MyError& err) { std::string msj = err.get_mesaj(); }
}

void test_obs() {
	Repository repo;
	Validator const validator;
	Contract contract;
	Service serv{ repo ,validator,contract };
	serv.Add_dis(1, "a", 2, "cc", "aa");
	serv.Add_dis(4, "d", 2, "dd", "cc");
	serv.Add_dis(2, "c", 3, "bb", "bb");
	serv.Add_dis(3, "b", 3, "aa", "aa");
	serv.Add_dis(5, "b", 3, "aa", "aa");
	serv.Add_dis(6, "b", 3, "aa", "aa");
	serv.Add_dis(7, "c", 3, "bb", "bb");
	int nr = 0;
	aux obj{nr,serv};
	serv.genereaza(3);
	assert(nr == 1);
	nr = 0;
	contract.goleste();
	assert(nr == 1);
}

void Run_tests() {
	test_add();
	test_val();
	test_del();
	test_mod();
	test_cauta();
	test_filtr();
	test_sort();
	test_contract();
	test_rap();
	test_file();
	test_undo();
	test_repoLab();
	test_obs();
}