/*
Si assumano le seguenti specifiche riguardanti la libreria Qt.

– Un oggetto della classe QString rappresenta una stringa di caratteri Unicode. La classe QString fornisce un costruttore QString(const char*) con il seguente comportamento: QString(str) costruisce una QString inizializzata con la stringa ASCII str.

– La classe QPaintDevice e` la classe base di tutti gli oggetti che possono essere “dipinti” sullo schermo.
• La classe QPaintDevice e` polimorfa.
• La classe QPaintDevice rende disponibile un metodo int height() const con il seguente comportamento: pd.height() ritorna l’altezza in pixel del QPaintDevice pd. E inoltre disponibile un metodo
int width() const con analogo comportamento per la larghezza.

– QWidget e` una sottoclasse di QPaintDevice i cui oggetti rappresentano delle componenti di una interfaccia grafica Qt.
• La classe QWidget rende disponibile un metodo bool hasFocus() const con il seguente comportamento: w.hasFocus() ritorna true quando la componente w detiene il keyboard focus.
• La classe QWidget rende disponibile un metodo void clearFocus() con il seguente comportamento: w.clearFocus() toglie il keyboard focus alla QWidget w.

– QAbstractButton e` derivata direttamente da QWidget ed e` la classe base astratta dei widget pulsante.
• La classe QAbstractButton rende disponibile un metodo void setText(const QString&) con il seguente comportamento: 
b.setText(s) setta l’etichetta testuale del QAbstractButton b alla stringa s. 

Definire una funzione 
vector<QWidget> fun(const std::vector<QPaintDevice*>&) 
con il seguente comportamento: in ogni invocazione fun(v):

1. per ogni puntatore p contenuto nel vector v:

– se p punta ad un oggetto obj che e` un QWidget avente sia l’altezza che la larghezza ≤ a 50 pixel e che detiene il keyboard focus
allora toglie il keyboard focus a obj;

– se p punta ad un oggetto obj che e` un QAbstractButton allora setta l’etichetta testuale di obj alla stringa “Pulsante”.

2. l’invocazione fun(v) deve ritornare un vector contenente tutti e soli gli oggetti puntati da un  puntatore p contenuti nel vector v che puntano ad un QWidget che non e' e` un QAbstractButton.
*/

std::vector<QWidget> fun(const std::vector<QPaintDevice*>& v)  {
  std::vector<QWidget> w;
  for(std::vector<QPaintDevice*>::const_iterator cit = v.begin();
      cit != v.end(); ++cit) {
    if(*cit != nullptr) {
      Qwidget* p = dynamic_cast<QWidget*>(*cit);
      if(p != nullptr && p->height() <= 50 && p->width() <=50 &&
	 p->hasFocus()) p->clearFocus(); 
      if(dynamic_cast<QAbstractButton*>(*cit))
	static_cast<QAbstractButton*>(*cit)->setText("Pulsante");
      if(p && !dynamic_cast<QAbstractButton*>(*cit))
	w.pushback(*p);
    }
    return w;
  }
}
