
#pragma once

#ifndef CODE_COMPONENTS_HPP
#define CODE_COMPONENTS_HPP


#include <cstdint>
#include <cmath>

#include <Tween.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "types.h"


template <typename Display>
class Component {
public:
    Component();
    Component(int8_t pos_x, int8_t pos_y, Display display);
    void moveTo(int8_t pos_x, int8_t pos_y, uint16_t time);
    void setVisible(bool visible);
    void setDisplay(Display display);
    bool isVisible();
    int8_t getPosX();
    int8_t getPosY();
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
    TextBox(String text, int8_t pos_x, int8_t pos_y, uint8_t font_size, const GFXfont *font, Display display);
    void setText(String text);
    void setFont(uint8_t &font);
    void setFontSize(uint8_t font_size);
    uint8_t getFontSize();
    void draw() override;
private:
    String text;
    const GFXfont *font;
    uint8_t font_size;
};



template <typename Display>
class Bitmap: public Component<Display> {
public:
    Bitmap(uint8_t *bitmap, int8_t pos_x, int8_t pos_y, uint8_t width, uint8_t height, Display display);
    void setBitmap(uint8_t *bitmap, uint8_t width, uint8_t height);
    void draw() override;
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
    Component<Display>::Component(int8_t pos_x, int8_t pos_y, Display display)
{
    this->pos.x = pos_x;
    this->pos.y = pos_y;
    this->visible = true;
    this->display = display;
}


template <typename Display>
    void Component<Display>::moveTo(int8_t pos_x, int8_t pos_y, uint16_t time_ms) {
    this->animator.clear();
    this->animator.add(this->pos)
                    .init(this->pos)
                    .then<Ease::ElasticOut>(double_Vec2(pos_x, pos_y), time_ms);

    this->animator.start();
}


template <typename Display>
    void Component<Display>::setVisible(bool visible) { this->visible = visible; }


template <typename Display>
    void Component<Display>::setDisplay(Display display) { this->display = display; }


template <typename Display>
    bool Component<Display>::isVisible() { return this->visible; }


template <typename Display>
    int8_t Component<Display>::getPosX() { return this->pos.x; }


template <typename Display>
    int8_t Component<Display>::getPosY() { return this->pos.y; }


template <typename Display>
    void Component<Display>::updateAnimator() { this->animator.update(); }


template <typename Display>
    void Component<Display>::draw() { }






/*****************************************************
 ***********         Class TextBox         ***********
 *****************************************************/

template <typename Display>
TextBox<Display>::TextBox(String text, int8_t pos_x, int8_t pos_y, uint8_t font_size, const GFXfont *font, Display display):
        Component<Display>(pos_x, pos_y, display)
{
    this->text = text;
    this->font_size = font_size;
    this->font = font;
}

template <typename Display>
void TextBox<Display>::setText(String text) { this->text = text; }

template <typename Display>
void TextBox<Display>::setFontSize(uint8_t font_size) { this->font_size = font_size; }

template <typename Display>
uint8_t TextBox<Display>::getFontSize() { return this->font_size; }

template <typename Display>
void TextBox<Display>::draw() {
    this->updateAnimator();
    this->display->setFont(font);
    this->display->setTextSize(this->font_size);
    this->display->setCursor(round(this->pos.x), round(this->pos.y));
    this->display->print(this->text);
}





/*****************************************************
 ***********         Class Bitmap         ************
 *****************************************************/


template<typename Display>
Bitmap<Display>::Bitmap(uint8_t *bitmap, int8_t pos_x, int8_t pos_y, uint8_t width, uint8_t height, Display display):
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
        this->display->drawBitmap(round(this->pos.x), round(this->pos.y), this->bitmap, this->width, this->height, 1);
}

#endif