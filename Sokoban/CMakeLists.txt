cmake_minimum_required(VERSION 3.31)
project(Sokoban)

set(CMAKE_CXX_STANDARD 20)

add_executable(Sokoban main.cpp
        SokobanGame.cpp
        SokobanGame.h

        TerminalFrame.cpp
        TerminalFrame.h
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
        ui/GameUi.h)
