#include <assert.h>

//-DNDEBUG

#undef abort

int main(int argc)
{
    assert(1==0);
    return 0;
}


