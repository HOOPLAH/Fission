#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Core/Component.h"

class SpriteComponent : public Component
{
    public:
        SpriteComponent(GameObject *object, std::string name, std::string imgPath, int frames = 1, int framesPerRow = 1);
        virtual ~SpriteComponent();

        virtual bool update(float dt);
        virtual void onRender(sf::RenderTarget *target, sf::RenderStates states = sf::RenderStates::Default);

        //accessors
        sf::Sprite *getSprite(){return mSprite;}

        //mutators
        void setFrames(int frames){mFrames = frames;}
        void setFramesPerRow(int frames){mFramesPerRow = frames;}
        void setAnimDelay(int delay){mAnimDelay = delay;}
        void setLoopAnim(bool loop){mLoopAnim = loop;}
        void setFrameLoop(int start, int end)
        {
            if (mStartFrame != start || mEndFrame != end) //make sure the frame loop is different before we reset
                mCurFrame=start;
            mStartFrame=start;mEndFrame=end;
        }
        bool getAnimFinished(){return !mLoopAnim&&mCurFrame==mEndFrame;}

    protected:
        sf::Sprite *mSprite;

        int mFrames;                            //Total number of frames in animation
        int mFramesPerRow;                      //Number of frames per row in sprite sheet
        sf::Vector2i mFrameDim;                 //The dimensions of a frame on the sprite sheet
        int mCurFrame;                          //The current frame of the animation
        int mFrameDir;                          //Direction to play the animation in
        sf::Clock mAnimClock;                   //clock used for animation
        int mAnimDelay;
        bool mLoopAnim;                         //Whether or not to loop the animation
        int mStartFrame;                        //The start frame of the animation loop
        int mEndFrame;                          //The end frame of the animation loop

    private:
};

#endif // SPRITECOMPONENT_H
