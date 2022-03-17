#include "lab1011.h"
#include "GUI.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qpushbutton.h>

#include <QtWidgets/qcombobox.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets\qformlayout.h>
#include <QtWidgets\qgridlayout.h>

#include <iostream>
#include <stdlib.h>
//#include <crtdbg.h>
#include "repo.h"
#include "serv.h"
#include "ui.h"
#include "teste.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	//try {
		Run_tests();
	//}
	//catch (const MyError& err) { std::cout << err.get_mesaj(); }

	Repository repo;
	//RepoLab repo{ 0.25 };
	//RepositoryF repo{ "fisier.txt" };

	const Validator validator;
	Contract contract;
	Service serv{ repo ,validator, contract };
	GUI interfata{serv};
    interfata.show();
	
	serv.Add_dis(1, "a", 2, "aa", "aa");
	serv.Add_dis(2, "c", 3, "bb", "bb");
	serv.Add_dis(3, "b", 3, "cc", "aa");
	serv.Add_dis(4, "d", 2, "dd", "cc");
	serv.Add_dis(5, "d", 2, "bb", "cc");

	serv.Add_dis(6, "d", 2, "bb", "cc");
	serv.Add_dis(7, "d", 2, "bb", "cc");
	serv.Add_dis(8, "d", 2, "bb", "cc");
	serv.Add_dis(9, "d", 2, "bb", "cc");
	serv.Add_dis(10, "d", 2, "bb", "cc");
	serv.Add_dis(11, "d", 2, "bb", "cc");
	serv.Add_dis(12, "d", 2, "bb", "cc");
	serv.Add_dis(13, "d", 2, "bb", "cc");
	serv.Add_dis(14, "d", 2, "bb", "cc");
	serv.Add_dis(15, "d", 2, "bb", "cc");
	
	interfata.Update();
	return a.exec();
}
