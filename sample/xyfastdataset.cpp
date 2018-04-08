/////////////////////////////////////////////////////////////////////////////
// Name:    xysimpledataset.cpp
// Purpose: xy simple dataset implementation
// Author:    Moskvichev Andrey V.
// Created:    2009/11/25
// Copyright:    (c) 2009 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include "xyfastdataset.h"
#include "wx/arrimpl.cpp"

IMPLEMENT_CLASS(XYFastSerie, wxObject)
IMPLEMENT_CLASS(XYFastDataset, XYDataset)

//
// XYFastSerie
//

XYFastSerie::XYFastSerie(const wxVector<double>& series_cx,
    const wxVector<double>& series_cy)
    : m_data_x(series_cx)
    , m_data_y(series_cy)
    , m_visible(true)
{
}

XYFastSerie::XYFastSerie(const wxVector<wxRealPoint>& seriesData)
{
    size_t n = seriesData.size();
    m_data_x.resize(n, 0);
    m_data_y.resize(n, 0);
    for (size_t n = 0; n < seriesData.size(); n++) {
        m_data_x[n] = seriesData[n].x;
        m_data_y[n] = seriesData[n].y;
    }
}

XYFastSerie::~XYFastSerie()
{

}

double XYFastSerie::GetX(size_t index)
{
    return m_data_x[index];
}

double XYFastSerie::GetY(size_t index)
{
    return m_data_y[index];
}

void XYFastSerie::UpdateX(double x)
{
    size_t n = m_data_x.size();
    if (n == 0)
        return;
    else if (n == 1) {
        m_data_x[0] = x;
        return;
    }

    memmove(&m_data_x[0], &m_data_x[1],
        (n - 1) * sizeof(double));
    m_data_x[n - 1] = x;
}

void XYFastSerie::UpdateX(size_t index, double x)
{
    m_data_x[index] = x;
}

void XYFastSerie::UpdateX(const wxVector<double>& x)
{
    m_data_x = x;
}

void XYFastSerie::UpdateY(double y)
{
    size_t n = m_data_y.size();
    if (n == 0)
        return;
    else if (n == 1) {
        m_data_y[0] = y;
        return;
    }

    memmove(&m_data_y[0], &m_data_y[1],
        (n - 1) * sizeof(double));
    m_data_y[n - 1] = y;
}

void XYFastSerie::UpdateY(size_t index, double y)
{
    m_data_y[index] = y;
}

void XYFastSerie::UpdateY(const wxVector<double>& y)
{
    m_data_y = y;
}

size_t XYFastSerie::GetCount()
{
    wxASSERT(m_data_x.size() == m_data_y.size());
    if (m_visible)
        return m_data_x.size();
    else
        return 0;
}

const wxString &XYFastSerie::GetName()
{
    return m_name;
}

void XYFastSerie::SetName(const wxString &name)
{
    m_name = name;
}

void XYFastSerie::UpdatePoint(size_t index, const wxRealPoint& values)
{
    m_data_x[index] = values.x;
    m_data_y[index] = values.y;
}

void XYFastSerie::Insert(size_t index, const wxRealPoint& values)
{
    m_data_x.insert(m_data_x.begin() + index, values.x);
    m_data_y.insert(m_data_y.begin() + index, values.y);
}

void XYFastSerie::Insert(size_t index, double cx, double cy)
{
    m_data_x.insert(m_data_x.begin() + index, cx);
    m_data_y.insert(m_data_y.begin() + index, cy);
}

void XYFastSerie::Remove(size_t index)
{
    m_data_x.erase(m_data_x.begin() + index);
    m_data_y.erase(m_data_y.begin() + index);
}

void XYFastSerie::Append(const wxRealPoint& values)
{
    m_data_x.push_back(values.x);
    m_data_y.push_back(values.y);
}

void XYFastSerie::Append(double cx, double cy)
{
    m_data_x.push_back(cx);
    m_data_y.push_back(cy);
}

void XYFastSerie::SetVisible(bool visible)
{
    m_visible = visible;
}

//
// XYFastDataset
//

XYFastDataset::XYFastDataset()
{
}

XYFastDataset::~XYFastDataset()
{

}


void XYFastDataset::AddSerie(XYFastSerie *serie)
{
    m_series.push_back(wxSharedPtr<XYFastSerie>(serie));
    DatasetChanged();
}

XYFastSerie* XYFastDataset::GetSerie(size_t series)
{
    wxCHECK(series < m_series.size(), 0);
    return m_series[series].get();
}

double XYFastDataset::GetX(size_t index, size_t serie)
{
    wxCHECK(serie < m_series.size(), 0);
    return m_series[serie]->GetX(index);
}

double XYFastDataset::GetY(size_t index, size_t serie)
{
    wxCHECK(serie < m_series.size(), 0);
    return m_series[serie]->GetY(index);
}

size_t XYFastDataset::GetSerieCount()
{
    return m_series.size();
}

size_t XYFastDataset::GetCount(size_t serie)
{
    return m_series[serie]->GetCount();
}

wxString XYFastDataset::GetSerieName(size_t serie)
{
    wxCHECK(serie < m_series.size(), wxEmptyString);
    return m_series[serie]->GetName();
}

void XYFastDataset::SetSerieName(size_t serie, const wxString &name)
{
    m_series[serie]->SetName(name);
    DatasetChanged();
}