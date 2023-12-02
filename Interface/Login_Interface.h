#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Login_Interface.h"

#include "Lobby_Interface.h"
class Login_Interface : public QMainWindow
{
    Q_OBJECT

public:
    Login_Interface(QWidget *parent = nullptr);
    ~Login_Interface();
public slots:
    void on_Loggin_clicked();
    void on_Register_clicked();
private:
    Ui::Guesser_InterfaceClass ui;
    Lobby_Interface* Lobby;
};
