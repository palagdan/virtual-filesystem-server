#include "../hppDir/request_handler.h"

RequestHandler::RequestHandler(HTTPRequest request) : m_request(request){

}

HTTPResponse RequestHandler::handlerRequest(const Router & router)  {
    std::string url = m_request.getPath();
    std::string method = m_request.getStrMethod();
    std::string address_dir = Utils::getDirectory(url);
    std::string static_file = Utils::getStaticFile(url);
    HTTPResponse response;
    if(router.getDirectories().find(address_dir) == router.getDirectories().end()){
        // not found
        m_handler = std::make_unique<UndefinedPathHandler>();
        m_handler->handleRequest(m_request, response, router);
        return response;
    }
    if(static_file.empty()){
        std::string directory = router.getDirectories()[address_dir];
        m_handler = std::make_unique<DirectoryHandler>();
        m_handler->handleRequest(m_request, response, router);
    }else{
        if(m_request.getStrMethod() == "POST"){
            m_handler = std::make_unique<ScriptHandler>();
            m_handler->handleRequest(m_request, response, router);
        }else{
            m_handler = std::make_unique<StaticFileHandler>();
            m_handler->handleRequest(m_request, response, router);
        }
    }
    return response;
}

