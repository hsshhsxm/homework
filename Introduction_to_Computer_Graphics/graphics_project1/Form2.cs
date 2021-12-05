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
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }

        // show draw line form
        private void button1_Click(object sender, EventArgs e)
        {
            var form1 = new Form1();
            form1.Show();
        }

        // show draw circle form
        private void button2_Click(object sender, EventArgs e)
        {
            var form3 = new Form3();
            form3.Show();
        }
    }
}
