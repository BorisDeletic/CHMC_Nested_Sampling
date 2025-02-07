#include "Gaussian.h"


const double GaussianLikelihood::LogLikelihood(const Eigen::VectorXd& theta)
{
    double loglikelihood = - var.log().sum() - 0.5 * var.size() * std::log(2 * M_PI);

    loglikelihood -= ((theta.array() - mean) / var).pow(2).sum() / 2;
    return loglikelihood;
}


const Eigen::VectorXd GaussianLikelihood::Gradient(const Eigen::VectorXd& theta)
{
    return - ((theta.array() - mean) / var.pow(2)).matrix();
}
