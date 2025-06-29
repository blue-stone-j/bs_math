import random
import csv

# 定义序列的长度
n_x = 50  # 可以根据需要调整这个值
# 生成序列
x_values = []
for i in range(n_x):
    r = random.uniform(-0.01, 0.01)
    x = i + r
    # 格式化为3位小数
    formatted_x = format(x, ".3f")
    x_values.append(formatted_x)

n_y=200
y_values = []
for i in range(n_y):
    r = random.uniform(-0.01, 0.01)
    y = n_x/n_y*i + r
    # 格式化为3位小数
    formatted_y = format(y, ".3f")
    y_values.append(formatted_y)

# 文件保存路径
file_path = 'output.csv'

# 将数据写入CSV文件，使用空格作为分隔符
with open(file_path, 'w', newline='') as file:
    writer = csv.writer(file, delimiter=' ')
    writer.writerow(y_values)
    writer.writerow(x_values)

print(f"数据已保存到文件：{file_path}，并保留了3位小数。")
