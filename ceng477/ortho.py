# orthogonal projected torus knot 
import numpy as np

l = -7.5
r = 7.5
b = -7.5
t = 7.5
n = 10.0
f = -10.0

ex, ey, ez = 0, 0, 15
nx, ny = 500, 500
xu, yu, zu = 1, 0, 0
xv, yv, zv = 0, 1, 0
xw, yw, zw = 0, 0, -1

Mcam_uvw = np.array([
    [xu, yu, zu, 0],
    [xv, yv, zv, 0],
    [xw, yw, zw, 0],
    [0,  0,  0,  1]])

Mcam_e = np.array([
    [1, 0, 0, -ex],
    [0, 1, 0, -ey],
    [0, 0, 1, -ez],
    [0, 0, 0, 1  ]])

Mcam = Mcam_uvw.dot(Mcam_e)

Morth = np.array([
    [2.0/(r-l), 0, 0, -(r+l)/(r-l)],
    [0, 2.0/(t-b), 0, -(t+b)/(t-b)],
    [0, 0, 2.0/(n-f), -(n+f)/(n-f)],
    [0, 0, 0, 1]])

Mvp = np.array([
    [nx/2.0, 0, 0, (nx-1)/2.0],
    [0, ny/2.0, 0, (ny-1)/2.0],
    [0, 0, 1, 0],
    [0, 0, 0, 1]])

M = Mvp.dot(Morth).dot(Mcam)

from math import sin, cos, pi

p,q = 3.0,7.0
step = 0.01

# convert angular coordinates
# r, theta, z to x, y, z
# take tuple, return tuple
def ang2xyz(angular):
	r, th, z = angular
	x = r*cos(th)
	y = r*sin(th)
	return x,y,z

# point list consists of tuples of (x,y,z) coordinates of the point
points = []

for t in np.arange(0, 2*pi*p, step):
	r_0 = 2 + cos(q*t/p)
	theta = t
	z = sin(q*t/p)
	points.append(ang2xyz((r_0, theta, z)))

p = []
for point in points:
    nppoint = np.array([point[0], point[1], 0, 1])
    p.append(M.dot(nppoint))

def write_ppm(mat, file_name):
    file_data = 'P3\n# %s\n' % file_name
    dimension = str(mat.shape[0]) + ' ' + str(mat.shape[1])
    max_val = '1'
    data = ''
    for i in mat:
        for j in i:
            pixel = [str(k) for k in [j] * 3]
            pixel = ' '.join(pixel)
            data += pixel + ' '
        data += '\n'
    file_data += dimension + '\n' + max_val + '\n' + data
    with open(file_name, 'w') as f:
        f.write(file_data)

mat = np.zeros( (ny, nx), dtype=np.uint8 )
for pn in p:
    x = int(pn[0])
    y = int(pn[1])
    #print x, y
    mat[y][x] = 1

write_ppm(mat, 'deneme.ppm')
