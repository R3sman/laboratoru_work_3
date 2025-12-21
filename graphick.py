


import matplotlib.pyplot as plt
import numpy as np

# Данные из таблицы сравнения (заполните своими результатами)
sizes = [100, 500, 1000, 5000, 10000, 50000, 100000]
insertion_times = []  # заполнить из вывода программы
merge_times = []      # заполнить из вывода программы

# Если нет данных, используем теоретические значения O(n^2) и O(n log n)
if not insertion_times:
    insertion_times = [size**2 / 10000000 for size in sizes]
    merge_times = [size * np.log2(size) / 1000000 for size in sizes]

plt.figure(figsize=(12, 5))

# График 1: Время выполнения
plt.subplot(1, 2, 1)
plt.plot(sizes, insertion_times, 'o-', label='Прямое включение (O(n²))')
plt.plot(sizes, merge_times, 's-', label='Слиянием (O(n log n))')
plt.xlabel('Размер массива')
plt.ylabel('Время выполнения (сек)')
plt.title('Сравнение времени сортировки')
plt.legend()
plt.grid(True, alpha=0.3)

# График 2: Ускорение
plt.subplot(1, 2, 2)
speedup = [insertion_times[i] / merge_times[i] if merge_times[i] > 0 else 0 
           for i in range(len(sizes))]
plt.plot(sizes, speedup, 'o-', label='Ускорение')
plt.xlabel('Размер массива')
plt.ylabel('Во сколько раз быстрее')
plt.title('Ускорение сортировки слиянием')
plt.legend()
plt.grid(True, alpha=0.3)

plt.tight_layout()
plt.savefig('sorting_comparison.png', dpi=150)
plt.show()

print("Анализ результатов:")
print("1. Сортировка прямым включением имеет сложность O(n²)")
print("2. Сортировка слиянием имеет сложность O(n log n)")
print("3. Для небольших массивов разница незначительна")
print("4. Для больших массивов сортировка слиянием значительно быстрее")