#include <GL/freeglut.h>
#include "vector_operation.h"
#include "matrix_operation.h"
#include "obj_functions.h"

/*
* 
* Luis Angel Sanchez Muñiz
* Graficación por computadora
* 29 Noviembre 2023
* 
* Uso de teclado
*   Tecla s = reinicia la animacion
*   Tecla a = Aumenta velocidad de camara a la izquierda 
*   Tecla d = Disminuye velocidad de camara a la derecha 
* 
* Uso de mouse
*   Click = cambia color de fondo (simulando cambio de oceano)
* 
*/

vector<double> ambLight = { 0.5,0.5,0.8 };
vector<double> dfLight = { 0.8,0.1,0.3 };
vector<double> dfPos = { 0.0, 0.0, 5.0 };
vector<double> dfPoint = { 0.0, 0.0, 0.0 };
vector<double> dfDirection;

double curveMove = 0;
double rotateObj = 0;
int sea = 0;
float cameraRotationAngle = 0.0f;

vector<vector<double>> seaColors = {
    {0.113,0.2,0.290},
    {0.105,0.160,0.319},
    {0.074,0.329,0.282}
};

void mouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        sea = (sea + 1) % 3;
        glClearColor(seaColors[sea][0], seaColors[sea][1], seaColors[sea][2], 1.0);
    }
}

void changeAnimation(unsigned char key, int x, int y) {
    const float rotationSpeed = 2.0f;

    if (key == 's') {
        curveMove = 0;
    }
    else if (key == 'a') {
        cameraRotationAngle += rotationSpeed;
    }
    else if (key == 'd') {
        cameraRotationAngle -= rotationSpeed;
    }
}

double getIluminationFactor(vector<vector<double>> nextVertex, vector<double> dfDirection) {
    vector<double> A = { nextVertex[0][0],nextVertex[0][1],nextVertex[0][2] };
    vector<double> B = { nextVertex[1][0],nextVertex[1][1],nextVertex[1][2] };
    vector<double> C = { nextVertex[2][0],nextVertex[2][1],nextVertex[2][2] };

    vector<double> normal = normalize(
        crossProduct(
            subtractVectors(B, A),
            subtractVectors(C, A)
        )
    );

    double factor = dotProduct(dfDirection, normal);
    if (factor < 0) factor = 0;

    return factor;
}

void initLight() {
    cout << "que onda" << endl;
     dfDirection = normalize(subtractVectors(dfPoint, dfPos));
}

void display()
{
    glRotatef(cameraRotationAngle, 0.0f, 1.0f, 0.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_TRIANGLES);

    Object obj = objects[0];
    matrix = matrixBezier(curveMove);
    for (const Face& face : obj.faces) {
            
        vector<vector<double>> nextVertex;
        for (size_t i = 0; i < 3; ++i) {
            double x = obj.vertices[face.vertexIndices[i]].x;
            double y = obj.vertices[face.vertexIndices[i]].y;
            double z = obj.vertices[face.vertexIndices[i]].z;

            vector<double>nextPos = multiplyMatrix(matrix, x, y, z);

            nextVertex.push_back({ nextPos[0], nextPos[1], nextPos[2]});
        }

        double factor = getIluminationFactor(nextVertex, dfDirection);
        glColor3f(
            0.4 * ambLight[0] + dfLight[0] * factor,
            0.4 * ambLight[1] + dfLight[1] * factor,
            0.4 * ambLight[2] + dfLight[2] * factor
        );
                
        for (auto v : nextVertex) {
            glVertex3f(v[0], v[1], v[2]);
        }
            
    } 
    
    obj = objects[1];
    matrix = matrixRotated(rotateObj);

    for (const Face& face : obj.faces) {
        vector<double> color = { 0.72, 0.45, 0.2 };

        vector<vector<double>> nextVertex;

        for (size_t i = 0; i < 3; ++i) {
            double x = obj.vertices[face.vertexIndices[i]].x;
            double y = obj.vertices[face.vertexIndices[i]].y;
            double z = obj.vertices[face.vertexIndices[i]].z;
            vector<double> mat2 = { x,y,z,1 };

            vector<double> res = resMatrixRotated(mat2, matrix);

            nextVertex.push_back({ res[0], res[1], res[2] });
        }

        double factor = getIluminationFactor(nextVertex, dfDirection);

        glColor3f(
            color[0] * ambLight[0] + dfLight[0] * factor,
            color[1] * ambLight[1] + dfLight[1] * factor,
            color[2] * ambLight[2] + dfLight[2] * factor
        );


        for (auto v : nextVertex) {
            glVertex3f(v[0], v[1], v[2]);
        }
    }

    obj = objects[2];

    for (const Face& face : obj.faces) {
        vector<double> color = { 0.72, 0.45, 0.2 };
        vector<vector<double>> nextVertex;

        for (size_t i = 0; i < 3; ++i) {
            double x = obj.vertices[face.vertexIndices[i]].x;
            double y = obj.vertices[face.vertexIndices[i]].y;
            double z = obj.vertices[face.vertexIndices[i]].z;
            vector<double> mat2 = { x,y,z,1 };

            vector<double> res = resMatrixRotated(mat2, matrix);

            nextVertex.push_back({ res[0], res[1], res[2] });
        }

        double factor = getIluminationFactor(nextVertex, dfDirection);
        
        glColor3f(
            color[0] * ambLight[0] + dfLight[0] * factor,
            color[1] * ambLight[1] + dfLight[1] * factor,
            color[2] * ambLight[2] + dfLight[2] * factor
        );


        for (auto v : nextVertex) {
            glVertex3f(v[0], v[1], v[2]);
        }
    }
    
    obj = objects[3];
    matrix = {
        {1, 0, 0, -4},
        {0, 1, 0, -6},
        {0, 0, 1, -2},
        {0, 0, 0, 1}
    };

    for (const Face& face : obj.faces) {

        vector<vector<double>> nextVertex;
        for (size_t i = 0; i < 3; ++i) {
            double x = obj.vertices[face.vertexIndices[i]].x;
            double y = obj.vertices[face.vertexIndices[i]].y;
            double z = obj.vertices[face.vertexIndices[i]].z;

            vector<double>nextPos = multiplyMatrix(matrix, x, y, z);

            nextVertex.push_back({ nextPos[0], nextPos[1], nextPos[2] });
        }

        double factor = getIluminationFactor(nextVertex, dfDirection);

        glColor3f(
            0.69 * ambLight[0] + dfLight[0] * factor,
            0.0 * ambLight[1] + dfLight[1] * factor,
            0.16 * ambLight[2] + dfLight[2] * factor
        );

        for (auto v : nextVertex) {
            glVertex3f(v[0], v[1], v[2]);
        }

    }
    
    obj = objects[4];

    for (const Face& face : obj.faces) {

        vector<vector<double>> nextVertex;
        for (size_t i = 0; i < 3; ++i) {
            double x = obj.vertices[face.vertexIndices[i]].x;
            double y = obj.vertices[face.vertexIndices[i]].y;
            double z = obj.vertices[face.vertexIndices[i]].z;

            vector<double>nextPos = multiplyMatrix(matrix, x, y, z);

            nextVertex.push_back({ nextPos[0], nextPos[1], nextPos[2] });
        }

        double factor = getIluminationFactor(nextVertex, dfDirection);

        glColor3f(
            0.57 * ambLight[0] + dfLight[0] * factor,
            0.54 * ambLight[1] + dfLight[1] * factor,
            0.505 * ambLight[2] + dfLight[2] * factor
        );

        for (auto v : nextVertex) {
            glVertex3f(v[0], v[1], v[2]);
        }

    }

    if (curveMove >= 0.6) {
        rotateObj += 0.1;
        if(curveMove <= 1) curveMove += t;
    }else {
        curveMove += t;
    }

    glEnd();
    glFlush();
    glutSwapBuffers();
}

void init(void)
{
    glClearColor(seaColors[sea][0], seaColors[sea][1], seaColors[sea][2], 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 800.0 / 600.0, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 10.0, -20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);
}


int main(int argc, char** argv)
{
    string objFile = "tiburon.obj";
    string objFile2 = "boya.obj";
    string objFile3 = "palo.obj";
    string objFile4 = "lava.obj";
    string objFile5 = "piedra.obj";

    loadOBJ(objFile);
    loadOBJ(objFile2);
    loadOBJ(objFile3);
    loadOBJ(objFile4);
    loadOBJ(objFile5);
    initLight();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Modelado 3D");
    init();
    glutKeyboardFunc(changeAnimation);
    glutMouseFunc(mouseButton);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();

    return 0;
}

