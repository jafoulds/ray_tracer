// Jared Foulds
// CSC 305 Assignment #1
// May 23, 2017
//
// This program is a simple ray tracer that computes a sphere and floor with diffuse shading
// and anti-aliasing features. It uses ideas and some code (vec3.h class, hitable_list class)
// from the provided in the book, "Ray Tracing in One Weekend" which was recommended in the
// assignment description

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <float.h>

#include "sphere.h"
#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "hitable_list.h"

using namespace std;

vec3 norm_sphere_random();
vec3 color(const ray& r, hitable *world);
void set_pixel_color(vec3 final, ofstream  &out);

bool sphere_hit = false;

vec3 bottom_left_start(-1.0, -1.0, -1.0);
vec3 x_axis(2.0, 0.0, 0.0);
vec3 y_axis(0.0, 2.0, 0.0);
vec3 origin(0.0, 0.8, 0.0);

int main()
{
  ofstream out("output.ppm");
  int image_x = 400;
  int image_y = 400;
  int rays = 200;

  out << "P3\n" << image_x << " " << image_y << "\n255" << endl;
  hitable * sphere_list[2];
  //increase by 0.1 measurements for x and y
  sphere_list[0] = new sphere(vec3(0.0,0,-2), 0.5);
  sphere_list[1] = new sphere(vec3(0,-100.5, -1), 100);
  hitable *world = new hitable_list(sphere_list,2);
  ray eye_ray;
  for (int j = image_y-1; j >= 0; j--) {
    for (int i = 0; i < image_x; i++) {
      vec3 final_color(0,0,0);
      for (int k=0; k< rays; k++){
        double u = double(drand48() + i) / double(image_x);
        double v = double(drand48() + j) / double(image_y);

        eye_ray = eye_ray.create_eye_ray(bottom_left_start,x_axis,y_axis, origin, u,v);
        //vec3 p = r.find_point(2.0);
        final_color += color(eye_ray, world);
      }
      final_color = final_color / double(rays);
      //raising to gamma 2 which raising the color to 1/gamma
      //increases and decreases brightness of shapes because you're squaring a
      //small number so red, blue, green values increase
      final_color = vec3( sqrt(final_color[0]), sqrt(final_color[1]), sqrt(final_color[2]));
      set_pixel_color(final_color, out);
    }
  }
  return 0;
}

vec3 color(const ray& r, hitable *world) {

    hit_record current_record;
    if (world->hit(r, 0.00001, DBL_MAX, current_record)) {
      sphere_hit = true;
      vec3 target = current_record.hitpoint + current_record.normal + norm_sphere_random();
      return 0.5*color(ray(current_record.hitpoint, target-current_record.hitpoint), world);
    }
    else {
      if(sphere_hit == true){
        sphere_hit = false;
        return vec3(0,0.7,0.2);
      }
      else{
        return vec3(0,0,0.7);
    }
  }
}

void set_pixel_color(vec3 final, ofstream  &out)
{
  int color_num = 255;
  int red = int(color_num*final[0]);
  int green = int(color_num*final[1]);
  int blue = int(color_num*final[2]);
  out << red << " " << green << " " << blue << endl;
}
vec3 norm_sphere_random()
{
  vec3 random;
    random = 2.0*vec3(drand48(),drand48(), drand48()) - vec3(1,1,1);
   while (random.squared_length() >= 1.0){
     random = 2.0*vec3(drand48(),drand48(), drand48()) - vec3(1,1,1);
   }
  return random;
}
