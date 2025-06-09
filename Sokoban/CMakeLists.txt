cmake_minimum_required(VERSION 3.31)

project(Sokoban)

set(CMAKE_CXX_STANDARD 20)


find_package(jsoncpp CONFIG REQUIRED)

add_executable(Sokoban main.cpp
        SokobanGame.cpp
        SokobanGame.h
        ui/TerminalFrame.cpp
        ui/TerminalFrame.h
        object/player.cpp
        object/player.h
        point.cpp
        point.h
        object/Box.cpp
        object/Box.h
        object/Entity.cpp
        object/Entity.h
        object/Goal.cpp
        object/Goal.h
        object/ICON.h
        object/RenderableObject.h
        PositionTracker.cpp
        PositionTracker.h
        ui/GameUi.cpp
        ui/GameUi.h
        ui/Menu/Menu.cpp
        ui/Menu/Menu.h
        ui/Menu/MenuItem.cpp
        ui/Menu/MenuItem.h
        ui/Menu/MenuManager.cpp
        ui/Menu/MenuManager.h
        KeyBoard.h
        ui/Menu/MenuMapItem.cpp
        ui/Menu/MenuMapItem.h
        GameData.h)

target_link_libraries(Sokoban PRIVATE JsonCpp::JsonCpp)
