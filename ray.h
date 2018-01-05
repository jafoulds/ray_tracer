#ifndef RAYH
#define RAYH
#include "vec3.h"

class ray
{
    public:
        ray() {}

        ray(vec3& o, const vec3& dt)
        {
          ori = o;
          dir = dt;
        }

        vec3 origin() const
        {
          return ori;
        }

        vec3 direction() const
        {
          return dir;
        }
        vec3 find_point(double t) const
        {
          return ori + t*dir;
        }

        ray create_eye_ray(vec3 corner, vec3 x, vec3 y, vec3 origin, double u, double v)
        {
          return ray(origin, corner + u*x + v*y);
        }
        
        vec3 ori;
        vec3 dir;
};

#endif
