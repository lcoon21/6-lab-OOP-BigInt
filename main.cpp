#include <iostream>
#include "BigInt.h"

using namespace std;

int main() {
    system("chcp 65001");
    BigInt a("f94967295");
    BigInt b("4");
    BigInt c;
    c = a / b;
//    unsigned long temp;
//    temp = a.toLong();
//    cout << temp;
    return 0;
}
