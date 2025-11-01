#include <iostream>

using namespace std;
//https://jafrog.com/2013/11/23/colors-in-terminal.html

void cores(){
    for (int i = 0; i <= 255; ++i) {
        cout << "\033[38;5;" << i << "m"
        << "\\033[38;5;" << i << "m"
        << "\033[0m" << endl;
    }
}

int main(){
    cores();
    return 0;
}