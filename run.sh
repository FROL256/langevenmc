# ==== BUILD LANGEVIN ====
g++ console/langevin/*.cpp \
    -I sdk -I home \
    -L. -linal -lsdk -lm \
    -w \
    -o langevin.out


# ==== RUN EXECUTABLE ====
LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH ./langevin.out
