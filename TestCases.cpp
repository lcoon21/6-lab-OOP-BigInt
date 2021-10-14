#define CATCH_CONFIG_MAIN

#include "BigInt.h"
#include "catch.hpp"

TEST_CASE("const with parametr") {
    BigInt n1("1000");
    BigInt n2;
    n2.SetValue("1000");
    bool check = false;
    if (n1 == n2)
        check = true;
    REQUIRE(check);
}

TEST_CASE("minus") {
    BigInt n1("1000");
    BigInt n2("100");
    BigInt n3("900");
    bool check = false;
    if ((n1 - n2) == n3)
        check = true;
    REQUIRE(check);
}

TEST_CASE("minus_neg") {
    BigInt n1("1000");
    BigInt n2("100");
    BigInt n3("900");
    bool check = false;
    if ((n2 - n1) == n3)
        check = true;
    REQUIRE(check);
}

TEST_CASE("plus") {
    BigInt n1("1000");
    BigInt n2("100");
    BigInt n3("1100");
    bool check = false;
    if ((n1 + n2) == n3)
        check = true;
    REQUIRE(check);
}

TEST_CASE("mult") {
    BigInt n1("1000");
    BigInt n2("100");
    BigInt n3("100000");
    bool check = false;
    if ((n1 * n2) == n3)
        check = true;
    REQUIRE(check);
}

TEST_CASE("div") {
    BigInt n1("1000");
    BigInt n2("100");
    BigInt n3("10");
    bool check = false;
    if ((n1 / n2) == n3)
        check = true;
    REQUIRE(check);
}

TEST_CASE("mod") {
    BigInt n1("1000");
    BigInt n2("100");
    BigInt n3("0");
    bool check = false;
    if ((n1 % n2) == n3)
        check = true;
    REQUIRE(check);
}

TEST_CASE("ass") {
    BigInt n1("145");
    BigInt n2("100");
    n1 = n2;
    bool check = false;
    if (n1 == n2)
        check = true;
    REQUIRE(check);
}

TEST_CASE("to_long") {
    BigInt n1("1234567890");
    unsigned long temp;
    temp = n1.toLong();
    bool check = false;
    if (temp == 1234567890)
        check = true;
    REQUIRE(check);
}

