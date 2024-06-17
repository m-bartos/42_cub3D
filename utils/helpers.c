// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   helpers.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/06/17 18:40:42 by orezek            #+#    #+#             */
// /*   Updated: 2024/06/17 20:48:45 by orezek           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// # include <math.h>
// # include "../cube.h"

// // Fix fish eye efect on the walls - Probably
// int FixAng(int a)
// {
// 	if(a > 359)
// 	{
// 		a -= 360;
// 	}
// 	if(a < 0)
// 	{
// 		a += 360;
// 	}
// 	return a;
// }

// // Convert degrees to radians
// float degToRad(int a)
// {
// 	return a*M_PI/180.0;
// }
// // What does it do?
// float distance(ax,ay,bx,by,ang)
// {
// 	return cos(degToRad(ang))*(bx-ax)-sin(degToRad(ang))*(by-ay);
// }


// void drawPlayer2D()
// {
//  glColor3f(1,1,0);
//  glPointSize(8);
//  glLineWidth(4);
//  glBegin(GL_POINTS); glVertex2i(px,py); glEnd();
//  glBegin(GL_LINES);  glVertex2i(px,py); glVertex2i(px+pdx*20,py+pdy*20); glEnd();
// }



// // global and static variables are initialized with 0
// void Buttons(unsigned char key,int x,int y)
// {
// 	float px,py,pdx,pdy,pa;

//  	if(key=='a')
// 	{
// 		pa+=5;
// 		pa=FixAng(pa);
// 		pdx=cos(degToRad(pa));
// 		pdy=-sin(degToRad(pa));}

// 	if(key=='d')
// 	{
// 		pa -= 5;
// 		pa = FixAng(pa);
// 		pdx = cos(degToRad(pa));
// 		pdy =- sin(degToRad(pa));
// 	}

//  	if(key=='w')
// 	{
// 		px += pdx * 5;
// 		py += pdy * 5;
// 	}
//  	if(key=='s')
// 	{
// 		px -= pdx * 5;
// 		py -= pdy * 5;
// 	}

//  	glutPostRedisplay();
// }
