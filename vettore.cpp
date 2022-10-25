/*
Definire una classe Vettore i cui oggetti rappresentano array di interi.
Vettore deve includere un costruttore di default, una operazione di concatenazione
che restituisce un nuovo vettore v1 + v2, una operazione di append v1.append(v2),
l’overloading di uguaglianza, dell’operatore di output e dell’operatore di indicizzazione.
Deve inoltre includere il costruttore di copia profonda, l’assegnazione profonda e la
distruzione profonda.
*/

#include<iostream>

class Vettore {
private:
    int* a;
    unsigned int size;
    //vettore vuoto IFF a == nummptr && size == 0   (IFF = if and only if)
public:
//blocchiamo la conversione da unsigned int => Vettore
    explicit Vettore(unsigned dim = 0, int v = 0): a(dim == 0 ? nullptr : new int[dim]), size(dim) {
        for(unsigned int k = 0; k < size; ++k) a[k] = v;
    }
    Vettore(const Vettore& v);
    Vettore& operator=(const Vettore& v);
    ~Vettore();

    Vettore operator+(const Vettore& v) const {
        Vettore w(size + v.size);
        unsigned int k = 0;
        for(; k < size; ++k) w.a[k] = a[k];
        for(; k < size + v.size; ++k) w.a[k] = v.a[k - size];
        return w;
    }

    void append(const Vettore& v) {
        //*this + v oppure this->operator+(v)
        *this = this->operator+(v); //assegnazione profonda
    }
};