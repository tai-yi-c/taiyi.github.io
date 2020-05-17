using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Timers;
namespace ElevatorSchedule_Beta
{
    public partial class ElevatorSchedule : Form
    {
        int TimeSlice;
        //button
        Button[] floor_updown = new Button[40];
        Button[] elevator = new Button[5];
        //显示器
        Button[] detection = new Button[5];
        //OS类
        OS myOS;
        //电梯内部按钮窗口
        Elevator[] ElevatorForm = new Elevator[5];
        //时钟

        System.Windows.Forms.Timer[] Clock = new System.Windows.Forms.Timer[5];
        public ElevatorSchedule()
        {
            //System.Windows.Forms.Control.CheckForIllegalCrossThreadCalls = false;
            InitializeComponent();
            
        }
        private void initiate(System.Windows.Forms.Timer[] Clock)
        {
            for(int i = 0; i < 5; i++)
            {
                Clock[i].Interval = TimeSlice;
                //Clock[i].Tick+= new EventHandler(Clock_Tick);
                Clock[i].Enabled = true;
                Clock[i].Start();
            }
            Dtimer.Interval= TimeSlice/2;
            Dtimer.Enabled = true;
            Dtimer.Start();
        }
        private void Clock_Tick(object sender, EventArgs e)
        {
            
        }
        private void ElevatorSchedule_Load(object sender, EventArgs e)
        {
            //最大化
            this.WindowState = FormWindowState.Maximized;
            //初始化按钮
            for (int i = 0; i < 40; i++)
            {
                floor_updown[i] = (Button)this.Controls.Find("button" + Convert.ToString(i + 6), true)[0];
                floor_updown[i].Click += new EventHandler(floor_updown_Click);
                floor_updown[i].Name =i.ToString();   
                floor_updown[i].BackColor = Color.Gray; 
            }
            for(int i = 0; i < 5; i++)
            {
                elevator[i]= (Button)this.Controls.Find("button" + Convert.ToString(i + 1), true)[0];
                //初始化电梯窗口
                ElevatorForm[i] = new Elevator();
            }
            //初始化OS类
            myOS = new OS(ElevatorForm,this);
            TimeSlice = myOS.TimeSlice;
            //初始化时钟
            Clock[0] = timer1; Clock[1] = timer2; Clock[2] = timer3; Clock[3] = timer4; Clock[4] = timer5;
            initiate(Clock);
        }
        //系统调用
        private void floor_updown_Click(object sender, System.EventArgs e)
        {
            //点击就更改按键状态
            Button btn = (Button)sender;
            btn.BackColor = Color.Yellow;
            btn.Enabled = false;
            //换算楼层和命令
            int rank = Convert.ToInt32(btn.Name);
            int floor = rank / 2+1;
            Order order;
            if (rank % 2 == 0) order = Order.up;
            else order = Order.down;
            //系统调用
            myOS.Dispatch(floor, order);
        }
        //修改外部按键,修改显示器 在TCB中调用
        public void Refresh(int id,int floor,Status status)
        {
            //修改按钮   name为button 6-45 上下按钮 偶数为上 奇数为下 恢复颜色和可点击属性
            Button btn2;
            //小心换算不要出错
            if (status == Status.up)
            {
                btn2 = (Button)this.Controls.Find(Convert.ToString((floor-1)*2 ), true)[0];
            }
            else
            {
                btn2 = (Button)this.Controls.Find(Convert.ToString((floor - 1) * 2+1), true)[0];
            }
            btn2.BackColor = Color.Gray;
            btn2.Enabled = true;
            
            //修改监视器 button46-button50为监视器
            Button btn1 = (Button)this.Controls.Find("button" + Convert.ToString(id + 46), true)[0];
            btn1.Text = Convert.ToString(floor) + "F";

            Label lab1 = (Label)this.Controls.Find("label" + Convert.ToString(id + 6), true)[0];
            if (status == Status.up) lab1.Text = "运行状态：" + "电梯上行";
            else if (status == Status.down) lab1.Text = "运行状态：" + "电梯下行";
            else lab1.Text = "运行状态：" + "电梯就绪";
        }
        
        //电梯运行画面更新
        public void Move(int id, int floor, Status status) 
        {
            

            //先实现一次移动一格子
            Button btn2 = (Button)this.Controls.Find("button" + Convert.ToString(id + 1), true)[0];
            int x = btn2.Location.X;
            int y = btn2.Location.Y;

            if (status == Status.up)
            {
                btn2.Location = new Point(x, y - pictureBox1.Height);
            }
            else if(status == Status.down)
            {
                btn2.Location = new Point(x, y + pictureBox1.Height);
            }
        }
        public void Alert(int id,int sig)
        {
            Button btn1 = (Button)this.Controls.Find("button" + Convert.ToString(id + 46), true)[0];
            if (sig == 0) {
                btn1.ForeColor = Color.Red;
            }
            else
            {
                btn1.ForeColor = Color.DarkGreen;
            }
                
        }
        public void Pause(int id, Status status)
        {
            Label lab1= (Label)this.Controls.Find("label" + Convert.ToString(id + 6), true)[0];
            if (status == Status.up) lab1.Text = "运行状态：电梯等待内部事件，上行";
            else if (status == Status.down) lab1.Text = "运行状态：电梯等待内部事件，下行";
            else lab1.Text = "运行状态：电梯就绪";
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            myOS.Schedule(1);
        }


        private void button1_Click(object sender, EventArgs e)
        {
            myOS.InForm[0].Text += "1";
            myOS.InForm[0].ShowDialog();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            myOS.InForm[1].Text += "2";
            myOS.InForm[1].ShowDialog();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            myOS.InForm[2].Text += "3";
            myOS.InForm[2].ShowDialog();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            myOS.InForm[3].Text += "4";
            myOS.InForm[3].ShowDialog();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            myOS.InForm[4].Text += "5";
            myOS.InForm[4].ShowDialog();
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            myOS.Schedule(2);
        }

        private void timer3_Tick(object sender, EventArgs e)
        {
            myOS.Schedule(3);
        }

        private void timer4_Tick(object sender, EventArgs e)
        {
            myOS.Schedule(4);
        }

        private void timer5_Tick(object sender, EventArgs e)
        {
            myOS.Schedule(5);
        }

        private void Dtimer_Tick(object sender, EventArgs e)
        {
            myOS.ReDispatch();
        }

        private void label11_Click(object sender, EventArgs e)
        {

        }
    }
}
