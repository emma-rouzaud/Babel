/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** Errors
*/

#include "Errors.hpp"

#include <iostream>

namespace babel {
    BabelError::BabelError(std::string const &message) : _message(message) {}

    AudioError::AudioError(std::string const &message) : BabelError(message) {}

    CodecError::CodecError(std::string const &message) : BabelError(message) {}

    NetworkError::NetworkError(std::string const &message) : BabelError(message) {}

    GraphicalError::GraphicalError(std::string const &message) : BabelError(message) {}
}
