/**
 *       @file  marker.hpp
 *      @brief  My LineMarker and RangeMarker for wxFreeChart
 * 
 *     @author  Haifeng CHEN (HF), optical.dlz@gmail.com
 *    @version  0.1
 *
 *   @internal
 *    Created:  2018/4/8 9:42:25
 *   Modified:  2018/4/8 9:42:25
 *   Revision:  none
 *   Compiler:  VS2015
 *    Company:  Saint-Gobain Research (Shanghai) Co., Ltd.
 *  Copyright:  Copyright (c) 2018, Haifeng CHEN
 * =====================================================================================
 */
#pragma once

#include <wx/marker.h>

class InteractiveLineMarker : public LineMarker
{
public:
    InteractiveLineMarker(wxPen linePen)
        : LineMarker(linePen)
        , m_visible(true)
    {

    }

    InteractiveLineMarker(wxColor lineColor, int lineWidth)
        : LineMarker(lineColor, lineWidth)
        , m_visible(true)
    {
    }

    ~InteractiveLineMarker()
    {

    }

    void SetVisible(bool visible = true)
    {
        m_visible = visible;
    }

    bool IsVisible() const
    {
        return m_visible;
    }

    virtual void Draw(wxDC &dc, wxRect rcData, Axis *horizAxis, Axis *vertAxis)
    {
        if (!m_visible)
            return;
        LineMarker::Draw(dc, rcData, horizAxis, vertAxis);
    }

private:
    bool m_visible;
};


class InteractiveRangeMarker : public RangeMarker
{
public:
    InteractiveRangeMarker(AreaDraw *rangeAreaDraw)
        : RangeMarker(rangeAreaDraw)
        , m_visible(true)
    {

    }

    virtual ~InteractiveRangeMarker()
    {

    }

    void SetVisible(bool visible = true)
    {
        m_visible = visible;
    }

    bool IsVisible() const
    {
        return m_visible;
    }

    virtual void Draw(wxDC &dc, wxRect rcData, Axis *horizAxis, Axis *vertAxis)
    {
        if (!m_visible)
            return;
        RangeMarker::Draw(dc, rcData, horizAxis, vertAxis);
    }

private:

    bool m_visible;
};