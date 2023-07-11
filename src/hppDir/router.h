#pragma once
#include <string>
#include <unordered_map>
#include <stdexcept>
#include <functional>
#include "logging.h"
#include <filesystem>



/**
 * @brief Handles routing and configuration of directories for HTTP requests.
 *
 * The Router class manages the routing and configuration of directories for handling HTTP requests. It provides methods for adding and deleting directories, retrieving the list of directories, retrieving directory paths and static file paths, and configuring directories with logging settings.
 */
class Router {
public:
    /**
     * @brief Default constructor for the Router class.
     */
    Router() = default;

    /**
     * @brief Default destructor for the Router class.
     */
    ~Router() = default;

    /**
     * @brief Adds a directory to the router.
     *
     * This function adds a directory to the router with the specified URL path and corresponding directory path.
     *
     * @param urlPath The URL path associated with the directory.
     * @param directoryPath The directory path on the file system.
     */
    void addDirectory(const std::string& urlPath, const std::string& directoryPath);

    /**
     * @brief Deletes a directory from the router.
     *
     * This function deletes the directory with the specified URL path from the router.
     *
     * @param urlPath The URL path of the directory to delete.
     * @return `true` if the directory was deleted successfully, `false` otherwise.
     */
    bool deleteDirectory(const std::string& urlPath);

    /**
     * @brief Retrieves the list of directories configured in the router.
     *
     * @return The configured directories as an unordered map of URL paths and corresponding directory paths.
     */
    std::unordered_map<std::string, std::string> getDirectories() const;


    /**
     * @brief Configures the directories with logging settings.
     *
     * This function configures the directories with the specified logging settings, using a unique pointer to a Logging object.
     *
     * @param directories The directories to configure, represented as an unordered map of URL paths and corresponding directory paths.
     * @param loggingPtr A unique pointer to a Logging object for logging configuration.
     */
    void configureDirectories(const std::unordered_map<std::string, std::string>& directories, std::unique_ptr<Logging>& loggingPtr) const;

    /**
    * @brief Adds a script command for a given file extension.
    *@param extension The file extension.
    * @param command The script command to execute.
    */
    void addScript(const std::string& extension, const std::string& command);

    /**
    * @brief Retrieves the map of scripts, where the keys are file extensions and the values are corresponding commands.
    * @return The map of scripts.
    */
    std::unordered_map<std::string, std::string> getScripts() const;

    /**
    * @brief Sets whether directories are treated as private.
    * @param enablePrivate Flag indicating whether directories should be treated as private.
    */
    void setDirectoriesPrivate(const bool enablePrivate);

    /**
    * @brief Checks whether directories are treated as private.
    * @return True if directories are treated as private, false otherwise.
    */
    bool getDirectoriesPrivate() const;

private:
    std::unordered_map<std::string, std::string> m_directories; /**< The configured directories as an unordered map of URL paths and corresponding directory paths. */
    std::unordered_map<std::string, std::string> m_scripts_extensions; /**< The map of script extensions and corresponding commands. */
    bool m_directories_private; /**< Flag indicating whether directories are treated as private. */
};


