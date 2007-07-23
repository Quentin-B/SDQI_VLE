/** 
 * @file Text.cpp
 * @brief 
 * @author The vle Development Team
 * @date lun, 23 jui 2007 11:48:34 +0200
 */

/*
 * Copyright (C) 2007 - The vle Development Team
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include <vle/oov/plugins/Text.hpp>



namespace vle { namespace oov { namespace plugin {

Text::Text(const std::string& location) :
    Plugin(location)
{
    m_file.open(location.c_str());
    if (not m_file.is_open()) {
        Throw(utils::InternalError, boost::format(
                "Cannot open file %1%") % location);
    }
}

Text::~Text()
{
    m_file.close();
}

void Text::onParameter(const vpz::ParameterTrame& /* trame */)
{
}

void Text::onNewObservable(const vpz::NewObservableTrame& trame)
{
    flush(utils::to_double(trame.time()));

    Assert(utils::InternalError, m_columns.find(trame.name()) == m_columns.end(),
           boost::format("Observable %1% already exist") % trame.name());

    m_columns[trame.name()] = m_buffer.size();
    m_buffer.push_back(value::Value());
}

void Text::onDelObservable(const vpz::DelObservableTrame& trame)
{
    flush(utils::to_double(trame.time()));
}

void Text::onValue(const vpz::ValueTrame& trame)
{
    flush(utils::to_double(trame.time()));

    for (vpz::ModelTrameList::const_iterator it = trame.trames().begin();
         it != trame.trames().end(); ++it) {

        std::map < std::string, int >::iterator jt;
        jt = m_columns.find(it->simulator());

        Assert(utils::InternalError, jt != m_columns.end(), boost::format(
                "The columns %1% does not exist. No new Observable ?") % 
            it->simulator());

        m_buffer[jt->second] = it->value();
    }
}

void Text::close()
{
    m_file << "# ";
    std::map < std::string, int >::iterator it = m_columns.begin();
    while (it != m_columns.end()) {
        m_file << it->first;
        it++;

        if (it != m_columns.end()) {
            m_file << '\t';
        }
    }
    m_file << '\n' << std::flush;
}

void Text::flush(double trame_time)
{
    if (trame_time != m_time) {
        std::vector < value::Value >::iterator it;
        for (it = m_buffer.begin(); it != m_buffer.end(); ++it) {
            if ((*it).get()) {
                m_file << (*it)->toString();
            } else {
                m_file << "NA";
            }

            if (it + 1 != m_buffer.end()) {
                m_file << '\t';
            }
            (*it).reset();
        }
        m_file << '\n' << std::flush;
    }
    m_time = trame_time;
}

}}} // namespace vle oov plugin