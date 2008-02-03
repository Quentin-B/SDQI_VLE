/**
 * @file vle/oov/PluginFactory.hpp
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


#ifndef VLE_OOV_PLUGINFACTORY_HPP
#define VLE_OOV_PLUGINFACTORY_HPP

#include <boost/noncopyable.hpp>
#include <glibmm/module.h>
#include <vle/oov/Plugin.hpp>
#include <string>



namespace vle { namespace oov {

    /**
     * @brief Plugin factory is use to build reference to the
     * Plugin load dynamically from the dynamics libraries.
     *
     */
    class PluginFactory
    {
    public:
        /**
         * @brief Constructor to load plugin from pathname.
         * @param plugin the name of the plugin to load.
         * @param pathname the name of the path where the plugin is.
         * @throw utils::InternalError if the plugin does not exist
         * in the pathname.
         */
        PluginFactory(const std::string& plugin,
                      const std::string& pathname);

        ~PluginFactory();

        PluginPtr build(const std::string& location);

    private:
        Glib::Module*   m_module;
        std::string     m_plugin;
    };

}} // namespace vle oov

#endif