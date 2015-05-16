#include <iostream>
#include "MyString.h"
#include <string>
#include <algorithm>
#include <iterator>
#include <memory>

int main()
{
    MyString a{"hel"};
    a[2] = 'e';
    std::cout << a;
    return 0;
}