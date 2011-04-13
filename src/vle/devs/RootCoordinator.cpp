/*
 * @file vle/devs/RootCoordinator.cpp
 *
 * This file is part of VLE, a framework for multi-modeling, simulation
 * and analysis of complex dynamical systems
 * http://www.vle-project.org
 *
 * Copyright (c) 2003-2007 Gauthier Quesnel <quesnel@users.sourceforge.net>
 * Copyright (c) 2003-2010 ULCO http://www.univ-littoral.fr
 * Copyright (c) 2007-2010 INRA http://www.inra.fr
 *
 * See the AUTHORS or Authors.txt file for copyright owners and contributors
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


#include <vle/devs/RootCoordinator.hpp>
#include <vle/devs/Coordinator.hpp>
#include <vle/devs/ModelFactory.hpp>
#include <vle/devs/Dynamics.hpp>
#include <vle/devs/ExternalEvent.hpp>
#include <vle/devs/Time.hpp>
#include <vle/utils/Rand.hpp>
#include <vle/graph/Model.hpp>
#include <cmath>

namespace vle { namespace devs {

RootCoordinator::RootCoordinator(const utils::ModuleManager& modulemgr)
    : m_rand(0), m_begin(0), m_currentTime(0), m_end(1.0), m_coordinator(0),
    m_root(0), m_modulemgr(modulemgr)
{
}

RootCoordinator::~RootCoordinator()
{
    delete m_coordinator;
    delete m_root;
}

void RootCoordinator::load(const vpz::Vpz& io)
{
    if (m_coordinator) {
        delete m_coordinator;
        delete m_root;
    }

    if (io.project().model().atomicModels().empty()) {
        throw utils::ArgError(_("RootCoordinator: no atomic model in this"
                                " vpz"));
    }

    m_rand.seed(io.project().experiment().seed());
    m_begin = io.project().experiment().begin();
    m_end = m_begin + io.project().experiment().duration();
    m_currentTime = m_begin;

    m_coordinator = new Coordinator(m_modulemgr,
                                    io.project().dynamics(),
                                    io.project().classes(),
                                    io.project().experiment(),
                                    io.project().model().atomicModels(),
                                    *this);

    m_coordinator->init(io.project().model(), m_currentTime, m_end);

    m_root = io.project().model().model();
}

void RootCoordinator::init()
{
    m_currentTime = m_begin;
}

bool RootCoordinator::run()
{
    m_currentTime = m_coordinator->getNextTime();

    if (m_currentTime == Time::infinity) {
        return false;
    } else if ((m_end - m_currentTime) < 0) {
        return false;
    }

    m_coordinator->run();
    return true;
}

void RootCoordinator::finish()
{
    if (m_coordinator) {
        m_coordinator->finish();
        m_outputs = m_coordinator->outputs();
        delete m_coordinator;
        m_coordinator = 0;
    }

    if (m_root) {
        delete m_root;
        m_root = 0;
    }
}

void RootCoordinator::refreshOutputs()
{
    m_outputs = m_coordinator->outputs();
}

}} // namespace vle devs
