template <typename T>
class Matrix;

template <typename T>
Matrix<T> operator+ (const Matrix<T> &lhs, const Matrix<T> & rhs);

template <typename T>
Matrix<T> combine_four(const Matrix<T> &ltop, const Matrix<T> & rtop, const Matrix<T> & lbot, const Matrix<T> &rbot);


template <typename T>
class Matrix{
private:
    T ** A = nullptr;
public:
    int * ref_count;
    
    int m, n;
    
    Matrix(int m, int n);
    
    T * operator[](int m) const;
	Matrix<T> operator()(int ms, int me, int ns, int ne) const;
    
    Matrix(const Matrix & src);
	Matrix<T> & operator=(const Matrix & src);
    Matrix(Matrix && src);
	Matrix<T> & operator=(Matrix && src);
    
    void print() const;
    
	friend Matrix<T> operator+<T> (const Matrix<T> & lhs, const Matrix<T> & rhs);
	friend Matrix<T> combine_four<T>(const Matrix<T> &ltop, const Matrix<T> & rtop, const Matrix<T> & lbot, const Matrix<T> &rbot);
    
    void free();
    ~Matrix();
};