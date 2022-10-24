#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>

using namespace std;

//             keyGeneration    Declaration

class keyGeneration{
    
    public:
        unsigned p;                 // p & q are prime inputs.
        unsigned q;
        unsigned n;                 // n = p * q
        unsigned phi_n;             // phi_n = (p-1) * (q-1) 
        unsigned e;                 // 1 < e < phi_n;     {e & phi_n are co-prime}       value used for encryption.
        unsigned d;                 // (e * d) mod phi_n = 1      value used for decryption
        
        // e & n -> public key & rest are private keys.

        void prompter();
        void primality_check();
        unsigned calculate_n();
        unsigned calculate_phi();
        unsigned calculate_e();
        unsigned calculate_d();

};

/*                   FUNCTIONS OF class keyGeneration definitions                */

void keyGeneration::prompter()
{
    cout<< " Please enter a prime number p: " << endl;
    cin >> p;
    cout<< " Please enter a prime number q: " << endl;
    cin >> q;
}

void keyGeneration:: primality_check()
{
    vector<unsigned> p_factors;
    for (unsigned i = 2;      i <= static_cast<unsigned>(sqrt(p));        i++)
    {
        if(p % i == 0)
        { 
            p_factors.push_back(i);
            p_factors.push_back(p/i);
        }
    }
    
    
    vector<unsigned> q_factors;
    for (unsigned i = 2;      i <= static_cast<unsigned>(sqrt(q));        i++)
    {
        if(q % i == 0)
        { 
            q_factors.push_back(i);
            q_factors.push_back(q/i);
        }
    }

    if (p_factors.size() != 0  ||  q_factors.size() !=0)
        throw (runtime_error(" Non-prime input "));
}


unsigned keyGeneration::calculate_n()
{
    n = p * q;
    return n;
}


unsigned keyGeneration::calculate_phi()
{
    phi_n = (p-1) * (q-1);
    return phi_n;
}


unsigned keyGeneration::calculate_e()
{
    unsigned i = 2;
    while (gcd(i, phi_n) != 1)
        i++;
    e = i;    
    if( e >= phi_n)
        throw (runtime_error("e is greater than or equal to phi n"));
    return e;    
}


unsigned keyGeneration::calculate_d()
{
    unsigned k = 1;

    while(((k * phi_n) + 1) % e != 0)
        k++;
    
    d = ((k * phi_n) + 1) / e;     

    return d;
        
}  


int main(int argc, const char * argv[])
{
    try
    {
        keyGeneration obj1;
        obj1.prompter();
        obj1.primality_check();
        cout << obj1.calculate_phi() << endl;
        cout << obj1.calculate_n() << endl;
        cout << obj1.calculate_e() << endl;
        cout << obj1.calculate_d() << endl;
    }
    catch(runtime_error & s)
    {
        cout << s.what() << endl;
    }
    return 0;
}