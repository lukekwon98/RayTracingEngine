#include "rtweekend.h"
#include "camera.h"
#include "hittable_list.h"
#include "sphere.h"
#include "material.h"

int main() {

    hittable_list world;

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 20;
    cam.max_depth         = 20;

    cam.vfov     = 20;
    cam.lookfrom = point3(13,2,3);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0.6;
    cam.focus_dist    = 10.0;

    cam.render(world);
}


// #include <iostream>
// #include "color.h"
// #include "vec3.h"
// #include "ray.h"
// #include "sphere.h"
// #include "hittable_list.h"
// #include "rtweekend.h"

// using namespace std;

// color ray_color(const ray& r, const hittable_list& world){
//     hit_record rec;
//     if(world.hit(r,interval(0,infinity),rec)){ //world = sphereless object
//         return 0.5 * (rec.normal + color(1,1,1));
//     }
//     vec3 unit_direction = unit_vector(r.direction());
//     auto t = 0.5*(unit_direction.y() + 1.0);
//     return (1.0-t)*color(1.0,1.0,1.0) + t*color(0.5,0.7,1.0);
// }

// int main(){
//     //Image
//     const auto aspect_ratio = 16.0/9.0;
//     const int image_width = 400; 
//     const int image_height = static_cast<int>(image_width / aspect_ratio);

//     //World
//     hittable_list world;
//     world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
//     world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

//     //Camera
//     auto viewport_height = 2.0;
//     auto viewport_width = aspect_ratio * viewport_height;
//     auto focal_length = 1.0;

//     auto origin = point3(0,0,0);
//     auto horizontal = vec3(viewport_width, 0, 0);
//     auto vertical = vec3(0,viewport_height,0);
//     auto lower_left_corner = origin - horizontal/2 -vertical/2 - vec3(0,0,focal_length);

//     //Render

//     cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

//     for(int j = image_height -1; j >= 0 ; j--){
//         cerr << "Scanlines remaining: " << j << '\n';
//         for (int i = 0; i < image_width ; i++){
//             auto u = double(i) / (image_width-1);
//             auto v = double(j) / (image_height-1);
//             ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);

//             //this creates a 'color' variable called 'pixel_color'
//             color pixel_color;

//             point3 center(0,0,-1);

//             auto t = hit_sphere(center,0.5, r);

//             if(t > 0.0){ 
//                 vec3 n = unit_vector(r.at(t) - center);
//                 pixel_color = 0.5*color(n.x()+1, n.y()+1, n.z()+1);
//             }
//             else{
//                 pixel_color = ray_color(r, world);
//             }

//             write_color(cout, pixel_color);
//         }
//     }

//     cerr << "\nDone.\n";

// }
//---------------------------------------------------------------------------------------------------------------------------------------------------------

// //this creates a 'color' variable called 'pixel_color'
// color pixel_color;
            
// if (hit_sphere(point3(0,0,-1),0.5,origin,vec)){
//     pixel_color = color(1,0,0);
// }
// else{
//     pixel_color = getColor(vec);
// }

// int main(){
//     int i, j;
//     const int image_width = 256;
//     const int image_height = 256;


//     cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

//     for(j = image_height -1 ; j >=0; j--){
//         cerr << "Scanlines reamining: " << j <<'\n';
//         for(i = 0; i < image_width; i++){
//             auto r = double(i) / (image_width-1);
//             auto g = double(j) / (image_height-1);
//             auto b = 0.25;

//             int ir = static_cast<int>(255.999*r);
//             int ig = static_cast<int>(255.999*g);
//             int ib = static_cast<int>(255.999*b);
            
//             cout << ir << ' ' << ig << ' ' << ib << '\n';
//         }
//     }

//     cerr << "\nDone.\n";
// }