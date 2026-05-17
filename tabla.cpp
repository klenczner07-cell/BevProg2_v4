#include "tabla.hpp"
using namespace genv;

Tabla::Tabla(Application* szulo, int x, int y, JatekMester* jm,
             std::function<void()> lepesutan) :
    Widget(szulo, x, y,
           JatekMester::OSZLOPOK * CELL,
           JatekMester::SOROK * CELL),
    _jm(jm), _lepesutan(lepesutan), _hovSor(-1), _hovOszlop(-1)
{}

void Tabla::draw() const {
    gout << move_to(_x, _y)
         << color(195, 160, 105)
         << box(_size_x, _size_y);

    for (int s = 0; s < JatekMester::SOROK; s++) {
        for (int o = 0; o < JatekMester::OSZLOPOK; o++) {
            int px = _x + o * CELL;
            int py = _y + s * CELL;

            bool kiemelt = (s == _hovSor && o == _hovOszlop
                            && _jm->getCella(s, o) == 0
                            && !_jm->vege()
                            && _jm->getAktualisJatekos() == 1);
            if (kiemelt) {
                gout << move_to(px + 1, py + 1)
                     << color(170, 200, 150)
                     << box(CELL - 1, CELL - 1);
            }

            gout << move_to(px, py)
                 << color(100, 70, 35)
                 << box(CELL, 1)
                 << move_to(px, py)
                 << box(1, CELL);

            int jel = _jm->getCella(s, o);
            if (jel == 1) {
                gout << move_to(px + 5, py + 5)
                     << color(15, 15, 15)
                     << box(CELL - 10, CELL - 10);
            } else if (jel == 2) {
                gout << move_to(px + 5, py + 5)
                     << color(245, 245, 245)
                     << box(CELL - 10, CELL - 10)
                     << move_to(px + 10, py + 10)
                     << color(195, 160, 105)
                     << box(CELL - 20, CELL - 20);
            }
        }
    }

    gout << move_to(_x + JatekMester::OSZLOPOK * CELL, _y)
         << color(100, 70, 35)
         << box(1, JatekMester::SOROK * CELL)
         << move_to(_x, _y + JatekMester::SOROK * CELL)
         << box(JatekMester::OSZLOPOK * CELL, 1);
}

void Tabla::handle(event esem) {
    if (esem.type != ev_mouse)
        return;
    if (_jm->vege())
        return;
    if (_jm->getAktualisJatekos() != 1)
        return;

    int o = (esem.pos_x - _x) / CELL;
    int s = (esem.pos_y - _y) / CELL;
    if (o < 0 || o >= JatekMester::OSZLOPOK || s < 0 || s >= JatekMester::SOROK)
        return;

    _hovSor = s;
    _hovOszlop = o;

    if (esem.button == btn_left) {
        bool sikeres = _jm->lepesKiserlet(s, o);
        if (sikeres)
            _lepesutan();
    }
}
