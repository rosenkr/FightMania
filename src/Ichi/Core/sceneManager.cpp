#include "Ichi/Core/sceneManager.h"
#include "Ichi/log.h"
#include <memory>

// Currently just a namespace library, not a class
// Uses a vector but perhaps another data structure is more reasonable
namespace ichi::core::sceneManager {

    // Shared instead of unique because activeScene wants to point at a scene pointed to in scenes
    static std::vector<std::shared_ptr<Scene>> scenes; 
    static std::shared_ptr<Scene> activeScene;

    // adds existing scene at the given index
    // The implementation must create a new scene and make it uniquely pointed to, then pass ownership to the manager by mgr.addScene, which calls move().
    void addScene(std::shared_ptr<Scene> scene, size_t index) {
        if (scenes.size() <= index) { 
            scenes.resize(index + 1);
        } 
        scenes.insert(scenes.begin()+index, scene);
    }

    // If index is within the proper range and scenes isnt empty, remove scene at index
    void removeScene(size_t index) {
        if(index >= 0 && index < scenes.size()) {
            scenes.erase(scenes.begin()+index);
        } else {
            ICHI_ERROR("Index error when removing scene at index");
        }
    }

    // If index in valid range and there is a unique pointer to a scene at the index, set that scene as active one.
    // Before setting the new scene, transfer back the old scene to the components vector
    void setActiveScene(size_t index) {
        if(index >= 0 && index < scenes.size() && scenes.at(index) != nullptr) {
            activeScene = scenes.at(index); 
        } else {
            ICHI_ERROR("Index error when setting active scene to scene at index");
        }
    }

    // call update on (active scene OR all scenes?), which calls update on its components
    // because what if a scene is updated even when it isnt active? 
    //void update();

    // call draw on the active scene
    //void draw();

}