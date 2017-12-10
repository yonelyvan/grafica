// g++ test.cpp -o m `pkg-config --cflags --libs opencv` -std=c++11
#include "opencv2/opencv.hpp"
#include "opencv2/opencv.hpp"
#include <dirent.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#define X first
#define Y second
#define show(X) cout << #X << " : " << X << endl;
#define PI 3.14159265
using namespace cv;
using namespace std;

// DAVID : recivir una carpeta de fotos y retornar una carpeta de archivos de puntos
typedef pair<int, int> point;
typedef vector<point> v_points;
vector<string> v_archivos;

v_points VP;

void leer_arch_carp(string carpeta, vector<string> &v_F){
    // in: nombre de la carpeta , vector que almacena los nombres
    DIR *d;
    struct dirent *dir;
    int i = 0;
    d = opendir(carpeta.c_str());

    if (d){
        while ((dir = readdir(d)) != NULL){
            i++;
            v_F.push_back(dir->d_name);
        }

        closedir(d);
    }
}

// escribir puntos blancos en fichero
void print_poits(int num_arch){
    int num_points = VP.size();
    char num_str[20];
    string ruta = "points/points"+to_string(num_arch)+".txt";
    show(num_points);
    ofstream myfile;
    myfile.open(ruta);
    for (int i = 0; i < VP.size(); ++i){
        myfile << VP[i].X << " " << 480 - VP[i].Y << " " << 0 << '\n';
    }
    myfile.close();
}

void test(string ruta, int num_arch){
    int threshold = 240;
    Mat img = imread(ruta);
    //imshow("img", img); //imagen original
                        //para mejoras aplicar filtros como blur gaus ... para eliminar ruido
                        //1)imagen a griz
    Mat img_gray;
    cvtColor(img, img_gray, CV_BGR2GRAY);
    //imshow("gris", img_gray);
    //2) extraer contornos
    Mat contornos;
    Canny(img_gray, contornos, threshold, threshold * 2, 5, true);
    imshow("contornos", contornos);
    //2) obtener puntos de los contornos
    vector<vector<Point> > p_contornos;
    //findContours( contours, found_contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    findContours(contornos, p_contornos, RETR_LIST, CV_CHAIN_APPROX_NONE); //CV_CHAIN_APPROX_SIMPLE);

    //guardar puntos en un vector de puntos (VP)
    for (int i = 0; i < p_contornos.size(); ++i){
        for (int j = 0; j < p_contornos[i].size(); ++j){
            int xx = p_contornos[i][j].x;
            int yy = p_contornos[i][j].y;
            VP.push_back(point(xx, yy)); //y:filas x:columnas
        }
    }
    if (waitKey(1e3) == 27){
        cout << "OK" << endl;
    }
    print_poits(num_arch);
    VP.clear();         // Limpiar el vector para una nueva imagen
}

int main(int argc, char **argv){
    string nom_carpeta = "data-imgs";
    string ruta ;
    leer_arch_carp(nom_carpeta, v_archivos);

    // Lee todo el vector de archivos
    for (int i = 1; i < v_archivos.size() - 1; i++){
        cout << "nombre [" << i << "] : " << v_archivos[i] << endl;
        ruta = nom_carpeta + "/" + v_archivos[i];
        test(ruta,i);
    }
    // print_poits();
    return 0;
}
