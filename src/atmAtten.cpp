#include "atmAtten.h"


double atmAtten(float temp, float pressure, float humidity, double distance, double freq) {
    double T = temp + 273.15;   //convert to kelvin
    double To1 = 273.15;        //triple point in k
    double To = 293.15;         //ref temp in K

    double Ps = pressure / 29.9212598;  //static pressure in atm
    double Pso = 1;                     // reference static pressure

    double F = freq / Ps;          //frequency per atm

    //calculate saturation pressure 
    //Psat = 10^(10.79586*(1-(To1/T))-5.02808*log10(T/To1)+1.50474e-4*(1-10^(-8.29692*((T/To1)-1)))-4.2873e-4*(1-10^(-4.76955*((To1/T)-1)))-2.2195983);
    double Psat = pow(10, 10.79586*(1-(To1/T)) - 5.02808*log(T/To1) + 1.50474e-4*(1-pow(10,(-8.29692*((T/To1)-1)))) - 4.2873e-4*(1-pow(10,(-4.76955*((To1/T)-1))))-2.2195983);

    //calculate absolute humidity
    //h = hrin*Psat/Ps;
    double h = humidity * Psat / Ps;

    //scaled relaxation frequency for Nitrogen
    //FrN = (To/T)^(1/2)*(9+280*h*exp(-4.17*((To/T)^(1/3)-1)));
    double FrN = pow(To/T, .5 * (9 + 280 * h * exp(-4.17 * (pow(To/T,1/3)-1))));

    //scaled relaxation frequency for Oxygen
    //FrO = (24+4.04e4*h*(.02+h)/(.391+h));
    double FrO = (24 + 40400 * h * (.02 * h) / (.391 + h));

    //attenuation coefficient in nepers/m
    //alpha = Ps.*F.^2.*(1.84e-11*(T/To)^(1/2) + (T/To)^(-5/2)*(1.275e-2*exp(-2239.1/T)./(FrO+F.^2/FrO) + 1.068e-1*exp(-3352/T)./(FrN+F.^2/FrN)));
    double alpha = Ps * pow(F,2) * (1.84e-11 * pow(T/To,1/2) + pow(T/To,-5/2) * (1.275e-2* exp(-2239.1 / T) / (pow(FrO+F,2) / FrO) + 1.068e-1 * exp(-3352/T) / (pow(FrN+F,2)/FrN)));

    printf("Psat: %f\th: %f\tFrN: %f\tFrO: %f\talpha: %f\n", Psat, h, FrN, FrO, alpha);

    return 10 * log(exp(2 * alpha)) * distance;
}
arma::vec atmAtten(float temp, float pressure, float humidity, double distance, arma::vec freq) {
    arma::vec to_return(freq.n_rows);
    for(uint8_t i = 0; i < freq.n_rows; i++)
        to_return(i) = atmAtten(temp, pressure, humidity, distance, freq(i));
    return to_return;
}