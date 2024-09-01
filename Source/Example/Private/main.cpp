#if defined(__clang__)
#define Meta(...) __attribute__((annotate(#__VA_ARGS__)))
#else
#define Meta(...)
#endif

#define Class(...) class Meta(type=class) __VA_ARGS__

Class(TestA)
{
public:
    class B
    {
    public:
        int x;
    };
public:
    Meta(true)
    int test_x;
private:
    Meta(This looks good)
    int test_y;
};

typedef TestA hhh;

int main()
{
    
    return 0;
}