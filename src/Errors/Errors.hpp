/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** Errors
*/

#ifndef ERRORS_HPP_
#define ERRORS_HPP_

#include <string>
#include <exception>
 
template<class Error>
void throw_func(
    std::string msg,
    char const* file,
    char const* function,
    std::size_t line)
{
    throw Error(
        std::string(
            std::string(file) + "(" +
            std::to_string(line) + "): [" +
            std::string(function) + "] --> " +
            std::string(msg)
        )
    );
}

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define EXCEPTION(TYPE, MESSAGE) \
    throw_func<TYPE>(MESSAGE, __FILENAME__, __func__, __LINE__)

namespace babel {
    class BabelError : public std::exception {
        public:
            BabelError(std::string const &message);

            const char  *what(void) const noexcept override { return (_message.c_str()); };
            const std::string getTypeError(void) const { return std::string("Babel error"); };

        protected:
            std::string _message;
    };

    class AudioError : public BabelError {
        public:
            AudioError(std::string const &message);

            const std::string getTypeError(void) const { return std::string("Audio error"); };
    };

    class CodecError : public BabelError {
        public:
            CodecError(std::string const &message);

            const std::string getTypeError(void) const { return std::string("Codec error"); };
    };

    class NetworkError : public BabelError {
        public:
            NetworkError(std::string const &message);

            const std::string getTypeError(void) const { return std::string("Network error"); };
    };

    class GraphicalError : public BabelError {
        public:
            GraphicalError(std::string const &message);

            const std::string getTypeError(void) const { return std::string("Graphical error"); };
    };
}

#endif /* !ERRORS_HPP_ */
