#include "Ichi/Scene/menu.h"
namespace ichi::scene{
    Menu::Menu(std::vector<std::unique_ptr<ichi::uicomponents::UIComponent>> uiComponents = {}) : Scene(), uiComponents(std::move(uiComponents)) { 
        pausable = false;
    }

}