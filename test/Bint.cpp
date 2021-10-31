//
// Created by 22332 on 2021/5/26.
//

#include "Bint.h"

Bint::Bint(const int b)
{
    int c, d = b;
    len = 0;
    memset(a, 0, sizeof(a));
    while(d > MAXN)
    {
        c = d - (d / (MAXN + 1)) * (MAXN + 1);
        d = d / (MAXN+1);
        a[len++] = c;
    }
    a[len++] = d;
}
Bint::Bint(const char*s)
{
    int t, k, index, l, i;
    memset(a, 0, sizeof(a));
    l = strlen(s);
    len = l / DLEN;
    if(l % DLEN)  ++len;
    index = 0;
    for(i = l-1; i >= 0; i -= DLEN)
    {
        t = 0;
        k = i - DLEN + 1;
        if(k<0) k=0;
        for(int j = k; j <= i; j++)
            t = t * 10 + s[j] - '0';
        a[index++] = t;
    }
}
Bint::Bint(const Bint & T):len(T.len) //拷贝构造函数
{
    memset(a,0,sizeof(a));
    for(int i = 0; i < len; ++i) a[i] = T.a[i];
}
Bint::Bint(const std::string s)
{
    int t, k, index, l, i;
    memset(a, 0, sizeof(a));
    l = s.length();
    len = l / DLEN;
    if(l % DLEN) ++len;
    index = 0;
    for(i = l-1; i >= 0; i -= DLEN)
    {
        t = 0;
        k = i - DLEN + 1;
        if(k < 0) k = 0;
        for(int j = k; j <= i; j++)  t = t * 10 + s[j] - '0';
        a[index++] = t;
    }
}
Bint & Bint::operator=(const Bint & n) //重载赋值运算符，大数之间进行赋值运算
{
    len = n.len;
    memset(a,0,sizeof(a));
    for(int i = 0; i < len; ++i) a[i] = n.a[i];
    return *this;
}
istream& operator>>(istream & in,Bint & b)
{
    char ch[M*4];
    in >> ch;
    int l = strlen(ch),count = 0, sum = 0, i =- 1;
    for(int i = l-1; i >=0 ;)
    {
        sum = 0;
        int t = 1;
        for(int j = 0; j < 4&&i >= 0; ++j, --i, t*=10) sum +=( ch[i] - '0') * t;
        b.a[count] = sum;
        ++count;
    }
    b.len = count++;
    return in;
}
ostream& operator<<(ostream& out,Bint& b) //重载输出运算符
{
    cout << b.a[b.len-1];
    for(int i = b.len-2; i >= 0; --i)
    {
        cout.width(DLEN);
        cout.fill('0');
        cout << b.a[i];
    }
    return out;
}
Bint Bint::operator+(const Bint & T) const
{
    Bint t(*this);
    int i, big;      //位数
    big = T.len > len ?T.len : len;
    for(i = 0; i < big; ++i)
    {
        t.a[i] += T.a[i];
        if(t.a[i] > MAXN)
        {
            ++t.a[i+1];
            t.a[i] -= MAXN + 1;
        }
    }
    if(t.a[big] != 0) t.len = big+1;
    else t.len = big;
    return t;
}
Bint Bint::operator-(const Bint & T) const
{
    int i,j,big;
    bool flag;
    Bint t1, t2;
    if(*this > T)
    {
        t1 = *this;
        t2 = T;
        flag = 0;
    }
    else
    {
        t1 = T;
        t2 = *this;
        flag = 1;
    }
    big = t1.len;
    for(i = 0; i < big; ++i)
        if(t1.a[i] < t2.a[i])
        {
            j = i + 1;
            while(t1.a[j] == 0) ++j;
            --t1.a[j--];
            while(j>i) t1.a[j--] += MAXN;
            t1.a[i] += MAXN+1-t2.a[i];
        }
        else t1.a[i] -= t2.a[i];

    t1.len = big;
    while(t1.a[t1.len-1] == 0 && t1.len > 1) --t1.len,--big;
    if(flag) t1.a[big-1] = 0 - t1.a[big-1];
    return t1;
}
Bint Bint::operator*(const Bint & T) const
{
    Bint ret;
    int i, j, up;
    int temp, temp1;
    for( i = 0; i < len; ++i)
    {
        up = 0;
        for(j = 0; j < T.len; ++j)
        {
            temp = a[i] * T.a[j] + ret.a[i+j] + up;
            if(temp > MAXN)
            {
                temp1 = temp - temp / (MAXN+1) * (MAXN+1);
                up = temp / (MAXN+1);
                ret.a[i+j] = temp1;
            }
            else up = 0, ret.a[i+j] = temp;
        }
        if(up != 0) ret.a[i+j] = up;
    }
    ret.len = i + j;
    while(ret.a[ret.len-1] == 0 && ret.len > 1) --ret.len;
    return ret;
}
Bint Bint::operator/(const int &b) const
{
    Bint ret;
    int i,down = 0;
    for(i = len-1; i >= 0; --i)
    {
        ret.a[i] = (a[i] + down * (MAXN+1)) / b;
        down = a[i] + down * (MAXN + 1) - ret.a[i]*b;
    }
    ret.len = len;
    while(ret.a[ret.len-1] == 0 && ret.len > 1) --ret.len;
    return ret;
}
int Bint::operator %(const int & b) const
{
    int i,d=0;
    for (i=len-1; i>=0; --i)
        d=((d*(MAXN+1))%b+a[i])%b;
    return d;
}
Bint Bint::operator^(const int & n) const
{
    Bint t,ret(1);
    if(n < 0) exit(-1);
    if(n == 0) return 1;
    if(n == 1) return *this;
    int m = n, i;
    while(m > 1)
    {
        t = *this;
        for(i = 1; i<<1<=m; i<<=1) t=t*t;
        m -= i;
        ret = ret * t;
        if(m == 1) ret = ret * (*this);
    }
    return ret;
}

