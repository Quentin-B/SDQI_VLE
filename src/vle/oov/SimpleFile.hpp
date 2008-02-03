/**
 * @file vle/oov/SimpleFile.hpp
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


#ifndef VLE_OOV_SIMPLEFILE_HPP
#define VLE_OOV_SIMPLEFILE_HPP

#include <vle/oov/Plugin.hpp>
#include <fstream>
#include <map>
#include <vector>



namespace vle { namespace oov { namespace plugin {

    class SimpleFile : public Plugin
    {
    public:
        SimpleFile(const std::string& location);

        virtual ~SimpleFile();

        virtual void onParameter(const vpz::ParameterTrame& trame);

        virtual void onNewObservable(const vpz::NewObservableTrame& trame);

        virtual void onDelObservable(const vpz::DelObservableTrame& trame);

        virtual void onValue(const vpz::ValueTrame& trame);

        virtual void close(const vpz::EndTrame& trame);

        virtual std::string extension() const = 0;

        virtual void writeSeparator(std::ostream& out) = 0;

        virtual void writeHead(std::ostream& out,
                               const std::vector < std::string >& heads) = 0;


    private:
        std::map < std::string, int >   m_columns;
        std::vector < value::Value >    m_buffer;
        double                          m_time;
        std::ofstream                   m_file;
        std::string                     m_filename;
        std::string                     m_filenametmp;
        bool                            m_isstart;


        void flush(double trame_time);

        void finalFlush(double trame_time);

        /**
         * @brief This function is use to build uniq name to each row of the
         * text output.
         * @param simulator the name of the devs::Model.
         * @param port the name of the state port of the devs::Model.
         * @return a representation of the uniq name.
         */
        inline std::string buildname(const std::string& simulator,
                                     const std::string& port);
    };

    std::string SimpleFile::buildname(const std::string& simulator,
                                      const std::string& port)
    {
        std::string result(simulator);
        result += '_';
        result += port;
        return result;
    }

}}} // namespace vle oov plugin

#endif