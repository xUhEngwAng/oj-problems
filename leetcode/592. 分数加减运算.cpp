#define MAX(X, Y) ((X)<(Y)?(Y):(X))
#define MIN(X, Y) ((X)<(Y)?(X):(Y))

int gcd(int lh, int rh){
    if(!lh) return rh;
    if(!rh) return lh;
    int mod = lh, a, b = rh;

    while(true){
        a = MAX(b, mod);
        b = MIN(b, mod);
        mod = a % b;
        if(mod == 0) return b;
    }
}

class Fraction {
public:
    int numerator;
    int denominator;

    Fraction(): numerator(0), denominator(1) {}
    Fraction(int n, int d): numerator(n), denominator(d) { simplify(); }

    Fraction operator+(const Fraction& rhf){
        int d = denominator * rhf.denominator;
        int n = numerator * rhf.denominator + rhf.numerator * denominator;
        return Fraction(n, d);
    }

    void simplify(){
        int _gcd = gcd(denominator, abs(numerator));
        denominator = denominator / _gcd;
        numerator = numerator / _gcd;
    }

    string str(){
        return to_string(numerator) + "/" + to_string(denominator);
    }
};

class Solution {
public:
    string fractionAddition(string expression) {
        int currpos = 0, nextpos;
        Fraction ret;

        while(true){
            nextpos = expression.find_first_of("+-", currpos+1);
            if(nextpos == string::npos) break;
            add(ret, expression.substr(currpos, nextpos-currpos));
            currpos = nextpos;
        }

        add(ret, expression.substr(currpos));
        return ret.str();
    }

    void add(Fraction& ret, const string& rh){
        int slashpos = rh.find("/");
        int n = stoi(rh.substr(0, slashpos));
        int d = stoi(rh.substr(slashpos+1));
        ret = ret + Fraction(n, d);
    }
};
