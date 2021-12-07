using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace graphics_project4
{
    public partial class Form1 : Form
    {
        List<PointF> points = new List<PointF>();
        List<PointF> curve = new List<PointF>();
        bool stopDraw = false;
        bool changeCurve = false;
        int selectedIndex = -1;

        public Form1()
        {
            InitializeComponent();
        }

        // click once to add a point or select a point
        private void PictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
            if (!stopDraw)
            {
                if (e.Button == MouseButtons.Left)
                {
                    points.Add(e.Location);
                    points = points.Distinct().ToList();
                }
                if (points.Count > 2)
                {
                    DrawCurve(PictureBox1.CreateGraphics());
                }
            }
            if (stopDraw)
            {
                for (int i = 0; i < points.Count; i++)
                {
                    if (Math.Abs(e.Location.X - points[i].X) < 10 && Math.Abs(e.Location.Y - points[i].Y) < 10)
                    {
                        selectedIndex = i;
                        changeCurve = true;
                        return;
                    }
                }
            }
        }

        // end change curve
        private void PictureBox1_MouseUp(object sender, MouseEventArgs e)
        {
            if (stopDraw && changeCurve)
            {
                points[selectedIndex] = e.Location;
                DrawFinalLine(PictureBox1.CreateGraphics());
                changeCurve = false;
            }
        }

        // click twice to end
        private void PictureBox1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            if (points.Count < 3)
            {
                MessageBox.Show("At least 3 points!");
                return;
            }
            if (!stopDraw)
            {
                points.Add(e.Location);
                points = points.Distinct().ToList();
                DrawFinalLine(PictureBox1.CreateGraphics());
            }
            stopDraw = true;
        }

        // move mouse to select point or change curve
        private void PictureBox1_MouseMove(object sender, MouseEventArgs e)
        {
            if (points.Count != 0 && !stopDraw)
            {
                DrawRubberLine(PictureBox1.CreateGraphics(), points.Last(), e.Location);
            }
            if (stopDraw && changeCurve)
            {
                points[selectedIndex] = e.Location;
                DrawFinalLine(PictureBox1.CreateGraphics());
                DrawCurve(PictureBox1.CreateGraphics());
            }
        }

        // draw lines, rubber band
        private void DrawRubberLine(Graphics g, PointF start, PointF end)
        {
            BufferedGraphicsContext context = BufferedGraphicsManager.Current;
            BufferedGraphics bg = context.Allocate(g, new Rectangle(0, 0, PictureBox1.Width, PictureBox1.Height));
            bg.Graphics.Clear(Color.White);
            for (int i = 0; i < points.Count - 1; ++i)
            {
                bg.Graphics.DrawLine(SystemPens.ControlText, points[i], points[i+1]);
                bg.Graphics.FillRectangle(Brushes.Black, points[i].X, points[i].Y, 4, 4);
            }
            Pen redPen = new Pen(Color.Red);
            for (int i = 0; i < curve.Count; i += 2)
            {
                bg.Graphics.DrawLine(redPen, curve[i], curve[i + 1]);
            }
            bg.Graphics.DrawLine(SystemPens.ControlText, start, end);
            bg.Graphics.FillRectangle(Brushes.Black, points.Last().X, points.Last().Y, 4, 4);
            bg.Render();
            bg.Dispose();
        }

        private void DrawFinalLine(Graphics g)
        {
            BufferedGraphicsContext context = BufferedGraphicsManager.Current;
            BufferedGraphics bg = context.Allocate(g, new Rectangle(0, 0, PictureBox1.Width, PictureBox1.Height));
            bg.Graphics.Clear(Color.White);
            for (int i = 0; i < points.Count - 1; ++i)
            {
                bg.Graphics.DrawLine(SystemPens.ControlText, points[i], points[i + 1]);
                bg.Graphics.FillRectangle(Brushes.Black, points[i].X, points[i].Y, 4, 4);
                if (i == points.Count - 2)
                {
                    bg.Graphics.FillRectangle(Brushes.Black, points[i+1].X, points[i+1].Y, 4, 4);
                }
            }
            Pen redPen = new Pen(Color.Red);
            for (int i = 0; i < curve.Count; i += 2)
            {
                bg.Graphics.DrawLine(redPen, curve[i], curve[i + 1]);
            }
            bg.Render();
            bg.Dispose();
        }

        private void CurveSplit(List<PointF> P, ref List<PointF> Q, ref List<PointF> R)
        {
            int n = P.Count - 1;
            for (int i = 0; i <= n; i++)
            {
                Q.Add(P[i]);
            }
            for (int i = 0; i <= n; ++i)
            {
                R.Add(new PointF());
            }
            for (int i = 1; i <= n; ++i)
            {
                R[n + 1 - i] = Q[n];
                for (int j = n; j >= i; --j)
                {
                    PointF tmp = new PointF((Q[j - 1].X + Q[j].X) / 2, (Q[j - 1].Y + Q[j].Y) / 2);
                    Q[j] = tmp;
                }
            }
            R[0] = Q[n];
        }

        private void DrawCurve(Graphics g)
        {
            if (points.Count < 3)
                return;
            curve.Clear();
            List<PointF> P = new List<PointF>();
            for (int i = 0; i < points.Count; ++i)
            {
                P.Add(points[i]);
            }
            List<PointF> Q = new List<PointF>();
            List<PointF> R = new List<PointF>();
            List<PointF> P1 = new List<PointF>();
            Stack<List<PointF>> stack = new Stack<List<PointF>>();
            stack.Push(P);
            while (stack.Count > 0)
            {
                P1 = stack.Pop();
                float maxD = 0;
                int n = P1.Count - 1;
                for (int i = 1; i <= n - 1; ++i)
                {
                    if (CountDistance(P1[i], P1[0], P1[n]) > maxD)
                    {
                        maxD = CountDistance(P1[i], P1[0], P1[n]);
                    }
                }
                if (maxD <= 1)
                {
                    curve.Add(P1[0]);
                    curve.Add(P1[n]);
                }
                else
                {
                    CurveSplit(P1, ref Q, ref R);
                    List <PointF> tmpQ = new List<PointF>();
                    for (int i = 0; i < Q.Count; ++i)
                    {
                        tmpQ.Add(Q[i]);
                    }
                    List<PointF> tmpR = new List<PointF>();
                    for (int i = 0; i < R.Count; ++i)
                    {
                        tmpR.Add(R[i]);
                    }
                    stack.Push(tmpQ);
                    stack.Push(tmpR);
                    Q.Clear();
                    R.Clear();
                }
            }
        }

        private float CountDistance(PointF pi, PointF p0, PointF pn)
        {
            double a = Math.Sqrt(Math.Pow(pi.X - p0.X, 2) + Math.Pow(pi.Y - p0.Y, 2));
            double b = Math.Sqrt(Math.Pow(pi.X - pn.X, 2) + Math.Pow(pi.Y - pn.Y, 2));
            double c = Math.Sqrt(Math.Pow(pn.X - p0.X, 2) + Math.Pow(pn.Y - p0.Y, 2));
            double s = (a + b + c) / 2;
            double d = 2 * Math.Sqrt(s * (s - a) * (s - b) * (s - c)) / c;
            return (float)d;
        }

        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            points.Clear();
            curve.Clear();
            DrawFinalLine(PictureBox1.CreateGraphics());
            stopDraw = false;
            changeCurve = false;
            selectedIndex = -1;
        }
    }
}
