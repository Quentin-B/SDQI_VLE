/**
 * @file vle/value/Map.cpp
 * @author The VLE Development Team
 * See the AUTHORS or Authors.txt file
 */

/*
 * VLE Environment - the multimodeling and simulation environment
 * This file is a part of the VLE environment
 * http://www.vle-project.org
 *
 * Copyright (C) 2003-2007 Gauthier Quesnel quesnel@users.sourceforge.net
 * Copyright (C) 2007-2010 INRA http://www.inra.fr
 * Copyright (C) 2003-2010 ULCO http://www.univ-littoral.fr
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


#include <vle/value/Map.hpp>
#include <vle/value/String.hpp>
#include <vle/value/Set.hpp>
#include <vle/value/Integer.hpp>
#include <vle/value/Double.hpp>
#include <vle/value/Boolean.hpp>
#include <vle/value/Matrix.hpp>
#include <vle/value/XML.hpp>
#include <vle/value/Deleter.hpp>
#include <vle/utils/Debug.hpp>
#include <vle/utils/Algo.hpp>
#include <boost/utility.hpp>

namespace vle { namespace value {

Map::Map(const Map& orig)
    : Value(orig)
{
    for (const_iterator it = orig.m_value.begin(); it != orig.m_value.end();
         ++it) {
        if ((*it).second) {
            m_value.insert(std::make_pair((*it).first,
                                          ((*it).second)->clone()));
        } else {
            m_value.insert(std::make_pair((*it).first, (value::Value*)0));
        }
    }
}

void Map::writeFile(std::ostream& out) const
{
    for (const_iterator it = m_value.begin(); it != m_value.end(); ++it) {
        if (it != m_value.begin()) {
            out << " ";
        }
        out << "(" << (*it).first.c_str() << ", ";
        (*it).second->writeFile(out);
        out << ")";
    }
}

void Map::writeString(std::ostream& out) const
{
    for (const_iterator it = m_value.begin(); it != m_value.end(); ++it) {
        if (it != m_value.begin()) {
            out << " ";
        }
        out << "(" << (*it).first.c_str() << ", ";
        (*it).second->writeString(out);
        out << ")";
    }
}

void Map::writeXml(std::ostream& out) const
{
    out << "<map>";

    for (const_iterator it = m_value.begin(); it != m_value.end(); ++it) {
        out << "<key name=\"" << (*it).first.c_str() << "\">";
        (*it).second->writeXml(out);
        out << "</key>";
    }
    out << "</map>";
}

Matrix& Map::addMatrix(const std::string& name)
{
    value::Matrix* value = new Matrix();

    add(name, value);

    return *value;
}

Set& Map::addSet(const std::string& name)
{
    value::Set* value = new Set();

    add(name, value);

    return *value;
}

Map& Map::addMap(const std::string& name)
{
    value::Map* value = new Map();

    add(name, value);

    return *value;
}

const Value* Map::operator[](const std::string& name) const
{
    const_iterator it = m_value.find(name);

    if (it == m_value.end()) {
        throw utils::ArgError(fmt(_(
                "Map: the key '%1%' does not exist")) % name);
    }

    return it->second;
}

Value* Map::operator[](const std::string& name)
{
    iterator it = m_value.find(name);

    if (it == m_value.end()) {
        throw utils::ArgError(fmt(_(
                "Map: the key '%1%' does not exist")) % name);
    }

    return it->second;
}

Value* Map::give(const std::string& name)
{
    iterator it = m_value.find(name);

    if (it == m_value.end()) {
        throw utils::ArgError(fmt(_(
                "Map: the key '%1%' does not exist")) % name);
    }

    Value* result = it->second;
    it->second = 0;
    m_value.erase(it);

    return result;
}

const Map& Map::getMap(const std::string& name) const
{
    return value::toMapValue(value::reference(get(name)));
}

const Set& Map::getSet(const std::string& name) const
{
    return value::toSetValue(value::reference(get(name)));
}

const Matrix& Map::getMatrix(const std::string& name) const
{
    return value::toMatrixValue(value::reference(get(name)));
}

Map& Map::getMap(const std::string& name)
{
    return value::toMapValue(value::reference(get(name)));
}

Set& Map::getSet(const std::string& name)
{
    return value::toSetValue(value::reference(get(name)));
}

Matrix& Map::getMatrix(const std::string& name)
{
    return value::toMatrixValue(value::reference(get(name)));
}

void Map::clear()
{
    std::stack < Value* > composite;

    for (iterator it = begin(); it != end(); ++it) {
        if (it->second) {
            if (isComposite(it->second)) {
                composite.push(it->second);
            } else {
                delete it->second;
            }
            it->second = 0;
        }
    }

    m_value.clear();
    deleter(composite);
}

Value* Map::getPointer(const std::string& name)
{
    iterator it = m_value.find(name);
    return it == m_value.end() ? 0 : it->second;
}

const Value* Map::getPointer(const std::string& name) const
{
    const_iterator it = m_value.find(name);
    return it == m_value.end() ? 0 : it->second;
}

}} // namespace vle value

