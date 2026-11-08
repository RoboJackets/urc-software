/*
Header file for the path-smoothing which uses gradient descent

Inputs:
    - A-Star Path


Outputs:
    - The same start point
    - The same end point


Smoothing the Path
    - Get the original A* Path

    - Get the immutable endpoints (start/end)

    - Begin running gradient descent

*/

#pragma once //prevents #include duplications in future headers that reference this one

#include <cstddef> //for std::size_t
#include <nav_msgs/msg/path.hpp> //references and allows this header to use the types (path specifically) from the other file



namespace urc_path_planning { //gives a consolidated naming for the implementation--this has access to these types and these methods, just in case another file has a similar name
    struct SmoothingParameters { //a public access 'class' which is currently used for establishing the shared and known paramters
        double data_weight;
        double smoothness_weight;
        double tolerance;
        std::size_t maximum_iterations;
    };

    class GradientDescentSmoother { //the actual smoother object
        public: //defines these methods to be public
            explicit GradientDescentSmoother(SmoothingParameters parameters); //this smoother's constructor must be implemented as explicit meaning that implicit conversion cannot happen

            nav_msgs::msg::Path smooth(const nav_msgs::msg::Path & original_path) const; // The first const protects the original path and the final const protects the smoother's member states (like parameters_)

        private: //ensures that nothing outside of the given object to edit these parameters (because they are this arbitrary smoother's constants, so any non-const method in this class can edit it but only from within)
            SmoothingParameters parameters_;
    };

} // namespace urc_path_planning





