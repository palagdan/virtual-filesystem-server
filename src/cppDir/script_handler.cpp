#include "../hppDir/script_handler.h"

void ScriptHandler::handleRequest(const HTTPRequest &request, HTTPResponse &response, const Router &router) {
    std::string url = request.getPath();
    std::string address_dir = Utils::getDirectory(url);
    std::string static_file = Utils::getStaticFile(url);
    std::string directory = router.getDirectories()[address_dir];

    std::filesystem::path fileSys = std::filesystem::current_path() / directory;
    std::string file_path = fileSys.string() + "/"  + static_file;

    if (!std::filesystem::exists(file_path)) {
        std::string err_msg = "File not found";
        response.setStatus(HTTPResponse::StatusCode::NOT_FOUND);
        response.addHeader("Content-Length", std::to_string(err_msg.size()));
        response.setBody(err_msg);
        return;
    }

    std::string extension = "." + Utils::getFileExtension(static_file);
    if(router.getScripts().find(extension) == router.getScripts().end()){
        // format unsupported
        std::string msg = "File extension to run the script is unsupported";
        response.setStatus(HTTPResponse::StatusCode::FORBIDDEN);
        response.addHeader("Content-Length", std::to_string(msg.size()));
        response.setBody(msg);
    }else{
        std::string commandTemplate = router.getScripts()[extension];
        std::string command = replaceFilepath(commandTemplate, file_path);

        std::string tempFile = fileSys.string() + "/" + "temp_output.txt";

        // Redirect the script output to the temporary file
        int timeoutInSeconds = 2; // Set the timeout value in seconds

        std::string commandWithOutputRedirect = command + " > " + tempFile;

        std::string commandWithTimeout = "timeout " + std::to_string(timeoutInSeconds) + " " + commandWithOutputRedirect;

        int result = std::system(commandWithTimeout.c_str());

        if (result == 0) {
            // Execution was successful
            std::ifstream outputFile(tempFile);
            std::string scriptOutput((std::istreambuf_iterator<char>(outputFile)), std::istreambuf_iterator<char>());
            outputFile.close();
            // Delete the temporary file
            std::remove(tempFile.c_str());
            response.setStatus(HTTPResponse::StatusCode::OK);
            response.addHeader("Content-Length", std::to_string(scriptOutput.size()));
            response.setBody(scriptOutput);
        } else {
            // Execution failed
            std::string err_msg = "File execution failed.";
            response.setStatus(HTTPResponse::StatusCode::INTERNAL_SERVER_ERROR);
            response.addHeader("Content-Length", std::to_string(err_msg.size()));
            response.setBody(err_msg);
        }
    }
}

std::string ScriptHandler::replaceFilepath(const std::string &commandTemplate, const std::string &filepath) {
    std::string command = commandTemplate;
    size_t pos = command.find("{filepath}");

    while (pos != std::string::npos) {
        command.replace(pos, 10, filepath);
        pos = command.find("{filepath}", pos + filepath.length());
    }

    return command;
}
