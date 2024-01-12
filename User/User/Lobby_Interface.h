#pragma once

#include <QMainWindow>
#include "ui_Lobby_Interface.h"
#include "Guess_Game_Interface.h"
#include "Drawer_Game_Interface.h"

#include <cpr/cpr.h>
#include <crow.h>
#include <fstream>


#include <QApplication>
#include <QListView>
#include <QStandardItemModel>
#include <QStandardItem>

#include "Transition.h"


class Lobby_Interface : public QMainWindow
{
	Q_OBJECT

public:
	Lobby_Interface(QWidget* parent = nullptr);
	~Lobby_Interface();
	void setName(std::string name);
	std::string getName();

public slots:
	void on_start_game_clicked();

	void getPLayers();
	void openInterface();
	void verifyStarted();

private:
	Ui::Lobby_InterfaceClass ui;
	std::string name;
	QTimer checkTimer;
	int ok = 0;
	QTimer* runTime = new QTimer(this); 
};



