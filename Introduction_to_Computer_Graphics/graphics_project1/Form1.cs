using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace graphics_project1
{
    public partial class Form1 : Form
    {

        private List<Point> pathPoint;
        private List<Point> endPoint;
        private Graphics g;
        private Pen grayPen;
        private Brush blackBrush;
        private PictureBox pictureBox1;
        private int col;
        private int row;
        private int cellSize;
        private bool drawLine;

        public Form1()
        {
            InitializeComponent();
            pictureBox1.BackColor = Color.White;
            pathPoint = new List<Point>();
            endPoint = new List<Point>();
            grayPen = new Pen(Color.Gray, 1);
            blackBrush = new SolidBrush(Color.Black);
            cellSize = 5;
            col = pictureBox1.Height / cellSize;
            row = pictureBox1.Width / cellSize;
            drawLine = false;
        }

        private void PictureBox1_Paint(object sender, PaintEventArgs e)
        {
            g = e.Graphics;
            // Horizontal line
            for (int i = 0; i <= col; ++i)
            {
                g.DrawLine(grayPen, 0, i * cellSize, row * cellSize, i * cellSize);
            }
            // Vertical line
            for (int i = 0; i <= row; ++i)
            {
                g.DrawLine(grayPen, i * cellSize, 0, i * cellSize, col * cellSize);
            }
            // draw end point when selected
            for (int i = 0; i < endPoint.Count; ++i)
            {
                Rectangle rect = new Rectangle(endPoint[i].X, endPoint[i].Y, cellSize, cellSize);
                g.FillRectangle(blackBrush, rect);
            }
            // draw line when drawLine == true
            if (drawLine == true)
            {
                for (int i = 0; i < pathPoint.Count; ++i)
                {
                    Rectangle rect = new Rectangle(pathPoint[i].X, pathPoint[i].Y, cellSize, cellSize);
                    g.FillRectangle(blackBrush, rect);
                }
            }
        }

        // mouse click to select point
        private void PictureBox1_MouseClick(object sender, MouseEventArgs e)
        {
            endPoint.Add(new Point(e.X / cellSize * cellSize, e.Y / cellSize * cellSize));
            pictureBox1.Invalidate();
        }

        // draw line
        private void Button1_Click(object sender, EventArgs e)
        {         
            if (endPoint.Count != 2)
            {
                MessageBox.Show("端点数必须为2！");
                return;
            }
            drawLine = true;
            BresenhamLine(endPoint[0], endPoint[1]);
            pictureBox1.Invalidate();
        }

        // clear line
        private void Button2_Click(object sender, EventArgs e)
        {
            if (pathPoint.Count != 0)
            {
                pathPoint.Clear();
            }
            if (endPoint.Count != 0)
            {
                endPoint.Clear();
            }
            drawLine = false;
            pictureBox1.Invalidate();
        }

        // use Bresenham algorithm to draw line
        private void BresenhamLine(Point startPoint, Point endPoint)
        {
            int x = startPoint.X, y = startPoint.Y;
            int dx = Math.Abs(endPoint.X - startPoint.X);
            int dy = Math.Abs(endPoint.Y - startPoint.Y);
            int s1, s2, tmp, interChange, f;
            if (endPoint.X - startPoint.X >= 0)
            {
                s1 = cellSize;
            }
            else
            {
                s1 = 0 - cellSize;
            }
            if (endPoint.Y - startPoint.Y >= 0)
            {
                s2 = cellSize;
            }
            else
            {
                s2 = 0 - cellSize;
            }
            if (dy > dx) 
            {
                tmp = dx;
                dx = dy;
                dy = tmp;
                interChange = 1;
            }
            else 
            {
                interChange = 0;
            }
            f = 2 * dy - dx;
            for (int i = 1; i < dx + 1; i += cellSize)
            {
                Point tmpPoint = new Point(x, y);
                pathPoint.Add(tmpPoint);
                if (f > 0)
                {
                    if (interChange == 1)
                    {
                        x += s1;
                    }
                    else 
                    {
                        y += s2;
                    }
                    f -= 2 * dx;
                }
                if (interChange == 1)
                {
                    y += s2;
                }
                else 
                {
                    x += s1;
                }
                f += 2 * dy;
            }
        }
    }
}