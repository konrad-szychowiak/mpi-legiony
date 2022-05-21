//
// Created by konrad on 18.04.2022.
//
#pragma once

#ifndef LEGIONY_CONFIG_HPP
#define LEGIONY_CONFIG_HPP

#include "./classes/legion.hxx"

Legion *legions[] = {
    Legion::withSize(2),
    Legion::withSize(3),
    Legion::withSize(5),
    Legion::withSize(8),
};

Trail *trails[] = {
//    Trail::withMaxThroughput(3),
    Trail::withMaxThroughput(8),
    Trail::withMaxThroughput(10),
};

#endif //LEGIONY_CONFIG_HPP
