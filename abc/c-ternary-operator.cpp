
if (c)
    x = v;
else
    y = v;

/* c style */
*(c ? &x : &y) = v;

/*c++ style*/
(c ? x : y) = v;

