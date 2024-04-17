project(SongPlayer VERSION 1.0 LANGUAGES CXX)

set(EXEC_NAME app${PROJECT_NAME})

set(CXX_SOURCE_FILES
    main.cpp
    PlayerController.hpp PlayerController.cpp
    AudioInfo.hpp AudioInfo.cpp
)
set(QML_SOURCE_FILES
    Main.qml
    ImageButton.qml
    AudioInfoBox.qml
    PlaylistPanel.qml
)
set(RESOURCE_FILES
    Assets/Audio/air_on_the_g_string.mp3
    Assets/Audio/eine_kleine_nachtmusik.mp3
    Assets/Audio/symphony_no_5.mp3
    Assets/Audio/reprezentuje_biede.mp3

    Assets/Icons/app_icon.ico
    Assets/Icons/next_icon.png
    Assets/Icons/pause_icon.png
    Assets/Icons/play_icon.png
    Assets/Icons/previous_icon.png
    Assets/Icons/menu_icon.png
    Assets/Icons/add_icon.png
    Assets/Icons/trash_icon.png

    Assets/Images/song_1.jpg
    Assets/Images/song_2.jpg
    Assets/Images/song_3.jpg

    Assets/Videos/video_1.avi
)

qt_add_executable(${EXEC_NAME})
qt_add_qml_module(${EXEC_NAME}
    URI ${PROJECT_NAME}
    VERSION ${PROJECT_VERSION}
    SOURCES ${CXX_SOURCE_FILES}
    QML_FILES ${QML_SOURCE_FILES}
)
qt_add_resources(${EXEC_NAME} "resources"
    PREFIX "/"
    FILES ${RESOURCE_FILES}
)

target_link_libraries(${EXEC_NAME} PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::Multimedia
)

set_target_properties(${EXEC_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER com.refraction.${PROJECT_NAME}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS ${EXEC_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
