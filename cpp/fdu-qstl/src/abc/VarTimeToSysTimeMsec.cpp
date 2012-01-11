/*
A variant time is stored as an 8-byte real value (double), representing a date between January 1, 1753
and December 31, 2078,inclusive. The value 2.0 represents January 1, 1900; 3.0 represents January 2, 1900, and so on.
Adding 1 to the value increments the date by a day. The fractional part of the value represents the time of day.
Therefore, 2.5 represents noon on January 1, 1900; 3.25 represents 6:00 A.M. on January 2, 1900, and so on.
so 0.5 represents 12 hours ie 12*60*60 seconds, hence 1 second = .0000115740740740
*/
static const double MSFT_FLOAT_1000MILLISECONDS = .0000115740740740;

static BOOL VariantTimeToSystemTimeWithMsec(const double ft, SYSTEMTIME* st)
{
    BOOL rc = FALSE;

    double halfsecond = MSFT_FLOAT_1000MILLISECONDS / 2.0; // a half of 1000 msec

    if ( VariantTimeToSystemTime(ft - halfsecond, st) != FALSE )
    {
        double fraction = ft - (unsigned long)ft; // extracts the fraction part

        double hours;
        hours = fraction = (fraction - (int)fraction) * 24;
        double minutes;
        minutes = (hours - (int)hours) * 60;
        double seconds;
        seconds = (minutes - (int)minutes) * 60;
        double milliseconds;
        milliseconds = (seconds - (int)seconds) * 1000;
        milliseconds = milliseconds + 0.5; // rounding off millisecond to the nearest millisecond

        if ( milliseconds < 1.0 || milliseconds > 999.0 ) //Fractional calculations may yield in results like
            milliseconds = 0; // 0.00001 or 999.9999 which should actually be zero (slightly above or below limits are actually zero)

        if ( milliseconds )
        {
            st->wMilliseconds = (WORD) milliseconds;
            rc = TRUE;
        }
        else
        {
            rc = VariantTimeToSystemTime(ft, st); //if there is 0 milliseconds, then we don't have the problem
        }
    }

    return rc;
}

BOOL SystemTimeToVariantTimeWithMilliseconds (/*input*/ SYSTEMTIME st, /*output*/double *dVariantTime)
{
    WORD wMilliSeconds = st.wMilliseconds; // save the milli second information

    st.wMilliseconds = 0; // pass 0 milliseconds to the function and get
                          // the converted value without milliseconds
    double dWithoutms;
    if (!SystemTimeToVariantTime(&st, &dWithoutms))
        return FALSE;

    // manually convert the millisecond information into variant
    // fraction and add it to system converted value
    *dVariantTime = dWithoutms + (ONETHOUSANDMILLISECONDS * wMilliSeconds / 1000.0);
    return TRUE;
}

