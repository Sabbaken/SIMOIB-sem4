#include <time.h>
#include <vector>
#include <iostream>
using namespace std;
typedef unsigned int uint;

uint phi (uint n) {
    uint result = n;
    for (uint i = 2; i*i <= n; ++i)
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    if (n > 1)
        result -= result / n;
    return result;
}


uint powMod (uint a, uint b, uint p) {
    uint res = 1;
    while (b)
        if (b & 1)
            res = uint (res * 1ll * a % p),  --b;
        else
            a = uint (a * 1ll * a % p),  b >>= 1;
    return res;
}


uint generator (uint p) {
    vector<int> fact;
    uint _phi = phi(p),  n = _phi;
    for (uint i = 2; i*i <= n; ++i)
        if (n % i == 0) {
            fact.push_back (i);
            while (n % i == 0)
                n /= i;
        }
    if (n > 1)
        fact.push_back (n);

    for (uint res = 2; res <= p; ++res) {
        bool ok = true;
        for (size_t i = 0; i < fact.size() && ok; ++i)
            ok &= powMod (res, _phi / fact[i], p) != 1;
        if (ok)  return res;
    }
    return -1;
}

uint getPubKey (uint a, uint g, uint p) {
    uint rez = g;
    while (a-- > 0)
        rez = rez*g % p;
    return rez;
}

int main() {
    srand((unsigned)time( NULL ));
    //      Alice generate private Key
    uint a = (uint)rand();
    //      generate params g and p (default p = 2957)
    uint p = 2957;
    uint g = generator(p);
    //      Alice find Public Key A
    uint A = getPubKey(a,g,p);
    //      Output
    cout << "\n Alice generate: \n\tPrivate Key:\t\t" << a <<
         "\n\tRandom parametr:\t" << p <<
         "\n\tPrimitive root:\t\t" << g <<
         "\n\tAlice Public Key:\t" << A << endl;
//---------------------------------------------------------------------------
    //      Bob generate private Key
    uint b = (uint)rand();
    //      Bob find Public Key B
    uint B = getPubKey(b,g,p);
//---------------------------------------------------------------------------
    cout << "\n Bob generate: \n\tPrivate Key:\t\t" << b <<
         "\n\tRandom parametr:\t" << p <<
         "\n\tPrimitive root:\t\t" << g <<
         "\n\tBob Public Key:\t\t" << B << endl;
    //      Alice get secret Key K
    uint Ka = getPubKey(a,B,p);
    //      Bob get secter Key K
    uint Kb = getPubKey(b,A,p);
    //      Output
    cout << "\n Bob Secret Key:\t" << Kb;
    cout << "\n Alice Secret Key:\t" << Ka;
    return 0;
}
