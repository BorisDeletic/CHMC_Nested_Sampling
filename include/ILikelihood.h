#ifndef CHMC_NESTED_SAMPLING_ILIKELIHOOD_H
#define CHMC_NESTED_SAMPLING_ILIKELIHOOD_H

#include <Eigen/Dense>

class ILikelihood {
public:
    virtual const Eigen::VectorXd PriorTransform(const Eigen::VectorXd& cube) = 0;
    virtual const double LogLikelihood(const Eigen::VectorXd& x) = 0;
    virtual const Eigen::VectorXd Gradient(const Eigen::VectorXd& x) = 0;

    virtual const int GetDimension() = 0;
};

#endif //CHMC_NESTED_SAMPLING_ILIKELIHOOD_H
