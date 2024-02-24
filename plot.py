import matplotlib.pyplot as plt

# Read data from the CSV file
data = []
with open('data.txt', 'r') as file:
    for line in file:
        data_point = list(map(float, line.strip().split(',')))
        data.append(data_point)

# Extract x and y values
x_values = [point[0] for point in data]

# Plot the data
for i in range(len(data[0]) - 1):
    plt.plot(x_values, [point[i + 1] for point in data], color='b')
plt.xlabel('X')
plt.ylabel('Y')
plt.title('Data from text file')
plt.grid(True)
plt.show()