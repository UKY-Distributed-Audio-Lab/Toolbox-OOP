#include "regmics.h"

// mat regmicsplane(mat fom, double sp, bool geom) {
//     //check input
//     if(fom.n_cols != 3 || fom.n_rows != 3)
//         throw std::invalid_argument("FOM (first parameter) must be a 3x3 arma::mat\n");
    
//     vec spacing = {sp, sp, sp};
//     return regmicsplane(fom, spacing, geom);
// }

// mat regmicsplane(mat &fom, vec &sp, bool geom) {


//     //generate 3 vectors for pointing to every point in plane
//     vec oa = fom.col(0);
//     vec ob = fom.col(1) - fom.col(0);
//     vec oc = fom.col(2) - fom.col(1);

//     mat mpos; //for returning mic positiions
//     double t;      //starting point for t
//     double mc;     //mic counter
    
    
//     if(geom) {
//         //Determine parametric increment on t and s that corresponds to spacing
//         double obsinc = sqrt(pow(sp(0),2) / sum(ob % ob)); //s spacing
//         double octinc = sqrt(pow(sp(1),2) / sum(oc % oc)); //t spacing
//         //Determine number of increments 
//         int nob = floor(1/obsinc + 2*datum::eps) + 1; // Number along vector ob (s)
//         int noc = floor(1/octinc + 2*datum::eps) + 1; // Number along vector oc (t)
//         mpos = zeros(3, nob*noc);

//         t = 0; mc = 0;
//         //loop for t increments
//         for(int k = 0; k < noc; k++) {
//             double s = 0;
//             //loop for s increments
//             for(int m = 0; m < nob; m++) {
//                 mpos.col(mc) = oa + ob*s + oc*t; //compute coordinates
//                 s += obsinc;
//                 mc++;
//             }
//             t += octinc;
//         }
//     }
//     else {
//         //Determine parametric increment on t and s that corresponds to spacing
//         double obshex = sqrt(pow(sp(0),2) / sum(ob % ob)); //s spacing
//         double octhex = sqrt((pow(sp(0),2) - pow(sp(0)/2,2)) / sum(oc % oc)); //t spacing
//         //Determine number of increments 
//         int nob = floor(1/obshex + 2*datum::eps) + 1; // Number along vector ob (s)
//         int noc = floor(1/octhex + 2*datum::eps) + 1; // Number along vector oc (t)
//         mpos = zeros(3, nob*noc);
        
//         t = 0; mc = 0;
//         //loop for t increments
//         for(int k = 1; k <= noc; k++) {
//             //compute odd and even rows offset
//             //isotropic spacing along s
//             double s = 0;
//             (float)k / 2 == floor((float)k/2) ? s = sqrt(pow(sp(0)/2,2) / sum(ob % ob)) : s = 0;
//             for(int m = 0; m < nob; m++) {
//                 if(s <= 1) {
//                     mpos.col(mc) = oa + ob*s + oc*t; //compute coordinates
//                     s += obshex;
//                     mc++;
//                 }
//             }
//             t += octhex;
//         }
//     }

//     return mpos.cols(0,mc-1);
// }