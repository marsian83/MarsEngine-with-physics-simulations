
#pragma once
#ifndef NAMEOF_H_20180129_123322
#define NAMEOF_H_20180129_123322


#define nameof(x) bravikov::_nameof<0>(#x, sizeof(x))


#include <string>
#include <regex>
#include <stdexcept>

namespace bravikov {
    template<int a>
    std::string _nameof(const std::string &x, std::size_t)
    {
        std::regex regex("^&?([_a-zA-Z]\\w*(->|\\.|::))*([_a-zA-Z]\\w*)$");
        std::smatch match;
        if (std::regex_match(x, match, regex)) {
            if (match.size() == 4) {
                return match[3];
            }
        }
        throw std::logic_error(
            "A bad expression x in nameof(x). The expression is \"" + x + "\"."
        );
    }
}

#endif /* #ifndef NAMEOF_H_20180129_123322 */