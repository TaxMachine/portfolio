//
// Created by taxis on 2023-12-24.
//

#ifndef HTTP_HPP
#define HTTP_HPP

#include <string>
#include <map>

struct HTTPResponse {
    std::string body;
    int status_code;
    std::map<std::string, std::string> headers;
};

struct HTTPRequest {
    std::string url;
    std::map<std::string, std::string> headers;
};

namespace HTTP {
    HTTPResponse get(const HTTPRequest& request);
    HTTPResponse post(const HTTPRequest& request);
};

#endif //HTTP_HPP
