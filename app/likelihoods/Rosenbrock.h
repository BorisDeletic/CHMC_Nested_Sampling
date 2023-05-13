#ifndef CHMC_NESTED_SAMPLING_ROSENBROCK_H
#define CHMC_NESTED_SAMPLING_ROSENBROCK_H

#include "ILikelihood.h"



class RosenbrockLikelihood : ILikelihood {
    inline RosenbrockLikelihood(double D, const double A, const double width)
            : mDim(D), A(A), priorWidth(width) {}

    const Eigen::VectorXd PriorTransform(const Eigen::VectorXd& cube) override;
    const double LogLikelihood(const Eigen::VectorXd& theta) override;
    const Eigen::VectorXd Gradient(const Eigen::VectorXd& theta) override;
    const int GetDimension() override { return mean.size(); };

private:
    const int mDim;
    const double A;
    const double priorWidth;

};


#endif //CHMC_NESTED_SAMPLING_ROSENBROCK_H
