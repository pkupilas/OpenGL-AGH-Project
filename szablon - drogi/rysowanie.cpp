/*

C++ przez OpenGL - szablon do �wicze� laboratoryjnych
(C) Micha� Turek.

*/

#ifdef _RYSOWANIE


/******************* SZABLON **************************/




// Tekstura podloza jest zapisana w pliku "data/land.bmp", definiowana bezpo�rednio w 3ds. 
// Wymagany format pliku: bmp, 24 bity na pixel.

glPushMatrix();
glTranslatef(0, 1, 0);
rysujModel("teren"); // malowanie pod�o�a
rysujModel("niebo"); // malowanie nieba
glPopMatrix();




/******************************************************/


#undef _RYSOWANIE
#endif
