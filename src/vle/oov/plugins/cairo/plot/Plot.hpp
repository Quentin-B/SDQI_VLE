/**
 * @file vle/oov/plugins/cairo/plot/Plot.hpp
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


#ifndef VLE_OOV_PLUGINS_CAIRO_PLOT_HPP
#define VLE_OOV_PLUGINS_CAIRO_PLOT_HPP

#include <vle/oov/CairoPlugin.hpp>
#include <list>
#include <map>
#include <vector>
#include <vle/oov/plugins/cairo/plot/Limit.hpp>
#include <vle/oov/plugins/cairo/plot/RealCurve.hpp>
#include <vle/oov/plugins/cairo/plot/IntCurve.hpp>
#include <vle/oov/plugins/cairo/plot/Parameter.hpp>

namespace vle { namespace oov { namespace plugin {

class Plot : public CairoPlugin
{
public:
    Plot(const std::string& location);
    virtual ~Plot() { }
    
    virtual void onParameter(const vpz::ParameterTrame& trame);
    
    virtual void onNewObservable(const vpz::NewObservableTrame& trame);
    
    virtual void onDelObservable(const vpz::DelObservableTrame& trame);
    
    virtual void onValue(const vpz::ValueTrame& trame);
    
    virtual void close(const vpz::EndTrame& trame);
    
    virtual void preferredSize(int& width, int& height);
    
    virtual void onSize(int width, int height)
        { mWidth = width; mHeight = height; }

private:
    std::vector < IntCurve * > mIntCurveList; // vector des courbes entieres
    std::vector < RealCurve * > mRealCurveList; // vector des courbes r�elles
    std::list < IntCurve * > mShowIntCurveList; // liste des courbes entieres affich�es
    std::list < RealCurve * > mShowRealCurveList; // liste des courbes �relles affich�es
    std::list < Limit * > mLimitList; // liste des limites
    Parameter mParameter;
    bool mFinish;

    std::vector < std::string > mColumns;
    std::map < std::string, int > mColumns2;
    double mTime;
    unsigned int mReceive;
    unsigned int mReceive2;

    int mWidth;
    int mHeight;

    double mStepHeight;

    Cairo::TextExtents mExtents;
    std::valarray < double > mDashes;

    std::vector < RealCurve * >::iterator m_it_dble;
    std::vector < IntCurve * > :: iterator m_it_int;

    Cairo::RefPtr < Cairo::ImageSurface > m_img;

    void draw();
    void drawAxis(Cairo::RefPtr < Cairo::Context > ctx);
    void drawVerticalStep(Cairo::RefPtr < Cairo::Context > ctx);
    void drawHorizontalStep(Cairo::RefPtr < Cairo::Context > ctx);
    void drawCurves(Cairo::RefPtr < Cairo::Context > ctx);
    void drawLimits(Cairo::RefPtr < Cairo::Context > ctx);

    void updateMinValueDrawn();
    void updateMaxValueDrawn();
    double getMaxValueN(int nb_check_value);
    double getMinValueN(int nb_check_value);

    void updateStepHeight();
    
    std::string buildname(const std::string& simulator,
			  const std::string& port)
        {
            std::string result(simulator);
            result += '_';
            result += port;
            return result;
        }
};
	    
}}} // namespace vle oov plugin

DECLARE_OOV_PLUGIN(vle::oov::plugin::Plot);

#endif