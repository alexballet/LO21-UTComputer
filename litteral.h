#ifndef LITTERAL_H
#define LITTERAL_H

class Litteral {
private:

public:


};

class LitteralNumerique : public Litteral {

};

class Entier : public LitteralNumerique {
private:
    int value;
public:
    Entier(int v): value(v){}
    int getValue() const;
};

class Reel : public LitteralNumerique {
private:
    double value;
public:
    Reel(double v): value(v){}
    double getValue() const;
};

#endif // LITTERAL_H
