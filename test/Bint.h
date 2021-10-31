#include<bits/stdc++.h>
#define MAXN 9999
#define M 1000
#define DLEN 4
using namespace std;

class Bint
{
private:
    int a[M];
    int len;
public:
    Bint()//Construction function
    {
        len=1;
        memset(a,0,sizeof(a));
    }
    Bint(const int);
    Bint(const char*);
    Bint(const Bint &);
    Bint(const std::string s);

    friend istream & operator>>(istream&,  Bint&);//Overloaded IO stream
    friend ostream & operator<<(ostream&,  Bint&);

    Bint &operator=(const Bint &);//Overloaded operator
    Bint  operator+(const Bint &) const;
    Bint  operator-(const Bint &) const;
    Bint  operator*(const Bint &) const;
    Bint  operator/(const int  &) const;
    Bint  operator^(const int  &) const;
    int   operator%(const int  &) const;

    bool operator < (const Bint &b) const
    {
        if(len != b.len) return len < b.len;
        for (int i=len-1; i>=0; --i)
            if(a[i] != b.a[i]) return a[i] < b.a[i];
        return false;
    }
    bool operator>(const Bint&b)const
    {
        return b < *this;
    }
    bool operator <= (const Bint &b) const
    {
        return !(b < *this);
    }
    bool operator >= (const Bint& b) const
    {
        return !(*this < b);
    }
    bool operator != (const Bint &b) const
    {
        return b < *this || *this < b;
    }
    bool operator == (const Bint &b) const
    {
        return !(b < *this) && !(*this < b);
    }
    void print()//output
    {
        printf("%d", a[len-1]);
        for(int i = len-2; i >= 0; --i)
            printf("%04d", a[i] );
        putchar('\n');
    };
};
