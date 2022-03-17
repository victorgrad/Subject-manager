#include "GUI.h"

GUI::GUI(Service& serv) :service{ serv } {
	serv.contract.addObserver(this);
	QHBoxLayout* WINDOW = new QHBoxLayout;
	this->setLayout(WINDOW);
	this->setPalette(paleta);
	//paleta.setColor(QPalette::, Qt::black);
	//this->setStyleSheet("background-color: magenta;");

	//partea din stanga
	QWidget* stanga = new QWidget;
	QVBoxLayout* stangal = new QVBoxLayout;
	stanga->setLayout(stangal);


	//lista_discipline = new QListWidget;
	//stangal->addWidget(lista_discipline);
	
	lista_discipline2 = new QTableWidget;
	stangal->addWidget(lista_discipline2);
	lista_discipline2->setColumnCount(5);
	lista_discipline2->setHorizontalHeaderLabels({ "ID", "Nume", "Ore", "Tip", "Cadru" });

	connect(lista_discipline2, &QTableWidget::itemSelectionChanged, [&]() {
		if (lista_discipline2->selectedItems().isEmpty()) {
			//txtid->setText("");
			txtid->setValue(0);
			txtcadru->setText("");
			txtnume->setText("");
			//txtore->setText("");
			txtore->setValue(0);
			txttip->setText("");
			return;
		}
		QTableWidgetItem* item = lista_discipline2->selectedItems().at(0);
		int linie = item->row();
		int id = lista_discipline2->item(linie, 0)->text().toInt();
		for (const Disciplina& dis : serv.repo.get_all()) {
			if (dis.get_id() == id) {
				//txtid->setText(lista_discipline2->item(linie, 0)->text());
				txtid->setValue(id);
				txtcadru->setText(dis.get_cadru().c_str());
				txtnume->setText(dis.get_nume().c_str());
				//txtore->setText(QString::number(dis.get_ore()));
				txtore->setValue(dis.get_ore());
				txttip->setText(dis.get_tip().c_str());
				break;
			}
		}
		});


	//lista_discipline2->show();
	QWidget* lista_opt1 = new QWidget;
	QHBoxLayout* lista_opt1l = new QHBoxLayout;
	lista_opt1->setLayout(lista_opt1l);
	sort_ore_button = new QPushButton("Sort Ore",this);
	sort_nume_button = new QPushButton("Sort Nume",this);
	sort_else_button = new QPushButton("Sort Cadru/Tip",this);

	lista_opt1l->addWidget(sort_ore_button);
	lista_opt1l->addWidget(sort_nume_button);
	lista_opt1l->addWidget(sort_else_button);

	connect(sort_ore_button, &QPushButton::released, this, &GUI::sort_ore);
	connect(sort_nume_button, &QPushButton::released, this, &GUI::sort_nume);
	connect(sort_else_button, &QPushButton::released, this, &GUI::sort_else);

	stangal->addWidget(lista_opt1);

	QWidget* lista_opt2 = new QWidget;
	QHBoxLayout* lista_opt2l = new QHBoxLayout;
	lista_opt2->setLayout(lista_opt2l);

	undo_button = new QPushButton{ "Undo" };
	lista_opt2l->addWidget(undo_button);
	connect(undo_button, &QPushButton::released, this, &GUI::undo);

	raport_button = new QPushButton{ "Generare Raport" };
	lista_opt2l->addWidget(raport_button);
	connect(raport_button, &QPushButton::released, this, &GUI::afiseaza_raport);
	stangal->addWidget(lista_opt2);

	QWidget* lista_opt3 = new QWidget;
	lista_opt3l = new QHBoxLayout;
	lista_opt3->setLayout(lista_opt3l);

	iesire_button = new QPushButton("Iesire",this);
	lista_opt3l->addWidget(iesire_button);
	connect(iesire_button, &QPushButton::released, this, &GUI::exit);
	lista_opt3l->addStretch();
	stangal->addWidget(lista_opt3);

	//partea din dreapta
	QWidget* dreapta = new QWidget;
	QVBoxLayout* dreaptal = new QVBoxLayout;
	dreapta->setLayout(dreaptal);
	//fromularul
	QWidget* formular = new QWidget;
	QFormLayout* formularl = new QFormLayout;
	formular->setLayout(formularl);
	QLabel* id = new QLabel("ID:");
	QLabel* nume = new QLabel("Nume:");
	QLabel* ore = new QLabel("Ore:");
	QLabel* tip = new QLabel("Tip:");
	QLabel* cadru = new QLabel("Cadru didactic:");

	//txtid = new QLineEdit;
	txtid = new QSpinBox;
	txtid->setMinimum(0);
	txtnume = new QLineEdit;
	//txtore = new QLineEdit;
	txtore = new QSlider(Qt::Horizontal);
	txtore->setMinimum(0);
	txtore->setMaximum(168);
	txttip = new QLineEdit;
	txtcadru = new QLineEdit;

	formularl->addRow(id, txtid);
	formularl->addRow(nume, txtnume);
	formularl->addRow(ore, txtore);
	formularl->addRow(tip, txttip);
	formularl->addRow(cadru, txtcadru);

	dreaptal->addWidget(formular);

	//opt dreapta

	QWidget* addmodstergefiltr = new QWidget;
	QHBoxLayout* addmodstergefiltrl = new QHBoxLayout;
	addmodstergefiltr->setLayout(addmodstergefiltrl);

	adauga_button = new QPushButton{ "Adauga" };
	addmodstergefiltrl->addWidget(adauga_button);
	connect(adauga_button, &QPushButton::released, this, &GUI::adauga);

	sterge_button = new QPushButton{ "Sterge" };
	addmodstergefiltrl->addWidget(sterge_button);
	connect(sterge_button, &QPushButton::released, this, &GUI::sterge);

	modifica_button = new QPushButton{ "Modifica" };
	addmodstergefiltrl->addWidget(modifica_button);
	connect(modifica_button, &QPushButton::released, this, &GUI::modifica);

	filtreaza_button = new QPushButton{ "Filtreaza" };
	addmodstergefiltrl->addWidget(filtreaza_button);
	connect(filtreaza_button, &QPushButton::released, this, &GUI::filtreaza);

	dreaptal->addWidget(addmodstergefiltr);
	
	//contract
	contract = new QWidget;
	QVBoxLayout* contractl = new QVBoxLayout;
	contract->setLayout(contractl);


	
	//formcontract
	QWidget* formularcontract = new QWidget;
	QFormLayout* formularcontractl = new QFormLayout;
	formularcontract->setLayout(formularcontractl);
	QLabel* idc = new QLabel("Nume Disciplina:");
	QLabel* nrdis = new QLabel("Numar Discipline:");

	txtidc = new QLineEdit;
	txtnrdis = new QLineEdit;

	formularcontractl->addRow(idc, txtidc);
	formularcontractl->addRow(nrdis, txtnrdis);
	
	contractl->addWidget(formularcontract);
	//optcontract
	QWidget* optcontract = new QWidget;
	QHBoxLayout* optcontractl = new QHBoxLayout;
	optcontract->setLayout(optcontractl);

	adauga_contract_button = new QPushButton{ "Adauga" };
	goleste_contract_button = new QPushButton{ "Goleste" };
	genereaza_contract_button = new QPushButton{ "Genereaza" };
	export_contract_button = new QPushButton{ "Export" };
	optcontractl->addWidget(adauga_contract_button);
	optcontractl->addWidget(goleste_contract_button);
	optcontractl->addWidget(genereaza_contract_button);
	optcontractl->addWidget(export_contract_button);
	connect(adauga_contract_button, &QPushButton::released, this, &GUI::adauga_contract);
	connect(goleste_contract_button, &QPushButton::released, this, &GUI::goleste_contract);
	connect(genereaza_contract_button, &QPushButton::released, this, &GUI::genereaza_contract);
	connect(export_contract_button, &QPushButton::released, this, &GUI::export_contract);

	contractl->addWidget(optcontract);
	
	dreaptal->addWidget(contract);

	QHBoxLayout* ctrbtnly=new QHBoxLayout;

	contract_button = new QPushButton{ "Contract" };
	ctrbtnly->addWidget(contract_button);
	connect(contract_button, &QPushButton::released, this, &GUI::afis_contract);

	contract_buttonro = new QPushButton{ "Contract Read only" };
	ctrbtnly->addWidget(contract_buttonro);
	connect(contract_buttonro, &QPushButton::released, this, &GUI::afis_contractro);

	dreaptal->addLayout(ctrbtnly);

	WINDOW->addWidget(stanga);
	WINDOW->addWidget(dreapta);
	this->setWindowTitle("Program cu discipline");
	this->setWindowIcon(QIcon("sad.png"));
}


void GUI::exit() {
	this->close();
}
/*
void GUI::afiseaza(std::vector<Disciplina> lista) {
	lista_discipline->clear();
	for (const Disciplina& dis : lista) {
		std::string stringul;
		stringul += "ID: ";
		stringul += std::to_string(dis.get_id())+" ";
		stringul += "Nume: ";
		stringul += dis.get_nume() + " ";
		stringul += "Ore: ";
		stringul += std::to_string(dis.get_ore()) + " ";
		stringul += "Tip: ";
		stringul += dis.get_tip() + " ";
		stringul += "Cadru: ";
		stringul += dis.get_cadru() + " ";
		//QListWidgetItem* listWidget = new QListWidgetItem(stringul.c_str());
		lista_discipline->addItem(stringul.c_str());
	}
}
*/
void GUI::afiseaza(std::vector<Disciplina> lista) {
	lista_discipline2->setRowCount(0);
	for (const Disciplina& dis : lista) {
		lista_discipline2->insertRow(lista_discipline2->rowCount());
		QTableWidgetItem* id = new QTableWidgetItem(QString::number(dis.get_id()));
		QTableWidgetItem* nume = new QTableWidgetItem(dis.get_nume().c_str());
		QTableWidgetItem* ore = new QTableWidgetItem(QString::number(dis.get_ore()));
		QTableWidgetItem* tip = new QTableWidgetItem(dis.get_tip().c_str());
		QTableWidgetItem* cadru = new QTableWidgetItem(dis.get_cadru().c_str());
		lista_discipline2->setItem(lista_discipline2->rowCount() - 1, 0, id);
		lista_discipline2->setItem(lista_discipline2->rowCount() - 1, 1, nume);
		lista_discipline2->setItem(lista_discipline2->rowCount() - 1, 2, ore);
		lista_discipline2->setItem(lista_discipline2->rowCount() - 1, 3, tip);
		lista_discipline2->setItem(lista_discipline2->rowCount() - 1, 4, cadru);
	}
}

void GUI::afiseaza_ore(std::vector<Disciplina> lista) {
	//lista_discipline2->setRowCount(0);
	for (const Disciplina& dis : lista) {
		for (int i = 0; i < lista_discipline2->rowCount(); i++) {
			std::string oretabel(lista_discipline2->item(i, 2)->text().toUtf8().constData());
			if (oretabel == std::to_string(dis.get_ore())) {
				lista_discipline2->item(i, 0)->setBackground(Qt::red);
				lista_discipline2->item(i, 1)->setBackground(Qt::red);
				lista_discipline2->item(i, 2)->setBackground(Qt::red);
				lista_discipline2->item(i, 3)->setBackground(Qt::red);
				lista_discipline2->item(i, 4)->setBackground(Qt::red);
			}
		}
	}
}

void GUI::afiseaza_repo() {
	try {
		std::vector<Disciplina> lista = service.repo.get_all();
		afiseaza(lista);
	}
	catch (const MyError& err) {
		Myerr->showMessage(err.get_mesaj().c_str());
	}
}

void GUI::Update() {
	//txtid->clear();
	txtid->setValue(0);
	//txtore->clear();
	txtore->setValue(0);
	txtnume->clear();
	txtcadru->clear();
	txttip->clear();
	txtnrdis->clear();
	txtidc->clear();
	update_contract_counter();
	afiseaza_repo();
}
void GUI::adauga() {
	int id, ore;
	std::string nume, tip, cadru,idi,orei;
	try {
		//idi = txtid->text().toLocal8Bit().constData();
		//orei = txtore->text().toLocal8Bit().constData();
		id = txtid->value();
		ore = txtore->value();
		nume = txtnume->text().toLocal8Bit().constData();
		cadru = txtcadru->text().toLocal8Bit().constData();
		tip = txttip->text().toLocal8Bit().constData();
		//id = service.validator.Validare_nr(idi);
		//ore = service.validator.Validare_nr(orei);
		service.Add_dis(id, nume, ore, tip, cadru);
	}
	catch (const MyError& err) {
		Myerr->showMessage(err.get_mesaj().c_str());
	}
	Update();
}

void GUI::sterge() {
	int id;
	std::string idi;
	try {
		idi = txtid->text().toLocal8Bit().constData();
		id = service.validator.Validare_nr(idi);
		service.Del_dis(id);
	}
	catch (const MyError& err) {
		Myerr->showMessage(err.get_mesaj().c_str());
	}
	Update();
}
void GUI::undo() {
	try {
		service.undo();
	}
	catch (const MyError& err) {
		Myerr->showMessage(err.get_mesaj().c_str());
	}
	Update();
}

void GUI::modifica() {
	int id, ore;
	std::string nume, tip, cadru, idi, orei;
	try {
		//idi = txtid->text().toLocal8Bit().constData();
		id = txtid->value();
		//orei = txtore->text().toLocal8Bit().constData();
		ore = txtore->value();
		nume = txtnume->text().toLocal8Bit().constData();
		cadru = txtcadru->text().toLocal8Bit().constData();
		tip = txttip->text().toLocal8Bit().constData();
		//id = service.validator.Validare_nr(idi);
		//ore = service.validator.Validare_nr(orei);
		service.Mod_dis(id, nume, ore, tip, cadru);
	}
	catch (const MyError& err) {
		Myerr->showMessage(err.get_mesaj().c_str());
	}
	Update();
}

void GUI::update_buton() {
	if (!este_update_buton) {
		update_button = new QPushButton{ "Update" };
		lista_opt3l->addWidget(update_button);
		connect(update_button, &QPushButton::released, this, &GUI::update_buton_click);
		este_update_buton = true;
	}
}

void GUI::update_buton_click() {
	lista_opt3l->removeWidget(update_button);
	delete update_button;
	update_button = nullptr;
	Update();
	este_update_buton = false;
}

void GUI::filtreaza() {
	int id, ore;
	std::string nume, tip, cadru, idi, orei;
	try {
		//idi = txtid->text().toLocal8Bit().constData();
		//orei = txtore->text().toLocal8Bit().constData();
		idi =std::to_string(txtid->value());
		orei =std::to_string(txtore->value());
		cadru = txtcadru->text().toLocal8Bit().constData();
		if ( orei == "0" && cadru == "") {
			id = service.validator.Validare_nr(idi);
			std::vector<Disciplina> lista = service.Caut_dis(id);
			afiseaza(lista);
			update_buton();
		}
		else if (idi == "0" && cadru == "") {
			ore = service.validator.Validare_nr(orei);
			std::vector<Disciplina> lista = service.Filtr_ore(ore);
			afiseaza_ore(lista);
			update_buton();
		}
		else if (cadru != "") {
			std::vector<Disciplina> lista = service.Filtr_cadru(cadru);
			afiseaza(lista);
			update_buton();
		}
	}
	catch (const MyError& err) {
		Myerr->showMessage(err.get_mesaj().c_str());
	}
}

void GUI::sort_ore() {
	std::vector<Disciplina> lista = service.Sort_ore();
	afiseaza(lista);
	update_buton();
}

void GUI::sort_nume() {
	std::vector<Disciplina> lista = service.Sort_nume();
	afiseaza(lista);
	update_buton();
}

void GUI::sort_else() {
	std::vector<Disciplina> lista = service.Sort_else();
	afiseaza(lista);
	update_buton();
}

void GUI::afiseaza_raport() {
	QListWidget* lista_raport = new QListWidget;
	lista_raport->setWindowTitle("Raport");
	std::map<std::string, DTO> dictionar;
	dictionar = service.genereaza_rap();
	std::map<std::string, DTO>::iterator itr;
	for (itr = dictionar.begin(); itr != dictionar.end(); itr++) {
		std::string stringul;
		stringul += "Tip: ";
		stringul += itr->first+" ";
		stringul += "Nr: ";
		stringul += std::to_string(itr->second.get_count());
		lista_raport->addItem(stringul.c_str());
	}
	lista_raport->show();
}

void GUI::update_contract_counter() {
	txtnrdis->setText(std::to_string(service.contract.nr_dis()).c_str());
}


void GUI::adauga_contract() {
	std::string nume;
	try {
		nume = txtidc->text().toLocal8Bit().constData();
		service.adauga_ctr(nume);
	}
	catch (const MyError& err) {
		Myerr->showMessage(err.get_mesaj().c_str());
	}
	Update();
}

void GUI::genereaza_contract() {
	std::string nri;
	int nr;
	try {
		nri = txtnrdis->text().toLocal8Bit().constData();
		nr = service.validator.Validare_nr(nri);
		service.genereaza(nr);
	}
	catch (const MyError& err) {
		Myerr->showMessage(err.get_mesaj().c_str());
	}
	Update();
}

void GUI::goleste_contract() {
	service.contract.goleste();
	Update();
}

void GUI::export_contract() {
	service.contract.export_ctr("exported.htm");
}

