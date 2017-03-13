//
// Created by Dillon Yao on 2/27/17.
//

#ifndef CITYBUILD_ANIMATION_H
#define CITYBUILD_ANIMATION_H


#include <vector>
#include <SFML/Graphics/Rect.hpp>

class Animation {
public:
    unsigned int startFrame;
    unsigned int endFrame;

    float duration;

    Animation() {}
    Animation(unsigned int startFrame, unsigned int endFrame, float duration) {
        this->startFrame = startFrame;
        this->endFrame = endFrame;
        this->duration = duration;
    }

    unsigned int getLength() { return endFrame - startFrame + 1;};
};

class AnimationHandler {
private:
    std::vector<Animation> animations;
    float t;
    int currentAnimation;

public:
    void addAnimation(Animation& animation);
    void update(const float dt);
    void changeAnimation(unsigned int animationID);

    sf::IntRect bounds;
    sf::IntRect frameSize;

    AnimationHandler() {
        this->t = 0.0f;
        this->currentAnimation = -1;
    }

    AnimationHandler(const sf::IntRect& frameSize)
    {
        this->frameSize = frameSize;
        this->t = 0.0f;
        this->currentAnimation = -1;
    }
};


#endif //CITYBUILD_ANIMATION_H
