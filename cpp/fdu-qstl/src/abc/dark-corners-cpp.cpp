// Hidden Features and Dark Corners of C++/STL
https://groups.google.com/forum/#!msg/comp.lang.c%2B%2B.moderated/VRhp2vEaheU/IN1YDXhz8TMJ
http://www.comeaucomputing.com/tryitout/

while( x --> 0 ) // x goes to 0

if (Object *p = get_object())
    p->use();

if (Object *p = get_object(), p != 0)
    p->use();

while (*p++ = *q++);

// According to the C++ Standard,
// a reference initialized with a temporary value
// makes that temporary value live for the lifetime of the reference itself.
//
// By now probably everyone know this one, but it was a major revelation
// for me at the time: when a temporary is assigned to a reference inside
// a {} block, it's lifetime is extended to the lifetime of a reference.
// That made ScopeGuard possible. ScopeGuard FTW!


