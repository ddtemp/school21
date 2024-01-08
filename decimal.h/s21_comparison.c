#include "s21_decimal.h"

int s21_less(s21_decimal value1, s21_decimal value2) {
    return s21_greaterOrEqual(value1, value2) == 0 ? 1 : 0;
}

int s21_lessOrEqual(s21_decimal value1, s21_decimal value2) {
    return s21_greater(value1, value2);
}

int s21_greater(s21_decimal value1, s21_decimal value2) {
    int greater = 0;
    int scaleOfValue1 = s21_getScale(value1);
    int scaleOfValue2 = s21_getScale(value2);
    int signOfValue1 = s21_getSign(value1);
    int signOfValue2 = s21_getSign(value2);

    if (scaleOfValue1 != scaleOfValue2) {
        
    }
}
