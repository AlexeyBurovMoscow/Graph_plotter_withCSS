#ifndef GENERATOR_H
#define GENERATOR_H

namespace Hard {
    class Generator
    {
    private:
        int curvalue;
        int minvalue;
        int maxvalue;
    private:
        Generator();
    public:
        static Generator& instance();
        int getRandValue();
        ~Generator(){}

    };
}

#endif // GENERATOR_H
