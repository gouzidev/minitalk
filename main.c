#include <printf.h>

int main()
{
    union test {
        int a;
        char b;
    };

    union test t;
    t.a = 850;
    printf("a -> %d\n", t.a);
    printf("b -> %d\n", t.b);
}