#include "batteryoutput.h"

namespace rtt {
namespace batteries {

static bool findstring(const std::string & s, const std::string & what)
{
    auto it = std::search(s.begin(), s.end(), what.begin(), what.end(),
        [](unsigned char c1, unsigned char c2)
        { return std::toupper(c1) == std::toupper(c2); }
    );
    return (it != s.end());
}

void BatteryOutput::appendStdOut(const std::string & stdOut) {
    detectionDone = false;

    this->stdOut.append(stdOut);
}

void BatteryOutput::appendStdErr(const std::string & stdErr) {
    this->stdErr.append(stdErr);
}

std::string BatteryOutput::getStdOut() const {
    return stdOut;
}

std::string BatteryOutput::getStdErr() const {
    return stdErr;
}

std::vector<std::string> BatteryOutput::getErrors() const {
    return errors;
}

std::vector<std::string> BatteryOutput::getWarnings() const {
    return warnings;
}

void BatteryOutput::doDetection() {
    detectErrsWarnsInStdOut();
}

void BatteryOutput::detectErrsWarnsInStdOut() {
    if(detectionDone)
        return;

    /* Detect warnings and errors here.
     * Detection happens only in stdOut variable. */

    std::istringstream input(stdOut);

    errors.clear();
    warnings.clear();

    for (std::string line; std::getline(input, line); ) {
        if (findstring(line, "warning"))
            warnings.push_back(line);
        if (findstring(line, "error"))
            errors.push_back(line);
    }

    detectionDone = true;
}

} // namespace batteries
} // namespace rtt

