// LargeNumbers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Âàì íóæíî ðåàëèçîâàòü êëàññ äëÿ ðàáîòû ñ áîëüøèìè ÷èñëàìè, êîòîðûå íå ïîìåùàþòñÿ â ñòàíäàðòíûå òèïû äàííûõ.

#include <iostream>
#include <vector>
#include <algorithm>  

class big_integer {
private:
    std::vector<int> digits;

public:
    //Конструктор с константной ссылкой
    big_integer(const std::string& str) {
        for (char ch : str) {
            digits.push_back(ch - '0');
        }
        std::reverse(digits.begin(), digits.end());
    }
//Конструктор копирования
    big_integer(const big_integer& other) : digits(other.digits) {}
//Конструктор перемещения
    big_integer(big_integer&& other) noexcept : digits(std::move(other.digits)) {}

  //Оператор перемещающего присваивания
    big_integer& operator=(big_integer&& other) noexcept {
        if (this != &other) {
            digits = std::move(other.digits);
        }
        return *this;
    }
// Оператор сложения
    big_integer operator+(const big_integer& other) const {
        big_integer result = *this;
        result += other;
        return result;
    }
// Оператор умножения на целое число
    big_integer operator*(int num) const {
        big_integer result = *this;
        result *= num;
        return result;
    }
    // Оператор сложения с присваиванием
    big_integer& operator+=(const big_integer& other) {
        int carry = 0;
        for (size_t i = 0; i < std::max(digits.size(), other.digits.size()) || carry; ++i) {
            if (i == digits.size()) {
                digits.push_back(0);
            }
            digits[i] += carry + (i < other.digits.size() ? other.digits[i] : 0);
            carry = digits[i] / 10;
            digits[i] %= 10;
        }
        return *this;
    }
// Оператор умножения на целое число с присваиванием
    big_integer& operator*=(int num) {
        int carry = 0;
        for (size_t i = 0; i < digits.size() || carry; ++i) {
            if (i == digits.size()) {
                digits.push_back(0);
            }
            long long current = digits[i] * 1ll * num + carry;
            digits[i] = current % 10;
            carry = current / 10;
        }
        return *this;
    }
    //Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const big_integer& bigint) {
        for (auto it = bigint.digits.rbegin(); it != bigint.digits.rend(); ++it) {
            os << *it;
        }
        return os;
    }
};

int main() {

    std::setlocale(LC_ALL, "RU");

    auto number1 = big_integer("114575");
    auto number2 = big_integer("78524");
    auto result = number1 + number2;
    std::cout << result; // 193099

    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
