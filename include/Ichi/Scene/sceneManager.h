#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include <memory>
#include "Ichi/Scene/scene.h"
#include "Ichi/Scene/popUpMenu.h"

namespace ichi::scene::sceneManager
{
    void draw();
    void update();

    bool addScene(int key, std::shared_ptr<Scene> scene);
    void removeScene(int key);

    void setActiveScene(int key);
    void setPopUpMenu(std::shared_ptr<PopUpMenu>);

    void shutDown();

    Scene *getActiveScene();
    Scene *getScene(int key);
}
#endif