use core::f64;
use half::f16;

pub const INFINITY: f64 = f64::INFINITY;
pub const PI: f64 = 3.141592653589;
use rand::Rng;
pub fn degrees_to_radians(degrees: f64) -> f64{
    return degrees * PI / 180.0;
}

pub fn randomf64() -> f64{
    let mut rng = rand::thread_rng();
    return rng.gen();
}

pub fn randomf64_range(min: f64, max: f64) -> f64{
    let mut rng = rand::thread_rng();
    return rng.gen_range(min..max);  
}

pub fn clamp(input: f64, min: f64, max: f64) -> f64 {
    if input < min {return min;};
    if input > max {return max;}
    





pub struct Vec3_h {
    x: f16,
    y: f16,
    z: f16
}

pub struct Vec3 {
    x: f32,
    y: f32,
    z: f32
}

pub struct Vec3_d {
    x: f64,
    y: f64,
    z: f64
}



impl Vec3_d{
    pub fn new(x: f64, y:f64, z: f64) -> Vec3_d{
         return Vec3_d{x, y, z}
    }
    pub fn x(&self) -> f64{ self.x }
    pub fn y(&self) -> f64{ self.y }
    pub fn z(&self) -> f64{ self.z }
    
    pub fn length(&self) -> f64{
        f64::sqrt(
            self.x * self.x +
            self.y * self.y +
            self.z * self.z
        )
    }
    pub fn squared_length(&self)->f64{
        self.x * self.x +
        self.y * self.y +
        self.z * self.z
    }
    pub fn random(&self) -> Vec3_d{
        return Vec3_d{x: randomf64(), y: randomf64(), z: randomf64()};
    }

    pub fn random_range(min: f64, max: f64) -> Vec3_d{
        return Vec3_d{x: randomf64_range(min, max), 
                      y: randomf64_range(min, max), 
                      z: randomf64_range(min,max)};
    }

    pub fn cross(v1: Vec3_d, v2: Vec3_d) -> Vec3_d{
        Vec3_d::new(
            v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
            -(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0]),
            v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]
        )
    }

    pub fn random_in_unit_sphere() -> Vec3{
        let p: Vec3; 
       loop{
            let p: Vec3 = Vec3::random_range(-1.0,1.0);
            if p.squared_length() >= 1.0 {
                continue;
            }
            return p;
        }
    }

    pub fn random_unit_vector() -> Vec3{
        let fuck: Vec3 = Vec3::random_in_unit_sphere();
        return Vec3::make_unit_vector(fuck);
    }
    pub fn write_color(&self, pixel_color: Vec3 ,  samples: f64) -> Pixel_color{
        let mut r: f64 = pixel_color.x();
        let mut g: f64 = pixel_color.y();
        let mut b: f64 = pixel_color.z();


        let scale: f64 = 1.0 / samples;
        //apply aces on linear color
        // got transform func from shadertoy somewhere lol
        r = apply_aces(scale * r);
        g = apply_aces(scale * g);
        b = apply_aces(scale * b);
    

        let pixel_r =  (256.0 * clamp(r, 0.0, 1.0)) as u32;
        let pixel_g =  (256.0 * clamp(g, 0.0, 1.0)) as u32;
        let pixel_b =  (256.0 * clamp(b, 0.0, 1.0)) as u32;
        return Pixel_color { r: pixel_r, g: pixel_g, b: pixel_b };
    }
    pub fn make_unit_vector(v : Vec3)->Vec3{
        v / v.length()
    }

    pub fn dot(v1 : &Vec3, v2 : &Vec3)->f64{
        v1.e[0] * v2.e[0] +
        v1.e[1] * v2.e[1] +
        v1.e[2] * v2.e[2]
    }
}
