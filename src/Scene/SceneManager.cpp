#include "Scene/SceneManager.h"

#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Core/GameObject.h"

/*#include "Rendering/CameraComponent.h"
#include "Rendering/LightComponent.h"
#include "Rendering/MeshComponent.h"
#include "Physics/CharacterControllerComponent.h"
#include "Physics/RigidBodyComponent.h"
#include "Logic/WeaponComponent.h"*/

SceneManager *SceneManager::Instance = NULL;

SceneManager::SceneManager()
{
    Instance = this;

    mCurrentScene = new Scene;
    mScenes.push_back(mCurrentScene);

    /*registerComponentCreationFunction("MeshComponent", MeshComponent::createComponent);
    registerComponentCreationFunction("LightComponent", LightComponent::createComponent);
    registerComponentCreationFunction("CameraComponent", CameraComponent::createComponent);
    registerComponentCreationFunction("CharacterControllerComponent", CharacterControllerComponent::createComponent);
    registerComponentCreationFunction("RigidBodyComponent", RigidBodyComponent::createComponent);
    registerComponentCreationFunction("WeaponComponent", WeaponComponent::createComponent);*/
}

SceneManager::~SceneManager()
{
    for (unsigned int s = 0; s < mScenes.size(); s++)
        delete mScenes[s];
}

bool SceneManager::update(float deltaTime)
{
    return mCurrentScene->update(deltaTime);
}

GameObject *SceneManager::createGameObject()
{
    GameObject *object = new GameObject;
    addGameObject(object);
    return object;
}

void SceneManager::registerComponentCreationFunction(std::string name, ComponentCreationFunction funcPointer)
{
    mComponentCreationFunctionNames.push_back(name);
    mComponentCreationFunctions.push_back(funcPointer);
}

void SceneManager::removeComponentCreationFunction(std::string name)
{
    for (unsigned int f = 0; f < mComponentCreationFunctions.size(); f++)
    {
        if (name == mComponentCreationFunctionNames[f])
        {
            mComponentCreationFunctions.erase(mComponentCreationFunctions.begin()+f);
            //mComponentCreationFunctionNames.erase(f);
            return;
        }
    }
}

ComponentCreationFunction SceneManager::getComponentCreationFunction(std::string name)
{
    for (unsigned int f = 0; f < mComponentCreationFunctions.size(); f++)
    {
        if (name == mComponentCreationFunctionNames[f])
            return mComponentCreationFunctions[f];
    }

    return NULL;
}