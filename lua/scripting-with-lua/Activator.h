template <typename T> class Activator {
    public:
    Activator(T t) {
    }
    
    template <typename Y> operator Y () {
        return Y();
    }
};
