#include "mbed.h"
#include "bbcar.h"
#include "bbcar_rpc.h"

Ticker servo_ticker;
PwmOut pin9(D9), pin8(D8);
Serial xbee(D12, D11);
BBCar car(pin8, pin9, servo_ticker);

int main()
{
    char buf[256], outbuf[256];
    double pwm_table0[] = {-150, -120, -90, -60, -30, 0, 30, 60, 90, 120, 150};
    double speed_table0[] = {-14.833, -14.195, -13.956, -12.122, -6.141, 0.000, 5.263, 11.404, 13.876, 14.754, 15.152}; //ok left 8
    double pwm_table1[] = {-150, -120, -90, -60, -30, 0, 30, 60, 90, 120, 150};
    double speed_table1[] = {-10.527, -11.165, -11.005, -10.607, -5.662, 0.000, 6.938, 10.846, 11.245, 11.005, 11.324};

    // first and fourth argument: length of table
    car.setCalibTable(11, pwm_table0, speed_table0, 11, pwm_table1, speed_table1);

    while (1) {
        for (int i = 0; ; i++) {
            buf[i] = xbee.getc();
            if (buf[i] == '\n') break;
        }
        RPC::call(buf, outbuf);
        xbee.printf("%s\r\n", outbuf);
    }
}
