//
// Created by maks on 11.03.2026.
//

#include "Filesystem.h"

#include <nlohmann/json.hpp>

#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <utility>

const std::string Filesystem::defaultNamespace = "minecraft";

const Filesystem::AssetTypes_ Filesystem::AssetTypes = {
    .MODEL = {"models", ".json"},
    .TEXTURE = {"textures", ".png"}
};


std::optional<std::unique_ptr<std::istream>> Filesystem::open(const std::string &path) {
    if (auto ifstream = std::make_unique<std::ifstream>(path); ifstream->is_open()) return ifstream;
    return std::nullopt;
}

std::optional<std::string> Filesystem::readAsString(const std::string &path) {
    auto opt_stream = open(path);
    if (opt_stream == std::nullopt) return std::nullopt;
    const auto stream = std::move(*opt_stream);
    std::ostringstream string_stream;
    string_stream << stream->rdbuf();
    if (string_stream.fail() || stream->fail()) {
        return std::nullopt;
    }
    return string_stream.str();
}

std::optional<std::vector<char>> Filesystem::readBytes(const std::string &path) {
    auto opt_stream = open(path);
    if (opt_stream == std::nullopt) return std::nullopt;
    const auto stream = std::move(*opt_stream);
    std::vector<char> data_read{std::istreambuf_iterator(*stream), {}};
    if (stream->fail()) {
        return std::nullopt;
    }
    return data_read;
}

std::optional<nlohmann::json> Filesystem::readAsJson(const std::string &path) {
    auto opt_stream = open(path);
    if (opt_stream == std::nullopt) return std::nullopt;
    const auto stream = std::move(*opt_stream);
    nlohmann::json json = nlohmann::json::parse(*stream);
    if (stream->fail()) {
        return std::nullopt;
    }
    return json;
}

bool Filesystem::iterateFiles(const std::string &path, const std::function<void(std::string)> &on_file) {
    const std::filesystem::path fspath(path);
    for (const auto& dir : std::filesystem::directory_iterator(fspath)) {
        if (!dir.is_regular_file()) continue;
        on_file(dir.path().filename());
    }
    return true;
}

bool Filesystem::iterateFilePaths(const std::string &path, const std::function<void(std::string)> &on_file) {
    const std::filesystem::path fspath(path);
    for (const auto& dir : std::filesystem::directory_iterator(fspath)) {
        if (!dir.is_regular_file()) continue;
        on_file(dir.path().string());
    }
    return true;
}

bool Filesystem::iterateFilePaths(const std::string &path, const std::function<void(std::string, std::string)> &on_file) {
    const std::filesystem::path fspath(path);
    for (const auto& dir : std::filesystem::directory_iterator(fspath)) {
        if (!dir.is_regular_file()) continue;
        on_file(dir.path().string(), dir.path().filename());
    }
    return true;
}

std::string Filesystem::fileName(const std::string &path) {
    const auto length = path.length();
    auto last_slash = path.find_last_of('/');
    if (last_slash == std::string::npos) return path;
    bool dir = false;
    if (last_slash == length - 1) {
        dir = true;
        last_slash = path.find_last_of('/', length - 2);
    }
    return path.substr(last_slash + 1, (length - 1) - (dir ? last_slash + 1 : last_slash ));
}

std::string Filesystem::removeExtension(const std::string &name) {
    const auto last_dot = name.find_last_of('.');
    if (last_dot == std::string::npos) return name;
    return name.substr(0, last_dot);
}

std::string Filesystem::fromNamespacedPath(const std::string &path, const AssetType &asset_type, const bool withExtension) {
    const auto namespace_separator = path.find_first_of(':');
    std::string _namespace = defaultNamespace;
    std::string adjusted_path = path;
    if (namespace_separator != std::string::npos) {
        _namespace = path.substr(0, namespace_separator);
        adjusted_path = path.substr(namespace_separator + 1);
    }
    return _namespace + "/" + asset_type.directory + "/" + adjusted_path + (withExtension ? asset_type.file_extension : "");
}


std::string Filesystem::defaultify(const std::string &path) {
    if (path.find_first_of(':') != std::string::npos) return path;
    return defaultNamespace + ":" + path;
}
