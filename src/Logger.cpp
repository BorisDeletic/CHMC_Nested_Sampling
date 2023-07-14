#include "Logger.h"
#include <iostream>

Logger::Logger(std::string name, bool logDiagnostics)
    :
    mName(name)
{
    mDeadFile.open(mName + "_dead-birth.txt");
    mPosteriorFile.open(mName + ".posterior");

    if (logDiagnostics) {
        mDiagnosticFile.open(mName + ".diagnostics");

        mDiagnosticFile
            << "iter,numlive,logZ,logZlive,likelihood,birth_likelihood,rejected,accept_prob,reflections,steps"
            << "epsilon,path_length,metric" << std::endl;
    }
}


// Log weight is prior volume shell w_i = X_{i-1} - X_i
void Logger::WritePoint(const MCPoint& point, const double logWeight) {
    if (!mDeadFile.is_open()) {
        mDeadFile.open(mName + "_dead-birth.txt", std::ios::app);
    }

    if (!mPosteriorFile.is_open()) {
        mPosteriorFile.open(mName + ".posterior", std::ios::app);
    }

    double logPosteriorWeight = logWeight + point.likelihood;
    mPosteriorFile << logPosteriorWeight << " ";
    mPosteriorFile << logWeight << " ";
    mPosteriorFile << -point.likelihood << " ";

    for (const double phi : point.derived) {
       // mDeadFile << phi << " ";
      //  mPosteriorFile << phi << " ";
    }

    for (const double theta : point.theta) {
        //      mDeadFile << theta << " ";
        //      mPosteriorFile << theta << " ";
    }

    mDeadFile << point.theta[0] << " ";
    mDeadFile << point.theta[1] << " ";
    mDeadFile << point.theta[2] << " ";

    mDeadFile << point.likelihood << " " << point.birthLikelihood << std::endl;
    mPosteriorFile << std::endl;
}


void Logger::WriteParamNames(const std::vector<std::string> &names, int totalParams)
{
    // mParamNameFile.open(mName + ".paramnames");

    for (const auto& name : names) {
        //    mParamNameFile << name << " " << name << std::endl;
    }

    for (int i = 1; i < totalParams - names.size() + 1; i++) {
        //    mParamNameFile << "p" << i << " \\theta{" << i << "}\n";
    }

    //  mParamNameFile.close();
}


void Logger::WriteSummary(const NSInfo& summary) {
    mSummaryFile.open(mName + ".stats");

    mSummaryFile << "Log (Z) = " << summary.logZ << std::endl;
    mSummaryFile << "Log (Z) Remaining = " << summary.logZLive << std::endl;

   // if (samplerSummary.rejectRatio != 0) {
   //     mSummaryFile << "Rejection Ratio = " << samplerSummary.rejectRatio << std::endl;
   // }

    mSummaryFile.close();
    mDeadFile.close();
}


void Logger::WriteDiagnostics(const NSInfo& info, const MCPoint& point, const IParams& params)
{
    if (!mDiagnosticFile.is_open()) {
        mDiagnosticFile.open(mName + ".diagnostic", std::ios::app);
    }

    mDiagnosticFile << info.iter;
    mDiagnosticFile << info.numLive;
    mDiagnosticFile << info.logZ;
    mDiagnosticFile << info.logZLive;

    mDiagnosticFile << point.likelihood;
    mDiagnosticFile << point.birthLikelihood;
    mDiagnosticFile << (point.rejected ? 1 : 0);
    mDiagnosticFile << point.acceptProbability;
    mDiagnosticFile << point.reflections;
    mDiagnosticFile << point.steps;

    mDiagnosticFile << params.GetEpsilon();
    mDiagnosticFile << params.GetPathLength();
    mDiagnosticFile << params.GetMetric()[0];
}
