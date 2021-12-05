using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Timers;
using System.Windows.Forms;

namespace graphics_project2
{
    public partial class Form1 : Form
    {
        public Point3D[] vertices = new Point3D[8];
        public Edge[] edges = new Edge[12];
        public bool perspective = true;
        public bool parallel = false;
        public bool spin = false;
        System.Timers.Timer timer = new System.Timers.Timer(500);

        public Form1()
        {
            InitializeComponent();
            textBox1.Text = "80";
            textBox2.Text = "70";
            textBox3.Text = "60";
            textBox4.Text = "10";
            label5.Parent = pictureBox1;
            label6.Parent = pictureBox1;
            label7.Parent = pictureBox1;
            label5.BackColor = Color.Transparent;
            label6.BackColor = Color.Transparent;
            label7.BackColor = Color.Transparent;
            Init_Vertices();
            Init_Edges();
        }

        void Init_Vertices()
        {
            vertices[0] = new Point3D(115, 115, 115);
            vertices[1] = new Point3D(115, 115, 215);
            vertices[2] = new Point3D(115, 215, 115);
            vertices[3] = new Point3D(115, 215, 215);
            vertices[4] = new Point3D(215, 115, 115);
            vertices[5] = new Point3D(215, 115, 215);
            vertices[6] = new Point3D(215, 215, 115);
            vertices[7] = new Point3D(215, 215, 215);
        }

        void Init_Edges()
        {
            edges[0] = new Edge
            {
                startPoint = vertices[0],
                endPoint = vertices[1]
            };
            edges[1] = new Edge
            {
                startPoint = vertices[0],
                endPoint = vertices[2]
            };
            edges[2] = new Edge
            {
                startPoint = vertices[0],
                endPoint = vertices[4]
            };
            edges[3] = new Edge
            {
                startPoint = vertices[1],
                endPoint = vertices[3]
            };
            edges[4] = new Edge
            {
                startPoint = vertices[1],
                endPoint = vertices[5]
            };
            edges[5] = new Edge
            {
                startPoint = vertices[2],
                endPoint = vertices[3]
            };
            edges[6] = new Edge
            {
                startPoint = vertices[2],
                endPoint = vertices[6]
            };
            edges[7] = new Edge
            {
                startPoint = vertices[3],
                endPoint = vertices[7]
            };
            edges[8] = new Edge
            {
                startPoint = vertices[4],
                endPoint = vertices[5]
            };
            edges[9] = new Edge
            {
                startPoint = vertices[4],
                endPoint = vertices[6]
            };
            edges[10] = new Edge
            {
                startPoint = vertices[5],
                endPoint = vertices[7]
            };
            edges[11] = new Edge
            {
                startPoint = vertices[6],
                endPoint = vertices[7]
            };
        }

        private void PictureBox1_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            Pen blackPen = new Pen(Color.Black, 1);
            Pen redPen = new Pen(Color.Red, 1);
            Pen grayPen = new Pen(Color.Gray, 1);
            
            g.DrawLine(grayPen, 400, 200, 400, 100);// y
            g.DrawLine(grayPen, 400, 200, 500, 200);// x
            int zx = (int)(200 * Math.Cos(45));
            int zy = (int)(200 * Math.Cos(45));
            g.DrawLine(grayPen, 400, 200, 400 - zx, 200 + zy);// z

            if (perspective)
            {
                for (int i = 0; i < 12; ++i)
                {
                    int xc = Int32.Parse(textBox1.Text);
                    int yc = Int32.Parse(textBox2.Text);
                    int zc = Int32.Parse(textBox3.Text);
                    Point3D cPoint = new Point3D(xc, yc, zc);
                    Point a = Perspective_Projection(cPoint, edges[i].startPoint);
                    Point b = Perspective_Projection(cPoint, edges[i].endPoint);
                    if (i == 1 || i == 2 || i == 6 || i == 9)
                    {
                        g.DrawLine(redPen, a.X + 400, 200 - a.Y, b.X + 400, 200 - b.Y);
                    }
                    else
                    {
                        g.DrawLine(blackPen, a.X + 400, 200 - a.Y, b.X + 400, 200 - b.Y);
                    }
                }
            }
                
            if (parallel)
            {
                for (int i = 0; i < 12; ++i)
                {
                    int xd = Int32.Parse(textBox1.Text);
                    int yd = Int32.Parse(textBox2.Text);
                    int zd = Int32.Parse(textBox3.Text);
                    Point3D dPoint = new Point3D(xd, yd, zd);
                    Point a = Parallel_Projection(dPoint, edges[i].startPoint);
                    Point b = Parallel_Projection(dPoint, edges[i].endPoint);
                    if (i == 1 || i == 2 || i == 6 || i == 9)
                    {
                        g.DrawLine(redPen, a.X + 400, 200 - a.Y, b.X + 400, 200 - b.Y);
                    }
                    else
                    {
                        g.DrawLine(blackPen, a.X + 400, 200 - a.Y, b.X + 400, 200 - b.Y);
                    }
                }
            }
        }

        public Point Perspective_Projection(Point3D cPoint, Point3D point3D)
        {
            Point point2D = new Point
            {
                X = cPoint.x + (point3D.x - cPoint.x) * cPoint.z / (cPoint.z - point3D.z),
                Y = cPoint.y + (point3D.y - cPoint.y) * cPoint.z / (cPoint.z - point3D.z)
            };
            return point2D;
        }
        public Point Parallel_Projection(Point3D dPoint, Point3D point3D)
        {
            Point point2D = new Point
            {
                X = point3D.x - point3D.z * dPoint.x / dPoint.z,
                Y = point3D.y - point3D.z * dPoint.y / dPoint.z
            };
            return point2D;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            // perspective
            perspective = true;
            parallel = false;
            pictureBox1.Invalidate();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            // parallel
            parallel = true;
            perspective = false;
            pictureBox1.Invalidate();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (spin == true)
            {
                spin = false;
            }
            else
            {
                spin = true;
            }
            if (spin)
            {
                timer.Elapsed += new System.Timers.ElapsedEventHandler(Spin_Cube);
                timer.AutoReset = true;
                timer.Enabled = true;
            }
            else
            {
                timer.Stop();
                Init_Vertices();
                Init_Edges();
                pictureBox1.Invalidate();
            }
        }

        private void Spin_Cube(Object source, ElapsedEventArgs e)
        {
            int step = Int32.Parse(textBox4.Text);
            for (int i = 0; i < 8; ++i)
            {
                int cosstep = (int)(Math.Cos(step) * 100);
                int sinstep = (int)(Math.Sin(step) * 100);
                int x = vertices[i].x;
                int z = vertices[i].z;
                vertices[i].x = cosstep * x / 100 + sinstep * z / 100;
                vertices[i].z = cosstep * z / 100 - sinstep * x / 100;
            }
            Init_Edges();
            pictureBox1.Invalidate();
        }
    }

    public class Point3D
    {
        public int x, y, z;
        public Point3D()
        {
            x = 0;
            y = 0;
            z = 0;
        }

        public Point3D(int x_, int y_, int z_)
        {
            x = x_;
            y = y_;
            z = z_;
        }
    }

    public class Edge
    {
        public Point3D startPoint;
        public Point3D endPoint;
        public List<Point> edgePoint;

        public Edge()
        {
            startPoint = new Point3D(0, 0, 0);
            endPoint = new Point3D(0, 0, 0);
            edgePoint = new List<Point>();
        }

        public Edge(Point3D a, Point3D b)
        {
            startPoint = new Point3D();
            endPoint = new Point3D();
            startPoint = a;
            endPoint = b;
            edgePoint = new List<Point>();
        }
    }

}
