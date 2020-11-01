#include <stdio.h>

struct file_io{
    #define isdigit(ch) ((ch) >= '0' && (ch) <= '9')
    char inbuf[1 << 25], *pin, outbuf[1 << 25], *pout;
    int stk[20];

    file_io(): pout(outbuf) {fread(pin = inbuf, 1, 1 << 25, stdin);}
    ~file_io() {fwrite(outbuf, 1, pout - outbuf, stdout);}

    inline void getint(int &num){
        bool neg = 0; num = 0;
        while(!isdigit(*pin)) if(*pin++ == '-') neg = 1;
        while(isdigit(*pin)) num = num * 10 + *pin++ - '0';
        if(neg) num = -num;
    }

    inline void putint(int num){
        static int *v = stk;
        if(!num) *pout++ = '0';
        else{
            if(num < 0) *pout++ = '-', num = -num;
            for(; num; num /= 10) *v++ = num % 10;
            while(v != stk) *pout++ = *--v + '0';
        }
    }

    inline void nextline() {*pout++ = '\n';}
} fio;
#define getint(num) fio.getint(num)
#define putint(num) fio.putint(num)
#define nextline() fio.nextline()