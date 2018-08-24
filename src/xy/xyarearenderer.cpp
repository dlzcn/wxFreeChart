/////////////////////////////////////////////////////////////////////////////
// Name:    xyarearenderer.cpp
// Purpose: xy area renderer
// Author:    Moskvichev Andrey V.
// Created:    2008/11/07
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/xy/xyarearenderer.h>

//
// TODO: need cleanup!
//

IMPLEMENT_CLASS(XYAreaRenderer, XYRenderer)

XYAreaRenderer::XYAreaRenderer(const wxPen& outlinePen, const wxBrush& areaBrush)
    : m_outlinePen(outlinePen)
    , m_areaBrush(areaBrush)
    , m_fillZero(false)
{
    
}

XYAreaRenderer::~XYAreaRenderer()
{
}

void XYAreaRenderer::Draw(wxDC &dc, wxRect rcData, wxCoord x0, wxCoord y0, wxCoord x1, wxCoord y1)
{
    wxPoint pts[4];

    if (x0 > x1) {
        wxCoord t = x1;
        x1 = x0;
        x0 = t;

        t = y1;
        y1 = y0;
        y0 = t;
    }

    pts[0] = wxPoint(x0, rcData.y + rcData.height);
    pts[1] = wxPoint(x0, y0);
    pts[2] = wxPoint(x1, y1);
    pts[3] = wxPoint(x1, rcData.y + rcData.height);

    dc.SetPen(wxNoPen);
    dc.DrawPolygon(4, pts);

    dc.SetPen(m_outlinePen);
    dc.DrawLine(pts[1], pts[2]);
}

//void XYAreaRenderer::Draw(wxDC &dc, wxRect rc, Axis *horizAxis, Axis *vertAxis, XYDataset *dataset)
//{
//    FOREACH_SERIE(serie, dataset) {
//        dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(GetSerieColour(serie)));
//
//        for (size_t n = 0; n < dataset->GetCount(serie) - 1; n++) {
//            double x0 = dataset->GetX(n, serie);
//            double y0 = dataset->GetY(n, serie);
//            double x1 = dataset->GetX(n + 1, serie);
//            double y1 = dataset->GetY(n + 1, serie);
//
//            // check whether segment is visible
//            if (!horizAxis->IntersectsWindow(x0, x1) &&
//                    !vertAxis->IntersectsWindow(y0, y1)) {
//                continue;
//            }
//
//            ClipHoriz(horizAxis, x0, y0, x1, y1);
//            ClipHoriz(horizAxis, x1, y1, x0, y0);
//            ClipVert(vertAxis, x0, y0, x1, y1);
//            ClipVert(vertAxis, x1, y1, x0, y0);
//
//            // translate to graphics coordinates.
//            wxCoord xg0, yg0;
//            wxCoord xg1, yg1;
//
//            xg0 = horizAxis->ToGraphics(dc, rc.x, rc.width, x0);
//            yg0 = vertAxis->ToGraphics(dc, rc.y, rc.height, y0);
//            xg1 = horizAxis->ToGraphics(dc, rc.x, rc.width, x1);
//            yg1 = vertAxis->ToGraphics(dc, rc.y, rc.height, y1);
//
//            Draw(dc, rc, xg0, yg0, xg1, yg1);
//        }
//    }
//}

void XYAreaRenderer::Draw(wxDC &dc, wxRect rc, Axis *horizAxis, Axis *vertAxis, XYDataset *dataset)
{
    FOREACH_SERIE(serie, dataset) {
        dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(GetSerieColour(serie)));
        dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(GetSerieColour(serie)));
        size_t sz = dataset->GetCount(serie);

        std::vector<wxPoint> pts;
        pts.reserve(sz);

        double x_min, x_max;
        horizAxis->GetDataBounds(x_min, x_max);
        double x0, y0;

        for (size_t n = 0; n < sz; n++) {
            x0 = dataset->GetX(n, serie);
            y0 = dataset->GetY(n, serie);
            if (x0 < x_min || x0 > x_max)
                continue;
            // translate to graphics coordinates.
            wxPoint pt;
            pt.x = horizAxis->ToGraphics(dc, rc.x, rc.width, x0);
            pt.y = vertAxis->ToGraphics(dc, rc.y, rc.height, y0);
            if (pts.empty())
                pts.push_back(pt);
            else {
                if (pts.back() != pt)
                    pts.push_back(pt);
            }
        }

        if (!pts.empty()) {
            if (m_fillZero) {
                y0 = vertAxis->ToGraphics(dc, rc.y, rc.height, 0);
            } else {
                y0 = rc.y + rc.height;
            }
            wxPoint pt = pts.back();
            pt.y = y0;
            pts.push_back(pt);
            pt = pts.front();
            pt.y = y0;
            pts.push_back(pt);
        }

        dc.SetPen(wxNoPen);
        dc.DrawPolygon(static_cast<int>(pts.size()), &pts[0]);

        pts.pop_back();
        pts.pop_back();
        dc.SetPen(m_outlinePen);
        dc.DrawLines(static_cast<int>(pts.size()), &pts[0]);
    }
}
