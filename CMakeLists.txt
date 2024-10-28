cmake_minimum_required(VERSION 3.16)
project(nwt4 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets PrintSupport LinguistTools)

file(GLOB SOURCES CONFIGURE_DEPENDS
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

file(GLOB HEADERS CONFIGURE_DEPENDS
        "${PROJECT_SOURCE_DIR}/include/*.h"
)

if(WIN32)
    file(GLOB PLATFORM_SOURCES CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/platform/windows/*.cpp")
    file(GLOB PLATFORM_HEADERS CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/platform/windows/*.h")
elseif(UNIX AND NOT APPLE)
    file(GLOB PLATFORM_SOURCES CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/platform/linux/*.cpp")
    file(GLOB PLATFORM_HEADERS CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/platform/linux/*.h")
endif()

list(APPEND SOURCES ${PLATFORM_SOURCES})
list(APPEND HEADERS ${PLATFORM_HEADERS})

qt6_wrap_cpp(HEADERS_MOC ${HEADERS})
qt6_add_resources(RESOURCES resources/images.qrc)

file(GLOB TS_FILES CONFIGURE_DEPENDS translations/*.ts)

add_executable(nwt4
        ${SOURCES}
        ${HEADERS_MOC}
        ${RESOURCES}
)

qt6_add_translations(nwt4
        INCLUDE_DIRECTORIES
        ${PROJECT_SOURCE_DIR}
        TS_FILES
        ${TS_FILES}
)

target_include_directories(nwt4 PRIVATE include)
if(WIN32)
    target_include_directories(nwt4 PRIVATE "${PROJECT_SOURCE_DIR}/include/platform/windows")
elseif(UNIX AND NOT APPLE)
    target_include_directories(nwt4 PRIVATE "${PROJECT_SOURCE_DIR}/include/platform/linux")
endif()

target_link_libraries(nwt4 Qt6::Widgets Qt6::PrintSupport)


if (WIN32)
    install(FILES
            "${Qt6_DIR}/../../../bin/Qt6Core.dll"
            "${Qt6_DIR}/../../../bin/Qt6Gui.dll"
            "${Qt6_DIR}/../../../bin/Qt6Gui.dll"
            "${Qt6_DIR}/../../../bin/Qt6Widgets.dll"
            "${Qt6_DIR}/../../../bin/Qt6PrintSupport.dll"
            "${Qt6_DIR}/../../../bin/libgcc_s_seh-1.dll"
            "${Qt6_DIR}/../../../bin/libstdc++-6.dll"
            "${Qt6_DIR}/../../../bin/libwinpthread-1.dll"
            DESTINATION .
    )
    install(FILES
            "${Qt6_DIR}/../../../plugins/platforms/qwindows.dll"
            DESTINATION platforms
    )
    install(FILES "LICENSE" "README.md" "nwt4.ico" DESTINATION .)
    install(TARGETS nwt4 DESTINATION .)
elseif (UNIX AND NOT APPLE)
    set(APP_ICON_SOURCE "${CMAKE_SOURCE_DIR}/nwt4.png")
    set(APP_ICON_DESTINATION "share/icons/hicolor/48x48/apps")

    install(FILES ${APP_ICON_SOURCE} DESTINATION ${APP_ICON_DESTINATION})

    configure_file(${CMAKE_SOURCE_DIR}/linnwt4.desktop.in
            ${CMAKE_BINARY_DIR}/linnwt4.desktop @ONLY)
    install(FILES ${CMAKE_BINARY_DIR}/linnwt4.desktop
            DESTINATION share/applications)

    install(FILES "LICENSE" "README.md" DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/${CMAKE_PROJECT_NAME}")
    install(TARGETS nwt4 DESTINATION bin)
endif()

set(CPACK_PACKAGE_VERSION "4.11.11")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Spectrumanalyser for NWT and m35-4400m Boards")
set(CPACK_PACKAGE_DESCRIPTION "Spectrumanalyser, Graphmanager, Frequency Synthesiser for NWT and m35-4400m SA Boards")
set(CPACK_PACKAGE_VENDOR "chrisabit-it")
set(CPACK_PACKAGE_CONTACT "chrisabit-it@posteo.de")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")

if (WIN32)
    set(CPACK_PACKAGE_NAME "winnwt4")
    set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-win64")
    set(CPACK_PACKAGE_INSTALL_DIRECTORY "WinNWT4")
    set(CPACK_NSIS_DISPLAY_NAME "WinNWT4")
    set(CPACK_NSIS_MODIFY_PATH OFF)
    set(CPACK_NSIS_INSTALLED_ICON_NAME "${PROJECT_SOURCE_DIR}/nwt4.ico")
    set(CPACK_NSIS_MUI_ICON "${PROJECT_SOURCE_DIR}/nwt4.ico")
    set(CPACK_NSIS_MUI_UNIICON "${PROJECT_SOURCE_DIR}/nwt4.ico")
    set(CPACK_NSIS_CREATE_ICONS_EXTRA
            "CreateShortCut '$DESKTOP\\\\WinNWT4.lnk' '$INSTDIR\\\\nwt4.exe' '' '$INSTDIR\\\\nwt4.ico'"
    )
    set(CPACK_NSIS_CONTACT "chrisabit-it@posteo.de")
    set(CPACK_GENERATOR "NSIS")
elseif (UNIX AND NOT APPLE)
    set(CPACK_PACKAGE_NAME "linnwt4")
    set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-amd64")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "chrisabit")
    set(CPACK_DEBIAN_PACKAGE_SECTION "hamradio")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "qt6-base-dev")
    set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
    set(CPACK_DEBIAN_ARCHITECTURE "amd64")
    set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")
    set(CPACK_GENERATOR "DEB")
endif()

include(CPack)