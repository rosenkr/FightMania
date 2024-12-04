#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include <memory>
#include "Ichi/Scene/scene.h"

namespace ichi::scene::sceneManager
{
    bool addScene(int key, std::shared_ptr<Scene> scene);
    void removeScene(int key);
    void setActiveScene(int key);
    void draw();
    void update();
}
#endif