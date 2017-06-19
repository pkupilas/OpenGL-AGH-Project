/*

 OpenGL - Szablon 3D do cwiczen laboratoryjnych
 (C) Micha³ Turek.

*/

#include <windows.h>
#include "glut.h"
#include "glaux.h"

#include "model3DS.h"
#include <time.h>
#include <direct.h>

#include <Main.h>
#include <math.h>	





//#include <GL/glaux.h>
//#define GLUTCHECKLOOP

	
// Wymiary okna
int oknoSzerkosc=800;
int oknoWysokosc=600;
bool oknoFullScreen = false;
GLint oknoLewe = 1, oknoPrawe = 2;      // id okien stereo 

UINT SkyboxTexture[12];
float rotateSky = 0.0f;
float lightDay = 1.0f;
float lightNight = 0.0f;
float timeOfDay = 1.0f;


// Opcje projekcji stereo
int stereoTryb = 0;
int stereoRozstawOczu = 3;				// dystans miêdzy oczami
int stereoPunktPatrzenia = 80;			// odleg³oœæ do punktu, na który patrz¹ oczy
bool stereoIDRamki = false;	
bool timing100FPS = true;				// flaga polecenia odmierzania czasu

// Kamera
int pozycjaMyszyX;						// na ekranie
int pozycjaMyszyY;
double kameraX;
double kameraY;
double kameraZ;
double kameraPunktY;
double kameraPredkoscPunktY;
double kameraPredkosc;
bool kameraPrzemieszczanie;		// przemieszczanie lub rozgl¹danie
double kameraKat;				// kat patrzenia
double kameraPredkoscObrotu;	
#define MIN_DYSTANS 0.5			// minimalny dystans od brzegu obszaru ograniczenia kamery
double obszarKamery = 0;

#define _DEFINICJE
#include "definicje.cpp"


		/** REJESTRATOR PRZESZKOD **/

struct przeszkoda{
	przeszkoda *next;
	double posX1;
	double posZ1;
	double posX2;
	double posZ2;
};
przeszkoda *obszarPrzeszkody = NULL;

void resetKamery(){
	kameraX = 20;
	kameraY = -0.5;
	kameraZ = 40;
	kameraKat = -0.4;
	kameraPunktY = -15;
	kameraPredkoscPunktY = 0;
	kameraPredkosc = 0;
	kameraPredkoscObrotu = 0;
	kameraPrzemieszczanie = true;
}

void ustalObszar (double X){
	obszarKamery = X;	
}

bool wObszarze(double posX, double posZ){ 
	if ( posX*posX + posZ*posZ > (obszarKamery-MIN_DYSTANS*2)*(obszarKamery-MIN_DYSTANS*2) ) return false;
	przeszkoda * pom = obszarPrzeszkody;
	while (pom){
		if (pom->posX1 < posX && 
			pom->posX2 > posX && 
			pom->posZ1 < posZ && 
			pom->posZ2 > posZ ) return false;
		pom = pom -> next;
	}
	return true;
}

void rejestrujPrzeszkode(double X1, double Z1, double X2, double Z2){
	przeszkoda * pom = new przeszkoda;
	if (X1 > X2) {double tmp = X1; X1 = X2; X2 = tmp;}
	if (Z1 > Z2) {double tmp = Z1; Z1 = Z2 ;Z2 = tmp;}
	pom -> posX1 = X1;
	pom -> posZ1 = Z1;
	pom -> posX2 = X2;
	pom -> posZ2 = Z2;
	pom -> next = obszarPrzeszkody;
	obszarPrzeszkody = pom;
}

		/** OBSLUGA INTERAKCJI Z UZYTKOWNIKIEM **/

void SzablonPrzyciskMyszyWcisniety (int button, int state, int x, int y)
{
	switch (state)
	{
		case GLUT_UP:
			kameraPredkosc = 0;
			kameraPredkoscObrotu = 0;
			kameraPredkoscPunktY = 0;
		break;
		case GLUT_DOWN:
				pozycjaMyszyX = x;
				pozycjaMyszyY = y;
			if (button == GLUT_LEFT_BUTTON)
				kameraPrzemieszczanie = true;
			else 
				kameraPrzemieszczanie = false;
		break;
	}
}

void SzablonRuchKursoraMyszy (int x, int y)
{
	kameraPredkoscObrotu = -(pozycjaMyszyX - x) * 0.001;
	if (kameraPrzemieszczanie)
	{
		kameraPredkosc = (pozycjaMyszyY - y) * 0.02;
		kameraPredkoscPunktY = 0;
	} else {
		kameraPredkoscPunktY = (pozycjaMyszyY - y) * 0.06;
		kameraPredkosc = 0;
	}
}

void SzablonKlawiszKlawiaturyWcisniety (GLubyte key, int x, int y)
{
   switch (key) {
   case 27:    
      exit(1);
   break;
   case ' ':    
      if (stereoTryb != 2) glutFullScreen();
      break;

   }

}

		/** INICJALIZACJA **/

#define _INTERAKCJA
#include "interakcja.cpp"

void windowInit()
{
	glClearColor(0.2, 0.2, 1.0, 0.0);			
    glShadeModel(GL_SMOOTH);					
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST); 
	glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); 
	glEnable(GL_LIGHTING);
	GLfloat  ambient[4] = {0.3,0.3,0.3,0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient); 
	GLfloat  ambientLight[4] = {0.3,0.3,0.3,0};
	GLfloat  specularLight[4] = {1.0,1.0,1.0,0};
	GLfloat  diffuseLight[4] = {1,1,1,0};
	GLfloat	 lightPos0[4] = {30,30,-30,1};

	/*******************MGLA**************************/

	float fogColor[4]= {0.7f, 0.7f, 0.7f, 0.1f};
	glFogi(GL_FOG_MODE,GL_EXP2); // [GL_EXP, GL_EXP2, GL_LINEAR ]
	glFogfv(GL_FOG_COLOR, fogColor); 
	glFogf(GL_FOG_DENSITY, 0.005f); 
	glFogf(GL_FOG_START, 0.0f); 
	glFogf(GL_FOG_END, 100.0f); 
	//glEnable(GL_FOG);  

}

void rozmiar (int width, int height)
{
	if (width==0) width++;
	if (width==0) width++;
	if (stereoTryb != 2) {
		oknoSzerkosc=width;   // przy stereo nie mo¿na zmieniaæ rozmiaru
		oknoWysokosc=height; 
	}
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glViewport(0,0,oknoSzerkosc,oknoWysokosc+24); 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
    gluPerspective(45.0f,(GLfloat)oknoSzerkosc/(GLfloat)oknoWysokosc,1.0f,10000.0f);
    glMatrixMode(GL_MODELVIEW);
}

void rozmiarLewe (int width, int height)
{
	glutSetWindow(oknoLewe);
	rozmiar (width, height);
}

void rozmiarPrawe (int width, int height)
{
	glutSetWindow(oknoPrawe);
	rozmiar (width, height);
}

		/** ZARZADANIE SKLADEM MODELI 3DS **/

struct model_w_skladzie {
	char * filename;
	model3DS * model;
	struct model_w_skladzie *wsk;
};
struct model_w_skladzie* sklad_modeli = NULL;

void dodajModel (model3DS * _model, char* file_name)
{
    struct model_w_skladzie* tmp;
    tmp = (struct model_w_skladzie *) malloc (sizeof(struct model_w_skladzie));
    tmp -> filename  = (char *) malloc(strlen(file_name)+1);
    strcpy( tmp -> filename, file_name);
    tmp -> model = _model;
    tmp->wsk = sklad_modeli;
    sklad_modeli = tmp;
}

model3DS * pobierzModel (char* file_name)
{
	struct model_w_skladzie* sklad_tmp = sklad_modeli;
	while (sklad_tmp){
		if (!_stricmp(sklad_tmp->filename,file_name)) return sklad_tmp->model;
		char file_name_full[_MAX_PATH];
			strcpy (file_name_full,file_name);
			strcat (file_name_full,".3ds");
		if (!_stricmp(sklad_tmp->filename,file_name_full)) return sklad_tmp->model;

		sklad_tmp = sklad_tmp->wsk;
	}
	return NULL;
}

void rysujModel(char * file_name, int tex_num = -1 )
{
	model3DS * model_tmp;	
	if (model_tmp = pobierzModel (file_name))
		if (tex_num == -1) 
			model_tmp -> draw();
		else
			model_tmp -> draw(tex_num, false);
		
}

void aktywujSpecjalneRenderowanieModelu(char * file_name, int spec_id = 0)
{
	model3DS * model_tmp;	
	if (model_tmp = pobierzModel (file_name))
		model_tmp->setSpecialTransform(spec_id);
}

void ladujModele()
{
	WIN32_FIND_DATA *fd;
	HANDLE fh;
	model3DS * model_tmp;
	char directory[_MAX_PATH];
	if( _getcwd( directory, _MAX_PATH ) == NULL ) return;
	strcat (directory,"\\data\\*.3ds");
	
	fd = (WIN32_FIND_DATA *)malloc(sizeof(WIN32_FIND_DATA));
	fh = FindFirstFile((LPCSTR) directory,fd);
	if(fh != INVALID_HANDLE_VALUE)
		do {
			if(fd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){	// katalogi ignorujemy
				if (FindNextFile(fh,fd)) continue; else break;
			}
			// ladowanie obiektu i dodanie do kontenera
			char filename[_MAX_PATH];
			strcpy (filename,"data\\");
			strcat (filename,fd->cFileName);
			model_tmp = new model3DS (filename,1,stereoTryb == 2);
			dodajModel (model_tmp,fd->cFileName);
			printf("[3DS] Model '%s' stored\n",fd->cFileName);
		} while(FindNextFile(fh,fd));
}

/**********************************************************
 		RYSOWANIE TRESCI RAMKI
 *********************************************************/

void rysujRamke(bool prawa)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Kasowanie ekranu
	glLoadIdentity();
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);

	// Load the Skybox textures
	JPEG_Skybox(SkyboxTexture, "data/texture/front.jpg", SKYFRONT);
	JPEG_Skybox(SkyboxTexture, "data/texture/back.jpg", SKYBACK);
	JPEG_Skybox(SkyboxTexture, "data/texture/left.jpg", SKYLEFT);
	JPEG_Skybox(SkyboxTexture, "data/texture/right.jpg", SKYRIGHT);
	JPEG_Skybox(SkyboxTexture, "data/texture/up.jpg", SKYUP);
	JPEG_Skybox(SkyboxTexture, "data/texture/down.jpg", SKYDOWN);
	JPEG_Skybox(SkyboxTexture, "data/texture/front2.jpg", SKYFRONT2);
	JPEG_Skybox(SkyboxTexture, "data/texture/back2.jpg", SKYBACK2);
	JPEG_Skybox(SkyboxTexture, "data/texture/left2.jpg", SKYLEFT2);
	JPEG_Skybox(SkyboxTexture, "data/texture/right2.jpg", SKYRIGHT2);
	JPEG_Skybox(SkyboxTexture, "data/texture/up2.jpg", SKYUP2);
	JPEG_Skybox(SkyboxTexture, "data/texture/down2.jpg", SKYDOWN2);

	
	switch (stereoTryb){
		case 0: // zwykle mono
			 gluLookAt (kameraX,kameraY,kameraZ,kameraX + 100*sin(kameraKat),3 + kameraPunktY	,kameraZ - 100*cos(kameraKat),0,1,0); // kamera
		break;
		case 1: // 3D-ready
		case 2: // pelne stereo
		case 3: // anaglyph
			if (prawa){			//  klatka prawa
				float newKameraX = kameraX - stereoRozstawOczu/2*cos(kameraKat);
				float newKameraZ = kameraZ - stereoRozstawOczu/2*sin(kameraKat);
				gluLookAt (newKameraX,kameraY,newKameraZ,kameraX+0.2 + stereoPunktPatrzenia*sin(kameraKat),3 + kameraPunktY	,kameraZ - stereoPunktPatrzenia*cos(kameraKat),0,1,0); // kamera
			}
			else {				// klatka lewa
				float newKameraX = kameraX + stereoRozstawOczu/2*cos(kameraKat);
				float newKameraZ = kameraZ + stereoRozstawOczu/2*sin(kameraKat);
				gluLookAt (newKameraX,kameraY,newKameraZ,kameraX+0.2 + stereoPunktPatrzenia*sin(kameraKat),3 + kameraPunktY	,kameraZ - stereoPunktPatrzenia*cos(kameraKat),0,1,0); // kamera
			}
		break;
	} //case


	#define _RYSOWANIE
	#include "rysowanie.cpp"	// rysowanie 
	  //=====================Light 0===============================================
	GLfloat	 lightPos0[4] = { 30,30,-30,1 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	glEnable(GL_LIGHT0);  // œwiatlo sceny
	GLfloat light_ambient[] = { 0, 0, 0, 1.0 };
	GLfloat light_diffuse[] = { lightDay, lightDay, lightDay, lightDay };
	GLfloat light_specular[] = { lightDay, lightDay, lightDay, lightDay };
	GLfloat light_position[] = { 30,30,-30,1 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	//=====================Light 1===============================================
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos0);
	glEnable(GL_LIGHT1);  // œwiatlo sceny
						  //	cycleLight -= 0.01f;
	GLfloat light_ambient1[] = { 0, 0, 0, 1.0 };
	GLfloat light_diffuse1[] = { lightNight, lightNight, lightNight, lightNight };
	GLfloat light_specular1[] = { lightNight, lightNight, lightNight, lightNight };
	GLfloat light_position1[] = { 30,30,-35,1 };
	GLfloat spot_direction1[] = { -1.0, -1.0, 0.0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 128);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction1);
	//=====================Light 2===============================================

	glLightfv(GL_LIGHT2, GL_POSITION, lightPos0);
	glEnable(GL_LIGHT2);  // œwiatlo sceny
	GLfloat light_ambient2[] = { 0, 0, 0, 1.0 };
	GLfloat light_diffuse2[] = { lightNight, lightNight, lightNight, lightNight };
	GLfloat light_specula2[] = { lightNight, lightNight, lightNight, lightNight };
	GLfloat light_position2[] = { 30,30,-15,1 };
	GLfloat spot_direction2[] = { -1.0, -1.0, 0.0 };


	glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_specula2);
	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 128);

	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 30.0);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction2);
	//=====================Light 3===============================================
	glLightfv(GL_LIGHT3, GL_POSITION, lightPos0);
	glEnable(GL_LIGHT3);  // œwiatlo sceny
	GLfloat light_ambient3[] = { 0, 0, 0, 1.0 };
	GLfloat light_diffuse3[] = { lightNight, lightNight, lightNight, lightNight };
	GLfloat light_specula3[] = { lightNight, lightNight, lightNight, lightNight };
	GLfloat light_position3[] = { 30,30,5,1 };
	GLfloat spot_direction3[] = { -1.0, -1.0, 0.0 };


	glLightfv(GL_LIGHT3, GL_AMBIENT, light_ambient3);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse3);
	glLightfv(GL_LIGHT3, GL_SPECULAR, light_specula3);
	glLightfv(GL_LIGHT3, GL_POSITION, light_position3);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 128);

	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 30.0);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot_direction3);
	//=====================Light 4===============================================
	glLightfv(GL_LIGHT4, GL_POSITION, lightPos0);
	glEnable(GL_LIGHT4);  // œwiatlo sceny
	GLfloat light_ambient4[] = { 0, 0, 0, 1.0 };
	GLfloat light_diffuse4[] = { lightNight, lightNight, lightNight, lightNight };
	GLfloat light_specula4[] = { lightNight, lightNight, lightNight, lightNight };
	GLfloat light_position4[] = { 30,30,20,1 };
	GLfloat spot_direction4[] = { -1.0, -1.0, 0.0 };


	glLightfv(GL_LIGHT4, GL_AMBIENT, light_ambient4);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, light_diffuse4);
	glLightfv(GL_LIGHT4, GL_SPECULAR, light_specula4);
	glLightfv(GL_LIGHT4, GL_POSITION, light_position4);
	glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 128);

	glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 30.0);
	glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, spot_direction4);
	//=====================Light 5===============================================
	glLightfv(GL_LIGHT5, GL_POSITION, lightPos0);
	glEnable(GL_LIGHT5);  // œwiatlo sceny
	GLfloat light_ambient5[] = { 0, 0, 0, 1.0 };
	GLfloat light_diffuse5[] = { lightNight, lightNight, lightNight, lightNight };
	GLfloat light_specula5[] = { lightNight, lightNight, lightNight, lightNight };
	GLfloat light_position5[] = { 30,30,40,1 };
	GLfloat spot_direction5[] = { -1.0, -1.0, 0.0 };


	glLightfv(GL_LIGHT5, GL_AMBIENT, light_ambient5);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, light_diffuse5);
	glLightfv(GL_LIGHT5, GL_SPECULAR, light_specula5);
	glLightfv(GL_LIGHT5, GL_POSITION, light_position5);
	glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 128);

	glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 30.0);
	glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, spot_direction5);
	//=====================Light 6===============================================
	glLightfv(GL_LIGHT6, GL_POSITION, lightPos0);
	glEnable(GL_LIGHT6);  // œwiatlo sceny
	GLfloat light_ambient6[] = { 0, 0, 0, 1.0 };
	GLfloat light_diffuse6[] = { lightNight, lightNight, lightNight, lightNight };
	GLfloat light_specula6[] = { lightNight, lightNight, lightNight, lightNight };
	GLfloat light_position6[] = { 30,30,58,1 };
	GLfloat spot_direction6[] = { -1.0, -1.0, 0.0 };


	glLightfv(GL_LIGHT6, GL_AMBIENT, light_ambient6);
	glLightfv(GL_LIGHT6, GL_DIFFUSE, light_diffuse6);
	glLightfv(GL_LIGHT6, GL_SPECULAR, light_specula6);
	glLightfv(GL_LIGHT6, GL_POSITION, light_position6);
	glLightf(GL_LIGHT6, GL_SPOT_EXPONENT, 128);

	glLightf(GL_LIGHT6, GL_SPOT_CUTOFF, 30.0);
	glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, spot_direction6);
	//=====================Light 7===============================================
	glLightfv(GL_LIGHT7, GL_POSITION, lightPos0);
	glEnable(GL_LIGHT7);  // œwiatlo sceny
	GLfloat light_ambient7[] = { 0, 0, 0, 1.0 };
	GLfloat light_diffuse7[] = { lightNight, lightNight, lightNight, lightNight };
	GLfloat light_specula7[] = { lightNight, lightNight, lightNight, lightNight };
	GLfloat light_position7[] = { 30,30,76,1 };
	GLfloat spot_direction7[] = { -1.0, -1.0, 0.0 };


	glLightfv(GL_LIGHT7, GL_AMBIENT, light_ambient7);
	glLightfv(GL_LIGHT7, GL_DIFFUSE, light_diffuse7);
	glLightfv(GL_LIGHT7, GL_SPECULAR, light_specula7);
	glLightfv(GL_LIGHT7, GL_POSITION, light_position7);
	glLightf(GL_LIGHT7, GL_SPOT_EXPONENT, 128);

	glLightf(GL_LIGHT7, GL_SPOT_CUTOFF, 30.0);
	glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, spot_direction7);
	
	//=====================DAY/NIGHT COUNT=========================
	lightDay = (sin(timeOfDay) / 2) + 0.5f;
	lightNight = 1.0 - lightDay;
	timeOfDay += 0.05;
	//lightDay = 0;
	//lightNight = 1.0;
	//=====================DRAW SKYBOX=========================
	Draw_Skybox(0, 0, 0, 500, 500, 500);	// Draw the Skybox
	
	glDeleteTextures(1, &SkyboxTexture[SKYBACK]);
	glDeleteTextures(1, &SkyboxTexture[SKYBACK2]);
	glDeleteTextures(1, &SkyboxTexture[SKYDOWN]);
	glDeleteTextures(1, &SkyboxTexture[SKYDOWN2]);
	glDeleteTextures(1, &SkyboxTexture[SKYFRONT]);
	glDeleteTextures(1, &SkyboxTexture[SKYFRONT2]);
	glDeleteTextures(1, &SkyboxTexture[SKYLEFT]);
	glDeleteTextures(1, &SkyboxTexture[SKYLEFT2]);
	glDeleteTextures(1, &SkyboxTexture[SKYRIGHT]);
	glDeleteTextures(1, &SkyboxTexture[SKYRIGHT2]);
	glDeleteTextures(1, &SkyboxTexture[SKYUP]);
	glDeleteTextures(1, &SkyboxTexture[SKYUP2]);


	glFlush(); 
    glPopMatrix();
}

void rysuj()
{
	switch (stereoTryb){
		case 0: // mono
			 rysujRamke (false);
			 glutSwapBuffers(); 
		break;
		case 1: // 3D-ready
			 stereoIDRamki = !stereoIDRamki;
			 rysujRamke (stereoIDRamki);
			 glutSwapBuffers(); 
		break;
		case 2: // pelne stereo
			glutSetWindow(oknoLewe);
			rysujRamke (false);
			glutSetWindow(oknoPrawe);
			rysujRamke  (true);
			glutSetWindow(oknoLewe);
	 		glutSwapBuffers();			// Wyslanie na ekran (L+P) synchronizowane
			glutSetWindow(oknoPrawe);
	 		glutSwapBuffers(); 
		break;
		case 3: // anaglyph
			glColorMask(true, false, false, false);
			rysujRamke (true);
			glClear(GL_DEPTH_BUFFER_BIT);
			glColorMask(false, true, true, false);
			rysujRamke (false);
			glColorMask(true, true, true, true);
			glutSwapBuffers(); 

	}

}

void timer()
{
	double kameraXTmp = kameraX+kameraPredkosc*sin(kameraKat);
    double kameraZTmp = kameraZ-kameraPredkosc*cos(kameraKat);
	kameraKat = kameraKat + kameraPredkoscObrotu;
	kameraPunktY = kameraPunktY + kameraPredkoscPunktY;
	if (wObszarze(kameraXTmp,kameraZTmp))
	{
		kameraX = kameraXTmp;
		kameraZ = kameraZTmp;
	} else 
		kameraPredkosc = 0;
	rysuj();		
}

void syncTimer (int ID)
{
	timer();
	glutTimerFunc(1,syncTimer,10);
}

int main(int argc, char **argv)
{
	#define _KONFIGURACJA
	#include "konfiguracja.cpp"
	if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 's') 	// poprawki w konfiguracji na podstawie parametró (te maj¹ pierwszeñstwo)
	{
		stereoTryb = 2;
		oknoSzerkosc=800;
		oknoWysokosc=600;
	}
	glutInit(&argc, argv);    	// INIT - wszystkie funkcje obs³ugi okna i przetwzrzania zdarzeñ realizuje GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	if (stereoTryb == 2) {
		glutInitWindowSize(oknoSzerkosc-8,oknoWysokosc);
		glutInitWindowPosition(0,0);
		oknoLewe = glutCreateWindow("Lewe");  // ==1
		HWND hwnd = FindWindow(NULL, "Lewe");
		SetWindowLong(hwnd, GWL_STYLE, WS_BORDER | WS_MAXIMIZE);
		glutSetWindow(oknoLewe);
		windowInit();
		glutReshapeFunc (rozmiarLewe);						// def. obs³ugi zdarzenia resize (GLUT)
		glutKeyboardFunc (KlawiszKlawiaturyWcisniety);		// def. obs³ugi klawiatury
		glutSpecialFunc (KlawiszSpecjalnyWcisniety);		// def. obs³ugi klawiatury (klawisze specjalne)
		glutMouseFunc (PrzyciskMyszyWcisniety); 			// def. obs³ugi zdarzenia przycisku myszy (GLUT)
		glutMotionFunc (RuchKursoraMyszy);					// def. obs³ugi zdarzenia ruchu myszy (GLUT)
		glutDisplayFunc(rysuj);								// def. funkcji rysuj¹cej
		glutInitWindowSize(oknoSzerkosc-8,oknoWysokosc);
		glutInitWindowPosition(oknoSzerkosc+4,0);
		oknoPrawe = glutCreateWindow("Prawe"); // ==2
		glutSetWindow(oknoPrawe);
		windowInit();
		hwnd = FindWindow(NULL, "Prawe");
		SetWindowLong(hwnd, GWL_STYLE, WS_BORDER | WS_MAXIMIZE);
		glutReshapeFunc (rozmiarPrawe);						// def. obs³ugi zdarzenia resize (GLUT)
		glutKeyboardFunc (KlawiszKlawiaturyWcisniety);		// def. obs³ugi klawiatury
		glutSpecialFunc (KlawiszSpecjalnyWcisniety);		// def. obs³ugi klawiatury (klawisze specjalne)
		glutMouseFunc (PrzyciskMyszyWcisniety); 			// def. obs³ugi zdarzenia przycisku myszy (GLUT)
		glutMotionFunc (RuchKursoraMyszy);					// def. obs³ugi zdarzenia ruchu myszy (GLUT)
		glutDisplayFunc(rysuj);								// def. funkcji rysuj¹cej



	} else {  // jedno okno
		glutInitWindowSize(oknoSzerkosc,oknoWysokosc);
		glutInitWindowPosition(0,0);
		oknoLewe = glutCreateWindow("Szablon");  
		windowInit();
		glutReshapeFunc (rozmiar);						// def. obs³ugi zdarzenia resize (GLUT)
		glutKeyboardFunc (KlawiszKlawiaturyWcisniety);		// def. obs³ugi klawiatury
		glutSpecialFunc (KlawiszSpecjalnyWcisniety);		// def. obs³ugi klawiatury (klawisze specjalne)
		glutMouseFunc (PrzyciskMyszyWcisniety); 			// def. obs³ugi zdarzenia przycisku myszy (GLUT)
		glutMotionFunc (RuchKursoraMyszy);					// def. obs³ugi zdarzenia ruchu myszy (GLUT)
		glutDisplayFunc(rysuj);								// def. funkcji rysuj¹cej
	}
		if (stereoTryb == 1 || !timing100FPS)
			glutIdleFunc(timer);				
		else 
			glutTimerFunc(10,syncTimer,10);
		resetKamery();
		//srand( (unsigned)time( NULL ) ); // generator liczb losowych
	    ladujModele();
		aktywujSpecjalneRenderowanieModelu("woda",1);
		aktywujSpecjalneRenderowanieModelu("most",2);
		if (oknoFullScreen && stereoTryb != 2) glutFullScreen();
		glutMainLoop();        
	return(0);    
}

void Draw_Skybox(float x, float y, float z, float width, float height, float length)
{
	// Center the Skybox around the given x,y,z position
	x = x - width / 2;
	y = y - 400;
	z = z - length / 2;

	float offset = -2.0f;
	float offsetXYZ = 1.0f;
	float x2 = x + offsetXYZ;
	float y2 = y + offsetXYZ;
	float z2 = z + offsetXYZ;
	float width2 = width + offset;
	float height2 = height + offset;
	float length2 = length + offset;

	glPushMatrix();
	glRotatef(rotateSky, 0.0f, 1.0f, 0.0f);
	//////////////////Nigh Skybox////////////////////////
	// Draw Front side
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[SKYFRONT]);
glDisable(GL_LIGHTING);
	glBegin(GL_QUADS);
	glColor4f(1.0, 1.0, 1.0, lightNight);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glEnd();


	// Draw Back side
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[SKYBACK]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glEnd();

	// Draw Left side
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[SKYLEFT]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glEnd();

	// Draw Right side
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[SKYRIGHT]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glEnd();

	// Draw Up side
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[SKYUP]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glEnd();

	// Draw Down side
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[SKYDOWN]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z);
	glEnd();

	//////////////////DAY Skybox////////////////////////
	// Draw Front side
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[SKYFRONT2]);
	glBegin(GL_QUADS);
	glColor4f(1.0, 1.0, 1.0, lightDay);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x2, y2, z2 + length2);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x2, y2 + height2, z2 + length2);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x2 + width2, y2 + height2, z2 + length2);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x2 + width2, y2, z2 + length2);
	glEnd();


	// Draw Back side
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[SKYBACK2]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x2 + width2, y2, z2);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x2 + width2, y2 + height2, z2);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x2, y2 + height2, z2);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x2, y2, z2);
	glEnd();

	// Draw Left side
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[SKYLEFT2]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x2, y2 + height2, z2);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x2, y2 + height2, z2 + length2);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x2, y2, z2 + length2);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x2, y2, z2);
	glEnd();

	// Draw Right side
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[SKYRIGHT2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x2 + width2, y2, z2);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x2 + width2, y2, z2 + length2);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x2 + width2, y2 + height2, z2 + length2);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x2 + width2, y2 + height2, z2);
	glEnd();

	// Draw Up side
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[SKYUP2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x2 + width2, y2 + height2, z2);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x2 + width2, y2 + height2, z2 + length2);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x2, y2 + height2, z2 + length2);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x2, y2 + height2, z2);
	glEnd();

	// Draw Down side
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[SKYDOWN2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x2, y2, z2);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x2, y2, z2 + length2);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x2 + width2, y2, z2 + length2);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x2 + width2, y2, z2);
	glEnd();
	glEnable(GL_LIGHTING);

	glPopMatrix();
	
	rotateSky += 0.1f;

}