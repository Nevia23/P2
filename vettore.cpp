/*
Definire una classe Vettore i cui oggetti rappresentano array di interi.
Vettore deve includere un costruttore di default, una operazione di concatenazione
che restituisce un nuovo vettore v1 + v2, una operazione di append v1.append(v2),
l’overloading di uguaglianza, dell’operatore di output e dell’operatore di indicizzazione.
Deve inoltre includere il costruttore di copia profonda, l’assegnazione profonda e la
distruzione profonda.
*/

#include<iostream>
using namespace std;

class Vettore {
private:
    int* a;
    unsigned int size;
    //vettore vuoto IFF a == nummptr && size == 0   (IFF = if and only if)
    int* copia() const {
        if(size == 0) return nullptr;
        //vettore di invocazione e' non vuoto
        int* b = new int[size];
        for(unsigned int k = 0; k < size; ++k) b[k] = a[k];
        return b;
    }

public:
//blocchiamo la conversione da unsigned int => Vettore
    explicit Vettore(unsigned dim = 0, int v = 0): a(dim == 0 ? nullptr : new int[dim]), size(dim) {
        for(unsigned int k = 0; k < size; ++k) a[k] = v;
    }

    Vettore(const Vettore& v): a(v.copia()), size(v.size) {
    }

    Vettore& operator=(const Vettore& v) {
        if(this != &v) {
            delete[] a;
            //delete size; è un grosso errore. Devo sovrascriverlo, non pulirlo
            size = v.size;
            a = v.copia();
        } 
        return *this;
    }

    ~Vettore() {
        delete[] a;
    }

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

    bool operator==(const Vettore&v) const {
        if(size != v.size) return false;
        //size == v.size
        for(unsigned int k = 0; k < size; ++k) if(a[k] != v.a[k]) return false;
        return true;
    }

    int& operator[](unsigned int k) const {
        return a[k]; //il controllo sull'accesso lo fa il chiamante
    }

    unsigned int getSize() const {
        return size;
    }
};

std::ostream& operator<<(std::ostream& os, const Vettore& v) {
    for(unsigned int k = 0; k < v.getSize(); ++k) os << v[k] << ' ';
    return os;
}

int main() {
    Vettore v1(4), v2(3, 2), v3(5, -3);
    v1 = v2 + v3;
    v2.append(v2);
    v3.append(v1).append(v3);
    std::cout << v1 << std::endl;
    std::cout << v2 << std::endl;
    std::cout << v3 << std::endl;    
}