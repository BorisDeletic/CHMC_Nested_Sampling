#ifndef CHMC_NESTED_SAMPLING_TYPES_H
#define CHMC_NESTED_SAMPLING_TYPES_H

#include <Eigen/Dense>

// Markov Chain point
typedef struct MCPoint {
    const Eigen::VectorXd theta;
    const double likelihood;
    const double birthLikelihood;
    const int reflections = 0;
    const int steps = 0;
    const double acceptProbability = 1;
    bool rejected = false;
    double energy = 0;
} MCPoint;

inline bool operator<(const MCPoint& a, const MCPoint& b) {
    return a.likelihood < b.likelihood;
}


typedef struct NSConfig {
    const int numLive;
    const int maxIters;
    const double precisionCriterion;
} NSConfig;


typedef struct NSSummary {
    const double logZ;
    const double logZRemaining;
} NSSummary;


typedef struct Rejections {
    int reflectionRejections;
    int energyRejections;
    int mIters;
} Rejections;

#endif //CHMC_NESTED_SAMPLING_TYPES_H
