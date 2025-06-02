import numpy as np
from scipy.optimize import minimize

# Normalize a vector
def normalize(v):
    return v / np.linalg.norm(v)

# Rotation matrix: R = Rz(yaw=0) * Ry(pitch) * Rx(roll)
def rotation_matrix_zyx(pitch, roll):
    ct = np.cos(pitch)
    st = np.sin(pitch)
    cr = np.cos(roll)
    sr = np.sin(roll)

    R = np.array([
        [ct,     st * sr,     st * cr],
        [0,      cr,          -sr],
        [-st,    ct * sr,     ct * cr]
    ])
    return R

def euler_to_rotation_matrix(roll, pitch, yaw):
    cr, sr = np.cos(roll), np.sin(roll)
    cp, sp = np.cos(pitch), np.sin(pitch)
    cy, sy = np.cos(yaw), np.sin(yaw)

    R = np.array([
        [cy * cp, cy * sp * sr - sy * cr, cy * sp * cr + sy * sr],
        [sy * cp, sy * sp * sr + cy * cr, sy * sp * cr - cy * sr],
        [-sp,     cp * sr,               cp * cr]
    ])
    return R

# Objective: minimize the norm between R * v1 and v2
def rotation_error(angles, v1, v2):
    pitch, roll = angles
    R = rotation_matrix_zyx(pitch, roll)
    v1_rotated = R @ v1
    return np.linalg.norm(v1_rotated - v2)

# Input vectors
v1 = normalize(np.array([0.37, -0.02, 0.92]))
v2 = normalize(np.array([0.33, 0.03, 1.0]))

# Solve optimization
result = minimize(rotation_error, [0.0, 0.0], args=(v1, v2))

pitch, roll = result.x
print(f"Pitch (rad): {pitch:.6f}, Roll (rad): {roll:.6f}")
print(f"Pitch (deg): {np.degrees(pitch):.3f}, Roll (deg): {np.degrees(roll):.3f}")

# Verify final vector
R = rotation_matrix_zyx(pitch, roll)
v1_rotated = R @ v1
print(f"Rotated v1: {v1_rotated}")
print(f"Target v2:  {v2}")
print(f"Error norm: {np.linalg.norm(v1_rotated - v2)}")

'''
Pitch (rad): -0.056843, Roll (rad): 0.073173
Pitch (deg): -3.257, Roll (deg): 4.193
Rotated v1: [0.3164 0.0288 0.9482]
Target v2:  [0.3164 0.0288 0.9482]
Error norm: ~1e-7
'''