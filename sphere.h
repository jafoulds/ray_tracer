#ifndef SPHEREH
#define SPHEREH

#include "math.h"
#include "hitable.h"

class sphere: public hitable  {
  public:
    sphere(vec3 x, double y)//constructor
    {
      center = x;
      radius = y;
    }
    virtual bool hit(const ray & r, double tmin, double tmax, hit_record& rec) const;

    vec3 center;
    double radius;
};

bool sphere::hit(const ray & r, double minimum_t, double maximum_t, hit_record& rec) const {
  bool is_hit = false;
  vec3 diff = r.origin() - center;

  double a = dot(r.direction(), r.direction());
  double b = dot(r.direction(), diff);
  double c = dot(diff, diff) - pow(radius, 2.0);

  double disc = pow(b, 2.0) - a*c;
  if (disc > 0) {
    double current_t = (0.0 - b - sqrt(disc)) / a;
    if(current_t > minimum_t && current_t < maximum_t){
      is_hit = true;
      rec.t = current_t;
      rec.hitpoint = r.find_point(current_t);
      rec.normal = (rec.hitpoint - center) / radius;
      return is_hit;
    }
  }
  return is_hit;
}

#endif
