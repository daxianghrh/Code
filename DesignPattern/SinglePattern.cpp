class SinglePattern {
public:
    static SinglePattern& getInstance() {
        static SinglePattern sp;
        return sp;
    }

private:
    SinglePattern() {}
    SinglePattern(const SinglePattern& sp) = delete;
    SinglePattern& operator= (const SinglePattern& sp) = delete;
};