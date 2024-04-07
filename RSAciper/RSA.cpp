#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <random>
#include <ctime>

using namespace boost::multiprecision;
using namespace std;

cpp_int gcd(cpp_int a, cpp_int b) {
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

cpp_int modPow(cpp_int base, cpp_int exponent, cpp_int modulus) {
    cpp_int result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

pair<cpp_int, cpp_int> generateKeys(cpp_int p, cpp_int q) {
    cpp_int n = p * q;
    cpp_int phi = (p - 1) * (q - 1);
    cpp_int e = 3;
    while (gcd(e, phi) != 1) {
        e += 2;
    }
    cpp_int d = 1, k = 0;
    while ((1 + k * phi) % e != 0 || d <= 1) {
        k++;
        d = (1 + k * phi) / e;
    }
    return { e, d };
}

cpp_int encrypt(cpp_int msg, cpp_int e, cpp_int n) {
    return modPow(msg, e, n);
}

cpp_int decrypt(cpp_int msg, cpp_int d, cpp_int n) {
    return modPow(msg, d, n);
}

int main() {
    // Простые числа p и q. Для реального приложения они должны быть значительно больше.
    cpp_int p = 61, q = 53;
    auto keys = generateKeys(p, q);
    cpp_int e = keys.first;
    cpp_int d = keys.second;
    cpp_int n = p * q;

    cpp_int message = 42; // Сообщение для шифрования
    cpp_int encrypted = encrypt(message, e, n);
    cpp_int decrypted = decrypt(encrypted, d, n);

    cout << "Original: " << message << endl;
    cout << "Encrypted: " << encrypted << endl;
    cout << "Decrypted: " << decrypted << endl;

    return 0;
}
