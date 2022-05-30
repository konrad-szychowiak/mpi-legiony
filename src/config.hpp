//
// Created by konrad on 18.04.2022.
//
#pragma once

#ifndef LEGIONY_CONFIG_HPP
#define LEGIONY_CONFIG_HPP

#include "./classes/legion.hxx"

Legion *legions[] = {
    Legion::withSize(7),
    Legion::withSize(6),
    Legion::withSize(5),
    Legion::withSize(8),
};

Trail *trails[] = {
//    Trail::withMaxThroughput(3),
    Trail::withMaxThroughput(8),
    Trail::withMaxThroughput(10),
};

#endif //LEGIONY_CONFIG_HPP
