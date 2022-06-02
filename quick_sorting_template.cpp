//Кухаренко Иван СКБ 211_2

#include <iostream>
#include <cmath>

using namespace std;

template<typename T>
void quick_sort(T* arr, int left, int right) {//функция быстрой сортировки, первый параметр-указатель на массив
	if ((right - left + 1) < 2) return;//       второй параметр-индекс левого элемента, третий параметр-индекс правого элемента
	else {
		T max = arr[left];
		T min = arr[left];
		int x;
		T a, av;

		for (int i = left + 1; i < right + 1; i++) {//нахожу минимальный элемент в массиве
			if (min > arr[i]) {
				min = arr[i];
			}
		}

		for (int i = left + 1; i < right + 1; i++) {//нахожу максимальный элемент в массиве
			if (max < arr[i]) {
				max = arr[i];
			}
		}

		av = (min + max) / 2;//нахожу среднее значение между максимальным и минимальным
		a = av;
		x = 1;

		for (int i = left; i < right + 1; i++) {//нахожу элемент, максимально приблеженный к среднему, и его индекс
			if (abs(av - arr[i]) < a) {
				a = abs(av - arr[i]);
				x = i;
			}
		}

		a = arr[x];//меняю местами самый правый элемент со средним, который нашли в цикле выше
		arr[x] = arr[right];
		arr[right] = a;

		for (int i = left, j = right - 1; i < j;) {
			if (arr[i] > arr[right]) {//иду слева направо по массиву, если нахожу элемент, который больше правого, выполняю след блок
				if (arr[j] <= arr[right]) {//теперь иду справа налево, если нахожу элемент, который меньше правого,
					a = arr[i];//            то меняю местами эти элементы
					arr[i] = arr[j];
					arr[j] = a;
					i++;//                   сдвигаюсь к следующим элементам
					j--;
				}
				else {//если не нашел элемента, который меньше правого, то сдвигаюсь справа налево на один элемент
					j--;
				}
			}
			else {//если не нашел элемента, который больше правого, то сдвигаюсь слева направо на один элемент
				i++;
			}
		}

		x = left;
		for (int i = left; i < right; i++) {//ищу место, куда можно переставить правый элемент так, что
			if (arr[i] <= arr[right]) {//     слева все элементы меньше либо равны этому правому элементу, а
				x = i + 1;//                  справа все элементы больше
			}
		}

		a = arr[x];//меняю правый элемент с элементом, индекс которого выьрали выше
		arr[x] = arr[right];
		arr[right] = a;

		quick_sort(arr, left, (x - 1));//рекурсивно применяю эту же функцию для левой части массива
		quick_sort(arr, (x + 1), right);//рекурсивно применяю эту же функцию для правой части массива
	}
}

int main() {
	setlocale(LC_ALL, "rus");

	int n;
	cout << "Введите количество элементов массива: " << endl;
	cin >> n;
	cout << endl << endl;

	cout << "Введите массив типа int: " << endl;//создаем массив типа int
	int* a_i = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> a_i[i];
		while (cin.fail()) {
			cout << "Неправильное значение, введите еще раз: " << endl;
			cin.clear();
			cin.ignore(32767, '\n');
			cin >> a_i[i];
		}
	}
	cout << endl << endl;

	cout << "Введите массив типа double: " << endl;//создаем массив типа double
	double* a_d = new double[n];
	for (int i = 0; i < n; i++) {
		cin >> a_d[i];
		while (cin.fail()) {
			cout << "Неправильное значение, введите еще раз: " << endl;
			cin.clear();
			cin.ignore(32767, '\n');
			cin >> a_d[i];
		}
	}
	cout << endl << endl;

	cout << "Введите массив типа char: " << endl;//создаем массив типа char
	char* a_ch = new char[n];
	for (int i = 0; i < n; i++) {
		cin >> a_ch[i];
		while (cin.fail()) {
			cout << "Неправильное значение, введите еще раз: " << endl;
			cin.clear();
			cin.ignore(32767, '\n');
			cin >> a_ch[i];
		}
	}
	cout << endl << endl;

	cout << "Отсортированный массив int: " << endl;//сортируем массив типа int
	quick_sort(a_i, 0, n - 1);
	for (int i = 0; i < n; i++) {
		cout << a_i[i] << " ";
	}
	cout << endl << endl;

	cout << "Отсортированный массив double: " << endl;//сортируем массив типа double
	quick_sort(a_d, 0, n - 1);
	for (int i = 0; i < n; i++) {
		cout << a_d[i] << " ";
	}
	cout << endl << endl;

	cout << "Отсортированный массив char: " << endl;//сортируем массив типа char
	quick_sort(a_ch, 0, n - 1);
	for (int i = 0; i < n; i++) {
		cout << a_ch[i] << " ";
	}
	cout << endl << endl;
}