#ifndef MENU_H
#define MENU_H
#include "Ichi/Scene/scene.h"
#include <vector>
#include <memory>
#include "Ichi/UIComponents/uicomponent.h"
namespace ichi::scene
{

    class Menu : public Scene
    {
    public:
        Menu(std::vector<core::Component *> comps, std::vector<ichi::uicomponents::UIComponent *> uicomps) : Scene(comps), uiComponents(std::move(uicomps)) { pausable = false; }
        void draw() const override;
        void update() override;

    private:
        std::vector<ichi::uicomponents::UIComponent *> uiComponents;
    };
}

#endif