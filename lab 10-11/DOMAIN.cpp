#include <iostream>
#include <exception>
#include "dom.h"

Disciplina::Disciplina(const int& id, const std::string& nume, const int& ore, const std::string& tip, const std::string& cadru) :id{ id }, nume{ nume }, ore{ ore }, tip{ tip }, cadru{ cadru } {
}

Disciplina::Disciplina(const Disciplina& ot) : id{ ot.id }, nume{ ot.nume }, ore{ ot.ore }, tip{ ot.tip }, cadru{ ot.cadru } {
	//std::cout << "S-a efectuat o copie!\n";
}

Disciplina::Disciplina() : id{ -1 }, nume{ "" }, ore{ -1 }, tip{ "" }, cadru{ "" } {
}

const std::string MyError::get_mesaj() const {
	return mesaj;
}

DTO::DTO(const std::string& tip, int nr) :tip{ tip }, count{ nr }{
}