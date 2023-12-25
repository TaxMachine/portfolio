//
// Created by taxis on 2023-12-24.
//

#include "http.hpp"

#include <emscripten/fetch.h>

#include <iostream>

HTTPResponse HTTP::get(const HTTPRequest& request) {
    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "GET");
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.onsuccess = [](emscripten_fetch_t* fetch) {
        emscripten_fetch_close(fetch);
    };
    attr.onerror = [](emscripten_fetch_t* fetch) {
        throw std::runtime_error("Failed to fetch " + std::string(fetch->url));
        emscripten_fetch_close(fetch);
    };
    const emscripten_fetch_t* res = emscripten_fetch(&attr, request.url.c_str());

    HTTPResponse response;
    response.body = std::string(res->data, res->numBytes);
    response.status_code = res->status;
    response.headers = {};

    return response;
}

HTTPResponse HTTP::post(const HTTPRequest& request) {
    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "POST");
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.onsuccess = [](emscripten_fetch_t* fetch) {
        emscripten_fetch_close(fetch);
    };
    attr.onerror = [](emscripten_fetch_t* fetch) {
        throw std::runtime_error("Failed to fetch " + std::string(fetch->url));
        emscripten_fetch_close(fetch);
    };
    const emscripten_fetch_t* res = emscripten_fetch(&attr, request.url.c_str());

    HTTPResponse response;
    response.body = std::string(res->data, res->numBytes);
    response.status_code = res->status;
    response.headers = {};

    return {};
}