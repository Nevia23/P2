/*Gli oggetti della classe Tree rappresentano alberi binari ricorsivamente definiti di char.
Si ridefiniscano assegnazione, costruttore di copia e distruttore di Tree come assegnazione,
copia e distruzione profonda. Scrivere esplicitamente eventuali dichiarazioni friend che
dovessero essere richieste da tale definizione.*/

class Nodo {
    friend class Tree;
//non posso creare oggetti Nodo perché il costruttore è in private
//posso definire solo puntatori a Nodo
private:
	Nodo(char c = '*', Nodo* s = 0, Nodo* d = 0): info(c), sx(s), dx(d) {}
	char info;
	Nodo* sx;  
	Nodo* dx;
};

class Tree {
public:
    //costruttore di default
	Tree(): root(nullptr) {}

    //overloading assegnazione
    Tree& operator=(const Tree& t) {
        if(this != &t) {
            distruggi(root);
            root = copia(t.root);
        }
        return *this;
    }

    //costruttore di copia
	Tree(const Tree& t): root(copia(t.root)) {}

    //distruttore
    ~Tree() {
        if(root) {
            distruggi(root);
        }
    }

private:
	Nodo* root;

    static Nodo* copia(Nodo* r) {
        if(r == nullptr) return nullptr;

        //albero puntato da r è non vuoto
        return new Nodo(r->info, copia(r->sx), copia(r->dx));
    }

    static void distruggi(Nodo* r) {
        if(r != nullptr) {
            distruggi(r->sx);
            distruggi(r->dx);
            delete r;  //distruttore standard di Nodo
        }
    }
};