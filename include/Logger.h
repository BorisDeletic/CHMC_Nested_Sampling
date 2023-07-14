#ifndef CHMC_NESTED_SAMPLING_LOGGER_H
#define CHMC_NESTED_SAMPLING_LOGGER_H

#include "IParams.h"
#include "types.h"
#include <vector>
#include <string>
#include <fstream>

class Logger {
public:
    Logger(std::string name, bool logDiagnostics = false);

    virtual void WritePoint(const MCPoint&, double logWeight);
    void WriteSummary(const NSInfo&);
    void WriteParamNames(const std::vector<std::string>& names, int totalParams);
    void WriteDiagnostics(const NSInfo&, const MCPoint&, const IParams&);

  //  void WriteLivePoints();
  //  void ReadLivePoints();

private:
    std::string mName;

    std::ofstream mDeadFile;
    std::ofstream mPosteriorFile;
    std::ofstream mSummaryFile;
    std::ofstream mParamNameFile;
    std::ofstream mDiagnosticFile;
};

#endif //CHMC_NESTED_SAMPLING_LOGGER_H
