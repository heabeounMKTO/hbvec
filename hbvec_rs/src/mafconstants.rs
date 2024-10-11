use rand::Rng;
pub const INFINITY: f64 = f64::INFINITY;
pub const PI: f64 = 3.141592653589;

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
   if input < min {
        return min;
    } else if input > max {
        return max;
    } else {
        input
    }
}
