/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** main
*/

#include <QtWidgets>
#include "Core.hpp"
#include "Window.hpp"
#include "Errors/Errors.hpp"
#include "Graphic/loginpage.hpp"

int main(int ac, char *av[])
{
    QApplication app(ac, av);
    babel::graphic::Window w;
    w.resize(640, 480);
    w.show();
    return app.exec();
}