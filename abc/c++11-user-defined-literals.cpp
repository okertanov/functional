// http://pyevolve.sourceforge.net/wordpress/?p=2104

std::string operator "" s (const char* p, size_t n)
{ return std::string(p,n); }

int main(void)
{
    std::cout << "convert me to a string"s.length() << std::endl;
    // here you don't need the parenthesis, note that the
    // c-string was automagically converted to std::string
    return 0;
}

int operator "" ex(const char *cmd, size_t num_chars)
{ return system(cmd); }

int main(void)
{
    "ls -lah"ex;
    return 0;
}

