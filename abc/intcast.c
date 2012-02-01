/*
    ukr.nodes (c) 2011
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

typedef void*       UntypedRef;
typedef UntypedRef  This;
typedef This        (*Ctor)(This);
typedef void        (*Dtor)(This);

#define new(T, O)               (O=(T##Ref)malloc(sizeof(T)), (O->this=O, O->ctor=T##Ctor,O->dtor=T##Dtor), O->ctor(O))
#define del(O)                  (O->dtor(O), free(O), O=0)
#define messageto(O, M, ...)    ((O->M)?O->M(O, ##__VA_ARGS__):0)

typedef struct __Class {
    This this;
    Ctor ctor;
    Dtor dtor;
    
    int (*method)(This);

    int field_a;
    int field_b;
} Class, *ClassRef;

This ClassCtor(This this)
{
    fprintf(stderr, "Inside Ctor = %p\n", this);
    ((ClassRef)this)->field_a = 0;
    ((ClassRef)this)->field_b = 0;
    return this;
}

void ClassDtor(This this)
{
    fprintf(stderr, "Inside Dtor = %p\n", this);
}

int method_sum(This this)
{
    fprintf(stderr, "Inside method_sum = %p\n", this);
    return (((ClassRef)this)->field_a + ((ClassRef)this)->field_b);
}

int method_mus(This this)
{
    fprintf(stderr, "Inside method_mus = %p\n", this);
    return (((ClassRef)this)->field_a ^ ((ClassRef)this)->field_b);
}

int main()
{
    int params = 0, result = 0;

    ClassRef summator, anotherSummator;
    new(Class, summator), new(Class, anotherSummator);
    assert(summator != 0 && anotherSummator != 0);

    /*1*/
    summator->field_a = 30;             //TODO: synthesize getters/setters
    summator->field_b = 12;
    summator->method  = method_sum;     //TODO: set VTABLE macro

    anotherSummator->field_a = 2;
    anotherSummator->field_b = 3;
    anotherSummator->method  = method_mus;

    /*2*/
    {
        int i;
        UntypedRef objects[2] = {summator, anotherSummator};
        for (i = 0; i < sizeof objects / sizeof objects[0]; i++)
        {
            result = messageto(((ClassRef)objects[i]), method);
            (!i?assert(result == 42):assert(result == 1));
            fprintf(stderr, "\tresult = %d\n", result);
        }
    }
    
    del(summator), del(anotherSummator);
    assert(summator == 0 && anotherSummator == 0);

    return 0;
}

