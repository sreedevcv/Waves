
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_library(UI
    MainWindow.cpp
    AudioChart.cpp
)

target_link_libraries(UI
    Qt6::Widgets
    Qt6::Charts
    audio
)
