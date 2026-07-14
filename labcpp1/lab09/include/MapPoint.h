#pragma once

#include <string>


namespace MP { class Point; }

namespace MTH {

    class Point
    {
    public:
        //
        // Basic constructor
        //
        Point(double x, double y);
        
        //
        // Basic deconstructor
        //
        ~Point();

        //
        // Important friendship
        //
        friend class ::MP::Point;
        friend void Print(const Point& point);

        //
        // Allows to copy MP::Point by assignment
        //
        Point& operator=(const Point& other);

    private:
        double m_X = 0.0, m_Y = 0.0;
    };

    //
    // Logs to the console MTH::Point object
    //
    void Print(const Point& point);

}

namespace MP {

    class Point
    {
    public:
        //
        // Basic constructor
        //
        Point(const std::string& name, double Lattitude, double Longitute);

        //
        // Constructor from MTH::Point to MP::Point
        //
        Point(const std::string& name, const ::MTH::Point& point);

        //
        // Basic destructor
        //
        ~Point();

        //
        // Important friendship
        //
        friend void Print(const Point& point);

        //
        // Allows to cast MTH::Point to MP::Point
        //
        operator ::MTH::Point() const;

    private:
        std::string m_Name;
        double m_Lattitude = 0.0, m_Longitute = 0.0;
    };

    //
    // Logs to the console MP::Point object
    //
    void Print(const Point& point);

}