#ifndef TABLA_HPP
#define TABLA_HPP

#include <functional>
#include "widgets.hpp"
#include "jatekmaster.hpp"

class Tabla : public Widget {
public:
    Tabla(Application* szulo, int x, int y, JatekMester* jm,
          std::function<void()> lepesutan);
    void draw() const override;
    void handle(genv::event esem) override;
private:
    static const int CELL = 34;
    JatekMester* _jm;
    std::function<void()> _lepesutan;
    int _hovSor;
    int _hovOszlop;
};

#endif
