# 50.017 GV Week 6 Lab Assignment 3
Victoria Yong 1004455

## Running the Code
In order to run the code, the paths of the obj files must be specified as './data/sphere.obj', and the path of the texture had to be changed to './data/texture.png'

## Texture Mapping
The coordinates of each vertex (i) in the model is stored as such:
```
	x = objModel.vertices[i].v[0]
	y = objModel.vertices[i].v[1]
	z = objModel.vertices[i].v[2]
```
The various texture mappings can be calculated using these vertex coordinates following the below formulas.

Let the texture coordinates be represented by `s` and `t`.

## Planar Parametrization
Planar parametrizations can be represented as a linear parametrization:
```
	(u, v) -> (Wu, Hv, z)

	Linear-mapping a point on texture T(s,t) to a point on p(u,v):
	u = as + bt + c
	v = ds + et + f
```
Hence, to calculate the texture coordinates for a planar mapping, 
```
	s = x + c
	t = y + f
```
where `c` and `f` are two arbitrary constants.

## Cylindrical Parametrization
Cylindrical parametrizations can be represented as:
```
	(θ, φ) -> (rcos(θ), rsin(θ), hφ)
```
To calculate this, first define the cylinder parametrically:
```
Cylinder's side surface:
	p(θ,y) = (rsinθ, rcosθ)
	Here (u, v) = (θ, y)

	y : -h/2 to h/2

```
Assigning texture coordinates:
```
	s = θ / 2π,
	t = ( y + h/2 ) / h
```

## Spherical Parametrization
Spherical parametrizations can be represented as:
```
	(θ, φ) -> (rcos(θ)sin(φ), rsin(θ)sin(φ), rcos(φ))
```
First define the variables of the parametric sphere equation:
```
	r = radius
	θ = angle from z-axis ( 0 ≤ θ ≤ π )
	φ = angle from x-axis ( 0 ≤ φ ≤ 2π )
```
Assigning texture coordinates:
```
	s = φ/2π
	t = θ/π

	Given a point (x, y, z), we can obtain (s, t) :
	t = cos-1 ( z / r ) / π
	s = cos-1( x / r sin ( t π ) ) / 2 π
```