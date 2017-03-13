//
// Created by Dillon Yao on 2/27/17.
//

#include "animation.h"

void AnimationHandler::update(const float dt) {
    if (currentAnimation >= this->animations.size() || currentAnimation < 0) {
        return;
    }
    float duration = this->animations[currentAnimation].duration;
    int frame = int((t + dt) / duration);
    if (frame > int(t / duration)) {
        frame %= this->animations[currentAnimation].getLength();
        sf::IntRect frameRect = this->frameSize;
        frameRect.left = frameRect.width * frame;
        frameRect.top = frameRect.height * currentAnimation;
        this->bounds = frameRect;
    }

    this->t += dt;
    if (this->t > duration* this->animations[currentAnimation].getLength()) {
        this->t = 0.0f;
    }
}

void AnimationHandler::addAnimation(Animation &animation) {
    this->animations.push_back(animation);
}

void AnimationHandler::changeAnimation(unsigned int animationID) {
    if (this->currentAnimation == animationID || animationID >= this->animations.size() || animationID < 0) {
        return;
    }

    this->currentAnimation = animationID;

    sf::IntRect rect = this->frameSize;
    rect.top = rect.height * animationID;
    this->bounds = rect;
    this->t = 0.0;
}