use crate::mafconstants::{randomf64, randomf64_range};
use core::{f64, fmt};
use half::f16;
use std::i8;

#[derive(Clone, Copy)]
pub struct Vec3 {
    x: f32,
    y: f32,
    z: f32,
}

impl fmt::Display for Vec3 {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "x: {}, y: {}, z: {}", self.x, self.y, self.z)
    }
}

impl From<i8> for Vec3 {
    fn from(item: i8) -> Vec3 {
        let _number = item as f32;
        Vec3 {
            x: _number,
            y: _number,
            z: _number,
        }
    }
}

impl From<i32> for Vec3 {
    fn from(item: i32) -> Vec3 {
        let _number = item as f32;
        Vec3 {
            x: _number,
            y: _number,
            z: _number,
        }
    }
}

impl From<f32> for Vec3 {
    fn from(item: f32) -> Vec3 {
        Vec3 {
            x: item,
            y: item,
            z: item,
        }
    }
}

impl From<f16> for Vec3 {
    fn from(item: f16) -> Vec3 {
        let _number = f32::from(item);
        Vec3 {
            x: _number,
            y: _number,
            z: _number,
        }
    }
}

impl From<f64> for Vec3 {
    fn from(item: f64) -> Vec3 {
        let _number: f32 = item as f32;
        Vec3 {
            x: _number,
            y: _number,
            z: _number,
        }
    }
}

impl std::ops::Neg for Vec3 {
    type Output = Vec3;
    fn neg(self) -> Vec3 {
        Vec3 { x: -self.x, y: -self.y, z: -self.z }
    }
}

impl std::ops::Add<Vec3> for Vec3 {
    type Output = Vec3;

    fn add(self, rhs: Vec3) -> Vec3 {
        Vec3 { x: self.x + rhs.x, y: self.y + rhs.y, z: self.z + rhs.z }
    }
}

impl std::ops::Sub<Vec3> for Vec3 {
    type Output = Vec3;
    fn sub(self, rhs: Vec3) -> Vec3 {
        Vec3 { x: self.x - rhs.x, y: self.y - rhs.y, z: self.z - rhs.z }
    }
}

impl std::ops::Mul<Vec3> for Vec3 {
    type Output = Vec3;

    fn mul(self, rhs: Vec3) -> Vec3 {
        Vec3::new(self.x * rhs.x, self.y * rhs.y, self.z * rhs.z)
    }
}

impl std::ops::Mul<f64> for Vec3 {
    type Output = Vec3;

    fn mul(self, rhs: f64) -> Vec3 {
        Vec3::new(self.x * rhs as f32, self.y * rhs as f32, self.z * rhs as f32)
    }
}

impl std::ops::Mul<Vec3> for f64 {
    type Output = Vec3;
    fn mul(self, rhs: Vec3) -> Vec3 {
        Vec3::new(self as f32 * rhs.x, self as f32 * rhs.y, self as f32 * rhs.z)
    }
}

impl std::ops::Div<Vec3> for Vec3 {
    type Output = Vec3;

    fn div(self, rhs: Vec3) -> Vec3 {
        Vec3::new(self.x / rhs.x, self.y / rhs.y, self.z / rhs.z)
    }
}

impl std::ops::Div<f64> for Vec3 {
    type Output = Vec3;

    fn div(self, rhs: f64) -> Vec3 {
        Vec3::new(self.x / rhs, self.y / rhs, self.z / rhs)
    }
}

impl std::ops::AddAssign<Vec3> for Vec3 {
    fn add_assign(&mut self, other: Vec3) {
        self.x += other.x;
        self.y += other.y;
        self.z += other.z;
    }
}

impl std::ops::AddAssign<f64> for Vec3 {
    fn add_assign(&mut self, other: f64) {
        self.x += other;
        self.y += other;
        self.z += other;
    }
}

impl std::ops::SubAssign<Vec3> for Vec3 {
    fn sub_assign(&mut self, other: Vec3) {
        self.x -= other.x;
        self.y -= other.y;
        self.z -= other.z;
    }
}

impl std::ops::SubAssign<f64> for Vec3 {
    fn sub_assign(&mut self, other: f64) {
        self.x -= other;
        self.y -= other;
        self.z -= other;
    }
}

impl std::ops::MulAssign<Vec3> for Vec3 {
    fn mul_assign(&mut self, other: Vec3) {
        self.x *= other.x;
        self.y *= other.y;
        self.z *= other.z;
    }
}

impl std::ops::MulAssign<f64> for Vec3 {
    fn mul_assign(&mut self, other: f64) {
        self.x *= other;
        self.y *= other;
        self.z *= other;
    }
}

impl std::ops::DivAssign<Vec3> for Vec3 {
    fn div_assign(&mut self, other: Vec3) {
        self.x /= other.x;
        self.y /= other.y;
        self.z /= other.z;
    }
}

impl std::ops::DivAssign<f64> for Vec3 {
    fn div_assign(&mut self, other: f64) {
        self.x /= other;
        self.y /= other;
        self.z /= other;
    }
}

impl Vec3 {
    pub fn new(x: f32, y: f32, z: f32) -> Vec3 {
        return Vec3 { x, y, z };
    }
    pub fn x(&self) -> f32 {
        self.x
    }
    pub fn y(&self) -> f32 {
        self.y
    }
    pub fn z(&self) -> f32 {
        self.z
    }

    pub fn length(&self) -> f32 {
        f64::sqrt(self.x * self.x + self.y * self.y + self.z * self.z)
    }
    pub fn squared_length(&self) -> f32 {
        self.x * self.x + self.y * self.y + self.z * self.z
    }
    pub fn random(&self) -> Vec3 {
        return Vec3 {
            x: randomf64() as f32,
            y: randomf64() as f32,
            z: randomf64() as f32,
        };
    }

    pub fn random_range(min: f32, max: f32) -> Vec3 {
        return Vec3 {
            x: randomf64_range(min as f64, max as f64) as f32,
            y: randomf64_range(min as f64, max as f64) as f32,
           z: randomf64_range(min as f64, max as f64) as f32,
        };
    }

    pub fn cross(v1: Vec3, v2: Vec3) -> Vec3 {
        Vec3::new(
            v1.y * v2.z - v1.z * v2.y,
            -(v1.x * v2.z - v1.z * v2.x),
            v1.x * v2.y - v1.y * v2.x,
        )
    }
    pub fn random_in_unit_sphere() -> Vec3 {
        let p: Vec3;
        loop {
            let p: Vec3 = Vec3::random_range(-1.0, 1.0);
            if p.squared_length() >= 1.0 {
                continue;
            }
            return p;
        }
    }
    pub fn random_unit_vector() -> Vec3 {
        let fuck: Vec3 = Vec3::random_in_unit_sphere();
        return Vec3::make_unit_vector(fuck);
    }
    pub fn make_unit_vector(v: Vec3) -> Vec3 {
        v / v.length()
    }

    pub fn dot(v1: &Vec3, v2: &Vec3) -> f32 {
        v1.x * v2.x + v1.y * v2.y + v1.z * v2.z
    }
}
