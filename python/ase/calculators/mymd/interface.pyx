# distutils: language = c++
# distutils: sources = MyMD.cpp
""" Defines interface to MyMD C++ library

This module implements the interface to C++ classes and functions
within MyMD that allow to interface the MyMD library directly.
This allows a much higher level of flexibility than communicating
with the binary via an input file.

This interface was created following the tutorial on
http://docs.cython.org/src/userguide/wrapping_CPlusPlus.html

"""
import cython


#class MyMD {
#  public:
#    /* Variables */
#    Integrator *integrator;
#    Force *force;
#    Atom *atom;
#
#    /* Methods */
#    void MyMD();
#    void ~MyMD();
#    void MDLoop();
#  private:
#    void readInput();
#    void allocateMemory();
#    void readRestart():
#}

cdef extern from "../../../../INC/MyMD.h":
    cdef cppclass MyMD:
        MyMD() except +
        void MDLoop()
        void readInput()
        void allocateMemory()
        void readRestart()

cdef MyMD *m = new MyMD()
