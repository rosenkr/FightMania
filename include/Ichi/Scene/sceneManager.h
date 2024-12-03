#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include <vector>
#include <memory>
#include "Ichi/Scene/scene.h"

namespace ichi::scene::sceneManager
{
    void addScene(std::shared_ptr<Scene> scene, size_t index);
    void removeScene(size_t index);
    void setActiveScene(size_t index);

    // void draw();
    // void update();

}
#endif