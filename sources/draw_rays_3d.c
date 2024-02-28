#include "../includes/cub3d.h"
void draw_3d_rays(t_data *data)
{
    printf("Drawing 3D rays\n");
    
    // Draw a vertical line for each ray
    for (int r = 0; r < 60; r++)
    {
        int lineOff = r * 8 + 530;
        int lineH = 100; // Adjust the line height as needed
        drawLine(lineOff, 160, lineOff, 160 + lineH, data, GREEN);
    }
}

void draw_3d_rays1(t_data *data)
{
    printf("Drawing 3D rays\n");
    int r, mx, my, mp, dof;
    float vx, vy, rx, ry, ra, xo, yo, disV, disH;
    int side;

    ra = FixAng(data->player_1->player_angle + 30); // ray set back 30 degrees

    for (r = 0; r < 60; r++)
    {
        //---Vertical---
        dof = 0;
        side = 0;
        disV = 100000;
        float Tan = tan(degToRad(ra));
        if (cos(degToRad(ra)) > 0.001)
        {
            rx = (((int)data->player_1->player_x >> 6) << 6) + 64;
            ry = (data->player_1->player_x - rx) * Tan + data->player_1->player_y;
            xo = 64;
            yo = -xo * Tan;
        } //looking left
        else if (cos(degToRad(ra)) < -0.001)
        {
            rx = (((int)data->player_1->player_x >> 6) << 6) - 0.0001;
            ry = (data->player_1->player_x - rx) * Tan + data->player_1->player_y;
            xo = -64;
            yo = -xo * Tan;
        } //looking right
        else
        {
            rx = data->player_1->player_x;
            ry = data->player_1->player_y;
            dof = 8;
        } //looking up or down. no hit

        while (dof < 8)
        {
            mx = (int)(rx) >> 6;
            my = (int)(ry) >> 6;
            if (mx >= 0 && mx < data->map->map_width && my >= 0 && my < data->map->map_height)
            {
                mp = my * data->map->map_width + mx;
                if (mp >= 0 && mp < data->map->map_width * data->map->map_height && data->map->map_array[my][mx] == '1')
                {
                    dof = 8;
                    disV = cos(degToRad(ra)) * (rx - data->player_1->player_x) - sin(degToRad(ra)) * (ry - data->player_1->player_y);
                } //hit
                else
                {
                    rx += xo;
                    ry += yo;
                    dof += 1;
                } //check next horizontal
            }
            else
            {
                break;
            }
        }
        vx = rx;
        vy = ry;

        //---Horizontal---
        dof = 0;
        disH = 100000;
        Tan = 1.0 / Tan;
        if (sin(degToRad(ra)) > 0.001)
        {
            ry = (((int)data->player_1->player_y >> 6) << 6) - 0.0001;
            rx = (data->player_1->player_y - ry) * Tan + data->player_1->player_x;
            yo = -64;
            xo = -yo * Tan;
        } //looking up
        else if (sin(degToRad(ra)) < -0.001)
        {
            ry = (((int)data->player_1->player_y >> 6) << 6) + 64;
            rx = (data->player_1->player_y - ry) * Tan + data->player_1->player_x;
            yo = 64;
            xo = -yo * Tan;
        } //looking down
        else
        {
            rx = data->player_1->player_x;
            ry = data->player_1->player_y;
            dof = 8;
        } //looking straight left or right

        while (dof < 8)
        {
            mx = (int)(rx) >> 6;
            my = (int)(ry) >> 6;
            if (mx >= 0 && mx < data->map->map_width && my >= 0 && my < data->map->map_height)
            {
                mp = my * data->map->map_width + mx;
                if (mp >= 0 && mp < data->map->map_width * data->map->map_height && data->map->map_array[my][mx] == '1')
                {
                    dof = 8;
                    disH = cos(degToRad(ra)) * (rx - data->player_1->player_x) - sin(degToRad(ra)) * (ry - data->player_1->player_y);
                } //hit
                else
                {
                    rx += xo;
                    ry += yo;
                    dof += 1;
                } //check next horizontal
            }
            else
            {
                break;
            }
        }

        if (disV < disH)
        {
            rx = vx;
            ry = vy;
            disH = disV;
        } //horizontal hit first

        drawLine(data->player_1->player_x, data->player_1->player_y, rx, ry, data, GREEN);

        int ca = FixAng(data->player_1->player_angle - ra);
        disH = disH * cos(degToRad(ca)); //fix fisheye
        int lineH = (data->map->square_size * 320) / (disH);
        if (lineH > 320)
        {
            lineH = 320;
        }                                 //line height and limit
        int lineOff = 160 - (lineH >> 1); //line offset

        drawLine(r * 8 + 530, lineOff, r * 8 + 530, lineOff + lineH, data, RED);

        ra = FixAng(ra - 1); //go to the next ray
    }
}
