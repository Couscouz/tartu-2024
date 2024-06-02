#ifndef DYNAMICLINE_H
#define DYNAMICLINE_H

template<class T>
class DynamicLine {

    public:
        T* p1; /* 1st point adress */
        T* p2; /* 2nd point adress */

        /**
         * \brief Parameterized constructor.
         *
         * This public method setup DynamicLine from 2 points adresses.
         * \param v1 1st point adress (T*)
         * \param v2 2nd point adress (T*)
         */
        DynamicLine (T* v1, T* v2) {
            p1 = v1;
            p2 = v2;
        };

        /**
         * \brief Copy constructor.
         *
         * This public method copy reference value
         * \param l The reference of a DynamicLine variable (DynamicLine&)
         */
        DynamicLine (const DynamicLine& l) {
            p1 = l.p1;
            p2 = l.p2;
        };

        /**
         * \brief Assignement operator.
         *
         * This public method get value of MyArray ref and copy it to current one
         * \param l The reference of a MyArray variable (MyArray&)
         */
        DynamicLine& operator= (const DynamicLine& l) {
            //check this element is not already l
            if (this != &l) {
                p1 = l.p1;
                p2 = l.p2;
            }
            return *this;
        };

        /**
         * \brief Destructor.
         *
         * This public method destroy the object by unallocating both points.
         */
        ~DynamicLine () {
            p1 = nullptr;
            p2 = nullptr;
        };
};

#endif // DYNAMICLINE_H
