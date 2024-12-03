#ifndef MENU_H
#define MENU_H
#include "scene.h"
#include <vector>
#include <memory>
#include "Ichi/UIComponents/uicomponent.h"
namespace ichi::scene{

    // A menu is a type of Scene that is non-pausable and only holds subclasses of UIComponents
    class Menu : public Scene {
        public:
            Menu(std::vector<std::unique_ptr<ichi::uicomponents::UIComponent>>);
            void draw() const override {}
            void update() override {}

        private:
            std::vector<std::unique_ptr<ichi::uicomponents::UIComponent>> uiComponents;
    };
}

#endif