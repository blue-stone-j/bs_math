'''
This script demonstrates how to find the rotation matrix between two vectors
'''

import numpy as np
from scipy.optimize import minimize

# Normalize function
def normalize(v):
    return v / np.linalg.norm(v)

v1 = normalize(np.array([0.37, -0.02, 0.92]))
v2 = normalize(np.array([0.33, 0.03, 1.0]))

# Define error between rotated v1 and v2
def rotation_error(angles):
    pitch, roll = angles
    cp, sp = np.cos(pitch), np.sin(pitch)
    cr, sr = np.cos(roll), np.sin(roll)
    
    # Rotation matrix R = Rx(roll) * Ry(pitch)
    R = np.array([
        [cp, 0, sp],
        [sr*sp, cr, -sr*cp],
        [-cr*sp, sr, cr*cp]
    ])
    rotated = R @ v1
    return np.linalg.norm(rotated - v2)

# Initial guess
result = minimize(rotation_error, [0.0, 0.0])

pitch, roll = result.x
print(f"Pitch (rad): {pitch}, Roll (rad): {roll}")
print(f"Pitch (deg): {np.degrees(pitch)}, Roll (deg): {np.degrees(roll)}")
