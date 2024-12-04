#include "Ichi/Scene/sceneManager.h"
#include "Ichi/log.h"
#include <memory>

namespace ichi::scene::sceneManager
{
    static std::map<int, std::shared_ptr<Scene>> scenes;
    static std::shared_ptr<Scene> activeScene;

    // Succesfully adds a scene if the key does not already have an associated scene
    bool addScene(int key, std::shared_ptr<Scene> scene)
    {
        auto it = scenes.find(key);
        if(it == scenes.end()) {
            scenes[key] = scene; 
            ICHI_INFO("Inserted scene at key {}", key);
            return true;
        } else {
            ICHI_ERROR("Failed to insert scene with key {}, the key already has an associated scene", key);
            return false;
        }
    }

    // Removes scene at key, logs whether a scene was actually removed if it existed or not
    void removeScene(int key)
    {
        if (scenes.erase(key) > 0) {
            ICHI_INFO("Removed the scene with key {}", key);
        } else {
            ICHI_ERROR("There is no scene to remove with the key {}", key);
        }
    }

    // Sets active scene at key, logs whether this was succesful or not
    void setActiveScene(int key)
    {
        auto it = scenes.find(key);
        if(it == scenes.end()){
            ICHI_ERROR("There is no active scene associated with key {}", key);
        } else {
            activeScene = scenes[key];
            ICHI_INFO("Active scene was set with key {}", key);
        }
    }

    Scene* getActiveScene() { 
        return activeScene.get(); 
    }

    Scene* getScene(int key){
        return scenes[key].get();
    }

    void update() {
        if (activeScene) {
            activeScene.get()->update(); 
        } else {
            ICHI_ERROR("No active scene to update");
        }
    }

    void draw() {
        if (activeScene) {
            activeScene.get()->draw(); 
        } else {
            ICHI_ERROR("No active scene to draw");
        }
    }
}