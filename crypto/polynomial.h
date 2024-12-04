#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
typedef struct Polynome Polynome;

Polynome *modulo(Polynome *poly, Polynome *modulo);
Polynome *add(Polynome *poly1, Polynome *poly2);
Polynome *sub(Polynome *poly1, Polynome *poly2);
Polynome *inverse(Polynome *poly);

#endif // POLYNOMIAL_H
