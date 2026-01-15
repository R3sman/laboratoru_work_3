# simple_sort_comparison.py
import time
import random
import matplotlib.pyplot as plt

def insertion_sort(arr):
    arr = arr.copy()
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key
    return arr

def merge_sort(arr):
    if len(arr) <= 1:
        return arr
    mid = len(arr) // 2
    left = merge_sort(arr[:mid])
    right = merge_sort(arr[mid:])
    
    result = []
    i = j = 0
    while i < len(left) and j < len(right):
        if left[i] < right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    result.extend(left[i:])
    result.extend(right[j:])
    return result

# Основная программа
sizes = [100, 500, 1000, 2000, 5000, 10000]
insertion_times = []
merge_times = []

print("Тестирование сортировок...")
print("-" * 40)

for size in sizes:
    # Генерируем случайный массив
    arr = [random.randint(0, 10000) for _ in range(size)]
    
    # Тестируем сортировку вставками
    start = time.time()
    insertion_sort(arr)
    insertion_times.append(time.time() - start)
    
    # Тестируем сортировку слиянием
    start = time.time()
    merge_sort(arr)
    merge_times.append(time.time() - start)
    
    print(f"Размер: {size:5d} | Вставками: {insertion_times[-1]:.4f} сек | Слиянием: {merge_times[-1]:.4f} сек")

# Строим график
plt.figure(figsize=(10, 6))
plt.plot(sizes, insertion_times, 'ro-', label='Сортировка вставками', linewidth=2, markersize=8)
plt.plot(sizes, merge_times, 'bs-', label='Сортировка слиянием', linewidth=2, markersize=8)
plt.xlabel('Размер массива')
plt.ylabel('Время выполнения (сек)')
plt.title('Сравнение методов сортировки')
plt.grid(True, alpha=0.3)
plt.legend()
plt.tight_layout()
plt.show()

# Дополнительный график с логарифмической шкалой
plt.figure(figsize=(10, 6))
plt.loglog(sizes, insertion_times, 'ro-', label='Сортировка вставками', linewidth=2, markersize=8)
plt.loglog(sizes, merge_times, 'bs-', label='Сортировка слиянием', linewidth=2, markersize=8)
plt.xlabel('Размер массива (log scale)')
plt.ylabel('Время выполнения (log scale)')
plt.title('Логарифмическое сравнение методов сортировки')
plt.grid(True, alpha=0.3, which='both')
plt.legend()
plt.tight_layout()
plt.show()
