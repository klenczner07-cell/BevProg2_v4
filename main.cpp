#include "application.hpp"
#include "button.hpp"
#include "felirat.hpp"
#include "tabla.hpp"
#include "jatekmaster.hpp"
#include <string>

class AmobaApp : public Application {
public:
    AmobaApp() : Application(720, 530), _jm(), _aiBekapcsolva(true) {
        _allapotSor  = new Felirat(this, 530, 10, 175, 40, "");
        _aiJelzo     = new Felirat(this, 530, 60, 175, 40, "");
        _tabla       = new Tabla(this, 10, 10, &_jm, [this]() { lepesUtanTeendo(); });
        _resetGomb   = new Button(this, 530, 110, 175, 38, "Uj jatek", [this]() {
            _jm.reset();
            allapotFrissit();
        });
        _aiGomb      = new Button(this, 530, 158, 175, 38, "AI: BE", [this]() {
            _aiBekapcsolva = !_aiBekapcsolva;
            _aiGomb->cimkecsere(_aiBekapcsolva ? "AI: BE" : "AI: KI");
            allapotFrissit();
        });
        _jatekNev    = new Felirat(this, 530, 206, 175, 40, "Amoba 5-in-a-row");
        allapotFrissit();
    }

private:
    void lepesUtanTeendo() {
        if (!_jm.vege() && _aiBekapcsolva && _jm.getAktualisJatekos() == 2) {
            auto [as, ao] = _jm.aiLepes(2);
            _jm.lepesKiserlet(as, ao);
        }
        allapotFrissit();
    }

    void allapotFrissit() {
        int ny = _jm.getNyertes();
        if (ny == 1) {
            _allapotSor->frissit("Fekete nyert!");
        } else if (ny == 2) {
            std::string uzenet = _aiBekapcsolva ? "Gep nyert!" : "Feher nyert!";
            _allapotSor->frissit(uzenet);
        } else if (_jm.teleE()) {
            _allapotSor->frissit("Dontetlen!");
        } else {
            int akt = _jm.getAktualisJatekos();
            if (_aiBekapcsolva && akt == 2)
                _allapotSor->frissit("Gep gondolkodik...");
            else if (akt == 1)
                _allapotSor->frissit("Te lepsz (fekete)");
            else
                _allapotSor->frissit("2. jatekos lep");
        }

        _aiJelzo->frissit(_aiBekapcsolva ? "Mod: ember vs gep" : "Mod: ket ember");
    }

    JatekMester _jm;
    bool        _aiBekapcsolva;
    Tabla*      _tabla;
    Felirat*    _allapotSor;
    Felirat*    _aiJelzo;
    Felirat*    _jatekNev;
    Button*     _resetGomb;
    Button*     _aiGomb;
};

int main() {
    AmobaApp app;
    app.event_loop();
    return 0;
}
