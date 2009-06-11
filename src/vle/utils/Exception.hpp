/**
 * @file vle/utils/Exception.hpp
 * @author The VLE Development Team
 */

/*
 * VLE Environment - the multimodeling and simulation environment
 * This file is a part of the VLE environment (http://vle.univ-littoral.fr)
 * Copyright (C) 2003 - 2008 The VLE Development Team
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef UTILS_EXCEPTION_HPP
#define UTILS_EXCEPTION_HPP

#include <string>
#include <exception>
#include <stdexcept>
#include <boost/format.hpp>
#include <vle/utils/i18n.hpp>



namespace vle { namespace utils {

    /**
     * @brief Base class to manage exception in VLE application.
     *
     */
    class BaseError : public std::runtime_error
    {
    public:
        explicit BaseError(const std::string& argv = std::string())
            : std::runtime_error(argv) {}

        explicit BaseError(const boost::format& argv)
            : std::runtime_error(argv.str()) {}
    };

    /**
     * @brief Throw to report a bad file access (read, write, open).
     *
     */
    class FileError : public BaseError
    {
    public:
        explicit FileError(const std::string& argv = std::string())
            : BaseError(argv) {}

        explicit FileError(const boost::format& argv)
            : BaseError(argv) {}
    };

    /**
     * @brief Throw to report a bad XML file parsing.
     *
     */
    class ParseError : public BaseError
    {
    public:
        explicit ParseError(const std::string& argv = std::string())
            : BaseError(argv) {}

        explicit ParseError(const boost::format& argv)
            : BaseError(argv) {}
    };

    /**
     * @brief Throw to report a bad parameter.
     *
     */
    class ArgError : public BaseError
    {
    public:
        explicit ArgError(const std::string& argv = std::string())
            : BaseError(argv) {}

        explicit ArgError(const boost::format& argv)
            : BaseError(argv) {}
    };

    /**
     * @brief Throw to report a bad parameter.
     *
     */
    class CastError : public BaseError
    {
    public:
        explicit CastError(const std::string& argv = std::string())
            : BaseError(argv) {}

        explicit CastError(const boost::format& argv)
            : BaseError(argv) {}
    };

    /**
     * @brief Throw to report an internal error.
     *
     */
    class InternalError : public BaseError
    {
    public:
        explicit InternalError(const std::string& argv = std::string())
            : BaseError(argv) {}

        explicit InternalError(const boost::format& argv)
            : BaseError(argv) {}
    };

    /**
     * @brief Throw to report an modelling error.
     */
    class ModellingError : public BaseError
    {
    public:
        explicit ModellingError(const std::string& argv = std::string())
            : BaseError(argv) {}

        explicit ModellingError(const boost::format& argv)
            : BaseError(argv) {}
    };

    /**
     * @brief Throw to report an unimplemted feature.
     */
    class NotYetImplemented : public BaseError
    {
    public:
        explicit NotYetImplemented(const std::string& argv = std::string())
            : BaseError(argv) {}

        explicit NotYetImplemented(const boost::format& argv)
            : BaseError(argv) {}
    };

    /**
     * @brief Throw to report a DEVS graph library error.
     */
    class DevsGraphError : public BaseError
    {
    public:
        explicit DevsGraphError(const std::string& argv = std::string())
            : BaseError(argv) {}

        explicit DevsGraphError(const boost::format& argv)
            : BaseError(argv) {}
    };

    class VpzError : public BaseError
    {
    public:
        explicit VpzError(const std::string& argv = std::string())
            : BaseError(argv) {}

        explicit VpzError(const boost::format& argv)
            : BaseError(argv) {}
    };

    /**
     * @brief Throw to report an error in SaxParser.
     */
    class SaxParserError : public BaseError
    {
    public:
        explicit SaxParserError(const std::string& argv = std::string())
            : BaseError(argv) {}

        explicit SaxParserError(const boost::format& argv)
            : BaseError(argv) {}
    };

}} // namespace vle utils

#endif
