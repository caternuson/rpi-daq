#include <stdio.h>
#include <ADS1015.h>
#include <unistd.h>

int main(void) {
    ADS1015 adc(0x48);

    while (1) {
        printf("%i\t%i\t%i\t%i\n",  adc.readADCSingleEnded(0),
                                    adc.readADCSingleEnded(1),
                                    adc.readADCSingleEnded(2),
                                    adc.readADCSingleEnded(3));
        usleep(100000);
    }
    
    return 0;
}