#pragma once

#include <wx/xy/xydataset.h>

#include <wx/dynarray.h>

/**
 * Holds data for one XY serie.
 */
class XYFastSerie : public wxObject
{
    DECLARE_CLASS(XYFastSerie)
public:
    /**
     * Constructs a new XY series using data that is already stored in the prepared vector.
     * @param seriesData The data that will be displayed by this series.
     */
    XYFastSerie(const wxVector<double>& series_cx, 
        const wxVector<double>& series_cy);
    XYFastSerie(const wxVector<wxRealPoint>& seriesData);

    virtual ~XYFastSerie();

    void Append(const wxRealPoint& values);
    void Append(double cx, double cy);

    void Insert(size_t index, const wxRealPoint& values);
    void Insert(size_t index, double cx, double cy);
    
    void Remove(size_t index);

    void SetVisible(bool visible = true);
    /**
     * Retrieves the X value of an existing data point within the series.
     * @param index The position of the data point within the series.
     * @return The X value for the selected data point.
     */
    double GetX(size_t index);

    /**
     * Retrieves the Y value of an existing data point within the series.
     * @param index The position of the data point within the series.
     * @return The Y value for the selected data point.
     */
    double GetY(size_t index);
    
    /**
     * Updates the X value of an existing data point within the series.
     * @param index The position of the data point within the series.
     * @param values The new values for X.
     */
    void UpdateX(double x);// remove the first, and update the empty last
    void UpdateX(size_t index, double x);
    void UpdateX(const wxVector<double>& x);
    
    /**
     * Updates the Y value of an existing data point within the series.
     * @param index The position of the data point within the series.
     * @param values The new value for Y.
     */
    void UpdateY(double y); // remove the first, and update the empty last
    void UpdateY(size_t index, double y);
    void UpdateY(const wxVector<double>& y);
    /**
     * Updates the X and Y values of an existing data point within the series.
     * @param index The position of the data point within the series.
     * @param values The new values for X and Y.
     */
    void UpdatePoint(size_t index, const wxRealPoint& values);

    size_t GetCount();

    const wxString &GetName();

    void SetName(const wxString &name);

private:
    bool m_visible;
    wxVector<double> m_data_x;
    wxVector<double> m_data_y;
    wxString m_name;  
};


/**
 * Simple xy dynamic dataset.
 */
class XYFastDataset : public XYDataset
{
    DECLARE_CLASS(XYFastDataset)
public:
    XYFastDataset();
    virtual ~XYFastDataset();

    /**
     * Constructs new xy serie.
     * @param serie new serie
     */
    void AddSerie(XYFastSerie *serie);

    XYFastSerie* GetSerie(size_t series);

    virtual double GetX(size_t index, size_t serie);// ;

    virtual double GetY(size_t index, size_t serie);// ;

    virtual size_t GetSerieCount();

    virtual size_t GetCount(size_t serie);

    virtual wxString GetSerieName(size_t serie);

    void SetSerieName(size_t serie, const wxString &name);

private:
    wxVector<wxSharedPtr<XYFastSerie> > m_series;
   
    friend XYFastSerie;
};
