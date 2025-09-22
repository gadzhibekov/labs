#pragma ocne

#define WITH_LOG

#include <string>
#include <QString>

void Log(const                  std::string&    str);
void Log(const                  QString&        str);

void LogWithWarning(const       QString&        str);
void LogWithError(const         QString&        str);
void LogWithInformation(const   QString&        str);