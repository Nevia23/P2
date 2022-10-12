#include <iostream>

class orario {
public:
    orario ();
    orario (int);
    orario (int, int);
    orario (int, int, int);
    int Ore ();
    int Minuti ();
    int Secondi ();
    orario operator+ (orario) const;
    orario operator- (orario) const;
    bool operator== (orario) const;
    bool operator> (orario) const;
    bool operator< (orario) const;

private:
    int sec;        
}