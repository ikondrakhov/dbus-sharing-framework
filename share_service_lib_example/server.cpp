#include <QCoreApplication>
#include <QtDBus/QtDBus>

#include <stdio.h>
#include <stdlib.h>

#include <filesystem>
#include <string>
#include <vector>

#include "Request.hpp"
#include "SharingService.hpp"

void process(const std::string& path) { std::cout << path << std::endl; };

int main(int argc, char* argv[]) {
    const std::vector<std::string> supportedFormats = {"mp4", "mov", "mp3"};

    const auto onOpenFile = [](const std::string& path, const Request& req) {
        if (!std::filesystem::exists(path)) {
            req.sendErrorResponse("File doesn't exist");
        } else {
            process(path);
            req.sendSuccessResponse();
        }
    };

    SharingService service("com.example.mediaplayer", supportedFormats,
                           onOpenFile);
    service.start();
}