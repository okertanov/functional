
#define NO      (0)
#define YES     (!NO)
#define MAYBE   (~42 & !NO | !YES)

#define Guess(m) (m==YES?MAYBE:NO)

int main()
{
    return Guess(MAYBE);
}

