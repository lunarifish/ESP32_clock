
#pragma once

#ifndef CODE_COMPONENTS_HPP
#define CODE_COMPONENTS_HPP


#include <cstdint>
#include "Tween.h"
#include "U8g2lib.h"
#include "animations_helper.h"



/**
 * TODO: change the way of animation implementation.
 *
 *       currently, a Component's animator controls the value of animator_target from 0 to 1,
 *       and calculate the Component's position based on pos_before_animation and animation_move_vector
 *       every frame.
 *
 *       A better way is to create a Vec2D struct to represent position, and let the animator
 *       work directly on this struct variable.
 *
 *       Afterwards, we can add a public method playTimeline(), and UI animations can be controlled by
 *       external modules easily.
 */

template <typename Display>
class Component {
public:
    Component();
    Component(uint8_t pos_x, uint8_t pos_y, Display display);
    void moveTo(uint8_t pos_x, uint8_t pos_y, uint16_t time);
    void playTimeline(Tween::Timeline timeline);
    void setVisible(bool visible);
    void setDisplay(Display display);
    bool isVisible();
    uint8_t getPosX();
    uint8_t getPosY();
    virtual void draw();
protected:
    void updateAnimator();

    Tween::Timeline animator;
    double animator_target;
    uint8_t pos[2];
    int8_t animation_move_vector[2] = {0, 0};   // After C11
    uint8_t pos_before_animation[2];
    volatile bool visible;
    Display display;
};


template <typename Display>
class TextBox: public Component<Display> {
public:
    TextBox(String text, uint8_t pos_x, uint8_t pos_y, const uint8_t *font, Display display);
    void setText(String text);
    void setFont(uint8_t &font);
    void draw();
private:
    String text;
    const uint8_t *font;
};



template <typename Display>
class Bitmap: public Component<Display> {
public:
    Bitmap(uint8_t *bitmap, uint8_t pos_x, uint8_t pos_y, uint8_t width, uint8_t height, Display display);
    void setBitmap(uint8_t *bitmap, uint8_t width, uint8_t height);
    void draw();
private:
    uint8_t *bitmap;
    uint8_t width, height;
};




/***************************
 *     implementations     *
 ***************************/


/*****************************************************
 **********         Class Component        ***********
 *****************************************************/

template <typename Display>
    Component<Display>::Component() { }
template <typename Display>
    Component<Display>::Component(uint8_t pos_x, uint8_t pos_y, Display display)
{
    this->pos[0] = pos_x;
    this->pos[1] = pos_y;
    this->pos_before_animation[0] = pos_x;
    this->pos_before_animation[1] = pos_y;
    this->visible = true;
    this->display = display;
}


template <typename Display>
    void Component<Display>::moveTo(uint8_t pos_x, uint8_t pos_y, uint16_t time_ms) {

    this->pos_before_animation[0] = this->pos[0];
    this->pos_before_animation[1] = this->pos[1];

    this->animation_move_vector[0] = pos_x - this->pos[0];
    this->animation_move_vector[1] = pos_y - this->pos[1];

    this->animator.clear();
    this->animator.add(this->animator_target)
        .init(0.0)
        .then<Ease::ElasticOut>(1.0, time_ms);

    this->animator.start();
}

template<typename Display>
    void Component<Display>::playTimeline(Tween::Timeline timeline) {

}

template <typename Display>
    void Component<Display>::setVisible(bool visible) { this->visible = visible; }


template <typename Display>
    void Component<Display>::setDisplay(Display display) { this->display = display; }


template <typename Display>
    bool Component<Display>::isVisible() { return this->visible; }


template <typename Display>
    uint8_t Component<Display>::getPosX() { return this->pos[0]; }


template <typename Display>
    uint8_t Component<Display>::getPosY() { return this->pos[1]; }


template <typename Display>
    void Component<Display>::updateAnimator() { 
        this->animator.update();
        this->pos[0] = this->pos_before_animation[0] + this->animator_target * this->animation_move_vector[0];
        this->pos[1] = this->pos_before_animation[1] + this->animator_target * this->animation_move_vector[1];
}


template <typename Display>
    void Component<Display>::draw() { }






/*****************************************************
 ***********         Class TextBox         ***********
 *****************************************************/

template <typename Display>
TextBox<Display>::TextBox(String text, uint8_t pos_x, uint8_t pos_y, const uint8_t *font, Display display):
        Component<Display>(pos_x, pos_y, display)
{
    this->text = text;
    this->font = font;
}


template <typename Display>
void TextBox<Display>::setText(String text) {
    this->text = text;
}


template <typename Display>
void TextBox<Display>::draw() {
    this->updateAnimator();
    this->display->setFont(font);
    this->display->drawStr(this->pos[0], this->pos[1], this->text.c_str());
}





/*****************************************************
 ***********         Class Bitmap         ************
 *****************************************************/


template<typename Display>
Bitmap<Display>::Bitmap(uint8_t *bitmap, uint8_t pos_x, uint8_t pos_y, uint8_t width, uint8_t height, Display display):
        Component<Display>(pos_x, pos_y, display)
{
    this->width = width;
    this->height = height;
    this->bitmap = bitmap;
}

template<typename Display>
    void Bitmap<Display>::setBitmap(uint8_t *bitmap, uint8_t width, uint8_t height) {
        this->bitmap = bitmap;
        this->width = width;
        this->height = height;
}

template<typename Display>
    void Bitmap<Display>::draw() {
        this->updateAnimator();
        this->display->drawXBMP(this->pos[0], this->pos[1], this->width, this->height, this->bitmap);
}

#endif