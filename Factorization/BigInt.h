#pragma once

#include <iostream>
#include <vector>

using namespace std;
#define uint unsigned int

class BigInt {
public:
    vector<uint>digits;
    uint length{};
     explicit BigInt(string num) {
        for(char i : num)
            digits.push_back((i - '0'));
        length = num.length();
    }
     explicit BigInt(vector<uint> digits) {
        this->digits = digits;
        length = digits.size();
    }
    uint &operator [](int index) {
        return digits[index];
    }
    friend BigInt operator+(BigInt num1, BigInt num2) {
        BigInt &number1 = num1.length > num2.length ? num1 : num2;
        BigInt &number2 = num1.length <= num2.length ? num1 : num2;
        int carry = 0;
        vector<uint>result(10000);
        int j = number2.length-1;
        for(int i = number1.length-1; i >= 0; i--){
            uint sum = 0;
            if(j >= 0)
                sum = number1[i] + number2[j] + carry;
            else
                sum = number1[i] + carry;
            result[i] = sum % 10;
            carry = sum / 10;
            j--;
        }
        BigInt Result(result);
        if(carry != 0) {
            result[number1.length] = carry;
            Result.length = number1.length+1;
        } else {
            Result.length = number1.length;
        }

        return Result;
    }

    friend BigInt operator *(BigInt num1, BigInt num2) {
        BigInt &number1 = num1.length > num2.length ? num1 : num2;
        BigInt &number2 = num1.length <= num2.length ? num1 : num2;
        vector<uint> num_arr(10000, 0);
        BigInt result(num_arr);
        if(number1[0] == 0 || number2[0] == 0) {
            result.length = 1;
            return result;
        }
        for(int i = number1.length-1; i >= number1.length/2 && number1.length > 1; i--)
            swap(number1[i], number1[number1.length-1-i]);

        for(int i = number2.length-1; i >= number2.length/2 && number2.length > 1; i--)
            swap(number2[i], number2[number2.length-1-i]);

        for(int i = 0; i < number2.length; i++)
            for(int j = 0; j < number1.length; j++)
                result[i + j] += number2[i] * number1[j];

        for(int i = 0; i < number1.length + number2.length; i++) {
            int t = result[i]/10;
            result[i] = result[i] % 10;
            result[i+1] = result[i+1] + t;
        }
        result.length = number1.length + number2.length;
        int i;
        for(i = number1.length + number2.length; i >= 0; i--) {
            if(result[i] > 0)
                break;
        }
        result.length = i+1;
        for(i = result.length-1; i >= result.length/2; i--)
            swap(result[i], result[result.length-1-i]);

        return result;
     }

     friend bool operator < (BigInt num1, BigInt num2) {
        if(num1.length < num2.length)
            return 1;

        if(num2.length < num1.length)
            return 0;

        for(int i = 0; i < num1.length; i++) {
            if(num1[i] < num2[i]) return 1;
            else if(num1[i] > num2[i]) return 0;
        }
        return 1;
    }

    friend bool operator == (BigInt num1, BigInt num2) {
         if(num1.length == num2.length) {
             for(int i = 0; i < num1.length; i++)
                 if(num1[i] != num2[i])
                     return 0;
             return 1;
         }
         return 0;
     }
    friend BigInt operator /(BigInt num1, int divisor) {
         if(divisor == 0) {
            throw invalid_argument("Divide by zero is impossible!!!");
         }
         vector<uint> answer(1000, 0);
         int idx = 0;
         int temp = num1[idx];
         int j = 0;
         while (temp < divisor)
             temp = temp * 10 + num1[++idx];
         while (num1.length > idx) {
             answer[j] = (temp / divisor);
             temp = (temp % divisor) * 10 + num1[++idx];
             j++;
         }
         BigInt res(answer);
         if (j == 0) {
             res.length = 1;
             return res;
         }
         res.length = j;
         return res;
     }

     friend BigInt operator %(BigInt &num1, BigInt &num2) {

     }



    static int Square_root(BigInt num) {
       BigInt l("0"), r(num.digits), mid("0"), one("1");
       while(l < r || l == r) {
           mid = (l + r) / 2;
           if(mid * mid == num)
               return mid;
           if(mid * mid < num) {
               l = mid + one;

           }else r = mid - one;
       }
       return mid;
    }

     friend bool Is_perfect(BigInt n) {
        if(Square_root(n) * Square_root(n) == n)
            return 1;
        else return 0;
     }

};


