#include "Ichi/Scene/sceneManager.h"

#include "Ichi/log.h"
#include "Ichi/Input/keyboard.h"

#include <memory>

namespace ichi::scene::sceneManager
{
    static std::map<int, std::shared_ptr<Scene>> scenes;
    static std::shared_ptr<Scene> activeScene;

    static std::shared_ptr<PopUpMenu> popUpMenu;

    // Succesfully adds a scene if the key does not already have an associated scene
    bool addScene(int key, std::shared_ptr<Scene> scene)
    {
        auto it = scenes.find(key);

        if (it != scenes.end()) // Key exists
        {
            ICHI_ERROR("Failed to insert scene with key {}, the key already has an associated scene", key);
            return false;
        }

        scenes[key] = scene;
        ICHI_INFO("Inserted scene at key {}", key);
        return true;
    }

    // Removes scene at key, logs whether a scene was actually removed if it existed or not
    void removeScene(int key)
    {
        if (scenes.erase(key) == 0)
        {
            ICHI_ERROR("There is no scene to remove with the key {}", key);
            return;
        }

        ICHI_INFO("Removed the scene with key {}", key);
    }

    // Sets active scene at key, logs whether this was succesful or not
    void setActiveScene(int key)
    {
        auto it = scenes.find(key);

        if (it == scenes.end())
        {
            ICHI_ERROR("There is no active scene associated with key {}", key);
            return;
        }

        activeScene = scenes[key];
        ICHI_INFO("Active scene was set with key {}", key);
    }

    void setPopUpMenu(std::shared_ptr<PopUpMenu> menu)
    {
        popUpMenu = menu;
    }

    Scene *getActiveScene()
    {
        return activeScene.get();
    }

    Scene *getScene(int key)
    {
        return scenes[key].get();
    }

    void update()
    {
        if (!activeScene)
        {
            ICHI_ERROR("No active scene to update");
            return;
        }

        if (input::Keyboard::keyIsPressed(input::Keyboard::Key::ICHIKEY_ESCAPE) && activeScene.get()->isPausable())
            activeScene.get()->setPaused(!activeScene.get()->isPaused());

        if (activeScene.get()->isPaused())
            popUpMenu.get()->update();
        else
            activeScene.get()->update();
    }

    void draw()
    {
        if (!activeScene)
        {
            ICHI_ERROR("No active scene to draw");
            return;
        }

        activeScene.get()->draw();

        if (activeScene.get()->isPaused())
            popUpMenu.get()->draw();
    }
}