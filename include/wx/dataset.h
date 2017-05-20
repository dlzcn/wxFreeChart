/////////////////////////////////////////////////////////////////////////////
// Name:    dataset.h
// Purpose: dataset base class declarations
// Author:    Moskvichev Andrey V.
// Created:    2008/11/07
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef DATASET_H_
#define DATASET_H_

#include <wx/wxfreechartdefs.h>

#include <wx/dynarray.h>
#include <wx/refobject.h>

#include <wx/marker.h>
#include <wx/render/chartrenderer.h>

#include <time.h>

class Dataset;
class DateTimeDataset;

/**
 * Simple class to help locate a data point in a specific dataset and series.
 */
class WXDLLIMPEXP_FREECHART DataItemLocator
{
public:
    /**
     * Constructor to fully specify a data point.
     */
    DataItemLocator (size_t dataset, size_t series, size_t index, bool valid);
    
    /**
     * Gets the dataset index where this data point is stored.
     * @return The dataset holding this data point.
     */
    size_t GetDataset();
    
    /**
     * Gets the series index where this data point is stored.
     * @return The series holding this data point.
     */
    size_t GetSeries();
    
    /**
     * Gets the index of this data point within the data series.
     * @return The index of this data point.
     */
    size_t GetIndex();
    
    /**
     * Gets the validity of this data point locator.
     * @return True if the locator contains valid information to locate a data point.
     */
    bool IsValid();

private:    
    size_t m_dataset;
    size_t m_series;
    size_t m_index;
    bool m_valid;
};

#define FOREACH_SERIE(index, dataset) \
    for (size_t index = 0; index < dataset->GetSerieCount(); index++)

#define FOREACH_DATAITEM(index, serie, dataset) \
    for (size_t index = 0; index < dataset->GetSeriesSize(serie); index++)

wxDECLARE_EVENT(EVT_DATASET_CHANGED, wxCommandEvent);        

inline const wxAny wxAnyMax(const wxAny& a, const wxAny& b)
{
    wxASSERT(a.HasSameType(b));
    
    if (a.CheckType<double>())
        return a.As<double>() > b.As<double>() ? a : b;
        
    if (a.CheckType<wxDateTime>())
        return a.As<wxDateTime>() > b.As<wxDateTime>() ? a : b;
        
    // Error: Unsupported any type.
    wxFAIL;
    
    return wxAny(0);
}

inline const wxAny wxAnyMin(const wxAny& a, const wxAny& b)
{
    wxASSERT(a.HasSameType(b));
    
    if (a.CheckType<double>())
        return a.As<double>() < b.As<double>() ? a : b;
        
    if (a.CheckType<wxDateTime>())
        return a.As<wxDateTime>() < b.As<wxDateTime>() ? a : b;
        
    // Error: Unsupported any type.
    wxFAIL;
    
    return wxAny(0);
}

/**
 * Base class for all datasets (XYDatasets, XYZDatasets, CategoryDatasets, OHLCDatasets, etc).
 *
 */
class WXDLLIMPEXP_FREECHART Dataset : public wxEvtHandler, public RefObject
{
    DECLARE_CLASS(Dataset)
public:
    Dataset();
    virtual ~Dataset();

    /**
     * Sets renderer for this dataset.
     * @param renderer new renderer
     */
    void SetRenderer(Renderer *renderer);

    Renderer *GetBaseRenderer();

    /**
     * Called to begin dataset update.
     * Each call must have corresponding EndUpdate call.
     * Increment dataset update counter.
     */
    void BeginUpdate();

    /**
     * Called to end dataset update.
     * Decrement dataset update counter, and fires
     * DatasetChanged event when counter equal zero.
     */
    void EndUpdate();

    /**
     * Returns serie count in this dataset.
     * @return serie count
     */
    virtual size_t GetSerieCount() const = 0;

    /**
     * Returns value count in serie specified by index.
     * @param serie index
     * @return value count
     */
    virtual size_t GetSeriesSize(size_t serie) const = 0;

    /**
     * Returns serie name.
     * @param serie index
     * @return serie name
     */
    virtual wxString GetSerieName(size_t serie) const = 0;

    /**
     * Returns minimal value.
     * @param vertical for datasets with XY coordinates, specifies direction
     * @return minimal value
     */
    virtual double GetMinValue(bool vertical) const = 0;

    /**
     * Returns maximal value.
     * @param vertical for datasets with XY coordinates, specifies direction
     * @return maximal value
     */
    virtual double GetMaxValue(bool vertical) const = 0;

    virtual DateTimeDataset *AsDateTimeDataset();

    /**
     * Adds marker to plot. Plot takes ownership of marker.
     * @param marker marker to be added
     */
    void AddMarker(Marker *marker);

    /**
     * Returns marker count.
     * @return marker count
     */
    size_t GetMarkersCount();

    /**
     * Returns marker at specified index.
     * @param index index of marker
     * @return marker at specified index
     */
    Marker *GetMarker(size_t index);

    //
    // DrawObjectObserver
    //
    // Received from renderer, or marker
    virtual void NeedRedraw(DrawObject *obj);

    /**
     * Called to indicate, that dataset is changed.
     * For call by derivate classes.
     */
    void DatasetChanged();

protected:
    /**
     * Checks whether renderer is acceptable by this dataset.
     */
    virtual bool AcceptRenderer(Renderer *r) = 0;

    Renderer *m_renderer;
private:
    bool m_updating;
    bool m_changed;

    MarkerArray m_markers;
};

/**
 * Base class for datasets, with date/time.
 */
class WXDLLIMPEXP_FREECHART DateTimeDataset
{
public:
    DateTimeDataset();
    virtual ~DateTimeDataset();

    /**
     * Returns date/time for specified index.
     * @param index index
     * @return date/time for specified index
     */
    virtual time_t GetDate(size_t index) const = 0;

    /**
     * Returns date/time count.
     * @return date/time count
     */
    virtual size_t GetSeriesSize() const = 0;
};

WX_DECLARE_USER_EXPORTED_OBJARRAY(Dataset *, DatasetArrayBase, WXDLLIMPEXP_FREECHART);

class WXDLLIMPEXP_FREECHART DatasetArray : public DatasetArrayBase
{
public:
    DatasetArray();
    virtual ~DatasetArray();

    void Add(Dataset *dataset);

    void Remove(Dataset *dataset);

    void RemoveAt(size_t index, size_t count = 1);
};

#endif /*DATASET_H_*/
