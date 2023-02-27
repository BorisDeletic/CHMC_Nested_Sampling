#ifndef CHMC_NESTED_SAMPLING_NESTEDSAMPLING_H
#define CHMC_NESTED_SAMPLING_NESTEDSAMPLING_H

#include "CHMC.h"
#include "IPrior.h"
#include "types.h"
#include <memory>
#include <string>
#include <set>

class Logger;

class NestedSampler {
public:
    NestedSampler(CHMC&, IPrior&, ILikelihood&, int numLive, std::string name);

    void Initialise();
    void Run(int steps);
private:
    MCPoint SampleFromPrior();

    CHMC& mCHMC;
    IPrior& mPrior;
    ILikelihood& mLikelihood;
    std::unique_ptr<Logger> mLogger;

    std::set<MCPoint> mLivePoints;
    const int mNumLive;
    const int mDimension;

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<double> mUniform;

    std::string mName;
};

#endif //CHMC_NESTED_SAMPLING_NESTEDSAMPLING_H
