#include <iostream>

using namespace std;

typedef unsigned char uchar;

struct Color{
    uchar r, g, b, a;
};

Color hex_col(unsigned int num){
    Color col;
    uchar val = num >> 24;
    cout << num << endl;
    col.r = val;
    num -= val<<24;
    val = num >> 16;
    col.g = val;
    num -= val << 16;
    val = num >> 8;
    col.b = val;
    num -= val << 8;
    col.a = num;

    return col;
}


int main(){

    unsigned int value = 0xff3412ff;
    Color col = hex_col(value);
    cout << +col.r << " " << +col.g << " " << +col.b << " " << +col.a << endl;
    return 0;

}


