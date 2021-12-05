using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace graphics_project1
{
    public partial class Form3 : Form
    {
        private List<Point> pathPoint;
        private Point centerPoint;
        private Graphics g;
        private Pen grayPen;
        private Brush blackBrush;
        private int col;
        private int row;
        private int cellSize;
        private bool drawCenter;
        private bool drawCircle;

        public Form3()
        {
            InitializeComponent();
            pictureBox1.BackColor = Color.White;
            pathPoint = new List<Point>();
            centerPoint = new Point(0, 0);
            grayPen = new Pen(Color.Gray, 1);
            blackBrush = new SolidBrush(Color.Black);
            cellSize = 5;
            col = pictureBox1.Height / cellSize;
            row = pictureBox1.Width / cellSize;
            drawCenter = false;
            drawCircle = false;
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
            // draw center point when drawCenter == true
            if (drawCenter == true)
            {
                Rectangle rect = new Rectangle(centerPoint.X, centerPoint.Y, cellSize, cellSize);
                g.FillRectangle(blackBrush, rect);
            }
            // draw Circle when drawCircle == true
            if (drawCircle == true)
            {
                for (int i = 0; i < pathPoint.Count; ++i)
                {
                    Rectangle rect = new Rectangle(pathPoint[i].X, pathPoint[i].Y, cellSize, cellSize);
                    g.FillRectangle(blackBrush, rect);
                }
            }
        }

        // mouse clicl to select center point
        private void PictureBox1_MouseClick(object sender, MouseEventArgs e)
        {
            centerPoint.X = e.X / cellSize * cellSize;
            centerPoint.Y = e.Y / cellSize * cellSize;
            drawCenter = true;
            pictureBox1.Invalidate();
        }

        // draw circle
        private void Button1_Click(object sender, EventArgs e)
        {
            int R;
            if (!int.TryParse(textBox1.Text, out R))
            {
                MessageBox.Show("半径必须为整数！");
                return;
            }
            if (drawCenter == false)
            {
                MessageBox.Show("必须选定圆的中点！");
                return;
            }
            drawCircle = true;
            BresenhamCircle(centerPoint, R);
            pictureBox1.Invalidate();
        }

        // textbox can only accept int
        private void TextBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!(Char.IsNumber(e.KeyChar)) && e.KeyChar != (char)8)
            {
                e.Handled = true;
            }   
        }

        // clear circle
        private void button2_Click(object sender, EventArgs e)
        {
            if (pathPoint.Count != 0)
            {
                pathPoint.Clear();
            }
            drawCircle = false;
            drawCenter = false;
            pictureBox1.Invalidate();
        }

        // add path point based on the principle of symmetry
        private void AddPoint(Point centerPoint, int x, int y)
        {
            pathPoint.Add(new Point(centerPoint.X + x, centerPoint.Y + y));
            pathPoint.Add(new Point(centerPoint.X + x, centerPoint.Y - y));
            pathPoint.Add(new Point(centerPoint.X - x, centerPoint.Y + y));
            pathPoint.Add(new Point(centerPoint.X - x, centerPoint.Y - y));
            pathPoint.Add(new Point(centerPoint.X + y, centerPoint.Y + x));
            pathPoint.Add(new Point(centerPoint.X + y, centerPoint.Y - x));
            pathPoint.Add(new Point(centerPoint.X - y, centerPoint.Y + x));
            pathPoint.Add(new Point(centerPoint.X - y, centerPoint.Y - x));
        }

        // use Bresenham algorithm to draw circle 
        private void BresenhamCircle(Point centerPoint, int R)
        {
            int x, y, d;
            x = 0;
            y = R * cellSize;
            d = 3 * cellSize * cellSize - 2 * cellSize * R;
            while (x < y)
            {
                AddPoint(centerPoint, x, y);
                if (d < 0)
                {
                    d += 4 * cellSize * x + 6 * cellSize * cellSize;
                }
                else
                {
                    d += 4 * cellSize * (x - y) + 10 * cellSize * cellSize;
                    y -= cellSize;
                }
                x += cellSize;
            }
            if (x == y)
            {
                AddPoint(centerPoint, x, y);
            }
        }
    }
}
