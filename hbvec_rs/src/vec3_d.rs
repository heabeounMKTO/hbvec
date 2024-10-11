/// f64 vec3 and it's operations

use core::{f64, fmt};

use crate::mafconstants::{randomf64_range, randomf64};

#[derive(Clone, Copy)]
pub struct Vec3_d {
    x: f64,
    y: f64,
    z: f64
}

impl fmt::Display for Vec3_d {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "x: {}, y: {}, z: {}", self.x, self.y, self.z)
    }
}


impl From<i32> for Vec3_d {
    fn from(item: i32) -> Vec3_d {
        let _number = f64::from(item);
        Vec3_d { x: _number, y: _number, z: _number }
    }
}

impl From<f32> for Vec3_d {
    fn from(item: f32) -> Vec3_d {
        let _number = f64::from(item);
        Vec3_d { x: _number, y: _number, z: _number }
    }
}

impl From<f64> for Vec3_d {
    fn from(item: f64) -> Vec3_d {
        Vec3_d { x: item, y: item, z: item }
    }
}



impl std::ops::Neg for Vec3_d{
    type Output = Vec3_d;
    fn neg(self) -> Vec3_d{
        Vec3_d::new(
            -self.x,
            -self.y,
            -self.z
        )
    }
}

impl std::ops::Add<Vec3_d> for Vec3_d{
    type Output = Vec3_d;

    fn add(self, rhs:Vec3_d) -> Vec3_d{
        Vec3_d::new(
            self.x + rhs.x,
            self.y + rhs.y,
            self.z + rhs.z
        )
    }
}

impl std::ops::Sub<Vec3_d> for Vec3_d {
    type Output = Vec3_d;

    fn sub(self, rhs: Vec3_d) -> Vec3_d {
        Vec3_d::new(
            self.x - rhs.x,
            self.y - rhs.y,
            self.z - rhs.z
        )
    }
}

impl std::ops::Mul<Vec3_d> for Vec3_d {
    type Output = Vec3_d;

    fn mul(self, rhs: Vec3_d) -> Vec3_d {
        Vec3_d::new(
            self.x * rhs.x,
            self.y * rhs.y,
            self.z * rhs.z
        )
    }
}

impl std::ops::Mul<f64> for Vec3_d {
    type Output = Vec3_d;

    fn mul(self, rhs: f64) -> Vec3_d {
        Vec3_d::new(
            self.x * rhs,
            self.y * rhs,
            self.z * rhs
        )
    }
}

impl std::ops::Mul<Vec3_d> for f64 {
    type Output = Vec3_d;

    fn mul(self, rhs: Vec3_d) -> Vec3_d {
        Vec3_d::new(
            self * rhs.x,
            self * rhs.y,
            self * rhs.z
        )
    }
}

impl std::ops::Div<Vec3_d> for Vec3_d {
    type Output = Vec3_d;

    fn div(self, rhs: Vec3_d) -> Vec3_d {
        Vec3_d::new(
            self.x / rhs.x,
            self.y / rhs.y,
            self.z / rhs.z
        )
    }
}

impl std::ops::Div<f64> for Vec3_d {
    type Output = Vec3_d;

    fn div(self, rhs: f64) -> Vec3_d {
        Vec3_d::new(
            self.x / rhs,
            self.y / rhs,
            self.z / rhs
        )
    }
}

impl std::ops::AddAssign<Vec3_d> for Vec3_d {
    fn add_assign(&mut self, other: Vec3_d) {
        self.x += other.x;
        self.y += other.y;
        self.z += other.z;
    }
}

impl std::ops::AddAssign<f64> for Vec3_d {
    fn add_assign(&mut self, other: f64) {
        self.x += other;
        self.y += other;
        self.z += other;
    }
}

impl std::ops::SubAssign<Vec3_d> for Vec3_d {
    fn sub_assign(&mut self, other: Vec3_d) {
        self.x -= other.x;
        self.y -= other.y;
        self.z -= other.z;
    }
}

impl std::ops::SubAssign<f64> for Vec3_d {
    fn sub_assign(&mut self, other: f64) {
        self.x -= other;
        self.y -= other;
        self.z -= other;
    }
}

impl std::ops::MulAssign<Vec3_d> for Vec3_d {
    fn mul_assign(&mut self, other: Vec3_d) {
        self.x *= other.x;
        self.y *= other.y;
        self.z *= other.z;
    }
}

impl std::ops::MulAssign<f64> for Vec3_d {
    fn mul_assign(&mut self, other: f64) {
        self.x *= other;
        self.y *= other;
        self.z *= other;
    }
}

impl std::ops::DivAssign<Vec3_d> for Vec3_d {
    fn div_assign(&mut self, other: Vec3_d) {
        self.x /= other.x;
        self.y /= other.y;
        self.z /= other.z;
    }
}

impl std::ops::DivAssign<f64> for Vec3_d {
    fn div_assign(&mut self, other: f64) {
        self.x /= other;
        self.y /= other;
        self.z /= other;
    }
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
            v1.y * v2.z - v1.z * v2.y,
            -(v1.x * v2.z - v1.z * v2.x),
            v1.x * v2.y - v1.y * v2.x
        )
    }
    pub fn random_in_unit_sphere() -> Vec3_d{
        let p: Vec3_d;
       loop{
            let p: Vec3_d = Vec3_d::random_range(-1.0,1.0);
            if p.squared_length() >= 1.0 {
                continue;
            }
            return p;
        }
    }
    pub fn random_unit_vector() -> Vec3_d{
        let fuck: Vec3_d = Vec3_d::random_in_unit_sphere();
        return Vec3_d::make_unit_vector(fuck);
    }
    pub fn make_unit_vector(v : Vec3_d)->Vec3_d{
        v / v.length()
    }

    pub fn dot(v1 : &Vec3_d, v2 : &Vec3_d) -> f64{
        v1.x * v2.x +
        v1.y * v2.y +
        v1.z * v2.z
    }
    }

