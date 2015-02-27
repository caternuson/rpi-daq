#include <stdio.h>
#include <ADS1015.h>
#include <unistd.h>

int main(void) {
    ADS1015 adc = ADS1015();
    
    while (1) {
        printf("%i\n",adc.readADCSingleEnded());
        usleep(100000);
    }
    
    return 0;
}