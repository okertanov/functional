#include <iostream>

volatile const char* p = "0";

int main() 
{
  std::cout << p << std::endl;
  return 0;
}