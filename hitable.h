#ifndef HITABLEH
#define HITABLEH

#include "ray.h"

struct hit_record
{
    double t;
    vec3 hitpoint;
    vec3 normal;
};

class hitable  {
    public:
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};
#endif
