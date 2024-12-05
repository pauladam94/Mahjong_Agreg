#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <stdbool.h>
// Polynomial expression that implements all basics operation
typedef struct Poly Poly;

Poly *poly_modulo(Poly *poly, Poly *modulo);
Poly *poly_add(Poly *poly1, Poly *poly2);
Poly *poly_sub(Poly *poly1, Poly *poly2);
Poly *poly_inverse(Poly *poly);
Poly *poly_from_string(const char *str);
bool poly_equals(Poly *p1, Poly *p2);

#endif // POLYNOMIAL_H
