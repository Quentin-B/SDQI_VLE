/*
 * @file examples/test/testdecision.cpp
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


#define BOOST_TEST_MAIN
#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE test_decision_extension

#include <boost/test/unit_test.hpp>
#include <boost/test/auto_unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <boost/lexical_cast.hpp>
#include <stdexcept>
#include <vle/manager.hpp>
#include <vle/vpz.hpp>
#include <vle/value.hpp>
#include <vle/utils.hpp>
#include <iostream>

struct F
{
    F() { vle::manager::init(); }
    ~F() { vle::manager::finalize(); }
};

BOOST_GLOBAL_FIXTURE(F)

    using namespace vle;

BOOST_AUTO_TEST_CASE(test_agentonly)
{
    vpz::Vpz file(utils::Path::path().getExampleFile("agentonly.vpz"));

    utils::ModuleManager man;
    manager::RunQuiet r(man);
    r.start(file);

    BOOST_REQUIRE_EQUAL(r.haveError(), false);
    oov::OutputMatrixViewList& out(r.outputs());
    BOOST_REQUIRE_EQUAL(out.size(),
                        (oov::OutputMatrixViewList::size_type)1);

    oov::OutputMatrix& view1(out["storage"]);

    value::MatrixView result(view1.values());

    BOOST_REQUIRE_EQUAL(result.shape()[0],
                        (value::MatrixView::size_type)2);
    BOOST_REQUIRE_EQUAL(result.shape()[1],
                        (value::MatrixView::size_type)11);

    BOOST_REQUIRE_EQUAL(value::toInteger(result[1][0]), 1);
    BOOST_REQUIRE_EQUAL(value::toInteger(result[1][1]), 4);
    BOOST_REQUIRE_EQUAL(value::toInteger(result[1][2]), 7);
    BOOST_REQUIRE_EQUAL(value::toInteger(result[1][3]), 8);
    BOOST_REQUIRE_EQUAL(value::toInteger(result[1][4]), 8);
    BOOST_REQUIRE_EQUAL(value::toInteger(result[1][5]), 8);
    BOOST_REQUIRE_EQUAL(value::toInteger(result[1][6]), 8);
    BOOST_REQUIRE_EQUAL(value::toInteger(result[1][7]), 8);
    BOOST_REQUIRE_EQUAL(value::toInteger(result[1][8]), 8);
    BOOST_REQUIRE_EQUAL(value::toInteger(result[1][9]), 8);
    BOOST_REQUIRE_EQUAL(value::toInteger(result[1][10]), 9);
}

BOOST_AUTO_TEST_CASE(test_agentonlyprecedenceconstraint)
{
    vpz::Vpz file(utils::Path::path().getExampleFile("agentonlyc.vpz"));

    utils::ModuleManager man;
    manager::RunQuiet r(man);
    r.start(file);

    BOOST_REQUIRE_EQUAL(r.haveError(), false);
    oov::OutputMatrixViewList& out(r.outputs());
    BOOST_REQUIRE_EQUAL(out.size(),
                        (oov::OutputMatrixViewList::size_type)1);

    oov::OutputMatrix& view1(out["storage"]);

    value::MatrixView result(view1.values());

    BOOST_REQUIRE_EQUAL(result.shape()[0],
                        (value::MatrixView::size_type)2);
    BOOST_REQUIRE_EQUAL(result.shape()[1],
                        (value::MatrixView::size_type)11);

    BOOST_REQUIRE_EQUAL(value::toInteger(result[1][0]), 1);
    BOOST_REQUIRE_EQUAL(value::toInteger(result[1][1]), 2);
    BOOST_REQUIRE_EQUAL(value::toInteger(result[1][2]), 3);
    BOOST_REQUIRE_EQUAL(value::toInteger(result[1][3]), 3);
    BOOST_REQUIRE_EQUAL(value::toInteger(result[1][4]), 3);
    BOOST_REQUIRE_EQUAL(value::toInteger(result[1][5]), 3);
    BOOST_REQUIRE_EQUAL(value::toInteger(result[1][6]), 3);
    BOOST_REQUIRE_EQUAL(value::toInteger(result[1][7]), 3);
    BOOST_REQUIRE_EQUAL(value::toInteger(result[1][8]), 3);
    BOOST_REQUIRE_EQUAL(value::toInteger(result[1][9]), 3);
    BOOST_REQUIRE_EQUAL(value::toInteger(result[1][10]), 4);
}

BOOST_AUTO_TEST_CASE(test_agentonlywakeup)
{
    vpz::Vpz file(utils::Path::path().getExampleFile("agentonlywakeup.vpz"));

    utils::ModuleManager man;
    manager::RunQuiet r(man);
    r.start(file);

    BOOST_REQUIRE_EQUAL(r.haveError(), false);
    oov::OutputMatrixViewList& out(r.outputs());
    BOOST_REQUIRE_EQUAL(out.size(),
                        (oov::OutputMatrixViewList::size_type)1);

    oov::OutputMatrix& view1(out["storage"]);

    value::MatrixView result(view1.values());

    BOOST_REQUIRE_EQUAL(result.shape()[0],
                        (value::MatrixView::size_type)2);
    BOOST_REQUIRE_EQUAL(result.shape()[1],
                        (value::MatrixView::size_type)11);

    BOOST_REQUIRE_EQUAL(value::toInteger(result[1][0]), 0);
    BOOST_REQUIRE_EQUAL(value::toInteger(result[1][1]), 1);
    BOOST_REQUIRE_EQUAL(value::toInteger(result[1][2]), 1);
    BOOST_REQUIRE_EQUAL(value::toInteger(result[1][3]), 1);
    BOOST_REQUIRE_EQUAL(value::toInteger(result[1][4]), 1);
    BOOST_REQUIRE_EQUAL(value::toInteger(result[1][5]), 1);
    BOOST_REQUIRE_EQUAL(value::toInteger(result[1][6]), 2);
    BOOST_REQUIRE_EQUAL(value::toInteger(result[1][7]), 2);
    BOOST_REQUIRE_EQUAL(value::toInteger(result[1][8]), 2);
    BOOST_REQUIRE_EQUAL(value::toInteger(result[1][9]), 2);
    BOOST_REQUIRE_EQUAL(value::toInteger(result[1][10]), 2);
}

