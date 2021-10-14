#include <iostream>
using namespace std;

class MyException : public exception
{
public:
    string s;
    MyException(string ss) : s(ss) {}
    ~MyException() throw () {} // Updated
    const char* what() const throw() { return s.c_str(); }
};

class BigInt {

public:

    BigInt();
    BigInt(char *value);
    BigInt(const BigInt &other);
    ~BigInt();
    void SetValue(char *value);

    BigInt operator+(BigInt n1);

    BigInt operator-(BigInt n1);

    BigInt operator*(BigInt n1);

    BigInt operator*(int n);

    BigInt operator/(int n);

    BigInt operator/(BigInt n1);

    BigInt operator%(BigInt n1);

    BigInt operator=(BigInt n1);

    bool operator>=(BigInt n1);

    bool operator==(BigInt n1);

    BigInt normii(BigInt n1);

    char* toString();

    void Print();

    void print_bin();

    unsigned long toLong();

    operator unsigned long int();

private:
    int *numbers;
    int length;

};

