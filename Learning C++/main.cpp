
#include <iostream>
#include <cstdio>
#define MAX_VALUE 10;

int main(int argc, char const *argv[]) {
    /* code */
    std::cout << "hello worlld!\n";

    int file_size;
    file_size = 10;
    std::cout << file_size << '\n';

    const double pi = 3.14;
    
    int x = 10;
    int y = x++;
    printf("x: %d, y: %d\n", x, y);

    printf("type you word(end with space or tab): ");
    std::string s1;
    std::cin >> s1;
    std::cin.ignore();
    printf("%s\n", s1.c_str());

    std::string full_line;
    std::getline(std::cin, full_line);
    printf("%s\n", full_line.c_str());

    return 0;
}
