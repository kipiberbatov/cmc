#ifndef _forman_h
#define _forman_h

#include "mesh.h"

mesh * forman(const mesh * m, const char * new_coordinates_format);

matrix_sparse **
forman_boundary(const mesh * m, const mesh * m_forman, matrix_sparse ** m_bd);

#endif /* _forman_h */
