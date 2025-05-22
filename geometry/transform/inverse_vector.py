'''
This script demonstrates how to find the inverse of an Euler angle rotation(only roll and pitch)
the result absolutely depends on the initial vector.
'''

import numpy as np
from scipy.optimize import minimize

def rotate_vector(v, roll, pitch):
    # Yaw = 0
    cp, sp = np.cos(pitch), np.sin(pitch)
    cr, sr = np.cos(roll), np.sin(roll)

    Ry = np.array([
        [ cp, 0, sp],
        [  0, 1,  0],
        [-sp, 0, cp]
    ])
    Rx = np.array([
        [1,   0,    0],
        [0,  cr, -sr],
        [0,  sr,  cr]
    ])
    R = Ry @ Rx
    return R @ v

def objective(x, v_from, v_target):
    roll, pitch = x
    v_rotated = rotate_vector(v_from, roll, pitch)
    return np.linalg.norm(v_rotated - v_target)

# Initial vector
v = np.array([0.0, 0.0, 1.0])

# Apply initial roll and pitch
roll1 = 0.1  # rad
pitch1 = 0.2 # rad
v2 = rotate_vector(v, roll1, pitch1)

# Now: calculate new roll and pitch to recover v
res = minimize(objective, x0=[0.0, 0.0], args=(v2, v))
roll2, pitch2 = res.x

# Check error
v_check = rotate_vector(v2, roll2, pitch2)
error = np.linalg.norm(v_check - v)

# Output
print(f"Initial roll1: {roll1:.6f} rad, pitch1: {pitch1:.6f} rad")
print(f"Inverse roll2: {roll2:.6f} rad, pitch2: {pitch2:.6f} rad")
print(f"Reconstruction error: {error:.6e}")
