#include "Adapter.h"

Adapter::Adapter(double initEpsilon, int initPathLength, const Eigen::VectorXd metric)
    :
    mEpsilon(initEpsilon),
    mPathLength(initPathLength),
    mMetric(metric)
{
    mMu = log(initEpsilon);
    mIter = 0;
    mSBar = 0;
    mXBar = 0;
}

void Adapter::Restart() {
    mIter = 0;
    mSBar = 0;
    mXBar = 0;
}

void Adapter::AdaptEpsilon(double acceptProb) {
    mIter++;

    acceptProb = acceptProb > 1 ? 1 : acceptProb;

    printf("e=%.10f, reflectrate=%.1f, iter=%d\n", mEpsilon, acceptProb*100, mIter);
//    std::cout << "e=" << mEpsilon << ", reflectionrate=" << acceptProb << ", iter=" << mIter << std::endl;

    // Nesterov Dual-Averaging of log(epsilon)
    const double eta = 1.0 / (mIter + mT0);

    mSBar = (1.0 - eta) * mSBar + eta * (-mDelta + acceptProb);

    const double x = mMu - mSBar * std::sqrt(mIter) / mGamma;
    const double x_eta = std::pow(mIter, -mKappa);

    mXBar = (1.0 - x_eta) * mXBar + x_eta * x;

    mEpsilon = std::exp(x);
}

/*
bool CHMC::WarmupAdapt(const MCPoint &init)
{
    int dim = init.theta.size();
    Eigen::MatrixXd samples( mWarmupSteps, dim);

    samples.row(0) = init.theta;

    for (int i = 1; i < mWarmupSteps; i++)
    {
        MCPoint last = {
                samples.row(i-1),
                0,
                0};

        MCPoint next = SamplePoint(last, -DBL_MAX);
        samples.row(i) = next.theta;
    }

    Eigen::VectorXd newMetric = CalculateVar(samples).cwiseInverse();
    // std::cerr << std::endl << newMetric << std::endl;

    mHamiltonian.SetMetric(newMetric);

    return true;
}


Eigen::VectorXd CHMC::CalculateVar(const Eigen::MatrixXd& samples) {
    Eigen::MatrixXd centered = samples.rowwise() - samples.colwise().mean();
    Eigen::MatrixXd cov = (centered.transpose() * centered) / double(samples.rows() - 1);

    //   std::cerr << cov.diagonal() << std::endl;
    return cov.diagonal().transpose();
}
*/