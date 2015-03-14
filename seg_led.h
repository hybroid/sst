#ifndef SEG_LED_H_INCLUDED
#define SEG_LED_H_INCLUDED

//#include <avr/io.h>

typedef struct divmod10_t
{
    uint16_t quot;
    uint8_t rem;
} divmod10_t;

inline static divmod10_t divmodu10(uint16_t n)
{
    divmod10_t res;
    // умножаем на 0.8
    res.quot = n >> 1;
    res.quot += res.quot >> 1;
    res.quot += res.quot >> 4;
    res.quot += res.quot >> 8;
    //res.quot += res.quot >> 16;
    uint16_t qq = res.quot;
    // делим на 8
    res.quot >>= 3;
    // вычисляем остаток
    res.rem = (uint8_t)(n - ((res.quot << 1) + (qq & ~7ul)));
    // корректируем остаток и частное
    if(res.rem > 9)
    {
        res.rem -= 10;
        res.quot ++;
    }
    return res;
}

char * utoa_fast_div(uint16_t value, char *buffer);

#endif // SEG_LED_H_INCLUDED
