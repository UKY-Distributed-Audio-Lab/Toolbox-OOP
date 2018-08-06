#include "atmAtten.h"

double atmAtten(float temp, float pressure, float humidity, double distance, double freq) {
    double T = temp + 273.15;   //convert to kelvin
    double To1 = 273.15;        //triple point in k
    double To = 293.15;         //ref temp in K

    double Ps = pressure / 29.9212598;  //static pressure in atm
    double Pso = 1;                     // reference static pressure

    double F = freq / Ps;          //frequency per atm

    //calculate saturation pressure 
    double Psat = pow(10, 10.79586*(1-(To1/T)) - 5.02808*log10(T/To1) + 1.50474e-4*(1-pow(10,(-8.29692*((T/To1)-1)))) - 4.2873e-4*(1-pow(10,(-4.76955*((To1/T)-1))))-2.2195983);

    //calculate absolute humidity
    double h = humidity * Psat / Ps;

    //scaled relaxation frequency for Nitrogen
    double FrN = pow(To/T, .5)*(9 + 280*h*exp(-4.17*(pow(To/T,1/3) - 1)));

    //scaled relaxation frequency for Oxygen
    double FrO = (24 + 4.04e4*h*(.02 + h)/(.391 + h));

    //attenuation coefficient in nepers/m
    double alpha = Ps*pow(F,2)*(1.84e-11*pow(T/To,1/2) + pow(T/To,-5/2)*(1.275e-2*exp(-2239.1/T)/(FrO + pow(F,2)/FrO) + 1.068e-1*exp(-3352/T)/(FrN + pow(F,2)/FrN)));

    return 10 * log10(exp(2 * alpha)) * distance;
}
arma::vec atmAtten(float temp, float pressure, float humidity, double distance, arma::vec freq) {
    arma::vec to_return(freq.n_rows);
    for(uint8_t i = 0; i < freq.n_rows; i++)
        to_return(i) = atmAtten(temp, pressure, humidity, distance, freq(i));
    return to_return;
}