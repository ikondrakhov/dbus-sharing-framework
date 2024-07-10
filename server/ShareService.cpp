#include "ShareService.hpp"

ShareService::ShareService() {}

QString ShareService::RegisterService(std::string name,
                              std::vector<std::string> supportedFormats) {
  return "register service";
}

QString ShareService::OpenFile(QString path) {
  std::cout << path.toStdString() << std::endl;
  return QString("open file ") + path;
}

QString ShareService::OpenFileUsingService(std::string path,
                                           std::string service) {
  return "open file using service";
}