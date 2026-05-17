# BevProg2_v4

Mit változtattam v3-hoz kepést:
- JatekMester::maxSorban() megszámolja, egy adott cellában
  elhelyezve a játékos korongját, legfeljebb hány egymást követő saját
  koronggal határolódik
- JatekMester::cellaPontszam() scoring függvény, értékeli hogy
  mennyire jó egy adott üres cellába lepni:
    * 200000 pont: azonnali nyerő lepés
    * 180000 pont: ellenfelet azonnal blokkolni kell
    * többi: saját sorozat^3 * 10 + ellenfél sorozat^3 * 7 + közép Bonus
- JatekMester::aiLepes() végigmegy minden üres cellán,
  a legjobb pontszámú helyre lep
- Button::cimkecsere() hozzaadva (dinamikus felirat frissiteshez)
- Tabla::handle() csak 1. jatekos kattintasat fogadja el (AI modban)
- AmobaApp::lepesUtanTeendo() : ha AI be van kapcsolva es a gep jon,
  azonnal meghivja az aiLepes()-t és elvégzi a gépi lepés-t
- AI be/ki kapcsoló gomb hozzáadva
- Állapotsor különböztet AI es ember-ember mód között
