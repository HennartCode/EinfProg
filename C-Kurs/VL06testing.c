#include <stdio.h>

int hailstone(int n) {
    int n_ = n;
    int result = 0;
    while(n_ != 1){
        if (n_%2 == 0){
            n_ /= 2;
        }else{
            n_ *= 3;
            n_ += 1;
        }
        result++;
    }

return result;
}

int main(int argc, char const *argv[])
{
    int i;
    for (i = 1; i < 10; i++){
    printf("%d\n",hailstone(i));
    }
    return 0;
}

