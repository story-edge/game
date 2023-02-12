cmake_minimum_required(VERSION 3.16)
project(game)

set(CMAKE_CXX_STANDARD 14)

add_executable(game main.cpp chess.hpp blackChess.hpp whileChess.hpp
        chessBoard.hpp player.hpp whilePlayer.hpp blackPlayer.hpp
        keyHandle.hpp  cursor.hpp judge.hpp winLogo.hpp goBan.hpp
        networkPlayer.hpp networkPlayer.hpp)
