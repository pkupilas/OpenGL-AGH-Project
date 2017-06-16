/*

C++ przez OpenGL - szablon do æwiczeñ laboratoryjnych
(C) Micha³ Turek.

*/

#ifdef _RYSOWANIE


/******************* SZABLON **************************/




// Tekstura podloza jest zapisana w pliku "data/land.bmp", definiowana bezpoœrednio w 3ds. 
// Wymagany format pliku: bmp, 24 bity na pixel.

glPushMatrix();
glTranslatef(0, 1, 0);
rysujModel("teren"); // malowanie pod³o¿a
rysujModel("niebo"); // malowanie nieba
glPopMatrix();




/******************************************************/


#undef _RYSOWANIE
#endif
