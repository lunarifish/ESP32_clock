
#pragma once

#ifndef CODE_COMPONENTS_HPP
#define CODE_COMPONENTS_HPP


#include <cstdint>
#include <cmath>
#include "Tween.h"
#include "U8g2lib.h"
#include "types.h"



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
    double_Vec2 pos;
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
    this->pos.x = pos_x;
    this->pos.y = pos_y;
    this->visible = true;
    this->display = display;
}


template <typename Display>
    void Component<Display>::moveTo(uint8_t pos_x, uint8_t pos_y, uint16_t time_ms) {
    this->animator.clear();
    this->animator.add(this->pos)
        .init(this->pos)
        .then<Ease::ElasticOut>(double_Vec2(pos_x, pos_y), time_ms);

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
    uint8_t Component<Display>::getPosX() { return this->pos.x; }


template <typename Display>
    uint8_t Component<Display>::getPosY() { return this->pos.y; }


template <typename Display>
    void Component<Display>::updateAnimator() { this->animator.update(); }


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
    this->display->drawStr(round(this->pos.x), round(this->pos.y), this->text.c_str());
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
        this->display->drawXBMP(round(this->pos.x), round(this->pos.y), this->width, this->height, this->bitmap);
}

#endif