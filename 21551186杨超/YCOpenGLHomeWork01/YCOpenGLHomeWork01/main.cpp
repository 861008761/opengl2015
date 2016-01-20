//
//  main.cpp
//  YCOpenGLHomeWork01
//
//  Created by YC－MacBookPro on 15/12/16.
//  Copyright © 2015年 YC－MacBookPro. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/GLUT.h>
using namespace std;

void myAxis()
{
    //绘制X轴
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    {
        glVertex3f( 0.0f, 0.0f, 0.0f);
        glVertex3f( 50.0f, 0.0f, 0.0f);
        //绘制坐标轴的箭头
        glVertex3f( 50.0f, 0.0f, 0.0f);
        glVertex3f( 49.0f, 1.0f, 0.0f);
        glVertex3f( 50.0f, 0.0f, 0.0f);
        glVertex3f( 49.0f,-1.0f, 0.0f);
    }
    glEnd();
    
    //绘制Y轴
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    {
        glVertex3f( 0.0f, 0.0f, 0.0f);
        glVertex3f( 0.0f, 50.0f, 0.0f);
        glVertex3f( 0.0f, 50.0f, 0.0f);
        glVertex3f( 1.0f, 49.0f, 0.0f);
        glVertex3f( 0.0f, 50.0f, 0.0f);
        glVertex3f( -1.0f, 49.0f, 0.0f);
    }
    glEnd();
    
    //绘制Z轴
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin( GL_LINES );
    {
        glVertex3f( 0.0f, 0.0f, 0.0f );
        glVertex3f( 0.0f, 0.0f, 50.0f );
        glVertex3f( 0.0f, 0.0f, 50.0f );
        glVertex3f( 0.0f, 1.0f, 49.0f );
        glVertex3f( 0.0f, 0.0f, 50.0f );
        glVertex3f( 0.0f, -1.0f, 49.0f);
    }
    glEnd();
}

//x轴和y轴位置
static GLfloat X_Axis = 0.0f;
static GLfloat Y_Axis = 0.0f;

//绘制太阳地球月亮的函数
void myDisplay()
{
    //清除缓冲区（颜色缓冲区、深度缓冲区、模板缓冲区），填充的颜色由glClearColor()指定
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    //开始渲染
    glPushMatrix();
    
    //使用键盘控制X轴、Y轴旋转
    glRotatef(X_Axis, 1.0f, 0.0f, 0.0f);
    glRotatef(Y_Axis, 0.0f, 1.0f, 0.0f);
    //绘制坐标系
    myAxis();
    
    glDisable(GL_LIGHTING);
    
    //绘制太阳
    glColor3f(0.9f, 0.1f, 0.1f);//设置太阳颜色
    glutSolidSphere(10.0f, 30, 30);//后面两个参数越大，绘制的球体越“圆”
    
    //绘制地球
    static GLfloat alpha = 0.0f;
    const GLfloat radius = 20.f;
    glRotatef(alpha, 0, 0, 1);
    glTranslatef(radius, radius, 0);
    glColor3f(0.2f, 0.2f, 0.9f);
    glutSolidSphere(4.0f, 30, 30);
    
    //绘制“月亮”
    glColor3f(1.0f, 1.0f, 0.0f);
    glRotatef(alpha/30.0*360.0 - alpha/360.0*360.0, 0.0f, 0.0f, -1.0f);
    glTranslatef(radius/2, 0.0f, 0.0f);
    glutSolidSphere(1.5f, 40, 40);
    
    //开始旋转
    alpha += 0.3f;
    if (alpha >= 360)
    {
        alpha -= 360;
    }
    //显示所绘制图像
    glPopMatrix();
    
    //使用双缓存，避免刷新时闪烁
    glutSwapBuffers();
}

void myReshape(GLsizei w, GLsizei h)
{
    //如果h为0的情况，w为0的情况呢
    if(!h)
    {
        h = 1;
    }
    //视口映射 把绘图坐标映射到窗口坐标、从逻辑笛卡尔坐标映射到物理屏幕像素坐标
    //视口就是窗口内部用于绘制裁剪区域的客户区域
    //从左下角开始，如果刚好和main函数中WindowSize相同大小，则显示图像刚好，否则有裁剪或者包裹
    glViewport(0, 0, w, h);
    
    //重置投影矩阵
    glMatrixMode(GL_PROJECTION);
    //将之前矩阵变换导致变化过的栈顶矩阵重新归位，置为单位矩阵！等于是之前的矩阵变换带来的影响到此为止了!
    glLoadIdentity();
    
    //正投影（也叫平行投影）设置
    GLfloat Ortho_Parm = 40.0f;//这个参数与绘制的球的半径有关，一般比半径大一些，把球体包裹在里面
    if (w <= h)
    {
        glOrtho(-Ortho_Parm, Ortho_Parm, -Ortho_Parm*h/w, Ortho_Parm*h/w, -Ortho_Parm, Ortho_Parm);
    }
    else
    {
        glOrtho(-Ortho_Parm*w/h, Ortho_Parm*w/h, -Ortho_Parm, Ortho_Parm, -Ortho_Parm, Ortho_Parm);
    }
    //重置模型视图矩阵
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //设置外部观察角度
    gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

//初始化界面
void myInit(void)
{
    //RGB颜色空间
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);//打开深度测试
}

int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,600);
    glutInitWindowPosition (400,200);
    glutCreateWindow("绘制太阳系");
    
    glutDisplayFunc(myDisplay);
    glutIdleFunc (myDisplay);
    
    glutReshapeFunc(myReshape);
    myInit();
    glutMainLoop();
    
    return 0;
}
