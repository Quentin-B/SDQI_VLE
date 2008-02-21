/**
 * @file src/vle/value/Map.cpp
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




#include <vle/value/Map.hpp>
#include <vle/value/String.hpp>
#include <vle/value/Set.hpp>
#include <vle/value/Integer.hpp>
#include <vle/value/Double.hpp>
#include <vle/value/Boolean.hpp>
#include <vle/utils/Debug.hpp>



namespace vle { namespace value {

MapFactory::MapFactory(const MapFactory& mapfactory) :
    ValueBase(mapfactory)
{
    for (MapValue::const_iterator it = mapfactory.m_value.begin();
         it != mapfactory.m_value.end(); ++it) {
        m_value[(*it).first] = CloneValue()((*it).second);
    }
}

Map MapFactory::create()
{
    return Map(new MapFactory());
}

Value MapFactory::clone() const
{
    return Value(new MapFactory(*this));
}

Value MapFactory::getValue(const std::string& name) const
{
    MapValue::const_iterator it = m_value.find(name);

    Assert(utils::ArgError, it != m_value.end(),
           boost::format("Map Value have no value name '%1%'\n") %
           name);

    return (*it).second;
}

const std::string& MapFactory::getStringValue(const std::string& name) const
{
    return value::toString(getValue(name));
}
    
bool MapFactory::getBooleanValue(const std::string& name) const
{
    return value::toBoolean(getValue(name));
}
    
long MapFactory::getLongValue(const std::string& name) const
{
    return value::toLong(getValue(name));
}

int MapFactory::getIntValue(const std::string& name) const
{
    return value::toInteger(getValue(name));
}
    
double MapFactory::getDoubleValue(const std::string& name) const
{
    return value::toDouble(getValue(name));
}
    
Map MapFactory::getMapValue(const std::string& name) const
{
    return value::toMapValue(getValue(name));
}
    
Set MapFactory::getSetValue(const std::string& name) const
{
    return value::toSetValue(getValue(name));
}

void MapFactory::clear()
{
    m_value.clear();
}
    
std::string MapFactory::toFile() const
{
    std::string s;
    MapValue::const_iterator it = m_value.begin();

    while (it != m_value.end()) {
        s += "(";
        s += (*it).first;
        s += ", ";
        s += (*it).second->toFile();
        s += ")";
        ++it;
        if (it != m_value.end()) {
            s += " ";
        }
    }
    return s;
}

std::string MapFactory::toString() const
{
    std::string s;
    MapValue::const_iterator it = m_value.begin();

    while (it != m_value.end()) {
        s += "(";
        s += (*it).first;
        s += ", ";
        s += (*it).second->toString();
        s += ")";
        ++it;
        if (it != m_value.end()) {
            s += " ";
        }
    }
    return s;
}

std::string MapFactory::toXML() const
{
    std::string s="<map>";
    MapValue::const_iterator it = m_value.begin();

    while (it != m_value.end()) {
        s += "<key name=\"";
        s += (*it).first;
        s += "\">";
        s += (*it).second->toXML();
        s += "</key>";
	++it;
    }
    s += "</map>";
    return s;
}

Map toMapValue(const Value& value)
{
    Assert(utils::InternalError, value->getType() == ValueBase::MAP,
           "Value is not a Map");
    return boost::static_pointer_cast < MapFactory >(value);
}

const MapValue& toMap(const Value& value)
{
    Assert(utils::InternalError, value->getType() == ValueBase::MAP,
           "Value is not a Map");
    return boost::static_pointer_cast < MapFactory >(value)->getValue();
}

}} // namespace vle value
