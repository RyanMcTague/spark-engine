include(FetchContent)

#set(MONO_ROOT "${CMAKE_SOURCE_DIR}/vendor/mono")
#set(ENV{PKG_CONFIG_PATH} "${MONO_ROOT}/lib/pkgconfig")
#set(ENV{PATH} ${MONO_ROOT}/bin:$ENV{PATH})
#message(NOTICE ${MONO_ROOT})
#include(FindPkgConfig)
#pkg_search_module(Mono REQUIRED "mono-2")
#
#if (Mono_FOUND)
#    mark_as_advanced(Mono_FOUND Mono_CFLAGS Mono_STATIC_LDFLAGS)
#    find_package_handle_standard_args(Mono Mono_FOUND Mono_CFLAGS Mono_STATIC_LDFLAGS)
#else ()
#    message(FATAL_ERROR "Cannot find mono")
#endif ()

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG        e2c92645460f680fd272fd2eed591efb2be7dc31
        GIT_PROGRESS   TRUE
)

FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
    FetchContent_Populate(glfw)

    set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
    set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
    set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
    set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")

    add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()

FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG        7c02e204c92545f869e2f04edaab1f19fe8b19fd
        GIT_PROGRESS   TRUE
)

FetchContent_GetProperties(spdlog)
if(NOT spdlog_POPULATED)
    FetchContent_Populate(spdlog)
    set(SPDLOG_BUILD_EXAMPLE OFF CACHE INTERNAL "Build example")
    set(SPDLOG_INSTALL OFF CACHE INTERNAL "Generate the install target")
    set(SPDLOG_FMT_EXTERNAL ON CACHE INTERNAL "Use external fmt library instead of bundled")

    add_subdirectory(${spdlog_SOURCE_DIR} ${spdlog_BINARY_DIR})
endif()

FetchContent_Declare(
        pugixml
        GIT_REPOSITORY https://github.com/zeux/pugixml.git
        GIT_TAG        db78afc2b7d8f043b4bc6b185635d949ea2ed2a8
        GIT_PROGRESS   TRUE
)

FetchContent_GetProperties(pugixml)
if(NOT pugixml_POPULATED)
    FetchContent_Populate(pugixml)
    add_subdirectory(${pugixml_SOURCE_DIR} ${pugixml_BINARY_DIR})
endif()

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/icaven/glm.git
        GIT_TAG        82f86a8057c169ae0d6c939dfa148970e97d6693
        GIT_PROGRESS   TRUE
)

FetchContent_GetProperties(glm)
if(NOT glm_POPULATED)
    FetchContent_Populate(glm)
endif()

FetchContent_Declare(
        nfd
        GIT_REPOSITORY https://github.com/btzy/nativefiledialog-extended.git
        GIT_TAG        5786fabceeaee4d892f3c7a16b243796244cdddc
        GIT_PROGRESS   TRUE
)

FetchContent_GetProperties(nfd)
if(NOT nfd_POPULATED)
    FetchContent_Populate(nfd)
    add_subdirectory(${nfd_SOURCE_DIR} ${nfd_BINARY_DIR})
endif()

FetchContent_Declare(
        SQLiteCpp
        GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
        GIT_TAG        fe6086c12679d8744c02fa03e83e75feca2413d8
        GIT_PROGRESS   TRUE
)

FetchContent_GetProperties(SQLiteCpp)
if(NOT SQLiteCpp_POPULATED)
    FetchContent_Populate(SQLiteCpp)
endif()

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG        9cca280a4d0ccf0c08f47a99aa71d1b0e52f8d03
        GIT_PROGRESS   TRUE
)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR})
endif()

FetchContent_Declare(
        stduuid
        GIT_REPOSITORY https://github.com/mariusbancila/stduuid.git
        GIT_TAG        3afe7193facd5d674de709fccc44d5055e144d7a
        GIT_PROGRESS   TRUE
)

FetchContent_GetProperties(stduuid)
if(NOT stduuid_POPULATED)
    FetchContent_Populate(stduuid)
endif()


