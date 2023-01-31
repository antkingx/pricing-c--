#include <iostream>
#include <cmath>
#include <algorithm>
#include <random>
#include "normdist.hpp"
using namespace std;



double generate_normal(double mean, double stddev) {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::normal_distribution<double> normal_dist(mean, stddev);
  return normal_dist(gen);
}



double
option_price_call_european_simulated(
    const double& S, //price of underlying
    const double& X, // exercice price
    const double& r, //risk free rate
    const double& sigma, //volatility of underlying
    const double& time, //time to maturity (in years)
    const int& nb_sims // number of simulations
){
    double R = (r - 0.5*pow(sigma,2))*time;
    double SD = sigma * sqrt(time);
    double sum_payoffs = 0.0;
    for (int n=1; n<=nb_sims; n++){
        double S_T = S*exp(R + SD * generate_normal());
        sum_payoffs += max(0.0, S_T - X);
    };
    return exp(-r*time) * (sum_payoffs/double(nb_sims));
}

void test_simulation_pricing() {
    double S = 100.0; 
    double K = 100.0;
    double r = 0.1;
    double sigma = 0.25;
    double time = 1.0;
    int nb_sims = 5000;

   /* cout << "call : black scholes price = " << option_price_call_european_simulated(S,K,r,sigma,time) << endl;
    cout << " simulated price = " */
         << option_price_call_european_simulated(S,K,r,sigma,time,nb_sims) << endl;
}
