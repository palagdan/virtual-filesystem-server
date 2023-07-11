#include "test_request.h"
#include <iostream>

void testParseRequest() {
    HTTPRequest request;
    std::vector<char> req = {
        'G', 'E', 'T', ' ', '/', ' ', 'H', 'T', 'T', 'P', '/', '1', '.', '1', '\r','\n',
        'H', 'o', 's', 't', ':', ' ', 'e', 'x', 'a', 'm', 'p', 'l', 'e', '.', 'c', 'o', 'm', '\r','\n',
        'C', 'o', 'n', 't', 'e', 'n', 't', '-', 'T', 'y', 'p', 'e', ':', ' ', 't', 'e', 'x', 't', '/', 'h', 't', 'm', 'l', '\r', '\n',
        '\r', '\n',
        'B', 'o', 'd', 'y'
    };

    request.parseRequest(req);

    // Test method, path, and version
    assert(request.getStrMethod() == "GET");
    assert(request.getPath() == "/");
    assert(request.getVersion() == "HTTP/1.1");

    // Test headers
    assert(request.getHeader()["Host"] == "example.com\r");
    assert(request.getHeader()["Content-Type"] == "text/html\r");

    // Test body
    assert(request.getBody() == "Body");
}

void runRequestTests(){
    testParseRequest();
}