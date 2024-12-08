#include "Ichi/Scene/menu.h"
namespace ichi::scene
{
    void Menu::draw() const
    {
        for (auto c : components)
            c->draw();

        for (auto ui : uiComponents)
            ui->draw();
    }
    void Menu::update()
    {
        for (auto c : components)
            c->update();

        for (auto ui : uiComponents)
            ui->update();
    }
}