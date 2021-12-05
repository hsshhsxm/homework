using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace graphics_project3
{
    
    public partial class Form1 : Form
    {
        List<Point> points = new List<Point>();
        List<Line> lines = new List<Line>();
        Point startPoint = Point.Empty;
        Point zeroPoint = Point.Empty;
        bool stopDraw = false;
        int line = 0;

        public Form1()
        {
            InitializeComponent();
        }

        // clear drawed
        private void button1_Click(object sender, EventArgs e)
        {
            startPoint = Point.Empty;
            zeroPoint = Point.Empty;
            stopDraw = false;
            lines.Clear();
            points.Clear();
            DrawLines(pictureBox1.CreateGraphics(), zeroPoint, zeroPoint);
            line = 0;
        }

        // mouse move, rubber band
        private void PictureBox1_MouseMove(object sender, MouseEventArgs e)
        {
            if (!startPoint.IsEmpty && !stopDraw)
            {
                DrawLines(pictureBox1.CreateGraphics(), startPoint, e.Location);
            }
        }

        // click once to select point
        private void pictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                if (startPoint.IsEmpty)
                {
                    startPoint = e.Location;
                    zeroPoint = e.Location;
                    points.Add(startPoint);
                }
                else
                {
                    Line tmp = new Line(startPoint, e.Location);
                    lines.Add(tmp);
                    startPoint = e.Location;
                    points.Add(startPoint);
                }
            }
        }

        // double click to end select point and fill color
        private void PictureBox1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            if (startPoint.IsEmpty)
                return;
            if (points.Count < 3)
            {
                MessageBox.Show("At least 3 points!");
                return;
            }
            if (!stopDraw)
            {
                Line tmp = new Line(startPoint, e.Location);
                lines.Add(tmp);
                startPoint = e.Location;
                points.Add(startPoint);
                DrawLines(pictureBox1.CreateGraphics(), startPoint, zeroPoint);
                tmp = new Line(startPoint, zeroPoint);
                lines.Add(tmp);
                stopDraw = true;
                polygonScan(pictureBox1.CreateGraphics());
            }
        }

        private void polygonScan(Graphics g)
        {
            // count max y and min y
            int maxY = 0;
            int minY = pictureBox1.Height;
            for (int i = 0; i < points.Count; i++)
            {
                if (points[i].Y > maxY)
                {
                    maxY = points[i].Y;
                }
                if (points[i].Y < minY)
                {
                    minY = points[i].Y;
                }
            }
            // init ET
            List<EDGE>[] edges = new List<EDGE>[maxY - minY + 1];
            for (int i = 0; i < edges.Length; i++)
            {
                edges[i] = new List<EDGE>();
            }
            InitET(edges, minY);
            // fill color
            List<EDGE> AEL = new List<EDGE>();
            Pen redPen = new Pen(Color.Red, 1);
            for (int i = minY; i < maxY; i++)
            {
                InsertEdgesToAEL(edges[i - minY], ref AEL);
                for (int j = 0; j < AEL.Count; j += 2)
                {
                    g.DrawLine(redPen, new Point((int)AEL[j].GetX(), i), new Point((int)AEL[j + 1].GetX(), i));
                }
                line = i;
                AEL.RemoveAll(IsEdgeInactive);
                AEL.ForEach(UpdateEdge);
                My_Sort(ref AEL);
            }
        }

        private void InitET(List<EDGE>[] edges, int minY)
        {
            List<int> tmpList = new List<int>();
            EDGE e;
            for (int i = 0; i < points.Count; i++)
            {
                Point start = points[i];
                Point end = points[(i + 1) % points.Count];
                Point prevStart = points[(i - 1 + points.Count) % points.Count];
                Point afterEnd = points[(i + 2) % points.Count];
                if (start.Y != end.Y)
                {
                    e = new EDGE();
                    e.SetDx(start, end);
                    if (end.Y > start.Y)
                    {
                        e.SetX((double)start.X);
                        if (afterEnd.Y >= end.Y)
                            e.SetYmax(end.Y - 1);
                        else
                            e.SetYmax(end.Y);
                        edges[start.Y - minY].Add(e);
                        tmpList.Add(start.Y - minY);
                    }
                    else
                    {
                        e.SetX((double)end.X);
                        if (prevStart.Y >= start.Y)
                            e.SetYmax(start.Y - 1);
                        else
                            e.SetYmax(start.Y);
                        edges[end.Y - minY].Add(e);
                        tmpList.Add(end.Y - minY);
                    }
                }
            }
            for (int i = 0; i < tmpList.Count; i++)
            {
                My_Sort(ref edges[tmpList[i]]);
            }
        }

        private void InsertEdgesToAEL(List<EDGE> edgeList, ref List<EDGE> AEL)
        {
            if (AEL.Count == 0)
            {
                AEL = edgeList;
                return;
            }
            List<EDGE> tmp = new List<EDGE>();
            int i = 0, j = 0;
            while (i < edgeList.Count && j < AEL.Count)
            {
                if (edgeList[i] == AEL[j])
                {
                    i++;
                    tmp.Add(AEL[j]);
                    j++;
                    continue;
                }
                if (edgeList[i] < AEL[j])
                {
                    tmp.Add(edgeList[i]);
                    i++;
                    continue;
                }
                if (edgeList[i] > AEL[j])
                {
                    tmp.Add(AEL[j]);
                    j++;
                    continue;
                }
            }
            while (i < edgeList.Count)
            {
                tmp.Add(edgeList[i]);
                i++;
            }
            while (j < AEL.Count)
            {
                tmp.Add(AEL[j]);
                j++;
            }
            AEL = tmp;
        }

        private void DrawLines(Graphics g, Point start, Point end)
        {
            BufferedGraphicsContext context = BufferedGraphicsManager.Current;
            BufferedGraphics bg = context.Allocate(g, new Rectangle(0, 0, pictureBox1.Width, pictureBox1.Height));
            bg.Graphics.Clear(Color.White);
            foreach (Line line in lines)
            {
                line.Draw(bg.Graphics);
            }
            bg.Graphics.DrawLine(SystemPens.ControlText, start, end);
            bg.Render();
            bg.Dispose();
        }

        private class Line
        {
            private Point start;
            private Point end;

            public Line(Point start_, Point end_)
            {
                this.start = start_;
                this.end = end_;
            }

            public void Draw(Graphics g)
            {
                Pen blackPen = new Pen(Color.Black, 1);
                g.DrawLine(blackPen, start, end);
            }

            public Point getStartPoint()
            {
                return start;
            }
            public Point getEndPoint()
            {
                return end;
            }
        }

        private class EDGE
        {
            private double x; // ET中表示边的下端点的x坐标，在AEL中则表示边与扫描线的交点的坐标
            private double dx; // 边的斜率的倒数
            private int ymax; // 边的上端点的y坐标；
            public void SetDx(Point a, Point b) { dx = (double)(b.X - a.X) / (double)(b.Y - a.Y); }
            public void SetX(double x_) { x = x_; }
            public void SetYmax(int y) { ymax = y; }
            public double GetX() { return x; }
            public double GetDx() { return dx; }
            public int GetYmax() { return ymax; }
            public static bool operator <(EDGE a, EDGE b)
            {
                return (Math.Abs(a.x - b.x) < 1 ? a.dx < b.dx : a.x < b.x);
            }
            public static bool operator >(EDGE a, EDGE b)
            {
                return (Math.Abs(a.x - b.x) < 1 ? a.dx > b.dx : a.x > b.x);
            }
            public static bool operator ==(EDGE a, EDGE b)
            {
                return (Math.Abs(a.x - b.x) < 1 ? a.dx == b.dx : a.x == b.x);
            }
            public static bool operator !=(EDGE a, EDGE b)
            {
                return (Math.Abs(a.x - b.x) > 1 ? a.dx != b.dx : a.x != b.x);
            }
        }
        private bool IsEdgeInactive(EDGE e)
        {
            return line == e.GetYmax();
        }
        private void UpdateEdge(EDGE e)
        {
            e.SetX(e.GetX() + e.GetDx());
        }
        private void My_Sort(ref List<EDGE> list)
        {
            EDGE d = new EDGE();
            for (int i = 0; i < list.Count - 1; i++)
            {
                for (int j = i + 1; j < list.Count; j++)
                {
                    if (list[j] < list[i])
                    {
                        d = list[j];
                        list[j] = list[i];
                        list[i] = d;
                    }
                }
            }
        }
    }
}
