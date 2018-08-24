/////////////////////////////////////////////////////////////////////////////
// Name:    xyarearenderer.h
// Purpose: xy area renderer declarations
// Author:    Moskvichev Andrey V.
// Created:    2008/11/07
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef XYAREARENDERER_H_
#define XYAREARENDERER_H_

#include <wx/xy/xyrenderer.h>

class WXDLLIMPEXP_FREECHART XYAreaRenderer : public XYRenderer
{
    DECLARE_CLASS(XYAreaRenderer)
public:
    XYAreaRenderer(const wxPen& outlinePen = *wxTRANSPARENT_PEN, const wxBrush& areaBrush = *wxGREY_BRUSH);
    virtual ~XYAreaRenderer();

    virtual void Draw(wxDC &dc, wxRect rc, Axis *horizAxis, Axis *vertAxis, XYDataset *dataset);

    virtual void Draw(wxDC &dc, wxRect rcData, wxCoord x0, wxCoord y0, wxCoord x1, wxCoord y1);

    void SetFillToZero(bool val) { m_fillZero = val; }
    bool GetFillToZero() const { return m_fillZero; }

private:
    wxPen m_outlinePen;
    wxBrush m_areaBrush;
    bool m_fillZero;
};

#endif /*XYAREARENDERER_H_*/
