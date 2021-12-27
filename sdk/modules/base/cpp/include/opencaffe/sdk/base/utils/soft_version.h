/**********************************************************************************************************************
 * Licensed under the Apache License, Version 2.0 (the "License");                                                    *
 * you may not use this file except in compliance with the License.                                                   *
 * You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0                                 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed   *
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.                      *
 * See the License for the specific language governing permissions and limitations under the License.                 *
 **********************************************************************************************************************/

#ifndef OPENCAFFE_SDK_BASE_SOFTWARE_INFO_H
#define OPENCAFFE_SDK_BASE_SOFTWARE_INFO_H

#include <string>

namespace OpenCaffe {

/// @brief Stores information about the version of the software
struct SoftwareInfo {
    /// @brief Supported version suffixes
    enum class VersionSuffix { NONE = 0, DEV = 1 };

    /// @brief Backward-compatible constructor
    ///
    /// @param version_major Major version number
    /// @param version_minor Minor version number
    /// @param version_patch Patch version number
    /// @param version_suffix_type Version suffix type
    /// @param vcs_branch VCS branch name
    /// @param vcs_commit VCS commit's hash
    /// @param vcs_date VCS commit's date
    // clang-format off
    [[deprecated("SoftwareInfo(int, int, int, int, const std::string&, const std::string&, const std::string&) is "
                 "deprecated since version 2.3.0 and will be removed in later releases.")]]
    SoftwareInfo(int version_major, int version_minor, int version_patch, int version_suffix_type,
                 const std::string &vcs_branch, const std::string &vcs_commit, const std::string &vcs_date);
    // clang-format on

    /// @brief Constructor
    ///
    /// @param version_major Major version number
    /// @param version_minor Minor version number
    /// @param version_patch Patch version number
    /// @param version_suffix_string Version suffix string
    /// @param vcs_branch VCS branch name
    /// @param vcs_commit VCS commit's hash
    /// @param vcs_date VCS commit's date
    SoftwareInfo(int version_major, int version_minor, int version_patch, const std::string &version_suffix_string,
                 const std::string &vcs_branch, const std::string &vcs_commit, const std::string &vcs_date);

    /// @brief Returns major version number
    int get_version_major() const;

    /// @brief Returns minor version number
    int get_version_minor() const;

    /// @brief Returns patch version number
    int get_version_patch() const;

    /// @brief Returns version suffix type
    // clang-format off
    [[deprecated("SoftwareInfo::get_version_dev() is deprecated since version 2.3.0 and will be removed in later "
                 "releases.")]]
    int get_version_dev() const;
    // clang-format on

    /// @brief Returns version suffix string
    std::string get_version_suffix() const;

    /// @brief Returns version as a string
    std::string get_version() const;

    /// @brief Returns version control software (vcs) branch
    std::string get_vcs_branch() const;

    /// @brief Returns version control software (vcs) commit
    std::string get_vcs_commit() const;

    /// @brief Returns version control software (vcs) commit's date
    std::string get_vcs_date() const;

private:
    /// Major version number
    int version_major_;

    /// Minor version number
    int version_minor_;

    /// Patch version number
    int version_patch_;

    /// Version suffix
    int version_suffix_type_;

    /// VCS branch
    std::string vcs_branch_;

    /// VCS commit
    std::string vcs_commit_;

    /// VCS commit's date
    std::string vcs_date_;
};

/// @brief return opencaffe software information
SoftwareInfo &get_opencaffe_software_info();

} // namespace OpenCaffe

#endif // OPENCAFFE_SDK_BASE_SOFTWARE_INFO_H
