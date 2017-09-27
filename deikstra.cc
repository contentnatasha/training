#include <iostream>
#include <vector>
#include <climits>

class Matrix {
public:
	Matrix(size_t n) : N(n), v(n*n) {
	}
	int& operator() (size_t row, size_t col) {
		return v[row*N + col];
	}
	const int& operator() (size_t row, size_t col) const {
		return v[row*N + col];
	}
	size_t size() const {
		return N;
	}
        int get (size_t row, size_t col) {
          return v[row*N + col];
        }
        void set (size_t row, size_t col, int value) {
          v[row*N + col] = value;
        } 
        void readMatrix() {
          int value;
	  for (size_t row = 0; row < size(); row++) {
		for (size_t col = 0; col < size(); col++) {
                  std::cin >> value;
		  set(row, col, value);
		}
	  }
        }
        void printMatrix() {
	  for (size_t row = 0; row < size(); row++) {
		for (size_t col = 0; col < size(); col++) {
			std::cout << get(row,col) << " ";
		}
		std::cout << std::endl;
	  }
        }
private:
	size_t N;
	std::vector<int> v;
};





int Deikstra(Matrix m, int start, int finish) {
	size_t N = m.size();
	std::vector<bool> visited(N, false); 
	std::vector<int> weights(N, INT_MAX);
	weights[start] = 0;
	for (size_t i = 0; i < N; i++) { // we don't use i anywhere here, just to make sure we visited all N vertices
		//finding the vertice with minimal weight
		int cur_weight = INT_MAX;
		int cur_vertice;
		for (size_t j = 0; j < N; j++) {
			if (!visited[j] && (weights[j] < cur_weight) ) {
				cur_weight = weights[j];
				cur_vertice = j;
			}
		}
		visited[cur_vertice] = true;
		// update all the vertice neighbores of cur_vertice
		for (size_t j = 0; j < N; j++) {
			if (!visited[j] && ( m(cur_vertice, j)!=-1 ) && ( weights[cur_vertice] + m(cur_vertice, j) < weights[j]) ) {
				weights[j] = weights[cur_vertice] + m(cur_vertice, j);
			}
		}
	}
	return (weights[finish] == INT_MAX) ? -1 : weights[finish];
}

int main() {
	size_t NVertice;
	std::cin >> NVertice;
	int start, finish;
	std::cin >> start;
	std::cin >> finish;
	Matrix m(NVertice);
        m.readMatrix();
	//std::cout << m(0,2) << " " << m(1,0) << std::endl;
	//PrintMatrix(m);
	std::cout << Deikstra(m, start-1, finish-1) << std::endl;
}
