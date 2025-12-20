#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <ppl7.h>
#include <ppl7-grafix.h>
#include <ppltk.h>
#include <ppltk-layout.h>

class Gender
{
public:
    enum GenderType {
        Male,
        Female
    };
};

class NameGenerator
{
private:
    std::vector<ppl7::String> male;
    std::vector<ppl7::String> female;
    std::vector<ppl7::String> second_names;
public:
    NameGenerator();
    void loadNames(const ppl7::String& locale);

    ppl7::String randomName(Gender gender);

};

class Game : public ppltk::Window
{
private:
    ppl7::grafix::Grafix* gfx;
    ppltk::WindowManager* wm;
    ppltk::WidgetStyle Style;
    NameGenerator nameGenerator;

    ppltk::Frame* menue;
    ppltk::Label* fpsLabel;
    ppltk::Button* exitButton;
    ppltk::HBoxLayout* layout_menue;

    virtual void closeEvent(ppltk::Event* event) override;
    virtual void mouseClickEvent(ppltk::MouseEvent* event) override;
    //virtual void resizeEvent(ppltk::ResizeEvent* event) override;

public:
    Game();
    ~Game();
    void init();
    void init_grafix();
    void run();
    void loadSavegame(const ppl7::String& filename);



};


#endif // GAMEENGINE_H