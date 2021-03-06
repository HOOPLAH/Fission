#ifndef PROJECTILECOMPONENT_H
#define PROJECTILECOMPONENT_H

#include <LTBL/Light/EmissiveLight.h>
#include <Core/Component.h>

class ProjectileComponent : public Component
{
    public:
        ProjectileComponent(GameObject *object, std::string name, int dmg, float range, bool visual = true);
        virtual ~ProjectileComponent();

        virtual bool update(float dt);
        virtual void onRender(sf::RenderTarget *target, sf::RenderStates states);

        // Accessors
        int getDamage(){return mDamage;}

    protected:
        /// Amount of damage to deal on a collision
        int mDamage;

        /// Distance left to travel
        float mDistanceLeft;

        /// Whether or not to draw an effect
        bool mVisual;

        /// Emissive light for visual bullets
        ltbl::EmissiveLight *mEmissiveLight;

    private:
};

#endif // PROJECTILECOMPONENT_H
