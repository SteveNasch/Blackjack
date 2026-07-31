cmake_minimum_required(VERSION 4.2)
project(Blackjack)

set(CMAKE_CXX_STANDARD 20)

add_executable(Blackjack main.cpp
        Card.cpp
        headers/Card.h
        headers/Deck.h
        Deck.cpp)
