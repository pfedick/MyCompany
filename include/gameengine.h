#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <ppl7.h>
#include <ppl7-grafix.h>
#include <ppltk.h>
#include <ppltk-layout.h>


class Game : public ppltk::Window
{
private:
    ppl7::grafix::Grafix* gfx;
    ppltk::WindowManager* wm;
    ppltk::WidgetStyle Style;

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