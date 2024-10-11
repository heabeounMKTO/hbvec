/// f64 vec3 and it's operations

use core::{f64, fmt};
use std::i8;
use half::f16;
use crate::mafconstants::{randomf64_range, randomf64};

#[derive(Debug, PartialEq, PartialOrd, Clone, Copy)]
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


impl From<i8> for Vec3_d {
    fn from(item: i8) -> Vec3_d {
        let _number = f64::from(item);
        Vec3_d { x: _number, y: _number, z: _number }
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

impl From<f16> for Vec3_d {
    fn from(item: f16) -> Vec3_d {
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

#[cfg(test)]
mod tests {
    use super::*;
    use approx::assert_relative_eq;

    #[test]
    fn test_new() {
        let v = Vec3_d::new(1.0, 2.0, 3.0);
        assert_eq!(v.x(), 1.0);
        assert_eq!(v.y(), 2.0);
        assert_eq!(v.z(), 3.0);
    }

    #[test]
    fn test_from_conversions() {
        let v1: Vec3_d = 5i8.into();
        assert_eq!(v1, Vec3_d::new(5.0, 5.0, 5.0));

        let v2: Vec3_d = 10i32.into();
        assert_eq!(v2, Vec3_d::new(10.0, 10.0, 10.0));

        let v3: Vec3_d = 15.0f32.into();
        assert_eq!(v3, Vec3_d::new(15.0, 15.0, 15.0));

        let v4: Vec3_d = f16::from_f32(20.0).into();
        assert_eq!(v4, Vec3_d::new(20.0, 20.0, 20.0));

        let v5: Vec3_d = 25.0f64.into();
        assert_eq!(v5, Vec3_d::new(25.0, 25.0, 25.0));
    }

    #[test]
    fn test_neg() {
        let v = Vec3_d::new(1.0, -2.0, 3.0);
        let negated = -v;
        assert_eq!(negated, Vec3_d::new(-1.0, 2.0, -3.0));
    }

    #[test]
    fn test_add() {
        let v1 = Vec3_d::new(1.0, 2.0, 3.0);
        let v2 = Vec3_d::new(4.0, 5.0, 6.0);
        let sum = v1 + v2;
        assert_eq!(sum, Vec3_d::new(5.0, 7.0, 9.0));
    }

    #[test]
    fn test_sub() {
        let v1 = Vec3_d::new(4.0, 5.0, 6.0);
        let v2 = Vec3_d::new(1.0, 2.0, 3.0);
        let diff = v1 - v2;
        assert_eq!(diff, Vec3_d::new(3.0, 3.0, 3.0));
    }

    #[test]
    fn test_mul() {
        let v1 = Vec3_d::new(2.0, 3.0, 4.0);
        let v2 = Vec3_d::new(5.0, 6.0, 7.0);
        let prod = v1 * v2;
        assert_eq!(prod, Vec3_d::new(10.0, 18.0, 28.0));

        let scalar_prod = v1 * 2.0;
        assert_eq!(scalar_prod, Vec3_d::new(4.0, 6.0, 8.0));

        let scalar_prod_reverse = 2.0 * v1;
        assert_eq!(scalar_prod_reverse, Vec3_d::new(4.0, 6.0, 8.0));
    }

    #[test]
    fn test_div() {
        let v1 = Vec3_d::new(10.0, 15.0, 20.0);
        let v2 = Vec3_d::new(2.0, 3.0, 4.0);
        let div = v1 / v2;
        assert_eq!(div, Vec3_d::new(5.0, 5.0, 5.0));

        let scalar_div = v1 / 2.0;
        assert_eq!(scalar_div, Vec3_d::new(5.0, 7.5, 10.0));
    }

    #[test]
    fn test_compound_assignments() {
        let mut v = Vec3_d::new(1.0, 2.0, 3.0);
        v += Vec3_d::new(1.0, 1.0, 1.0);
        assert_eq!(v, Vec3_d::new(2.0, 3.0, 4.0));

        v -= Vec3_d::new(1.0, 1.0, 1.0);
        assert_eq!(v, Vec3_d::new(1.0, 2.0, 3.0));

        v *= Vec3_d::new(2.0, 2.0, 2.0);
        assert_eq!(v, Vec3_d::new(2.0, 4.0, 6.0));

        v /= Vec3_d::new(2.0, 2.0, 2.0);
        assert_eq!(v, Vec3_d::new(1.0, 2.0, 3.0));

        v += 1.0;
        assert_eq!(v, Vec3_d::new(2.0, 3.0, 4.0));

        v -= 1.0;
        assert_eq!(v, Vec3_d::new(1.0, 2.0, 3.0));

        v *= 2.0;
        assert_eq!(v, Vec3_d::new(2.0, 4.0, 6.0));

        v /= 2.0;
        assert_eq!(v, Vec3_d::new(1.0, 2.0, 3.0));
    }

    #[test]
    fn test_length() {
        let v = Vec3_d::new(3.0, 4.0, 0.0);
        assert_relative_eq!(v.length(), 5.0);
    }

    #[test]
    fn test_squared_length() {
        let v = Vec3_d::new(1.0, 2.0, 3.0);
        assert_eq!(v.squared_length(), 14.0);
    }

    #[test]
    fn test_cross() {
        let v1 = Vec3_d::new(1.0, 2.0, 3.0);
        let v2 = Vec3_d::new(4.0, 5.0, 6.0);
        let cross = Vec3_d::cross(v1, v2);
        assert_eq!(cross, Vec3_d::new(-3.0, 6.0, -3.0));
    }

    #[test]
    fn test_dot() {
        let v1 = Vec3_d::new(1.0, 2.0, 3.0);
        let v2 = Vec3_d::new(4.0, 5.0, 6.0);
        let dot = Vec3_d::dot(&v1, &v2);
        assert_eq!(dot, 32.0);
    }

    #[test]
    fn test_make_unit_vector() {
        let v = Vec3_d::new(3.0, 4.0, 0.0);
        let unit = Vec3_d::make_unit_vector(v);
        assert_relative_eq!(unit.length(), 1.0);
        assert_relative_eq!(unit.x(), 0.6);
        assert_relative_eq!(unit.y(), 0.8);
        assert_relative_eq!(unit.z(), 0.0);
    }

    #[test]
    fn test_random() {
        let v = Vec3_d::new(0.0, 0.0, 0.0);
        let random = v.random();
        assert!(random.x() >= 0.0 && random.x() <= 1.0);
        assert!(random.y() >= 0.0 && random.y() <= 1.0);
        assert!(random.z() >= 0.0 && random.z() <= 1.0);
    }

    #[test]
    fn test_random_range() {
        let random = Vec3_d::random_range(-1.0, 1.0);
        assert!(random.x() >= -1.0 && random.x() <= 1.0);
        assert!(random.y() >= -1.0 && random.y() <= 1.0);
        assert!(random.z() >= -1.0 && random.z() <= 1.0);
    }

    #[test]
    fn test_random_in_unit_sphere() {
        let point = Vec3_d::random_in_unit_sphere();
        assert!(point.squared_length() < 1.0);
    }

    #[test]
    fn test_random_unit_vector() {
        let unit = Vec3_d::random_unit_vector();
        assert_relative_eq!(unit.length(), 1.0, epsilon = 1e-6);
    }
}





