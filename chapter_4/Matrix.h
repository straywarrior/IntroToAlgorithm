
class Matrix{
private:
    int ** A = nullptr;
public:
    int ref_count;
    
    int m, n;
    
    Matrix(int m, int n);
    
    int * operator[](int m) const;
    Matrix operator()(int ms, int me, int ns, int ne) const;
    
    void print() const;
    
    friend Matrix operator+ (const Matrix & lhs, const Matrix & rhs);
    friend Matrix combine_four(const Matrix &ltop, const Matrix & rtop, const Matrix & lbot, const Matrix &rbot);
    
    ~Matrix();
};