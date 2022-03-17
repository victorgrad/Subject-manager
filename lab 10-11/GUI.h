#pragma once
#include <qpushbutton.h>
#include "ui_lab1011.h"
#include "lab1011.h"
#include "serv.h"
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
#include <QtWidgets/qerrormessage.h>
#include <QtWidgets/qspinbox.h>
#include <QtWidgets/qslider.h>
#include <qpainter.h>
#include <qpolygon.h>
#include <map>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

class ContractWindow :public QWidget, public Observer
{
public:

    ContractWindow(Service& serv) :service{ serv } {
        QVBoxLayout* contractl = new QVBoxLayout;
        this->setLayout(contractl);

        //list contract

        lista_contract = new QListWidget;
        contractl->addWidget(lista_contract);
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
        connect(adauga_contract_button, &QPushButton::released, this, &ContractWindow::adauga_contract);
        connect(goleste_contract_button, &QPushButton::released, this, &ContractWindow::goleste_contract);
        connect(genereaza_contract_button, &QPushButton::released, this, &ContractWindow::genereaza_contract);
        connect(export_contract_button, &QPushButton::released, this, &ContractWindow::export_contract);

        contractl->addWidget(optcontract);
        update_contract_counter();
        service.contract.addObserver(this);
    }

    ~ContractWindow() {
        service.contract.removeObserver(this);
    }

private:

    QLineEdit* txtidc;
    QLineEdit* txtnrdis;
    QPushButton* adauga_contract_button;
    QPushButton* goleste_contract_button;
    QPushButton* export_contract_button;
    QPushButton* genereaza_contract_button;
    Service& service;
    QErrorMessage* Myerr = new QErrorMessage;
    QListWidget* lista_contract;

    void update() override {
        update_contract_counter();
    }

    void update_contract_counter() {
        txtnrdis->setText(std::to_string(service.contract.nr_dis()).c_str());
        update_contract();
    }

    void adauga_contract() {
        std::string nume;
        try {
            nume = txtidc->text().toLocal8Bit().constData();
            service.adauga_ctr(nume);
        }
        catch (const MyError& err) {
            Myerr->showMessage(err.get_mesaj().c_str());
        }
        update_contract_counter();
    }

    void genereaza_contract() {
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
        update_contract_counter();
    }

    void goleste_contract() {
        service.contract.goleste();
        update_contract_counter();
    }

    void export_contract() {
        service.contract.export_ctr("exported.htm");
    }


    void update_contract() {
        lista_contract->clear();
        for (const Disciplina& dis : service.contract.discipline) {
            std::string stringul;
            stringul += dis.get_nume();
            lista_contract->addItem(stringul.c_str());
        }
    }
};



class ContractReadOnlyGui :public QWidget, public Observer
{
    Q_OBJECT

public:

    ContractReadOnlyGui(Service& serv) :service{ serv } {
        service.contract.addObserver(this);
    }

    ~ContractReadOnlyGui() {
        service.contract.removeObserver(this);
    }

protected:
    Service& service;

    void paintEvent(QPaintEvent*) override {
        QPainter p{ this };
        srand(time(NULL));
        for (int i = 0; i < service.contract.discipline.size();i++) {
            int x = rand() % 500;
            int y = rand() % 400;
            p.drawImage(x, y, QImage("sad.png").scaled(50,50,Qt::KeepAspectRatio));
        }
    }

    void update() override {
        this->repaint();
    }
};



class GUI : public QWidget, public Observer
{
private:
    void afiseaza(std::vector<Disciplina> lista);
    void afiseaza_ore(std::vector<Disciplina> lista);
    void adauga();
    void sterge();
    void modifica();
    void afiseaza_repo();
    void exit();
    void undo();
    void filtreaza();
    void update_buton();
    void update_buton_click();
    void sort_ore();
    void sort_nume();
    void sort_else();
    void afiseaza_raport();
    
    void update_contract_counter();
    void adauga_contract();
    void genereaza_contract();
    void goleste_contract();
    void export_contract();
    //void update_contract();
    
    Service& service;
    void afis_contract() {
        ContractWindow* ctr = new ContractWindow{ service };
        ctr->show();
    }

    void afis_contractro() {
        ContractReadOnlyGui* ctrrd = new ContractReadOnlyGui{ service };
        ctrrd->show();
    }

    void update() override {
        this->Update();
    }


    bool este_update_buton = false;
    QErrorMessage* Myerr = new QErrorMessage;
    QPalette paleta;
    QHBoxLayout* lista_opt3l;
    QListWidget* lista_discipline;
    //QListWidget* lista_contract;
    QTableWidget* lista_discipline2;
    QWidget* contract;
    QSpinBox* txtid;
    //QLineEdit* txtid;
    QLineEdit* txtnume;
    QSlider* txtore;
    //QLineEdit* txtore;
    QLineEdit* txttip;
    QLineEdit* txtcadru;

    QLineEdit* txtidc;
    QLineEdit* txtnrdis;
    //buttons
    QPushButton* sort_ore_button;
    QPushButton* sort_nume_button;
    QPushButton* sort_else_button;
    QPushButton* iesire_button;
    QPushButton* adauga_button;
    QPushButton* sterge_button;
    QPushButton* undo_button;
    QPushButton* modifica_button;
    QPushButton* filtreaza_button;
    QPushButton* update_button;
    QPushButton* raport_button;
    QPushButton* adauga_contract_button;
    QPushButton* goleste_contract_button;
    QPushButton* export_contract_button;
    QPushButton* genereaza_contract_button;
    QPushButton* contract_button;
    QPushButton* contract_buttonro;

public:
    GUI(Service& serv);
    void Update();
};
