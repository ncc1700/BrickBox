//
// Created by maks on 11.03.2026.
//

#ifndef BRICKBOX_FILESYSTEM_H
#define BRICKBOX_FILESYSTEM_H
#include <istream>
#include <memory>
#include <optional>
#include <vector>
#include <functional>
#include <nlohmann/json_fwd.hpp>

class Filesystem {
public:
    static const std::string defaultNamespace;

    struct AssetType {
        const std::string directory;
        const std::string file_extension;
    };

    static const struct AssetTypes_ {
        AssetType MODEL;
        AssetType TEXTURE;
    } AssetTypes;



    // Read-write
    static std::optional<std::unique_ptr<std::istream>> open(const std::string &path);
    static std::optional<std::string> readAsString(const std::string &path);
    static std::optional<std::vector<char>> readBytes(const std::string &path);
    static std::optional<nlohmann::json> readAsJson(const std::string &path);
    static bool iterateFiles(const std::string& path, const std::function<void(std::string file_name)> &on_file);
    static bool iterateFilePaths(const std::string& path, const std::function<void(std::string file_path)> &on_file);
    static bool iterateFilePaths(const std::string& path, const std::function<void(std::string file_path, std::string file_name)> &on_file);

    // Utilities
    static std::string fileName(const std::string &path);
    static std::string removeExtension(const std::string &name);
    static std::string fromNamespacedPath(const std::string &path, const AssetType &asset_type, bool withExtension = true);
    static std::string defaultify(const std::string& path);
};


#endif //BRICKBOX_FILESYSTEM_H