import numpy as np

point = (95,20)
point_to_rotate_about = (-40,50)
phi = -45

size = 257

org = size / 2
phi *= np.pi / 180.0
x_p, y_p = point_to_rotate_about
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


table = np.ones( (size,size), dtype=np.uint8)
table[org, :] = 0
table[:, org] = 0

move_to_org = np.array(
[[1,0,-x_p],
 [0,1,-y_p],
 [0,0,  1]])

move_back = np.array(
[[1,0,x_p],
 [0,1,y_p],
 [0,0,  1]])

rotate = np.array(
[[np.cos(phi), -np.sin(phi), 0],
 [np.sin(phi), np.cos(phi),  0],
 [          0,           0,  1]])

transformation = move_back.dot(rotate).dot(move_to_org)
point_vec = np.array(list(point) + [1]).T
new_point = transformation.dot(point_vec)

table[-point[1] + org, point[0] + org] = 0
table[-new_point[1] + org, new_point[0] + org] = 0

write_ppm(table, 'deneme.ppm')

