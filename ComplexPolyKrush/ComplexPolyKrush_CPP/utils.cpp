#include <cmath>
#include <complex>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <iterator>

using namespace std;
typedef complex<double> base;

double get_random_number(double a=-9.5){
    return a + roundf(rand() % 20);
}

base * generate_random_coeffs(int n){
    base * random_coeffs = new base[n];
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        double a = get_random_number();
        double b = get_random_number();
        base rnd_complex_num(a, b);
        random_coeffs[i] = rnd_complex_num;
    }

    return random_coeffs;
}

template <class Container>
void split(const string& str, Container& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
              istream_iterator<string>(),
              back_inserter(cont));
}

base * fill_from_vector(vector<string> y, int n){
    base * x = new base[n];

    for (int i = 0, j = 0; i < 2*n; i+=2){
        double re = stof(y[i]);
        double im = stof(y[i+1]);
        base c(re, im);
        x[j++] = c;
    }

    return x;
}



