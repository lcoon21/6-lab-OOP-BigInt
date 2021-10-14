#include "BigInt.h"
#include "string.h"
#include "cmath"
#include <iostream>

using namespace std;

BigInt::BigInt() {
    numbers = nullptr;  //нуллпоинтер, чтобы в сеттере не было проблем с очисткой памяти
    SetValue("0");
}

BigInt::BigInt(char *value) {  //конструктор с параметром-числом
    numbers = nullptr;
    SetValue(value);
}

BigInt::BigInt(const BigInt &other) {
    this->length = other.length;
    this->numbers = new int[other.length];
    for (int i = 0; i < other.length; i++) {
        this->numbers[i] = other.numbers[i];
    }
}

BigInt::~BigInt() {
    delete[] numbers;
}

void BigInt::SetValue(char *value) {  //записать число в массив
    delete[] this->numbers;  //удаляет прошлый массив, чтобы записать новый
    try {
        length = strlen(value);
    }
    catch (const exception &e) {
        cout << e.what() << endl;
    }
    this->numbers = new int[length];  //выделяем память под длину массива
    try {
        for (int i = 0; i < length; i++) {
            if (value[i] < 48 || value[i] > 57) {
                MyException ex("hueglot");
                throw ex;
            }
            this->numbers[i] = value[i] - '0';
        }
    }
    catch (MyException &ex) {
        cout << ex.what() << endl;
    }
}

BigInt BigInt::operator+(BigInt n1) {
    BigInt temp;
    // если длина первого слагаемого больше второго
    if (this->length >= n1.length) {
        //то переносим во временный массив цифр цифры текущего числа
        temp.length = this->length;
        temp.numbers = new int[this->length];
        for (int i = 0; i < this->length; i++)
            temp.numbers[i] = this->numbers[i];

        //после чего прибавляем к цифрам временного массива цифры слагаемого
        int i = this->length - 1;
        for (int j = n1.length - 1; j >= 0; j--)
            temp.numbers[i--] += n1.numbers[j];
    } else {
        //иначе поступаем ровно наоборот
        temp.length = n1.length;
        temp.numbers = new int[n1.length];
        for (int i = 0; i < n1.length; i++)
            temp.numbers[i] = n1.numbers[i];

        int i = n1.length - 1;
        for (int j = this->length - 1; j >= 0; j--)
            temp.numbers[i--] += this->numbers[j];
    }
    temp = normii(temp);
    return temp;
}

BigInt BigInt::operator-(BigInt n1) {
    BigInt temp;
    try {
        if (this->length >= n1.length) {
            //то переносим во временный массив цифр цифры текущего числа
            temp.length = this->length;
            try {
                temp.numbers = new int[this->length];
            }
            catch (const exception& e) {
                cout << e.what() << endl;
            }
            for (int i = 0; i < this->length; i++)
                temp.numbers[i] = this->numbers[i];

            //после чего прибавляем к цифрам временного массива цифры слагаемого
            int i = this->length - 1;
            for (int j = n1.length - 1; j >= 0; j--)
                temp.numbers[i--] -= n1.numbers[j];
        } else {
            MyException ex("First num is smaller");
            throw ex;
        }
        temp = normii(temp);
        return temp;
    }
    catch (MyException &ex) {
        cout << ex.what() << endl;
    }
}

BigInt BigInt::operator*(BigInt n1) {
    BigInt result;
    int multiplier = 1;    //множитель, равный 10^значение_разряда_числа
    for (int i = n1.length - 1; i >= 0; i--) {
        //создаем копию текущего числа
        BigInt temp(*this);

        //складываем его с самим собой ОЧЕРЕДНАЯ_ЦИФРА_ЧИСЛА раз
        for (int j = 0; j < n1.numbers[i] * multiplier; j++)
            result = result + temp;
        //множитель умножаем на 10
        multiplier *= 10;
    }
    return result;
}

BigInt BigInt::operator*(int n) {
    BigInt result;
    result.length = this->length + n;
    result.numbers = new int[result.length];
    for (int i = 0; i < this->length; i++) {
        result.numbers[i] = this->numbers[i];
    }
    for (int i = this->length; i < result.length; i++) {
        result.numbers[i] = 0;
    }

    return result;
}

BigInt BigInt::operator/(int n) {
    BigInt result;
    result.length = this->length - n;
    result.numbers = new int[result.length];
    for (int i = 0; i < result.length; i++) {
        result.numbers[i] = this->numbers[i];
    }

    return result;
}


BigInt BigInt::operator/(BigInt n1) {
    try {
        if (n1.numbers[0] == 0) {
            MyException ex("You cannot divide by zero");
            throw ex;
        }
        BigInt divider(n1);  // делитель
        BigInt dividend(*this);  // делимое
        BigInt result;
//деление происходит путём вычитания делителя из делимого
        while (dividend >= divider) {
            dividend = dividend - divider;
            result.numbers[result.length - 1]++;
            result = normii(result);
        }

        result = normii(result);
        return result;
    }
    catch (MyException &ex) {
        cout << ex.what() << endl;
    }
}

BigInt BigInt::operator%(BigInt n1) {
    try {
        if (n1.numbers[0] == 0) {
            MyException ex("You cannot divide by zero");
            throw ex;
        }
        BigInt divider(n1);
        BigInt dividend(*this);
        BigInt result;
// тоже самое, что и в /, но выводится остаток от делимого
        while (dividend >= divider) {  //перегрузим ещё оператор >=
            dividend = dividend - divider;
            result.numbers[result.length - 1]++;
            result = normii(result);
        }

        result = normii(result);
        return dividend;
    }
    catch (MyException &ex) {
        cout << ex.what() << endl;
    }
}

bool BigInt::operator>=(BigInt n1) {
    if (this->length > n1.length) {
        return 1;  // если длина делимого > делителя, то в / вернем 1
    } else if (this->length < n1.length) {
        return 0;  // в обратном случае 0
    } else if (this->length == n1.length) {  //обработка, если длины равны
        for (int i = 0; i < this->length; i++) {
            if (numbers[i] > n1.numbers[i]) {
                return 1;
            } else if (numbers[i] < n1.numbers[i]) {
                return 0;
            }
        }
        int count = 0;
        // обработка, если числа одинаковые
        for (int i = 0; i < this->length; i++) {
            if (numbers[i] == n1.numbers[i]) {
                count++;
            }
        }
        if (count == this->length) {
            return 1;
        }
    }
    return 0;
}


bool BigInt::operator==(BigInt n1) {  // пегерузка == для >=
    if (this->length == n1.length) {
        int count = 0;
        for (int i = 0; i < this->length; i++) {
            if (numbers[i] == n1.numbers[i]) {
                count++;
            }
        }
        if (count == this->length) {
            return 1;
        }
    }
    return 0;
}


BigInt BigInt::operator=(BigInt n1) {  // перегрузка присваивания
    delete[] numbers;
    length = n1.length;
    this->numbers = new int[length];
    for (int i = 0; i < length; i++) {
        numbers[i] = n1.numbers[i];
    }
    return *this;
}

BigInt BigInt::normii(BigInt n1) {
    //создаем копию входного массива
    BigInt result(n1);

    for (int i = result.length - 1; i >= 1; i--)
        if (result.numbers[i] < 0) {
            result.numbers[i - 1]--;
            result.numbers[i] += 10;
        }
    //до тех пор, пока массив начинается с нуля или не достиг длины в 1
    while (!result.numbers[0] && (result.length != 1)) {
        //удаляем ноль из начала массива
        int *new_result = new int[result.length - 1];
        for (int i = 1; i < result.length; i++)
            new_result[i - 1] = result.numbers[i];

        result.length--;
        delete[] result.numbers;
        result.numbers = new_result;
    }

    //нормализуем цифры, превышающие 9 - десятки переносим на следующий разряд, а единицы оставляем тут же
    for (int i = result.length - 1; i >= 1; i--) {
        result.numbers[i - 1] += result.numbers[i] / 10;
        result.numbers[i] %= 10;
    }

    //пока первый элемент превышает 9
    while (result.numbers[0] >= 10) {
        //расширяем массив цифр и в его начало добавляем значение нового разряда
        int *new_result = new int[result.length + 1];
        for (int i = result.length - 1; i >= 0; i--)
            new_result[i + 1] = result.numbers[i];

        new_result[0] = new_result[1] / 10;
        new_result[1] %= 10;
        result.length++;
        delete[] result.numbers;
        result.numbers = new_result;
    }


    return result;
}

char *BigInt::toString() {
    char *str;
    str = new char[length];
    int i;
    for (i = 0; i < length; i++) {
        str[i] = numbers[i] + '0';
    }
    str[i] = '\0';
    return str;
}

void BigInt::print_bin() {
    BigInt mas;
    BigInt temp(*this);
    BigInt two("2");  // 2 нашего типа данных, чтобы можно было делить
    BigInt tempArray;
    while (temp >= two) {  // пока число делится на 2, то
        BigInt rec = temp % two;  // записываем остаток от деления на каждой итерации
        mas.numbers[mas.length - 1] = rec.numbers[0];
        tempArray = mas;
        for (int i = 0; i < tempArray.length; i++) {
            tempArray.numbers[i] = mas.numbers[i];
        }
        mas.numbers = new int[++mas.length];
        for (int i = 0; i < tempArray.length; i++) {
            mas.numbers[i] = tempArray.numbers[i];
        }
        temp = temp / two;
    }
    mas.numbers[mas.length - 1] = temp.numbers[0];
    cout << "Бинарный вид: ";
    for (int i = mas.length - 1; i >= 0; i--) {
        cout << mas.numbers[i];
    }
    cout << endl;
}

BigInt::operator unsigned long() {
    unsigned long int chislo = ULONG_MAX;
    BigInt result("4294967295");
    unsigned long int ulong_num = 0;
    bool flag = 1;
    if (this->length > result.length) {
        unsigned long int tenDegree = pow(10, result.length);
        for (int i = 0; i < result.length; i++, tenDegree /= 10) {
            ulong_num += this->numbers[i] * tenDegree;
        }
    }
    if (this->length < result.length) {
        unsigned long int tenDegree = pow(10, this->length);
        for (int i = 0; i < this->length; i++, tenDegree /= 10) {
            ulong_num += this->numbers[i] * tenDegree;
        }
    }
    if (this->length == result.length) {
        unsigned long int tenDegree = pow(10, this->length);
        for (int i = 0; i < result.length; i++) {
            if (this->numbers[i] == result.numbers[i]) {

            } else if (this->numbers[i] > result.numbers[i]) {
                flag = 0;
                break;
            } else flag = 1;
        }
        if (flag) {
            unsigned long int tenDegree = pow(10, this->length);
            for (int i = 0; i < this->length; i++, tenDegree /= 10) {
                ulong_num += this->numbers[i] * tenDegree;
            }
            return ulong_num;
        } else {
            cout << "chislo bolshoe pizdec";
            return 5;
        }
    }
}

unsigned long BigInt::toLong() {
    unsigned long temp;
    BigInt result("4294967295");
    try {
        if (result >= *this) {
            temp = this->numbers[0];
            for (int i = 1; i < this->length; i++) {
                temp = temp * 10 + this->numbers[i];
            }
            return temp;
        } else {
            MyException ex("Unable to long");
            throw ex;
        }
    }
    catch (MyException &ex) {
        cout << ex.what() << endl;
    }
}


void BigInt::Print() {
    for (int i = 0; i < this->length; i++) {
        cout << this->numbers[i];
    }
}


