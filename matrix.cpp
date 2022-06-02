#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <string>
#include <mutex>

std::mutex mut;

template<typename T>
class Matrix;

template<typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& mat) {
	for (int i = 0; i < mat.N; i++) {
		for (int j = 0; j < mat.M; j++) {
			out << mat.num[i][j] << " ";
		}
		out << std::endl;
	}
	return out;
}

template<typename T>
class Matrix {//объявление структуры
	int N;
	int M;
	std::vector<std::vector<T>> num;
	friend std::ostream& operator<<<T>(std::ostream&, const Matrix&);
public:
	Matrix() {
		N = 0;
		M = 0;
	}
	Matrix(int n, int m) {
		N = n;
		M = m;
		num.assign(N, std::vector<T>(M));
	}
	Matrix(std::initializer_list<std::pair<std::pair<int, int>, T>> l) {
		int n = 0, m = 0;
		const std::pair<std::pair<int, int>, T>* l_ptr = l.begin();
		for (; l_ptr != l.end(); l_ptr++) {
			if ((*l_ptr).first.first > n) {
				n = (*l_ptr).first.first;
			}
			if ((*l_ptr).first.second > m) {
				m = (*l_ptr).first.second;
			}
		}
		N = n + 1;
		M = m + 1;
		num.assign(N, std::vector<T>(M));
		l_ptr = l.begin();
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				num[i][j] = 0;
			}
		}
		for (; l_ptr != l.end(); l_ptr++) {
			num[(*l_ptr).first.first][(*l_ptr).first.second] = (*l_ptr).second;
		}
	}
	Matrix(const Matrix& Mt) {
		this->num.assign(Mt.N, std::vector<T>(Mt.M));
		this->N = Mt.N;
		this->M = Mt.M;
		for (int i = 0; i < this->N; i++) {
			for (int j = 0; j < this->M; j++) {
				this->num[i][j] = Mt.num[i][j];
			}
		}
	}
	Matrix(Matrix&& Mt) {
		*this = Mt;
	}
	void making_rand();
	void create(std::string&&);
	void rewrite(std::string&&);
	T lines();
	T columns();
	Matrix operator*(const Matrix&);
	Matrix operator*(const double);
	friend Matrix&& operator*(const double, const Matrix&);
	Matrix operator+(const Matrix&);
	Matrix operator-(const Matrix&);
	Matrix operator!();
	double det();
	Matrix transp();
	T dop(int, int);
	Matrix matrix_dop();
	Matrix reverse();
	bool operator==(const Matrix&);
	bool operator==(const int);
	Matrix operator=(Matrix&&) noexcept;
	Matrix operator=(const Matrix&);
	static Matrix matrix_1(const int);
	static Matrix matrix_0(const int, const int);
	void print();
};

template<typename T>
void Matrix<T>::making_rand() {
	for (int i = 0; i < this->N; i++) {
		for (int j = 0; j < this->M; j++) {
			this->num[i][j] = std::rand() % 10;
		}
	}
}

template<typename T>
void Matrix<T>::create(std::string&& file_name) {
	std::ifstream file;
	file.open(std::move(file_name));
	if (!file.is_open()) { throw "Can't open this file"; }
	else {
		if (file) {
			file >> N;
			file >> M;
			num.assign(N, std::vector<T>(M));
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M; j++) {
					file >> num[i][j];
				}
			}
		}
	}
	file.close();
}

template<typename T>
void Matrix<T>::rewrite(std::string&& file_name) {
	std::ifstream file;
	file.open(std::move(file_name));
	if (!file.is_open()) { throw "Can't open this file"; }
	else {
		if (file) {
			num.assign(this->N, std::vector<T>(M), 0);
			for (int i = 0; i < this->N; i++) {
				for (int j = 0; j < this->M; j++) {
					file >> num[i][j];
				}
			}
		}
	}
	file.close();
}

template<typename T>
T Matrix<T>::lines() {
	return N;
}

template<typename T>
T Matrix<T>::columns() {
	return M;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix& Mt) {
	if (this->M != Mt.N) { break; }
	else {
		mut.lock();
		Matrix mat(this->N, Mt.M);
		std::thread* thd = new std::thread[this->N];
		for (int i = 0; i < this->N; i++) {
			thd[i] = std::thread([&mat, &i, this, &Mt]() {
				for (int j = 0; j < Mt.M; j++) {
					int sum = 0;
					for (int k = 0; k < this->M; k++) {
						sum += this->num[i][k] * Mt.num[k][j];
					}
					mat.num[i][j] = sum;
				}
				});
		}
		for (int i = 0; i < this->N; i++) {
			thd[i].join();
		}
		mut.unlock();
		return mat;
	}
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const double k) {
	mut.lock();
	Matrix mat(this->N, this->M);
	std::thread* thd = new std::thread[this->N];
	for (int i = 0; i < this->N; i++) {
		thd[i] = std::thread([&mat, this, &k, &i]() {
			for (int j = 0; j < this->M; j++) {
				mat.num[i][j] = this->num[i][j] * k;
			}
			});
	}
	for (int i = 0; i < this->N; i++) {
		thd[i].join();
	}
	mut.unlock();
	return mat;
}

template<typename T>
Matrix<T> operator*(const double k, const Matrix<T>& Mt) {
	return Mt * k;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& Mt) {
	if (this->N != Mt.N && this->M != Mt.M) { throw "Can't fold"; }
	else {
		mut.lock();
		Matrix mat(this->N, this->M);
		std::thread* thd = new std::thread[this->N];
		for (int i = 0; i < this->N; i++) {
			thd[i] = std::thread([&mat, &Mt, this, &i]() {
				for (int j = 0; j < this->M; j++) {
					mat.num[i][j] = this->num[i][j] + Mt.num[i][j];
				}
				});
		}
		for (int i = 0; i < this->N; i++) {
			thd[i].join();
		}
		mut.unlock();
		return mat;
	}
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix& Mt) {
	if (this->N != Mt.N && this->M != Mt.M) { break; }
	else {
		mut.lock();
		Matrix mat(this->N, this->M);
		std::thread* thd = new std::thread[this->N];
		for (int i = 0; i < this->N; i++) {
			thd[i] = std::thread([&mat, &Mt, this, &i]() {
				for (int j = 0; j < this->M; j++) {
					mat.num[i][j] = this->num[i][j] - Mt.num[i][j];
				}
				});
		}
		for (int i = 0; i < this->N; i++) {
			thd[i].join();
		}
		mut.unlock();
		return mat;
	}
}

template<typename T>
Matrix<T> Matrix<T>::operator!() {
	return this->reverse();
}

template<typename T>
double Matrix<T>::det() {
	if (this->N == this->M) {
		int d = this->N;
		if (d == 1)
			return this->num[0][0];
		else if (d == 2)
			return this->num[0][0] * this->num[1][1] - this->num[0][1] * this->num[1][0];//детерминант матрицы 2х2
		else {
			double sum = 0;
			for (int k = 0; k < d; k++) {
				Matrix mat(this->N - 1, this->M - 1);
				for (int i = 0; i < d - 1; i++) {
					for (int j = 0; j < d - 1; j++) {
						if (j < k) {
							mat.num[i][j] = this->num[i + 1][j];
						}
						else {
							mat.num[i][j] = this->num[i + 1][j + 1];
						}
					}
				}
				sum += int(pow(-1, k + 2)) * this->num[0][k] * mat.det();
			}
			return sum;
		}
	}
	else { throw "Matrix hasn't the determinant"; }
}

template<typename T>
Matrix<T> Matrix<T>::transp() {//находим присоединенную и транспонируем ее
	Matrix mat(this->M, this->N);
	for (int i = 0; i < this->N; i++) {
		for (int j = 0; j < this->M; j++) {
			mat.num[j][i] = this->num[i][j];
		}
	}
	return mat;
}

template<typename T>
T Matrix<T>::dop(int i, int j) {//находим алгебраическое дополнение матрицы на позиции i, j
	Matrix mat(this->N - 1, this->M - 1);
	for (int k = 0; k < this->N - 1; k++) {
		for (int l = 0; l < this->M - 1; l++) {
			if (k < i && l < j) {
				mat.num[k][l] = this->num[k][l];
			}
			else if (k >= i && l < j) {
				mat.num[k][l] = this->num[k + 1][l];
			}
			else if (k < i && l >= j) {
				mat.num[k][l] = this->num[k][l + 1];
			}
			else if (k >= i && l >= j) {
				mat.num[k][l] = this->num[k + 1][l + 1];
			}
		}
	}
	return pow(-1, i + j) * mat.det();
}

template<typename T>
Matrix<T> Matrix<T>::matrix_dop() {
	mut.lock();
	Matrix mat(this->N, this->M);
	mat = *this;
	std::thread* thd = new std::thread[this->N];
	for (int i = 0; i < this->N; i++) {
		thd[i] = std::thread([&mat, this, i]() {
			for (int j = 0; j < this->M; j++) {
				mat.num[i][j] = this->dop(i, j);
			}
			});
	}
	for (int i = 0; i < this->N; i++) {
		thd[i].join();
	}
	mat = mat.transp();
	mut.unlock();
	return mat;
}

template<typename T>
Matrix<T> Matrix<T>::reverse() {//создаем обратную матрицу
	T deter = this->det();
	if (deter == 0) { throw "No reverse matrix"; }
	else {
		Matrix mat(this->M, this->N);
		mat = this->matrix_dop();
		for (int i = 0; i < this->N; i++) {
			for (int j = 0; j < this->M; j++) {
				mat.num[i][j] = double(mat.num[i][j]) / double(deter);
			}
		}
		return mat;
	}
}

template<typename T>
bool Matrix<T>::operator==(const Matrix& Mt) {
	if (this->N != Mt.N || this->M != Mt.M) { return false; }
	else {
		int n = 0;
		for (int i = 0; i < this->N; i++) {
			for (int j = 0; j < this->M; j++) {
				if (this->num[i][j] != Mt.num[i][j]) { return false; }
			}
		}
		return true;
	}
}

template<typename T>
bool Matrix<T>::operator==(const int num) {
	if (num != 1 || num != 0) { throw "Unexpected number for comparing"; }
	else {
		int n = 0;
		for (int i = 0; i < this->N; i++) {
			for (int j = 0; j < this->M; j++) {
				if (this->num[i][j] != num) { return false; }
			}
		}
		return true;
	}
}

template<typename T>
Matrix<T> Matrix<T>::operator=(Matrix&& Mt) noexcept {
	this->num.assign(Mt.N, std::vector<T>(Mt.M));
	this->N = Mt.N;
	this->M = Mt.M;
	for (int i = 0; i < this->N; i++) {
		for (int j = 0; j < this->M; j++) {
			this->num[i][j] = Mt.num[i][j];
		}
	}
	for (int i = 0; i < Mt.N; i++) {
		Mt.num[i].clear();
	}
	Mt.N = 0;
	Mt.M = 0;
	return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator=(const Matrix& Mt) {
	this->num.assign(Mt.N, std::vector<T>(Mt.M));
	this->N = Mt.N;
	this->M = Mt.M;
	for (int i = 0; i < this->N; i++) {
		for (int j = 0; j < this->M; j++) {
			this->num[i][j] = Mt.num[i][j];
		}
	}
	return *this;
}

template<typename T>
static Matrix<T> Matrix<T>::matrix_1(const int n) {
	Matrix mat(n, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) { mat.num[i][j] = 1; }
			else { mat.num[i][j] = 0; }
		}
	}
	return mat;
}

template<typename T>
static Matrix<T> Matrix<T>::matrix_0(const int n, const int m) {
	Matrix mat(n, m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			mat.num[i][j] = 0;
		}
	}
	return mat;
}

template<typename T>
void Matrix<T>::print() {
	for (int i = 0; i < this->N; i++) {
		for (int j = 0; j < this->M; j++) {
			std::cout << this->num[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

int main() {
	setlocale(LC_ALL, "rus");
	try {
		std::string name;
		//Matrix<double> mat(5, 5);
		Matrix<double> mat;
		Matrix<double> mat_rev, mat_rev2;
		Matrix<double> mat_l{ std::make_pair(std::make_pair(0,0),1), std::make_pair(std::make_pair(0,1),2), std::make_pair(std::make_pair(1,0),3), std::make_pair(std::make_pair(1,1),4) };
		//mat.making_rand();
		std::cout << mat;
		std::cout << "Введите имя файла для записи матрицы" << std::endl;
		std::cin >> name;
		mat.create(std::move(name));
		std::cout << mat;
		Matrix<double> mat1(std::move(mat));
		mat_rev = !mat1;
		std::cout << mat_rev;
		mat_rev2 = std::move(mat_rev);
		std::cout << mat_rev;
		std::cout << mat;
		std::cout << mat_l;
	}
	catch (const char* msg) {
		std::cerr << msg << std::endl;
	}

	return 0;
}