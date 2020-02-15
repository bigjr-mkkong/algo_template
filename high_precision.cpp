#include <bits/stdc++.h>
using namespace std; 
const int maxn=1926;
struct big_integer
{
    static const int base = 1000;
    static const int width = 3;

    vector<int> v;
    bool is_negative;

    big_integer(long long num = 0)
    {
        *this = num;
        is_negative = false;
    }

    big_integer operator = (long long val)
    {
        v.clear();

        if (val < 0)
        {
            val = -val;
            is_negative = true;
        }
        do
        {
            v.push_back(val % base);
            val /= base;
        } while (val > 0);

        return *this;
    }

    big_integer operator = (const string &str) 
    {
        v.clear();

        string str2 = str;
        if (str2[0] == '-')
        {
            is_negative = true;
            for (string::iterator i = str2.begin(); i < str2.end() - 1; i++)
            {
                *i = *(i + 1);
            }
            *(str2.end() - 1) = '\0';
            str2.resize(str2.length() - 1);
        }

        int cur, len = (str2.length() - 1) / width + 1;
        for (int i = 0; i < len; i++)
        {
            int end = str2.length() - i * width;
            int begin = max(0, end - width);
            sscanf(str2.substr(begin, end - begin).c_str(), "%d", &cur);
            v.push_back(cur);
        }

        return *this;
    }

    big_integer operator + (const big_integer &addend) const 
    {
        big_integer sum;
        sum.v.clear();

        if (is_negative == true)
        {
            if (addend.is_negative == true) sum.is_negative = true;
            else return addend - (-*this);
        }
        else if (addend.is_negative == true)
        {
            return *this - (-addend);
        }

        for (int i = 0, carry = 0; carry != 0 || i < v.size() || i < addend.v.size(); i++)
        {
            int cur = carry;
            if (i < v.size()) cur += v[i];
            if (i < addend.v.size()) cur += addend.v[i];
            carry = cur / base;
            cur %= base;
            sum.v.push_back(cur);
        }

        return sum;
    }

    big_integer operator - (const big_integer &subtrahend) const 
    {
        big_integer difference;
        difference.v.clear();

        if (is_negative == false && subtrahend.is_negative == false && *this < subtrahend)
            return -(subtrahend - *this);
        if (is_negative == true && subtrahend.is_negative == false)
            return -(-*this + subtrahend);
        else if (is_negative == false && subtrahend.is_negative == true)
            return *this + (-subtrahend);
        else if (is_negative == true && subtrahend.is_negative == true)
            return -subtrahend - (-*this);

        for (int i = 0, carry = 0; carry != 0 || i < v.size(); i++)
        {
            int cur = v[i] + carry;
            if (i < subtrahend.v.size()) cur -= subtrahend.v[i];
            if (cur >= 0) carry = 0;
            else
            {
                carry = -1;
                cur += base;
            }
            difference.v.push_back(cur);
        }

        for (int i = difference.v.size() - 1; i >= 0; i--)
        {
            if (difference.v[i] == 0) difference.v.resize(difference.v.size() - 1);
            else break;
        }
        if (difference.v.size() == 0) difference.v.resize(1, 0);

        return difference;
    }

    big_integer operator - () const 
    {
        big_integer big_int = *this;
        big_int.is_negative = !(is_negative);
        return big_int;
    }

    big_integer operator * (const big_integer &multiplier) const
    {
        big_integer product;
        product.v.clear();

        if (is_negative != multiplier.is_negative) product.is_negative = true;

        for (int i = 0; i < v.size(); i++)
        {
            for (int j = 0; j < multiplier.v.size(); j++)
            {
                if (i + j >= product.v.size()) product.v.resize(i + j + 1, 0);
                product.v[i + j] += this->v[i] * multiplier.v[j];
                if (product.v[i + j] >= base)
                {
                    if (i + j + 1 >= product.v.size()) product.v.resize(i + j + 1 + 1, 0);
                    product.v[i + j + 1] += product.v[i + j] / base;
                    product.v[i + j] %= base;
                }
            }
        }

        for (int i = product.v.size() - 1; i >= 0; i--)
        {
            if (product.v[i] == 0) product.v.resize(product.v.size() - 1);
            else break;
        }
        if (product.v.size() == 0) product.v.resize(1, 0);

        return product;
    }

    big_integer operator / (const big_integer &divisor) const // Division
    {
        big_integer divisor__ = divisor;
        big_integer quotient = 0;

        if (is_negative != (divisor < 0)) quotient.is_negative = true;

        big_integer remainder = 0;
        for (int i = v.size() - 1; i >= 0; i--)
        {
            remainder = remainder * base + v[i];

            int lwr_bound = 0, upr_bound = base - 1, mid;
            big_integer mid_bi;
            while (lwr_bound <= upr_bound)
            {
                mid = (lwr_bound + upr_bound) / 2;
                mid_bi = (long long)mid;
                big_integer bi = remainder - mid_bi * divisor;
                if (remainder - mid_bi * divisor < divisor && remainder - mid_bi * divisor >= 0) break;
                else if (remainder - mid_bi * divisor >= divisor) lwr_bound = mid + 1;
                else upr_bound = mid - 1;
            }

            quotient = quotient * base + mid_bi;
            remainder = remainder - mid_bi * divisor;
        }

        for (int i = quotient.v.size() - 1; i >= 0; i--)
        {
            if (quotient.v[i] == 0) quotient.v.resize(quotient.v.size() - 1);
            else break;
        }
        if (quotient.v.size() == 0) quotient.v.resize(1, 0);

        return quotient;
    }

    big_integer operator % (const big_integer &divisor) const 
    {
        big_integer quotient = *this / divisor;
        big_integer remainder = *this - quotient * divisor;
        return remainder;
    }

    big_integer operator += (const big_integer &addend)
    {
        *this = *this + addend;
        return *this;
    }

    big_integer operator -= (const big_integer &subtrahend) 
    {
        *this = *this - subtrahend;
        return *this;
    }

    big_integer operator *= (const big_integer &multiplier) 
    {
        *this = *this * multiplier;
        return *this;
    }

    big_integer operator /= (const long long &divisor) 
    {
        *this = *this / divisor;
        return *this;
    }

    big_integer operator %= (const long long &divisor) 
    {
        *this = *this / divisor;
        return *this;
    }

    big_integer operator ++ () 
    {
        big_integer addend = (long long)1;
        *this = *this + addend;
        return *this;
    }

    big_integer operator -- () 
    {
        big_integer subtrahend = (long long)1;
        *this = *this - subtrahend;
        return *this;
    }

    big_integer operator ++ (int) 
    {
        big_integer addend = (long long)1;
        *this = *this + addend;
        return *this;
    }

    big_integer operator -- (int) 
    {
        big_integer subtrahend = (long long)1;
        *this = *this - subtrahend;
        return *this;
    }

    bool operator < (const big_integer &big_int) const 
    {
        if (is_negative == true && big_int.is_negative == false) return true;
        if (is_negative == false && big_int.is_negative == true) return false;
        if (is_negative == true && big_int.is_negative == true)
        {
            big_integer big_int1, big_int2;
            big_int1 = *this; big_int1.is_negative = false;
            big_int2 = big_int; big_int2.is_negative = false;
            return big_int2 < big_int1;
        }

        if (v.size() != big_int.v.size()) return v.size() < big_int.v.size();
        for (int i = v.size() - 1; i >= 0; i--)
        {
            if (v[i] != big_int.v[i]) return v[i] < big_int.v[i];
        }

        return false;
    }

    bool operator > (const big_integer &big_int) const
    {
        return big_int < *this;
    }

    bool operator <= (const big_integer &big_int) const 
    {
        return !(*this > big_int);
    }

    bool operator >= (const big_integer &big_int) const 
    {
        return !(*this < big_int);
    }

    bool operator != (const big_integer &big_int) const 
    {
        return *this < big_int || *this > big_int;
    }

    bool operator == (const big_integer &big_int) const 
    {
        return !(*this != big_int);
    }

    friend istream &operator >> (istream &in, big_integer &big_int) 
    {
        string str;
        if (!(in >> str)) return in;
        big_int = str;
        return in;
    }

    friend ostream &operator << (ostream &out, big_integer &big_int)
    {
        if (big_int.is_negative == true) out << '-';
        out << big_int.v.back();

        for (int i = big_int.v.size() - 1 - 1; i >= 0; i--)
        {
            char str[base + 5];
            sprintf(str, "%0*d", width, big_int.v[i]);
            out << str;
        }

        return out;
    }
};
big_integer a,b;
int main(void){
	ios::sync_with_stdio(false);
	cin>>a>>b;
	a*=b;
	cout<<a<<endl;
} 
