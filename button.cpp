#include "button.hpp"
using namespace genv;

Button::Button(Application* szulo, int x, int y, int sx, int sy,
               std::string felirat, std::function<void()> fn) :
    Widget(szulo, x, y, sx, sy),
    _felirat(felirat), _fn(fn)
{}

void Button::draw() const {
    gout.load_font("LiberationSans-Regular.ttf", 17);
    gout << move_to(_x, _y)
         << color(100, 100, 100)
         << box(_size_x, _size_y)
         << move_to(_x + 2, _y + 2)
         << color(200, 200, 200)
         << box(_size_x - 4, _size_y - 4)
         << move_to(_x + 10, _y + 12)
         << color(20, 20, 20)
         << text(_felirat);
}

void Button::handle(event esem) {
    if (esem.type == ev_mouse && esem.button == btn_left
            && is_selected(esem.pos_x, esem.pos_y))
        kattint();
}

void Button::kattint() {
    _fn();
}

void Button::cimkecsere(std::string ujFelirat) {
    _felirat = ujFelirat;
}
