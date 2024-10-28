import matplotlib.pyplot as plt

x = [0, 1, 2, 3, 4]
y = [3.881086, 3.017097, 2.946905, 3.482113, 3.262930]


plt.bar(x, y)
plt.title('Tree node making')
plt.xlabel('Epoch')       
plt.ylabel('Elapsed (ms)')
plt.grid(axis = 'y')

# Y 축의 최대값 설정
plt.ylim(0, 5)  # Y 축의 최소값 0, 최대값 30으로 설정

for i in range(len(x)):
    plt.text(x[i], y[i] + 0.1, str(y[i]), ha='center', va='bottom')

plt.show()
