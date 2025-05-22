'''
This script demonstrates how to find the inverse of a rotation matrix
'''


import numpy as np
from scipy.spatial.transform import Rotation as R
from scipy.optimize import minimize

# Step 1: Define original roll and pitch (in radians), yaw = 0
roll1 = 0.2     # rad
pitch1 = 0.3    # rad
yaw1 = 0.0      # rad (fixed)

# Create initial rotation matrix R1 (extrinsic ZYX)
r1 = R.from_euler('ZYX', [yaw1, pitch1, roll1])
R1 = r1.as_matrix()

# Step 2: Invert the rotation matrix
R2_target = R1.T  # R^-1 = R.T for pure rotation matrix

# Step 3: Minimize || R_candidate - R2_target ||_F with yaw = 0
def objective(x):
    roll2, pitch2 = x
    r_candidate = R.from_euler('ZYX', [0.0, pitch2, roll2])
    return np.linalg.norm(r_candidate.as_matrix() - R2_target)

# Initial guess [0, 0]
result = minimize(objective, [0.0, 0.0])
roll2, pitch2 = result.x

# Output result
print("Initial rotation:")
print("  roll1  =", roll1)
print("  pitch1 =", pitch1)
print("  yaw1   =", yaw1)

print("\nRecovered inverse rotation (yaw=0 constraint):")
print("  roll2  =", roll2)
print("  pitch2 =", pitch2)
print("  yaw2   = 0.0")
