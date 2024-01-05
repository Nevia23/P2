#include<iostream>
using namespace std;

class A {
private:
  void h() {cout<<" A::h ";}
public:
  virtual void g() {cout <<" A::g ";}
  virtual void f() {cout <<" A::f "; g(); h();} 
  void m() {cout <<" A::m "; g(); h();}
  virtual void k() {cout <<" A::k "; g(); h(); m(); } 
  A* n() {cout <<" A::n "; return this;}  //il binding è statico perché non c'è il virtual, ma il this è un puntatore A che punta...? Dipende! Potrebbe essere un puntatore polimorfo con tipo dinamico che è sottotipo del tipo statico.
};

class B: public A {
private:
  void h() {cout <<" B::h ";}  //tecnicamente è una RIDEFINIZIONE tecnica perché nella derivata non so che esiste l'h() privata della base
public:
  virtual void g() {cout <<" B::g ";}
  void m() {cout <<" B::m "; g(); h();}  //questa è una RIDEFINIZIONE di m()
  void k() {cout <<" B::k "; g(); h(); m();}  //questo è un overriding
  B* n() {cout <<" B::n "; return this;}  //ridefinizione. E' una versione covariante sul tipo di ritorno. this è un B*. Sempre binding statico
};

int main(){

B* b = new B(); //b è un B che punta ad un B
A* a = new B(); //a è un A che punta ad un B

// COMPILA?
// UNDEFINED BEHAVIOUR?
// COSA STAMPA?

b->f(); // A::f B::g A::h
/*
- Compila? Il compilatore ragiona solo con i tipi statici. Visto che il puntatore di invcazione è un B, va in B a cercare
in B se c'è un match per il tentativo di chiamata ad f().
f() non c'è in B ma potrebbe essere ereditata. In A infatti c'è. Non ci sono overloading, niente mascheramenti, quindi viene
direttamente ereditata, è direttamente accessibile. Quindi SI', COMPILA!!!
- Nel punto precedente il compilatore ha selezionato il prototipo. Ora, a run time, si guarda la virtual table di B se c'è un
overriding di f() ma si vede che nella entry di f() si punta alla f di A, quindi si seleziona questa.
- Stampa A::f e poi esegue le altre chiamate. g() ha come puntatore di invocazione this che ha tipo statico A quindi il compilatore
cerca g() in A. Lo seleziona come prototipo (è ritardato). Controlla se c'è un overriding ed effettivamente c'è. Quindi il puntatore
this con cui viene invocato è un puntatore A che punta ad un B.
Per quanto riguarda h() il compilatore la trova nella parte privata di A. Poiché la funzione non è virtuale (e normalmente non lo sarà
mai nella parte privata) il binding è statico.
*/

b->m(); // B::m B::g B::h
b->k(); // B::k B::g B::h (B::m B::g B::h)
a->f(); // A::f B::g A::h
a->m(); // A::m B::g A::h
a->k(); // B::k B::g B::h (B::m B::g B::h)
(b->n())->g(); // B::n B::g 
/*
Primo check da fare: check di tipo. b->n() : il compilatore seleziona l'n() in B. Che tipo ha (b->n())? B*, quindi il binding su ->g() va cercato 
su B.
*/

((b->n())->n())->g(); // B::n B::n B::g 
(a->n())->g(); // A::n B::g 
/*
a->n() ritorna un puntatore marcato A* che punta dove punta a (ed a punta ad un B) quindi controlla se c'è un overriding in B.
*/

(a->n())->m(); // A::n (A::m B::g A::h)
}